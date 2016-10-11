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

    // Sabertooth configuration button, label and flag
    connect(ui->cboMotorSerialBaud, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSabertoothBaudLabel()));
    connect(ui->cmdSetSabertoothBaud, SIGNAL(released()), this, SLOT(cmdSetSabertoothBaud_clicked()));
    ui->lblSetSabertoothBaud->setText(QString("Set Sabertooth baud rate to: %1").arg(ui->cboMotorSerialBaud->currentData().toUInt()));
    ui->cmdSetSabertoothBaud->setEnabled(false);
    ui->cmdSetSabertoothBaud->setChecked(false);
    setSabertoothBaudRate = false;

    // Pololu configuration buttons and flags
    connect(ui->cmdConfigPololuDrive, SIGNAL(released()), this, SLOT(cmdConfigurePololuDrive_clicked()));
    connect(ui->cmdConfigPololuTurret, SIGNAL(released()), this, SLOT(cmdConfigurePololuTurret_clicked()));
    ui->cmdConfigPololuDrive->setEnabled(false);
    ui->cmdConfigPololuTurret->setEnabled(false);
    configurePololuDrive = false;
    configurePololuTurret = false;
}

void MainWindow::updateSabertoothBaudLabel()
{
    ui->lblSetSabertoothBaud->setText(QString("Set Sabertooth baud rate to: %1").arg(ui->cboMotorSerialBaud->currentData().toUInt()));
}

void MainWindow::cmdSetSabertoothBaud_clicked()
{
uint8_t desired_baud;

    // Tell the TCB to configure the Sabertooth device (V2 versions only) for the current Serial2 baud rate
    if (!setSabertoothBaudRate)    // Don't start configuration if one is already going
    {
        switch (ui->cboMotorSerialBaud->currentData().toUInt())
        {
            case 2400:
                desired_baud = SABERTOOTH_BAUD_2400;
                break;
            case 9600:
                desired_baud = SABERTOOTH_BAUD_9600;
                break;
            case 19200:
                desired_baud = SABERTOOTH_BAUD_19200;
                break;
            case 38400:
                desired_baud = SABERTOOTH_BAUD_38400;
                break;
            case 115200:
                desired_baud = SABERTOOTH_BAUD_115200;
                break;
            default:
                // Should not end up here
                desired_baud = 0;
                return;
        }
        ui->cmdSetSabertoothBaud->setChecked(true);
        ui->cmdSetSabertoothBaud->setText(QString("Please Wait"));
        comm->SetSabertoothBaudRate(desired_baud);
        setSabertoothBaudRate = true;    // Set flag
    }
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
