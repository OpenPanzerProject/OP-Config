#ifndef AUXCHANNELPOSITIONSCOMBO_H
#define AUXCHANNELPOSITIONSCOMBO_H

#include <QObject>
#include <QComboBox>
#include <op_defines.h>

class AuxChannelPositionsCombo : public QComboBox
{
    Q_OBJECT
public:
    AuxChannelPositionsCombo(QWidget *parent = 0);

private slots:
  void AuxChannelPositionChangedSlot(const QString &);

private:

signals:
  void AuxChannelPositionChanged(AuxChannelPositionsCombo *);

};

#endif // AUXCHANNELPOSITIONSCOMBO_H






