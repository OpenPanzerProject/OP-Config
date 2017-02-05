#include "mainwindow.h"
#include "ui_mainwindow.h"


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
}
void MainWindow::ShowHideSoundCardSettings()
{
    switch (ui->cboSoundDevice->getCurrentSoundDevice())
    {
        case SD_BENEDINI_TBSMINI:
            // REMOVE
            // Remove the volume control function and user sounds 3 & 4 functions, they are not compatible.
            RemoveVolumeUserSoundFunctions3_4();
            // Remove squeaks 4-6
            DisableSqueaks4_6();
            // Remove barrel sound option
            DisableBarrelSoundSetting();
            // ENABLE
            // Enable squeaks 1-3
            EnableSqueaks1_3();
            EnableMinSqueakSpeed();
            // Enable Headlight sound option
            EnableHeadlightSoundSetting();
            break;


        case SD_OP_SOUND_CARD:
            // Add volume control functions and all user sound functions.
            // The add function will only add it if it isn't there already.
            AddVolumeFunction();
            AddUserSoundFunctions1_4();

            // Enable everything
            EnableSqueaks1_3();
            EnableSqueaks4_6();
            EnableMinSqueakSpeed();
            EnableBarrelSoundSetting();
            EnableHeadlightSoundSetting();
            break;


        case SD_TAIGEN_SOUND:
            // We remove the volume control and all user sound functions
            RemoveVolumeUserSoundFunctions1_4();

            // Disable all squeaks and the headlight options
            DisableSqueaks1_3();
            DisableSqueaks4_6();
            DisableMinSqueakSpeed();
            DisableHeadlightSoundSetting();

            // But we do enable barrel sound option
            EnableBarrelSoundSetting();
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

void MainWindow::EnableBarrelSoundSetting()
{
    // Enable barrel sound option
    ui->chkEnableBarrelSound->setEnabled(true);
    ui->chkEnableBarrelSound->setChecked(DeviceData.BarrelSound_Enabled);
}

void MainWindow::DisableBarrelSoundSetting()
{
    ui->chkEnableBarrelSound->setChecked(false);
    ui->chkEnableBarrelSound->setEnabled(false);
}

void MainWindow::EnableHeadlightSoundSetting()
{
    // Enable headlight sound option
    ui->chkEnableHeadlightSound->setEnabled(true);
    ui->chkEnableHeadlightSound->setChecked(DeviceData.HeadlightSound_Enabled);
    ShowHideHeadlightSoundNote(ui->chkEnableHeadlightSound->isChecked());
}

void MainWindow::DisableHeadlightSoundSetting()
{
    ui->chkEnableHeadlightSound->setChecked(false);
    ui->chkEnableHeadlightSound->setEnabled(false);
    ui->lblHeadlightSound->hide();
}

void MainWindow::AddVolumeFunction()
{
    // Add volume control function
    // The add function will only add a function if it isn't there already.
    ui->cboSelectFunction->AddSF(SF_SET_VOLUME);
}

void MainWindow::AddUserSoundFunctions1_4()
{
    // Add all user sound functions.
    // The add function will only add a function if it isn't there already.
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
}

void MainWindow::AddUserSoundFunctions1_2()
{
    // Add user sound functions 1 & 2
    // The add function will only add a function if it isn't there already.
    ui->cboSelectFunction->AddSF(SF_USER_SOUND1_ONCE);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND1_RPT);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND1_OFF);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND2_ONCE);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND2_RPT);
    ui->cboSelectFunction->AddSF(SF_USER_SOUND2_OFF);
}

void MainWindow::RemoveVolumeUserSoundFunctions1_4()
{
    // We remove the volume control and all user sound functions
    ui->cboSelectFunction->RemoveSF(SF_SET_VOLUME);
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
    // Make sure we didn't already have a function trigger defined for any of them either
    // Note we use a single | not || because we want the if statement to evaluate all conditions regardless
    if (FT_TableModel->removeFunctionFromList(SF_SET_VOLUME)       |
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
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND4_OFF))
        RemovedFunctionTriggersMsgBox();
}

void MainWindow::RemoveVolumeUserSoundFunctions3_4()
{
    // We remove the volume control and all user sound functions
    ui->cboSelectFunction->RemoveSF(SF_SET_VOLUME);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND3_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND3_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND3_OFF);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND4_ONCE);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND4_RPT);
    ui->cboSelectFunction->RemoveSF(SF_USER_SOUND4_OFF);
    // Make sure we didn't already have a function trigger defined for any of them either
    // Note we use a single | not || because we want the if statement to evaluate all conditions regardless
    if (FT_TableModel->removeFunctionFromList(SF_SET_VOLUME)       |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND3_ONCE) |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND3_RPT)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND3_OFF)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND4_ONCE) |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND4_RPT)  |
        FT_TableModel->removeFunctionFromList(SF_USER_SOUND4_OFF))
        RemovedFunctionTriggersMsgBox();
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

void MainWindow::ShowHideHeadlightSoundNote(bool isChecked)
{
    if (isChecked) ui->lblHeadlightSound->show();
    else ui->lblHeadlightSound->hide();
}
