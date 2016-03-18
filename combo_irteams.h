#ifndef IRTEAMSCOMBOBOX_H
#define IRTEAMSCOMBOBOX_H

#include <QObject>
#include <QComboBox>
#include <op_defines.h>

class IRTeamsComboBox : public QComboBox
{
    Q_OBJECT
public:
    IRTeamsComboBox(QWidget *parent = 0);

    void SetupNone(void);
    void SetupFOVTeams(void);
};

#endif // IRTEAMSCOMBOBOX_H


