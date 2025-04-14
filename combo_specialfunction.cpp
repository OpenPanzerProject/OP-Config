#include "combo_specialfunction.h"

SpecialFunctionComboBox::SpecialFunctionComboBox(QWidget *parent) : QComboBox(parent)
{
    // We fill the combo box with a list of all the special functions - their descriptions in the Label column, and their codes in the user Data column.
    // We get these key/value pairs from our OP_QMaps class (it holds a bunch of maps of interest)
    OPQMap = new OP_QMaps;
    SFQMap = OPQMap->getAllSpecialFunctionsQMap();
    QList<_special_function> SFQMap_Sort = OPQMap->getAllSpecialFunctionsSortOrder();
    SFDigitalQMap = OPQMap->getDigitalSpecialFunctionsQMap();
    SFAnalogQMap = OPQMap->getAnalogSpecialFunctionsQMap();

    // Populate the combo box
    // UNFORTUNATELY, QMaps can only be accessed by sorted key, that is the way they are designed. But we want to
    // display these in arbitrary order, because we may add new special functions in time that we want grouped with
    // earlier ones. We probably should have used a QHash instead but at this point I am leery of changing that.
//    QMapIterator<_special_function, QString> i(SFQMap);
//    while (i.hasNext())
//    {
//        i.next();
//        qDebug() << i.value();
//        insertItem(count(), i.value(), i.key());    // QMap key in this case is the ID of the special function. Value is the name.
//    }

    // Instead what we've done is create a distinct QList of special functions in the order we would like them to appear.
    // We iterate through the sort list and use it to pick the items we want from the QMap to insert into the combo box.
    _special_function sf;
    QString qs;
    QListIterator<_special_function> i(SFQMap_Sort);
    while(i.hasNext())
    {
        sf = i.next();                          // This is the _special_function byte
        qs = SFQMap.value(sf);                  // This is the special function name from our QMap
        if (sf == SF_NULL_FUNCTION || qs !="")  // Not every special function may be active. Ignore it if it returns blank except
        {                                       // for the first one which we already know is blank and we want to keep in the list.
            // qDebug() << qs;
            insertItem(count(), qs, sf);
        }
    }

    // Because it will be less coding, we first add everything, then remove the external outputs after
    this->removeExternalOutputsA();
    this->removeExternalOutputsB();
    // Now other processes will add them back if appropriate

    // Connect to my custom signal
    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(CurrentFunctionChangedSlot(int)));
}

void SpecialFunctionComboBox::CurrentFunctionChangedSlot(int selection)
{
    // in Qt 5.4, the following line worked:
 //   _special_function sf = static_cast<_special_function>(selection);

    // However it does not work in Qt6.8, because "selection" passed is now the Index, whereas previously it would seem it was the data.
    // Our special functions (a byte/numeric value that references the function in question) is not the same thing as the index in the list,
    // instead this number is held in data.
//    _special_function sf = qvariant_cast<_special_function>(this->currentData()); // This also works.
    _special_function sf = static_cast<_special_function>(this->currentData().toUInt());
    //qDebug() << selection << " " << this->currentData();

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
    boolean pulseThere = false;
    boolean blinkThere = false;

    // We won't know until we've been through every item of the list, which ones are present
    // Assume none are, run through each item, set a flag if it already exists
    for (int i=0; i<this->count(); i++)
    {
        if (this->itemData(i) == SF_OUTPUT_A_TOGGLE) toggleThere = true;
        if (this->itemData(i) == SF_OUTPUT_A_ON) onThere = true;
        if (this->itemData(i) == SF_OUTPUT_A_OFF) offThere = true;
        if (this->itemData(i) == SF_OUTPUT_A_PULSE) pulseThere = true;
        if (this->itemData(i) == SF_OUTPUT_A_BLINK) blinkThere = true;
    }

    // If any don't exists, add them
    if (!toggleThere) this->insertItem(count(), SFQMap.value(SF_OUTPUT_A_TOGGLE), SF_OUTPUT_A_TOGGLE);
    if (!onThere) this->insertItem(count(), SFQMap.value(SF_OUTPUT_A_ON), SF_OUTPUT_A_ON);
    if (!offThere) this->insertItem(count(), SFQMap.value(SF_OUTPUT_A_OFF), SF_OUTPUT_A_OFF);
    if (!pulseThere) this->insertItem(count(), SFQMap.value(SF_OUTPUT_A_PULSE), SF_OUTPUT_A_PULSE);
    if (!blinkThere) this->insertItem(count(), SFQMap.value(SF_OUTPUT_A_BLINK), SF_OUTPUT_A_BLINK);

    // If any were added, emit the signal
    if (!toggleThere || !onThere || !offThere || !pulseThere || !blinkThere)
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
    boolean pulseThere = false;
    boolean blinkThere = false;

    // We won't know until we've been through every item of the list, which ones are present
    // Assume none are, run through each item, set a flag if it already exists
    for (int i=0; i<this->count(); i++)
    {
        if (this->itemData(i) == SF_OUTPUT_B_TOGGLE) toggleThere = true;
        if (this->itemData(i) == SF_OUTPUT_B_ON) onThere = true;
        if (this->itemData(i) == SF_OUTPUT_B_OFF) offThere = true;
        if (this->itemData(i) == SF_OUTPUT_B_PULSE) pulseThere = true;
        if (this->itemData(i) == SF_OUTPUT_B_BLINK) blinkThere = true;
    }

    // If any don't exists, add them
    if (!toggleThere) this->insertItem(count(), SFQMap.value(SF_OUTPUT_B_TOGGLE), SF_OUTPUT_B_TOGGLE);
    if (!onThere) this->insertItem(count(), SFQMap.value(SF_OUTPUT_B_ON), SF_OUTPUT_B_ON);
    if (!offThere) this->insertItem(count(), SFQMap.value(SF_OUTPUT_B_OFF), SF_OUTPUT_B_OFF);
    if (!pulseThere) this->insertItem(count(), SFQMap.value(SF_OUTPUT_B_PULSE), SF_OUTPUT_B_PULSE);
    if (!blinkThere) this->insertItem(count(), SFQMap.value(SF_OUTPUT_B_BLINK), SF_OUTPUT_B_BLINK);

    // If any were added, emit the signal
    if (!toggleThere || !onThere || !offThere || !pulseThere || !blinkThere)
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
        if (this->itemData(i) == SF_OUTPUT_A_PULSE) { this->removeItem(i);  _EOA_Present = false; }
        if (this->itemData(i) == SF_OUTPUT_A_BLINK) { this->removeItem(i);  _EOA_Present = false; }
    }
}

void SpecialFunctionComboBox::removeExternalOutputsB(void)
{
    for (int i=0; i<this->count(); i++)
    {
        if (this->itemData(i) == SF_OUTPUT_B_TOGGLE) { this->removeItem(i); _EOB_Present = false; }
        if (this->itemData(i) == SF_OUTPUT_B_ON) { this->removeItem(i); _EOB_Present = false; }
        if (this->itemData(i) == SF_OUTPUT_B_OFF) { this->removeItem(i); _EOB_Present = false; }
        if (this->itemData(i) == SF_OUTPUT_B_PULSE) { this->removeItem(i); _EOB_Present = false; }
        if (this->itemData(i) == SF_OUTPUT_B_BLINK) { this->removeItem(i); _EOB_Present = false; }
    }
}

void SpecialFunctionComboBox::addRCPassthrough(int rcOutput)
{
    boolean rcOutputThere1 = false;
    boolean rcOutputThere2 = false;
    _special_function rcFunction1;  // There actually two functions for each RC Output
    _special_function rcFunction2;

    switch (rcOutput)
    {
    case 1:
        rcFunction1 = SF_RC1_PASS;
        rcFunction2 = SF_RC1_PASS_PAN;
        _RCOutput1_Present = true;     // It may actually not be present yet, but it will be by the time this function exits.
        break;
    case 2:
        rcFunction1 = SF_RC2_PASS;
        rcFunction2 = SF_RC2_PASS_PAN;
        _RCOutput2_Present = true;
        break;
    case 3:
        rcFunction1 = SF_RC3_PASS;
        rcFunction2 = SF_RC3_PASS_PAN;
        _RCOutput3_Present = true;
        break;
    case 4:
        rcFunction1 = SF_RC4_PASS;
        rcFunction2 = SF_RC4_PASS_PAN;
        _RCOutput4_Present = true;
        break;
    case 6:
        rcFunction1 = SF_RC6_PASS;
        rcFunction2 = SF_RC6_PASS_PAN;
        _RCOutput6_Present = true;
        break;
    case 7:
        rcFunction1 = SF_RC7_PASS;
        rcFunction2 = SF_RC7_PASS_PAN;
        _RCOutput7_Present = true;
        break;
    case 8:
        rcFunction1 = SF_RC8_PASS;
        rcFunction2 = SF_RC8_PASS_PAN;
        _RCOutput8_Present = true;
        break;
    default:
        rcFunction1 = SF_NULL_FUNCTION;
        rcFunction2 = SF_NULL_FUNCTION;
    }

    // Do nothing if invalid number
    if (rcFunction1 == SF_NULL_FUNCTION && rcFunction2 == SF_NULL_FUNCTION) return;

    // We won't know until we've been through every item of the list, which ones are present
    // Assume none are, run through each item, set a flag if it already exists
    for (int i=0; i<this->count(); i++)
    {
        if (this->itemData(i) == rcFunction1) rcOutputThere1 = true;
        if (this->itemData(i) == rcFunction2) rcOutputThere2 = true;
    }

    // If any don't exists, add them
    if (!rcOutputThere1) this->insertItem(count(), SFQMap.value(rcFunction1), rcFunction1);
    if (!rcOutputThere2) this->insertItem(count(), SFQMap.value(rcFunction2), rcFunction2);

    // If any were added, emit the signal
    if (!rcOutputThere1 || !rcOutputThere2)
    {
        emit rcPassthroughAdded(rcOutput);   // Let the world know this has been added
    }
}
void SpecialFunctionComboBox::removeRCPassthrough(int rcOutput)
{
    _special_function rcFunction1;
    _special_function rcFunction2;

    switch (rcOutput)
    {
    case 1:
        rcFunction1 = SF_RC1_PASS;
        rcFunction2 = SF_RC1_PASS_PAN;
        _RCOutput1_Present = false;     // It may actually not be removed yet, but it will be by the time this function exits.
        break;
    case 2:
        rcFunction1 = SF_RC2_PASS;
        rcFunction2 = SF_RC2_PASS_PAN;
        _RCOutput2_Present = false;
        break;
    case 3:
        rcFunction1 = SF_RC3_PASS;
        rcFunction2 = SF_RC3_PASS_PAN;
        _RCOutput3_Present = false;
        break;
    case 4:
        rcFunction1 = SF_RC4_PASS;
        rcFunction2 = SF_RC4_PASS_PAN;
        _RCOutput4_Present = false;
        break;
    case 6:
        rcFunction1 = SF_RC6_PASS;
        rcFunction2 = SF_RC6_PASS_PAN;
        _RCOutput6_Present = false;
        break;
    case 7:
        rcFunction1 = SF_RC7_PASS;
        rcFunction2 = SF_RC7_PASS_PAN;
        _RCOutput7_Present = false;
        break;
    case 8:
        rcFunction1 = SF_RC8_PASS;
        rcFunction2 = SF_RC8_PASS_PAN;
        _RCOutput8_Present = false;
        break;
    default:
        rcFunction1 = SF_NULL_FUNCTION;
        rcFunction2 = SF_NULL_FUNCTION;
    }

    // Do nothing if invalid number
    if (rcFunction1 == SF_NULL_FUNCTION && rcFunction2 == SF_NULL_FUNCTION) return;

    for (int i=0; i<this->count(); i++)
    {
        if (this->itemData(i) == rcFunction1) { this->removeItem(i); }
        if (this->itemData(i) == rcFunction2) { this->removeItem(i); }
    }
}
void SpecialFunctionComboBox::removeAllRCPassthroughs(void)
{
    removeRCPassthrough(1);
    removeRCPassthrough(2);
    removeRCPassthrough(3);
    removeRCPassthrough(4);
    removeRCPassthrough(6);
    removeRCPassthrough(7);
    removeRCPassthrough(8);
}
void SpecialFunctionComboBox::addAllRCPassthroughs(void)
{
    addRCPassthrough(1);
    addRCPassthrough(2);
    addRCPassthrough(3);
    addRCPassthrough(4);
    addRCPassthrough(6);
    addRCPassthrough(7);
    addRCPassthrough(8);
}

boolean SpecialFunctionComboBox::isRCPassthroughPresent(int rcOutput)
{
    switch (rcOutput)
    {
    case 1:
        return _RCOutput1_Present;
        break;
    case 2:
        return _RCOutput2_Present;
        break;
    case 3:
        return _RCOutput3_Present;
        break;
    case 4:
        return _RCOutput4_Present;
        break;
    case 6:
        return _RCOutput6_Present;
        break;
    case 7:
        return _RCOutput7_Present;
        break;
    case 8:
        return _RCOutput8_Present;
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

