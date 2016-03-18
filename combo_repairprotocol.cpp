#include "combo_repairprotocol.h"

RepairProtocolComboBox::RepairProtocolComboBox(QWidget *parent) : QComboBox(parent)
{
    /* generate the default options with associated values */

    /* From OP_IRLib.h
    #define IR_RPR_CLARK   		// Repair signal: Clark TK-20, 22, and 60 repair protocol
    #define IR_RPR_IBU 	   		// Repair signal: Italian Battle Unit
    #define IR_RPR_RCTA	   		// Repair signal: RC Tanks Australia Mako. Theoretically this is the same as IBU, but untested.
    */

    this->insertItem(count(), "Clark Repair", IR_RPR_CLARK);
    this->insertItem(count(), "IBU Repair", IR_RPR_IBU);
    this->insertItem(count(), "RCTA Repair", IR_RPR_RCTA);
}

