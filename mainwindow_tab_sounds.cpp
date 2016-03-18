#include "mainwindow.h"
#include "ui_mainwindow.h"


//------------------------------------------------------------------------------------------------------------------------>>
// FORM CONTROLS - SOUND TAB
//------------------------------------------------------------------------------------------------------------------------>>
void MainWindow::SetupControls_SoundTab(void)
{
    // Here we would connect a stacked widget with (future) card-dependent settings to the sound-device select combo box
    // connect(ui->cboSoundDevice, SIGNAL(currentSoundDeviceChanged(int)), ui->stackedWidgetSoundCards, SLOT(setCurrentIndex(int)));
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
    // Also, if we disable all three squeaks, no need to show the min-squeak speed or any other generic squeak settings
    connect(ui->chkEnableSqueak1, SIGNAL(clicked(bool)), this, SLOT(ShowHideOtherSqueakSettings(bool)));
    connect(ui->chkEnableSqueak2, SIGNAL(clicked(bool)), this, SLOT(ShowHideOtherSqueakSettings(bool)));
    connect(ui->chkEnableSqueak3, SIGNAL(clicked(bool)), this, SLOT(ShowHideOtherSqueakSettings(bool)));
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
