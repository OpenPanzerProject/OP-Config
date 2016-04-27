#include "combo_recoilservopreset.h"

RecoilServoPresetComboBox::RecoilServoPresetComboBox(QWidget *parent) : QComboBox(parent)
{
    /* generate the default options with associated values */

    insertItem(0, "", 0);
    this->insertItem(count(), "Taigen Tiger 1 Airsoft Servo Recoil", 1);

    /* THIS ISN'T PRESENTLY USED BECAUSE FOR NOW THERE IS ONLY A SINGLE PRESET, AND WE JUST SET OUR DEFAULT
     * VALUES TO IT. But if some day we get a lot of other pre-assembled servo recoil units available for sale,
     * we can create more presets the user can choose to setup the recoil servo. You will need to emit a signal
     * when the value in the combo box is changed, and then have data saved somewhere about the servo's
     * reversed status, time to recoil and time to return, as well as min and max values.
     *
     */
}
