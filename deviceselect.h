#ifndef DEVICESELECT_H
#define DEVICESELECT_H

#include <QDialog>
#include <devices.h>
#include <mainwindow.h>

namespace Ui {
    class deviceselect;
}

class deviceselect : public QDialog
{
    Q_OBJECT

public:
    explicit deviceselect(QWidget *parent = 0);
    ~deviceselect();

signals:
    void buttonClickedSignal(OP_device_name);

private slots:
    void on_cmdTCB_clicked();
    void on_cmdMiniTCB_clicked();
    void on_cmdScoutESC_clicked();

private:
    Ui::deviceselect *ui;

    OP_device_name WhichDevice;
};

#endif // DEVICESELECT_H
