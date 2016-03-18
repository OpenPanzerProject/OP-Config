#include "deviceselect.h"
#include "ui_deviceselect.h"

deviceselect::deviceselect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deviceselect)
{
    ui->setupUi(this);

    MainWindow *w = new MainWindow();

    connect(this, SIGNAL(buttonClickedSignal(OP_device_name)), w, SLOT(setDevice(OP_device_name)));
}


deviceselect::~deviceselect()
{
    delete ui;
}

void deviceselect::on_cmdTCB_clicked()
{
    const OP_device_name SelectedDevice = TCB;
    emit buttonClickedSignal(SelectedDevice);
    this->close();
}

void deviceselect::on_cmdMiniTCB_clicked()
{
    const OP_device_name SelectedDevice = MiniTCB;
    emit buttonClickedSignal(SelectedDevice);
    this->close();
}

void deviceselect::on_cmdScoutESC_clicked()
{
    const OP_device_name SelectedDevice = ScoutESC;
    emit buttonClickedSignal(SelectedDevice);
    this->close();
}
