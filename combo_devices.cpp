#include "combo_devices.h"

DeviceComboBox::DeviceComboBox(QWidget *parent) : QComboBox(parent)
{
    // Fill on creation
//    this->insertItem(0, "TCB Mk II", DEVICE_TCB_MKII);            // For later use
    this->insertItem(1, "TCB", DEVICE_TCB_MKI);
    this->insertItem(2, "TCB - DIY Version", DEVICE_TCB_DIY);
    this->insertItem(3, "TCB - Heclo Shield", DEVICE_HECLO_SHIELD);
    this->insertItem(4, "Scout ESC (R11+)", DEVICE_SCOUT);
    this->insertItem(5, "Scout ESC (R10 & prior)", DEVICE_SCOUT_R10);
    this->insertItem(6, "Sound Card", DEVICE_TEENSYSOUND);
    this->insertItem(7, "Generic ATmega328", DEVICE_ATMEGA328);
    this->insertItem(8, "Generic ATmega2560", DEVICE_ATMEGA2560);
    this->insertItem(9, "Generic Teensy 3.2",DEVICE_TEENSY32);
//    this->insertItem(10, "AT CM", DEVICE_AT_MKI);            // For later use

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
