#include "combo_drivepreset.h"

DrivePresetComboBox::DrivePresetComboBox(QWidget *parent) : QComboBox(parent) {}

void DrivePresetComboBox::setCategory(PRESET_TYPE pt)
{
    /* generate the default options with associated values */

    // PRESETS ARE BASICALLY EXPERIMENTAL FOR NOW.
    // In fact, as of time of publication, preset 2 & 3 don't actually do
    // anything. When we create some real presets, we may want to give them
    // better names than "Accel Preset 2"
    switch (pt)
    {
        case ptAccel:
            insertItem(0, "None", ADP_NONE);
            insertItem(count(), "Accel Preset 1", ADP_PRESET_1);
            insertItem(count(), "Accel Preset 2", ADP_PRESET_2);
            insertItem(count(), "Accel Preset 3", ADP_PRESET_3);
            break;

        case ptDecel:
            insertItem(0, "None", DDP_NONE);
            insertItem(count(), "Decel Preset 1", DDP_PRESET_1);
            insertItem(count(), "Decel Preset 2", DDP_PRESET_2);
            insertItem(count(), "Decel Preset 3", DDP_PRESET_3);
            break;
    }
}

