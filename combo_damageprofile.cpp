#include "combo_damageprofile.h"

DamageProfileComboBox::DamageProfileComboBox(QWidget *parent) : QComboBox(parent)
{
    /* generate the default options with associated values */

    /* From OP_Tank.h
    typedef char DAMAGEPROFILES;
    #define TAMIYA_DAMAGE   	0		// Stock Tamiya damage profile
    #define OPENPANZER_DAMAGE	1		// Open Panzer damage profile
    */

    this->insertItem(count(), "Tamiya Spec", TAMIYA_DAMAGE);
    this->insertItem(count(), "Experimental", OPENPANZER_DAMAGE);
}

