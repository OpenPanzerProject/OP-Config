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
    connect(ui->chkEnableSqueak1, SIGNAL(clicked(bool)), this, SLOT(ShowHideOtherSqueakSettings(bool)));
    connect(ui->chkEnableSqueak2, SIGNAL(clicked(bool)), this, SLOT(ShowHideOtherSqueakSettings(bool)));
    connect(ui->chkEnableSqueak3, SIGNAL(clicked(bool)), this, SLOT(ShowHideOtherSqueakSettings(bool)));
    connect(ui->chkEnableSqueak4, SIGNAL(clicked(bool)), this, SLOT(ShowHideOtherSqueakSettings(bool)));
    connect(ui->chkEnableSqueak5, SIGNAL(clicked(bool)), this, SLOT(ShowHideOtherSqueakSettings(bool)));
    connect(ui->chkEnableSqueak6, SIGNAL(clicked(bool)), this, SLOT(ShowHideOtherSqueakSettings(bool)));
}
void MainWindow::ShowHideSoundCardSettings()
{
    switch (ui->cboSoundDevice->getCurrentSoundDevice())
    {
        case SD_BENEDINI_TBSMINI:
            // We remove the volume control function and user sounds 3 & 4 functions, they are not compatible.
            ui->cboSelectFunction->RemoveSF(SF_SET_VOLUME);
            ui->cboSelectFunction->RemoveSF(SF_USER_SOUND3_ONCE);
            ui->cboSelectFunction->RemoveSF(SF_USER_SOUND3_RPT);
            ui->cboSelectFunction->RemoveSF(SF_USER_SOUND3_OFF);
            ui->cboSelectFunction->RemoveSF(SF_USER_SOUND4_ONCE);
            ui->cboSelectFunction->RemoveSF(SF_USER_SOUND4_RPT);
            ui->cboSelectFunction->RemoveSF(SF_USER_SOUND4_OFF);
            // Make sure we didn't already have a function trigger defined for any of them either
            if (FT_TableModel->removeFunctionFromList(SF_SET_VOLUME) ||
                FT_TableModel->removeFunctionFromList(SF_USER_SOUND3_ONCE) ||
                FT_TableModel->removeFunctionFromList(SF_USER_SOUND3_RPT) ||
                FT_TableModel->removeFunctionFromList(SF_USER_SOUND3_OFF) ||
                FT_TableModel->removeFunctionFromList(SF_USER_SOUND4_ONCE) ||
                FT_TableModel->removeFunctionFromList(SF_USER_SOUND4_RPT) ||
                FT_TableModel->removeFunctionFromList(SF_USER_SOUND4_OFF))
                RemovedFunctionTriggersMsgBox();
            // We also disable squeaks 4-6
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
            // And the barrel sound option
            ui->chkEnableBarrelSound->setChecked(false);
            ui->chkEnableBarrelSound->setEnabled(false);
            break;

        case SD_OP_SOUND_CARD:
            // Add volume control functions and user sounds 3 & 4 functions, these are available
            // The add function will only add it if it isn't there already
            ui->cboSelectFunction->AddSF(SF_SET_VOLUME);
            ui->cboSelectFunction->AddSF(SF_USER_SOUND3_ONCE);
            ui->cboSelectFunction->AddSF(SF_USER_SOUND3_RPT);
            ui->cboSelectFunction->AddSF(SF_USER_SOUND3_OFF);
            ui->cboSelectFunction->AddSF(SF_USER_SOUND4_ONCE);
            ui->cboSelectFunction->AddSF(SF_USER_SOUND4_RPT);
            ui->cboSelectFunction->AddSF(SF_USER_SOUND4_OFF);

            // We also enable squeaks 4-6
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

            // Enable barrel sound option as well
            ui->chkEnableBarrelSound->setEnabled(true);
            ui->chkEnableBarrelSound->setChecked(DeviceData.BarrelSound_Enabled);

            break;


        // Not yet implemented
        // case SD_BEIER_USMRC2:
            // break;
    }
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
void MainWindow::ShowHideOtherSqueakSettings(bool)
{
    // If all three squeaks are disabled, disable general squeak settings
    if (ui->chkEnableSqueak1->isChecked() || ui->chkEnableSqueak2->isChecked() || ui->chkEnableSqueak3->isChecked())
    {
        ui->lblMinSqueakSpeed1->setEnabled(true);
        ui->lblMinSqueakSpeed2->setEnabled(true);
        ui->spinMinSqueakSpeed->setEnabled(true);
        ui->spinMinSqueakSpeed->setValue(DeviceData.MinSqueakSpeedPct);
    }
    else
    {
        ui->lblMinSqueakSpeed1->setEnabled(false);
        ui->lblMinSqueakSpeed2->setEnabled(false);
        ui->spinMinSqueakSpeed->setEnabled(false);
    }
}

void MainWindow::ShowHideHeadlightSoundNote(bool isChecked)
{
    if (isChecked) ui->lblHeadlightSound->show();
    else ui->lblHeadlightSound->hide();
}
