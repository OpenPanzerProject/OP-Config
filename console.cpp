#include "console.h"

Console::Console()
{
    // Objects
    // ---------------------------------------------------------------------------------------------------------------------------------->>
        serial = new QSerialPort(this);
        // setSettingsRestoredOnClose will be deprecated in QT 6 and beyond. If true, it means QSerialPort will restore the
        // previous settings on close, which is the default. Some have found that if prior to opening the DTR was low, QSerialPort
        // will set DTR back to low on disconnect. In our case that is not really a terrible problem (it resets the device, which we
        // may want to do anyway). The bigger issue is resetting on connect, but we have sort of found a way to work around that.
        // Sadly, regardless of what we put this setting to or any other, I can not get QSerialPort to behave consistently with regards
        // to DTR on open.
        serial->setSettingsRestoredOnClose(false);


    // ---------------------------------------------------------------------------------------------------------------------------------->>
    // Signals and Slots
    // ---------------------------------------------------------------------------------------------------------------------------------->>
    // Console Connection connections
        connect(this, SIGNAL(ConnectionChanged(boolean)), this, SLOT(ProcessConnectionChange(boolean)));

    // Serial connections
        connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
        connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
}

void Console::begin()
{
    Connected = false;
    NumErrors = 0;
    ClearResponseData();
}


//------------------------------------------------------------------------------------------------------------------------>>
// PORT: OPEN, CLOSE, ETC
//------------------------------------------------------------------------------------------------------------------------>>
void Console::updatePortSettings(QString comName)
{

    #define USB_BAUD_RATE           QSerialPort::Baud115200

    currentPortSettings.name = comName;
    currentPortSettings.baudRate = USB_BAUD_RATE;
        currentPortSettings.stringBaudRate = QString::number(currentPortSettings.baudRate);
    currentPortSettings.dataBits = QSerialPort::Data8;
        currentPortSettings.stringDataBits = QStringLiteral("8");
    currentPortSettings.parity = QSerialPort::NoParity;
        currentPortSettings.stringParity = tr("None");
    currentPortSettings.stopBits = QSerialPort::OneStop;
        currentPortSettings.stringStopBits = QStringLiteral("1");
    currentPortSettings.flowControl = QSerialPort::NoFlowControl;   // We don't want hardware flow control
        currentPortSettings.stringFlowControl = tr("None");
}

void Console::openSerial(void)
{
    serial->setPortName(currentPortSettings.name);
    serial->setBaudRate(currentPortSettings.baudRate);
    serial->setDataBits(currentPortSettings.dataBits);
    serial->setParity(currentPortSettings.parity);
    serial->setStopBits(currentPortSettings.stopBits);
    serial->setFlowControl(currentPortSettings.flowControl);

    if (serial->isOpen()) { serial->close(); } // Close before opening

    if (serial->open(QIODevice::ReadWrite)) // This statement can take a while to complete
    {   // When checking isDataTerminalReady(), a return value of true means DTR is high, return false means DTR is low.
        // However, when using the setDataTerminalReady(bool) function, you set it to to high by passing false, and low by passing true.
        // In other words, you use the opposite commands when setting. Although it does make sense given the terminology of the
        // functions, it can be confusing.

        // On the Arduino boards as well as the TCB, DTR is not used for flow control, instead setting the pin to low causes a hardware reset.
        // This can be useful, but if all we want is to communicate, we don't want the host (pc) to set DTR low (mean data terminal is ready) -
        // because that will restart the board and we will never get to communicate. So we explicitly set data terminal NOT ready,
        // which has the effect of putting DTR high.

        // Note, this can only be set after the serial port is open.
        serial->setDataTerminalReady(false); // False here means "set DTR pin High"

        emit ConnectionChanged(true);      // Let the Main window know we successfully opened the COM port
    }
    else
    {
        emit ConnectionChanged(false);      // Let the Main window know we did not connect
        //qDebug() << serial->errorString();
    }
}

void Console::closeSerial()
{
    // We also try to reset the device
    toggleDTR();    // This is the same as resetDevice in OpenPanzerComm. We are probably going to be snooping on Arduino's mostly
                    // so might as well.
    // Close the port
    if (serial->isOpen())
    {   // Make sure DTR is high at the end, in case it makes any difference next time
        serial->setDataTerminalReady(false); // False here means "set DTR pin High"
        serial->close();
    }
    Connected = false;
    emit ConnectionChanged(false);  // Now we can emit our connection signal
}

void Console::ProcessConnectionChange(boolean connected)
{   // This slot gets called any time the connection status changes

    if (connected)
    {
        // Clear the error count
        NumErrors = 0;
    }
    else
    {

    }
}

void Console::toggleDTR()
{   // We toggle the DTR pin low. This causes the device to reboot.
    if (serial->isOpen())
    {
        serial->setDataTerminalReady(true);  // True here means "set DTR pin Low." This will cause device to reset.
        serial->setDataTerminalReady(false); // False here means "set DTR pin High"
    }
}



//------------------------------------------------------------------------------------------------------------------------>>
// RECEIVING
//------------------------------------------------------------------------------------------------------------------------>>
void Console::readData()
{
    // This is what Console example does
//    QByteArray data = serial->readAll();
//    console->putData(data);

    // Then on the console side, putData is defined as:
//    void Console::putData(const QByteArray &data)
//    {
//        insertPlainText(QString(data));
//        QScrollBar *bar = verticalScrollBar();
//        bar->setValue(bar->maximum());
//    }

    responseData += serial->readAll();
    emit AnyData(); // Just to let us know something has come in
    //    while (serial->waitForReadyRead(10))
}


//------------------------------------------------------------------------------------------------------------------------>>
// UTILITIES
//------------------------------------------------------------------------------------------------------------------------>>
void Console::ClearResponseData(void)
{
    responseData = 0;
}

boolean Console::isConnected(void)
{
    return Connected;
}



//------------------------------------------------------------------------------------------------------------------------>>
// ERROR HANDLING
//------------------------------------------------------------------------------------------------------------------------>>

void Console::handleError(QSerialPort::SerialPortError error)
{
    // What the Qt Console example does:
//    if (error == QSerialPort::ResourceError)
//    {
//        qDebug() << serial->errorString();
//        closeSerialPort();
//    }

    // What OpenPanzerComm does: basically ignores anything
    if (error != 0)
    {
        emit CommError(serial->errorString(), serial->error());
        serial->clearError();
    }
}




