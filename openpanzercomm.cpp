#include "openpanzercomm.h"

OpenPanzerComm::OpenPanzerComm()
{
    // Objects
    // ---------------------------------------------------------------------------------------------------------------------------------->>
        serial = new QSerialPort(this);
        // setSettingsRestoredOnClose will be deprecated in QT 6 and beyond. If setSettingsRestoredOnClose is true, it means QSerialPort
        // will restore the previous settings on close, which is the default. Some have found that if prior to opening the port that
        // DTR was low, QSerialPort will set DTR back to low on disconnect. In our case that is not really a terrible problem (it resets
        // the device, which we *may* want to do anyway (depends)). The bigger issue is resetting on connect, but we have sort of found a
        // way to work around that. Sadly, regardless of what we put this setting to or any other, I can not get QSerialPort to behave
        // consistently with regards to the state of DTR on serial port open. Not to mention the crazy things Windows does with it when the
        // port is closed as part of its "discovery" (basically toggle DTR every half second, keeping the TCB in a continual state of reset).
        serial->setSettingsRestoredOnClose(false);

        // Timers
        initTimer = new QTimer(this);
        blitzTimer = new QTimer(this);
        watchdogTimer = new QTimer(this);
        stayAwakeTimer = new QTimer(this);
        radioStreamingTimer = new QTimer(this);
        SkipWatchdog = false;

    // ---------------------------------------------------------------------------------------------------------------------------------->>
    // Signals and Slots
    // ---------------------------------------------------------------------------------------------------------------------------------->>
    // Timer connections
        connect(initTimer, SIGNAL(timeout()), this, SLOT(connectionFailed()));      // If initTimer times out, we were unable to connect
        connect(blitzTimer, SIGNAL(timeout()), this, SLOT(sendInit()));             // Send the INIT_STRING
        connect(watchdogTimer, SIGNAL(timeout()), this, SLOT(watchdogBark()));      // If the watchdog timer runs out, it will bark.
        connect(stayAwakeTimer, SIGNAL(timeout()), this, SLOT(keepDeviceAwake()));  // Every time the stayAwakeTimer pulses, we will send a stay-awake signal to device.
        connect(radioStreamingTimer, SIGNAL(timeout()), this, SLOT(radioStreamingTimeout())); // When the radio streaming timer expires, it means the device has quit streaming radio data.

    // Open Panzer Connection connections
        connect(this, SIGNAL(ConnectionChanged(boolean)), this, SLOT(ProcessConnectionChange(boolean)));
        connect(this, SIGNAL(AnyRequest()), this, SLOT(startWatchdog()));   // Any time we send a request, start the watchdog timer
        connect(this, SIGNAL(AnyData()), this, SLOT(restartWatchdog()));    // Any time some portion of a response comes back, restart the watchdog
        connect(this, SIGNAL(AnySentence()), this, SLOT(stopWatchdog()));   // Any time a complete sentence is received, stop the watchdog timer
        connect(this, SIGNAL(RepeatSentence()), this, SLOT(processRepeatSentence()));

    // Serial connections
        connect(this, SIGNAL(IncrementError()), this, SLOT(handleNonCriticalError()));
        connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
        connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
}

void OpenPanzerComm::begin()
{
    Connected = false;
    Snooping = false;
    RadioStreaming = false;
    SentenceReceived = false;
    _EEPROM_Written = false;
    NumErrors = 0;
    WatchdogTimeout = WATCHDOG_TIME_DEFAULT;
    StayAwakeJustSent = false;
    ClearResponseData();

    CRCRequired = true; // Meaning, we only accept sentences that include, and match, a CRC
}



//------------------------------------------------------------------------------------------------------------------------>>
// PORT: OPEN, CLOSE, ETC
//------------------------------------------------------------------------------------------------------------------------>>
void OpenPanzerComm::updatePortSettings(QString comName, QSerialPort::BaudRate baud)
{
    currentPortSettings.name = comName;
    currentPortSettings.baudRate = baud;
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

void OpenPanzerComm::setSerialSettings(void)
{
    serial->setPortName(currentPortSettings.name);
    serial->setBaudRate(currentPortSettings.baudRate);
    serial->setDataBits(currentPortSettings.dataBits);
    serial->setParity(currentPortSettings.parity);
    serial->setStopBits(currentPortSettings.stopBits);
    serial->setFlowControl(currentPortSettings.flowControl);
}

void OpenPanzerComm::openSerial_forSnoop(void)
{
    setSerialSettings();    // Make sure these are updated

    // Close before opening, this actually shouldn't happen though.
    // But if it does, we also throw in a "set DTR pin High" just for good measure. (High means don't reset the device.)
    if (serial->isOpen()) { serial->setDataTerminalReady(true); serial->close(); }

    if (serial->open(QIODevice::ReadWrite)) // This statement can take a while to complete
    {

        // Note, this can only be set after the serial port is open.
//        serial->setRequestToSend(true);      // Don't need to worry about RTS
        serial->setDataTerminalReady(true); // True here means "set DTR pin High", ie don't reset device

        // If we are just snooping, all we need to do is open the serial port: which we've already done if we're at this statement.
        Snooping = true;
    }
    else
    {
        Snooping = false;
    }
    // Emit the signal to let us know what happened
    emit SnoopingChanged(Snooping);
}

void OpenPanzerComm::openSerial_forComms(void)
{
    setSerialSettings();    // Make sure these are updated

    // Close before opening, this actually shouldn't happen though.
    // But if it does, we also throw in a "set DTR pin High" just for good measure. (High means don't reset the device.)
//    if (serial->isOpen()) { serial->setDataTerminalReady(true); serial->close(); }

    if (serial->open(QIODevice::ReadWrite)) // This statement can take a while to complete
    {   // When checking isDataTerminalReady(), a return value of true means DTR is high, return false means DTR is low.
        // When using the setDataTerminalReady(bool) function, you set it to to high by passing true, and low by passing false.
        // I've tested this empirically with a voltmeter. setDataTerminalReady(false) WILL put DTR to low and it WILL cause the
        // TCB to reset. This is fine if that's what we want to do, but we don't always.

        // On the Arduino boards as well as the TCB, DTR is not used for flow control, instead it is capacitively coupled with the RESET pin
        // on the ATmega chip. Setting DTR low causes the RESET pin to go low, which causes a hardware reset.
        // This can be useful in some situations, but in others we'd rather avoid a reset if we can. In practice, a reset seems unavoidable
        // but the bigger issue is that for some reason DTR can be _held_ low during communication attempts, which will keep the chip
        // in reset the entire time, making communication impossible. This seems to happen on occasion especially with bluetooth
        // communication.

        // Note, this can only be set after the serial port is open.
//        serial->setRequestToSend(true);      // Don't need to worry about RTS
        serial->setDataTerminalReady(true); // True here means "set DTR pin High", ie don't reset device

        // But - in testing, this doesn't seem to work consistently. QSerialPort seems to toggle DTR if it feels like it, probably based on
        // its prior state or who knows. So we try to keep it high, but we have to be prepared for the fact that connecting may
        // reboot the device. We handle this in ConnectToDevice()
        ConnectToDevice();
    }
    else
    {
        emit ConnectionChanged(false);      // Let the Main window know we did not connect
        //qDebug() << serial->errorString();
    }
}
void OpenPanzerComm::ConnectFromSnoop(void)
{
    // Here we assume the serial is open because we are already snooping. Instead of closing/opening the port,
    // we leave it open and try to connect directly from here.
    if (serial->isOpen())
    {
        Snooping = false;               // Stop snooping
        emit SnoopingChanged(Snooping); // Emit the signal to let us know what happened
        ConnectToDevice();              // Go straight to connect
    }
}

void OpenPanzerComm::ConnectToDevice(void)
{
    // Here's how it works:
    // 1. We start the initTimer. If we don't connect before it expires, we give up
    // 2. Set startBlitz to false. We don't want to blitz the controller just yet.
    // 3. Send the init string right away. If we're lucky, DTR won't be set low, and the device will connect on the first try.
    //    After it has sent this first string, sendInit also sets startBlitz to true.
    // 4. Because we know DTR probably *will* be toggled on the first send, we start a second timer called blitzTimer. This timer has two time settings,
    //    FIRST_BLITZ_TIME, and SECOND_BLITZ_TIME. We start with the first one, which is set to some length that should be long enough for
    //    the device to reset if it's going to. This timer is also set to single shot (only happens once).
    // 5. FIRST_BLITZ_TIME expires, and blitzTimer calls sendInit() again. sendInit sends the init string a second time, hoping
    //    to catch the device as it wakes from reboot. But in case it's too early, and because startBlitz is set to true, sendInit
    //    will re-configure blitzTimer as a repeating timer with intervale of SECOND_BLITZ_TIME. This interval is much shorter.
    //    Every time blitzTimer reaches that interval it will keep calling sendInit() (thus "blitzing" the device with our init string
    //    over and over). This continues until the device responds or else our original initTimer expires and we give up trying.
    // 6. If the device does respond at any time, both initTimer and blitzTimer are stopped in readData(). So we only keep blitzing as long as
    //    we need, but no longer.

    //  Yes, it's convoluted, but this is the only way I've found to reliably connect. If issues arise, probably the first thing to try would
    //  be tweaking the values of FIRST and SECOND blitz times, rather than changing the concept generally, which I think is sound.

    initTimer->setSingleShot(true);
    initTimer->start(INIT_TIME);        // 1. Start this first, because sendInit() will only do anything if initTimer is active
    startBlitz = false;                 // 2. We are not ready to blitz, just send the init string once
    sendInit();                         // 3. Send the first init string in the hope that we connect right away. This will also set startBlitz to true
    blitzTimer->setSingleShot(true);    // 4. Because it probably won't connect, start the blitz timer.
    blitzTimer->start(FIRST_BLITZ_TIME);//    The first time is single shot, second and subsequent times will be configured by sendInit()
}

void OpenPanzerComm::sendInit()
{
    if (initTimer->isActive() && Connected == false)
    {
        static QString mystring = INIT_STRING;
        static QByteArray Identify = mystring.toUtf8();

        if (serial->isOpen() && serial->isWritable())
        {
            // Clear response, do this *before* sending anything
            ClearResponseData();
            SentenceReceived = false;   // Reset this as well. DO NOT DO THIS in ClearResponseData()
            serial->write(Identify);
            if (DEBUG_MSGS) qDebug() << "Sent: OPZ";
            if (APPEND_SENT_TO_CONSOLE) { QByteArray qc = Identify; emit NewData(qc.prepend("<- ")); }
            // You have to wait for bytes to be written or else it will skip!!
            if (!serial->waitForBytesWritten(50))
            {
                //qDebug() << serial->errorString();
            }
            if (startBlitz)
            {
                blitzTimer->setSingleShot(false);
                blitzTimer->start(SECOND_BLITZ_TIME);
            }
            else
            {
                startBlitz = true;
            }
        }
    }
    else
    {
        // The watchdog has expired. Quit spamming the device with INIT_STRINGs
        blitzTimer->stop();
    }
}

void OpenPanzerComm::connectionFailed()
{   // We come here if initTimer expires. That means we were unable to connect.

    closeSerial();   // We no longer close the serial port here
}

void OpenPanzerComm::closeSerial()
{
    if (!Snooping) TellDevice_Goodbye();

    // If we wrote settings to the device, we want it to reboot so it can apply the new settings.
    // If we didn't write anything, we *don't* want to reset the device, leave DTR high.
    if(_EEPROM_Written) { resetDevice(); }

    // Close the port
    if (serial->isOpen())
    {   // Make sure DTR is high at the end, in case it makes any difference next time
        serial->setDataTerminalReady(true); // True here means "set DTR pin High"
        serial->close();
    }
    // If we disconnect while the radio is streaming, we want to emit the radio streaming
    // signal first.
    if (RadioStreaming)
    {
        stopRadioStreamingTimer();  // We stop the streaming timer to prevent it from expiring *after* we've already disconnected
        RadioStreaming = false;     // Now we set the flag false and emit the signal that would normally have been emitted when
        emit RadioStreamingChanged(false);  // the timer expired
    }

    Connected = false;
    emit ConnectionChanged(Connected);

    if (Snooping)
    {
        Snooping = false;
        emit SnoopingChanged(Snooping);
    }
}

void OpenPanzerComm::TellDevice_Goodbye(void)
{
    if (Connected) // Otherwise the device already left us a while ago.
    {
        clearSentenceOUT();
        SentenceOUT.Command = SentenceOUT.ID = PCCMD_DISCONNECT;
        sendSentence(SentenceOUT);
    }
}

void OpenPanzerComm::ProcessConnectionChange(boolean connected)
{   // This slot gets called any time the connection status changes

    if (connected)
    {
        // Whenever we connect, start the stayAwake timer
        // The watchdog timer will get started later when we actually send a request
        startStayAwakeTimer();                  // Keep the device connected
        // Clear the error count
        NumErrors = 0;
        // Start off with this set to false. It will get set to true if we updated any EEPROM
        _EEPROM_Written = false;
    }
    // Whenever we disconnect, stop both timers
    else
    {
        stopWatchdog();                         // Stop this timer first
        stopStayAwakeTimer();                   // Now also stop the stay awake timer
    }
}

void OpenPanzerComm::resetDevice()
{   // We toggle the DTR pin low. This causes the device to reboot.
    if (serial->isOpen())
    {   if (DEBUG_MSGS) qDebug() << "Attempt to reset device.";
        // Yes, there is no pause between setting DTR low and putting it back to high.
        // Tested with a meter, it still gets set low momentarily, and it still resets the device.
        serial->setDataTerminalReady(false);  // False here means "set DTR pin Low." This will cause device to reset.
        serial->setDataTerminalReady(true); // True here means "set DTR pin High"
    }
}

void OpenPanzerComm::Snoop()
{
   // Here we want to start snooping
   if (Connected)
   {
       // If we are already connected to the device, then the serial port is already open. All we need to do is
       // tell the device to exit communication mode and go into normal operation mode, but we leave the serial port
       // open so we can listen to whatever it says in normal operation mode.

       // Tell the device to resume normal operation:
       TellDevice_Goodbye();

       // If while we were "connected" we posted any changes, we probably want to see their effect in the console,
       // and this won't happen until the device is reset. So let's try to reboot it too, but ONLY if we
       // wrote changes:
       if (_EEPROM_Written) { resetDevice(); }

       // Now update flags and emit signals
       Connected = false;               // In this case, Connected = false doesn't mean the port is closed,
       emit ConnectionChanged(false);   // it just means we aren't in communication mode anymore.

       Snooping = true;
       emit SnoopingChanged(true);      // This emits the Snooping true signal
   }
   else
   {   // In this case we want to snoop and the serial port isn't open yet, so we will open it.
       openSerial_forSnoop();           // openSerial_forSnoop() will take care of emitting the correct signals
   }
}

void OpenPanzerComm::ProcessSnoopingChange(boolean) //  snooping)
{
    //
}

//------------------------------------------------------------------------------------------------------------------------>>
// SENDING
//------------------------------------------------------------------------------------------------------------------------>>
void OpenPanzerComm::clearSentenceOUT()
{
    SentenceOUT.Command = SentenceOUT.ID = SentenceOUT.Checksum = SentenceOUT.NumValues = 0;
    SentenceOUT.Value.clear();
    SentenceOUT.Value = QByteArray::number(0);
}

boolean OpenPanzerComm::sendNullValueSentence(uint8_t CMD)
{
    // We can use this one when we don't need to send a value, just a command (repeated in the ID slot)
    clearSentenceOUT();
    SentenceOUT.Command = SentenceOUT.ID = CMD;
    return sendSentence(SentenceOUT);
}

boolean OpenPanzerComm::sendSentence(DataSentence &_sentence)
{
    // Convert sentence to byte array
    QByteArray bas = sentenceToByteArray(_sentence);

    // Clear response, do this *before* sending anything
    ClearResponseData();
    SentenceReceived = false;   // Reset this as well. DO NOT DO THIS in ClearResponseData()

    // Now send the sentence
    if (serial->isOpen() && serial->isWritable())
    {
        serial->write(bas);
        emit AnyRequest();          // This lets us know we should start the watchdog timer for a response
        StayAwakeJustSent = false;  // We might have just sent a stay awake command, but we'll let the calling routine set that flag.
                                    // This way in all other cases it is automatically set to false.

        // You have to wait for bytes to be written or else it will skip!!
        if (!serial->waitForBytesWritten(50))
        {
            if (DEBUG_MSGS) qDebug() << serial->errorString();
            closeSerial();  // We fail on this case and close the port
            return false;
        }

        // Ok, it was really sent

        // Debug if option is set
        if (DEBUG_MSGS) qDebug() << "Sent: " << bas;

        // Put a copy on the console if option is set
        if (APPEND_SENT_TO_CONSOLE)
        {
            QByteArray qc = bas;
            emit NewData(qc.prepend("<- "));
        }
        return true;
    }
    else
    {
        return false;
    }
}

QByteArray OpenPanzerComm::sentenceToByteArray(DataSentence _sentence)
{
    // Convert our sentence elements into a single byte array, including CRC
    // We have the option of skipping the CRC check on reception, but regardless we always
    // include the CRC on transmission.
    QByteArray bas;
    bas = QByteArray::number(_sentence.Command);
    bas.append(DELIMITER);
    bas.append(QByteArray::number(_sentence.ID));
    bas.append(DELIMITER);
    bas.append(_sentence.Value); //_sentence.Value is already a QByteArray
    bas.append(DELIMITER);
    bas.append(QByteArray::number(calcrc(bas.data(), bas.size())));    // As opposed to the function sizeof in Arduino, this one actually works at runtime
    bas.append(NEWLINE);
    return bas;
}

// When the device sends a DVCMD_REPEAT_SENTENCE request
void OpenPanzerComm::processRepeatSentence(void)
{
    // Every sentence we send should have been saved in SentenceOUT
    // so we just need to resend it. But we start an error count in case
    // this is indicative of a deeper problem.
    if (NumErrors < MAX_ERRORS)
    {
        sendSentence(SentenceOUT);
        NumErrors += 1;
    }
    else
    {
        closeSerial();
        emit CommError("Too many errors - device disconnected.", QSerialPort::NoError );
    }
}

void OpenPanzerComm::requestUtilizedRadioChannels(void)
{
    sendNullValueSentence(PCCMD_NUM_CHANNELS);
}

void OpenPanzerComm::startStreamRadio(void)
{
    sendNullValueSentence(PCCMD_STARTSTREAM_RADIO);
}

void OpenPanzerComm::stopStreamRadio(void)
{
    // see the discussion in watchdogBark() below for more info on this skipping business. But basically we want to
    // skip it whenever we end a streaming operation from the device (but we don't want to skip it on other communications).
    SkipWatchdog = true;
    sendNullValueSentence(PCCMD_STOPSTREAM_RADIO);
    // We'll let the streaming timer expire, which will set the RadioStreaming flag = false.
}

void OpenPanzerComm::requestFirmwareVersion(void)
{
    sendNullValueSentence(PCCMD_READ_VERSION);
}

void OpenPanzerComm::requestMinOPCVersion(void)
{
    sendNullValueSentence(PCCMD_MINOPC_VERSION);
}

void OpenPanzerComm::SetSabertoothBaudRate(uint8_t SabertoothBaud)
{
    clearSentenceOUT();
    SentenceOUT.Command = PCCMD_SABERTOOTH_BAUD;
    SentenceOUT.ID = SentenceOUT.Command;
    SentenceOUT.Value = QByteArray::number(SabertoothBaud);
    SentenceOUT.Checksum = 0;       // Checksum will get calculated by sendSentence
    changeWatchdogTimeout(WATCHDOG_TIME_SABERTOOTH_SETUP);  // It takes longer to do this setup than our typical timeout, so we temporarily increase it.
    sendSentence(SentenceOUT);                              // See "processNextSentence" in "mainwindow_device_rw.cpp" for where we set this back to default.
}

void OpenPanzerComm::ConfigurePololu_Drive(void)
{
    sendNullValueSentence(PCCMD_CONFPOLOLU_DRIVE);
}

void OpenPanzerComm::ConfigurePololu_Turret(void)
{
    sendNullValueSentence(PCCMD_CONFPOLOLU_TURRET);
}

void OpenPanzerComm::readEEPROM(uint16_t WhatID)
{
    clearSentenceOUT();
    SentenceOUT.Command = PCCMD_READ_EEPROM;
    SentenceOUT.ID = WhatID;
    SentenceOUT.Value = QByteArray::number(0);  // No value for read command
    SentenceOUT.Checksum = 0;       // Checksum will get calculated by sendSentence
    sendSentence(SentenceOUT);
}

void OpenPanzerComm::writeEEPROM(uint16_t WhatID, QByteArray WhatValue)
{
    // Set this flag so we know an EEPROM update took place. In this case, we will try to
    // reset the device when we disconnect, so it automatically reloads variables from the new
    // EEPROM data
    _EEPROM_Written = true;
    clearSentenceOUT();
    SentenceOUT.Command = PCCMD_UPDATE_EEPROM;
    SentenceOUT.ID = WhatID;
    SentenceOUT.Value = WhatValue;
    SentenceOUT.Checksum = 0;       // Checksum will get calculated by sendSentence
    sendSentence(SentenceOUT);
}

//------------------------------------------------------------------------------------------------------------------------>>
// RECEIVING
//------------------------------------------------------------------------------------------------------------------------>>
void OpenPanzerComm::readData()
{

    QByteArray data = serial->readAll();

    if (Snooping)
    {
        emit NewData(data);             // This emits the actual data received from this call. We can use this to display incoming data in the console window
        return;                         // We don't need to do anything else in snooping mode
    }
    else if (APPEND_RECEIVED_TO_CONSOLE)
    {
        QByteArray qc = data;           // Here we also want to display the incoming data on the console
        emit NewData(qc.prepend("-> "));
    }

    emit AnyData();                 // This signal is only used internally to the Comm class, and is used to reset the watchdog timer
    responseData += data;
    //responseData += serial->readAll();
    SentenceReceived = false;
    // Have we reached newline?
    if (responseData.endsWith(NEWLINE))
    {   // If so, see if this is a valid sentence
        if (ParseSentence(responseData))
        {
            SentenceReceived = true;
            emit AnySentence(); // We will use this to halt the watchdog timer

            if (DEBUG_MSGS) sentenceToDebug(SentenceIN, false);  // This sends the sentence to the debug port so we can see it

            switch (SentenceIN.Command)
            {
                case DVCMD_NEXT_SENTENCE:
                    if (SentenceIN.ID == SentenceIN.Command)
                    {
                        if (!Connected)
                        {
                            Connected = true;
                            if (initTimer->isActive()) initTimer->stop();   // We don't want initTimer to expire, because that means we failed to connect. So stop it.
                            if (blitzTimer->isActive()) blitzTimer->stop(); // Stop this one too.
                            emit ConnectionChanged(true);
                        }
                        // Sometimes there will be a minor error that does not require a halt in whatever we're doing, but we still want to
                        // know about. The TCB can send back "Next Sentence" but if the Value (which would typically be ignored) is not 0,
                        // that means whatever we asked it to do previously didn't work. For now the only time this really comes into play
                        // is if we asked it to save a value for a variable it couldn't find. The TCB will go ahead and ask us for the next
                        // variable to save but let us know it was unable to save the last one. This happens very rarely and typically only
                        // when the TCB firmware version has fallen behind an OP Config update.
                        if (SentenceIN.Value.toUInt() == 0) emit NextSentence(false);   // No flag, no problem
                        else                                emit NextSentence(true);    // Flag set
                        // This is also the response to our stay awake command. If that is what we just sent, make sure
                        // to reset the MissedStayAwakeCount to 0 since we have received a reply.
                        if (StayAwakeJustSent)
                        {
                            MissedStayAwakeCount = 0;
                        }
                    }
                    break;

                case DVCMD_REPEAT_SENTENCE:
                    if (SentenceIN.ID == SentenceIN.Command) emit RepeatSentence();
                    break;

                case DVCMD_RETURN_VALUE:
                    // IDs above MIN_EEPROM_ID are always eeprom variables
                    if (SentenceIN.ID > MIN_EEPROM_ID)
                    {
                        emit HereIsValue(SentenceIN.ID, SentenceIN.Value, true);    // True means a value was returned
                    }
                    // IDs less than MIN_EEPROM_ID are special cases. The ID will usually be a repeat of the CMD that was sent,
                    // but not always, such as in the case with radio streaming data.
                    else
                    {
                        switch (SentenceIN.ID)
                        {
                            // Value will be firmware version
                            case PCCMD_READ_VERSION:
                                emit HereIsFirmwareVersion(SentenceIN.Value);
                                break;

                            // Value will be the minimum version of OP Config the TCB expects.
                            // We can use this to alert the user if they need to update OP Config
                            case PCCMD_MINOPC_VERSION:
                                emit HereIsMinOPCVersion(SentenceIN.Value);
                                break;

                            // Returns number of utilized channels
                            case PCCMD_NUM_CHANNELS:
                                emit HereAreNumChannels(SentenceIN.Value.toUInt());
                                break;

                            // Returns pulse-widths for each utilized channel, stored in the Values array
                            case DVID_RADIOSTREAM_LO:
                            case DVID_RADIOSTREAM_HI:
                                if (!RadioStreaming)
                                {   // Radio streaming has begun
                                    startRadioStreamingTimer();
                                    emit RadioStreamingChanged(true);
                                }
                                else
                                {   // Radio streaming already started - in this case we just
                                    // restart the timer so it doesn't expire.
                                    reStartRadioStreamingTimer();
                                }

                                // If using SBus the TCB may have 16 channels worth of data to send. Due to time
                                // constraints between processing the 16 incoming channels from the receiver and sending
                                // it out, the TCB will actually only send out 8 channels at a time. First it will send
                                // channels 1-8, then channels 9-16, then back and forth. The ID tells us which is what.
                                // For the bank of channels not received, we just leave the values to what they were last time around.
                                for (int i = 0; i<SentenceIN.NumValues; i++)
                                {
                                    if (SentenceIN.ID == DVID_RADIOSTREAM_LO) pulseWidths[i] = SentenceIN.Values[i].toInt();
                                    else pulseWidths[i+8] = SentenceIN.Values[i].toInt();   // Hi starts at Channel 9 and goes up
                                }
                                // Emit the signal and pass the array.
                                emit HereArePulseWidths(pulseWidths);
                        }
                    }
                    break;

                case DVCMD_RADIO_NOTREADY:
                    // We requested something to do with the radio, but the radio is either not on, not ready, or can't be read for some reason.
                    emit RadioNotReady();
                    break;

                case DVCMD_NOSUCH_VALUE:
                    if (SentenceIN.ID == SentenceIN.Command) emit HereIsValue(SentenceIN.ID, SentenceIN.Value, false);    // False means a value was not found (SentenceIn.Value will be 0 but should be ignored)
                    break;

                case DVCMD_GOODBYE:
                    if (SentenceIN.ID == SentenceIN.Command)
                    {
                        if (Connected)
                        {
                            closeSerial();  // This handles the emission of the ConnectionChanged() signal
                        }
                    }
                    break;

            }
        }
        ClearResponseData();
    }
}


// This attempts to convert a stream of characters into the four components of our standard "sentence":
// Command, ID, Value, and Checksum. If we get those four pieces, this function returns true, and the
// DataSentence that is passed by reference is updated.
boolean OpenPanzerComm::ParseSentence(QByteArray &data)
{
    char line_segment[SENTENCE_BUFF];

    boolean completeSentence = false;
    uint8_t segment_length = 0;
    uint8_t numDelimiters = 0;
    char c;

    // Initialize sentence components
    SentenceIN.Command = SentenceIN.ID = SentenceIN.Checksum = SentenceIN.NumValues = 0;
    SentenceIN.Value[0] = '\0';
    for (int i=0; i<MAX_SENTENCE_VALUES; i++) { SentenceIN.Values[i][0] = '\0'; }


    // We step through each byte in the char array and parse pieces of the sentence as they are seperated by a delimiter, or at the end by newline
    for (int line_length=0; line_length<data.size(); line_length++)
    {
        c = data[line_length];
        switch (c)
        {
        case '\n':                         // end of transmission
            if (numDelimiters >= 2 && segment_length > 0)
            {
                // This is the end. The number received will be the checksum received.
                // We subtract 1 from segment_length so that the newline char doesn't get counted as part of the number
                SentenceIN.Checksum = constructNumber(line_segment, segment_length-1);

                // Is checksum required?
                if (CRCRequired && (SentenceIN.Checksum != calcrc(data.data(), line_length - segment_length))) // The data() method of the QByteArray returns a char *
                {	// Checksum doesn't add up.                                                                // Strangely we don't need to subtract 1 from segment_length here
                    completeSentence = false;
                    /*
                    qDebug() << "Calc CRC: " << calcrc(data.data(), line_length - segment_length - 1);
                    qDebug() << "CRC Received: " << SentenceIN.Checksum;
                    qDebug() << "Segment Length: " << (line_length - segment_length); */
                }
                else
                {
                    // CRC matches, or wasn't required - sentence successfully received and parsed!
                    completeSentence = true;
                }
            }
            else
            {
                // There weren't enough segments received to make a complete sentence,
                // but we got to the end of the transmission. Something bad happened.
                completeSentence = false;
            }

            break;

        case '\r':   // discard carriage return
            break;

        case DELIMITER:
            // terminate the array with a null byte
            line_segment[segment_length] = 0;
            switch (numDelimiters)
            {
                case 0:
                    // This is the first number. The first number received will be our Command
                    SentenceIN.Command = constructNumber(line_segment, segment_length);
                    break;

                case 1:
                    // This is the second delimiter. The number we received will be our ID
                    SentenceIN.ID = constructNumber(line_segment, segment_length);
                    break;

                case 2:
                    // This is the third delimiter. The bytes received will be our value.
                    // We don't know of what type yet, just keep it a ByteArray for now.
                    SentenceIN.Value = SentenceIN.Values[0] = line_segment;
                    SentenceIN.NumValues = 1;
                    break;
                default:
                    // Keep putting values into the next open slot of the array
                    // But check to make sure we still have an open slot left - we can't exceed MAX_SENTENCE_VALUES
                    if (SentenceIN.NumValues + 1 <= MAX_SENTENCE_VALUES)
                    {
                        SentenceIN.Values[SentenceIN.NumValues++] = line_segment;
                    }
            }
            // reset segment
            segment_length = 0;
            numDelimiters += 1;
            break;

        default:
            // keep adding if not full (minus 1 to allow for terminating null byte)
            if (line_length < (SENTENCE_BUFF - 1))
            {
                line_segment[segment_length++] = c;
            }
            else
            {
                // Overflow! Something didn't go right, maybe we're reading random junk
                completeSentence = false;
            }
        }
    }
    return completeSentence;
}



//------------------------------------------------------------------------------------------------------------------------>>
// TIMERS
//------------------------------------------------------------------------------------------------------------------------>>
void OpenPanzerComm::watchdogBark(void)
{
    // This SkipWatchdog business is a hack, and I don't like hacks, but I found it necessary.

    // The typical behavior is this: any sentence sent to the device triggers startWatchdog() due to the signal/slot connection
    // between AnyRequest() -> startWatchdog(). The watchdog timer starts and if we don't receive a response to our request
    // before it expires, then we consider comms to be lost.

    // This works brilliantly when communication is one sentence back and forth with each device speaking once and taking turns.
    // But when we request the device to stream us radio data, now the device is speaking many times in a row and the PC is just
    // listening and interjecting occasionally. In this scenario, when the PC requests the device to stop streaming, the device always
    // gets the command, the device stops streaming, and the device always then requests the next sentence. But for some reason, the
    // PC about 8 times out of 10 will miss the "next sentence" response. This causes it to think comms have been lost and disconnect.

    // In much testing I can't figure out exactly why it misses this sentence, but I believe it is because the watchdog timer gets restarted
    // any time data comes in. If the stop command is sent in the middle of an incoming sentence (quite likely because they are streamed
    // non-stop), then the incoming stream sentence will clear the watchdog but the next sentence (the response to the stop request)
    // will start it once again. Of course, if the response is successfuly read the watchdog should be stopped but somehow it is not
    // successfully read. Maybe the PC can't keep up with every incoming sentence...

    // If the PC sends the "stop streaming" command after the streaming has really stopped, then the PC will always receive the response.
    // So one hack around this would  be to send the stop streaming command twice, but I went with this hack instead. We now have
    // a global flag called SkipWatchdog. The stopStreamRadio() function sets the flag to true before sending the command
    // to stop streaming. Even though in startWatchdog() below we don't start the watchdog if skipWatchdog = true,
    // the watchdog timer is almost certainly *already* started because of incoming data from the stream is constantly re-starting it.

    // So we do a second check here when the watchdog timer expires. If SkipWatchdog = true we just set it to false but ignore the
    // timeout.

    if (SkipWatchdog)
    {
        // We want this to only apply once, so if SkipWatchdog is true, set it to false.
        // This forces whatever function that wants to skip it, to deliberately set the flag each time.
        SkipWatchdog = false;
    }
    else
    {
        // If this timer runs out, we were expecting a response from the device but didn't get it.

        // If the last communication with the device was just a "stay awake" command, we allow it to miss
        // some number of times before we force a disconnect.
        if (StayAwakeJustSent)
        {
            StayAwakeJustSent = false;      // Reset this flag

            MissedStayAwakeCount += 1;      // Increment the count of stay awakes that have been missed

            if (MissedStayAwakeCount > ALLOWED_STAY_AWAKE_MISSES)
            {
                MissedStayAwakeCount = 0;   // Reset for the next time we initiate comms
                closeSerial();              // Force disconnect
                if (DEBUG_MSGS) qDebug() << "Watchdog Timer expired!";
            }
        }
        else
        {
            // If we were communicating anything other than just "stay awake", we don't allow the device to miss
            // the response even one. In this case we sent some other command, got nothing back, so now
            // we disconnect
            closeSerial();
            if (DEBUG_MSGS) qDebug() << "Watchdog Timer expired!";
        }
    }
}
void OpenPanzerComm::startWatchdog(void)
{
    if (Connected & !SkipWatchdog)  // Don't start if SkipWatchdog = true
    {
        watchdogTimer->setSingleShot(true);
        watchdogTimer->start(WatchdogTimeout);
        stopStayAwakeTimer();   // This does NOT need to be running when we are communicating
    }
}
void OpenPanzerComm::restartWatchdog(void)
{
    if (Connected)
    {
        watchdogTimer->start(WatchdogTimeout);    // Starting an already-running timer just re-starts it
    }
}
void OpenPanzerComm::changeWatchdogTimeout(int time)
{
    WatchdogTimeout = time;
    restartWatchdog();
}
void OpenPanzerComm::defaultWatchdogTimeout(void)
{
    WatchdogTimeout = WATCHDOG_TIME_DEFAULT;
}
void OpenPanzerComm::stopWatchdog(void)
{
    watchdogTimer->stop();
    startStayAwakeTimer();  // This needs to be running when we are not communicating
}

void OpenPanzerComm::keepDeviceAwake(void)
{
    // Send a stay awake sentence. It could be anything, but to prevent other actions from
    // occuring by sending actual commands, we send a stay awake command which the device
    // will simply respond to with a "next sentence" request.
    clearSentenceOUT();
    SentenceOUT.Command = SentenceOUT.ID = PCCMD_STAY_AWAKE;
    sendSentence(SentenceOUT);
    // The stay awake command is different from other commands in one other way - we will allow
    // the device to miss the response to it some number of times (the issue is probably more likely that the PC
    // fails to read the response in the midst of radio streaming). To know that this is the last
    // command sent, set this flag
    StayAwakeJustSent = true;

}
void OpenPanzerComm::startStayAwakeTimer(void)
{   // This is a repetitive timer that will keep triggering over and over until stopped
    if (Connected && stayAwakeTimer->isActive() == false)
    {
        stayAwakeTimer->start(STAY_AWAKE_BEEP_TIME);
    }
}
void OpenPanzerComm::stopStayAwakeTimer(void)
{
    stayAwakeTimer->stop();
}
void OpenPanzerComm::startRadioStreamingTimer(void)
{
    radioStreamingTimer->setSingleShot(true);
    radioStreamingTimer->start(RADIO_STREAM_OVER_TIME);
    RadioStreaming = true;
}
void OpenPanzerComm::reStartRadioStreamingTimer(void)
{
    // It should already be created, but just in case...
    if (!RadioStreaming) radioStreamingTimer->setSingleShot(true);
    // Starting a timer that is already started will re-start it
    radioStreamingTimer->start(RADIO_STREAM_OVER_TIME);
    RadioStreaming = true;
}
void OpenPanzerComm::stopRadioStreamingTimer(void)
{
    if (radioStreamingTimer->isActive()) { radioStreamingTimer->stop(); }
    RadioStreaming = false;
}
void OpenPanzerComm::radioStreamingTimeout(void)
{   // This function gets called if the radio stream fails to send the next streaming message
    // within RADIO_STREAM_OVER_TIME time.
    if (RadioStreaming)
    {
        RadioStreaming = false;
        emit RadioStreamingChanged(false);
    }
}


//------------------------------------------------------------------------------------------------------------------------>>
// UTILITIES
//------------------------------------------------------------------------------------------------------------------------>>
void OpenPanzerComm::ClearResponseData(void)
{
    responseData = 0;
}

boolean OpenPanzerComm::isConnected(void)
{
    return Connected;
}

boolean OpenPanzerComm::isSnooping(void)
{
    return Snooping;
}

boolean OpenPanzerComm::isRadioStreaming(void)
{
    return RadioStreaming;
}

// This will convert a string of characters into a number
// The number must be able to fit into a 4-byte int32
int32_t OpenPanzerComm::constructNumber(char *c, int numBytes)
{
    boolean negative = false;
    int32_t constructedNumber = 0;
    for (int i=0; i<=numBytes; i++)
    {
        if ((i==0) && (c[i] == '-')) { negative = true; }
        else if (c[i] >= '0' && c[i] <= '9')
        {
            constructedNumber *= 10;          // Prior digit gets shifted over by power of ten
            constructedNumber += c[i] - '0';  // Char will be decimal equivalent of number. Decimal 48 is char 0 and it goes up from there. So we subtract char 0 from the received char to get the actual number
        }
    }
    if (negative) { constructedNumber = -constructedNumber; }
    return constructedNumber;

}

// This will calculate a CRC value from a character string
int16_t OpenPanzerComm::calcrc(char *ptr, int16_t count)
{
    int16_t crc;
    uint8_t i;

    crc = 0;
    while (--count >= 0)
    {
        crc = crc ^ (int16_t) *ptr++ << 8;
        i = 8;
        do
        {
            if (crc & 0x8000)
                crc = crc << 1 ^ 0x1021;
            else
                crc = crc << 1;
        } while(--i);
    }
    return (crc);
}

void OpenPanzerComm::skipCRC(void)
{
    CRCRequired = false;
}

void OpenPanzerComm::requireCRC(void)
{
    CRCRequired = true;
}

//------------------------------------------------------------------------------------------------------------------------>>
// DEBUGGING
//------------------------------------------------------------------------------------------------------------------------>>
void OpenPanzerComm::sentenceToDebug(DataSentence sentence, boolean Sent)
{
    if (Sent)
    {
        qDebug() << "Sent: " << sentence.Command << "|" << sentence.ID << "|" << sentence.Value << "|" << sentence.Checksum;
    }
    else
    {
        qDebug() << "Received: " << sentence.Command << "|" << sentence.ID << "|" << sentence.Value << "|" << sentence.Checksum;
    }
}

void OpenPanzerComm::sentenceToMsgBox(DataSentence sentence)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Sentence");
    msgBox.setText(QString("Command: %1 \nID: %2 \nValue: %3\nChecksum: %4").arg(sentence.Command).arg(sentence.ID).arg(QString(sentence.Value)).arg(sentence.Checksum));
    msgBox.exec();
}


//------------------------------------------------------------------------------------------------------------------------>>
// ERROR HANDLING
//------------------------------------------------------------------------------------------------------------------------>>

void OpenPanzerComm::handleError(QSerialPort::SerialPortError error)
{
//    if (error == QSerialPort::ResourceError)
//    {
//        qDebug() << serial->errorString();
//    }

    if (error != 0)
    {
        emit CommError(serial->errorString(), serial->error());
        serial->clearError();
    }
}

void OpenPanzerComm::handleNonCriticalError(void)
{
    if (NumErrors > MAX_COMM_ERRORCOUNT)
    {
        closeSerial();
        emit CommError("Too many communication errors occured. Device disconnected.", QSerialPort::NoError);
    }
}


