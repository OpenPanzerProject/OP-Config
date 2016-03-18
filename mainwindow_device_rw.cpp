#include "mainwindow.h"
#include "ui_mainwindow.h"

// See second half of this file for device reading/writing functions

//------------------------------------------------------------------------------------------------------------------------>>
// DEVICE - CONNECT/DISCONNECT/ERROR HANDLING
//------------------------------------------------------------------------------------------------------------------------>>
// This gets called when the user clicks on the connect/disconnect button
void MainWindow::toggleDeviceConnection()
{
    // First, we ignore any clicks if we are in the middle of flashing
    if (AttemptFlash)
    {
        ui->cmdConnect->setChecked(false);  // Don't let the button check
        return;                             // Exit
    }

    // Otherwise,
    if (comm->isConnected())
    {
        disconnectFromDevice();
    }
    else
    {
        ClearConsole();                    // Clear the console window
        MouseWait();                       // Wait cursor
        ui->cmdConnect->setChecked(true);  // "Check" (depress) the button, but disable it and set the text to wait
            ui->cmdConnect->setText("wait");
                ui->cmdConnect->setEnabled(false);
        // Also disable these controls
        ui->cboCOMPorts->setEnabled(false);
        ui->cboConsoleBaud->setEnabled(false);
        ui->cmdSnoop->setEnabled(false);
        ui->cmdFlashHex->setEnabled(false);
        AttemptConnect = true;             // Set a flag to indicate a connection attempt is underway
        SerialStatus_SetAttemptConnect();  // Set the serial status label
        connectToDevice();                 // Now try to connect. Either it will succeed, and button will be re-enabled with
     }                                     // text of "Disconnect", or it will fail and button will be re-enabled with text of "Connect"
}
void MainWindow::connectToDevice()
{
    comm->openSerial_forComms();
}
void MainWindow::disconnectFromDevice()
{
    comm->closeSerial();
}
void MainWindow::ShowConnectionStatus(boolean connected)
{
    AttemptConnect = false; // The attempt is over, we know now whether we are actually connected or not.
    MouseRestore();

    if (connected)
    {
        SetStatusLabel("Connected to device",slNeutral);
        ui->actionConnect->setEnabled(false);   // Disable connect action, we are connected
        ui->actionDisconnect->setEnabled(true); // Enable disconnect action
        ui->cmdConnect->setChecked(true);       // "Check" connect button
            ui->cmdConnect->setText("Disconnect");  // Change text to "disconnect"
                ui->cmdConnect->setEnabled(true);
        ui->actionRead->setEnabled(true);       // Read action enabled
        ui->cmdReadDevice->setEnabled(true);    // Read device button enabled
        ui->actionWrite->setEnabled(true);      // Write action enabled
        ui->cmdWriteDevice->setEnabled(true);   // Write device button enabled
        ui->cmdRadioStream->setEnabled(true);   // Radio streaming button is enabled

        // It won't matter, but it's confusing if the user can change COM port or baud rate while connected.
        ui->cboCOMPorts->setEnabled(false);
        ui->cboConsoleBaud->setEnabled(false);

        // However we do re-enabled the Snoop and Flash buttons. If they are clicked they will cause a disconnect, but that's ok
        ui->cmdFlashHex->setEnabled(true);
        ui->cmdSnoop->setEnabled(true);

        statusProgressBar->hide();
            qApp->processEvents();

        // Set read/write flags to false. Shouldn't be necessary but just to be safe.
        resetReadWriteProcess();

        // Update serial status Label
        SerialStatus_SetConnected();

        // First thing after connection, is we send a request for the firmware version
        comm->requestFirmwareVersion();
    }
    else
    {
        if (!AttemptFlash)  SetStatusLabel("Disconnected from device",slBad);   // If we disconnected to try flashing, we don't need a warning
        ui->actionConnect->setEnabled(true);    // Enable connect action
        ui->actionDisconnect->setEnabled(false);// Disabled disconnect action, we are disconnected
        ui->cmdConnect->setEnabled(true);       // Enable connect button in case it is still disconnected from a failed read/write operation
        ui->cmdConnect->setChecked(false);      // Un-"check" connect button
            ui->cmdConnect->setText("Connect"); //
                ui->cmdConnect->setEnabled(true);
        ui->actionRead->setEnabled(false);      // Read action disabled
        ui->cmdReadDevice->setEnabled(false);   // Read device button disabled
        ui->actionWrite->setEnabled(false);     // Write action disabled
        ui->cmdWriteDevice->setEnabled(false);  // Write device button disabled

        // Re-enable these controls
        ui->cboCOMPorts->setEnabled(true);
        ui->cboConsoleBaud->setEnabled(true);
        ui->cmdFlashHex->setEnabled(true);
        ui->cmdSnoop->setEnabled(true);

        // Reset radio streaming buttons in case we disconnected in the middle of a stream
        ui->cmdRadioStream->setChecked(false);
            ui->cmdRadioStream->setText("Read Radio");
                ui->cmdRadioStream->setEnabled(false);
        ui->cmdSaveCenters->setChecked(false);
                ui->cmdSaveCenters->setEnabled(false);
        ui->cmdSaveMinMax->setChecked(false);
                ui->cmdSaveMinMax->setEnabled(false);
        if (Flag_StartRadioStream) FadeOutRadioStreaming();
        Flag_StartRadioStream = false;

        // Set read/write flags to false
        resetReadWriteProcess();

        // Update the serial status Label - but not if we disconnected to try flashing, in that case
        // the flashing routine will set its own message.
        if (!AttemptFlash) SerialStatus_SetNotConnected();

        // Hide status bar
        statusProgressBar->hide();
            qApp->processEvents();
    }
}
void MainWindow::ProcessCommError(QString, QSerialPort::SerialPortError )
{   // QString errorText, QSerialPort::SerialPortError errNum
    // Actually, for a given number, the text can be different at different times...
    // 2 - Access is denied (usually because you have the port open in the Arduino IDE)
    // 5  - Unknown error
    // 9  - The handle is invalid
    // 11 - Unknown error
    //qDebug() << "Comm Error Num: " << errNum << " Text: " << errorText;

    // Don't even show this. It shows up when the error isn't even an issue, and is just confusing
    //SetStatusLabel("Comm Error",slBad);

    // But mostly, these errors are too bad, but there's no point in bothering the user with them.
    // Just let the connect fail and they can try again.
//    if (errNum == 9 || errNum == 11)
//    {   // No point in showing these worthless errors to user
//        qDebug() << "Suck it";
//    }
//    else
//    {
//       msgBox(errorText, vbOkOnly, "CommunicationErrr", vbCritical);
//    }
}



//------------------------------------------------------------------------------------------------------------------------>>
// DEVICE - READING AND WRITING
//------------------------------------------------------------------------------------------------------------------------>>
void MainWindow::resetReadWriteProcess()
{
    nextVarPos = 0;
    readAllSettings = false;
    writeAllSettings = false;
    writeSomeSettings = false;
}
void MainWindow::updateVarArray_fromSerial(uint16_t ID, QByteArray value)
{
    // This function triggers when we receive back the value of a setting we requested from the device

    // Update the value in our array
    updateVarArray_byID(ID, value);

    // If we are in the middle of reading all settings sequentially, proceed to next
    if (readAllSettings)
    {
        // In this case we want to read every setting, so as soon as one is read in,
        // we request the next.
        if (nextVarPos < NUM_STORED_VARS)       // NUM_STORED_VARS is the absolute number but since the array is zero-based that last position will be 1-less
        {
            statusProgressBar->setValue(nextVarPos);     // Update progress bar
            sendReadCommand_byPos(nextVarPos);           // request next variable
            nextVarPos += 1;                             // increment for next time
        }
        else
        {
            readAllSettings = false;
            nextVarPos = 0;
            // Done with progress bar
            statusProgressBar->hide();
                qApp->processEvents();
            // Now we're done, we can re-enable these
            reEnableDeviceActions();

            // Ok, we've loaded the settings from our device into VarArray.
            // Now we need to copy the VarArray to named variables,
            // and then copy the named variables to our controls.
            VarArray_to_Variables();
            Variables_to_Controls();

            // If we make it here, by definition we read everything
            SetStatusLabel(QString("All settings read (100%)"),slGood);
            ui->cmdReadDevice->setChecked(false);
            ui->cmdSnoop->setEnabled(true);
            ui->cmdFlashHex->setEnabled(true);
            MouseRestore();
        }
    }
}
// This reads all settings sequentially
void MainWindow::readSettingsFromDevice(void)
{
    MouseWait();
    ui->cmdReadDevice->setChecked(true);
    ui->cmdSnoop->setEnabled(false);
    ui->cmdFlashHex->setEnabled(false);

    readAllSettings = true;                 // Set the read all flag
    nextVarPos = 2;                         // Next one will be number 2

    // Show and initialize the progress bar
    statusProgressBar->show();
            qApp->processEvents();
    statusProgressBar->setRange(1, NUM_STORED_VARS);
    statusProgressBar->setValue(1);

    // Don't allow user to disconnect/read/write while we are in the midst of reading/writing
    tempDisableDeviceActions();

    sendReadCommand_byPos(1);               // Read the first value
    // Now when the value is read, the readAllSettings flag will cause the read routine to request
    // the next variable, until they have finally all been read. This will be done in updateVarArray_fromSerial
}
// Send a command to device to return a value
void MainWindow::sendReadCommand_byPos(uint16_t VarPos)
{
    if (VarPos > 0 && VarPos < NUM_STORED_VARS) // Last number is actually one less than NUM_STORED_VARS
    {
        comm->readEEPROM(STORAGEVARS[VarPos].varID);
    }
}
// This writes all settings sequentially
void MainWindow::writeAllSettingsToDevice()
{
    MouseWait();
    ui->cmdWriteDevice->setChecked(true);
    ui->cmdSnoop->setEnabled(false);
    ui->cmdFlashHex->setEnabled(false);
    writeAllSettings = true;        // Set the write all flag
    startVarPos = 1;                // We are writing all vars, so start at 1 and got to NUM_STORED_VARS - 2
    endVarPos = NUM_STORED_VARS - 2;// Minus 2 because: -1 because the array is zero-based and NUM_STORED_VARS is the actual count
                                    //                  -1 another because we don't write the last variable, which is InitStamp. We
                                    //                     can read it, but we don't write it to the device (otherwise the device may
                                    //                     re-initialize to its internal defaults after we've updated it with our new
                                    //                     values. InitStamp is for use by the device only).
    nextVarPos = 2;                 // Next var will be number 2

    // Before we can write our settings, we need to make sure VarArray is updated with the current values
    // from the form
    Controls_to_Variables();        // This puts the control values into our named variables
    Variables_to_VarArray();        // This copies our named variables into the VarArray

    // Show and initialize the progress bar
    statusProgressBar->show();
            qApp->processEvents();
    statusProgressBar->setRange(startVarPos, endVarPos);
    statusProgressBar->setValue(startVarPos);

    // Don't allow user to disconnect/read/write while we are in the midst of reading/writing
    tempDisableDeviceActions();

    sendWriteCommand_byPos(startVarPos);  // Write the first value
    // Now when the value is written, and the device responds, the writeAllSettings flag will cause the acknowledgment routine
    // to send the next variable to be written, until they have finally all been sent. This will be done in processNextSentence
}
void MainWindow::writeSomeSettingsToDevice(uint16_t startID, uint16_t endID)
{
    // Similar to the above, but here we're writing a subset of values starting from one ID and ending at another ID
    writeSomeSettings = true;        // Set the write all flag

    // This routine takes variable IDs but we actually send data by incrementing the variable position in the array
    startVarPos = findStorageArrayPosition(startID);
    endVarPos = findStorageArrayPosition(endID);
    if (endID == 9999) endVarPos -= 1;  // Don't write InitStamp. If that is the last var, only send up to the var before it.
    //qDebug() << "Start Pos: " << startVarPos << " End Pos: " << endVarPos;
    nextVarPos = startVarPos + 1;

    // Before we can write our settings, we need to make sure VarArray is updated with the current values
    // from the form
    Controls_to_Variables();        // This puts the control values into our named variables
    Variables_to_VarArray();        // This copies our named variables into the VarArray

    // Show and initialize the progress bar
    statusProgressBar->show();
            qApp->processEvents();
    statusProgressBar->setRange(startVarPos, endVarPos);
    statusProgressBar->setValue(startVarPos);

    // Don't allow user to disconnect/read/write while we are in the midst of reading/writing
    tempDisableDeviceActions();

    sendWriteCommand_byPos(startVarPos);  // Write the first value
    // Now when the value is written, and the device responds, the writeSomeSettings flag will cause the acknowledgment routine
    // to send the next variable to be written, until they have finally all been sent. This will be done in processNextSentence.

}
void MainWindow::sendWriteCommand_byPos(uint16_t VarPos)
{
    // Make sure this is a valid variable
    if (VarPos > 0 && VarPos < NUM_STORED_VARS) // Last number is actually one less than NUM_STORED_VARS.
    {                                           // We assume we won't be passed InitStamp (last var) but if we are, this routine will still write it.
        comm->writeEEPROM(STORAGEVARS[VarPos].varID, VarArray.value(STORAGEVARS[VarPos].varID));
    }
}
// When the device responds with a SERID_NEXT_SENTENCE request
void MainWindow::processNextSentence(void)
{

    // If we receive a next sentence request from the device, it is ready for next.
    // In some cases we don't need to do anything specifically here, but if
    // we are in the middle of writing all settings sequentially, proceed to next
    if (writeAllSettings || writeSomeSettings)
    {
        if (nextVarPos <= endVarPos)
        {
            statusProgressBar->setValue(nextVarPos);    // Update progress bar
            sendWriteCommand_byPos(nextVarPos);         // send next variable
            nextVarPos += 1;                            // increment for next time
        }
        else
        {
            // If we make it here, by definition we wrote everything we wanted to
            // But, we might want to display a different message depending on what was written
            if (writeSomeSettings && Flag_RadioValuesChanged)
            {
                SetStatusLabel(QString("Radio settings saved"),slNeutral);
                Flag_RadioValuesChanged = false;    // We're done
            }
            else
            {   // We assume all other cases are "Write All Settings"
                SetStatusLabel(QString("All settings written (100%)"),slGood);
            }

            // We're done writing settings no matter who called it
            writeAllSettings = false;
            writeSomeSettings = false;
            nextVarPos = 0;

            // Done with progress bar
            statusProgressBar->hide();
                qApp->processEvents();

            // Now we're done, we can re-enable these
            reEnableDeviceActions();
            ui->cmdWriteDevice->setChecked(false);
            ui->cmdSnoop->setEnabled(true);
            ui->cmdFlashHex->setEnabled(true);

            MouseRestore();
        }
    }
}
void MainWindow::tempDisableDeviceActions()
{
    // Don't allow user to disconnect/read/write while we are in the midst of reading/writing
    ui->actionDisconnect->setEnabled(false);
    ui->cmdConnect->setEnabled(false);
    ui->actionRead->setEnabled(false);
    ui->cmdReadDevice->setEnabled(false);
    ui->actionWrite->setEnabled(false);
    ui->cmdWriteDevice->setEnabled(false);

    ui->cmdRadioStream->setEnabled(false);
    ui->cmdSaveCenters->setEnabled(false);
    ui->cmdSaveMinMax->setEnabled(false);
}
void MainWindow::reEnableDeviceActions()
{
    // After reading/writing operation is complete, we re-enable these
    ui->actionDisconnect->setEnabled(true);
    ui->cmdConnect->setEnabled(true);
    ui->actionRead->setEnabled(true);
    ui->cmdReadDevice->setEnabled(true);
    ui->actionWrite->setEnabled(true);
    ui->cmdWriteDevice->setEnabled(true);

    ui->cmdRadioStream->setEnabled(true);
    if (comm->isRadioStreaming())   // These only get re-enabled if we are presently streaming.
    {
        ui->cmdSaveCenters->setEnabled(true);
        ui->cmdSaveMinMax->setEnabled(true);
    }
}
