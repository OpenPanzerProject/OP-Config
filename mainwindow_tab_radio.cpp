#include "mainwindow.h"
#include "ui_mainwindow.h"


//------------------------------------------------------------------------------------------------------------------------>>
// FORM CONTROLS - RADIO TAB - SETUP
//------------------------------------------------------------------------------------------------------------------------>>
void MainWindow::SetupControls_RadioTab(void)
{

    // Initialize these to false
    Flag_StartRadioStream = false;
    Flag_SaveCenterValues = false;
    Flag_SaveMinMaxValues = false;
    Flag_RadioValuesChanged = false;

    // Here we create an array of ChannelSettings struct that point to the individual variables
    // Later this will let us update these channel settings quickly by stepping through the array
    ChannelSettings[0].channelNum = &DeviceData.Sticks.Throttle.Settings.channelNum;
    ChannelSettings[1].channelNum = &DeviceData.Sticks.Turn.Settings.channelNum;
    ChannelSettings[2].channelNum = &DeviceData.Sticks.Elevation.Settings.channelNum;
    ChannelSettings[3].channelNum = &DeviceData.Sticks.Azimuth.Settings.channelNum;
    ChannelSettings[4].channelNum = &DeviceData.AuxChannel[0].Settings.channelNum;
    ChannelSettings[5].channelNum = &DeviceData.AuxChannel[1].Settings.channelNum;
    ChannelSettings[6].channelNum = &DeviceData.AuxChannel[2].Settings.channelNum;
    ChannelSettings[7].channelNum = &DeviceData.AuxChannel[3].Settings.channelNum;
    ChannelSettings[8].channelNum = &DeviceData.AuxChannel[4].Settings.channelNum;
    ChannelSettings[9].channelNum = &DeviceData.AuxChannel[5].Settings.channelNum;
    ChannelSettings[10].channelNum = &DeviceData.AuxChannel[6].Settings.channelNum;
    ChannelSettings[11].channelNum = &DeviceData.AuxChannel[7].Settings.channelNum;
    ChannelSettings[12].channelNum = &DeviceData.AuxChannel[8].Settings.channelNum;
    ChannelSettings[13].channelNum = &DeviceData.AuxChannel[9].Settings.channelNum;
    ChannelSettings[14].channelNum = &DeviceData.AuxChannel[10].Settings.channelNum;
    ChannelSettings[15].channelNum = &DeviceData.AuxChannel[11].Settings.channelNum;

    ChannelSettings[0].pulseMin = &DeviceData.Sticks.Throttle.Settings.pulseMin;
    ChannelSettings[1].pulseMin = &DeviceData.Sticks.Turn.Settings.pulseMin;
    ChannelSettings[2].pulseMin = &DeviceData.Sticks.Elevation.Settings.pulseMin;
    ChannelSettings[3].pulseMin = &DeviceData.Sticks.Azimuth.Settings.pulseMin;
    ChannelSettings[4].pulseMin = &DeviceData.AuxChannel[0].Settings.pulseMin;
    ChannelSettings[5].pulseMin = &DeviceData.AuxChannel[1].Settings.pulseMin;
    ChannelSettings[6].pulseMin = &DeviceData.AuxChannel[2].Settings.pulseMin;
    ChannelSettings[7].pulseMin = &DeviceData.AuxChannel[3].Settings.pulseMin;
    ChannelSettings[8].pulseMin = &DeviceData.AuxChannel[4].Settings.pulseMin;
    ChannelSettings[9].pulseMin = &DeviceData.AuxChannel[5].Settings.pulseMin;
    ChannelSettings[10].pulseMin = &DeviceData.AuxChannel[6].Settings.pulseMin;
    ChannelSettings[11].pulseMin = &DeviceData.AuxChannel[7].Settings.pulseMin;
    ChannelSettings[12].pulseMin = &DeviceData.AuxChannel[8].Settings.pulseMin;
    ChannelSettings[13].pulseMin = &DeviceData.AuxChannel[9].Settings.pulseMin;
    ChannelSettings[14].pulseMin = &DeviceData.AuxChannel[10].Settings.pulseMin;
    ChannelSettings[15].pulseMin = &DeviceData.AuxChannel[11].Settings.pulseMin;

    ChannelSettings[0].pulseMax = &DeviceData.Sticks.Throttle.Settings.pulseMax;
    ChannelSettings[1].pulseMax = &DeviceData.Sticks.Turn.Settings.pulseMax;
    ChannelSettings[2].pulseMax = &DeviceData.Sticks.Elevation.Settings.pulseMax;
    ChannelSettings[3].pulseMax = &DeviceData.Sticks.Azimuth.Settings.pulseMax;
    ChannelSettings[4].pulseMax = &DeviceData.AuxChannel[0].Settings.pulseMax;
    ChannelSettings[5].pulseMax = &DeviceData.AuxChannel[1].Settings.pulseMax;
    ChannelSettings[6].pulseMax = &DeviceData.AuxChannel[2].Settings.pulseMax;
    ChannelSettings[7].pulseMax = &DeviceData.AuxChannel[3].Settings.pulseMax;
    ChannelSettings[8].pulseMax = &DeviceData.AuxChannel[4].Settings.pulseMax;
    ChannelSettings[9].pulseMax = &DeviceData.AuxChannel[5].Settings.pulseMax;
    ChannelSettings[10].pulseMax = &DeviceData.AuxChannel[6].Settings.pulseMax;
    ChannelSettings[11].pulseMax = &DeviceData.AuxChannel[7].Settings.pulseMax;
    ChannelSettings[12].pulseMax = &DeviceData.AuxChannel[8].Settings.pulseMax;
    ChannelSettings[13].pulseMax = &DeviceData.AuxChannel[9].Settings.pulseMax;
    ChannelSettings[14].pulseMax = &DeviceData.AuxChannel[10].Settings.pulseMax;
    ChannelSettings[15].pulseMax = &DeviceData.AuxChannel[11].Settings.pulseMax;

    ChannelSettings[0].pulseCenter = &DeviceData.Sticks.Throttle.Settings.pulseCenter;
    ChannelSettings[1].pulseCenter = &DeviceData.Sticks.Turn.Settings.pulseCenter;
    ChannelSettings[2].pulseCenter = &DeviceData.Sticks.Elevation.Settings.pulseCenter;
    ChannelSettings[3].pulseCenter = &DeviceData.Sticks.Azimuth.Settings.pulseCenter;
    ChannelSettings[4].pulseCenter = &DeviceData.AuxChannel[0].Settings.pulseCenter;
    ChannelSettings[5].pulseCenter = &DeviceData.AuxChannel[1].Settings.pulseCenter;
    ChannelSettings[6].pulseCenter = &DeviceData.AuxChannel[2].Settings.pulseCenter;
    ChannelSettings[7].pulseCenter = &DeviceData.AuxChannel[3].Settings.pulseCenter;
    ChannelSettings[8].pulseCenter = &DeviceData.AuxChannel[4].Settings.pulseCenter;
    ChannelSettings[9].pulseCenter = &DeviceData.AuxChannel[5].Settings.pulseCenter;
    ChannelSettings[10].pulseCenter = &DeviceData.AuxChannel[6].Settings.pulseCenter;
    ChannelSettings[11].pulseCenter = &DeviceData.AuxChannel[7].Settings.pulseCenter;
    ChannelSettings[12].pulseCenter = &DeviceData.AuxChannel[8].Settings.pulseCenter;
    ChannelSettings[13].pulseCenter = &DeviceData.AuxChannel[9].Settings.pulseCenter;
    ChannelSettings[14].pulseCenter = &DeviceData.AuxChannel[10].Settings.pulseCenter;
    ChannelSettings[15].pulseCenter = &DeviceData.AuxChannel[11].Settings.pulseCenter;

    ChannelSettings[0].pulse = &DeviceData.Sticks.Throttle.pulse;
    ChannelSettings[1].pulse = &DeviceData.Sticks.Turn.pulse;
    ChannelSettings[2].pulse = &DeviceData.Sticks.Elevation.pulse;
    ChannelSettings[3].pulse = &DeviceData.Sticks.Azimuth.pulse;
    ChannelSettings[4].pulse = &DeviceData.AuxChannel[0].pulse;
    ChannelSettings[5].pulse = &DeviceData.AuxChannel[1].pulse;
    ChannelSettings[6].pulse = &DeviceData.AuxChannel[2].pulse;
    ChannelSettings[7].pulse = &DeviceData.AuxChannel[3].pulse;
    ChannelSettings[8].pulse = &DeviceData.AuxChannel[4].pulse;
    ChannelSettings[9].pulse = &DeviceData.AuxChannel[5].pulse;
    ChannelSettings[10].pulse = &DeviceData.AuxChannel[6].pulse;
    ChannelSettings[11].pulse = &DeviceData.AuxChannel[7].pulse;
    ChannelSettings[12].pulse = &DeviceData.AuxChannel[8].pulse;
    ChannelSettings[13].pulse = &DeviceData.AuxChannel[9].pulse;
    ChannelSettings[14].pulse = &DeviceData.AuxChannel[10].pulse;
    ChannelSettings[15].pulse = &DeviceData.AuxChannel[11].pulse;

    ChannelSettings[0].reversed = &DeviceData.Sticks.Throttle.Settings.reversed;
    ChannelSettings[1].reversed = &DeviceData.Sticks.Turn.Settings.reversed;
    ChannelSettings[2].reversed = &DeviceData.Sticks.Elevation.Settings.reversed;
    ChannelSettings[3].reversed = &DeviceData.Sticks.Azimuth.Settings.reversed;
    ChannelSettings[4].reversed = &DeviceData.AuxChannel[0].Settings.reversed;
    ChannelSettings[5].reversed = &DeviceData.AuxChannel[1].Settings.reversed;
    ChannelSettings[6].reversed = &DeviceData.AuxChannel[2].Settings.reversed;
    ChannelSettings[7].reversed = &DeviceData.AuxChannel[3].Settings.reversed;
    ChannelSettings[8].reversed = &DeviceData.AuxChannel[4].Settings.reversed;
    ChannelSettings[9].reversed = &DeviceData.AuxChannel[5].Settings.reversed;
    ChannelSettings[10].reversed = &DeviceData.AuxChannel[6].Settings.reversed;
    ChannelSettings[11].reversed = &DeviceData.AuxChannel[7].Settings.reversed;
    ChannelSettings[12].reversed = &DeviceData.AuxChannel[8].Settings.reversed;
    ChannelSettings[13].reversed = &DeviceData.AuxChannel[9].Settings.reversed;
    ChannelSettings[14].reversed = &DeviceData.AuxChannel[10].Settings.reversed;
    ChannelSettings[15].reversed = &DeviceData.AuxChannel[11].Settings.reversed;

    ChannelSettings[0].deadband = &DeviceData.Sticks.Throttle.Settings.deadband;
    ChannelSettings[1].deadband = &DeviceData.Sticks.Turn.Settings.deadband;
    ChannelSettings[2].deadband = &DeviceData.Sticks.Elevation.Settings.deadband;
    ChannelSettings[3].deadband = &DeviceData.Sticks.Azimuth.Settings.deadband;
    // There is no deadband setting for aux channels...

    // Now we create an array of form objects
    highSlider[0] = ui->sliderThrottleHigh;
    highSlider[1] = ui->sliderSteeringHigh;
    highSlider[2] = ui->sliderElevationHigh;
    highSlider[3] = ui->sliderRotationHigh;
    highSlider[4] = ui->sliderAux1High;
    highSlider[5] = ui->sliderAux2High;
    highSlider[6] = ui->sliderAux3High;
    highSlider[7] = ui->sliderAux4High;
    highSlider[8] = ui->sliderAux5High;
    highSlider[9] = ui->sliderAux6High;
    highSlider[10] = ui->sliderAux7High;
    highSlider[11] = ui->sliderAux8High;
    highSlider[12] = ui->sliderAux9High;
    highSlider[13] = ui->sliderAux10High;
    highSlider[14] = ui->sliderAux11High;
    highSlider[15] = ui->sliderAux12High;

    lowSlider[0] = ui->sliderThrottleLow;
    lowSlider[1] = ui->sliderSteeringLow;
    lowSlider[2] = ui->sliderElevationLow;
    lowSlider[3] = ui->sliderRotationLow;
    lowSlider[4] = ui->sliderAux1Low;
    lowSlider[5] = ui->sliderAux2Low;
    lowSlider[6] = ui->sliderAux3Low;
    lowSlider[7] = ui->sliderAux4Low;
    lowSlider[8] = ui->sliderAux5Low;
    lowSlider[9] = ui->sliderAux6Low;
    lowSlider[10] = ui->sliderAux7Low;
    lowSlider[11] = ui->sliderAux8Low;
    lowSlider[12] = ui->sliderAux9Low;
    lowSlider[13] = ui->sliderAux10Low;
    lowSlider[14] = ui->sliderAux11Low;
    lowSlider[15] = ui->sliderAux12Low;


    lblChannelMin[0] = ui->lblThrottleMin;
    lblChannelMin[1] = ui->lblSteeringMin;
    lblChannelMin[2] = ui->lblElevationMin;
    lblChannelMin[3] = ui->lblRotationMin;
    lblChannelMin[4] = ui->lblAux1Min;
    lblChannelMin[5] = ui->lblAux2Min;
    lblChannelMin[6] = ui->lblAux3Min;
    lblChannelMin[7] = ui->lblAux4Min;
    lblChannelMin[8] = ui->lblAux5Min;
    lblChannelMin[9] = ui->lblAux6Min;
    lblChannelMin[10] = ui->lblAux7Min;
    lblChannelMin[11] = ui->lblAux8Min;
    lblChannelMin[12] = ui->lblAux9Min;
    lblChannelMin[13] = ui->lblAux10Min;
    lblChannelMin[14] = ui->lblAux11Min;
    lblChannelMin[15] = ui->lblAux12Min;

    lblChannelMax[0] = ui->lblThrottleMax;
    lblChannelMax[1] = ui->lblSteeringMax;
    lblChannelMax[2] = ui->lblElevationMax;
    lblChannelMax[3] = ui->lblRotationMax;
    lblChannelMax[4] = ui->lblAux1Max;
    lblChannelMax[5] = ui->lblAux2Max;
    lblChannelMax[6] = ui->lblAux3Max;
    lblChannelMax[7] = ui->lblAux4Max;
    lblChannelMax[8] = ui->lblAux5Max;
    lblChannelMax[9] = ui->lblAux6Max;
    lblChannelMax[10] = ui->lblAux7Max;
    lblChannelMax[11] = ui->lblAux8Max;
    lblChannelMax[12] = ui->lblAux9Max;
    lblChannelMax[13] = ui->lblAux10Max;
    lblChannelMax[14] = ui->lblAux11Max;
    lblChannelMax[15] = ui->lblAux12Max;

    lblChannelPulse[0] = ui->lblThrottlePulse;
    lblChannelPulse[1] = ui->lblSteeringPulse;
    lblChannelPulse[2] = ui->lblElevationPulse;
    lblChannelPulse[3] = ui->lblRotationPulse;
    lblChannelPulse[4] = ui->lblAux1Pulse;
    lblChannelPulse[5] = ui->lblAux2Pulse;
    lblChannelPulse[6] = ui->lblAux3Pulse;
    lblChannelPulse[7] = ui->lblAux4Pulse;
    lblChannelPulse[8] = ui->lblAux5Pulse;
    lblChannelPulse[9] = ui->lblAux6Pulse;
    lblChannelPulse[10] = ui->lblAux7Pulse;
    lblChannelPulse[11] = ui->lblAux8Pulse;
    lblChannelPulse[12] = ui->lblAux9Pulse;
    lblChannelPulse[13] = ui->lblAux10Pulse;
    lblChannelPulse[14] = ui->lblAux11Pulse;
    lblChannelPulse[15] = ui->lblAux12Pulse;

    lblChannelPosition[0] = ui->lblThrottleDirection;
    lblChannelPosition[1] = ui->lblSteeringDirection;
    lblChannelPosition[2] = ui->lblElevationDirection;
    lblChannelPosition[3] = ui->lblRotationDirection;
    lblChannelPosition[4] = ui->lblAux1Pos;
    lblChannelPosition[5] = ui->lblAux2Pos;
    lblChannelPosition[6] = ui->lblAux3Pos;
    lblChannelPosition[7] = ui->lblAux4Pos;
    lblChannelPosition[8] = ui->lblAux5Pos;
    lblChannelPosition[9] = ui->lblAux6Pos;
    lblChannelPosition[10] = ui->lblAux7Pos;
    lblChannelPosition[11] = ui->lblAux8Pos;
    lblChannelPosition[12] = ui->lblAux9Pos;
    lblChannelPosition[13] = ui->lblAux10Pos;
    lblChannelPosition[14] = ui->lblAux11Pos;
    lblChannelPosition[15] = ui->lblAux12Pos;

    // Apply css to the sliders
    QFile file(":/css/channelsliderhigh.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        for (int i=0; i<COUNT_OP_CHANNELS; i++ )
        {
            highSlider[i]->setStyleSheet(file.readAll());
            file.seek(0);   // Return to beginning of file
        }
        file.close();
    }
    QFile file2(":/css/channelsliderlow.qss");
    if(file2.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        for (int i=0; i<COUNT_OP_CHANNELS; i++ )
        {
            lowSlider[i]->setStyleSheet(file2.readAll());
            file2.seek(0);  // Return to beginning of file
        }
        file2.close();
    }

    // Populate the channel order combos. We pass true/false if this is an aux channel or not
    ui->cboThrottleChannelNum->setup(false);
    ui->cboTurnChannelNum->setup(false);
    ui->cboElevationChannelNum->setup(false);
    ui->cboAzimuthChannelNum->setup(false);
    ui->cboAux1ChannelNum->setup(true);
    ui->cboAux2ChannelNum->setup(true);
    ui->cboAux3ChannelNum->setup(true);
    ui->cboAux4ChannelNum->setup(true);
    ui->cboAux5ChannelNum->setup(true);
    ui->cboAux6ChannelNum->setup(true);
    ui->cboAux7ChannelNum->setup(true);
    ui->cboAux8ChannelNum->setup(true);
    ui->cboAux9ChannelNum->setup(true);
    ui->cboAux10ChannelNum->setup(true);
    ui->cboAux11ChannelNum->setup(true);
    ui->cboAux12ChannelNum->setup(true);
    // Also create an array of these boxes so we can quickly do calculations on all of them in a loop
    channelOrderCombo[0] = ui->cboThrottleChannelNum;
    channelOrderCombo[1] = ui->cboTurnChannelNum;
    channelOrderCombo[2] = ui->cboElevationChannelNum;
    channelOrderCombo[3] = ui->cboAzimuthChannelNum;
    channelOrderCombo[4] = ui->cboAux1ChannelNum;
    channelOrderCombo[5] = ui->cboAux2ChannelNum;
    channelOrderCombo[6] = ui->cboAux3ChannelNum;
    channelOrderCombo[7] = ui->cboAux4ChannelNum;
    channelOrderCombo[8] = ui->cboAux5ChannelNum;
    channelOrderCombo[9] = ui->cboAux6ChannelNum;
    channelOrderCombo[10] = ui->cboAux7ChannelNum;
    channelOrderCombo[11] = ui->cboAux8ChannelNum;
    channelOrderCombo[12] = ui->cboAux9ChannelNum;
    channelOrderCombo[13] = ui->cboAux10ChannelNum;
    channelOrderCombo[14] = ui->cboAux11ChannelNum;
    channelOrderCombo[15] = ui->cboAux12ChannelNum;

    // Array of aux channel types (analog or digital). These boxes have been promoted to AnalogDigitalComboBox-es,
    // the values are filled in automatically on creation
    auxTypeCombo[0] = ui->cboAux1Type;
    auxTypeCombo[1] = ui->cboAux2Type;
    auxTypeCombo[2] = ui->cboAux3Type;
    auxTypeCombo[3] = ui->cboAux4Type;
    auxTypeCombo[4] = ui->cboAux5Type;
    auxTypeCombo[5] = ui->cboAux6Type;
    auxTypeCombo[6] = ui->cboAux7Type;
    auxTypeCombo[7] = ui->cboAux8Type;
    auxTypeCombo[8] = ui->cboAux9Type;
    auxTypeCombo[9] = ui->cboAux10Type;
    auxTypeCombo[10] = ui->cboAux11Type;
    auxTypeCombo[11] = ui->cboAux12Type;

    // Array of aux channel switch positions, these are of type AuxChannelPositionsCombo
    auxSwitchPosCombo[0] = ui->cboAux1NumSwitchPos;
    auxSwitchPosCombo[1] = ui->cboAux2NumSwitchPos;
    auxSwitchPosCombo[2] = ui->cboAux3NumSwitchPos;
    auxSwitchPosCombo[3] = ui->cboAux4NumSwitchPos;
    auxSwitchPosCombo[4] = ui->cboAux5NumSwitchPos;
    auxSwitchPosCombo[5] = ui->cboAux6NumSwitchPos;
    auxSwitchPosCombo[6] = ui->cboAux7NumSwitchPos;
    auxSwitchPosCombo[7] = ui->cboAux8NumSwitchPos;
    auxSwitchPosCombo[8] = ui->cboAux9NumSwitchPos;
    auxSwitchPosCombo[9] = ui->cboAux10NumSwitchPos;
    auxSwitchPosCombo[10] = ui->cboAux11NumSwitchPos;
    auxSwitchPosCombo[11] = ui->cboAux12NumSwitchPos;

    // Array of stick channel reversed settings
    stickReversedCheck[0] = ui->chkThrottleReversed;
    stickReversedCheck[1] = ui->chkTurnReversed;
    stickReversedCheck[2] = ui->chkElevationReversed;
    stickReversedCheck[3] = ui->chkRotationReversed;

    // Array of aux channel reversed settings
    auxReversedCheck[0] = ui->chkAux1_Reversed;
    auxReversedCheck[1] = ui->chkAux2_Reversed;
    auxReversedCheck[2] = ui->chkAux3_Reversed;
    auxReversedCheck[3] = ui->chkAux4_Reversed;
    auxReversedCheck[4] = ui->chkAux5_Reversed;
    auxReversedCheck[5] = ui->chkAux6_Reversed;
    auxReversedCheck[6] = ui->chkAux7_Reversed;
    auxReversedCheck[7] = ui->chkAux8_Reversed;
    auxReversedCheck[8] = ui->chkAux9_Reversed;
    auxReversedCheck[9] = ui->chkAux10_Reversed;
    auxReversedCheck[10] = ui->chkAux11_Reversed;
    auxReversedCheck[11] = ui->chkAux12_Reversed;

    // Signals and slots
    // Save information when any aux channel number is changed, and enable/disable the channel type and position-count combos as required
    // This is some extremely tricky stuff. I don't want to mess with six different slots for the six different aux channel combos,
    // but I don't have an easy way to pass the aux channel number to the slot. QSignalMapper alas only works with parameter-less signals,
    // otherwise I could use that. But I want to pass the new paramater channel number in *addition* to the existing parameters of the signal
    // There is a way that works by some kind of C++ lambda shit, don't ask me what it means, but this amazingly does work.
    // The only thing is I can't create these signals in a loop, but that is a small price to pay for replacing six slots with 1
    // And - it only seems to work on custom signals emitted from a subclassed version, not QComboBox directly
    connect(ui->cboThrottleChannelNum, &ChannelOrderComboBox::channelNumberChanged, [this](const QString &oldChannel, const QString &newChannel, ChannelOrderComboBox* changedCombo) {SaveChannelNum(oldChannel, newChannel, changedCombo, 0);});
    connect(ui->cboTurnChannelNum, &ChannelOrderComboBox::channelNumberChanged, [this](const QString &oldChannel, const QString &newChannel, ChannelOrderComboBox* changedCombo) {SaveChannelNum(oldChannel, newChannel, changedCombo, 1);});
    connect(ui->cboElevationChannelNum, &ChannelOrderComboBox::channelNumberChanged, [this](const QString &oldChannel, const QString &newChannel, ChannelOrderComboBox* changedCombo) {SaveChannelNum(oldChannel, newChannel, changedCombo, 2);});
    connect(ui->cboAzimuthChannelNum, &ChannelOrderComboBox::channelNumberChanged, [this](const QString &oldChannel, const QString &newChannel, ChannelOrderComboBox* changedCombo) {SaveChannelNum(oldChannel, newChannel, changedCombo, 3);});
    connect(ui->cboAux1ChannelNum, &ChannelOrderComboBox::channelNumberChanged, [this](const QString &oldChannel, const QString &newChannel, ChannelOrderComboBox* changedCombo) {SaveChannelNum(oldChannel, newChannel, changedCombo, 0);});
    connect(ui->cboAux2ChannelNum, &ChannelOrderComboBox::channelNumberChanged, [this](const QString &oldChannel, const QString &newChannel, ChannelOrderComboBox* changedCombo) {SaveChannelNum(oldChannel, newChannel, changedCombo, 1);});
    connect(ui->cboAux3ChannelNum, &ChannelOrderComboBox::channelNumberChanged, [this](const QString &oldChannel, const QString &newChannel, ChannelOrderComboBox* changedCombo) {SaveChannelNum(oldChannel, newChannel, changedCombo, 2);});
    connect(ui->cboAux4ChannelNum, &ChannelOrderComboBox::channelNumberChanged, [this](const QString &oldChannel, const QString &newChannel, ChannelOrderComboBox* changedCombo) {SaveChannelNum(oldChannel, newChannel, changedCombo, 3);});
    connect(ui->cboAux5ChannelNum, &ChannelOrderComboBox::channelNumberChanged, [this](const QString &oldChannel, const QString &newChannel, ChannelOrderComboBox* changedCombo) {SaveChannelNum(oldChannel, newChannel, changedCombo, 4);});
    connect(ui->cboAux6ChannelNum, &ChannelOrderComboBox::channelNumberChanged, [this](const QString &oldChannel, const QString &newChannel, ChannelOrderComboBox* changedCombo) {SaveChannelNum(oldChannel, newChannel, changedCombo, 5);});
    connect(ui->cboAux7ChannelNum, &ChannelOrderComboBox::channelNumberChanged, [this](const QString &oldChannel, const QString &newChannel, ChannelOrderComboBox* changedCombo) {SaveChannelNum(oldChannel, newChannel, changedCombo, 6);});
    connect(ui->cboAux8ChannelNum, &ChannelOrderComboBox::channelNumberChanged, [this](const QString &oldChannel, const QString &newChannel, ChannelOrderComboBox* changedCombo) {SaveChannelNum(oldChannel, newChannel, changedCombo, 7);});
    connect(ui->cboAux9ChannelNum, &ChannelOrderComboBox::channelNumberChanged, [this](const QString &oldChannel, const QString &newChannel, ChannelOrderComboBox* changedCombo) {SaveChannelNum(oldChannel, newChannel, changedCombo, 8);});
    connect(ui->cboAux10ChannelNum, &ChannelOrderComboBox::channelNumberChanged, [this](const QString &oldChannel, const QString &newChannel, ChannelOrderComboBox* changedCombo) {SaveChannelNum(oldChannel, newChannel, changedCombo, 9);});
    connect(ui->cboAux11ChannelNum, &ChannelOrderComboBox::channelNumberChanged, [this](const QString &oldChannel, const QString &newChannel, ChannelOrderComboBox* changedCombo) {SaveChannelNum(oldChannel, newChannel, changedCombo, 10);});
    connect(ui->cboAux12ChannelNum, &ChannelOrderComboBox::channelNumberChanged, [this](const QString &oldChannel, const QString &newChannel, ChannelOrderComboBox* changedCombo) {SaveChannelNum(oldChannel, newChannel, changedCombo, 11);});

    // I said above it only seems to work with promoted objects, but here I was able to do it from a regular QCheckbox.
    // I think the issue is that you can't use an overloaded signal, there must only be a single definition for the signal paramater(s)
    // This just updates the variable each time any of the reversed checkboxes is toggled.
    connect(ui->chkThrottleReversed, &QCheckBox::toggled, [this](bool isChecked) {SaveChannelReversed(isChecked, 0);});
    connect(ui->chkTurnReversed, &QCheckBox::toggled, [this](bool isChecked) {SaveChannelReversed(isChecked, 1);});
    connect(ui->chkElevationReversed, &QCheckBox::toggled, [this](bool isChecked) {SaveChannelReversed(isChecked, 2);});
    connect(ui->chkRotationReversed, &QCheckBox::toggled, [this](bool isChecked) {SaveChannelReversed(isChecked, 3);});
    connect(ui->chkAux1_Reversed, &QCheckBox::toggled, [this](bool isChecked) {SaveChannelReversed(isChecked, 4);});
    connect(ui->chkAux2_Reversed, &QCheckBox::toggled, [this](bool isChecked) {SaveChannelReversed(isChecked, 5);});
    connect(ui->chkAux3_Reversed, &QCheckBox::toggled, [this](bool isChecked) {SaveChannelReversed(isChecked, 6);});
    connect(ui->chkAux4_Reversed, &QCheckBox::toggled, [this](bool isChecked) {SaveChannelReversed(isChecked, 7);});
    connect(ui->chkAux5_Reversed, &QCheckBox::toggled, [this](bool isChecked) {SaveChannelReversed(isChecked, 8);});
    connect(ui->chkAux6_Reversed, &QCheckBox::toggled, [this](bool isChecked) {SaveChannelReversed(isChecked, 9);});
    connect(ui->chkAux7_Reversed, &QCheckBox::toggled, [this](bool isChecked) {SaveChannelReversed(isChecked, 10);});
    connect(ui->chkAux8_Reversed, &QCheckBox::toggled, [this](bool isChecked) {SaveChannelReversed(isChecked, 11);});
    connect(ui->chkAux9_Reversed, &QCheckBox::toggled, [this](bool isChecked) {SaveChannelReversed(isChecked, 12);});
    connect(ui->chkAux10_Reversed, &QCheckBox::toggled, [this](bool isChecked) {SaveChannelReversed(isChecked, 13);});
    connect(ui->chkAux11_Reversed, &QCheckBox::toggled, [this](bool isChecked) {SaveChannelReversed(isChecked, 14);});
    connect(ui->chkAux12_Reversed, &QCheckBox::toggled, [this](bool isChecked) {SaveChannelReversed(isChecked, 15);});

    // Save the deadband whenever it is changed. This one doesn't work because valueChanged is overloaded to return either an
    // int or a QString, and I guess this only works if it is singular. I could create a whole new class for these four spin boxes,
    // but instead just make 4 slots.
    //connect(ui->spinThrottleDeadband, &QSpinBox::valueChanged, [this](int whatVal) {SaveDeadband(whatVal, 0);});
    connect(ui->spinThrottleDeadband, SIGNAL(valueChanged(int)), this, SLOT(SaveThrottleDeadband(int)));
    connect(ui->spinTurnDeadband, SIGNAL(valueChanged(int)), this, SLOT(SaveTurnDeadband(int)));
    connect(ui->spinElevationDeadband, SIGNAL(valueChanged(int)), this, SLOT(SaveElevationDeadband(int)));
    connect(ui->spinAzimuthDeadband, SIGNAL(valueChanged(int)), this, SLOT(SaveAzimuthDeadband(int)));

    // Save information when any aux channel type is changed, and enable/disable the position-count combo as required
    connect(ui->cboAux1Type, &AnalogDigitalComboBox::analogDigitalChanged, [this](AnalogDigitalComboBox* changedCombo) {SaveAuxChannelType(changedCombo, 0);});
    connect(ui->cboAux2Type, &AnalogDigitalComboBox::analogDigitalChanged, [this](AnalogDigitalComboBox* changedCombo) {SaveAuxChannelType(changedCombo, 1);});
    connect(ui->cboAux3Type, &AnalogDigitalComboBox::analogDigitalChanged, [this](AnalogDigitalComboBox* changedCombo) {SaveAuxChannelType(changedCombo, 2);});
    connect(ui->cboAux4Type, &AnalogDigitalComboBox::analogDigitalChanged, [this](AnalogDigitalComboBox* changedCombo) {SaveAuxChannelType(changedCombo, 3);});
    connect(ui->cboAux5Type, &AnalogDigitalComboBox::analogDigitalChanged, [this](AnalogDigitalComboBox* changedCombo) {SaveAuxChannelType(changedCombo, 4);});
    connect(ui->cboAux6Type, &AnalogDigitalComboBox::analogDigitalChanged, [this](AnalogDigitalComboBox* changedCombo) {SaveAuxChannelType(changedCombo, 5);});
    connect(ui->cboAux7Type, &AnalogDigitalComboBox::analogDigitalChanged, [this](AnalogDigitalComboBox* changedCombo) {SaveAuxChannelType(changedCombo, 6);});
    connect(ui->cboAux8Type, &AnalogDigitalComboBox::analogDigitalChanged, [this](AnalogDigitalComboBox* changedCombo) {SaveAuxChannelType(changedCombo, 7);});
    connect(ui->cboAux9Type, &AnalogDigitalComboBox::analogDigitalChanged, [this](AnalogDigitalComboBox* changedCombo) {SaveAuxChannelType(changedCombo, 8);});
    connect(ui->cboAux10Type,&AnalogDigitalComboBox::analogDigitalChanged, [this](AnalogDigitalComboBox* changedCombo) {SaveAuxChannelType(changedCombo, 9);});
    connect(ui->cboAux11Type,&AnalogDigitalComboBox::analogDigitalChanged, [this](AnalogDigitalComboBox* changedCombo) {SaveAuxChannelType(changedCombo, 10);});
    connect(ui->cboAux12Type,&AnalogDigitalComboBox::analogDigitalChanged, [this](AnalogDigitalComboBox* changedCombo) {SaveAuxChannelType(changedCombo, 11);});

    // Save information when any aux channel position-counts are changed
    connect(ui->cboAux1NumSwitchPos, &AuxChannelPositionsCombo::AuxChannelPositionChanged, [this](AuxChannelPositionsCombo* changedCombo) {SaveAuxChannelPositions(changedCombo, 0);});
    connect(ui->cboAux2NumSwitchPos, &AuxChannelPositionsCombo::AuxChannelPositionChanged, [this](AuxChannelPositionsCombo* changedCombo) {SaveAuxChannelPositions(changedCombo, 1);});
    connect(ui->cboAux3NumSwitchPos, &AuxChannelPositionsCombo::AuxChannelPositionChanged, [this](AuxChannelPositionsCombo* changedCombo) {SaveAuxChannelPositions(changedCombo, 2);});
    connect(ui->cboAux4NumSwitchPos, &AuxChannelPositionsCombo::AuxChannelPositionChanged, [this](AuxChannelPositionsCombo* changedCombo) {SaveAuxChannelPositions(changedCombo, 3);});
    connect(ui->cboAux5NumSwitchPos, &AuxChannelPositionsCombo::AuxChannelPositionChanged, [this](AuxChannelPositionsCombo* changedCombo) {SaveAuxChannelPositions(changedCombo, 4);});
    connect(ui->cboAux6NumSwitchPos, &AuxChannelPositionsCombo::AuxChannelPositionChanged, [this](AuxChannelPositionsCombo* changedCombo) {SaveAuxChannelPositions(changedCombo, 5);});
    connect(ui->cboAux7NumSwitchPos, &AuxChannelPositionsCombo::AuxChannelPositionChanged, [this](AuxChannelPositionsCombo* changedCombo) {SaveAuxChannelPositions(changedCombo, 6);});
    connect(ui->cboAux8NumSwitchPos, &AuxChannelPositionsCombo::AuxChannelPositionChanged, [this](AuxChannelPositionsCombo* changedCombo) {SaveAuxChannelPositions(changedCombo, 7);});
    connect(ui->cboAux9NumSwitchPos, &AuxChannelPositionsCombo::AuxChannelPositionChanged, [this](AuxChannelPositionsCombo* changedCombo) {SaveAuxChannelPositions(changedCombo, 8);});
    connect(ui->cboAux10NumSwitchPos,&AuxChannelPositionsCombo::AuxChannelPositionChanged, [this](AuxChannelPositionsCombo* changedCombo) {SaveAuxChannelPositions(changedCombo, 9);});
    connect(ui->cboAux11NumSwitchPos,&AuxChannelPositionsCombo::AuxChannelPositionChanged, [this](AuxChannelPositionsCombo* changedCombo) {SaveAuxChannelPositions(changedCombo, 10);});
    connect(ui->cboAux12NumSwitchPos,&AuxChannelPositionsCombo::AuxChannelPositionChanged, [this](AuxChannelPositionsCombo* changedCombo) {SaveAuxChannelPositions(changedCombo, 11);});

    // ChannelOrderComboBoxes have a custom signal, we connect all of them to the ValidateChannelOrder slot
    // This is to prevent the user from assigning the same channel number to more than one channel
    connect(ui->cboThrottleChannelNum,  SIGNAL(channelNumberChanged(QString,QString,ChannelOrderComboBox*)), this, SLOT(ValidateChannelOrder(QString,QString,ChannelOrderComboBox*)));
    connect(ui->cboTurnChannelNum,      SIGNAL(channelNumberChanged(QString,QString,ChannelOrderComboBox*)), this, SLOT(ValidateChannelOrder(QString,QString,ChannelOrderComboBox*)));
    connect(ui->cboElevationChannelNum, SIGNAL(channelNumberChanged(QString,QString,ChannelOrderComboBox*)), this, SLOT(ValidateChannelOrder(QString,QString,ChannelOrderComboBox*)));
    connect(ui->cboAzimuthChannelNum,   SIGNAL(channelNumberChanged(QString,QString,ChannelOrderComboBox*)), this, SLOT(ValidateChannelOrder(QString,QString,ChannelOrderComboBox*)));
    connect(ui->cboAux1ChannelNum,      SIGNAL(channelNumberChanged(QString,QString,ChannelOrderComboBox*)), this, SLOT(ValidateChannelOrder(QString,QString,ChannelOrderComboBox*)));
    connect(ui->cboAux2ChannelNum,      SIGNAL(channelNumberChanged(QString,QString,ChannelOrderComboBox*)), this, SLOT(ValidateChannelOrder(QString,QString,ChannelOrderComboBox*)));
    connect(ui->cboAux3ChannelNum,      SIGNAL(channelNumberChanged(QString,QString,ChannelOrderComboBox*)), this, SLOT(ValidateChannelOrder(QString,QString,ChannelOrderComboBox*)));
    connect(ui->cboAux4ChannelNum,      SIGNAL(channelNumberChanged(QString,QString,ChannelOrderComboBox*)), this, SLOT(ValidateChannelOrder(QString,QString,ChannelOrderComboBox*)));
    connect(ui->cboAux5ChannelNum,      SIGNAL(channelNumberChanged(QString,QString,ChannelOrderComboBox*)), this, SLOT(ValidateChannelOrder(QString,QString,ChannelOrderComboBox*)));
    connect(ui->cboAux6ChannelNum,      SIGNAL(channelNumberChanged(QString,QString,ChannelOrderComboBox*)), this, SLOT(ValidateChannelOrder(QString,QString,ChannelOrderComboBox*)));
    connect(ui->cboAux7ChannelNum,      SIGNAL(channelNumberChanged(QString,QString,ChannelOrderComboBox*)), this, SLOT(ValidateChannelOrder(QString,QString,ChannelOrderComboBox*)));
    connect(ui->cboAux8ChannelNum,      SIGNAL(channelNumberChanged(QString,QString,ChannelOrderComboBox*)), this, SLOT(ValidateChannelOrder(QString,QString,ChannelOrderComboBox*)));
    connect(ui->cboAux9ChannelNum,      SIGNAL(channelNumberChanged(QString,QString,ChannelOrderComboBox*)), this, SLOT(ValidateChannelOrder(QString,QString,ChannelOrderComboBox*)));
    connect(ui->cboAux10ChannelNum,     SIGNAL(channelNumberChanged(QString,QString,ChannelOrderComboBox*)), this, SLOT(ValidateChannelOrder(QString,QString,ChannelOrderComboBox*)));
    connect(ui->cboAux11ChannelNum,     SIGNAL(channelNumberChanged(QString,QString,ChannelOrderComboBox*)), this, SLOT(ValidateChannelOrder(QString,QString,ChannelOrderComboBox*)));
    connect(ui->cboAux12ChannelNum,     SIGNAL(channelNumberChanged(QString,QString,ChannelOrderComboBox*)), this, SLOT(ValidateChannelOrder(QString,QString,ChannelOrderComboBox*)));

    // Radio streaming buttons
    ui->cmdRadioStream->setChecked(false);    // Start not streaming
    ui->cmdRadioStream->setEnabled(false);    // Also start not enabled, it will get enabled after we connect to the device
    ui->cmdSaveMinMax->setEnabled(false);     // These are also disabled until streaming actually begins
    ui->cmdSaveCenters->setEnabled(false);    // ""   ""
    ui->frmChannelVals->hide();               // Finally, we hide the entire streaming frame

    // Radio streaming button connections
    connect(ui->cmdRadioStream, SIGNAL(clicked(bool)), this, SLOT(cmdToggleRadioStream_Click()));
    connect(ui->cmdSaveMinMax, SIGNAL(released()), this, SLOT(cmdSaveMinMax_Click()));
    connect(ui->cmdSaveCenters, SIGNAL(released()), this, SLOT(cmdSaveCenters_Click()));
    connect(this, SIGNAL(PulseCentersSaved(boolean)), this, SLOT(ConfirmCentersSaved(boolean)));

}


//------------------------------------------------------------------------------------------------------------------------>>
// FORM CONTROLS - RADIO TAB - RADIO STREAMING
//------------------------------------------------------------------------------------------------------------------------>>
// This is the "checkable" button we use to start/stop streaming. If not started already, clicking the button will first
// request the number of utilized channels, when the device responds, then streaming will start. If we are streaming, then clicking
// this button will request streaming to end. Either way, the actual actions that occur when streaming starts or stops are
// handlded in SetRadioStreamStatus below
void MainWindow::cmdToggleRadioStream_Click()
{
    if (comm->isRadioStreaming())
    {
        comm->stopStreamRadio();
    }
    else
    {
        ui->cmdRadioStream->setChecked(true);  // "Check" (depress) the button, but disable it and set the text to wait
        ui->cmdRadioStream->setText("wait");
        ui->cmdRadioStream->setEnabled(false);

        // Before we actually start streaming, we first request the number of utilized channels
        // When the response arrives we will then proceed to initiate streaming.
        NumUtilizedChannels = 0;                // reset
        comm->requestUtilizedRadioChannels();   // request
        Flag_StartRadioStream = true;           // The flag isn't to specify that streaming has started, it is to specify that we
                                                // *want* streaming to start after the number of channels has been read.
    }
}
// This slot is connected to the comm object signal that fires when streaming has started or stopped.
void MainWindow::SetRadioStreamStatus(boolean streaming)
{
    if (streaming)
    {
        SetStatusLabel("Streaming Radio",slNeutral);
        ui->cmdRadioStream->setChecked(true);                 // "Check" stream button
            ui->cmdRadioStream->setText("Done Reading");      // Change text to done
                ui->cmdRadioStream->setEnabled(true);
        ui->cmdSaveCenters->setEnabled(true);                 // Enable these buttons
        ui->cmdSaveMinMax->setEnabled(true);                  //

        // While streaming, we don't want the user to try reading/writing to the device
        DisableDeviceActionsDuringRadioStream();

        // Also initialize these to false, they will get set later if they apply
        Flag_RadioValuesChanged = false;
        Flag_SaveCenterValues = false;
        Flag_SaveMinMaxValues = false;

        //ui->frmChannelVals->show();
        FadeInRadioStreaming();
    }
    else
    {
        ui->cmdConnect->setEnabled(true);       // Enable stream button in case
        ui->cmdRadioStream->setChecked(false);                // Un-"check" stream button
            ui->cmdRadioStream->setText("Read Radio");
                ui->cmdRadioStream->setEnabled(true);
        ui->cmdSaveCenters->setEnabled(false);                // Disable these buttons
        ui->cmdSaveMinMax->setEnabled(false);                 //
        Flag_StartRadioStream = false;                        // Reset this

        // Now streaming is over we can re-enable these, but only if we are still connected
        EnableDeviceActionsAfterRadioStream();  // This function will check the connection status

        // This flag means the user ran the save-center-values or the save-min/max-values routines while we were streaming
        // In that case, we'd like to go ahead and post these changes to the device rather than relying on the user to remember
        // to click the write-to-device button, and anyway, we might sometimes only want to update these radio values.
        if (Flag_RadioValuesChanged)
        {
            if (comm->isConnected())
            {
                writeSomeSettingsToDevice(RADIO_SETTINGS_START_ID, RADIO_SETTINGS_END_ID);
            }
        }

        FadeOutRadioStreaming();
        // Or you could hide it right away
        //ui->frmChannelVals->hide();
    }
}
void MainWindow::DisableDeviceActionsDuringRadioStream()
{
    // While streaming, we don't want the user to try reading/writing to the device
    ui->actionRead->setEnabled(false);
    ui->cmdReadDevice->setEnabled(false);
    ui->actionWrite->setEnabled(false);
    ui->cmdWriteDevice->setEnabled(false);

    // Or this either
    ui->actionResetAllVals->setEnabled(false);
}
void MainWindow::EnableDeviceActionsAfterRadioStream()
{
    // Streaming is over, we can re-enable these, but only if we are still connected:
    // Because one reason streaming may have stopped is because we disconnected.
    if (comm->isConnected())
    {
        ui->actionRead->setEnabled(true);
        ui->cmdReadDevice->setEnabled(true);
        ui->actionWrite->setEnabled(true);
        ui->cmdWriteDevice->setEnabled(true);
    }
    // This one can be re-enabled regardless of connection status
    ui->actionResetAllVals->setEnabled(true);
}
void MainWindow::SaveNumUtilizedChannels(uint8_t numChannels)
{   // If the device responded with the number of utilized channels, this routine will get called

    // Save it
    NumUtilizedChannels = numChannels;

    // Let's run through each channel order and make sure as many are active as they have utilized, but
    // if they aren't utilizing the full amount, set the extras to NA
    if (NumUtilizedChannels > STICKCHANNELS)
    {
        // Run through the utilized channels, make sure they show up.
        for (int i=STICKCHANNELS; i<NumUtilizedChannels; i++)
        {
            if (channelOrderCombo[i+1]->currentText() == "N/A")
            {   // Set the channel order to the 1 + the prior channel order
                channelOrderCombo[i+1]->setCurrentIndex(channelOrderCombo[i]->currentIndex()+1);
            }
        }

        // Run through the extra channels beyond the utilized ones and set them to NA
        if (NumUtilizedChannels < COUNT_OP_CHANNELS)
        {
            for (int i=COUNT_OP_CHANNELS; i>NumUtilizedChannels;i--)
            {
                // Let's set the unused channels to N/A
                channelOrderCombo[i-1]->setCurrentIndex(channelOrderCombo[i-1]->findText("N/A"));
            }
        }
    }

    // If they have at least 4 channels, proceed with radio streaming
    if (NumUtilizedChannels >= STICKCHANNELS)
    {
        if (Flag_StartRadioStream)
        {
            // If Flag_StartRadioStream is set to true, it means that once we know the number of channels
            // we want the device to start streaming radio data, so go ahead and send the command.
            comm->startStreamRadio();
        }
    }
    else
    {
        SetStatusLabel("Inadequate channels detected!", slBad);
        msgBox(QString("The radio reports only %1 channels connected. A minimum of 4 is required.").arg(NumUtilizedChannels),vbOkOnly, "Inadequate Channels", vbExclamation);
    }
}
void MainWindow::RadioNotReady()
{
    // In this case, we tried to get the device to give us information about the radio, but the device tells us the
    // radio is not ready (could also mean it is not on, or not connected)
    // Abort whatever we had started
    SetStatusLabel("Request failed", slNeutral);
    SetRadioStreamStatus(false);
    msgBox("The radio is not detected!", vbOkOnly, "Radio Not Ready", vbExclamation);
}
// Fade in/out effect for the radio streaming frame. Probably unecessary but it looks cool.
void MainWindow::FadeInRadioStreaming(void)
{
    // Fade in the radio streaming objects
    QFrame *w = ui->frmChannelVals;
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    w->setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(RADIO_STREAM_FADEIN_TIME);
    a->setStartValue(0);
    a->setEndValue(1);
    a->setEasingCurve(QEasingCurve::InBack);
    w->show();
    a->start(QPropertyAnimation::DeleteWhenStopped);
    // Nothing needs to happen when the fade-in completes
    //connect(a,SIGNAL(finished()),this,SLOT(SomeSlot()));
}
void MainWindow::FadeOutRadioStreaming()
{
    // Fade out the label
    QFrame *w = ui->frmChannelVals;
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    w->setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(RADIO_STREAM_FADEOUT_TIME);
    a->setStartValue(1);
    a->setEndValue(0);
    a->setEasingCurve(QEasingCurve::OutBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);
}
// This function first tells the user to center the sticks (we don't really save centers for the aux channels)
// then when they click "Ok" to the message box, center values are saved
void MainWindow::cmdSaveCenters_Click()
{

    msgBox("Please center the sticks on your transmitter.\n\nWhen you click \"Ok\", the center values will be saved.",vbOkOnly,"Save Centers",vbExclamation);
    // We set this flag to true. Now the ReadPulseWidths function below will take care of saving the center values
    Flag_SaveCenterValues = true;
}
void MainWindow::cmdSaveMinMax_Click()
{
    if (!Flag_SaveMinMaxValues)
    {
        msgBox("Move all the controls on your radio until the Min and Max values stop changing.\n\nWhen you are done, click the \"Save Min/Max\" button to complete.",vbOkOnly,"Save Min Max",vbExclamation);

        // "Depress" the min/max button
        ui->cmdSaveMinMax->setChecked(true);

        // We set this flag to true. Now the ReadPulseWidths function below will take care of saving the min/max values
        Flag_SaveMinMaxValues = true;

        // While we're doing this, we need to disable the save min/max and streaming buttons
        ui->cmdSaveCenters->setEnabled(false);
        ui->cmdRadioStream->setChecked(false);  // We "uncheck" this while disabling it to make the checked min/max button stand out more
        ui->cmdRadioStream->setEnabled(false);
        // To make it clearer what we're doing, we also hide pulses/and position labels
        ShowHidePulsesPositions(false);
    }
    else
    {
        Flag_SaveMinMaxValues = false;
        ui->cmdSaveMinMax->setChecked(false);
        ui->cmdSaveCenters->setEnabled(true);
        ui->cmdRadioStream->setChecked(true);
        ui->cmdRadioStream->setEnabled(true);
        // Now show these again
        ShowHidePulsesPositions(true);
    }
}
void MainWindow::ShowHidePulsesPositions(boolean show)
{
    if (!show)
    {
        ui->lblPulseHeaderSticks->hide();
        ui->lblPulseHeaderAux->hide();
        ui->lblStickDirection->hide();
        ui->lblSwitchPos->hide();
        for (int i=0; i<COUNT_OP_CHANNELS; i++)
        {
            lblChannelPulse[i]->hide();
            lblChannelPosition[i]->hide();
        }
    }
    else
    {
        ui->lblPulseHeaderSticks->show();
        ui->lblPulseHeaderAux->show();
        ui->lblStickDirection->show();
        ui->lblSwitchPos->show();
        for (int i=0; i<STICKCHANNELS; i++)
        {
            lblChannelPulse[i]->show();
            lblChannelPosition[i]->show();
        }
        for (int i=STICKCHANNELS; i<COUNT_OP_CHANNELS; i++)
        {
            if (channelOrderCombo[i]->currentText() != "N/A")
            {
                lblChannelPulse[i]->show();
                lblChannelPosition[i]->show();
            }
        }
    }
}

// This slot gets called by the comm object whenever a stream of PPM pulse-widths arrives. A pointer to the array
// of NumUtilizedChannels pulseWidths is passed for us to do with as we want. We apply the pulse widths to our visual
// slider objects, labels, and whatever.
void MainWindow::ReadPulseWidths(int16_t *pulseWidths)
{

    // We'll use these to save stick centers. Unsigned long because we are going to add a stream of pulses which could get
    // kind of large. Then we'll divide by the number of samples taken to get an average for the center.
    static unsigned long TotPulseCenter[STICKCHANNELS]{0,0,0,0};
    const int TOTAL_SAMPLES = 16; // This shouldn't take more than a quarter second at 115,200 baud
    static int NumSamplesTaken = 0;
    float TempFloat = 0.0;

    // These variables will help with saving min/max values
    static boolean runningMinMax = false;


    if (Flag_SaveMinMaxValues == true && runningMinMax == false)
    {   // This means the user has just started the save min/max routine
        // We start by clearing all the min/max values. We do this by setting them all to center instead
        for (int i=0; i<COUNT_OP_CHANNELS; i++)
        {
            *ChannelSettings[i].pulseMin = DEFAULT_PULSE_CENTER;
            *ChannelSettings[i].pulseMax = DEFAULT_PULSE_CENTER;
            lblChannelMin[i]->setText(QString::number(DEFAULT_PULSE_CENTER));
            lblChannelMax[i]->setText(QString::number(DEFAULT_PULSE_CENTER));
        }
        runningMinMax = true;
    }

    // Here we display the radio stream. The sliders show the stick position, the pulse label shows the current pulse,
    // and the direction/position labels show the direction/position of the channel
    for (int i=0; i<NumUtilizedChannels; i++)
    {
        for (int j=0; j<COUNT_OP_CHANNELS; j++)
        {
            if ((*ChannelSettings[j].channelNum - 1) == i)
            {
                // If we are saving min/max values, we update the min/max value to the new pulse-width if the pulse-width
                // exceeds the existing min/max value. We also handle the sliders a little bit different. Instead of showing
                // the instantaneous pulse, we fill the sliders with min/max values, so as the min/max is filled in, the sliders
                // become filled in as well.
                if (runningMinMax)
                {
                    if (pulseWidths[i] < *ChannelSettings[j].pulseMin)
                    {   // pulse width is less than our existing min - update the min,
                        // and set the low slider to the new min value, as well as the min label
                        *ChannelSettings[j].pulseMin = pulseWidths[i];
                        lowSlider[j]->setValue(pulseWidths[i]);
                        lblChannelMin[j]->setText(QString::number(pulseWidths[i]));
                    }
                    if (pulseWidths[i] > *ChannelSettings[j].pulseMax)
                    {   // pulse width is greater than our existing max - update the max,
                        // andset the high slider to the new max value, as well as the max label
                        *ChannelSettings[j].pulseMax = pulseWidths[i];
                        highSlider[j]->setValue(pulseWidths[i]);
                        lblChannelMax[j]->setText(QString::number(pulseWidths[i]));
                    }
                }
                else
                {   // This is the default behavior - the sliders show the current stick position relative to center
                    lowSlider[j]->setValue(pulseWidths[i]);
                    highSlider[j]->setValue(pulseWidths[i]);
                }
                // Pulse label
                lblChannelPulse[j]->setText(QString::number(pulseWidths[i]));
                // Direction label (so the user knows which direction the stick is commanding)
                if (j < STICKCHANNELS)
                {
                    lblChannelPosition[j]->setText(calculateStickDirection(j, pulseWidths[i]));

                    // Also if this is a stick channel, and we are saving the center pulse width, then
                    // save it.
                    if (Flag_SaveCenterValues)
                    {
                        TotPulseCenter[j] += pulseWidths[i];
                    }
                }
                // Position label (so the user knows which switch position the device thinks it reads)
                if (j>=STICKCHANNELS)
                {
                    int AuxNum = j-STICKCHANNELS;
                    if (auxTypeCombo[AuxNum]->currentIndex())   // This check will return true if aux channel is digital
                    {
                        lblChannelPosition[j]->setText(QString("Pos %1").arg(calculateAuxSwitchPos(pulseWidths[i],auxSwitchPosCombo[AuxNum]->currentText().toUInt(), auxReversedCheck[AuxNum]->isChecked())));
                    }
                    else
                    {
                        // Channel is analog, there is no decoded "position"
                        lblChannelPosition[j]->setText("");
                    }
                }
            }
        }
    }

    // SAVE CENTER VALUES
    // We are going to count up to TOTAL_SAMPLES and then take an average for the stick centers
    if (Flag_SaveCenterValues)
    {
        NumSamplesTaken += 1;
        if (NumSamplesTaken >= TOTAL_SAMPLES)
        {
            // We're done. Take the average and save it to our variable (only for stick channels)
            for (int j=0; j<STICKCHANNELS; j++)
            {
                TempFloat = (float)TotPulseCenter[j] / (float)TOTAL_SAMPLES;
                *ChannelSettings[j].pulseCenter = (int16_t)TempFloat;
                TotPulseCenter[j] = 0;  // Reset for next time
                //qDebug() << "Chan " << j+1 << " center: " << TempFloat;
            }
            // For AUX channels, we also save centers to DEFAULT_PULSE_CENTER (not actual center, because we don't know it, and it doesn't matter)
            for (int j=STICKCHANNELS; j<COUNT_OP_CHANNELS; j++)
            {
                *ChannelSettings[j].pulseCenter = DEFAULT_PULSE_CENTER;
            }
            // Update the sliders to the new center values
            UpdateChannelControls_MinMaxCenter();

            // Set this flag to true, so we know to save these changes to device when we stop streaming
            Flag_RadioValuesChanged = true;

            // Now reset for next time
            NumSamplesTaken = 0;
            Flag_SaveCenterValues = false;

            // This is kind of silly, but it just calls ConfirmCentersSaved. If we were going to implement a watchdog timer
            // we could have the timer call ConfirmCentersSaved(false) but I'm going to skip that for now.
            emit PulseCentersSaved(true);
        }
    }

    // SAVE MIN MAX
    // We're done saving min/max. The actual values will already be stored in their respective variables.
    if (Flag_SaveMinMaxValues == false && runningMinMax == true)
    {
        // Stop the min/max process
        runningMinMax = false;

        SetStatusLabel("Min/Max values recorded",slNeutral);

        // Set this flag to true, so we know to save these changes to the device when we stop streaming
        Flag_RadioValuesChanged = true;
    }
}
void MainWindow::UpdateChannelControls_MinMaxCenter(void)
{
    for (int i=0; i<COUNT_OP_CHANNELS; i++)
    {
        lowSlider[i]->setRange(MIN_POSSIBLE_PULSE, *ChannelSettings[i].pulseCenter+SLIDER_CENTER_ADJUST);
        highSlider[i]->setRange(*ChannelSettings[i].pulseCenter-SLIDER_CENTER_ADJUST, MAX_POSSIBLE_PULSE);

        lowSlider[i]->setValue(*ChannelSettings[i].pulseCenter);
        highSlider[i]->setValue(*ChannelSettings[i].pulseCenter);

        lblChannelMin[i]->setText(QString::number(*ChannelSettings[i].pulseMin));
        lblChannelMax[i]->setText(QString::number(*ChannelSettings[i].pulseMax));
    }
}
void MainWindow::ConfirmCentersSaved(boolean saved)
{
    if (saved)
    {
        SetStatusLabel("Center values recorded",slNeutral);
    }
    else
    {
        // For some reason this message box will also cause a disconnect...
        msgBox("Unable to save pulse centers. Please retry.", vbOkOnly, "Error", vbCritical);
    }
}
QString MainWindow::calculateStickDirection(uint8_t StickNum, int16_t Pulse)
{
    QString lblText = "";

    switch (StickNum)
    {
        // Throttle
        case 0:
            if (Pulse >= *ChannelSettings[StickNum].pulseCenter + *ChannelSettings[StickNum].deadband)
            {
                if (*ChannelSettings[StickNum].reversed) lblText = "Reverse";
                else lblText = "Forward";
            }
            else if (Pulse <= *ChannelSettings[StickNum].pulseCenter - *ChannelSettings[StickNum].deadband)
            {
                if (*ChannelSettings[StickNum].reversed) lblText = "Forward";
                else lblText = "Reverse";
            }
            else
            {
                lblText = "Stop";
            }
            break;

        // Steering
        case 1:
            if (Pulse >= *ChannelSettings[StickNum].pulseCenter + *ChannelSettings[StickNum].deadband)
            {
                if (*ChannelSettings[StickNum].reversed) lblText = "Left";
                else lblText = "Right";
            }
            else if (Pulse <= *ChannelSettings[StickNum].pulseCenter - *ChannelSettings[StickNum].deadband)
            {
                if (*ChannelSettings[StickNum].reversed) lblText = "Right";
                else lblText = "Left";
            }
            else
            {
                lblText = "Straight";
            }
            break;

        // Turret elevation
        case 2:
            if (Pulse >= *ChannelSettings[StickNum].pulseCenter + *ChannelSettings[StickNum].deadband)
            {
                if (*ChannelSettings[StickNum].reversed) lblText = "Down";
                else lblText = "Up";
            }
            else if (Pulse <= *ChannelSettings[StickNum].pulseCenter - *ChannelSettings[StickNum].deadband)
            {
                if (*ChannelSettings[StickNum].reversed) lblText = "Up";
                else lblText = "Down";
            }
            else
            {
                lblText = "Steady";
            }
            break;

        // Turret rotation
        case 3:
            if (Pulse >= *ChannelSettings[StickNum].pulseCenter + *ChannelSettings[StickNum].deadband)
            {
                if (*ChannelSettings[StickNum].reversed) lblText = "Left";
                else lblText = "Right";
            }
            else if (Pulse <= *ChannelSettings[StickNum].pulseCenter - *ChannelSettings[StickNum].deadband)
            {
                if (*ChannelSettings[StickNum].reversed) lblText = "Right";
                else lblText = "Left";
            }
            else
            {
                lblText = "Stop";
            }
            break;

    }

return lblText;

}
uint8_t MainWindow::calculateAuxSwitchPos(int16_t Pulse, uint8_t NumPositions, boolean Reversed)
{
    // Thanks to Rob Tillaart for the distance function
    // http://forum.arduino.cc/index.php?topic=254836.0

    // This takes a pulse and returns the switch position with the
    // nearest matching pulse

    uint8_t pos = 0;
    int d = 9999;
    int distance = abs(RC_MULTISWITCH_START_POS - Pulse);

    for (int i = 1; i < NumPositions; i++)
    {
        switch (NumPositions)
        {
            case 2: d = abs(MultiSwitch_MatchArray2[i] - Pulse);   break;
            case 3: d = abs(MultiSwitch_MatchArray3[i] - Pulse);   break;
            case 4: d = abs(MultiSwitch_MatchArray4[i] - Pulse);   break;
            case 5: d = abs(MultiSwitch_MatchArray5[i] - Pulse);   break;
            case 6: d = abs(MultiSwitch_MatchArray6[i] - Pulse);   break;
        }

        if (d < distance)
        {
            pos = i;
            distance = d;
        }
    }

    // Add 1 to POS because from here we don't want zero-based
    pos += 1;

    // Swap positions if channel is reversed.
    if (Reversed)
    {
        switch (NumPositions)
        {
            case 2:
                if (pos == 1) pos = 2;
                else pos = 1;
                break;
            case 3:
                if (pos == 1) pos = 3;
                else if (pos == 3) pos = 1;
                break;
            case 4:
                if (pos == 1) pos = 4;
                else if (pos == 2) pos = 3;
                else if (pos == 3) pos = 2;
                else if (pos == 4) pos = 1;
                break;
            case 5:
                if (pos == 1) pos = 5;
                else if (pos == 2) pos = 4;
                else if (pos == 4) pos = 2;
                else if (pos == 5) pos = 1;
                break;
            case 6:
                if (pos == 1) pos = 6;
                else if (pos == 2) pos = 5;
                else if (pos == 3) pos = 4;
                else if (pos == 4) pos = 3;
                else if (pos == 5) pos = 2;
                else if (pos == 6) pos = 1;
                break;
        }
    }

    return pos;
}


//------------------------------------------------------------------------------------------------------------------------>>
// FORM CONTROLS - RADIO TAB - SAVE AND VALIDATE VALUE CHANGES
//------------------------------------------------------------------------------------------------------------------------>>
void MainWindow::SaveChannelReversed(bool checked, int WhatChannel)
{   // Any change in the reversed status of a channel, save to our variable
    *ChannelSettings[WhatChannel].reversed = checked;
}
void MainWindow::SaveThrottleDeadband(int value)
{
    DeviceData.Sticks.Throttle.Settings.deadband = value;
}
void MainWindow::SaveTurnDeadband(int value)
{
    DeviceData.Sticks.Turn.Settings.deadband = value;
}
void MainWindow::SaveElevationDeadband(int value)
{
    DeviceData.Sticks.Elevation.Settings.deadband = value;
}
void MainWindow::SaveAzimuthDeadband(int value)
{
    DeviceData.Sticks.Azimuth.Settings.deadband = value;
}
void MainWindow::checkAuxChannelsAgainstFunctionTriggers()
{   boolean anyRemoved = false;

    for (int i=0; i<AUXCHANNELS; i++)
    {
        // Check for function triggers belonging to aux channels that are no longer present (set to N/A)
        if (channelOrderCombo[STICKCHANNELS + i]->currentText() == "N/A")   // Aux channel order combos start after stick channels, so add STICKCHANNELS to number
        {
            anyRemoved |= FT_TableModel->removeAuxTriggers(i+1);  // This function will remove any trigger belonging to the aux channel
                                                                  // In the table model the aux channels are numbered starting at 1
        }

        // Check for aux channels set to digital assigned to analog functions
        // Check for aux channels set to analog assigned to digital functions
        anyRemoved |= FT_TableModel->checkAuxChannelTypesAgainstFunctionTriggers(i+1, auxTypeCombo[i]->currentData().toBool());

        // Check for difference in positions
        anyRemoved |= FT_TableModel->checkAuxChannelPositionsAgainstFunctionTriggers(i+1, auxSwitchPosCombo[i]->currentText().toInt());
    }

    if (anyRemoved)
    {
        RemovedFunctionTriggersMsgBox();
    }
}
void MainWindow::ValidateChannelOrder(QString priorChan, QString newChan, ChannelOrderComboBox *changedCombo)
{
    // This routine runs any time a ChannelOrderComboBox changes value. No two channels can have the same channel number,
    // so we want to check if the value the user has changed it to, is already assigned to a different channel. If so,
    // we swap the value of that other channel with the value this box had before it was changed (that is the one channel
    // we now know for certain is free).
    ChannelOrderComboBox *cboSaveMe = changedCombo; // We actually don't want it to equal changedCombo, but we need to initialize
                                                    // it to something to prevent compiler warnings. Later it will be set to what
                                                    // we want.
    boolean doSearch = false;

    // Let's create a list of all unused channels. We'll do this by populating a list of all possible channels
    // Later we'll remove each channel that is being used. At the end, we'll have a list of only the unused
    // channels remaining
    QList<int> unUsedChannels;
    for (int i=1; i<=COUNT_OP_CHANNELS; i++)
    {
        unUsedChannels.insert(unUsedChannels.size(),i);
    }

    // If they've changed it to "N/A" we don't care
    if (newChan != "N/A")
    {
        // iterate through all ChannelOrderComboBox-es within the frmChannelOrder frame
        QList<ChannelOrderComboBox*> cboList = ui->frmChannelOrder->findChildren<ChannelOrderComboBox*>();
        foreach(ChannelOrderComboBox *cbo, cboList)
        {
            // Only check other combos, not the one we've just changed
            if (cbo != changedCombo)
            {   // Remove this used channel from the list
                if (cbo->currentText() != "N/A")
                {
                    unUsedChannels.removeAt(unUsedChannels.indexOf(cbo->currentText().toInt()));
                }

                // This combo has the channel number we want to use
                if (cbo->currentText() == newChan)
                {
                    if (priorChan == "N/A" && cbo->isAux() == false)
                    {   // If the prior channel was "N/A", and the channel number we're stealing is from
                        // one of the sticks (who don't have an "N/A" option), we can't set that
                        // stick to the prior channel of "N/A". Instead we need to assign it an un-used channel,
                        // but we won't know which channels are un-used until we get to the end.
                        cboSaveMe = cbo;
                        doSearch = true;    // This lets us know we have to run through a search after
                    }
                    else
                    {   // In this case, we can just do a straight swap
                        cbo->setCurrentText(priorChan);
                    }
                }
            }
        }
        // Now if we need, set this one combo to the first unused channel remaining
        if (doSearch)
        {
            doSearch = false;
            cboSaveMe->setCurrentText(QString::number(unUsedChannels.value(0)));
        }
    }
}
void MainWindow::SaveChannelNum(QString priorChan, QString newChan, ChannelOrderComboBox *changedCombo, int WhatChannel)
{
    int AuxChannelNum;
    int StickChannelNum;

    // We don't need priorChan or newChan in the following code, but they do need to be part of the function definition
    // for our CONNECT to work correctly. To disable the compiler warnings, do this:
    (void)priorChan;
    (void)newChan;

    if (changedCombo->isAux() == false)
    {
        StickChannelNum = WhatChannel;
        *ChannelSettings[StickChannelNum].channelNum = changedCombo->currentIndex() + 1;
    }
    else
    {
        AuxChannelNum = WhatChannel;
        // Any change, save to our variable
        DeviceData.AuxChannel[AuxChannelNum].Settings.channelNum = changedCombo->currentIndex();

        // When Aux Channel is set to N/A, disable some other stuff
        if (DeviceData.AuxChannel[AuxChannelNum].Settings.channelNum == 0)
        {
            // If aux channel is set to N/A, disable the channel type and number-of-position combos
            // To make it look pretty, we add an empty item, set the selection to it, then disable the control
            if (auxTypeCombo[AuxChannelNum]->findText("") == -1)    // If empty item doesn't already exist,
                auxTypeCombo[AuxChannelNum]->addItem("");           // insert and empty item
            if (auxSwitchPosCombo[AuxChannelNum]->findText("") == -1)
                auxSwitchPosCombo[AuxChannelNum]->addItem("");
            auxTypeCombo[AuxChannelNum]->setCurrentText("");        // Set the combos to it
            auxSwitchPosCombo[AuxChannelNum]->setCurrentText("");
            auxReversedCheck[AuxChannelNum]->setChecked(false);     // Clear Reversed check
            //auxTypeCombo[AuxChannelNum]->setEnabled(false);         // Now disable combos
            //auxSwitchPosCombo[AuxChannelNum]->setEnabled(false);
            //auxReversedCheck[AuxChannelNum]->setEnabled(false);     // Disabled reverse check box
            auxTypeCombo[AuxChannelNum]->hide();
            auxSwitchPosCombo[AuxChannelNum]->hide();
            auxReversedCheck[AuxChannelNum]->hide();
            // But we don't want blank variables, so put them back to default
            DeviceData.AuxChannel[AuxChannelNum].Settings.Digital = true;
            DeviceData.AuxChannel[AuxChannelNum].Settings.numPositions = 2;
            DeviceData.AuxChannel[AuxChannelNum].Settings.reversed = false;

            // Hide also the pulse-width stuff
            lowSlider[AuxChannelNum+STICKCHANNELS]->hide();
            highSlider[AuxChannelNum+STICKCHANNELS]->hide();
            lblChannelMin[AuxChannelNum+STICKCHANNELS]->hide();
            lblChannelMax[AuxChannelNum+STICKCHANNELS]->hide();
            lblChannelPulse[AuxChannelNum+STICKCHANNELS]->hide();
            lblChannelPosition[AuxChannelNum+STICKCHANNELS]->hide();

            // If the channel is set to "N/A", any function triggers that rely on this channel
            // as a trigger, must be removed
            if (FT_TableModel->removeAuxTriggers(AuxChannelNum+1))  // Add 1 because it is not zero-based
                RemovedFunctionTriggersMsgBox();
        }
        else
        {
            // If aux channel is set to some number, (re)enable these. In this order we need to:
            // - Set the combos to the current variables
            // - Since that will take us off the fake empty entry, we can now remove the empty entry
            // - Then finally re-enable
            // Set controls to current variable settings:
            auxTypeCombo[AuxChannelNum]->setCurrentIndex(auxTypeCombo[AuxChannelNum]->findData(DeviceData.AuxChannel[AuxChannelNum].Settings.Digital));
            auxSwitchPosCombo[AuxChannelNum]->setCurrentText(QString::number(DeviceData.AuxChannel[AuxChannelNum].Settings.numPositions));
            auxReversedCheck[AuxChannelNum]->setChecked(DeviceData.AuxChannel[AuxChannelNum].Settings.reversed);
            // Now remove the empty item
            auxTypeCombo[AuxChannelNum]->removeItem(auxTypeCombo[AuxChannelNum]->findText(""));
            // But only remove the empty item on the SwitchPosCombo if the channel type is digital, otherwise we still want it
            if (DeviceData.AuxChannel[AuxChannelNum].Settings.Digital)
            {
                auxSwitchPosCombo[AuxChannelNum]->removeItem(auxSwitchPosCombo[AuxChannelNum]->findText(""));
            }
            else
            {   // Otherwise if this is analog, keep the SwitchPos combo on the empty option since positions don't apply
                auxSwitchPosCombo[AuxChannelNum]->setCurrentText("");
                DeviceData.AuxChannel[AuxChannelNum].Settings.numPositions = 2; // But default to 2 positions in our variable because that is the default we want to return to when they change it back to digital.
            }
            // Now re-enable
            //auxTypeCombo[AuxChannelNum]->setEnabled(true);
            //auxSwitchPosCombo[AuxChannelNum]->setEnabled(true);
            //auxReversedCheck[AuxChannelNum]->setEnabled(true);
            auxTypeCombo[AuxChannelNum]->show();
            auxSwitchPosCombo[AuxChannelNum]->show();
            auxReversedCheck[AuxChannelNum]->show();

            // Show the pulse-width stuff
            lowSlider[AuxChannelNum+STICKCHANNELS]->show();
            highSlider[AuxChannelNum+STICKCHANNELS]->show();
            lblChannelMin[AuxChannelNum+STICKCHANNELS]->show();
            lblChannelMax[AuxChannelNum+STICKCHANNELS]->show();
            lblChannelPulse[AuxChannelNum+STICKCHANNELS]->show();
            lblChannelPosition[AuxChannelNum+STICKCHANNELS]->show();
        }
    }
}
void MainWindow::SaveAuxChannelType(AnalogDigitalComboBox *, int AuxChannelNum)
{
    // Any change, save to our variable
    DeviceData.AuxChannel[AuxChannelNum].Settings.Digital = static_cast<boolean>(auxTypeCombo[AuxChannelNum]->currentData().toUInt());
    if (!DeviceData.AuxChannel[AuxChannelNum].Settings.Digital)
    {
        // Type is set to analog, re-set and disable the count-of-switch positions combo
        if (auxSwitchPosCombo[AuxChannelNum]->findText("") == -1)   // If empty item doesn't already exist,
            auxSwitchPosCombo[AuxChannelNum]->addItem("");          // insert an empty item.
        auxSwitchPosCombo[AuxChannelNum]->setCurrentText("");       // Set the combo to it
        auxSwitchPosCombo[AuxChannelNum]->setEnabled(false);        // Now disable the combo
        DeviceData.AuxChannel[AuxChannelNum].Settings.numPositions = 2; // But default to 2 positions in our variable just so it's a number
    }
    else
    {
        // Type is set to digital, show the count-of-switch positions combo
        // First set the type to the actual number in variable, not the empty selection
        auxSwitchPosCombo[AuxChannelNum]->setCurrentText(QString::number(DeviceData.AuxChannel[AuxChannelNum].Settings.numPositions));
        // Now we're off the empty selection, remove it
        auxSwitchPosCombo[AuxChannelNum]->removeItem(auxSwitchPosCombo[AuxChannelNum]->findText(""));
        // Now re-enable
        auxSwitchPosCombo[AuxChannelNum]->setEnabled(true);
    }

    // Either way, we must check this change against our existing function triggers!
    if (FT_TableModel->checkAuxChannelTypesAgainstFunctionTriggers(AuxChannelNum+1, auxTypeCombo[AuxChannelNum]->currentData().toBool()))
        RemovedFunctionTriggersMsgBox();
}
void MainWindow::SaveAuxChannelPositions(AuxChannelPositionsCombo *, int AuxChannelNum)
{
    // Any change, save to our variable
    DeviceData.AuxChannel[AuxChannelNum].Settings.numPositions = auxSwitchPosCombo[AuxChannelNum]->currentData().toUInt();

    // We also need to check this change against our function triggers in case any are no longer valid
    if (FT_TableModel->checkAuxChannelPositionsAgainstFunctionTriggers(AuxChannelNum+1, auxSwitchPosCombo[AuxChannelNum]->currentData().toUInt()))
        RemovedFunctionTriggersMsgBox();
}
