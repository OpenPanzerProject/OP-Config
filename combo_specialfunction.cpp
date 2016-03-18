#include "combo_specialfunction.h"

SpecialFunctionComboBox::SpecialFunctionComboBox(QWidget *parent) : QComboBox(parent)
{
    // We fill the combo box with a list of all the special functions - their descriptions in the Label column, and their codes in the user Data column.
    // We get these key/value pairs from our OP_QMaps class (it holds a bunch of maps of interest)
    OPQMap = new OP_QMaps;
    SFQMap = OPQMap->getAllSpecialFunctionsQMap();
    SFDigitalQMap = OPQMap->getDigitalSpecialFunctionsQMap();
    SFAnalogQMap = OPQMap->getAnalogSpecialFunctionsQMap();

    // Populate the combo box
    QMapIterator<_special_function, QString> i(SFQMap);
    while (i.hasNext())
    {
        i.next();
        insertItem(count(), i.value(), i.key());
    }

    // Because it will be less coding, we first add everything, then remove the external outputs after
    this->removeExternalOutputsA();
    this->removeExternalOutputsB();
    // Now other processes will add them back if appropriate

    // If either the text or index has changed, emit our custom signal
    connect(this, SIGNAL(editTextChanged(QString)), this, SLOT(CurrentFunctionChangedSlot(QString)));
    connect(this, SIGNAL(currentIndexChanged(QString)), this, SLOT(CurrentFunctionChangedSlot(QString)));
}

void SpecialFunctionComboBox::CurrentFunctionChangedSlot(const QString &)
{
    // Send out a signal with the old value, the new value, and a pointer to this box
    _special_function sf = static_cast<_special_function>(this->currentData().toInt());
    emit currentFunctionChanged(sf, OPQMap->isSpecialFunctionDigital(sf));
}

boolean SpecialFunctionComboBox::isFunctionDigital(_special_function sf)
{
    return OPQMap->isSpecialFunctionDigital(sf);
}

void SpecialFunctionComboBox::AddSF(_special_function sf)
{
    boolean alreadyThere = false;

    for (int i=0; i<this->count(); i++)
    {
        if (this->itemData(i) == sf) alreadyThere = true;
    }

    if (!alreadyThere)
    {
        this->insertItem(count(), SFQMap.value(sf), sf);
        // emit a signal
        emit specialFunctionAdded(sf);
    }
}

void SpecialFunctionComboBox::RemoveSF(_special_function sf)
{
    for (int i=0; i<this->count(); i++)
    {
        if (this->itemData(i) == sf) { this->removeItem(i); emit specialFunctionRemoved(sf); }
    }
}

boolean SpecialFunctionComboBox::isSFPresent(_special_function sf)
{
    for (int i=0; i<this->count(); i++)
    {
        if (this->itemData(i) == sf) { return true; }
    }
    // If we make it to here, the special function is not present
    return false;
}

void SpecialFunctionComboBox::addExternalOutputsA(void)
{
    boolean toggleThere = false;
    boolean onThere = false;
    boolean offThere = false;

    // We won't know until we've been through every item of the list, which ones are present
    // Assume none are, run through each item, set a flag if it already exists
    for (int i=0; i<this->count(); i++)
    {
        if (this->itemData(i) == SF_OUTPUT_A_TOGGLE) toggleThere = true;
        if (this->itemData(i) == SF_OUTPUT_A_ON) onThere = true;
        if (this->itemData(i) == SF_OUTPUT_A_OFF) offThere = true;
    }

    // If any don't exists, add them
    if (!toggleThere) this->insertItem(count(), SFQMap.value(SF_OUTPUT_A_TOGGLE), SF_OUTPUT_A_TOGGLE);
    if (!onThere) this->insertItem(count(), SFQMap.value(SF_OUTPUT_A_ON), SF_OUTPUT_A_ON);
    if (!offThere) this->insertItem(count(), SFQMap.value(SF_OUTPUT_A_OFF), SF_OUTPUT_A_OFF);

    // If any were added, emit the signal
    if (!toggleThere || !onThere || !offThere)
    {
        _EOA_Present = true;
        emit externalOutputsA_Added();    // Let the world know this has been added
    }
}

void SpecialFunctionComboBox::addExternalOutputsB(void)
{
    boolean toggleThere = false;
    boolean onThere = false;
    boolean offThere = false;

    // We won't know until we've been through every item of the list, which ones are present
    // Assume none are, run through each item, set a flag if it already exists
    for (int i=0; i<this->count(); i++)
    {
        if (this->itemData(i) == SF_OUTPUT_B_TOGGLE) toggleThere = true;
        if (this->itemData(i) == SF_OUTPUT_B_ON) onThere = true;
        if (this->itemData(i) == SF_OUTPUT_B_OFF) offThere = true;
    }

    // If any don't exists, add them
    if (!toggleThere) this->insertItem(count(), SFQMap.value(SF_OUTPUT_B_TOGGLE), SF_OUTPUT_B_TOGGLE);
    if (!onThere) this->insertItem(count(), SFQMap.value(SF_OUTPUT_B_ON), SF_OUTPUT_B_ON);
    if (!offThere) this->insertItem(count(), SFQMap.value(SF_OUTPUT_B_OFF), SF_OUTPUT_B_OFF);

    // If any were added, emit the signal
    if (!toggleThere || !onThere || !offThere)
    {
        _EOB_Present = true;
        emit externalOutputsB_Added();    // Let the world know this has been added
    }
}

boolean SpecialFunctionComboBox::isExternalOutputAPresent(void)
{
    return _EOA_Present;
}

boolean SpecialFunctionComboBox::isExternalOutputBPresent(void)
{
    return _EOB_Present;
}

void SpecialFunctionComboBox::removeExternalOutputsA(void)
{
    for (int i=0; i<this->count(); i++)
    {
        if (this->itemData(i) == SF_OUTPUT_A_TOGGLE) { this->removeItem(i); _EOA_Present = false; }
        if (this->itemData(i) == SF_OUTPUT_A_ON) { this->removeItem(i);  _EOA_Present = false; }
        if (this->itemData(i) == SF_OUTPUT_A_OFF) { this->removeItem(i);  _EOA_Present = false; }
    }
}

void SpecialFunctionComboBox::removeExternalOutputsB(void)
{
    for (int i=0; i<this->count(); i++)
    {
        if (this->itemData(i) == SF_OUTPUT_B_TOGGLE) { this->removeItem(i); _EOB_Present = false; }
        if (this->itemData(i) == SF_OUTPUT_B_ON) { this->removeItem(i); _EOB_Present = false; }
        if (this->itemData(i) == SF_OUTPUT_B_OFF) { this->removeItem(i); _EOB_Present = false; }
    }
}


void SpecialFunctionComboBox::addServoPassthrough(int servoNum)
{
    boolean servoThere = false;
    _special_function servoFunction;

    switch (servoNum)
    {
    case 1:
        servoFunction = SF_SERVO1_PASS;
        _Servo1_Present = true;     // It may actually not be present yet, but it will be by the time this function exits.
        break;
    case 2:
        servoFunction = SF_SERVO2_PASS;
        _Servo2_Present = true;
        break;
    case 3:
        servoFunction = SF_SERVO3_PASS;
        _Servo3_Present = true;
        break;
    case 4:
        servoFunction = SF_SERVO4_PASS;
        _Servo4_Present = true;
        break;
    default:
        servoFunction = SF_NULL_FUNCTION;
    }

    // Do nothing if invalid number
    if (servoFunction == SF_NULL_FUNCTION) return;

    // We won't know until we've been through every item of the list, which ones are present
    // Assume none are, run through each item, set a flag if it already exists
    for (int i=0; i<this->count(); i++)
    {
        if (this->itemData(i) == servoFunction) servoThere = true;
    }

    // If any don't exists, add them
    if (!servoThere) this->insertItem(count(), SFQMap.value(servoFunction), servoFunction);

    // If any were added, emit the signal
    if (!servoThere)
    {
        emit servoPassthroughAdded(servoNum);   // Let the world know this has been added
    }
}
void SpecialFunctionComboBox::removeServoPassthrough(int servoNum)
{
    _special_function servoFunction;

    switch (servoNum)
    {
    case 1:
        servoFunction = SF_SERVO1_PASS;
        _Servo1_Present = false;     // It may actually not be removed yet, but it will be by the time this function exits.
        break;
    case 2:
        servoFunction = SF_SERVO2_PASS;
        _Servo2_Present = false;
        break;
    case 3:
        servoFunction = SF_SERVO3_PASS;
        _Servo3_Present = false;
        break;
    case 4:
        servoFunction = SF_SERVO4_PASS;
        _Servo4_Present = false;
        break;
    default:
        servoFunction = SF_NULL_FUNCTION;
    }

    // Do nothing if invalid number
    if (servoFunction == SF_NULL_FUNCTION) return;

    for (int i=0; i<this->count(); i++)
    {
        if (this->itemData(i) == servoFunction) { this->removeItem(i); }
    }
}
void SpecialFunctionComboBox::removeAllServoPassthroughs(void)
{
    removeServoPassthrough(1);
    removeServoPassthrough(2);
    removeServoPassthrough(3);
    removeServoPassthrough(4);
}
void SpecialFunctionComboBox::addAllServoPassthroughs(void)
{
    addServoPassthrough(1);
    addServoPassthrough(2);
    addServoPassthrough(3);
    addServoPassthrough(4);
}

boolean SpecialFunctionComboBox::isServoPassthroughPresent(int servoNum)
{
    switch (servoNum)
    {
    case 1:
        return _Servo1_Present;
        break;
    case 2:
        return _Servo2_Present;
        break;
    case 3:
        return _Servo3_Present;
        break;
    case 4:
        return _Servo4_Present;
        break;
    default:
        return false;
    }
}


// We can programmatically set the combo box to a value by passing it directly the enum code
void SpecialFunctionComboBox::setCurrentFunction(int sf)
{
    this->setCurrentIndex(this->findData(sf));
}

// We can programmatically set the combo box to a value by passing it a special_function enum member name
void SpecialFunctionComboBox::setCurrentFunction(const _special_function& sf)
{
    this->setCurrentIndex(this->findData(sf));

}

void SpecialFunctionComboBox::clearCurrentFunction(void)
{
    this->setCurrentFunction(SF_NULL_FUNCTION);
}

// This returns the current actual special_function
_special_function SpecialFunctionComboBox::getCurrentFunction(void)
{
    return static_cast<_special_function>(this->currentData().toInt());
}

