#include "mainwindow.h"
#include "ui_mainwindow.h"


// Here we have two routines for setting all controls to the current value of our named variables, or
// setting all named variables to the values specified in the controls.

//------------------------------------------------------------------------------------------------------------------------>>
// VARIABLES TO CONTROLS & CONTROLS TO VARIABLES
//------------------------------------------------------------------------------------------------------------------------>>
void MainWindow::Variables_to_Controls(void)
{
    // Functions tab
    // ---------------------------------------------------------------------------------------------------------->>
    // We run the function tab first, because that allows us to populate the data model before we set all the channel settings.
    // Then, as the channel settings are loaded, they will automatically trigger validation checks against the model, and any
    // invalid function-triggers will get removed.

    // In this case, we are updating the FunctionTriggerTableModel, not a specific control. The QTableView widget will
    // automatically display the information from the model.
    // First we must clear every possible trigger, because we won't be updating them all.
    FT_TableModel->ClearModel();
    // Now save the function triggers from our array to the table model
    for (int i = 0; i < MAX_FUNCTION_TRIGGERS; i++)
    {
        if (DeviceData.SF_Trigger[i].TriggerID > 0 && DeviceData.SF_Trigger[i].specialFunction != SF_NULL_FUNCTION)
        {   // We assume the insert works, but if it doesn't, it won't matter, we won't want that function trigger anyway
            FT_TableModel->insertFunctionTrigger(DeviceData.SF_Trigger[i].specialFunction, DeviceData.SF_Trigger[i].TriggerID);
        }
    }
    // Turret stick ignore time - turret movements last less than this time are ignored (quick movement to extremes for special functions)
    ui->spinIgnoreTurretDelay->setValue(DeviceData.IgnoreTurretDelay_mS);

    // Radio tab
    // ---------------------------------------------------------------------------------------------------------->>
    // STICKS
    // Channel numbers - subtract 1 because Index is zero-based
    ui->cboThrottleChannelNum->setCurrentIndex(DeviceData.Sticks.Throttle.Settings.channelNum - 1);
    ui->cboTurnChannelNum->setCurrentIndex(DeviceData.Sticks.Turn.Settings.channelNum - 1);
    ui->cboElevationChannelNum->setCurrentIndex(DeviceData.Sticks.Elevation.Settings.channelNum - 1);
    ui->cboAzimuthChannelNum->setCurrentIndex(DeviceData.Sticks.Azimuth.Settings.channelNum - 1);
    // Deadband - only applies to stick channels, none on Aux
    ui->spinThrottleDeadband->setValue(DeviceData.Sticks.Throttle.Settings.deadband);
    ui->spinTurnDeadband->setValue(DeviceData.Sticks.Turn.Settings.deadband);
    ui->spinElevationDeadband->setValue(DeviceData.Sticks.Elevation.Settings.deadband);
    ui->spinAzimuthDeadband->setValue(DeviceData.Sticks.Azimuth.Settings.deadband);
    // Reversed
    for (int i=0; i<STICKCHANNELS; i++)
    {
        stickReversedCheck[i]->setChecked(*ChannelSettings[i].reversed);
    }
    // AUX CHANNELS
    for (int i=0; i<AUXCHANNELS; i++)
    {
        // Aux channel switch positions (if digital)
        auxSwitchPosCombo[i]->setCurrentText(QString::number(DeviceData.AuxChannel[i].Settings.numPositions));
        // Aux channel types (analog digital) - set by user data, not index
        auxTypeCombo[i]->setCurrentIndex(auxTypeCombo[i]->findData(DeviceData.AuxChannel[i].Settings.Digital));
        // Aux channel reversed settings
        auxReversedCheck[i]->setChecked(DeviceData.AuxChannel[i].Settings.reversed);
        // Aux channel channel numbers
        channelOrderCombo[STICKCHANNELS + i]->setCurrentIndex(DeviceData.AuxChannel[i].Settings.channelNum);
        // Now sanity-check all the aux channel controls
        SaveChannelNum("", "", channelOrderCombo[STICKCHANNELS + i], i);
        SaveAuxChannelType(auxTypeCombo[i],i);
        SaveAuxChannelPositions(auxSwitchPosCombo[i],i);
    }
    // BOTH STICKS AND AUX - Channels min/max/center/sliders
    UpdateChannelControls_MinMaxCenter();   // This takes care of the sliders and min/max labels
    for (int i=0; i<COUNT_OP_CHANNELS; i++)  // These are the actual pulse-widths and channel "positions"
    {
        // We can leave these blank for now, they will get updated when we are actually connected and streaming
        //lblChannelPulse[i]->setText(QString::number(*ChannelSettings[i].pulse));
        lblChannelPulse[i]->setText("");
        lblChannelPosition[i]->setText("");
    }


    // Motor tab
    // ---------------------------------------------------------------------------------------------------------->>
    // Motor settings
    ui->cboDriveType->setCurrentIndex(ui->cboDriveType->findData(DeviceData.DriveType));
    ShowHideHalftrackTurn(ui->cboDriveType->currentIndex());
    ui->cboDriveMotors->setCurrentDriveType(DeviceData.DriveMotors);
    ui->cboTurretRotationMotor->setCurrentDriveType(DeviceData.TurretRotationMotor);
    ui->cboTurretElevationMotor->setCurrentDriveType(DeviceData.TurretElevationMotor);
    // Mechanical barrel settings
    ui->cboMechBarrelType->setCurrentIndex(ui->cboMechBarrelType->findData(DeviceData.Airsoft));
    ui->spinRecoilDelay->setValue(DeviceData.RecoilDelay);
    ui->chkEnableMechBarrel->setChecked(DeviceData.MechanicalBarrelWithCannon);
    SetMechBarrelAuto(ui->chkEnableMechBarrel->isChecked());
    ShowHideRecoilDelay();
    // Recoil servo settings
    ui->spinRecoilTimeToRecoil->setValue(DeviceData.RecoilServo_Recoil_mS);
    ui->spinRecoilTimeToReturn->setValue(DeviceData.RecoilServo_Return_mS);
    ui->chkEnableRecoilServo->setChecked(DeviceData.ServoRecoilWithCannon);
    SetRecoilServoAuto(ui->chkEnableRecoilServo->isChecked());
    // Smoker settings - convert to Percent-based for user convenience (0-100, but they are actually 0-255)
    ui->cboSmokerControl->setCurrentIndex(ui->cboSmokerControl->findData(DeviceData.SmokerControlAuto));
    ui->spinSmokerMax->setValue(qRound(static_cast<double>(DeviceData.SmokerMaxSpeed)/MOTOR_MAX_FWDSPEED_DBL*100.0));
    ui->spinSmokerIdle->setValue(qRound(static_cast<double>(DeviceData.SmokerIdleSpeed)/MOTOR_MAX_FWDSPEED_DBL*100.0));
    ui->spinSmokerFastIdle->setValue(qRound(static_cast<double>(DeviceData.SmokerFastIdleSpeed)/MOTOR_MAX_FWDSPEED_DBL*100.0));
    ShowHideSmokerSettings();


    // Lights & IO Tab
    // ---------------------------------------------------------------------------------------------------------->>
    // Brake/Running lights
    ui->chkBrakesOnAtStop->setChecked(DeviceData.BrakesAutoOnAtStop);
    ui->spinRunningLightsDimLevel->setValue(DeviceData.RunningLightsDimLevelPct);
    ui->chkRunningLightsAlwaysOn->setChecked(DeviceData.RunningLightsAlwaysOn);
    // Machine Gun blinking
    ui->spinMGBlink_mS->setValue(DeviceData.MGLightBlink_mS);
    // Blink lights when radio signal lost
    ui->chkBlinkSignalLost->setChecked(DeviceData.FlashLightsWhenSignalLost);
    // High Intensity Flash Unit
    ui->chkHiFlashWithCannon->setChecked(DeviceData.HiFlashWithCannon);
    SetHiFlashAuto(ui->chkHiFlashWithCannon->isChecked());
    // Aux Output Settings
    ui->spinAuxFlash_mS->setValue(DeviceData.AuxLightFlashTime_mS);
    ui->spinAuxBlinkOn_mS->setValue(DeviceData.AuxLightBlinkOnTime_mS);
    ui->spinAuxBlinkOff_mS->setValue(DeviceData.AuxLightBlinkOffTime_mS);
    ui->spinAuxPresetDim->setValue(DeviceData.AuxLightPresetDim);
    // External I/O - set the combo to our user data, which means, we can't go directly to index
    // This sets the input type (analog or digital). Only applies if the data direction is input
    ui->cboPortA_InputType->setCurrentIndex(ui->cboPortA_InputType->findData(DeviceData.PortA.Settings.Digital));
    ui->cboPortB_InputType->setCurrentIndex(ui->cboPortB_InputType->findData(DeviceData.PortB.Settings.Digital));
    // This will validate the input types against our function triggers
    SavePortA_InputType(ui->cboPortA_InputType->currentIndex());
    SavePortB_InputType(ui->cboPortB_InputType->currentIndex());
    // Now we set the data direction
    ui->cboPortADataDirection->setCurrentIndex(ui->cboPortADataDirection->findData(DeviceData.PortA.Settings.dataDirection));
    ui->cboPortBDataDirection->setCurrentIndex(ui->cboPortBDataDirection->findData(DeviceData.PortB.Settings.dataDirection));
    // Now we hide the input type if the data direction is actually an output
    ShowHideInputAType(ui->cboPortADataDirection->currentIndex());
    ShowHideInputBType(ui->cboPortBDataDirection->currentIndex());
    // Validate external I/O selections
    SetupPortAFunctionTrigger(ui->cboPortADataDirection->currentIndex());
    SetupPortBFunctionTrigger(ui->cboPortBDataDirection->currentIndex());


    // Driving tab
    // ---------------------------------------------------------------------------------------------------------->>
    // Driving
    ui->chkEngineAutoStart->setChecked(DeviceData.EngineAutoStart);
    double autostop = DeviceData.EngineAutoStopTime_mS;  // We need to convert mS to Minutes with 1-decimal precision
    autostop /= 60000;
    ui->dspinEngineAutoStop->setValue(autostop);
    ui->spinReverseSpeed->setValue(DeviceData.MaxReverseSpeedPct);
    double secs;    // The following three need to be converted from milliseconds to seconds
    secs = static_cast<double>(DeviceData.TimeToShift_mS) / 1000.0;
    ui->dspinShiftTime->setValue(secs);
    secs = static_cast<double>(DeviceData.TransmissionDelay_mS) / 1000.0;
    ui->dspinTransDelay->setValue(secs);
    secs = static_cast<double>(DeviceData.EnginePauseTime_mS) / 1000.0;
    ui->dspinEngineDelay->setValue(secs);
    ui->spinNudgePercent->setValue(DeviceData.MotorNudgePct);
    ui->spinNudgeTime->setValue(DeviceData.NudgeTime_mS);
    ShowHideNudgeTime(DeviceData.MotorNudgePct);
    // Acceleration/Deceleration
    ui->chkAccelEnable->setChecked(DeviceData.AccelRampEnabled);
    ui->cboAccelPreset->setCurrentIndex(ui->cboAccelPreset->findData(DeviceData.AccelPreset));
    ui->cboAccelLevel->setCurrentIndex(DeviceData.AccelSkipNum - 1);     // Here we set the literal index (-1 because combo is zero-based)
    ui->chkDecelEnable->setChecked(DeviceData.DecelRampEnabled);
    ui->cboDecelPreset->setCurrentIndex(ui->cboDecelPreset->findData(DeviceData.DecelPreset));
    ui->cboDecelLevel->setCurrentIndex(DeviceData.DecelSkipNum -1 );     // Here we set the literal index (-1 because combo is zero-based)
    // Turning
    ui->cboTurnMode->setCurrentIndex(DeviceData.TurnMode - 1);           // Here we set the literal index (-1 because combo is zero-based)
    ui->chkNeutralTurn->setChecked(DeviceData.NeutralTurnAllowed);
    ui->spinNeutralTurnSpeed->setValue(DeviceData.NeutralTurnPct);
    ui->spinHalftrackTurnPct->setValue(DeviceData.HalftrackTreadTurnPct);
    ShowHideNeutralTurnAllowed(ui->cboDriveType->currentIndex());
    // Accelerometer
    ui->chkEnableBarrel->setChecked(DeviceData.EnableBarrelStabilize);
    ui->spinBarrelSensitivity->setValue(DeviceData.BarrelSensitivity);
    ui->chkEnableHills->setChecked(DeviceData.EnableHillPhysics);
    ui->spinHillSensitivity->setValue(DeviceData.HillSensitivity);
    ShowHideBarrelSensitivity(ui->chkEnableBarrel->isChecked());
    ShowHideHillSensitivity(ui->chkEnableHills->isChecked());
    if (DeviceData.TurretElevationMotor == SERVO_PAN) ShowHideBarrelStabilization(true);
    else ShowHideBarrelStabilization(false);

    // Battle tab
    // ---------------------------------------------------------------------------------------------------------->>
    // Custom weight class settings
    ui->spinMaxHits->setValue(DeviceData.CustomClassSettings.maxHits);
    double reload = DeviceData.CustomClassSettings.reloadTime;  // We need to convert milli-seconds to seconds
    reload /= 1000;
    ui->dspinReloadTime->setValue(reload);
    double recover = DeviceData.CustomClassSettings.recoveryTime;   // We need to convert milli-seconds to seconds
    recover /= 1000;
    ui->dspinRecoveryTime->setValue(recover);
    // Cannon IR settings
    ui->cboFireProtocol->setCurrentIndex(ui->cboFireProtocol->findData(DeviceData.IR_FireProtocol));
    SetupIRTeamList(ui->cboFireProtocol->currentIndex());
    ui->cboTeam->setCurrentIndex(ui->cboTeam->findData(DeviceData.IR_Team));
    ui->cboHitProtocol_2->setCurrentIndex(ui->cboHitProtocol_2->findData(DeviceData.IR_HitProtocol_2));
    ui->chkSendTankID->setChecked(DeviceData.SendTankID);
    ui->spinTankID->setValue(DeviceData.TankID);
    // Machine Gun IR settings
    ui->cboMGProtocol->setCurrentIndex(ui->cboMGProtocol->findData(DeviceData.IR_MGProtocol));
    ui->chkUseMG->setChecked(DeviceData.Use_MG_Protocol);
    ui->chkAcceptMG->setChecked(DeviceData.Accept_MG_Damage);
    ui->spinMaxMGHits->setValue(DeviceData.CustomClassSettings.maxMGHits); // Actually part of our custom weight class settings
    // Repair IR settings
    ui->cboRepairProtocol->setCurrentIndex(ui->cboRepairProtocol->findData(DeviceData.IR_RepairProtocol));
    // Damage settings
    ui->cboDamageProfile->setCurrentIndex(ui->cboDamageProfile->findData(DeviceData.DamageProfile));
    SetupSecondaryCannonIR(ui->cboFireProtocol->currentIndex());
    ShowHideCannonIRSettings(ui->cboFireProtocol->currentIndex());
    ShowHideMGIRSettings(ui->cboMGProtocol->currentIndex());
    ShowHideMGHits(ui->chkAcceptMG->isChecked());
    ShowHideOtherBattleSettings(0);  // The paramater passed in this case makes no difference and isn't used
    ShowHideTankIDSettings(ui->chkSendTankID->isChecked());

    // Sound tab
    // ---------------------------------------------------------------------------------------------------------->>
    // Sound device
    ui->cboSoundDevice->setCurrentSoundDevice(DeviceData.SoundDevice);
    // Squeaks
    ui->chkEnableSqueak1->setChecked(DeviceData.Squeak1_Enabled);
    ui->spinSqueak1Min->setValue(DeviceData.Squeak1_MinInterval_mS);
    ui->spinSqueak1Max->setValue(DeviceData.Squeak1_MaxInterval_mS);
    ui->chkEnableSqueak2->setChecked(DeviceData.Squeak2_Enabled);
    ui->spinSqueak2Min->setValue(DeviceData.Squeak2_MinInterval_mS);
    ui->spinSqueak2Max->setValue(DeviceData.Squeak2_MaxInterval_mS);
    ui->chkEnableSqueak3->setChecked(DeviceData.Squeak3_Enabled);
    ui->spinSqueak3Min->setValue(DeviceData.Squeak3_MinInterval_mS);
    ui->spinSqueak3Max->setValue(DeviceData.Squeak3_MaxInterval_mS);
    ui->spinMinSqueakSpeed->setValue(DeviceData.MinSqueakSpeedPct);
    ShowHideOtherSqueakSettings(false); // It doesn't matter what we pass to this function, it won't use the value anyway
    ShowHideSqueak1Settings(ui->chkEnableSqueak1->isChecked());
    ShowHideSqueak2Settings(ui->chkEnableSqueak2->isChecked());
    ShowHideSqueak3Settings(ui->chkEnableSqueak3->isChecked());
    // Other enables
    ui->chkEnableTurretSound->setChecked(DeviceData.TurretSound_Enabled);
    ui->chkEnableHeadlightSound->setChecked(DeviceData.HeadlightSound_Enabled);
    ShowHideHeadlightSoundNote(ui->chkEnableHeadlightSound->isChecked());

    // Misc tab
    // ---------------------------------------------------------------------------------------------------------->>
    // Other Baud Rates
    //ui->cboUSBBaud->setCurrentBaudRate(DeviceData.USBSerialBaud);   // Leaving this fixed for now
    ui->cboMotorSerialBaud->setCurrentBaudRate(DeviceData.MotorSerialBaud);
    ui->cboAuxSerialBaud->setCurrentBaudRate(DeviceData.AuxSerialBaud);
    ui->cboSer3Baud->setCurrentBaudRate(DeviceData.Serial3TxBaud);
    // Low Voltage Cutoff
    ui->chkLVCEnabled->setChecked(DeviceData.LVC_Enabled);
    double LVC = DeviceData.LVC_Cutoff_mV;  // We need to convert mV to Volts with 1-decimal precision
    LVC /= 1000;
    ui->dspinLVCVoltage->setValue(LVC);
    // Debugging
    ui->chkDebug->setChecked(DeviceData.PrintDebug);
}


void MainWindow::Controls_to_Variables(void)
{
    // Radio tab
    // ---------------------------------------------------------------------------------------------------------->>
    // STICKS
    // Channel numbers - add 1 because Index is zero-based
    DeviceData.Sticks.Throttle.Settings.channelNum = ui->cboThrottleChannelNum->currentIndex() + 1;
    DeviceData.Sticks.Turn.Settings.channelNum = ui->cboTurnChannelNum->currentIndex() + 1;
    DeviceData.Sticks.Elevation.Settings.channelNum = ui->cboElevationChannelNum->currentIndex() + 1;
    DeviceData.Sticks.Azimuth.Settings.channelNum = ui->cboAzimuthChannelNum->currentIndex() + 1;
    // Deadband - only applies to stick channels, none on Aux
    DeviceData.Sticks.Throttle.Settings.deadband = ui->spinThrottleDeadband->value();
    DeviceData.Sticks.Turn.Settings.deadband = ui->spinTurnDeadband->value();
    DeviceData.Sticks.Elevation.Settings.deadband = ui->spinElevationDeadband->value();
    DeviceData.Sticks.Azimuth.Settings.deadband = ui->spinAzimuthDeadband->value();
    // Stick reversed
    for (int i=0; i<STICKCHANNELS; i++)
    {
        *ChannelSettings[i].reversed = stickReversedCheck[i]->isChecked();
    }
    // AUX CHANNELS
    for (int i=0; i<AUXCHANNELS; i++)
    {   // Aux channel numbers
        DeviceData.AuxChannel[i].Settings.channelNum = channelOrderCombo[STICKCHANNELS + i]->currentIndex();
        // Aux channel types - save the User Data value, not the index. But we must convert QVariant to boolean
        DeviceData.AuxChannel[i].Settings.Digital = auxTypeCombo[i]->itemData(auxTypeCombo[i]->currentIndex()).toBool();
        // Aux channel number of switch positions (if digital)
        DeviceData.AuxChannel[i].Settings.numPositions = auxSwitchPosCombo[i]->currentText().toUInt();
        // Aux channel reversed settings
        DeviceData.AuxChannel[i].Settings.reversed =  auxReversedCheck[i]->isChecked();
    }

    // STICK & AUX BOTH
    for (int i=0; i<COUNT_OP_CHANNELS; i++)
    {
        *ChannelSettings[i].pulseMin = lblChannelMin[i]->text().toInt();
        *ChannelSettings[i].pulseMax = lblChannelMax[i]->text().toInt();
        // Pulse center is saved to the variable as part of the radio setup routine, and it isn't stored in any control,
        // so we don't need to update the variable here.
        //*ChannelSettings[i].pulseCenter =
    }

    // Motor tab
    // ---------------------------------------------------------------------------------------------------------->>
    // Motor settings
    DeviceData.DriveType = static_cast<DRIVETYPE>(ui->cboDriveType->currentData().toUInt());
    DeviceData.DriveMotors = ui->cboDriveMotors->getCurrentDriveType();
    DeviceData.TurretRotationMotor = ui->cboTurretRotationMotor->getCurrentDriveType();
    DeviceData.TurretElevationMotor = ui->cboTurretElevationMotor->getCurrentDriveType();
    // Mechanical Barrel settings
    DeviceData.MechanicalBarrelWithCannon = ui->chkEnableMechBarrel->isChecked();
    DeviceData.Airsoft = ui->cboMechBarrelType->currentData().toBool();
    DeviceData.RecoilDelay = ui->spinRecoilDelay->value();
    // Recoil Servo settings
    DeviceData.ServoRecoilWithCannon = ui->chkEnableRecoilServo->isChecked();
    DeviceData.RecoilServo_Recoil_mS = ui->spinRecoilTimeToRecoil->value();
    DeviceData.RecoilServo_Return_mS = ui->spinRecoilTimeToReturn->value();
    // Smoker settings - convert 0-100 back to 0-255
    DeviceData.SmokerControlAuto = static_cast<boolean>(ui->cboSmokerControl->currentData().toUInt());
    DeviceData.SmokerMaxSpeed = qRound((static_cast<double>(ui->spinSmokerMax->value())/100.0)*MOTOR_MAX_FWDSPEED_DBL);
    DeviceData.SmokerIdleSpeed = qRound((static_cast<double>(ui->spinSmokerIdle->value())/100.0)*MOTOR_MAX_FWDSPEED_DBL);
    DeviceData.SmokerFastIdleSpeed = qRound((static_cast<double>(ui->spinSmokerFastIdle->value())/100.0)*MOTOR_MAX_FWDSPEED_DBL);

    // Lights & IO tab
    // ---------------------------------------------------------------------------------------------------------->>
    // Brake/Running lights
    DeviceData.BrakesAutoOnAtStop = ui->chkBrakesOnAtStop->isChecked();
    DeviceData.RunningLightsDimLevelPct = ui->spinRunningLightsDimLevel->value();
    DeviceData.RunningLightsAlwaysOn = ui->chkRunningLightsAlwaysOn->isChecked();
    // Machine Gun blinking
    DeviceData.MGLightBlink_mS = ui->spinMGBlink_mS->value();
    // Blink lights if radio signal lost
    DeviceData.FlashLightsWhenSignalLost = ui->chkBlinkSignalLost->isChecked();
    // Aux Output Settings
    DeviceData.AuxLightFlashTime_mS = ui->spinAuxFlash_mS->value();
    DeviceData.AuxLightBlinkOnTime_mS = ui->spinAuxBlinkOn_mS->value();
    DeviceData.AuxLightBlinkOffTime_mS = ui->spinAuxBlinkOff_mS->value();
    DeviceData.AuxLightPresetDim = ui->spinAuxPresetDim->value();
    // High-Intensity Flash Unit
    DeviceData.HiFlashWithCannon = ui->chkHiFlashWithCannon->isChecked();
    // External I/O - Save the user data, not the index, but we must convert the QVariant to UInt/bool
    DeviceData.PortA.Settings.dataDirection = ui->cboPortADataDirection->itemData(ui->cboPortADataDirection->currentIndex()).toUInt();
    DeviceData.PortB.Settings.dataDirection = ui->cboPortBDataDirection->itemData(ui->cboPortBDataDirection->currentIndex()).toUInt();
    DeviceData.PortA.Settings.Digital = ui->cboPortA_InputType->itemData(ui->cboPortA_InputType->currentIndex()).toBool();
    DeviceData.PortB.Settings.Digital = ui->cboPortB_InputType->itemData(ui->cboPortB_InputType->currentIndex()).toBool();

    // Functions tab
    // ---------------------------------------------------------------------------------------------------------->>
    // In this case we are copying not from a literal control, but from our table model, into variables.
    // All we need to save is the Trigger ID and SpecialFunction number, we don't need descriptions on the device.
    // First, clear all variables
    for (int i=0; i<MAX_FUNCTION_TRIGGERS; i++)
    {
        DeviceData.SF_Trigger[i].TriggerID = 0;
        DeviceData.SF_Trigger[i].specialFunction = SF_NULL_FUNCTION;
    }
    // Now add the ones from our model
    QModelIndex index;
    for (int i=0; i<FT_TableModel->rowCount(); i++)
    {
        // Column 0 - Trigger ID
        index = FT_TableModel->index(i, 0, QModelIndex());
            DeviceData.SF_Trigger[i].TriggerID = FT_TableModel->data(index, Qt::DisplayRole).toUInt();
        // Column 1 - Special Function
        index = FT_TableModel->index(i, 1, QModelIndex());
            DeviceData.SF_Trigger[i].specialFunction = static_cast<_special_function>(FT_TableModel->data(index, Qt::DisplayRole).toUInt());
    }
    // Turret stick ignore time - turret movements last less than this time are ignored (quick movement to extremes for special functions)
    DeviceData.IgnoreTurretDelay_mS = ui->spinIgnoreTurretDelay->value();

    // Driving tab
    // ---------------------------------------------------------------------------------------------------------->>
    // Driving
    DeviceData.EngineAutoStart = ui->chkEngineAutoStart->isChecked();
    DeviceData.EngineAutoStopTime_mS = static_cast<int32_t>(ui->dspinEngineAutoStop->value() * 60000.0); // We need to convert minutes to milli-seconds
    DeviceData.MaxReverseSpeedPct = ui->spinReverseSpeed->value();
    // The following three need to be converted from seconds to milliseconds
    DeviceData.TimeToShift_mS = static_cast<uint16_t>(ui->dspinShiftTime->value() * 1000.0);
    DeviceData.TransmissionDelay_mS = static_cast<uint16_t>(ui->dspinTransDelay->value() * 1000.0);
    DeviceData.EnginePauseTime_mS = static_cast<uint16_t>(ui->dspinEngineDelay->value() * 1000.0);
    DeviceData.MotorNudgePct = ui->spinNudgePercent->value();
    DeviceData.NudgeTime_mS = ui->spinNudgeTime->value();
    // Acceleration/Deceleration
    DeviceData.AccelRampEnabled = ui->chkAccelEnable->isChecked();
    DeviceData.AccelPreset = static_cast<ACCEL_DRIVE_PRESET>(ui->cboAccelPreset->itemData(ui->cboAccelPreset->currentIndex()).toUInt());
    DeviceData.AccelSkipNum = ui->cboAccelLevel->currentIndex() + 1;   // Here we save the literal index + 1 (combo is zero-based)
    DeviceData.DecelRampEnabled = ui->chkDecelEnable->isChecked();
    DeviceData.DecelPreset = static_cast<DECEL_DRIVE_PRESET>(ui->cboDecelPreset->itemData(ui->cboDecelPreset->currentIndex()).toUInt());
    DeviceData.DecelSkipNum = ui->cboDecelLevel->currentIndex() + 1;   // Here we save the literal index + 1 (combo is zero-based)
    // Turning
    DeviceData.TurnMode = ui->cboTurnMode->currentIndex() + 1;         // Here we save the literal index + 1 (combo is zero-based)
    DeviceData.NeutralTurnAllowed = ui->chkNeutralTurn->isChecked();
    DeviceData.NeutralTurnPct = ui->spinNeutralTurnSpeed->value();
    DeviceData.HalftrackTreadTurnPct = ui->spinHalftrackTurnPct->value();
    // Accelerometer
    DeviceData.EnableBarrelStabilize = ui->chkEnableBarrel->isChecked();
    DeviceData.BarrelSensitivity = ui->spinBarrelSensitivity->value();
    DeviceData.EnableHillPhysics = ui->chkEnableHills->isChecked();
    DeviceData.HillSensitivity = ui->spinHillSensitivity->value();

    // Battle tab
    // ---------------------------------------------------------------------------------------------------------->>
    // Custom weight class settings
    DeviceData.CustomClassSettings.maxHits = ui->spinMaxHits->value();
    DeviceData.CustomClassSettings.reloadTime = static_cast<uint16_t>(ui->dspinReloadTime->value() * 1000.0); // We need to convert seconds to milli-seconds
    DeviceData.CustomClassSettings.recoveryTime = static_cast<uint16_t>(ui->dspinRecoveryTime->value() * 1000.0); // We need to convert seconds to milli-seconds
    // Cannon IR settings
    DeviceData.IR_FireProtocol = static_cast<IRTYPES>(ui->cboFireProtocol->itemData(ui->cboFireProtocol->currentIndex()).toUInt());
    DeviceData.IR_Team = static_cast<IRTEAMS>(ui->cboTeam->itemData(ui->cboTeam->currentIndex()).toUInt());
    DeviceData.IR_HitProtocol_2 = static_cast<IRTYPES>(ui->cboHitProtocol_2->itemData(ui->cboHitProtocol_2->currentIndex()).toUInt());
    DeviceData.SendTankID = ui->chkSendTankID->isChecked();
    DeviceData.TankID = ui->spinTankID->value();
    // Machine Gun IR settings
    DeviceData.IR_MGProtocol = static_cast<IRTYPES>(ui->cboMGProtocol->itemData(ui->cboMGProtocol->currentIndex()).toUInt());
    DeviceData.Use_MG_Protocol = ui->chkUseMG->isChecked();
    DeviceData.Accept_MG_Damage = ui->chkAcceptMG->isChecked();
    DeviceData.CustomClassSettings.maxMGHits = ui->spinMaxMGHits->value();  // Actually part of our custom weight class
    // Repair IR settings
    DeviceData.IR_RepairProtocol = static_cast<IRTYPES>(ui->cboRepairProtocol->itemData(ui->cboRepairProtocol->currentIndex()).toUInt());
    // Damage Settings
    DeviceData.DamageProfile = static_cast<DAMAGEPROFILES>(ui->cboDamageProfile->itemData(ui->cboDamageProfile->currentIndex()).toUInt());

    // Sound tab
    // ---------------------------------------------------------------------------------------------------------->>
    // Sound device
    DeviceData.SoundDevice = ui->cboSoundDevice->currentData().toUInt();
    // Squeaks
    DeviceData.Squeak1_Enabled = ui->chkEnableSqueak1->isChecked();
    DeviceData.Squeak1_MinInterval_mS = ui->spinSqueak1Min->value();
    DeviceData.Squeak1_MaxInterval_mS = ui->spinSqueak1Max->value();
    DeviceData.Squeak2_Enabled = ui->chkEnableSqueak2->isChecked();
    DeviceData.Squeak2_MinInterval_mS = ui->spinSqueak2Min->value();
    DeviceData.Squeak2_MaxInterval_mS = ui->spinSqueak2Max->value();
    DeviceData.Squeak3_Enabled = ui->chkEnableSqueak3->isChecked();
    DeviceData.Squeak3_MinInterval_mS = ui->spinSqueak3Min->value();
    DeviceData.Squeak3_MaxInterval_mS = ui->spinSqueak3Max->value();
    DeviceData.MinSqueakSpeedPct = ui->spinMinSqueakSpeed->value();
    // Other enables
    DeviceData.TurretSound_Enabled = ui->chkEnableTurretSound->isChecked();
    DeviceData.HeadlightSound_Enabled = ui->chkEnableHeadlightSound->isChecked();

    // Misc tab
    // ---------------------------------------------------------------------------------------------------------->>
    // Other Baud Rates
    //DeviceData.USBSerialBaud = ui->cboUSBBaud->getCurrentBaudRate();  // Leaving this fixed for now
    DeviceData.MotorSerialBaud = ui->cboMotorSerialBaud->getCurrentBaudRate();
    DeviceData.AuxSerialBaud = ui->cboAuxSerialBaud->getCurrentBaudRate();
    DeviceData.Serial3TxBaud = ui->cboSer3Baud->getCurrentBaudRate();
    // Low Voltage Cutoff
    DeviceData.LVC_Enabled = ui->chkLVCEnabled->isChecked();
    DeviceData.LVC_Cutoff_mV = static_cast<uint16_t>(ui->dspinLVCVoltage->value() * 1000.0);  // We need to convert Volts to milliVolts
    // Debugging
    DeviceData.PrintDebug = ui->chkDebug->isChecked();
}



