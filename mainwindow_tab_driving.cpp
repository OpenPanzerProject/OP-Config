#include "mainwindow.h"
#include "ui_mainwindow.h"


//------------------------------------------------------------------------------------------------------------------------>>
// FORM CONTROLS - DRIVING TAB
//------------------------------------------------------------------------------------------------------------------------>>
void MainWindow::SetupControls_DrivingTab(void)
{
    QString display;
    QString level;

    // Setup accel/decel preset combos
    ui->cboAccelPreset->setCategory(ptAccel);
    ui->cboDecelPreset->setCategory(ptDecel);

    // Setup accel/decel level combos
    // We wil be using the index number to reference the level, so we don't need user data,
    // and we can put whatever we want for the display text
    for (int i = 0; i < MAX_SKIP_NUM; i++)
    {
        display = QString::number(i+1);
        display.append("   (~");
        level.setNum(((i+1)*0.5),'f',1);
        display.append(level);
        display.append(" sec)");
        ui->cboAccelLevel->insertItem(i, display);
        ui->cboDecelLevel->insertItem(i, display);
    }

    // Turn Modes
    for (int i = 0; i < NUM_TURN_MODES; i++)
    {
        ui->cboTurnMode->insertItem(i, QString::number(i+1));
    }

    // Connect Signals and Slots
    // If we disable neutral turns, no need to allow a neutral turn percent speed
    connect(ui->chkNeutralTurn, SIGNAL(clicked(bool)), this, SLOT(ShowHideNeutralTurnPct(bool)));
    // If we disable accel/decel, disable some other options as well
    connect(ui->chkAccelEnable, SIGNAL(clicked(bool)), this, SLOT(ShowHideAccelOptions(bool)));
    connect(ui->chkDecelEnable, SIGNAL(clicked(bool)), this, SLOT(ShowHideDecelOptions(bool)));
    // If we disable barrel stabilization or hill physics, disable the sensitivity options as well
    connect(ui->chkEnableBarrel, SIGNAL(clicked(bool)), this, SLOT(ShowHideBarrelSensitivity(bool)));
    connect(ui->chkEnableHills, SIGNAL(clicked(bool)), this, SLOT(ShowHideHillSensitivity(bool)));
    // If we disable the nudge feature (by setting nudge percent to zero), disable the nudge time
    connect(ui->spinNudgePercent, SIGNAL(valueChanged(int)), this, SLOT(ShowHideNudgeTime(int)));

    // FOR NOW WE ARE HIDING THE IMU SETTINGS BECAUSE THE FUNCTIONALITY IS NOT COMPLETE ON THE TCB
    // However, the code here is done and the settings are saved/recorded to TCB if we just unhide
    // this frame, and add back the IMU-specific functions that are commented out in getopqmaps.cpp
    ui->frmIMU->hide();
}
void MainWindow::ShowHideNudgeTime(int nudgePct)
{
    if (nudgePct > 0)
    {
        ui->lblNudgeTime1->setEnabled(true);
        ui->lblNudgeTime2->setEnabled(true);
        ui->spinNudgeTime->setEnabled(true);
        DeviceData.NudgeTime_mS = ui->spinNudgeTime->value();
    }
    else
    {
        ui->lblNudgeTime1->setEnabled(false);
        ui->lblNudgeTime2->setEnabled(false);
        ui->spinNudgeTime->setEnabled(false);
    }
}

void MainWindow::ShowHideNeutralTurnAllowed(int)
{
    if (ui->cboDriveType->currentData() == DT_TANK)
    {
        // Enable the turn mode option
        ui->lblTurnMode->setEnabled(true);
        ui->cboTurnMode->setEnabled(true);

        // Enable the option for enabling/disabling neutral turns
        if (!ui->chkNeutralTurn->isEnabled())
        {
            ui->lblNeutralTurnAllowed->setEnabled(true);
            ui->lblMaxNeutralTurn->setEnabled(true);
            ui->chkNeutralTurn->setEnabled(true);
            ui->chkNeutralTurn->setChecked(DeviceData.NeutralTurnAllowed);
            ShowHideNeutralTurnPct(DeviceData.NeutralTurnAllowed);
        }
        // Hide these labels
        ui->lblNoTurnSettingsForCars->hide();
        ui->lblNoTurnSettingsForHalftracks->hide();
    }
    else
    {
        // This is not a tank, so disable all the neutral turn options
        ui->lblNeutralTurnAllowed->setEnabled(false);
        ui->lblMaxNeutralTurn->setEnabled(false);
        DeviceData.NeutralTurnAllowed = false;
        ui->chkNeutralTurn->setChecked(false);
        ui->chkNeutralTurn->setEnabled(false);
        ShowHideNeutralTurnPct(DeviceData.NeutralTurnAllowed);

        // Also, if this is a single rear-drive vehicle, disable the Turn Mode option as well
        if (ui->cboDriveType->currentData() == DT_CAR)
        {
            ui->lblTurnMode->setEnabled(false);
            ui->cboTurnMode->setEnabled(false);
            // And show a helpful note
            ui->lblNoTurnSettingsForCars->show();
            ui->lblNoTurnSettingsForHalftracks->hide();
        }
        else
        {
            ui->lblTurnMode->setEnabled(true);
            ui->cboTurnMode->setEnabled(true);
            ui->lblNoTurnSettingsForCars->hide();
            ui->lblNoTurnSettingsForHalftracks->show();
        }
    }
}
void MainWindow::ShowHideNeutralTurnPct(bool checked)
{   // If neutral turns are allowed, enable the spin box to set the neutral turn max speed.
    // Otherwise, disable the spin box.
    if (checked)
    {
        ui->lblMaxNeutralTurn->setEnabled(true);
        ui->spinNeutralTurnSpeed->setEnabled(true);
        ui->spinNeutralTurnSpeed->setValue(DeviceData.NeutralTurnPct);
    }
    else
    {
        ui->lblMaxNeutralTurn->setEnabled(false);
        DeviceData.NeutralTurnPct = 50;             // Reset to default amount, though it won't matter
        ui->spinNeutralTurnSpeed->setValue(DeviceData.NeutralTurnPct);
        ui->spinNeutralTurnSpeed->setEnabled(false);
    }
}
void MainWindow::ShowHideHalftrackTurn(int)
{
    if (ui->cboDriveType->currentData() == DT_HALFTRACK)
    {
        ui->lblHalftrackTurnPercent->setEnabled(true);
        ui->spinHalftrackTurnPct->setEnabled(true);
        ui->spinHalftrackTurnPct->setValue(DeviceData.HalftrackTreadTurnPct);
    }
    else
    {
        ui->lblHalftrackTurnPercent->setEnabled(false);
        DeviceData.HalftrackTreadTurnPct = 50;      // Reset to default amount, though it won't matter
        ui->spinHalftrackTurnPct->setValue(DeviceData.HalftrackTreadTurnPct);
        ui->spinHalftrackTurnPct->setEnabled(false);
    }
}
void MainWindow::ShowHideAccelOptions(bool isChecked)
{
    if (isChecked)
    {   // Show options
        ui->lblAccelPreset->setEnabled(true);
        ui->cboAccelPreset->setEnabled(true);
        ui->lblAccelLevel->setEnabled(true);
        ui->cboAccelLevel->setEnabled(true);
    }
    else
    {   // Hide options
        ui->lblAccelPreset->setEnabled(false);
        ui->cboAccelPreset->setCurrentIndex(ui->cboAccelPreset->findData(ADP_NONE));
        ui->cboAccelPreset->setEnabled(false);
        ui->lblAccelLevel->setEnabled(false);
        ui->cboAccelLevel->setCurrentIndex(3);  // This will put it on item 4, which is default
        ui->cboAccelLevel->setEnabled(false);
    }
}
void MainWindow::ShowHideDecelOptions(bool isChecked)
{
    if (isChecked)
    {   // Show options
        ui->lblDecelPreset->setEnabled(true);
        ui->cboDecelPreset->setEnabled(true);
        ui->lblDecelLevel->setEnabled(true);
        ui->cboDecelLevel->setEnabled(true);
    }
    else
    {   // Hide options
        ui->lblDecelPreset->setEnabled(false);
        ui->cboAccelPreset->setCurrentIndex(ui->cboDecelPreset->findData(DDP_NONE));
        ui->cboDecelPreset->setEnabled(false);
        ui->lblDecelLevel->setEnabled(false);
        ui->cboDecelLevel->setCurrentIndex(3);  // This will put it on item 4, which is default
        ui->cboDecelLevel->setEnabled(false);
    }
}
void MainWindow::ShowHideBarrelSensitivity(bool isChecked)
{
    if (isChecked)
    {
        ui->lblBarrelSensitivity1->setEnabled(true);
        ui->lblBarrelSensitivity2->setEnabled(true);
        ui->spinBarrelSensitivity->setEnabled(true);
        ui->spinBarrelSensitivity->setValue(DeviceData.BarrelSensitivity);
    }
    else
    {
        ui->lblBarrelSensitivity1->setEnabled(false);
        ui->lblBarrelSensitivity2->setEnabled(false);
        DeviceData.BarrelSensitivity = 50;
        ui->spinBarrelSensitivity->setValue(DeviceData.BarrelSensitivity);
        ui->spinBarrelSensitivity->setEnabled(false);
    }
}
void MainWindow::ShowHideHillSensitivity(bool isChecked)
{
    if (isChecked)
    {
        ui->lblHillSensitivity1->setEnabled(true);
        ui->lblHillSensitivity2->setEnabled(true);
        ui->spinHillSensitivity->setEnabled(true);
        ui->spinHillSensitivity->setValue(DeviceData.HillSensitivity);
    }
    else
    {
        ui->lblHillSensitivity1->setEnabled(false);
        ui->lblHillSensitivity2->setEnabled(false);
        DeviceData.HillSensitivity = 50;
        ui->spinHillSensitivity->setValue(DeviceData.HillSensitivity);
        ui->spinHillSensitivity->setEnabled(false);
    }
}
void MainWindow::ShowHideBarrelStabilization(bool isEnabled)
{
    if (isEnabled)
    {
        ui->lblBarrelNote->hide();
        ui->lblEnableBarrelStabilization->setEnabled(true);
        ui->chkEnableBarrel->setEnabled(true);
        ui->chkEnableBarrel->setChecked(DeviceData.EnableBarrelStabilize);
    }
    else
    {
        ui->lblBarrelNote->show();
        ui->lblEnableBarrelStabilization->setEnabled(false);
        ui->chkEnableBarrel->setChecked(false);
        DeviceData.EnableBarrelStabilize = false;
        ui->chkEnableBarrel->setEnabled(false);
    }
}

