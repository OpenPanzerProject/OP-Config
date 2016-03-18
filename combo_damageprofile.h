#ifndef DAMAGEPROFILECOMBOBOX_H
#define DAMAGEPROFILECOMBOBOX_H

#include <QObject>
#include <QComboBox>
#include <op_defines.h>

class DamageProfileComboBox : public QComboBox
{
    Q_OBJECT
public:
    DamageProfileComboBox(QWidget *parent = 0);
};

#endif // DAMAGEPROFILECOMBOBOX_H


