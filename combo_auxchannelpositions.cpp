#include "combo_auxchannelpositions.h"

AuxChannelPositionsCombo::AuxChannelPositionsCombo(QWidget *parent) : QComboBox(parent)
{
    // Fill on creation
    this->insertItem(0, "2", 2);
    this->insertItem(1, "3", 3);

    // We could also create more positions. 5 positions is already programmed on both the TCB side and in this
    // program, though it doesn't make much sense for most radios.
    // A 6-position switch might be more common (mix between a 2 and 3 position switch), and maybe an arbitrary number
    // up to whatever for people who want to install multi-position rotary knobs...

    //    this->insertItem(2, "5", 5);

    // Connect to my custom signal
    connect(this, SIGNAL(editTextChanged(QString)), this, SLOT(AuxChannelPositionChangedSlot(QString)));
    connect(this, SIGNAL(currentIndexChanged(QString)), this, SLOT(AuxChannelPositionChangedSlot(QString)));
}
void AuxChannelPositionsCombo::AuxChannelPositionChangedSlot(const QString &)
{
    // Send out custom signal with a pointer to this box
    emit AuxChannelPositionChanged(this);
}

