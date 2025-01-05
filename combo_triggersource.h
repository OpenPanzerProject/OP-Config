#ifndef TRIGGERSOURCECOMBOBOX_H
#define TRIGGERSOURCECOMBOBOX_H

#include <QObject>
#include <QComboBox>
#include <op_defines.h>
#include <getopqmaps.h>

class TriggerSourceComboBox : public QComboBox
{
    Q_OBJECT
public:
    TriggerSourceComboBox(QWidget *parent = 0);

    _trigger_source getCurrentTriggerSource(void);
    void clearCurrentTriggerSource(void);       // Doesn't remove anything from the list, just sets the combo to select nothing

    boolean isTriggerSourceAux(_trigger_source);

    boolean isExternalInputAPresent(void);
    boolean isExternalInputBPresent(void);
    void addExternalInputA(void);
    void addExternalInputB(void);
    void removeExternalInputA(void);
    void removeExternalInputB(void);

signals:
    void externalInputA_Added(void);
    void externalInputB_Added(void);
    // void currentTriggerSourceChanged(const QString &oldTS, const QString &newTS, TriggerSourceComboBox *changedCombo);

public slots:
    void setCurrentTriggerSource(const _trigger_source& sf);
    void setCurrentTriggerSource(int);

private slots:
    // void CurrentTriggerSourceChangedSlot(const QString &newTriggerSource);   // We will connect this slot to the built-in index changed, and emit our custom signals

private:
  boolean _EIA_Present = false;
  boolean _EIB_Present = false;
  OP_QMaps *OPQMap;
  QMap<_trigger_source, QString> TSQMap;
  QMap<_trigger_source, QString> TSDigitalQMap;
  QMap<_trigger_source, QString> TSAnalogQMap;
};

#endif // TRIGGERSOURCECOMBOBOX_H
