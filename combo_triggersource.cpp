#include "combo_triggersource.h"

TriggerSourceComboBox::TriggerSourceComboBox(QWidget *parent) : QComboBox(parent)
{
    // We fill the combo box with a list of all the triggers - their descriptions in the Label column, and their codes in the user Data column.
    // We get these key/value pairs from our OP_QMaps class (it holds a bunch of maps of interest)
    OPQMap = new OP_QMaps;
    TSQMap = OPQMap->getAllTriggerSourcesQMap();
    TSDigitalQMap = OPQMap->getDigitalTriggerSourcesQMap();
    TSAnalogQMap = OPQMap->getAnalogTriggerSourcesQMap();

    // We don't populate this combo box. It is set later by other processes
    _EIA_Present = false;
    _EIB_Present = false;

    // Connect to my custom signal
    //connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(CurrentTriggerSourceChangedSlot(int)));
}

boolean TriggerSourceComboBox::isTriggerSourceAux(_trigger_source ts)
{
    return OPQMap->isTriggerSourceAuxChannel(ts);
}

void TriggerSourceComboBox::addExternalInputA(void)
{
    boolean alreadyThere = false;

    for (int i=0; i<this->count(); i++)
    {
        if (this->itemData(i) == TS_INPUT_A) alreadyThere = true;
    }
    if (!alreadyThere)
    {
        this->insertItem(count(), TSQMap.value(TS_INPUT_A), TS_INPUT_A);
        _EIA_Present = true;
        emit externalInputA_Added();    // Let the world know this has been added
    }
}

void TriggerSourceComboBox::addExternalInputB(void)
{
    boolean alreadyThere = false;

    for (int i=0; i<this->count(); i++)
    {
        if (this->itemData(i) == TS_INPUT_B) alreadyThere = true;
    }
    if (!alreadyThere)
    {
        this->insertItem(count(), TSQMap.value(TS_INPUT_B), TS_INPUT_B);
        _EIB_Present = true;
        emit externalInputB_Added();    // Let the world know this has been added
    }
}

boolean TriggerSourceComboBox::isExternalInputAPresent(void)
{
    return _EIA_Present;
}

boolean TriggerSourceComboBox::isExternalInputBPresent(void)
{
    return _EIB_Present;
}

void TriggerSourceComboBox::removeExternalInputA(void)
{
    for (int i=0; i<this->count(); i++)
    {
        if (this->itemData(i) == TS_INPUT_A) this->removeItem(i); //_EIA_Present = false;
    }
}

void TriggerSourceComboBox::removeExternalInputB(void)
{
    for (int i=0; i<this->count(); i++)
    {
        if (this->itemData(i) == TS_INPUT_B) this->removeItem(i); //_EIB_Present = false;
    }
}

// We can programmatically set the combo box to a value by passing it directly the enum code
void TriggerSourceComboBox::setCurrentTriggerSource(int ts)
{
    this->setCurrentIndex(this->findData(ts));
}

// We can programmatically set the combo box to a value by passing it a special_function enum member name
void TriggerSourceComboBox::setCurrentTriggerSource(const _trigger_source& ts)
{
    this->setCurrentIndex(this->findData(ts));

}

void TriggerSourceComboBox::clearCurrentTriggerSource(void)
{
    this->setCurrentTriggerSource(TS_NULL_TRIGGER);
}

// This returns the current actual trigger source
_trigger_source TriggerSourceComboBox::getCurrentTriggerSource(void)
{
    return static_cast<_trigger_source>(this->currentData().toInt());
}
