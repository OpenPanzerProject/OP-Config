#include "mainwindow.h"
#include "ui_mainwindow.h"


//------------------------------------------------------------------------------------------------------------------------>>
// FORM CONTROLS - LIGHTS & IO TAB
//------------------------------------------------------------------------------------------------------------------------>>
void MainWindow::SetupControls_LightsIOTab(void)
{
    // Setup external I/O data direction combo boxes
    ui->cboPortADataDirection->insertItem(0, "Input", DD_INPUT); // Arduino data-direction flag is 0 for input
    ui->cboPortADataDirection->insertItem(1, "Output",DD_OUTPUT); // Arduino data-direction flag is 1 for output
    ui->cboPortBDataDirection->insertItem(0, "Input", DD_INPUT); // Arduino data-direction flag is 0 for input
    ui->cboPortBDataDirection->insertItem(1, "Output",DD_OUTPUT); // Arduino data-direction flag is 1 for output
    ui->cboPortA_DataType->insertItem(0, "Analog (variable)", 0);   // Initialize to types under Analog direction
    ui->cboPortA_DataType->insertItem(1, "Digital (on/off)",1);     // but they can be changed later if direction
    ui->cboPortB_DataType->insertItem(0, "Analog (variable)", 0);   // is changed
    ui->cboPortB_DataType->insertItem(1, "Digital (on/off)",1);

    // Signals and slots
    // This handles validation of Aux output usage if the user checks the option to auto-flash Aux output with cannon fire
    connect(ui->chkAuxFlashWithCannon, SIGNAL(clicked(bool)), this, SLOT(ValidateAuxFlash(bool)));
    // This adds/removes the manual High Intensity flash function from the list depending on if the user wants to trigger
    // it manually or automatically with cannon fire.
    connect(ui->chkHiFlashWithCannon, SIGNAL(clicked(bool)), this, SLOT(SetHiFlashAuto(bool)));
    // If external I/O is set to output, hide the input type combo, or show it if set to input
    // Also save the current setting to our variable
    connect(ui->cboPortADataDirection, SIGNAL(currentIndexChanged(int)), this, SLOT(SetupInputAType(int)));
    connect(ui->cboPortBDataDirection, SIGNAL(currentIndexChanged(int)), this, SLOT(SetupInputBType(int)));
    // On any input type change, save setting to variable
    connect(ui->cboPortA_DataType, SIGNAL(currentIndexChanged(int)), this, SLOT(SavePortA_InputType(int)));
    connect(ui->cboPortB_DataType, SIGNAL(currentIndexChanged(int)), this, SLOT(SavePortB_InputType(int)));

    // Additionally, depending on whether the external I/O is set to input or output, determines whether that port
    // get assigned as a trigger (input) or a function (output). We have extra slots for that
    connect(ui->cboPortADataDirection, SIGNAL(currentIndexChanged(int)), this, SLOT(SetupPortAFunctionTrigger(int)));
    connect(ui->cboPortBDataDirection, SIGNAL(currentIndexChanged(int)), this, SLOT(SetupPortBFunctionTrigger(int)));

    // Now we make sure the setup runs once at startup
    SetupPortAFunctionTrigger(ui->cboPortADataDirection->findData(ui->cboPortADataDirection->currentIndex()));
    SetupPortBFunctionTrigger(ui->cboPortBDataDirection->findData(ui->cboPortBDataDirection->currentIndex()));
}
void MainWindow::SetHiFlashAuto(bool isChecked)
{
    if (isChecked)
    {   // User wants the high intensity flash unit to flash automatically with cannon fire
        // We remove the manual flash function from the function list
        ui->cboSelectFunction->RemoveSF(SF_HI_FLASH);
        // Make sure we didn't already have a function trigger defined for it too
        if (FT_TableModel->removeFunctionFromList(SF_HI_FLASH)) { RemovedFunctionTriggersMsgBox(); }
    }
    else
    {   // User does not want the high-intensity flash unit to flash automatically with cannon fire.
        // Add a manual control option to the function list instead.
        // The add function will only add it if it isn't there already
        ui->cboSelectFunction->AddSF(SF_HI_FLASH);
    }
}
void MainWindow::ValidateAuxFlash(bool isChecked)
{

    if (isChecked)
    {
        // In this case we are using the Aux Output for a cannon flash so we disable the Flicker Lights during Engine Start option
        // which would conflict with the use of the Aux output
        if (ui->chkFlickerHeadlights->isChecked() == true)
        {
            ui->chkFlickerHeadlights->setChecked(false);
            // msgBox("The Flicker Lights during Engine Start option will not be available under Separate Heat & Fan "
            //        "because it would create a conflict with the use of the Aux output. That option has been disabled on the Lights tab.",vbOkOnly,"Flicker Lights Option Disabled",vbExclamation);
        }
        DeviceData.FlickerLightsOnEngineStart = false;
        ui->chkFlickerHeadlights->setEnabled(false);
        ui->lblFlickerLights->setEnabled(false);
    }
    else
    {
        // Here we can permit the "Flicker Lights during Engine Start" setting to become active since the Aux output will
        // not be used for the cannon flash, BUT we also need to make sure that it isn't being reserved for the smoker fan
        if (ui->cboSmokerType->currentData() != SMOKERTYPE_ONBOARD_SEPARATE)
        {
            ui->chkFlickerHeadlights->setEnabled(true);
            ui->lblFlickerLights->setEnabled(true);
        }
    }
}
void MainWindow::SetupInputAType(int indexnum)
{
    // Any change, save to our variable
    DeviceData.PortA.Settings.dataDirection = ui->cboPortADataDirection->itemData(indexnum).toUInt();

    // Now take some action depending on what it is
    if (DeviceData.PortA.Settings.dataDirection == 1)  // 1 means output
    {
        // Port A data direction is set to output:
        ui->cboPortA_DataType->setItemText(0, "Default Low");
        ui->cboPortA_DataType->setItemText(1, "Default High");
    }
    else
    {
        // Port A data direction is set to input:
        ui->cboPortA_DataType->setItemText(0, "Analog (variable)");
        ui->cboPortA_DataType->setItemText(1, "Digital (on/off)");
    }

    // Set the type to the actual number in variable
    ui->cboPortA_DataType->setCurrentIndex(ui->cboPortA_DataType->findData(DeviceData.PortA.Settings.dataType));

    // Either way, we must check this change against our existing function-triggers!
    if (FT_TableModel->checkExternalPortDirectionAgainstFunctionTriggers(1, DeviceData.PortA.Settings.dataDirection))
        RemovedFunctionTriggersMsgBox();
}
void MainWindow::SavePortA_InputType(int indexnum)
{
    // Any change, save to our variable
    DeviceData.PortA.Settings.dataType = ui->cboPortA_DataType->itemData(indexnum).toUInt();

    // We also need to check this change against our function triggers in case any are no longer valid
    if (FT_TableModel->checkExternalPortInputTypeAgainstFunctionTriggers(1, DeviceData.PortA.Settings.dataType))
        RemovedFunctionTriggersMsgBox();
}
void MainWindow::SetupInputBType(int indexnum)
{
    // Any change, save to our variable
    DeviceData.PortB.Settings.dataDirection = ui->cboPortBDataDirection->itemData(indexnum).toUInt();

    // Now take some action depending on what it is
    if (DeviceData.PortB.Settings.dataDirection == 1)  // 1 means output
    {
        // Port B data direction is set to output:
        ui->cboPortB_DataType->setItemText(0, "Default Low");
        ui->cboPortB_DataType->setItemText(1, "Default High");
    }
    else
    {
        // Port B data direction is set to input:
        ui->cboPortB_DataType->setItemText(0, "Analog (variable)");
        ui->cboPortB_DataType->setItemText(1, "Digital (on/off)");
    }

    // Set the type to the actual number in variable
    ui->cboPortB_DataType->setCurrentIndex(ui->cboPortB_DataType->findData(DeviceData.PortB.Settings.dataType));

    // Either way, we must check this change against our existing function-triggers!
    if (FT_TableModel->checkExternalPortDirectionAgainstFunctionTriggers(2, DeviceData.PortB.Settings.dataDirection))
        RemovedFunctionTriggersMsgBox();
}
void MainWindow::SavePortB_InputType(int indexnum)
{
    // Any change, save to our variable
    DeviceData.PortB.Settings.dataType = ui->cboPortB_DataType->itemData(indexnum).toUInt();

    // We also need to check this change against our function triggers in case any are no longer valid
    if (FT_TableModel->checkExternalPortInputTypeAgainstFunctionTriggers(2, DeviceData.PortA.Settings.dataType))
        RemovedFunctionTriggersMsgBox();
}
void MainWindow::SetupPortAFunctionTrigger(int indexnum)
{
    if (ui->cboPortADataDirection->itemData(indexnum) == 1)  // 1 means output
    {
        // If Port A data direction is set to output, we need to add the PortA output functions to our list of special functions,
        // while also making sure Port A is no longer in the list of triggers
        ui->cboSelectFunction->addExternalOutputsA();
        ui->cboTriggerSource->removeExternalInputA();
    }
    else
    {
        // But if Port A data direction is set to input, we need to remove the Port A output function from the function list.
        // We don't need to worry about adding Port A input to the trigger source list, because the trigger source list will
        // fill it in automatically as required.
        ui->cboSelectFunction->removeExternalOutputsA();
    }
}
void MainWindow::SetupPortBFunctionTrigger(int indexnum)
{
    if (ui->cboPortBDataDirection->itemData(indexnum) == 1)  // 1 means output
    {
        // If Port B data direction is set to output, we need to add the PortB output functions to our list of special functions,
        // while also making sure Port B is no longer in the list of triggers
        ui->cboSelectFunction->addExternalOutputsB();
        ui->cboTriggerSource->removeExternalInputB();
    }
    else
    {
        // But if Port B data direction is set to input, we need to remove the Port B output function from the function list.
        // We don't need to worry about adding Port B input to the trigger source list, because the trigger source list will
        // fill it in automatically as required.
        ui->cboSelectFunction->removeExternalOutputsB();
    }
}

