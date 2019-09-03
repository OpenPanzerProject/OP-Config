#include "combo_smokertype.h"

SmokerTypeComboBox::SmokerTypeComboBox(QWidget *parent) :	QComboBox(parent)
{
        // Fill on creation
    this->insertItem(1, "Combined Heat & Fan", SMOKERTYPE_ONBOARD_STANDARD);
    this->insertItem(2, "Separate Heat & Fan", SMOKERTYPE_ONBOARD_SEPARATE);
    this->insertItem(3, "Experimental", SMOKERTYPE_SERIAL);

    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(emitSmokerTypeChanged()));

}

void SmokerTypeComboBox::emitSmokerTypeChanged()
{   // Whenever index changes, we emit the current smoker type in both QByteArray and QString format.
    emit currentSmokerTypeChanged(this->currentData().toByteArray());
    emit currentSmokerTypeChanged(this->currentText());
    emit currentSmokerTypeChanged(static_cast<Smoker_t>(this->currentData().toUInt()));
}

// We can programmatically set the combo box to a value by passing it directly the enum code
void SmokerTypeComboBox::setCurrentSmokerType(int smokerTypeCode)
{
    this->setCurrentIndex(this->findData(smokerTypeCode));
}

// We can programmatically set the combo box to a value by passing it a Smoker_t enum member name
void SmokerTypeComboBox::setCurrentSmokerType(const Smoker_t& smokerType)
{
    this->setCurrentIndex(this->findData(smokerType));

}

// Returns the current index by string name
int SmokerTypeComboBox::getCode(QString label)
{
    return this->findText(label);
}

// Returns the current index by enum code
QString SmokerTypeComboBox::getLabel(int code)
{
    return this->itemText(this->findData(code));
}

// This returns the current actual Smoker_t
Smoker_t SmokerTypeComboBox::getCurrentSmokerType(void)
{
    return Smoker_t(this->currentData().toInt());
}

