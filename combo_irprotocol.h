#ifndef IRPROTOCOLCOMBOBOX_H
#define IRPROTOCOLCOMBOBOX_H

#include <QObject>
#include <QComboBox>
#include <op_defines.h>

class IRProtocolComboBox : public QComboBox
{
    Q_OBJECT
public:
    IRProtocolComboBox(QWidget *parent = 0);

    void SetupPrimary(void);
    void SetupSecondary(IRTYPES skipType = IR_UNKNOWN);

    void InsertNoneSelection(void);
    void InsertDisableSelection(void);

};

#endif // IRPROTOCOLCOMBOBOX_H

