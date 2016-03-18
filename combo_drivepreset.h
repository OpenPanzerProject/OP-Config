#ifndef DRIVEPRESETCOMBOBOX_H
#define DRIVEPRESETCOMBOBOX_H

#include <QObject>
#include <QComboBox>
#include <op_defines.h>

enum PRESET_TYPE
{   ptAccel,
    ptDecel
};

class DrivePresetComboBox : public QComboBox
{
    Q_OBJECT
public:
    DrivePresetComboBox(QWidget *parent = 0);
    void setCategory(PRESET_TYPE pt);
};


#endif // DRIVEPRESETCOMBOBOX_H
