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

}
