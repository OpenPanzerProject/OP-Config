#include "combo_analogdigital.h"

AnalogDigitalComboBox::AnalogDigitalComboBox(QWidget *parent) : QComboBox(parent)
{
    // Fill on creation
    this->insertItem(0, "Analog (pot)", 0);
    this->insertItem(1, "Digital (switch)",1);

    // Connect to my custom signal
    connect(this, SIGNAL(editTextChanged(QString)), this, SLOT(AnalogDigitalChangedSlot(QString)));
    connect(this, SIGNAL(currentIndexChanged(QString)), this, SLOT(AnalogDigitalChangedSlot(QString)));
}
void AnalogDigitalComboBox::AnalogDigitalChangedSlot(const QString )
{
    // Send out custom signal with a pointer to this box
    emit analogDigitalChanged(this);
}
