#include "combo_baudrates.h"

BaudRateComboBox::BaudRateComboBox(QWidget *parent) : QComboBox(parent) {}

void BaudRateComboBox::setCategory(BaudCategory bc)
{
   /* generate the default options with associated values */

    // We use a slightly different set of rates for the different serial ports.
    // For example, motor serial is restricted in the rates it can use.
    switch (bc)
    {
        case bcMotorSerial:
            insertItem(count(), "19200", 19200);
            insertItem(count(), "38400", 38400);
            // Technically the Pololu controllers can run at 115200, and *some* of the Sabertooth can (not the 2x5 though).
            // However we will leave it out.
            break;


        case bcConsole:
            // This is the baud rate we will use for the serial port object. We use actual QSerialPort rates because
            // these will be passed to the OpenPanzerComm object, rather than sent to the device for saving.
            insertItem(count(), QStringLiteral("4800"), QSerialPort::Baud4800);
            insertItem(count(), QStringLiteral("9600"), QSerialPort::Baud9600);
            insertItem(count(), QStringLiteral("19200"), QSerialPort::Baud19200);
            insertItem(count(), QStringLiteral("38400"), QSerialPort::Baud38400);
            insertItem(count(), QStringLiteral("57600"), QSerialPort::Baud57600);
            insertItem(count(), QStringLiteral("115200"), QSerialPort::Baud115200);
        break;

        // The remaining are baud rates for the other TCB serial ports. We only allow the most common ones.
        case bcSerial3:
        case bcUSBSerial:
        case bcAuxSerial:
        default :
            insertItem(count(), "19200", 19200);
            insertItem(count(), "38400", 38400);
            insertItem(count(), "57600", 57600);
            insertItem(count(), "115200", 115200);
    }

// Create our own custom signal
    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(emitCurrentBaudRateChanged()));
}

void BaudRateComboBox::emitCurrentBaudRateChanged()
{   // Whenever index changes, we emit the current drive type in however many formats we need
    // This is QByteArray
    emit currentBaudRateChanged(this->currentData().toByteArray());
}

// This returns the current actual BaudRates enum
uint32_t BaudRateComboBox::getCurrentBaudRate(void)
{
    return this->currentData().toUInt(); // UN-signed LONG
}

// We can programmatically set the combo box to a value by passing it a BaudRates enum member name/number
void BaudRateComboBox::setCurrentBaudRate(int baudRate)
{
    this->setCurrentIndex(this->findData(baudRate));

}

void BaudRateComboBox::setDefaultBaudRate(void)
{
    this->setCurrentIndex(this->findData(DEFAULTBAUDRATE));
}
