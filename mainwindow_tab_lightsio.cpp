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
    // External I/O type (analog vs "digital" inputs - although in fact we will read all inputs via analogRead)
    ui->cboPortA_InputType->insertItem(0, "Analog (variable)", 0);
    ui->cboPortA_InputType->insertItem(1, "Digital (on/off)",1);
    ui->cboPortB_InputType->insertItem(0, "Analog (variable)", 0);
    ui->cboPortB_InputType->insertItem(1, "Digital (on/off)",1);

    // Signals and slots
    // This adds/removes the manual High Intensity flash function from the list depending on if the user wants to trigger
    // it manually or automatically with cannon fire.
    connect(ui->chkHiFlashWithCannon, SIGNAL(clicked(bool)), this, SLOT(SetHiFlashAuto(bool)));
    // If external I/O is set to output, hide the input type combo, or show it if set to input
    // Also save the current setting to our variable
    connect(ui->cboPortADataDirection, SIGNAL(currentIndexChanged(int)), this, SLOT(ShowHideInputAType(int)));
    connect(ui->cboPortBDataDirection, SIGNAL(currentIndexChanged(int)), this, SLOT(ShowHideInputBType(int)));
    // On any input type change, save setting to variable
    connect(ui->cboPortA_InputType, SIGNAL(currentIndexChanged(int)), this, SLOT(SavePortA_InputType(int)));
    connect(ui->cboPortB_InputType, SIGNAL(currentIndexChanged(int)), this, SLOT(SavePortB_InputType(int)));

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
void MainWindow::ShowHideInputAType(int indexnum)
{
    // Any change, save to our variable
    DeviceData.PortA.Settings.dataDirection = ui->cboPortADataDirection->itemData(indexnum).toUInt();

    // Now take some action depending on what it is
    if (DeviceData.PortA.Settings.dataDirection == 1)  // 1 means output
    {
        // If Port A data direction is set to output, disable the input-type combo (digital/analog)
        if (ui->cboPortA_InputType->findText("") == -1)
            ui->cboPortA_InputType->addItem("");
        ui->cboPortA_InputType->setCurrentText("");
        ui->cboPortA_InputType->setEnabled(false);
        DeviceData.PortA.Settings.Digital = true;  // Default to digital in our variable so it still has a valid number
    }
    else
    {
        // First set the type to the actual number in variable, not the empty selection
        ui->cboPortA_InputType->setCurrentIndex(ui->cboPortA_InputType->findData(DeviceData.PortA.Settings.Digital));
        // Now we're off the empty selection, remove it
        ui->cboPortA_InputType->removeItem(ui->cboPortA_InputType->findText(""));
        // Now re-enable
        ui->cboPortA_InputType->setEnabled(true);
    }

    // Either way, we must check this change against our existing function-triggers!
    if (FT_TableModel->checkExternalPortDirectionAgainstFunctionTriggers(1, DeviceData.PortA.Settings.dataDirection))
        RemovedFunctionTriggersMsgBox();
}
void MainWindow::SavePortA_InputType(int indexnum)
{
    // Any change, save to our variable
    DeviceData.PortA.Settings.Digital = ui->cboPortA_InputType->itemData(indexnum).toBool();

    // We also need to check this change against our function triggers in case any are no longer valid
    if (FT_TableModel->checkExternalPortInputTypeAgainstFunctionTriggers(1, DeviceData.PortA.Settings.Digital))
        RemovedFunctionTriggersMsgBox();
}
void MainWindow::ShowHideInputBType(int indexnum)
{
    // Any change, save to our variable
    DeviceData.PortB.Settings.dataDirection = ui->cboPortBDataDirection->itemData(indexnum).toUInt();

    // Now take some action depending on what it is
    if (DeviceData.PortB.Settings.dataDirection == 1)  // 1 means output
    {
        // If Port B data direction is set to output, disable the input-type combo (digital/analog)
        if (ui->cboPortB_InputType->findText("") == -1)
            ui->cboPortB_InputType->addItem("");
        ui->cboPortB_InputType->setCurrentText("");
        ui->cboPortB_InputType->setEnabled(false);
        DeviceData.PortB.Settings.Digital = true;  // Default to digital in our variable so it still has a valid number
    }
    else
    {
        // First set the type to the actual number in variable, not the empty selection
        ui->cboPortB_InputType->setCurrentIndex(ui->cboPortB_InputType->findData(DeviceData.PortB.Settings.Digital));
        // Now we're off the empty selection, remove it
        ui->cboPortB_InputType->removeItem(ui->cboPortB_InputType->findText(""));
        // Now re-enable
        ui->cboPortB_InputType->setEnabled(true);
    }

    // Either way, we must check this change against our existing function-triggers!
    if (FT_TableModel->checkExternalPortDirectionAgainstFunctionTriggers(2, DeviceData.PortA.Settings.dataDirection))
        RemovedFunctionTriggersMsgBox();
}
void MainWindow::SavePortB_InputType(int indexnum)
{
    // Any change, save to our variable
    DeviceData.PortB.Settings.Digital = ui->cboPortB_InputType->itemData(indexnum).toBool();

    // We also need to check this change against our function triggers in case any are no longer valid
    if (FT_TableModel->checkExternalPortInputTypeAgainstFunctionTriggers(2, DeviceData.PortA.Settings.Digital))
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

