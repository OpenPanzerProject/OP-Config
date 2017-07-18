#include "mainwindow.h"
#include "ui_mainwindow.h"


//------------------------------------------------------------------------------------------------------------------------>>
// FORM CONTROLS - MOTOR TAB
//------------------------------------------------------------------------------------------------------------------------>>
void MainWindow::SetupControls_MotorTab(void)
{
    // Setup the drive type combo
    ui->cboDriveType->insertItem(1, "Tank (Dual drive motors)", DT_TANK);
    ui->cboDriveType->insertItem(2, "Tank (Single drive motor + steering motor, eg DKLM)", DT_DKLM);
    ui->cboDriveType->insertItem(3, "Halftrack (Dual drive motors + Steering servo)", DT_HALFTRACK);
    ui->cboDriveType->insertItem(4, "Car (Single drive motor + Steering servo)", DT_CAR);
    ui->cboDriveType->setCurrentIndex(0);

    // Setup the motor type combo boxes
    ui->cboDriveMotors->setCategory(mcDrive);
    ui->cboTurretRotationMotor->setCategory(mcTurretRotation);
    ui->cboTurretElevationMotor->setCategory(mcTurretElevation);

    // Smoker control combo
    ui->cboSmokerControl->insertItem(0, "Auto (with engine speed)", true);
    ui->cboSmokerControl->insertItem(1, "Manual (with analog function trigger)", false);
    ui->cboSmokerControl->setCurrentIndex(0);
    connect(ui->cboSmokerControl, SIGNAL(currentIndexChanged(int)), this, SLOT(ShowHideSmokerSettings()));

    // Setup the airsoft/recoil combo
    ui->cboMechBarrelType->insertItem(1, "Airsoft", true);
    ui->cboMechBarrelType->insertItem(2, "Mechanical Recoil", false);
    // If they select Airsoft, disable the mech recoil settings
    connect(ui->cboMechBarrelType, SIGNAL(currentIndexChanged(int)), this, SLOT(ShowHideRecoilDelay()));
    // This handles the user setting related to whether mechanical barrel should auto trigger with cannon fire.
    connect(ui->chkEnableMechBarrel, SIGNAL(clicked(bool)), this, SLOT(SetMechBarrelAuto(bool)));

    // Setup servo recoil
    // This handles the user setting related to whether recoil servo should auto trigger with cannon fire.
    connect(ui->chkEnableRecoilServo, SIGNAL(clicked(bool)), this, SLOT(SetRecoilServoAuto(bool)));
    // We hide these two controls for now - a label and a combo box. Later someday when more pre-made recoil units become
    // available for purchase, we can enable these and have various presets that correspond to settings appropriate for
    // those pre-built units. For now, there is really only a single unit available, the Taigen Tiger 1 combination
    // airsoft/servo recoil unit. We just set our default values to work with it.
    ui->lblRecoilServoPreset->hide();
    ui->cboRecoilServoPreset->hide();

    // Any changes in the motor selections will trigger a validation routine
    connect(ui->cboDriveType, SIGNAL(currentIndexChanged(int)), this, SLOT(ValidateMotorSelections()));
    connect(ui->cboDriveMotors, SIGNAL(currentDriveTypeChanged(Drive_t)), this, SLOT(ValidateMotorSelections()));
    connect(ui->cboTurretRotationMotor, SIGNAL(currentDriveTypeChanged(Drive_t)), this, SLOT(ValidateMotorSelections()));
    connect(ui->cboTurretElevationMotor, SIGNAL(currentDriveTypeChanged(Drive_t)), this, SLOT(ValidateMotorSelections()));
    // We also want to enable/disable the Halftrack turn percent setting depending on whether the selected drive type is
    // halftrack or not. The signal goes here, but the slot will show up under the Driving tab function list
    connect(ui->cboDriveType, SIGNAL(currentIndexChanged(int)), this, SLOT(ShowHideHalftrackTurn(int)));
    // If they do select halftrack, we also auto-disable neutral turns
    connect(ui->cboDriveType, SIGNAL(currentIndexChanged(int)), this, SLOT(ShowHideNeutralTurnAllowed(int)));

    // Click on the ESC Warning label and it will take them to the help page
    connect(ui->lblESCWarningHelp, SIGNAL(linkActivated(QString)), this, SLOT(showPageDocumentation(QString)));
}
void MainWindow::SetMechBarrelAuto(bool isChecked)
{
    if (isChecked)
    {   // User wants the airsoft/or mechanical recoil to occur automatically with cannon fire
        // We remove the manual airsoft/mech recoil function from the function list
        ui->cboSelectFunction->RemoveSF(SF_MECH_BARREL);
        // Make sure we didn't already have a function trigger defined for it too
        if (FT_TableModel->removeFunctionFromList(SF_MECH_BARREL)) { RemovedFunctionTriggersMsgBox(); }
    }
    else
    {   // User does not want airsoft/or mechanical recoil to occur automatically with cannon fire.
        // Add a manual control option to the function list
        // The add function will only add it if it isn't there already
        ui->cboSelectFunction->AddSF(SF_MECH_BARREL);
    }
}
void MainWindow::SetRecoilServoAuto(bool isChecked)
{
    if (isChecked)
    {   // User wants the recoil servo action to occur automatically with cannon fire
        // We remove the manual servo recoil function from the function list
        ui->cboSelectFunction->RemoveSF(SF_RECOIL_SERVO);
        // Make sure we didn't already have a function trigger defined for it too
        if (FT_TableModel->removeFunctionFromList(SF_RECOIL_SERVO)) { RemovedFunctionTriggersMsgBox(); }
    }
    else
    {   // User does not want recoil servo action to occur automatically with cannon fire.
        // Add a manual control option to the function list
        // The add function will only add it if it isn't there already
        ui->cboSelectFunction->AddSF(SF_RECOIL_SERVO);
    }
}
void MainWindow::ShowHideRecoilDelay()
{
    if (ui->cboMechBarrelType->currentData() == true)
    {   // Airsoft selected - don't give delay options
        ui->lblRecoilDelay1->setEnabled(false);
        ui->lblRecoilDelay2->setEnabled(false);
        ui->lblRecoilDelay3->setEnabled(false);
        ui->spinRecoilDelay->setValue(0);
        DeviceData.RecoilDelay = 0;
        ui->spinRecoilDelay->setEnabled(false);
    }
    else
    {   // Mechanical recoil selected - provide delay options
        ui->lblRecoilDelay1->setEnabled(true);
        ui->lblRecoilDelay2->setEnabled(true);
        ui->lblRecoilDelay3->setEnabled(true);
        ui->spinRecoilDelay->setEnabled(true);
        ui->spinRecoilDelay->setValue(DeviceData.RecoilDelay);
    }
}
void MainWindow::ShowHideSmokerSettings()
{
    if (ui->cboSmokerControl->currentData() == true)
    {   // Auto control - show the speed settings
        // Show labels
        ui->lblSmokerIdle->setEnabled(true);
        ui->lblSmokerIdle2->setEnabled(true);
        ui->lblSmokerFastIdle->setEnabled(true);
        ui->lblSmokerFastIdle2->setEnabled(true);
        ui->lblSmokerMax->setEnabled(true);
        ui->lblSmokerMax2->setEnabled(true);
        ui->lblSmokeDestroyed->setEnabled(true);
        ui->lblSmokeDestroyed2->setEnabled(true);
        ui->lblSmokeDestroyed3->setEnabled(true);
        // Show spinners
        ui->spinSmokerIdle->setEnabled(true);
        ui->spinSmokerFastIdle->setEnabled(true);
        ui->spinSmokerMax->setEnabled(true);
        ui->spinSmokeDestroyed->setEnabled(true);
        // Set spinner vals
        ui->spinSmokerMax->setValue(qRound(static_cast<double>(DeviceData.SmokerMaxSpeed)/MOTOR_MAX_FWDSPEED_DBL*100.0));
        ui->spinSmokerIdle->setValue(qRound(static_cast<double>(DeviceData.SmokerIdleSpeed)/MOTOR_MAX_FWDSPEED_DBL*100.0));
        ui->spinSmokerFastIdle->setValue(qRound(static_cast<double>(DeviceData.SmokerFastIdleSpeed)/MOTOR_MAX_FWDSPEED_DBL*100.0));
        ui->spinSmokeDestroyed->setValue(qRound(static_cast<double>(DeviceData.SmokerDestroyedSpeed)/MOTOR_MAX_FWDSPEED_DBL*100.0));
        // Also in this case, we remove the manual smoker control functions from the function list
        ui->cboSelectFunction->RemoveSF(SF_SMOKER);     // This is an analog function for manual control of the speed (voltage)
        ui->cboSelectFunction->RemoveSF(SF_SMOKER_ON);  // This is a digital function that allows manual control on
        ui->cboSelectFunction->RemoveSF(SF_SMOKER_OFF); // This is a digital function that allows manual control off
        // Make sure we didn't already have a function trigger defined for it too
        // Note we use a single | not || because we want the if statement to evaluate all conditions regardless
        if (FT_TableModel->removeFunctionFromList(SF_SMOKER)    |
            FT_TableModel->removeFunctionFromList(SF_SMOKER_ON) |
            FT_TableModel->removeFunctionFromList(SF_SMOKER_OFF))
            { RemovedFunctionTriggersMsgBox(); }
        // Auto control does mean however that we want the three enable/disable/toggle functions to be available in the function list
        // The add function will only add it if it isn't there already
        ui->cboSelectFunction->AddSF(SF_SMOKER_ENABLE);
        ui->cboSelectFunction->AddSF(SF_SMOKER_DISABLE);
        ui->cboSelectFunction->AddSF(SF_SMOKER_TOGGLE);
    }
    else
    {   // Manual control - hide the speed settings
        // Hide labels
        ui->lblSmokerIdle->setEnabled(false);
        ui->lblSmokerIdle2->setEnabled(false);
        ui->lblSmokerFastIdle->setEnabled(false);
        ui->lblSmokerFastIdle2->setEnabled(false);
        ui->lblSmokerMax->setEnabled(false);
        ui->lblSmokerMax2->setEnabled(false);
        ui->lblSmokeDestroyed->setEnabled(false);
        ui->lblSmokeDestroyed2->setEnabled(false);
        ui->lblSmokeDestroyed3->setEnabled(false);
        // Hide spinners
        ui->spinSmokerIdle->setEnabled(false);
        ui->spinSmokerFastIdle->setEnabled(false);
        ui->spinSmokerMax->setEnabled(false);
        ui->spinSmokeDestroyed->setEnabled(false);
        // Manual control means we need to add the smoker control functions to the function list
        // The add function will only add it if it isn't there already
        ui->cboSelectFunction->AddSF(SF_SMOKER);    // This is an analog function for manual control of the speed (voltage)
        ui->cboSelectFunction->AddSF(SF_SMOKER_ON); // This is a digital function that allows manual control on
        ui->cboSelectFunction->AddSF(SF_SMOKER_OFF);// This is a digital function that allows manual control off
        // But it also means we want to remove the three enable/disable/toggle functions because those only
        // apply to auto control
        ui->cboSelectFunction->RemoveSF(SF_SMOKER_ENABLE);
        ui->cboSelectFunction->RemoveSF(SF_SMOKER_DISABLE);
        ui->cboSelectFunction->RemoveSF(SF_SMOKER_TOGGLE);
        // Make sure we didn't already have a function trigger defined for it too
        // Note we use a single | not || because we want the if statement to evaluate all conditions regardless
        if (FT_TableModel->removeFunctionFromList(SF_SMOKER_ENABLE)  |
            FT_TableModel->removeFunctionFromList(SF_SMOKER_DISABLE) |
            FT_TableModel->removeFunctionFromList(SF_SMOKER_TOGGLE))
            RemovedFunctionTriggersMsgBox();
    }
}


void MainWindow::ValidateMotorSelections()
{
    // Some combinations are not possible, for example, drive motors set to Onboard as well as turret motors.
    if (ui->cboDriveMotors->isOnboard() && (ui->cboTurretRotationMotor->isOnboard() || ui->cboTurretElevationMotor->isOnboard()))
    {
        // Set the motor to RC Output instead
        ui->cboDriveMotors->setCurrentIndex(ui->cboDriveMotors->findData(SERVO_ESC));
        msgBox("Only the turret or the drive motors can be connected to the onboard motor driver, but not both. Please check again.\n\nThe drive motor selection has been changed to RC Output for now.",vbOkOnly,"Invalid Motor Selections",vbExclamation);
    }

    // Another combination that is not possible, is drive type set to Halftrack with dual drive motors with
    // drive motors set to RC Output - that is because in halftrack/car mode, the Right Tread RC Output is used for the steering servo
    if (ui->cboDriveType->currentData() == DT_HALFTRACK && ui->cboDriveMotors->isRCOutput())
    {
        // Set the motor to Sabertooth instead
        ui->cboDriveMotors->setCurrentIndex(ui->cboDriveMotors->findData(SABERTOOTH));
        msgBox("When drive type is set to dual-motor halftrack, the dual drive motors must be powered by the onboard drivers or a serial controller.\n\nThe drive motor selection has been changed to Sabertooth for now.",vbOkOnly,"Invalid Motor Selections",vbExclamation);
    }

    // We will however allow both turret and drive motors to be driven by serial, but the user will need to make
    // some kind of Y-harness and assign each serial ESC a unique address


    // Another restriction is that turn modes are disabled for cars (obviously) as well as clutch-style tank gearboxes.
    // First, make sure they are all already there (AddSF will only add them if they are not)
    ui->cboSelectFunction->AddSF(SF_TURNMODE_1);
    ui->cboSelectFunction->AddSF(SF_TURNMODE_2);
    ui->cboSelectFunction->AddSF(SF_TURNMODE_3);
    // Now remove them if necessary
    if (ui->cboDriveType->currentData() == DT_CAR || ui->cboDriveType->currentData() == DT_DKLM)
    {
        ui->cboSelectFunction->RemoveSF(SF_TURNMODE_1);
        ui->cboSelectFunction->RemoveSF(SF_TURNMODE_2);
        ui->cboSelectFunction->RemoveSF(SF_TURNMODE_3);
        // Note we use a single | not || because we want the if statement to evaluate all conditions regardless
        if (FT_TableModel->removeFunctionFromList(SF_TURNMODE_1) |
            FT_TableModel->removeFunctionFromList(SF_TURNMODE_2) |
            FT_TableModel->removeFunctionFromList(SF_TURNMODE_3))
            RemovedFunctionTriggersMsgBox();
    }

    // Neutral turns are not allowed for Cars and Halftracks, so remove that function if necessary
    // First, make sure they are all already there (AddSF will only add them if they are not)
    ui->cboSelectFunction->AddSF(SF_NT_ENABLE);
    ui->cboSelectFunction->AddSF(SF_NT_DISABLE);
    ui->cboSelectFunction->AddSF(SF_NT_TOGGLE);
    // Now remove them if necessary
    if (ui->cboDriveType->currentData() == DT_CAR || ui->cboDriveType->currentData() == DT_HALFTRACK)
    {
        ui->cboSelectFunction->RemoveSF(SF_NT_ENABLE);
        ui->cboSelectFunction->RemoveSF(SF_NT_DISABLE);
        ui->cboSelectFunction->RemoveSF(SF_NT_TOGGLE);
        // Note we use a single | not || because we want the if statement to evaluate all conditions regardless
        if (FT_TableModel->removeFunctionFromList(SF_NT_ENABLE) |
            FT_TableModel->removeFunctionFromList(SF_NT_DISABLE) |
            FT_TableModel->removeFunctionFromList(SF_NT_TOGGLE))
            RemovedFunctionTriggersMsgBox();
    }

    // If the drive motor type is set to the Scout ESC, we allow a special setting on the Driving tab that, if enabled, tells the
    // Scout to attempt to drag the slower moving (inner) track during turns. This can be used for heavy models with wide tracks
    // that are driven with free-wheeling gearboxes such as the Taigen V2 Steel 3:1 and 4:1 gearboxes that otherwise do not want to
    // slow down in a turn and make it in fact very difficult to turn the model at all.
    ValidateFreewheelingGearboxOptions();

    // If the turret elevation motor is set to SERVO_PAN we enable the option to implement barrel stabilization (on the Driving tab).
    // Otherwise if it is any other setting, stabilization is unavailable
    if (ui->cboTurretElevationMotor->getCurrentDriveType() == SERVO_PAN)
        ShowHideBarrelStabilization(true);
    else
        ShowHideBarrelStabilization(false);

    // Now depending on what *wasn't* selected, it may be possible to add pass-through servo signals to unused servo outputs
    // This is its own function because there are other elements that influence the available passthroughs, specifically
    // sound card selection.
    ValidateRCPassthroughs();

    // Also depending on what *wasn't* selected, it may be possible to use the onboard Motor A or B output
    // as a general purpose ESC. First, remove and then add so they will be next to each other (if both are available):
    ui->cboSelectFunction->RemoveSF(SF_MOTOR_A);
    ui->cboSelectFunction->RemoveSF(SF_MOTOR_B);
    ui->cboSelectFunction->AddSF(SF_MOTOR_A);
    ui->cboSelectFunction->AddSF(SF_MOTOR_B);
    // Now remove either one if they should not be there
    if (ui->cboTurretRotationMotor->isOnboard())
    {
        ui->cboSelectFunction->RemoveSF(SF_MOTOR_A);
        if (FT_TableModel->removeFunctionFromList(SF_MOTOR_A))
            RemovedFunctionTriggersMsgBox();
    }
    if (ui->cboTurretElevationMotor->isOnboard())
    {
        ui->cboSelectFunction->RemoveSF(SF_MOTOR_B);
        if (FT_TableModel->removeFunctionFromList(SF_MOTOR_B))
            RemovedFunctionTriggersMsgBox();
    }
    if (ui->cboDriveMotors->isOnboard())
    {
        if (ui->cboDriveType->currentData() == DT_CAR)
        {   // In the case of a car only Motor A is taken
            if (FT_TableModel->removeFunctionFromList(SF_MOTOR_A))
                RemovedFunctionTriggersMsgBox();
        }
        else
        {
            // Drive type is Tank or Halftrack or DKLM - remove both onboard drivers
            ui->cboSelectFunction->RemoveSF(SF_MOTOR_A);
            ui->cboSelectFunction->RemoveSF(SF_MOTOR_B);
            // Note we use a single | not || because we want the if statement to evaluate all conditions regardless
            if (FT_TableModel->removeFunctionFromList(SF_MOTOR_A) | FT_TableModel->removeFunctionFromList(SF_MOTOR_B))
                RemovedFunctionTriggersMsgBox();
        }
    }

    // Now provide some connection hints based on the user's selection
    // If the user selected halftrack or car, show the steering servo message
    if (ui->cboDriveType->currentData() == DT_HALFTRACK || ui->cboDriveType->currentData() == DT_CAR)
    {
        ui->lblSteeringServo->show();
    }
    else
    {
        ui->lblSteeringServo->hide();
    }
    // Now the drive motor connection
    // Drive motors driven by Serial
    if (ui->cboDriveMotors->isSerial())
    {   if (ui->cboDriveType->currentData() == DT_HALFTRACK || ui->cboDriveType->currentData() == DT_TANK)
        {
            switch (ui->cboDriveMotors->getCurrentDriveType())
            {
            case SABERTOOTH:
                ui->lblDriveMotors->setText("Connect motors to Sabertooth: Left = \"M1\", Right = \"M2\"");
                break;
            case POLOLU:
                ui->lblDriveMotors->setText("Connect motors to Pololu Qik: Left = \"M0\", Right = \"M1\"");
                break;
            case OP_SCOUT:
                ui->lblDriveMotors->setText("Connect motors to Scout: Left = \"M1\", Right = \"M2\"");
                break;
            default:
                ui->lblDriveMotors->setText("");
            }
        }
        else if (ui->cboDriveType->currentData() == DT_DKLM)
        {
            switch (ui->cboDriveMotors->getCurrentDriveType())
            {
            case SABERTOOTH:
                ui->lblDriveMotors->setText("Connect motors to Sabertooth: Propulsion = \"M1\", Steering = \"M2\"");
                break;
            case POLOLU:
                ui->lblDriveMotors->setText("Connect motors to Pololu Qik: Propulsion = \"M0\", Steering = \"M1\"");
                break;
            case OP_SCOUT:
                ui->lblDriveMotors->setText("Connect motors to Scout: Propulsion = \"M1\", Steering = \"M2\"");
                break;
            default:
                ui->lblDriveMotors->setText("");
            }
        }
        else if (ui->cboDriveType->currentData() == DT_CAR)
        {
            switch (ui->cboDriveMotors->getCurrentDriveType())
            {
            case SABERTOOTH:
                ui->lblDriveMotors->setText("Connect drive motor to Sabertooth \"M1\"");
                break;
            case POLOLU:
                ui->lblDriveMotors->setText("Connect drive motor to Pololu Qik \"M0\"");
                break;
            case OP_SCOUT:
                ui->lblDriveMotors->setText("Connect drive motor to Scout \"M1\"");
                break;
            default:
                ui->lblDriveMotors->setText("");
            }
        }
    }

    // Drive motors driven by RC
    if (ui->cboDriveMotors->isRCOutput())
    {
        if (ui->cboDriveType->currentData() == DT_HALFTRACK || ui->cboDriveType->currentData() == DT_TANK)
        {
            ui->lblDriveMotors->setText("Plug Left ESC into RC Output 1, Right ESC into RC Output 2");
        }
        else if (ui->cboDriveType->currentData() == DT_DKLM)
        {
            ui->lblDriveMotors->setText("Plug Propulsion ESC into RC Output 1, Steering ESC into RC Output 2");
        }
        else if (ui->cboDriveType->currentData() == DT_CAR)
        {
            ui->lblDriveMotors->setText("Plug motor ESC into RC Output 1, steering servo into RC Output 2");
        }
    }

    // Drive motors driven by Onboard
    if (ui->cboDriveMotors->isOnboard())
    {
        if (ui->cboDriveType->currentData() == DT_HALFTRACK || ui->cboDriveType->currentData() == DT_TANK)
        {
            ui->lblDriveMotors->setText("Connect motors to terminals on TCB: Left = \"Motor A\", Right = \"Motor B\"");
        }
        else if (ui->cboDriveType->currentData() == DT_DKLM)
        {
            ui->lblDriveMotors->setText("Connect propulsion motor to \"Motor A\", steering motor to \"Motor B\"");
        }
        else if (ui->cboDriveType->currentData() == DT_CAR)
        {
            ui->lblDriveMotors->setText("Connect drive motor to \"Motor A\" screw terminals on TCB");
        }
    }

    // Now the turret rotation  motor
    if (ui->cboTurretRotationMotor->isSerial())
    {    switch (ui->cboTurretRotationMotor->getCurrentDriveType())
        {
        case SABERTOOTH:
            ui->lblRotationMotor->setText("Connect turret rotation motor to \"M1\" on Sabertooth");
            break;
        case POLOLU:
            ui->lblRotationMotor->setText("Connect turret rotation motor to \"M0\" on Pololu Qik");
            break;
        case OP_SCOUT:
            ui->lblRotationMotor->setText("Connect turret rotation motor to \"M1\" on Scout");
            break;
        case DRIVE_DETACHED:
            ui->lblRotationMotor->setText("");
        default:
            ui->lblRotationMotor->setText("");
        }
    }
    if (ui->cboTurretRotationMotor->isRCOutput())
    {
        if (ui->cboTurretRotationMotor->getCurrentDriveType() == SERVO_ESC)
        {   ui->lblRotationMotor->setText("Connect turret rotation Servo/ESC to RC Output 3"); }
        else if (ui->cboTurretRotationMotor->getCurrentDriveType() == SERVO_PAN)
        {   ui->lblRotationMotor->setText("Connect turret rotation Servo to RC Output 3"); }
    }
    if (ui->cboTurretRotationMotor->isOnboard())
        ui->lblRotationMotor->setText("Connect turret rotation motor to \"Motor A\" screw terminals on TCB");
    // Do this last or it doesn't apply somehow
    if (ui->cboTurretRotationMotor->getCurrentDriveType() == DRIVE_DETACHED)
        ui->lblRotationMotor->setText("");

    // Now the barrel elevation  motor
    if (ui->cboTurretElevationMotor->isSerial())
    {    switch (ui->cboTurretElevationMotor->getCurrentDriveType())
        {
        case SABERTOOTH:
            ui->lblElevationMotor->setText("Connect barrel elevation motor to \"M2\"  on Sabertooth");
            break;
        case POLOLU:
            ui->lblElevationMotor->setText("Connect barrel eleavation motor to \"M1\" on Pololu Qik");
            break;
        case OP_SCOUT:
            ui->lblElevationMotor->setText("Connect barrel elevation motor to \"M2\"  on Scout");
            break;
        case DRIVE_DETACHED:
            ui->lblElevationMotor->setText("");
        default:
            ui->lblElevationMotor->setText("");
        }
    }
    if (ui->cboTurretElevationMotor->isRCOutput())
    {
        if (ui->cboTurretElevationMotor->getCurrentDriveType() == SERVO_ESC)
        {   ui->lblElevationMotor->setText("Connect barrel elevation Servo/ESC to RC Output 4"); }
        else if (ui->cboTurretElevationMotor->getCurrentDriveType() == SERVO_PAN)
        {   ui->lblElevationMotor->setText("Connect barrel elevation Servo to RC Output 4"); }
    }
    if (ui->cboTurretElevationMotor->isOnboard())
        ui->lblElevationMotor->setText("Connect barrel elevation motor to \"Motor B\" screw terminals on TCB");
    // Do this last or it doesn't apply somehow
    if (ui->cboTurretElevationMotor->getCurrentDriveType() == DRIVE_DETACHED)
        ui->lblElevationMotor->setText("");

    // Check if any selections are ESCs, and if so, show the ESC warning message
    if (ui->cboDriveMotors->isESC() || ui->cboTurretRotationMotor->isESC() || ui->cboTurretElevationMotor->isESC())
    {
        ui->frmESCWarning->show();
    }
    else
    {
        ui->frmESCWarning->hide();
    }

    // Finally, we may need to enable/disable the turret stick delay options, depending on whether the turret stick
    // is set to control any motor or whether it has been detached.
    UpdateTurretStickDelayOptions(FT_TableModel->isTurretStickPresent());

}


void MainWindow::ValidateRCPassthroughs()
{
    // Depending on what is *not* selected, either as drive types or sound card options, some RC outputs may be
    // freed up for general pass-through directly from the radio. Since the TCB only accepts serial RC inputs, this
    // can be useful for controlling servos even with small receivers that don't have servo outputs.

    // So these functions always remain together in the list, we will do all of them whether they need it or not.

    // First, add all:
    ui->cboSelectFunction->removeAllRCPassthroughs();    // Remove and then add, so we can be sure they go in order
    ui->cboSelectFunction->addAllRCPassthroughs();       // Now add all in order


    // Now: remove the ones that should not be there. If we remove one from the combo, check also if it exists already in our
    // function trigger list, and if so, remove it from there too.

    // Servo 1 & 2 - available if drive motors are not RC outputs, and if there is no steering servo
    if (ui->cboDriveMotors->isRCOutput())
    {   // In this case we lose both servo 1 & 2
        ui->cboSelectFunction->removeRCPassthrough(SERVONUM_LEFTTREAD);
        ui->cboSelectFunction->removeRCPassthrough(SERVONUM_RIGHTTREAD);

        // Now make sure these aren't in our function triggers
        // Note we use a single | not || because we want the if statement to evaluate all conditions regardless
        if (FT_TableModel->removeFunctionFromList(SF_RC1_PASS)     |
            FT_TableModel->removeFunctionFromList(SF_RC1_PASS_PAN) |
            FT_TableModel->removeFunctionFromList(SF_RC2_PASS)     |
            FT_TableModel->removeFunctionFromList(SF_RC2_PASS_PAN))
            RemovedFunctionTriggersMsgBox();
    }
    else
    {
        if (ui->cboDriveType->currentData() != DT_TANK)
        {   // Even if the drive motors are not RC outs, we might still lose the right tread servo slot if we have
            // a steering servo, which we will if this is a halftrack or car
            ui->cboSelectFunction->removeRCPassthrough(SERVONUM_RIGHTTREAD);
            // Now make sure this isn't in our function trigger list
            // Note we use a single | not || because we want the if statement to evaluate all conditions regardless
            if (FT_TableModel->removeFunctionFromList(SF_RC2_PASS) |
                FT_TableModel->removeFunctionFromList(SF_RC2_PASS_PAN))
                RemovedFunctionTriggersMsgBox();
        }
    }
    // Servo 3 - available if turret rotation is not RC output
    if (ui->cboTurretRotationMotor->isRCOutput())
    {
        ui->cboSelectFunction->removeRCPassthrough(SERVONUM_TURRETROTATION);
        // Now make sure this isn't in our function trigger list
        // Note we use a single | not || because we want the if statement to evaluate all conditions regardless
        if (FT_TableModel->removeFunctionFromList(SF_RC3_PASS) |
            FT_TableModel->removeFunctionFromList(SF_RC3_PASS_PAN))
            RemovedFunctionTriggersMsgBox();
    }
    // Servo 4 - available if turret elevation is not RC output
    if (ui->cboTurretElevationMotor->isRCOutput())
    {
        ui->cboSelectFunction->removeRCPassthrough(SERVONUM_TURRETELEVATION);
        // Now make sure this isn't in our function trigger list
        // Note we use a single | not || because we want the if statement to evaluate all conditions regardless
        if (FT_TableModel->removeFunctionFromList(SF_RC4_PASS) |
            FT_TableModel->removeFunctionFromList(SF_RC4_PASS_PAN))
            RemovedFunctionTriggersMsgBox();
    }

    // Servo 5 - never available, always reserved for recoil action

    // Servos 6-8 - available depending on sound card selection
    switch (ui->cboSoundDevice->getCurrentSoundDevice())
    {
        case SD_BENEDINI_TBSMINI:
            // Benedini sound card requires three outputs so none of these are available
            ui->cboSelectFunction->removeRCPassthrough(6);
            ui->cboSelectFunction->removeRCPassthrough(7);
            ui->cboSelectFunction->removeRCPassthrough(8);
            // Now make sure this isn't in our function trigger list
            // Note we use a single | not || because we want the if statement to evaluate all conditions regardless
            if (FT_TableModel->removeFunctionFromList(SF_RC6_PASS)     |
                FT_TableModel->removeFunctionFromList(SF_RC6_PASS_PAN) |
                FT_TableModel->removeFunctionFromList(SF_RC7_PASS)     |
                FT_TableModel->removeFunctionFromList(SF_RC7_PASS_PAN) |
                FT_TableModel->removeFunctionFromList(SF_RC8_PASS)     |
                FT_TableModel->removeFunctionFromList(SF_RC8_PASS_PAN))
                RemovedFunctionTriggersMsgBox();
            break;

        case SD_TAIGEN_SOUND:
            // The Taigen sound card only needs output 8, the other two are free for general use
            ui->cboSelectFunction->removeRCPassthrough(8);
            // Now make sure this isn't in our function trigger list
            // Note we use a single | not || because we want the if statement to evaluate all conditions regardless
            if (FT_TableModel->removeFunctionFromList(SF_RC8_PASS) |
                FT_TableModel->removeFunctionFromList(SF_RC8_PASS_PAN))
                RemovedFunctionTriggersMsgBox();
            break;
    }
}
