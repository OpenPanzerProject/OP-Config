#ifndef BAUDRATECOMBOBOX_H
#define BAUDRATECOMBOBOX_H

#include <QObject>
#include <QComboBox>
#include <QSerialPort>  // So we can access baud rates
#include <op_defines.h>

enum BaudCategory
{   bcMotorSerial,
    bcSerial3,
    bcAuxSerial,
    bcUSBSerial,
    bcConsole
};

class BaudRateComboBox : public QComboBox
{
    Q_OBJECT
public:
    BaudRateComboBox(QWidget *parent = 0);
    void setCategory(BaudCategory mc);
    uint32_t getCurrentBaudRate(void);
    void setCurrentBaudRate(int baudRate);
    void setDefaultBaudRate(void);

signals:
    void currentBaudRateChanged(QByteArray);

private slots:
    void emitCurrentBaudRateChanged();

};

#endif // BAUDRATECOMBOBOX_H
