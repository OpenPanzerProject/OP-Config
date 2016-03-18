#include "combo_mgprotocol.h"

MGProtocolComboBox::MGProtocolComboBox(QWidget *parent) : QComboBox(parent)
{

    /* generate the default options with associated values */


    /* From OP_IRLib.h - Only the machine gun protocols
    #define IR_UNKNOWN     		// None
    #define IR_MG_CLARK			// Machine gun: Clark protocol (Sony)
    #define IR_MG_MAKO			// Machine gun: Mako protocol
    */

    this->insertItem(count(), "Disable MG IR", IR_UNKNOWN);
    this->insertItem(count(), "Clark MG", IR_MG_CLARK);
    this->insertItem(count(), "RCTA MG", IR_MG_RCTA);

}
