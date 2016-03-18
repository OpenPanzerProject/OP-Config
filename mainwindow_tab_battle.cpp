#include "mainwindow.h"
#include "ui_mainwindow.h"


//------------------------------------------------------------------------------------------------------------------------>>
// FORM CONTROLS - BATTLE TAB
//------------------------------------------------------------------------------------------------------------------------>>
void MainWindow::SetupControls_BattleTab(void)
{
    // Setup the primary and secondary IR protocols
    ui->cboFireProtocol->SetupPrimary();    // Primary is the protocol the cannon fires. Damage is also taken with hits from this protocol.
    ui->cboHitProtocol_2->SetupSecondary(); // An optional secondary protocol is NOT fired, but you can take damage from it.

    // Setup the Team combo. We start it with no entry (just none) and disabled
    ui->cboTeam->SetupNone();
    ui->cboTeam->setEnabled(false);

    // If the primary protocol changes, update the list of secondary protocols
    connect(ui->cboFireProtocol, SIGNAL(currentIndexChanged(int)), this, SLOT(SetupSecondaryCannonIR(int)));

    // If the primary protocol changes, check the team list in case that needs to be set as well.
    connect(ui->cboFireProtocol, SIGNAL(currentIndexChanged(int)), this, SLOT(SetupIRTeamList(int)));

    // If the cannon or MG protocols are disabled, you can disable some other settings
    connect(ui->cboFireProtocol, SIGNAL(currentIndexChanged(int)), this, SLOT(ShowHideCannonIRSettings(int)));
    connect(ui->cboMGProtocol, SIGNAL(currentIndexChanged(int)), this, SLOT(ShowHideMGIRSettings(int)));

    // If both cannon and MG protocols are disabled, you can disable even more stuff
    connect(ui->cboFireProtocol, SIGNAL(currentIndexChanged(int)), this, SLOT(ShowHideOtherBattleSettings(int)));
    connect(ui->cboMGProtocol, SIGNAL(currentIndexChanged(int)), this, SLOT(ShowHideOtherBattleSettings(int)));

    // If we don't accept incoming MG hits, we can disable the max MG hits setting
    connect(ui->chkAcceptMG, SIGNAL(toggled(bool)), this, SLOT(ShowHideMGHits(bool)));

    // RC Tanks Australia Tank ID
    // DISABLED FOR NOW
    // I don't really like the way RCTA includes an ID number in their transmission. They take a three digit number,
    // split it into the individual numbers, and send each number one-by-one in three distinct Sony transmissions.
    // So for example, the number 456 is sent as "4", then "5", then "6". If the receiving device misses a single one
    // of those codes, the ID will not be read correctly. The silly thing is, each Sony code is 12-bits long, so you could
    // easily fit the entire 3-digit number PLUS a bunch of other data into a single code, and then repeat that same
    // code 3 times to give the receiver a much better chance of reading it. Overall length of the transmission would be identical,
    // and encoding/decoding would be easier as well (instead of trying to break apart a number into characters and then
    // reassembling it on the receiving end, you would just send the number as a number).

    // I don't think it's a bad idea overall to include an identifier in the IR transmission, so I have already created a variable
    // for it. But if we're going to do that we need to use a better method, and probably, the thing should be part of a
    // larger discussion about what the ideal Tank IR protocol would be if we were creating a new one from scratch.
    ui->lblSendRCTAID->hide();
    ui->chkSendTankID->hide();
    ui->spinTankID->hide();
    ui->lblSpinTankID->hide();
    // If we were going to include the tank ID, uncomment the following line:
    // User has the option of including a Tank ID number in cannon fire transmissions
    //connect(ui->chkSendTankID, SIGNAL(toggled(bool)), this, SLOT(ShowHideTankIDSettings(bool)));
}
void MainWindow::SetupIRTeamList(int)
{
    IRTYPES ir = static_cast<IRTYPES>(ui->cboFireProtocol->itemData(ui->cboFireProtocol->currentIndex()).toUInt());
    switch (ir)
    {
    case IR_FOV:
        ui->lblTeam->setEnabled(true);
        ui->cboTeam->SetupFOVTeams();
        ui->cboTeam->setEnabled(true);
        break;
    default:
        ui->lblTeam->setEnabled(false);
        ui->cboTeam->SetupNone();
        ui->cboTeam->setEnabled(false);
    }
}

void MainWindow::SetupSecondaryCannonIR(int)
{   // Any time the primary protocol changes, repopulate the secondary list (it is basically everything except the
    // primary selection)
    ui->cboHitProtocol_2->SetupSecondary(static_cast<IRTYPES>(ui->cboFireProtocol->currentData().toUInt()));

}
void MainWindow::ShowHideCannonIRSettings(int curIndex)
{   // If cannon IR is disabled, disable some related settings

    if (curIndex == 0)
    {   // Disable Cannon IR options
        ui->lblHitProtocol_2->setEnabled(false);
        ui->cboHitProtocol_2->setEnabled(false);
    }
    else
    {
        ui->lblHitProtocol_2->setEnabled(true);
        ui->cboHitProtocol_2->setEnabled(true);
    }
}
void MainWindow::ShowHideMGIRSettings(int curIndex)
{   // If machine gun IR is disabled, disable some related settings

    if (curIndex == 0)
    {   // Disable MG IR options
        ui->lblUseMG->setEnabled(false);
        ui->chkUseMG->setChecked(false);
        ui->chkUseMG->setEnabled(false);
        ui->lblAcceptMG->setEnabled(false);
        ui->chkAcceptMG->setChecked(false);
        ui->chkAcceptMG->setEnabled(false);
        ui->lblMaxMGHits1->setEnabled(false);
        ui->lblMaxMGHits2->setEnabled(false);
        ui->spinMaxMGHits->setEnabled(false);

    }
    else
    {
        ui->lblUseMG->setEnabled(true);
        ui->chkUseMG->setEnabled(true);
        ui->lblAcceptMG->setEnabled(true);
        ui->chkAcceptMG->setEnabled(true);
        ShowHideMGHits(ui->chkAcceptMG->isChecked());
    }
}
void MainWindow::ShowHideMGHits(bool isChecked)
{
    if (isChecked)
    {
        ui->lblMaxMGHits1->setEnabled(true);
        ui->lblMaxMGHits2->setEnabled(true);
        ui->spinMaxMGHits->setEnabled(true);
    }
    else
    {
        // We aren't accepting hits from MG, so we don't need this setting
        ui->lblMaxMGHits1->setEnabled(false);
        ui->lblMaxMGHits2->setEnabled(false);
        ui->spinMaxMGHits->setEnabled(false);
    }
}

void MainWindow::ShowHideOtherBattleSettings(int)
{   // If both cannon and machine gun IR are disabled, disable some related settings

    if (ui->cboFireProtocol->currentIndex() == 0 && ui->cboMGProtocol->currentIndex() == 0)
    {   // If we aren't using the cannon or the machine gun IR, we also don't need to worry
        // about repair IR or damage settings
        ui->lblRepairProtocol->setEnabled(false);
        ui->cboRepairProtocol->setCurrentIndex(0);
        ui->cboRepairProtocol->setEnabled(false);
        ui->lblDamageProfile->setEnabled(false);
        ui->cboDamageProfile->setCurrentIndex(0);
        ui->cboDamageProfile->setEnabled(false);
    }
    else
    {
        ui->lblRepairProtocol->setEnabled(true);
        ui->cboRepairProtocol->setEnabled(true);
        ui->lblDamageProfile->setEnabled(true);
        ui->cboDamageProfile->setEnabled(true);

    }
}
void MainWindow::ShowHideTankIDSettings(bool checked)
{
    if (checked)
    {
        ui->spinTankID->setEnabled(true);
        ui->spinTankID->setValue(DeviceData.TankID);
    }
    else
    {
        ui->spinTankID->setEnabled(false);
        ui->spinTankID->setValue(1);
    }
}
