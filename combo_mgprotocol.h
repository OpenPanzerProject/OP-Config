#ifndef IRMGPROTOCOLCOMBOBOX_H
#define IRMGPROTOCOLCOMBOBOX_H

#include <QObject>
#include <QComboBox>
#include <op_defines.h>

class MGProtocolComboBox : public QComboBox
{
    Q_OBJECT
public:
    MGProtocolComboBox(QWidget *parent = 0);
};

#endif // IRMGPROTOCOLCOMBOBOX_H

