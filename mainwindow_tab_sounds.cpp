#include "mainwindow.h"
#include "ui_mainwindow.h"

// This tab gets a 10 out of 10 for craptastic...

//------------------------------------------------------------------------------------------------------------------------>>
// FORM CONTROLS - SOUND TAB
//------------------------------------------------------------------------------------------------------------------------>>
void MainWindow::SetupControls_SoundTab(void)
{
    // Here we would connect a stacked widget with (future) card-dependent settings to the sound-device select combo box
    // connect(ui->cboSoundDevice, SIGNAL(currentSoundDeviceChanged(int)), ui->stackedWidgetSoundCards, SLOT(setCurrentIndex(int)));

    // Or, if the available settings aren't drastically different, we can handle them with a show/hide routine
    connect(ui->cboSoundDevice, SIGNAL(currentSoundDeviceChanged(int)), this, SLOT(ShowHideSoundCardSettings()));

    // However since we are not now using it we hide it and disable it
    ui->stackedWidgetSoundCards->setEnabled(false);
    ui->stackedWidgetSoundCards->hide();

    // Connect Signals and Slots
    // If we disable neutral turns, no need to allow a neutral turn percent speed
    connect(ui->chkEnableHeadlightSound, SIGNAL(clicked(bool)), this, SLOT(ShowHideHeadlightSoundNote(bool)));
    connect(ui->chkEnableHeadlight2Sound, SIGNAL(clicked(bool)), this, SLOT(ShowHideHeadlight2SoundNote(bool)));
    // If we disable one of the squeaks, we also disable the min/max settings for that squeak
    connect(ui->chkEnableSqueak1, SIGNAL(clicked(bool)), this, SLOT(ShowHideSqueak1Settings(bool)));
    connect(ui->chkEnableSqueak2, SIGNAL(clicked(bool)), this, SLOT(ShowHideSqueak2Settings(bool)));
    connect(ui->chkEnableSqueak3, SIGNAL(clicked(bool)), this, SLOT(ShowHideSqueak3Settings(bool)));
    connect(ui->chkEnableSqueak4, SIGNAL(clicked(bool)), this, SLOT(ShowHideSqueak4Settings(bool)));
    connect(ui->chkEnableSqueak5, SIGNAL(clicked(bool)), this, SLOT(ShowHideSqueak5Settings(bool)));
    connect(ui->chkEnableSqueak6, SIGNAL(clicked(bool)), this, SLOT(ShowHideSqueak6Settings(bool)));
    // Also, if we disable all three squeaks, no need to show the min-squeak speed or any other generic squeak settings
    connect(ui->chkEnableSqueak1, SIGNAL(clicked()), this, SLOT(ShowHideOtherSqueakSettings()));
    connect(ui->chkEnableSqueak2, SIGNAL(clicked()), this, SLOT(ShowHideOtherSqueakSettings()));
    connect(ui->chkEnableSqueak3, SIGNAL(clicked()), this, SLOT(ShowHideOtherSqueakSettings()));
    connect(ui->chkEnableSqueak4, SIGNAL(clicked()), this, SLOT(ShowHideOtherSqueakSettings()));
    connect(ui->chkEnableSqueak5, SIGNAL(clicked()), this, SLOT(ShowHideOtherSqueakSettings()));
    connect(ui->chkEnableSqueak6, SIGNAL(clicked()), this, SLOT(ShowHideOtherSqueakSettings()));

    // Apply css to the volume sliders
    QFile file(":/css/volumeslider.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ui->sliderEngineVolume->setStyleSheet(file.readAll());
        file.seek(0);   // Return to beginning of file
        ui->sliderOverlayVolume->setStyleSheet(file.readAll());
        file.seek(0);   // Return to beginning of file
        ui->sliderEffectsVolume->setStyleSheet(file.readAll());
        file.close();
    }

    // Signals and slots for volume sliders
    connect(ui->sliderEngineVolume, SIGNAL(valueChanged(int)), this, SLOT(UpdateEngineVolumeLabel(int)));
    connect(ui->sliderOverlayVolume, SIGNAL(valueChanged(int)), this, SLOT(UpdateOverlayVolumeLabel(int)));
    connect(ui->sliderEffectsVolume, SIGNAL(valueChanged(int)), this, SLOT(UpdateEffectsVolumeLabel(int)));

}

void MainWindow::UpdateEngineVolumeLabel(int v)
{
    ui->lblEngineVolume->setText(QString("%1%").arg(v));
}

void MainWindow::UpdateOverlayVolumeLabel(int v)
{
    ui->lblOverlayVolume->setText(QString("%1%").arg(v));
}

void MainWindow::UpdateEffectsVolumeLabel(int v)
{
    ui->lblEffectsVolume->setText(QString("%1%").arg(v));
}

void MainWindow::ShowHideSoundCardSettings()
{
    switch (ui->cboSoundDevice->getCurrentSoundDevice())
    {
        case SD_BENEDINI_TBSMINI:
            // Hide volumes
            ui->frmVolume->hide();
            // Remove functions not applicable
            RemoveSoundFunctionsBenedini_Mini();
            // Add those that are
            AddSoundFunctionsBenedini_Mini();
            // Enable 3 squeaks
            ui->frmSqueaks->show();
            ui->frmSqueaks->resize(411,241);
            ShowSqueakHeader();
            EnableSqueaks1_3();
            DisableSqueaks4_6();
            EnableMinSqueakSpeed();
            SqueakSettingsMoveUp();
            // Enable headlight option
            EnableHeadlightSoundSetting();
            // But not Light 2
            DisableHeadlight2SoundSetting();
            // Enable turret sound settings
            EnableTurretSoundSettings();
            break;

        case SD_BENEDINI_TBSMICRO:
            // We remove the volume control and all user sound functions
            RemoveSoundFunctionsBenedini_Micro();
            ui->frmVolume->hide();
            ui->frmSqueaks->hide();
            // Disable and hide all squeak options
            HideSqueakHeader();
            DisableSqueaks1_3();
            DisableSqueaks4_6();
            DisableMinSqueakSpeed();
            // Disable and hide headlight option
            DisableHeadlightSoundSetting();
            DisableHeadlight2SoundSetting();
            // Disable turret sound settings
            DisableTurretSoundSettings();
            break;

        case SD_OP_SOUND_CARD:
            // The only functions we need to remove for this card are the stepwise volume control functions,
            // since we can instead control volume directly
            RemoveVolumeFunctionsStep();
            // But that's it, otherwise make sure all options are available.
            AddSoundFunctionsOP();
            // Show volume
            ui->frmVolume->show();
            // Enable all squeaks
            ui->frmSqueaks->show();
            ui->frmSqueaks->resize(411,331);
            ShowSqueakHeader();
            EnableSqueaks1_3();
            EnableSqueaks4_6();
            EnableMinSqueakSpeed();
            SqueakSettingsMoveDown();
            // Enable all headlight options
            EnableHeadlightSoundSetting();
            EnableHeadlight2SoundSetting();
            // Enable turret sound settings
            EnableTurretSoundSettings();
            break;


        case SD_TAIGEN_SOUND:
            // We remove the volume control and all user sound functions
            RemoveSoundFunctionsTaigen();
            ui->frmVolume->hide();
            ui->frmSqueaks->hide();
            // Disable and hide all squeak options
            HideSqueakHeader();
            DisableSqueaks1_3();
            DisableSqueaks4_6();
            DisableMinSqueakSpeed();
            // Disable and hide headlight options
            DisableHeadlightSoundSetting();
            DisableHeadlight2SoundSetting();
            // Enable turret sound settings
            EnableTurretSoundSettings();
            break;

        // Not yet implemented
        // case SD_BEIER_USMRC2:
            // break;
    }

    // Now depending on what wasn't selected, some RC outputs may become available for general passthrough
    // This function is in mainwindow_tab_motors.cpp
    ValidateRCPassthroughs();

    // Update squeak stuff too
    ShowHideOtherSqueakSettings();
}

void MainWindow::EnableTurretSoundSettings()
{
    // Enable barrel sound option
    ui->chkEnableBarrelSound->setEnabled(true);
    ui->chkEnableBarrelSound->setChecked(DeviceData.BarrelSound_Enabled);
    // Enable turret sound option
    ui->chkEnableTurretSound->setEnabled(true);
    ui->chkEnableTurretSound->setChecked(DeviceData.TurretSound_Enabled);
}
void MainWindow::DisableTurretSoundSettings()
{
    ui->chkEnableBarrelSound->setChecked(false);
    ui->chkEnableBarrelSound->setEnabled(false);

    ui->chkEnableTurretSound->setChecked(false);
    ui->chkEnableTurretSound->setEnabled(false);
}

void MainWindow::EnableHeadlightSoundSetting()
{
    // Enable headlight sound option
    ui->chkEnableHeadlightSound->setEnabled(true);
    ui->chkEnableHeadlightSound->setChecked(DeviceData.HeadlightSound_Enabled);
    // Show
    ui->lblHeadlightSound->show();
    ui->chkEnableHeadlightSound->show();
    ShowHideHeadlightSoundNote(ui->chkEnableHeadlightSound->isChecked());
}
void MainWindow::DisableHeadlightSoundSetting()
{
    ui->chkEnableHeadlightSound->setChecked(false);
    ui->chkEnableHeadlightSound->setEnabled(false);
    // Hide all
    ui->lblHeadlightSound->hide();
    ui->chkEnableHeadlightSound->hide();
    ui->lblHeadlightSoundNote->hide();
}
void MainWindow::ShowHideHeadlightSoundNote(bool isChecked)
{
    if (isChecked) ui->lblHeadlightSoundNote->show();
    else ui->lblHeadlightSoundNote->hide();
}
void MainWindow::EnableHeadlight2SoundSetting()
{
    // Enable headlight 2 sound option
    ui->chkEnableHeadlight2Sound->setEnabled(true);
    ui->chkEnableHeadlight2Sound->setChecked(DeviceData.HeadlightSound2_Enabled);
    // Show
    ui->lblHeadlight2Sound->show();
    ui->chkEnableHeadlight2Sound->show();
    ShowHideHeadlight2SoundNote(ui->chkEnableHeadlight2Sound->isChecked());
}
void MainWindow::DisableHeadlight2SoundSetting()
{
    ui->chkEnableHeadlight2Sound->setChecked(false);
    ui->chkEnableHeadlight2Sound->setEnabled(false);
    // Hide all
    ui->lblHeadlight2Sound->hide();
    ui->chkEnableHeadlight2Sound->hide();
    ui->lblHeadlight2SoundNote->hide();
}
void MainWindow::ShowHideHeadlight2SoundNote(bool isChecked)
{
    if (isChecked) ui->lblHeadlight2SoundNote->show();
    else ui->lblHeadlight2SoundNote->hide();
}

void MainWindow::RemoveVolumeFunctionsStep()
{
    ui->cboSelectFunction->RemoveSF(SF_INCR_VOLUME);
    ui->cboSelectFunction->RemoveSF(SF_DECR_VOLUME);
    ui->cboSelectFunction->RemoveSF(SF_STOP_VOLUME);
    // Make sure we didn't already have a function trigger defined for any of them either
    // Note we use a single | not || because we want the if statement to evaluate all conditions regardless
    if (FT_TableModel->removeFunctionFromList(SF_INCR_VOLUME) |
        FT_TableModel->removeFunctionFromList(SF_DECR_VOLUME)|
        FT_TableModel->removeFunctionFromList(SF_STOP_VOLUME))
            RemovedFunctionTriggersMsgBox();
}

void MainWindow::AddSoundFunctionsOP()
{
    // Remove them all first, then add them, so they show up together
    ui->cboSelectFunction->RemoveSF(SF_SET_VOLUME);
    ui->cboSelectFunction->RemoveSF(SF_OVERLAY_ENABLE);
    ui->cboSelectFunction->RemoveSF(SF_OVERLAY_DISABLE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND1_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND1_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND1_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND2_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND2_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND2_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND3_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND3_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND3_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND4_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND4_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND4_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND5_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND5_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND5_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND6_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND6_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND6_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND7_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND7_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND7_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND8_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND8_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND8_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND9_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND9_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND9_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND10_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND10_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND10_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND11_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND11_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND11_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND12_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND12_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND12_OFF);
    // Add all user sound functions.
    // The add function will only add a function if it isn't there already.
    ui->cboSelectFunction->AddSF(SF_SET_VOLUME);
    ui->cboSelectFunction->AddSF(SF_OVERLAY_ENABLE);
    ui->cboSelectFunction->AddSF(SF_OVERLAY_DISABLE);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND1_ONCE);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND1_RPT);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND1_OFF);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND2_ONCE);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND2_RPT);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND2_OFF);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND3_ONCE);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND3_RPT);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND3_OFF);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND4_ONCE);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND4_RPT);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND4_OFF);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND5_ONCE);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND5_RPT);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND5_OFF);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND6_ONCE);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND6_RPT);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND6_OFF);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND7_ONCE);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND7_RPT);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND7_OFF);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND8_ONCE);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND8_RPT);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND8_OFF);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND9_ONCE);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND9_RPT);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND9_OFF);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND10_ONCE);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND10_RPT);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND10_OFF);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND11_ONCE);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND11_RPT);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND11_OFF);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND12_ONCE);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND12_RPT);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND12_OFF);
}

void MainWindow::RemoveSoundFunctionsTaigen()
{
    // Remove all user sound functions and volume adjustment functions
    ui->cboSelectFunction->RemoveSF(SF_SET_VOLUME);
    ui->cboSelectFunction->RemoveSF(SF_OVERLAY_ENABLE);
    ui->cboSelectFunction->RemoveSF(SF_OVERLAY_DISABLE);
    ui->cboSelectFunction->RemoveSF(SF_INCR_VOLUME);
    ui->cboSelectFunction->RemoveSF(SF_DECR_VOLUME);
    ui->cboSelectFunction->RemoveSF(SF_STOP_VOLUME);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND1_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND1_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND1_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND2_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND2_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND2_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND3_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND3_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND3_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND4_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND4_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND4_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND5_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND5_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND5_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND6_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND6_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND6_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND7_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND7_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND7_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND8_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND8_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND8_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND9_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND9_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND9_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND10_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND10_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND10_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND11_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND11_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND11_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND12_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND12_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND12_OFF);
    // Make sure we didn't already have a function trigger defined for any of them either
    // Note we use a single | not || because we want the if statement to evaluate all conditions regardless
    if (FT_TableModel->removeFunctionFromList(SF_SET_VOLUME)       |
        FT_TableModel->removeFunctionFromList(SF_OVERLAY_ENABLE)   |
        FT_TableModel->removeFunctionFromList(SF_OVERLAY_DISABLE)  |
        FT_TableModel->removeFunctionFromList(SF_INCR_VOLUME)      |
        FT_TableModel->removeFunctionFromList(SF_DECR_VOLUME)      |
        FT_TableModel->removeFunctionFromList(SF_STOP_VOLUME)      |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND1_ONCE) |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND1_RPT)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND1_OFF)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND2_ONCE) |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND2_RPT)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND2_OFF)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND3_ONCE) |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND3_RPT)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND3_OFF)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND4_ONCE) |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND4_RPT)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND4_OFF)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND5_ONCE) |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND5_RPT)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND5_OFF)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND6_ONCE) |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND6_RPT)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND6_OFF)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND7_ONCE) |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND7_RPT)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND7_OFF)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND8_ONCE) |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND8_RPT)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND8_OFF)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND9_ONCE) |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND9_RPT)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND9_OFF)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND10_ONCE)|
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND10_RPT) |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND10_OFF) |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND11_ONCE)|
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND11_RPT) |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND11_OFF) |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND12_ONCE)|
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND12_RPT) |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND12_OFF))
        RemovedFunctionTriggersMsgBox();
}
void MainWindow::RemoveSoundFunctionsBenedini_Micro()
{
    RemoveSoundFunctionsTaigen();
}
void MainWindow::RemoveSoundFunctionsBenedini_Mini()
{
    uint8_t removed = 0;

    // Remove the analog volume adjustment function,
    // and also user sound functions 4-6 if instead those are being used for squeaks
    // and always user sound functions 7+
    ui->cboSelectFunction->RemoveSF(SF_SET_VOLUME);
    ui->cboSelectFunction->RemoveSF(SF_OVERLAY_ENABLE);
    ui->cboSelectFunction->RemoveSF(SF_OVERLAY_DISABLE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND7_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND7_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND7_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND8_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND8_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND8_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND9_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND9_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND9_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND10_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND10_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND10_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND11_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND11_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND11_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND12_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND12_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND12_OFF);
    if (ui->chkEnableSqueak1->isChecked())
    {
        ui->cboSelectFunction->RemoveSF(SF_USER_SOUND4_ONCE);
        ui->cboSelectFunction->RemoveSF(SF_USER_SOUND4_RPT);
        ui->cboSelectFunction->RemoveSF(SF_USER_SOUND4_OFF);
    }
    if (ui->chkEnableSqueak2->isChecked())
    {
        ui->cboSelectFunction->RemoveSF(SF_USER_SOUND5_ONCE);
        ui->cboSelectFunction->RemoveSF(SF_USER_SOUND5_RPT);
        ui->cboSelectFunction->RemoveSF(SF_USER_SOUND5_OFF);
    }
    if (ui->chkEnableSqueak3->isChecked())
    {
        ui->cboSelectFunction->RemoveSF(SF_USER_SOUND6_ONCE);
        ui->cboSelectFunction->RemoveSF(SF_USER_SOUND6_RPT);
        ui->cboSelectFunction->RemoveSF(SF_USER_SOUND6_OFF);
    }
    // Make sure we didn't already have a function trigger defined for any of them either
    // Note we use a single | not || because we want the if statement to evaluate all conditions regardless
    if (FT_TableModel->removeFunctionFromList(SF_SET_VOLUME)) removed += 1;
    if (FT_TableModel->removeFunctionFromList(SF_OVERLAY_ENABLE)) removed += 1;
    if (FT_TableModel->removeFunctionFromList(SF_OVERLAY_DISABLE)) removed += 1;
    if (ui->chkEnableSqueak1->isChecked())
    {
        if (FT_TableModel->removeFunctionFromList(SF_USER_SOUND4_ONCE) |
            FT_TableModel->removeFunctionFromList(SF_USER_SOUND4_RPT)  |
            FT_TableModel->removeFunctionFromList(SF_USER_SOUND4_OFF))
            removed += 1;
    }
    if (ui->chkEnableSqueak2->isChecked())
    {
        if (FT_TableModel->removeFunctionFromList(SF_USER_SOUND5_ONCE) |
            FT_TableModel->removeFunctionFromList(SF_USER_SOUND5_RPT)  |
            FT_TableModel->removeFunctionFromList(SF_USER_SOUND5_OFF))
            removed += 1;
    }
    if (ui->chkEnableSqueak3->isChecked())
    {
        if (FT_TableModel->removeFunctionFromList(SF_USER_SOUND6_ONCE) |
            FT_TableModel->removeFunctionFromList(SF_USER_SOUND6_RPT)  |
            FT_TableModel->removeFunctionFromList(SF_USER_SOUND6_OFF))
            removed += 1;
    }
    if (FT_TableModel->removeFunctionFromList(SF_USER_SOUND7_ONCE) |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND7_RPT)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND7_OFF)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND8_ONCE) |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND8_RPT)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND8_OFF)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND9_ONCE) |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND9_RPT)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND9_OFF)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND10_ONCE)|
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND10_RPT) |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND10_OFF) |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND11_ONCE)|
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND11_RPT) |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND11_OFF) |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND12_ONCE)|
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND12_RPT) |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND12_OFF))
        removed += 1;

    if (removed > 0) RemovedFunctionTriggersMsgBox();
}
void MainWindow::AddSoundFunctionsBenedini_Mini()
{
    ui->cboSelectFunction->RemoveSF(SF_INCR_VOLUME);
    ui->cboSelectFunction->RemoveSF(SF_DECR_VOLUME);
    ui->cboSelectFunction->RemoveSF(SF_STOP_VOLUME);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND1_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND1_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND1_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND2_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND2_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND2_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND3_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND3_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND3_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND4_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND4_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND4_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND5_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND5_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND5_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND6_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND6_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND6_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND7_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND7_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND7_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND8_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND8_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND8_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND9_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND9_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND9_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND10_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND10_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND10_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND11_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND11_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND11_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND12_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND12_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND12_OFF);
    // Add all user sound functions.
    // The add function will only add a function if it isn't there already.
    ui->cboSelectFunction->AddSF(SF_INCR_VOLUME);
    ui->cboSelectFunction->AddSF(SF_DECR_VOLUME);
    ui->cboSelectFunction->AddSF(SF_STOP_VOLUME);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND1_ONCE);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND1_RPT);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND1_OFF);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND2_ONCE);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND2_RPT);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND2_OFF);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND3_ONCE);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND3_RPT);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND3_OFF);
    if (!ui->chkEnableSqueak1->isChecked())
    {
        ui->cboSelectFunction->AddSF(SF_USER_SOUND4_ONCE);
        ui->cboSelectFunction->AddSF(SF_USER_SOUND4_RPT);
        ui->cboSelectFunction->AddSF(SF_USER_SOUND4_OFF);
    }
    if (!ui->chkEnableSqueak2->isChecked())
    {
        ui->cboSelectFunction->AddSF(SF_USER_SOUND5_ONCE);
        ui->cboSelectFunction->AddSF(SF_USER_SOUND5_RPT);
        ui->cboSelectFunction->AddSF(SF_USER_SOUND5_OFF);
    }
    if (!ui->chkEnableSqueak3->isChecked())
    {
        ui->cboSelectFunction->AddSF(SF_USER_SOUND6_ONCE);
        ui->cboSelectFunction->AddSF(SF_USER_SOUND6_RPT);
        ui->cboSelectFunction->AddSF(SF_USER_SOUND6_OFF);
    }
}
void MainWindow::UpdateSoundFunctionsBenedini()
{
    // If we are using the Benedini sound card the presence of users sound functions 5-6
    // will depend on whether the user has enabled squeaks 1-3 or not
    if (ui->cboSoundDevice->getCurrentSoundDevice() == SD_BENEDINI_TBSMINI)
    {
        RemoveSoundFunctionsBenedini_Mini(); // This removes any user functions if they are reserved for squeaks instead
        AddSoundFunctionsBenedini_Mini();    // This makes sure all appropriate Benedini functions are added in order
    }

}

void MainWindow::EnableSqueaks1_3()
{
    // Enable Squeaks 1 - 3
    ui->spinSqueak1Min->setEnabled(true);
    ui->spinSqueak1Max->setEnabled(true);
    ui->spinSqueak2Min->setEnabled(true);
    ui->spinSqueak2Max->setEnabled(true);
    ui->spinSqueak3Min->setEnabled(true);
    ui->spinSqueak3Max->setEnabled(true);
    ui->chkEnableSqueak1->setEnabled(true);
    ui->chkEnableSqueak2->setEnabled(true);
    ui->chkEnableSqueak3->setEnabled(true);
    // And set them to the saved values
    ui->chkEnableSqueak1->setChecked(DeviceData.Squeak1_Enabled);
    ui->spinSqueak1Min->setValue(DeviceData.Squeak1_MinInterval_mS);
    ui->spinSqueak1Max->setValue(DeviceData.Squeak1_MaxInterval_mS);
    ui->chkEnableSqueak2->setChecked(DeviceData.Squeak2_Enabled);
    ui->spinSqueak2Min->setValue(DeviceData.Squeak2_MinInterval_mS);
    ui->spinSqueak2Max->setValue(DeviceData.Squeak2_MaxInterval_mS);
    ui->chkEnableSqueak3->setChecked(DeviceData.Squeak3_Enabled);
    ui->spinSqueak3Min->setValue(DeviceData.Squeak3_MinInterval_mS);
    ui->spinSqueak3Max->setValue(DeviceData.Squeak3_MaxInterval_mS);
    ShowHideSqueak1Settings(ui->chkEnableSqueak1->isChecked());
    ShowHideSqueak2Settings(ui->chkEnableSqueak2->isChecked());
    ShowHideSqueak3Settings(ui->chkEnableSqueak3->isChecked());
    // Now show them
    ui->lblSqueak1->show();
    ui->lblSqueak2->show();
    ui->lblSqueak3->show();
    ui->chkEnableSqueak1->show();
    ui->chkEnableSqueak2->show();
    ui->chkEnableSqueak3->show();
    ui->spinSqueak1Min->show();
    ui->spinSqueak1Max->show();
    ui->spinSqueak2Min->show();
    ui->spinSqueak2Max->show();
    ui->spinSqueak3Min->show();
    ui->spinSqueak3Max->show();
    // If we are showing squeaks 1-3 we also will need the squeak settings
    ui->lblMinSqueakSpeed1->show();
    ui->lblMinSqueakSpeed2->show();
    ui->spinMinSqueakSpeed->show();
}
void MainWindow::EnableSqueaks4_6()
{
    // Enable Squeaks 4 - 6
    ui->spinSqueak4Min->setEnabled(true);
    ui->spinSqueak4Max->setEnabled(true);
    ui->spinSqueak5Min->setEnabled(true);
    ui->spinSqueak5Max->setEnabled(true);
    ui->spinSqueak6Min->setEnabled(true);
    ui->spinSqueak6Max->setEnabled(true);
    ui->chkEnableSqueak4->setEnabled(true);
    ui->chkEnableSqueak5->setEnabled(true);
    ui->chkEnableSqueak6->setEnabled(true);
    // And set them to the saved values
    ui->chkEnableSqueak4->setChecked(DeviceData.Squeak4_Enabled);
    ui->spinSqueak4Min->setValue(DeviceData.Squeak4_MinInterval_mS);
    ui->spinSqueak4Max->setValue(DeviceData.Squeak4_MaxInterval_mS);
    ui->chkEnableSqueak5->setChecked(DeviceData.Squeak5_Enabled);
    ui->spinSqueak5Min->setValue(DeviceData.Squeak5_MinInterval_mS);
    ui->spinSqueak5Max->setValue(DeviceData.Squeak5_MaxInterval_mS);
    ui->chkEnableSqueak6->setChecked(DeviceData.Squeak6_Enabled);
    ui->spinSqueak6Min->setValue(DeviceData.Squeak6_MinInterval_mS);
    ui->spinSqueak6Max->setValue(DeviceData.Squeak6_MaxInterval_mS);
    ShowHideSqueak4Settings(ui->chkEnableSqueak4->isChecked());
    ShowHideSqueak5Settings(ui->chkEnableSqueak5->isChecked());
    ShowHideSqueak6Settings(ui->chkEnableSqueak6->isChecked());
    // Now show them
    ui->lblSqueak4->show();
    ui->lblSqueak5->show();
    ui->lblSqueak6->show();
    ui->chkEnableSqueak4->show();
    ui->chkEnableSqueak5->show();
    ui->chkEnableSqueak6->show();
    ui->spinSqueak4Min->show();
    ui->spinSqueak4Max->show();
    ui->spinSqueak5Min->show();
    ui->spinSqueak5Max->show();
    ui->spinSqueak6Min->show();
    ui->spinSqueak6Max->show();
}

void MainWindow::DisableSqueaks1_3()
{
    ui->spinSqueak1Min->setValue(DeviceData.Squeak1_MinInterval_mS);    // Set the values to default
    ui->spinSqueak1Max->setValue(DeviceData.Squeak1_MaxInterval_mS);
    ui->spinSqueak2Min->setValue(DeviceData.Squeak2_MinInterval_mS);
    ui->spinSqueak2Max->setValue(DeviceData.Squeak2_MaxInterval_mS);
    ui->spinSqueak3Min->setValue(DeviceData.Squeak3_MinInterval_mS);
    ui->spinSqueak3Max->setValue(DeviceData.Squeak3_MaxInterval_mS);
    ui->spinSqueak1Min->setEnabled(false);                              // Now disable
    ui->spinSqueak1Max->setEnabled(false);
    ui->spinSqueak2Min->setEnabled(false);
    ui->spinSqueak2Max->setEnabled(false);
    ui->spinSqueak3Min->setEnabled(false);
    ui->spinSqueak3Max->setEnabled(false);
    // Uncheck these squeaks
    ui->chkEnableSqueak1->setChecked(false);                            // Uncheck all selections
    ui->chkEnableSqueak2->setChecked(false);
    ui->chkEnableSqueak3->setChecked(false);
    // Now disable them
    ui->chkEnableSqueak1->setEnabled(false);                            // Now disable
    ui->chkEnableSqueak2->setEnabled(false);
    ui->chkEnableSqueak3->setEnabled(false);
    // Now hide them
    ui->lblSqueak1->hide();
    ui->lblSqueak2->hide();
    ui->lblSqueak3->hide();
    ui->chkEnableSqueak1->hide();
    ui->chkEnableSqueak2->hide();
    ui->chkEnableSqueak3->hide();
    ui->spinSqueak1Min->hide();
    ui->spinSqueak1Max->hide();
    ui->spinSqueak2Min->hide();
    ui->spinSqueak2Max->hide();
    ui->spinSqueak3Min->hide();
    ui->spinSqueak3Max->hide();
    // If we are getting rid of squeaks 1-3 we also don't need the squeak settings
    ui->lblMinSqueakSpeed1->hide();
    ui->lblMinSqueakSpeed2->hide();
    ui->spinMinSqueakSpeed->hide();
}
void MainWindow::DisableSqueaks4_6()
{
    ui->spinSqueak4Min->setValue(DeviceData.Squeak4_MinInterval_mS);    // Set the values to default
    ui->spinSqueak4Max->setValue(DeviceData.Squeak4_MaxInterval_mS);
    ui->spinSqueak5Min->setValue(DeviceData.Squeak5_MinInterval_mS);
    ui->spinSqueak5Max->setValue(DeviceData.Squeak5_MaxInterval_mS);
    ui->spinSqueak6Min->setValue(DeviceData.Squeak6_MinInterval_mS);
    ui->spinSqueak6Max->setValue(DeviceData.Squeak6_MaxInterval_mS);
    ui->spinSqueak4Min->setEnabled(false);                              // Now disable
    ui->spinSqueak4Max->setEnabled(false);
    ui->spinSqueak5Min->setEnabled(false);
    ui->spinSqueak5Max->setEnabled(false);
    ui->spinSqueak6Min->setEnabled(false);
    ui->spinSqueak6Max->setEnabled(false);
    // Uncheck these squeaks
    ui->chkEnableSqueak4->setChecked(false);                            // Uncheck all selections
    ui->chkEnableSqueak5->setChecked(false);
    ui->chkEnableSqueak6->setChecked(false);
    // Now disable them
    ui->chkEnableSqueak4->setEnabled(false);                            // Now disable
    ui->chkEnableSqueak5->setEnabled(false);
    ui->chkEnableSqueak6->setEnabled(false);
    // Now hide them
    ui->lblSqueak4->hide();
    ui->lblSqueak5->hide();
    ui->lblSqueak6->hide();
    ui->chkEnableSqueak4->hide();
    ui->chkEnableSqueak5->hide();
    ui->chkEnableSqueak6->hide();
    ui->spinSqueak4Min->hide();
    ui->spinSqueak4Max->hide();
    ui->spinSqueak5Min->hide();
    ui->spinSqueak5Max->hide();
    ui->spinSqueak6Min->hide();
    ui->spinSqueak6Max->hide();
}

void MainWindow::EnableMinSqueakSpeed()
{
    ui->spinMinSqueakSpeed->setEnabled(true);
    ui->spinMinSqueakSpeed->setValue(DeviceData.MinSqueakSpeedPct);
}
void MainWindow::DisableMinSqueakSpeed()
{
    ui->spinMinSqueakSpeed->setValue(DeviceData.MinSqueakSpeedPct);
    ui->spinMinSqueakSpeed->setEnabled(false);
}

void MainWindow::SqueakSettingsMoveUp(void)
{   // We want the squeak settings to show up below the last visible individual squeak settings,
    // so we index the top of the controls to that one
    int newTop = ui->chkEnableSqueak3->y()+28;
    ui->lblMinSqueakSpeed1->move(ui->lblMinSqueakSpeed1->x(), newTop);
    ui->lblMinSqueakSpeed2->move(ui->lblMinSqueakSpeed2->x(), newTop);
    ui->spinMinSqueakSpeed->move(ui->spinMinSqueakSpeed->x(), newTop);
}
void MainWindow::SqueakSettingsMoveDown(void)
{   // We want the squeak settings to show up below the last visible individual squeak settings,
    // so we index the top of the controls to that one
    int newTop = ui->chkEnableSqueak6->y()+28;
    ui->lblMinSqueakSpeed1->move(ui->lblMinSqueakSpeed1->x(), newTop);
    ui->lblMinSqueakSpeed2->move(ui->lblMinSqueakSpeed2->x(), newTop);
    ui->spinMinSqueakSpeed->move(ui->spinMinSqueakSpeed->x(), newTop);
}

void MainWindow::HideSqueakHeader(void)
{
//    ui->lblSqueakHeader1->hide();
    ui->lblSqueakHeader2->hide();
    ui->lblSqueakHeader3->hide();
    ui->lblSqueakHeader4->hide();
    ui->lblSqueakHeader5->hide();
    ui->frmSqueakHeader1->hide();
    ui->frmSqueakHeader2->hide();
}
void MainWindow::ShowSqueakHeader(void)
{
//    ui->lblSqueakHeader1->show();
    ui->lblSqueakHeader2->show();
    ui->lblSqueakHeader3->show();
    ui->lblSqueakHeader4->show();
    ui->lblSqueakHeader5->show();
    ui->frmSqueakHeader1->show();
    ui->frmSqueakHeader2->show();
}

void MainWindow::ShowHideSqueak1Settings(bool isChecked)
{
    if (isChecked)
    {
        ui->spinSqueak1Min->setEnabled(true);
        ui->spinSqueak1Max->setEnabled(true);
    }
    else
    {
        ui->spinSqueak1Min->setEnabled(false);
        ui->spinSqueak1Max->setEnabled(false);
    }

    // In the case of the Benedini card only, if this squeak is enabled it takes
    // the place of a user sound, but if disabled we add the user sound option
    if (ui->cboSoundDevice->getCurrentSoundDevice() == SD_BENEDINI_TBSMINI)
        UpdateSoundFunctionsBenedini();
}
void MainWindow::ShowHideSqueak2Settings(bool isChecked)
{
    if (isChecked)
    {
        ui->spinSqueak2Min->setEnabled(true);
        ui->spinSqueak2Max->setEnabled(true);
    }
    else
    {
        ui->spinSqueak2Min->setEnabled(false);
        ui->spinSqueak2Max->setEnabled(false);
    }

    // In the case of the Benedini card only, if this squeak is enabled it takes
    // the place of a user sound, but if disabled we add the user sound option
    if (ui->cboSoundDevice->getCurrentSoundDevice() == SD_BENEDINI_TBSMINI)
        UpdateSoundFunctionsBenedini();
}
void MainWindow::ShowHideSqueak3Settings(bool isChecked)
{
    if (isChecked)
    {
        ui->spinSqueak3Min->setEnabled(true);
        ui->spinSqueak3Max->setEnabled(true);
    }
    else
    {
        ui->spinSqueak3Min->setEnabled(false);
        ui->spinSqueak3Max->setEnabled(false);
    }

    // In the case of the Benedini card only, if this squeak is enabled it takes
    // the place of a user sound, but if disabled we add the user sound option
    if (ui->cboSoundDevice->getCurrentSoundDevice() == SD_BENEDINI_TBSMINI)
        UpdateSoundFunctionsBenedini();
}
void MainWindow::ShowHideSqueak4Settings(bool isChecked)
{
    if (isChecked)
    {
        ui->spinSqueak4Min->setEnabled(true);
        ui->spinSqueak4Max->setEnabled(true);
    }
    else
    {
        ui->spinSqueak4Min->setEnabled(false);
        ui->spinSqueak4Max->setEnabled(false);
    }
}
void MainWindow::ShowHideSqueak5Settings(bool isChecked)
{
    if (isChecked)
    {
        ui->spinSqueak5Min->setEnabled(true);
        ui->spinSqueak5Max->setEnabled(true);
    }
    else
    {
        ui->spinSqueak5Min->setEnabled(false);
        ui->spinSqueak5Max->setEnabled(false);
    }
}
void MainWindow::ShowHideSqueak6Settings(bool isChecked)
{
    if (isChecked)
    {
        ui->spinSqueak6Min->setEnabled(true);
        ui->spinSqueak6Max->setEnabled(true);
    }
    else
    {
        ui->spinSqueak6Min->setEnabled(false);
        ui->spinSqueak6Max->setEnabled(false);
    }
}
void MainWindow::ShowHideOtherSqueakSettings(void)
{
    // If any squeak is enabled, enable general squeak settings
    if (ui->chkEnableSqueak1->isChecked() ||
            ui->chkEnableSqueak2->isChecked() ||
            ui->chkEnableSqueak3->isChecked() ||
            ui->chkEnableSqueak4->isChecked() ||
            ui->chkEnableSqueak5->isChecked() ||
            ui->chkEnableSqueak6->isChecked() )
    {
        ui->lblMinSqueakSpeed1->setEnabled(true);
        ui->lblMinSqueakSpeed2->setEnabled(true);
        ui->spinMinSqueakSpeed->setEnabled(true);
        ui->spinMinSqueakSpeed->setValue(DeviceData.MinSqueakSpeedPct);
    }
    else
    {
        // If all squeaks are disabled, disable general squeak settings
        ui->lblMinSqueakSpeed1->setEnabled(false);
        ui->lblMinSqueakSpeed2->setEnabled(false);
        ui->spinMinSqueakSpeed->setValue(DeviceData.MinSqueakSpeedPct);
        ui->spinMinSqueakSpeed->setEnabled(false);
    }
}



