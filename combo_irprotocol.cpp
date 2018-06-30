#include "combo_irprotocol.h"


IRProtocolComboBox::IRProtocolComboBox(QWidget *parent) : QComboBox(parent) {}

void IRProtocolComboBox::SetupPrimary()
{
// Setup Primary appends every value, along with a disable option
    this->insertItem(0, "Disable Cannon IR", IR_UNKNOWN);
    this->insertItem(count(), "Tamiya", IR_TAMIYA);                     // We need to explicitly list both of these, because
    this->insertItem(count(), "Tamiya 2-Shot Kill", IR_TAMIYA_2SHOT);   // the user can only choose to fire one or the other, not both.
    this->insertItem(count(), "Taigen (V1)", IR_TAIGEN_V1);             // Taigen V1
    this->insertItem(count(), "Taigen (V2/V3)", IR_TAIGEN);             // Taigen V2/V3
    this->insertItem(count(), "Heng-Long", IR_HENGLONG);
    this->insertItem(count(), "Tamiya 1/35", IR_TAMIYA_35);
    this->insertItem(count(), "VsTank 1/24", IR_VSTANK);
    this->insertItem(count(), "Forces of Valor 1/24", IR_FOV);
    //this->insertItem(count(), "Open Panzer", IR_OPENPANZER);  // For some future day when Open Panzer becomes the standard... ha!
}

void IRProtocolComboBox::SetupSecondary(IRTYPES skipIR)
{
IRTYPES previousIR = static_cast<IRTYPES>(this->currentData().toUInt());

// Secondary gives us every option other than the one already selected in primary
// It also give us a "None" option

// First, clear anything in the box
    this->clear();

// Now add the None option
    this->insertItem(0, "None", IR_UNKNOWN);

// Now add all the remaining options - the only unusual thing here, is that we add a single entry for Tamiya 1/16
    // The user doesn't have to specify both Tamiya AND Tamiya 2-Shot Kill, if they just specify Tamiya we will automatically
    // check for hits from both. Of course in the primary slot (above) we do list both separately, because when firing the tank
    // can only fire one or the other.
    this->insertItem(count(), "Tamiya (Incl. 2-Shot Kill)", IR_TAMIYA);
    this->insertItem(count(), "Taigen (V1)", IR_TAIGEN_V1);
    this->insertItem(count(), "Taigen (V2/V3)", IR_TAIGEN);
    this->insertItem(count(), "Heng-Long", IR_HENGLONG);
    this->insertItem(count(), "Tamiya 1/35", IR_TAMIYA_35);
    this->insertItem(count(), "VsTank 1/24", IR_VSTANK);
    this->insertItem(count(), "Forces of Valor 1/24", IR_FOV);
    //this->insertItem(count(), "Open Panzer", IR_OPENPANZER);  // For some future day when Open Panzer becomes the standard... ha!

// This gets complicated, but in the case of Tamiya, if the primary protocol is either
    // regular Tamiya or Tamiya 2-shot, we remove both from the secondary, because both will automatically be checked
    if (skipIR == IR_TAMIYA || skipIR == IR_TAMIYA_2SHOT)
    {
        for (int i=0; i<this->count(); i++)
        {
            if (this->itemData(i) == IR_TAMIYA || this->itemData(i) == IR_TAMIYA_2SHOT) this->removeItem(i);
        }
    }
    // Now remove the protocol passed as skipIR, unless it is zero.
    else if (skipIR != IR_UNKNOWN)
    {
        for (int i=0; i<this->count(); i++)
        {
            if (this->itemData(i) == skipIR) this->removeItem(i);
        }
    }

// Finally - try to put the selection back on whatever they had before, unless what they had before
    // has now moved to primary (but in that case it won't even be in this list)
    for (int i=0; i<this->count(); i++)
    {
        if (this->itemData(i) == previousIR) this->setCurrentIndex(i);
    }
}

void IRProtocolComboBox::InsertNoneSelection()
{
    // Sometimes, but not always, we may want the user to have the option of selecting "none"
    this->insertItem(0, "None", IR_UNKNOWN);
}

void IRProtocolComboBox::InsertDisableSelection()
{
    this->insertItem(0, "Disable Cannon IR", IR_UNKNOWN);
}
