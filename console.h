#ifndef CONSOLE_H
#define CONSOLE_H

#include <QtCore/QtGlobal>
#include <QtSerialPort/QSerialPort> // Serial port
#include <QDebug.h>
#include <arduino_compat.h>         // Gives us Arduino-like data type names


#define MAX_CONSOLE_ERRORCOUNT		10		// How many communication errors do we permit before simply disconnecting

struct ConsolePortSettings {
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


class Console : public QObject // By inheriting from QObject, the class can use signal and slot mechanism
{
    Q_OBJECT    // need this macro for QObject to work

    public:
         explicit Console();                // Constructor

        // Functions
        void    begin();                       // Init
        void    updatePortSettings(QString comName);   // For now just updates the COM port to use (other settings are hard-coded)
        void    openSerial(void);              // Open serial port and attempt to connect to device
        void    closeSerial(void);             // Close serial port and tell device Goodbye
        boolean isConnected(void);          // returns connection status
        void    toggleDTR(void);

        // Vars
        ConsolePortSettings currentPortSettings;


    signals:
        void    ConnectionChanged(boolean connected);      // Signal for anytime we connect or disconnect
        void    AnyData(void);                             // This doesn't necessarily mean a sentence has arrived, but we use this to restart the watchdog
        void    CommError(QString, QSerialPort::SerialPortError);                        // Signal for errors that need to be displayer to the user

    private:

        // Vars
        // ---------------------------------------------------------------------------------------------------->>
          QSerialPort  *serial;
          int           NumErrors;
          boolean       Connected;
          QByteArray    responseData;

        // Reading data
        // ---------------------------------------------------------------------------------------------------->>
          void    ClearResponseData(void);

     private slots:
         // Serial Slots
         // ---------------------------------------------------------------------------------------------------->>
            void readData(void);
            void handleError(QSerialPort::SerialPortError error);
            void ProcessConnectionChange(boolean connected);

};

#endif // CONSOLE_H
