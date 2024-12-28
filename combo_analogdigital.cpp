#include "combo_analogdigital.h"

AnalogDigitalComboBox::AnalogDigitalComboBox(QWidget *parent) : QComboBox(parent)
{
    // Fill on creation
    this->insertItem(0, "Analog (pot)", 0);
    this->insertItem(1, "Digital (switch)",1);

    // Connect to my custom signal
    connect(this, &AnalogDigitalComboBox::currentIndexChanged, this, &AnalogDigitalComboBox::AnalogDigitalChangedSlot);
}
void AnalogDigitalComboBox::AnalogDigitalChangedSlot(const int )
{
    // Send out custom signal with a pointer to this box
    emit analogDigitalChanged(this);
}
