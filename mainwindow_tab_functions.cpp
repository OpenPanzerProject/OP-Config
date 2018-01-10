#include "mainwindow.h"
#include "ui_mainwindow.h"


//------------------------------------------------------------------------------------------------------------------------>>
// FORM CONTROLS - FUNCTIONS TAB
//------------------------------------------------------------------------------------------------------------------------>>
void MainWindow::SetupControls_FunctionsTab(void)
{   // This tab is where special functions are linked to triggers.
    // There are three main combo boxes, and they must be manipulated in order.
    // First, the user selects the special function they want triggered.
    // Depending on the function, the appropriate trigger sources are then displayed in the second combo,
    // the user selects the trigger source they want to use.
    // Depending on the trigger source, the appropriate trigger actions are then displayed in the third combo
    // Finally the user selects a trigger action and clicks the add button to create a link between the function and the trigger action

    // Table model reference
    // We could apply our FT_TableModel data model directly to our QTableView, but we only want to display certain columns (filtering),
    // and we want to be able to sort. For these additional features, we need to actually implement a QSortFilterProxyModel
    // that displays the columns we want, then apply *that* model to our QTableView.
    FT_ProxyModel = new QSortFilterProxyModel;
    FT_ProxyModel->setSourceModel(FT_TableModel);
    // Set our table view to the proxy model instead
    //ui->tblFunctionTriggers->setModel(FT_TableModel);
    ui->tblFunctionTriggers->setModel(FT_ProxyModel);
    // As it turns out, we conveniently don't need to subclass anything to hide columns, that is a property of QTableView widget thank god.
    ui->tblFunctionTriggers->setColumnHidden(0,true);   // Trigger ID
    ui->tblFunctionTriggers->setColumnHidden(1,true);   // Special Function #
    // We only want the user to be able to select whole rows, not individual items within a row (though it won't really matter)
    ui->tblFunctionTriggers->setSelectionBehavior(QAbstractItemView::SelectRows);
    // We can restrict to only one row selected at a time, or multiple. However, it is much easier to remove rows when you can
    // only select one at a time, so we leave it at SingleSelection
    ui->tblFunctionTriggers->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->tblFunctionTriggers->setSelectionMode(QAbstractItemView::MultiSelection);

    // The special function combo gets filled automatically because the constructor for SpecialFunctionComboBox does it.
    // As for the other two, we start with trigger sources and trigger actions empty
    // The trigger source is set according to the special function which we don't know yet
    ui->cboTriggerSource->clear();
    // The trigger action is set according to the trigger source which we don't know yet
    ui->cboTriggerAction->clear();

    // Signals and slots
    // Anytime a special function is selected, update the trigger source list
    connect(ui->cboSelectFunction, SIGNAL(currentFunctionChanged(_special_function,boolean)), SLOT(SetupTriggerSources(_special_function,boolean)));   // When they select a function, setup the trigger sources
    // Anytime a trigger source is selected, update the trigger action list
    connect(ui->cboTriggerSource, SIGNAL(currentIndexChanged(int)), SLOT(SetupTriggerActions(int)));
    // These buttons add or remove a function-trigger from the function trigger table model
    connect(ui->cmdAddFunctionTrigger, SIGNAL(clicked(bool)), this, SLOT(cmdAddFunctionTrigger_clicked(bool)));
    connect(ui->cmdRemoveFunctionTrigger, SIGNAL(clicked(bool)), this, SLOT(cmdRemoveFunctionTrigger_clicked(bool)));
    // Whenever data is changed in the table model, it will emit a signal to let us know whether the turret stick is one of the triggers
    // If so we will display specific options related to the turret stick triggers, otherwise we will disable them
    connect(FT_TableModel, SIGNAL(TurretStickPresent(boolean)), this, SLOT(UpdateTurretStickDelayOptions(boolean)));
    // We also have a signal to tell us how many rows are in the model, which we display
    connect(FT_TableModel, SIGNAL(functionTriggerCount(int)), this, SLOT(UpdateFunctionTriggerCount(int)));
}
void MainWindow::UpdateTurretStickDelayOptions(boolean isTSPresent)
{
    if (isTSPresent)    // Meaning, is the turret stick present in the funciton list as a trigger
    {
        if (ui->cboTurretElevationMotor->getCurrentDriveType() == DRIVE_DETACHED &&
            ui->cboTurretRotationMotor->getCurrentDriveType()  == DRIVE_DETACHED)
        {   // In this case, we do have functions assigned to the turret stick, but the turret stick is detached from any motor control.
            // Therefore we can disable the turret stick delay
            ui->spinIgnoreTurretDelay->setEnabled(false);
            ui->lblIgnoreTurretStickNote->setText("(Ignored because turret stick detached<br />from turret motors)");
            ui->lblIgnoreTurretStickNote->show();
        }
        else
        {
            // In this case we do have a turret stick trigger to a function, and the turret stick is also being used to control
            // some motor, so we enable the option to add a delay
            ui->spinIgnoreTurretDelay->setEnabled(true);
            ui->lblIgnoreTurretStickNote->hide();
        }
    }
    else
    {
        // In this case we have no functions assigned to the turret stick, so no need to enable the delay
        ui->spinIgnoreTurretDelay->setEnabled(false);
        ui->lblIgnoreTurretStickNote->setText("(Ignored because no turret stick<br />triggers are defined)");
        ui->lblIgnoreTurretStickNote->show();
    }
}
void MainWindow::UpdateFunctionTriggerCount(int count)
{
    ui->lblFunctionTriggerCount->setText(QString("Function-trigger count: %1").arg(count));
}

void MainWindow::SetupTriggerSources(_special_function sf, boolean isSFDigital)
{   // This gets triggered any time the user selects a special function from the drop down

    ui->cboTriggerSource->clear();
    ui->cboTriggerAction->clear();

    // Always add a null option
    ui->cboTriggerSource->insertItem(0,"",TS_NULL_TRIGGER);

    // Now add the other items as appropriate
    if (sf != SF_NULL_FUNCTION) // Assuming they selected something...
    {
        if (isSFDigital)
        {
            // Only add digital trigger sources
            // Turret stick always counts
            ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Turret Stick", TS_TURRET_STICK);
            // Aux channels only if they are set to digital
            if (DeviceData.AuxChannel[0].Settings.Digital && DeviceData.AuxChannel[0].Settings.channelNum > 0)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Aux Channel 1", TS_AUX1 );
            if (DeviceData.AuxChannel[1].Settings.Digital && DeviceData.AuxChannel[1].Settings.channelNum > 0)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Aux Channel 2", TS_AUX2 );
            if (DeviceData.AuxChannel[2].Settings.Digital && DeviceData.AuxChannel[2].Settings.channelNum > 0)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Aux Channel 3", TS_AUX3 );
            if (DeviceData.AuxChannel[3].Settings.Digital && DeviceData.AuxChannel[3].Settings.channelNum > 0)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Aux Channel 4", TS_AUX4 );
            if (DeviceData.AuxChannel[4].Settings.Digital && DeviceData.AuxChannel[4].Settings.channelNum > 0)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Aux Channel 5", TS_AUX5 );
            if (DeviceData.AuxChannel[5].Settings.Digital && DeviceData.AuxChannel[5].Settings.channelNum > 0)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Aux Channel 6", TS_AUX6 );
            if (DeviceData.AuxChannel[6].Settings.Digital && DeviceData.AuxChannel[6].Settings.channelNum > 0)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Aux Channel 7", TS_AUX7 );
            if (DeviceData.AuxChannel[7].Settings.Digital && DeviceData.AuxChannel[7].Settings.channelNum > 0)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Aux Channel 8", TS_AUX8 );
            if (DeviceData.AuxChannel[8].Settings.Digital && DeviceData.AuxChannel[8].Settings.channelNum > 0)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Aux Channel 9", TS_AUX9 );
            if (DeviceData.AuxChannel[9].Settings.Digital && DeviceData.AuxChannel[9].Settings.channelNum > 0)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Aux Channel 10", TS_AUX10 );
            if (DeviceData.AuxChannel[10].Settings.Digital && DeviceData.AuxChannel[10].Settings.channelNum > 0)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Aux Channel 11", TS_AUX11 );
            if (DeviceData.AuxChannel[11].Settings.Digital && DeviceData.AuxChannel[11].Settings.channelNum > 0)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Aux Channel 12", TS_AUX12 );
            // External I/O ports only if they are set to inputs (triggers) and digital
            if (DeviceData.PortA.Settings.dataDirection == DD_INPUT && DeviceData.PortA.Settings.dataType == true)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "External Input A", TS_INPUT_A);
            if (DeviceData.PortB.Settings.dataDirection == DD_INPUT && DeviceData.PortB.Settings.dataType == true)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "External Input B", TS_INPUT_B);
            // Speed-based triggers
            ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Vehicle Speed Increases Above:", TS_SPEED_INCR );
            ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Vehicle Speed Decreases Below:", TS_SPEED_DECR );
            // Ad-Hoc Triggers
            ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Brakes Applied", TS_ADHC_BRAKES );
            ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Cannon Hit", TS_ADHC_CANNONHIT );
            ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Vehicle Destroyed", TS_ADHC_DESTROYED );
        }
        else
        {   // In this case we only want to show analog inputs
            // Aux channels only if they are set to analog
            if (!DeviceData.AuxChannel[0].Settings.Digital && DeviceData.AuxChannel[0].Settings.channelNum > 0)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Aux Channel 1", TS_AUX1 );
            if (!DeviceData.AuxChannel[1].Settings.Digital && DeviceData.AuxChannel[1].Settings.channelNum > 0)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Aux Channel 2", TS_AUX2 );
            if (!DeviceData.AuxChannel[2].Settings.Digital && DeviceData.AuxChannel[2].Settings.channelNum > 0)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Aux Channel 3", TS_AUX3 );
            if (!DeviceData.AuxChannel[3].Settings.Digital && DeviceData.AuxChannel[3].Settings.channelNum > 0)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Aux Channel 4", TS_AUX4 );
            if (!DeviceData.AuxChannel[4].Settings.Digital && DeviceData.AuxChannel[4].Settings.channelNum > 0)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Aux Channel 5", TS_AUX5 );
            if (!DeviceData.AuxChannel[5].Settings.Digital && DeviceData.AuxChannel[5].Settings.channelNum > 0)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Aux Channel 6", TS_AUX6 );
            if (!DeviceData.AuxChannel[6].Settings.Digital && DeviceData.AuxChannel[6].Settings.channelNum > 0)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Aux Channel 7", TS_AUX7 );
            if (!DeviceData.AuxChannel[7].Settings.Digital && DeviceData.AuxChannel[7].Settings.channelNum > 0)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Aux Channel 8", TS_AUX8 );
            if (!DeviceData.AuxChannel[8].Settings.Digital && DeviceData.AuxChannel[8].Settings.channelNum > 0)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Aux Channel 9", TS_AUX9 );
            if (!DeviceData.AuxChannel[9].Settings.Digital && DeviceData.AuxChannel[9].Settings.channelNum > 0)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Aux Channel 10", TS_AUX10 );
            if (!DeviceData.AuxChannel[10].Settings.Digital && DeviceData.AuxChannel[10].Settings.channelNum > 0)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Aux Channel 11", TS_AUX11 );
            if (!DeviceData.AuxChannel[11].Settings.Digital && DeviceData.AuxChannel[11].Settings.channelNum > 0)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Aux Channel 12", TS_AUX12 );
            // External I/O ports only if they are set to inputs (triggers) and analog
            if (DeviceData.PortA.Settings.dataDirection == DD_INPUT && DeviceData.PortA.Settings.dataType == false)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "External Input A", TS_INPUT_A);
            if (DeviceData.PortB.Settings.dataDirection == DD_INPUT && DeviceData.PortB.Settings.dataType == false)
                ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "External Input B", TS_INPUT_B);
            // Throttle command, vehicle and engine speeds, always present
            // OK - These work, and they are implemented in the TCB firmware as well. However I really see no clear use-case for them.
            // One wonders if they are worth enabling...
            ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Throttle Command", TS_THROTTLE_COMMAND);
            ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Engine Speed", TS_ENGINE_SPEED);
            ui->cboTriggerSource->insertItem(ui->cboTriggerSource->count(), "Vehicle Speed", TS_VEHICLE_SPEED);
        }
    }

    // Start de-selected (actually selecting null)
    ui->cboTriggerSource->setCurrentIndex(0);
}
void MainWindow::SetupTriggerActions(int)
{   // This gets triggered any time the user selects a trigger source from the drop-down

    int numPositions = 0;
    ui->cboTriggerAction->clear();  // clear trigger actions to start

    // What trigger source did they select -
    _trigger_source ts = static_cast<_trigger_source>(ui->cboTriggerSource->currentData().toInt());

    if (ts == TS_NULL_TRIGGER)
    {   // A trigger wasn't actually selected
        ui->cboTriggerAction->insertItem(0, "", -1);
    }
    else
    {
        if (ui->cboSelectFunction->isFunctionDigital(static_cast<_special_function>(ui->cboSelectFunction->currentData().toUInt())))
        {
            ui->cboTriggerAction->insertItem(0, "", -1);

            // Trigger source is Turret Stick (digital input)
            if (ui->cboTriggerSource->currentData()==TS_TURRET_STICK)
            {
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "Top Left", SP_TL);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "Top Center", SP_TC);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "Top Right", SP_TR);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "Middle Left", SP_ML);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "Middle Center", SP_MC);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "Middle Right", SP_MR);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "Bottom Left", SP_BL);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "Bottom Center", SP_BC);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "Bottom Right", SP_BR);
            }
            // Trigger source is Aux Channel (digital input)
            else if (ui->cboTriggerSource->isTriggerSourceAux(ts))
            {
                switch (ts)
                {
                    case TS_AUX1:
                        numPositions = DeviceData.AuxChannel[0].Settings.numPositions;
                        break;
                    case TS_AUX2:
                        numPositions = DeviceData.AuxChannel[1].Settings.numPositions;
                        break;
                    case TS_AUX3:
                        numPositions = DeviceData.AuxChannel[2].Settings.numPositions;
                        break;
                    case TS_AUX4:
                        numPositions = DeviceData.AuxChannel[3].Settings.numPositions;
                        break;
                    case TS_AUX5:
                        numPositions = DeviceData.AuxChannel[4].Settings.numPositions;
                        break;
                    case TS_AUX6:
                        numPositions = DeviceData.AuxChannel[5].Settings.numPositions;
                        break;
                    case TS_AUX7:
                        numPositions = DeviceData.AuxChannel[6].Settings.numPositions;
                        break;
                    case TS_AUX8:
                        numPositions = DeviceData.AuxChannel[7].Settings.numPositions;
                        break;
                    case TS_AUX9:
                        numPositions = DeviceData.AuxChannel[8].Settings.numPositions;
                        break;
                    case TS_AUX10:
                        numPositions = DeviceData.AuxChannel[9].Settings.numPositions;
                        break;
                    case TS_AUX11:
                        numPositions = DeviceData.AuxChannel[10].Settings.numPositions;
                        break;
                    case TS_AUX12:
                        numPositions = DeviceData.AuxChannel[11].Settings.numPositions;
                        break;
                    case TS_INPUT_A:
                    case TS_INPUT_B:
                        numPositions = 2;
                        break;
                    default:
                        numPositions = 0;
                }
                switch (numPositions)
                {
                    case 2: // 2 positions, with values 1/5
                        ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "Pos 1", SP_POS1);
                        ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "Pos 2", SP_POS5);
                        break;
                    case 3: // 3 positions, with values 1/3/5
                        ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "Pos 1", SP_POS1);
                        ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "Pos 2", SP_POS3);
                        ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "Pos 3", SP_POS5);
                        break;
                    case 5: // 5 positions, with values 1/2/3/4/5
                        ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "Pos 1", SP_POS1);
                        ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "Pos 2", SP_POS2);
                        ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "Pos 3", SP_POS3);
                        ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "Pos 4", SP_POS4);
                        ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "Pos 5", SP_POS5);
                        break;
                }
            }
            // Trigger source is External Port (digital input)
            else if (ui->cboTriggerSource->currentData() == TS_INPUT_A ||
                     ui->cboTriggerSource->currentData() == TS_INPUT_B)
            {
                // These can only be on/off (if digital)
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "On", 1);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "Off", 0);
            }
            // Speed increase trigger
            else if (ui->cboTriggerSource->currentData() == TS_SPEED_INCR)
            {
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), " 0%", 0);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "10%", 10);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "20%", 20);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "30%", 30);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "40%", 40);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "50%", 50);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "60%", 60);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "70%", 70);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "80%", 80);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "90%", 90);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "99%", 99);
            }
            // Speed decrease trigger
            else if (ui->cboTriggerSource->currentData() == TS_SPEED_DECR)
            {
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), " 1%", 1);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "10%", 10);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "20%", 20);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "30%", 30);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "40%", 40);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "50%", 50);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "60%", 60);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "70%", 70);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "80%", 80);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "90%", 90);
                ui->cboTriggerAction->insertItem(ui->cboTriggerAction->count(), "100%", 100);
            }
            // AD-HOC TRIGGERS
            // For now none of these need any specific source information beyond the trigger itself
//            else if (ui->cboTriggerSource->currentData() == TS_ADHC_BRAKES)
//            {
//            }
        }
        // Trigger source is Analog of some kind (doesn't matter whether Aux channel or External Port
        else
        {
            // Analog, they only need a single selection which we will place for them and which doesn't actually
            // mean anything other than as verification to the user this is an analog function
            ui->cboTriggerAction->insertItem(0,"Variable",0);
        }
    }
}
void MainWindow::cmdAddFunctionTrigger_clicked(bool)
{   // Add function trigger
    uint16_t TriggerID = 0;
    QString strPos = "";

    // Get the selected function:
    _special_function sf = static_cast<_special_function>(ui->cboSelectFunction->currentData().toInt());
    boolean sf_digital = ui->cboSelectFunction->isFunctionDigital(sf);

    // Get the trigger source:
    _trigger_source ts = static_cast<_trigger_source>(ui->cboTriggerSource->currentData().toInt());

    // Get the trigger action:
    int ta = ui->cboTriggerAction->currentData().toInt();
    strPos = ui->cboTriggerAction->currentText();

    // Only add if these values are valid
    if (sf != SF_NULL_FUNCTION && ts != TS_NULL_TRIGGER && strPos != "")
    {
        // Now construct the trigger ID
        switch (ts)
        {
            // TURRET STICK
            // ---------------------------------------------------------------------------->>
            case TS_TURRET_STICK:
                if (ta > 0 && ta <= MAX_SPEC_POS)
                {   // For the turret stick, the TriggerID is the trigger action
                    TriggerID = ta;
                }
                break;

            // AUX CHANNELS
            // ---------------------------------------------------------------------------->>
            // Aux channel trigger IDs are constructed from three pieces of information:
            // The channel number, the number of positions the switch has (if digital switch), and the position of the trigger,
            // or in other words, the trigger action.
            // The formula for digital trigger IDs is:
            // (ChannelNumber * trigger_id_multiplier_auxchannel) + (NumberOfSwitchPositions * switch_pos_multiplier) + Switch Position
            // But if the trigger is analog, the formula for TriggerID is just:
            // (ChannelNumber * trigger_id_multiplier_auxchannel)
            case TS_AUX1:
                TriggerID = (1 * trigger_id_multiplier_auxchannel);
                if (sf_digital) TriggerID += (DeviceData.AuxChannel[0].Settings.numPositions * switch_pos_multiplier) + ta;
                break;
            case TS_AUX2:
                TriggerID = (2 * trigger_id_multiplier_auxchannel);
                if (sf_digital) TriggerID += (DeviceData.AuxChannel[1].Settings.numPositions * switch_pos_multiplier) + ta;
                break;
            case TS_AUX3:
                TriggerID = (3 * trigger_id_multiplier_auxchannel);
                if (sf_digital) TriggerID += (DeviceData.AuxChannel[2].Settings.numPositions * switch_pos_multiplier) + ta;
                break;
            case TS_AUX4:
                TriggerID = (4 * trigger_id_multiplier_auxchannel);
                if (sf_digital) TriggerID += (DeviceData.AuxChannel[3].Settings.numPositions * switch_pos_multiplier) + ta;
                break;
            case TS_AUX5:
                TriggerID = (5 * trigger_id_multiplier_auxchannel);
                if (sf_digital) TriggerID += (DeviceData.AuxChannel[4].Settings.numPositions * switch_pos_multiplier) + ta;
                break;
            case TS_AUX6:
                TriggerID = (6 * trigger_id_multiplier_auxchannel);
                if (sf_digital) TriggerID += (DeviceData.AuxChannel[5].Settings.numPositions * switch_pos_multiplier) + ta;
                break;
            case TS_AUX7:
                TriggerID = (7 * trigger_id_multiplier_auxchannel);
                if (sf_digital) TriggerID += (DeviceData.AuxChannel[6].Settings.numPositions * switch_pos_multiplier) + ta;
                break;
            case TS_AUX8:
                TriggerID = (8 * trigger_id_multiplier_auxchannel);
                if (sf_digital) TriggerID += (DeviceData.AuxChannel[7].Settings.numPositions * switch_pos_multiplier) + ta;
                break;
            case TS_AUX9:
                TriggerID = (9 * trigger_id_multiplier_auxchannel);
                if (sf_digital) TriggerID += (DeviceData.AuxChannel[8].Settings.numPositions * switch_pos_multiplier) + ta;
                break;
            case TS_AUX10:
                TriggerID = (10 * trigger_id_multiplier_auxchannel);
                if (sf_digital) TriggerID += (DeviceData.AuxChannel[9].Settings.numPositions * switch_pos_multiplier) + ta;
                break;
            case TS_AUX11:
                TriggerID = (11 * trigger_id_multiplier_auxchannel);
                if (sf_digital) TriggerID += (DeviceData.AuxChannel[10].Settings.numPositions * switch_pos_multiplier) + ta;
                break;
            case TS_AUX12:
                TriggerID = (12 * trigger_id_multiplier_auxchannel);
                if (sf_digital) TriggerID += (DeviceData.AuxChannel[11].Settings.numPositions * switch_pos_multiplier) + ta;
                break;
            // EXTERNAL INPUTS
            // ---------------------------------------------------------------------------->>
            // External input trigger IDs are constructed from two pieces of information:
            // The input number, and the position of the trigger (1/0 or on/off if digital)
            // The formula for digital inputs is:
            // (PortNumber * trigger_id_multiplier_ports) + Input Switch Position
            // But if the input is analog, the TriggerID is just:
            // (PortNumber * trigger_id_multiplier_ports) without anything about the Switch Position
            case TS_INPUT_A:
                TriggerID = (1 * trigger_id_multiplier_ports);
                if (sf_digital) TriggerID += ta;
                break;
            case TS_INPUT_B:
                TriggerID = (2 * trigger_id_multiplier_ports);
                if (sf_digital) TriggerID += ta;
                break;

            // SPEED INCREASE/DECREASE TRIGGERS
            // ---------------------------------------------------------------------------->>
            // These are specific IDs plus a number from 0-100 to indicate the set level
            case TS_SPEED_INCR:
                TriggerID = trigger_id_speed_increase;
                if (sf_digital) TriggerID += ta;    // Trigger ID is the ID plus the set level
                break;
            case TS_SPEED_DECR:
                TriggerID = trigger_id_speed_decrease;
                if (sf_digital) TriggerID += ta;    // Trigger ID is the ID plus the set level
                break;

            // THROTTLE COMMAND / VEHICLE / ENGINE SPEEDS
            // ---------------------------------------------------------------------------->>
            // These are very simple, just a single number with no other information
            case TS_THROTTLE_COMMAND:
                TriggerID = trigger_id_throttle_command;
                break;
            case TS_ENGINE_SPEED:
                TriggerID = trigger_id_engine_speed;
                break;
            case TS_VEHICLE_SPEED:
                TriggerID = trigger_id_vehicle_speed;
                break;

            // AD-HOC
            // ---------------------------------------------------------------------------->>
            // See below - v


            // UNKNOWN
            // ---------------------------------------------------------------------------->>
            default:
                TriggerID = 0;
        }
    }
    // AD-HOC
    // ------------------------------------------------------------------------------------>>
    // But wait! Ad-Hoc functions may not have a trigger action (strPos will = "")
    // But this is fine. So handle them separately here
    else if (sf != SF_NULL_FUNCTION && ts != TS_NULL_TRIGGER) //  && strPos != "")
    {
        // Now construct the trigger ID
        switch (ts)
        {
        // These are just hard-coded to a specific ID. For now none have actual ta (trigger actions)
        case TS_ADHC_BRAKES:
            TriggerID = ADHOC_TRIGGER_BRAKES_APPLIED;
            break;
        case TS_ADHC_CANNONHIT:
            TriggerID = ADHOC_TRIGGER_CANNON_HIT;
            break;
        case TS_ADHC_DESTROYED:
            TriggerID = ADHOC_TRIGGER_VEHICLE_DESTROYED;
            break;
        default:
            TriggerID = 0;
        }
    }

    // If we have a Trigger ID, we are ready to go
    if (TriggerID > 0)
    {
        if (!FT_TableModel->insertFunctionTrigger(sf, TriggerID))
        {
            msgBox(FT_TableModel->errorText(),vbOkOnly, "Add Function Trigger", vbExclamation);
        }
        else
        {   // Function trigger was successfully added. Let's clear the combos
            ui->cboSelectFunction->clearCurrentFunction();
            ui->cboTriggerSource->clear();
            ui->cboTriggerAction->clear();
        }
    }
}

void MainWindow::cmdRemoveFunctionTrigger_clicked(bool)
{
    // Remove selected function trigger

    // We need to access the selection model to identify the rows selected.
    // This will only work correctly assuming we have set the selection to Rows and SingleSelection only (not multi)
    // But that makes the most sense so that is what we have done in the SetupFunctionTab routine

    QModelIndexList selectedList = ui->tblFunctionTriggers->selectionModel()->selectedRows();
    //QModelIndexList selectedList = ui->tblFunctionTriggers->selectionModel()->selectedIndexes();
    for( int i=0; i<selectedList.count(); i++)
    {
        QModelIndex index = selectedList.at(i);
        // I was doing this, but then when you sorted it, it would remove the wrong row
        // FT_TableModel->removeRow(index.row());
        // Now I map the proxy model to the source, and remove from the proxy.
        // This *seems* to be working
        FT_ProxyModel->mapToSource(index);
        FT_ProxyModel->removeRow(index.row());
    }
}
