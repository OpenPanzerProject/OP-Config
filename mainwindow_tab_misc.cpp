#include "mainwindow.h"
#include "ui_mainwindow.h"


//------------------------------------------------------------------------------------------------------------------------>>
// FORM CONTROLS - MISC TAB
//------------------------------------------------------------------------------------------------------------------------>>
void MainWindow::SetupControls_MiscTab()
{
    // Setup baud rate combo boxes
    //ui->cboUSBBaud->setCategory(bcUSBSerial);     // Leaving this hard-coded for now
    ui->cboAuxSerialBaud->setCategory(bcAuxSerial);
    ui->cboMotorSerialBaud->setCategory(bcMotorSerial);
    ui->cboSer3Baud->setCategory(bcSerial3);

    // Pololu configuration buttons
    connect(ui->cmdConfigPololuDrive, SIGNAL(released()), this, SLOT(cmdConfigurePololuDrive_clicked()));
    connect(ui->cmdConfigPololuTurret, SIGNAL(released()), this, SLOT(cmdConfigurePololuTurret_clicked()));
    // Start them disabled, they will be enabled once we're connected to the device
    ui->cmdConfigPololuDrive->setEnabled(false);
    ui->cmdConfigPololuTurret->setEnabled(false);
    // Initialize these to false
    configurePololuDrive = false;
    configurePololuTurret = false;
}

void MainWindow::cmdConfigurePololuDrive_clicked()
{
    // Tell the TCB to configure the Pololu device for drive motor
    if (!configurePololuDrive && !configurePololuTurret)    // Don't start configuration if one is already going
    {
        comm->ConfigurePololu_Drive();
        configurePololuDrive = true;    // Set flag
    }

}

void MainWindow::cmdConfigurePololuTurret_clicked()
{
    // Tell the TCB to configure the Pololu device for turret motor
    if (!configurePololuDrive && !configurePololuTurret)    // Don't start configuration if one is already going
    {
        comm->ConfigurePololu_Turret();
        configurePololuTurret = true;    // Set flag
    }
}
