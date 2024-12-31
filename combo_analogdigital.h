#ifndef ANALOGDIGITALCOMBOBOX_H
#define ANALOGDIGITALCOMBOBOX_H

#include <QObject>
#include <QComboBox>
#include <op_defines.h>

class AnalogDigitalComboBox : public QComboBox
{
    Q_OBJECT
public:
    AnalogDigitalComboBox(QWidget *parent = 0);

private slots:
  void AnalogDigitalChangedSlot(const int);

private:

signals:
  void analogDigitalChanged(AnalogDigitalComboBox *);

};

#endif // ANALOGDIGITALCOMBOBOX_H
