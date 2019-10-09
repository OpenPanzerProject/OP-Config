#include "combo_auxchannelpositions.h"

AuxChannelPositionsCombo::AuxChannelPositionsCombo(QWidget *parent) : QComboBox(parent)
{
    // Fill on creation
    this->insertItem(0, "2", 2);
    this->insertItem(1, "3", 3);
    this->insertItem(2, "4", 4);
    this->insertItem(3, "5", 5);
    this->insertItem(4, "6", 6);
    this->insertItem(5, "7", 7);
    this->insertItem(6, "8", 8);
    this->insertItem(7, "9", 9);
    // We aren't able to go beyond single-digit positions unless we change the trigger ID numbering scheme
    // this->insertItem(8, "10", 10);
    // this->insertItem(9, "11", 11);
    // this->insertItem(10, "12", 12);

    // Switches with up to 6 positions are already defined in TCB firmware, and the number can be increased to any
    // higher amount, although exceeding 3 positions doesn't make sense for most radios unless the user can
    // do advaned programming or has installed a custom rotary knob. 6 positions are probably the common for these
    // modifications (or the user can mix a 2 and 3 position switch).

    // For now we hide positions 4 and 5 just to reduce clutter but they are available with no other change than
    // simply uncommenting the lines above. If positions greater than 6 are desired new definitions will need to
    // be created in TCB firmware, mainly in OP_Radio

    // Connect to my custom signal
    connect(this, SIGNAL(editTextChanged(QString)), this, SLOT(AuxChannelPositionChangedSlot(QString)));
    connect(this, SIGNAL(currentIndexChanged(QString)), this, SLOT(AuxChannelPositionChangedSlot(QString)));
}
void AuxChannelPositionsCombo::AuxChannelPositionChangedSlot(const QString &)
{
    // Send out custom signal with a pointer to this box
    emit AuxChannelPositionChanged(this);
}

