#include "combo_devices.h"

DeviceComboBox::DeviceComboBox(QWidget *parent) : QComboBox(parent)
{
    // Fill on creation
    this->insertItem(0, "TCB", DEVICE_TCB);
    this->insertItem(1, "Scout ESC (R11+)", DEVICE_SCOUT);
    this->insertItem(2, "Scout ESC (R10 & prior)", DEVICE_SCOUT_R10);
    this->insertItem(3, "Sound Card", DEVICE_TEENSYSOUND);

    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(emitFlashDeviceChanged()));

}

void DeviceComboBox::emitFlashDeviceChanged()
{   // Whenever index changes, we emit the current
    emit flashDeviceChanged(static_cast<DEVICE>(this->currentData().toUInt()));
}

// This returns the current actual Device enum
DEVICE DeviceComboBox::getCurrentDevice(void)
{
    return this->currentData().toUInt(); // UN-signed LONG
}
