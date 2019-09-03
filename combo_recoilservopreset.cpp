#include "combo_recoilservopreset.h"

RecoilServoPresetComboBox::RecoilServoPresetComboBox(QWidget *parent) : QComboBox(parent)
{
    // Fill on creation
    this->insertItem(1, "", RS_PRESET_NONE);
    this->insertItem(2, "Taigen Tiger 1 w/ Airsoft Servo Recoil", RS_PRESET_TAIGEN_TIGER1);

    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(emitRecoilServoPresetChanged()));

    /* THIS ISN'T PRESENTLY USED BECAUSE FOR NOW THERE IS ONLY A SINGLE PRESET, AND WE JUST SET OUR DEFAULT
     * VALUES TO IT. But if some day we get a lot of other pre-assembled servo recoil units available for sale,
     * we can create more presets the user can choose to setup the recoil servo. You will need to emit a signal
     * when the value in the combo box is changed, and then have data saved somewhere about the servo's
     * reversed status, time to recoil and time to return, as well as min and max values.
     *
     * You will also want to define the available preset numbers in TCB firmware as well.
     *
     * For now the preset number is a uint8_t that is passed to the TCB in the eeprom variable #2020 "RecoilServo_PresetNum"
     */
}

void RecoilServoPresetComboBox::emitRecoilServoPresetChanged()
{   // Whenever index changes, we emit the current smoker type in both QByteArray and QString format.
    emit currentRecoilPresetChanged(this->currentData().toByteArray());
    emit currentRecoilPresetChanged(this->currentText());
    emit currentRecoilPresetChanged(static_cast<RecoilPreset>(this->currentData().toUInt()));
}

// We can programmatically set the combo box to a value by passing it directly the enum code
void RecoilServoPresetComboBox::setCurrentRecoilPreset(int recoilPresetNum)
{
    this->setCurrentIndex(this->findData(recoilPresetNum));
}

// We can programmatically set the combo box to a value by passing it a Smoker_t enum member name
void RecoilServoPresetComboBox::setCurrentRecoilPreset(const RecoilPreset& rs)
{
    this->setCurrentIndex(this->findData(rs));

}

// Returns the current index by string name
int RecoilServoPresetComboBox::getCode(QString label)
{
    return this->findText(label);
}

// Returns the current index by enum code
QString RecoilServoPresetComboBox::getLabel(int code)
{
    return this->itemText(this->findData(code));
}

// This returns the current actual Smoker_t
RecoilPreset RecoilServoPresetComboBox::getCurrentRecoilPreset(void)
{
    return RecoilPreset(this->currentData().toInt());
}

