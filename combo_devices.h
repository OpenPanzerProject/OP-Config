#ifndef DEVICECOMBOBOX_H
#define DEVICECOMBOBOX_H

#include <QObject>
#include <QComboBox>
#include <op_defines.h>


class DeviceComboBox : public QComboBox
{
        Q_OBJECT
public:
    DeviceComboBox(QWidget *parent = 0);
    DEVICE getCurrentDevice(void);

signals:
    void flashDeviceChanged(DEVICE);      // here we pass back an actual DEVICE type

private slots:
    void emitFlashDeviceChanged();        // We will connect this slot to the built-in index changed, and emit our custom signals

};


#endif // DEVICECOMBOBOX_H
