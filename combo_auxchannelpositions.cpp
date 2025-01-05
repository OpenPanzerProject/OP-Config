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

    // Connect to my custom signal
    connect(this, &AuxChannelPositionsCombo::currentIndexChanged, this, &AuxChannelPositionsCombo::AuxChannelPositionChangedSlot);
}
void AuxChannelPositionsCombo::AuxChannelPositionChangedSlot(const int &)
{
    // Send out custom signal with a pointer to this box
    emit AuxChannelPositionChanged(this);
}
