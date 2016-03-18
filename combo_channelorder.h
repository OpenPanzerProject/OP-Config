#ifndef CHANNELORDERCOMBOBOX_H
#define CHANNELORDERCOMBOBOX_H

#include <QObject>
#include <QComboBox>
#include <op_defines.h>



class ChannelOrderComboBox : public QComboBox
{
    Q_OBJECT
public:
    ChannelOrderComboBox(QWidget *parent = 0);
    void setup(boolean isAux);
    boolean isAux();

private slots:
  void channelNumberChangedSlot(const QString &newChannel);

private:
  QString _priorChannel;
  boolean _isAux;

signals:
  void channelNumberChanged(const QString &oldChannel, const QString &newChannel, ChannelOrderComboBox *changedCombo);
  //void currentIndexChanged(int, ChannelOrderComboBox *changedCombo);

};

#endif // CHANNELORDERCOMBOBOX_H

