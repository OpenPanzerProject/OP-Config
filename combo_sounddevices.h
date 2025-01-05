#ifndef SOUNDDEVICESCOMBOBOX_H
#define SOUNDDEVICESCOMBOBOX_H

#include <QObject>
#include <QComboBox>
#include <op_defines.h>

class SoundDevicesComboBox : public QComboBox
{
    Q_OBJECT
public:
    SoundDevicesComboBox(QWidget *parent = 0);

    SOUND_DEVICE getCurrentSoundDevice(void);

public slots:
    void setCurrentSoundDevice(const SOUND_DEVICE& sd);
    void setCurrentSoundDevice(int sd);

signals:
    void currentSoundDeviceChanged(int);

private slots:
    void CurrentDeviceChangedSlot(void);

};

#endif // SOUNDDEVICESCOMBOBOX_H
