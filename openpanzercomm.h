/* OP_PCComm.h			Open Panzer PC Communication - a library for talking to a PC, primarily intended for use with the desktop application
 * Version 1.0   		July 2015
 * Copyright 2015		Luke Middleton	openpanzer.org
 *
 * This library provides functions for listening, responding to and executing commands received from a computer application.
 * Primarily this will involve updating all variable stored in EEPROM from settings the user has defined in the desktop app.
 *
 * We use a constructed serial protocol of "sentences" composed of up to four pieces of information, seperated by a delimiter character (we use the pipe char "|")
 * The first two values of the sentence must always be non-zero. These are the "Command" and the "ID"
 * The next two values in the sentence are the "value" to be operated upon, and finally, a "Checksum" of all or part of the sentence
 * In some cases there will be no value relevant to the command being sent, and in that case there won't be an ID either because the ID
 * identifies the value. In those cases, the command is repeated twice, first in the command slot, then in the ID slot, and in those cases
 * the Value and Checksom slots should still be sent but with 0 in them.
 *
 * Some examples in pseudo code:
 *
 * PC tells us to upate a variable in EEPROM
 * -------------------------------------------------------------------------------------------------
 * 124|2212|120|xxx newline
 * 124 		- command to update EEPROM (see definitions of commands below)
 * | 		- delimiter
 * 2212 	- ID of the value to be updated (in our Excel we see this is SmokerFastIdleSpeed)
 * | 		- delimiter
 * 120 		- the new value the EEPROM should be set to
 * | 		- delimiter
 * xxx 		- checksum (not calculated for this example)
 * newline	- newline character, tells us the sentence is over
 *
 * PC tells us to disconnect
 * -------------------------------------------------------------------------------------------------
 * 31|31|0|0 newline
 * 31		- command to tell the Tank Control Board we are done, disconnect
 * |		- delimiter
 * 31		- command repeated in the ID slot
 * |		- delimiter
 * 0		- nothing needed in the value slot, but we still include the slot
 * |		- delimiter
 * 0		- nothing needed in the checksum slot, but we still include the slot
 * newline	- end of sentence
 *
 *
 * Tank Control Board tells PC to repeat the last sentence (something didn't go right with reception)
 * -------------------------------------------------------------------------------------------------
 * 135|135|0|0 newline
 * 135		- command to tell the computer we need the last sentence resent
 * |		- delimiter
 * 135		- command repeated in the ID slot
 * |		- delimiter
 * 0		- nothing needed in the value slot, but we still include the slot
 * |		- delimiter
 * 0		- nothing needed in the checksum slot, but we still include the slot
 * newline	- end of sentence
 *
 * Tank Control Board gives the PC a value (PC must request it first, this would be the response)
 * -------------------------------------------------------------------------------------------------
 * 136|2212|120|xxx newline
 * 136		- command to tell the computer we are giving him a value
 * |		- delimiter
 * 2212		- ID of the value we are sending (should match the ID the computer just requested)
 * |		- delimiter
 * 120		- the value presently in eeprom
 * |		- delimiter
 * 0		- checksum (not calculated in this example)
 * newline	- end of sentence
 *
 *
 * Almost all communication is one sentence each device, back and forth. So PC will send a sentence and wait for TCB to send a sentence,
 * then TCB will wait for the PC to send a sentence, etc... In other words, each device should only send one sentence a time, and
 * refrain from sending any more sentences until it hears back from the other device.
 * The exception to this is if the watchdog timer expires, in which case the TCB will tell the PC it's saying goodbye.
 *
 *
 */


#ifndef OPENPANZERCOMM_H
#define OPENPANZERCOMM_H

#include <QtCore/QtGlobal>

#include <QMessageBox>
#include <QtSerialPort/QSerialPort> // Serial port
#include <QString.h>
#include <QDebug.h>
#include <QTimer.h>
#include <arduino_compat.h>         // Gives us Arduino-like data type names
#include <op_devicedata_struct.h>
#include <op_eeprom_varinfo.h>


// We've decided to allow the user to modify the baud rate because we also want to implement a general-purpose
// console. This gives them one extra thing to think about though when connecting to the TCB, so set this to
// the USB_BAUD_RATE setting in OP_Config.h and we will default to it.
#define USB_DEFAULT_BAUD_RATE    QSerialPort::Baud115200

#define DELIMITER           	'|'
#define NEWLINE             	'\n'

// Communication Errors
#define MAX_ERRORS              10      // How many communication errors allowed before we just disconnect

// Time
#define INIT_TIME               4100    // How much total time will we use to try to connect to the device
#define FIRST_BLITZ_TIME        2000    // Time in milliseconds between the first init string and how long we think the device takes to reboot (and get past bootloader)
#define SECOND_BLITZ_TIME       500     // Time in milliseconds between spamming the device repeatedly with our INIT_STRING
#define WATCHDOG_TIME_DEFAULT   1000    // Time in milliseconds we will wait for a response from the device generally.
#define WATCHDOG_TIME_SABERTOOTH_SETUP 3000 // When we command a Sabertooth baud rate setup routine of the TCB, the response will take over 2 seconds, so we must increase the default watchdog timeout time
#define STAY_AWAKE_BEEP_TIME    4000    // How often should we send a stay-awake signal to the device. Should be less than the device's timeout time.
                                        // In fact, best to set it to less than 1/2 the device's timeout time, so you always have at least 2 chances to get through
                                        // before the device auto-disconnects. The TCB is set to timeout after 8.5 seconds of no signal.
#define ALLOWED_STAY_AWAKE_MISSES 2     // How many stay awake commands will we allow to go by without a response from the device before we disconnect.
                                        // All other types of commands we require a response to each one.
#define RADIO_STREAM_OVER_TIME  800     // If we don't get a radio streaming sentence in this amount of time, consider streaming done.

// Commands sent by PC
#define INIT_STRING				"OPZ\n"	// The initialization string to tell the device to start listening

#define PCCMD_SABERTOOTH_BAUD   118     // PC wants us to set the baud rate on a Sabertooth V2 device connected to Serial 2
#define PCCMD_CONFPOLOLU_DRIVE  119     // PC wants us to configure a Pololu device connected to Serial 2 for use with drive motors
#define PCCMD_CONFPOLOLU_TURRET 120     // PC wants us to configure a Pololu device connected to Serial 2 for use with turret motors
#define PCCMD_NUM_CHANNELS      121     // Tell the device to send us the number of utilized channels
#define PCCMD_STARTSTREAM_RADIO	122     // Tell the device to send us radio pulse widths
#define PCCMD_STOPSTREAM_RADIO	123		// Tell the device to stop streaming pulse-widths
#define PCCMD_UPDATE_EEPROM	  	124
#define PCCMD_READ_EEPROM	    126
#define PCCMD_READ_VERSION		128     // Request the TCB to tell us what version of firmware it is running
#define PCCMD_STAY_AWAKE        129
#define PCCMD_MINOPC_VERSION    130     // Request the TCB to tell us the minimum version of OP Config its version of firmware requires
#define PCCMD_DISCONNECT      	31

// Return "Commands" (identifiers) from Device
#define DVCMD_RADIO_NOTREADY	132     // In respond to a request for information about the radio, this indicates the radio is not detected or ready
#define DVCMD_NEXT_SENTENCE		133     // Request for next command, also used as a general acknowledgment by the device
#define DVCMD_REPEAT_SENTENCE	135
#define DVCMD_RETURN_VALUE		136
#define DVCMD_NOSUCH_VALUE		137
#define DVCMD_GOODBYE			138

// IDs returned by device that are NOT EEPROM
// Note that in most non-EEPROM operations, the device actually returns a copy of the sent command in the ID slot.
// But radio streaming is an exception.
#define DVID_RADIOSTREAM_LO		401
#define DVID_RADIOSTREAM_HI		402

// IDs returned by device that ARE EEPROM
#define MIN_EEPROM_ID			1000	// Any ID over this number will be the ID of an eeprom variable. Any ID below it will be something else

// Safety
#define SERIAL_COMM_TIMEOUT 	7000	// How many milliseconds of inactivity do we wait before we just disconnect from the computer (1000 ms = 1 second)
#define MAX_COMM_ERRORCOUNT		10		// How many communication errors do we permit before simply disconnecting

// Other communication stuff
#define MAX_SENTENCE_VALUES     8       // This is kind of scary, it's just hardcoded here. Make sure TCB doesn't exceed it.
                                        // Presently TCB knows not to send more than 8. When it streams radio data, it only
                                        // sends 8 channels at a time, and alternates between the first 8 and the second 8 for 16 channel radios.
#define SENTENCE_BUFF			128     // Enough bytes to hold all the characters of a sentence. In practice it shouldn't actually exceed 64,
                                        // but this is a computer with unlimited resources, so set it high to be safe.

// If we also want to include data sent or received in communication mode to the console, set these to true
#define APPEND_SENT_TO_CONSOLE  true
#define APPEND_RECEIVED_TO_CONSOLE  true

// Debugging
#define DEBUG_MSGS              false    // Set to true to have serial comms printed to the debug panel
#define DEBUG_SEND_RECEIVE      false    // Print the send/receive sentences to the debug panel


struct PortSettings {
    QString name;
    QString stringBaudRate;
    //qint32 baudRate;
    QSerialPort::BaudRate baudRate;
    QSerialPort::DataBits dataBits;
    QString stringDataBits;
    QSerialPort::Parity parity;
    QString stringParity;
    QSerialPort::StopBits stopBits;
    QString stringStopBits;
    QSerialPort::FlowControl flowControl;
    QString stringFlowControl;
};

struct DataSentence {
    uint8_t     Command = 0;
    uint16_t    ID = 0;
    QByteArray  Value;                         // EEPROM and most other sentences will have a single value
    QByteArray  Values[MAX_SENTENCE_VALUES];   // But some sentences like radio pulse widths can have multiple values
    uint8_t     NumValues;                     // The number of values received (ignored when sending)
    int16_t     Checksum = 0;
};



// Class OP_PCComm
class OpenPanzerComm : public QObject // By inheriting from QObject, the class can use signal and slot mechanism
{
    Q_OBJECT    // need this macro for QObject to work

    // -------------------------------------------------------------------------------------------------------->>
    // PUBLIC
    // -------------------------------------------------------------------------------------------------------->>
    public:
         explicit OpenPanzerComm();		// Constructor

        // Functions
        void begin();           // Init
        void skipCRC();         // Mostly used for testing, we can skip CRC checking (the CRC portion of the sentence must still be provided though, it just won't be checked)
        void requireCRC();      // turn CRC back on
        void updatePortSettings(QString comName, QSerialPort::BaudRate);   // For now just updates the COM port and Baud rate (other settings are hard-coded)
        void openSerial_forComms(void);  // Open serial port and attempt to connect to device
        void openSerial_forSnoop(void);  // Open serial port, and that's it.
        void closeSerial(void); // Close serial port and tell device Goodbye
        void Snoop(void);       // This opens the serial port but doesn't attempt to establish communication with the device
        void ConnectFromSnoop(void);        // Attempt to connect after we have already opened the serial port for snooping
        void requestFirmwareVersion(void);
        void requestMinOPCVersion(void);
        void requestUtilizedRadioChannels(void);
        void startStreamRadio(void);
        void stopStreamRadio(void);
        void SetSabertoothBaudRate(uint8_t SabertoothBaud);
        void defaultWatchdogTimeout(void);                      // The Sabertooth setup takes a long time so we temporarily increase the watchdog timeout. This public function allows us to set it back when we're done.
        void ConfigurePololu_Drive(void);
        void ConfigurePololu_Turret(void);

        boolean sendNullValueSentence(uint8_t CMD);
        boolean sendSentence(DataSentence &_sentence);
        void readEEPROM(uint16_t WhatID);
        void writeEEPROM(uint16_t WhatID, QByteArray WhatValue);

        boolean isConnected(void);  // returns connection status
        boolean isSnooping(void);   // returns snooping status
        boolean isRadioStreaming(void); // Is the radio currently streaming?
        void resetDevice(void);     // We may want to reboot the device in order for it to load new variables we have passed.

        // Vars
        PortSettings currentPortSettings;
        int16_t pulseWidths[COUNT_OP_CHANNELS];         // Array to store pulse widths when the device streams radio data


        //public slots:

    // -------------------------------------------------------------------------------------------------------->>
    // SIGNALS
    // -------------------------------------------------------------------------------------------------------->>
    signals:
        void ConnectionChanged(boolean connected);      // Signal for anytime we connect or disconnect
        void SnoopingChanged(boolean snooping);         // Signal for anytime we open or close port for the purpose of snooping
        void RadioStreamingChanged(boolean streaming);  // Radio streaming has started or stopped
        void HereIsFirmwareVersion(QString version);    // Signal for providing firmware version
        void HereIsMinOPCVersion(QString version);      // Signal for providing the minimum OP Config version the TCB expects
        void HereIsValue(uint16_t ID, QByteArray Value, boolean found);// Signal for providing value read from device
        void HereAreNumChannels(uint8_t numChannels);   // Return the number of utilized radio channels
        void HereArePulseWidths(int16_t *pulseWidths);  // Return an array of pulse widths
        void RadioNotReady(void);                       // If the radio is not ready/connected, this signal gets sent
        void RepeatSentence(void);                      // Repeat sentence signal
        void NextSentence(boolean);                     // Next sentence signal
        void AnyData(void);                             // This doesn't necessarily mean a sentence has arrived, but we use this to restart the watchdog
        void NewData(const QByteArray &data);           // Used for the console functionality, this just returns a QByteArray of data that has come in
        void AnySentence(void);                         // A full sentence has arrived, we can use this to stop the watchdog timer
        void AnyRequest(void);                          // Any outgoing request to the device, we will use this to start the watchdog timer
        void CommError(QString, QSerialPort::SerialPortError);                        // Signal for errors that need to be displayer to the user
        void IncrementError(void);                      // Non-critical error handling

    // -------------------------------------------------------------------------------------------------------->>
    // PRIVATE
    // -------------------------------------------------------------------------------------------------------->>
    private:

        // Vars
        // ---------------------------------------------------------------------------------------------------->>
          QSerialPort  *serial;
          boolean		CRCRequired;
          int           numErrors;
          boolean       Connected;  // Connected is serial port open and continous comms established with device
          boolean       Snooping;   // Snopping is serial port open and we are just listening (console mode)
          boolean       RadioStreaming;
          QByteArray    responseData;
          boolean       SentenceReceived;
          DataSentence  SentenceIN;
          DataSentence  SentenceOUT;
          uint8_t       NumErrors;        // How many communication errors have we accumulated since connecting
          int           WatchdogTimeout;

        // Connection
        // ---------------------------------------------------------------------------------------------------->>
          void setSerialSettings(void);

        // Reading data
        // ---------------------------------------------------------------------------------------------------->>
          void    ClearResponseData(void);
          boolean ParseSentence(QByteArray &data);
          boolean AcknowledgmentReceived();
          boolean GoodbyeReceived();

        // Sending data
        // ---------------------------------------------------------------------------------------------------->>
          void clearSentenceOUT(void);
          void ConnectToDevice(void);          // Sends the INIT_STRING
          void TellDevice_Goodbye(void);
          QByteArray sentenceToByteArray(DataSentence _sentence);
          boolean _EEPROM_Written;
          boolean StayAwakeJustSent;
          uint8_t MissedStayAwakeCount;

        // Utilities
        // ---------------------------------------------------------------------------------------------------->>
          int32_t constructNumber(char *c, int numBytes);
          int16_t calcrc(char *ptr, int16_t count);

        // Debugging
        // ---------------------------------------------------------------------------------------------------->>
          void sentenceToDebug(DataSentence sentence, boolean Sent);
          void sentenceToMsgBox(DataSentence sentence);

        // Timer stuff
        // ---------------------------------------------------------------------------------------------------->>
           boolean startBlitz;                 // Set to true after we think the device has rebooted, and now we will start spamming it with init strings
           boolean SkipWatchdog;               // We can set this to true to skip a watchdog-response timer for one sentence
           QTimer *initTimer;                  // This timer will run wile we try to connect to the device.
           QTimer *blitzTimer;                 // This timer will repeatedly send the INIT_STRING until either we get a response, or initTimer expires
           QTimer *watchdogTimer;              // This timer will alert us if we don't get a response from the device
           QTimer *stayAwakeTimer;             // This timer will be used to remain connected to the device even when we aren't actively doing anything with it.
           void startStayAwakeTimer(void);
           void stopStayAwakeTimer(void);
           QTimer *radioStreamingTimer;        // Will use this timer to determine when radio streaming has stopped
           void startRadioStreamingTimer(void);
           void reStartRadioStreamingTimer(void);
           void stopRadioStreamingTimer(void);
           void changeWatchdogTimeout(int);

     // -------------------------------------------------------------------------------------------------------->>
     // PRIVATE SLOTS
     // -------------------------------------------------------------------------------------------------------->>
     private slots:
         // Serial Slots
         // ---------------------------------------------------------------------------------------------------->>
            void readData(void);
            void handleError(QSerialPort::SerialPortError error);
            void handleNonCriticalError(void);

         // Timer slots
         // ---------------------------------------------------------------------------------------------------->>
           void ProcessConnectionChange(boolean connected);  // If true we start the watchdog timer, if false we clear it.
           void ProcessSnoopingChange(boolean snooping);     //
           void sendInit(void);
           void connectionFailed(void);
           void watchdogBark(void);
           void keepDeviceAwake(void);
           void startWatchdog(void);       // We will connect this to OpenPanzerComm->AnyRequest signal
           void restartWatchdog(void);     // We will connect this to OpenPanzerComm->AnyData signal
           void stopWatchdog(void);        // We will connect this to OpenPanzerComm->AnySentence signal
           void radioStreamingTimeout(void);    // If this timer expires, radio streaming has ended.

         // Communication slots
         // ---------------------------------------------------------------------------------------------------->>
           void processRepeatSentence(void);        // When the device sends a DVCMD_REPEAT_SENTENCE request

};


#endif // OPENPANZERCOMM_H

