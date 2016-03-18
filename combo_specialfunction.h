#ifndef SPECIALFUNCTIONCOMBOBOX_H
#define SPECIALFUNCTIONCOMBOBOX_H

#include <QObject>
#include <QComboBox>
#include <op_defines.h>
#include <getopqmaps.h>
#include <QDebug>

class SpecialFunctionComboBox : public QComboBox
{
    Q_OBJECT
public:
    SpecialFunctionComboBox(QWidget *parent = 0);

    _special_function getCurrentFunction(void);
    void clearCurrentFunction(void);    // Remove a function from this trigger

    // I/O output functions
    boolean isExternalOutputAPresent(void);
    boolean isExternalOutputBPresent(void);
    void addExternalOutputsA(void);
    void addExternalOutputsB(void);
    void removeExternalOutputsA(void);
    void removeExternalOutputsB(void);
    boolean isFunctionDigital(_special_function sf);

    // Servo pass-through functions
    void addServoPassthrough(int);
    void addAllServoPassthroughs(void);
    void removeServoPassthrough(int);
    void removeAllServoPassthroughs(void);
    boolean isServoPassthroughPresent(int);

    // Generic add/remove function
    void AddSF(_special_function sf);
    void RemoveSF(_special_function sf);
    boolean isSFPresent(_special_function sf);


signals:
    void externalOutputsA_Added(void);
    void externalOutputsB_Added(void);
    void currentFunctionChanged(_special_function, boolean);
    void servoPassthroughAdded(int);
    void specialFunctionAdded(_special_function);
    void specialFunctionRemoved(_special_function);

public slots:
    void setCurrentFunction(const _special_function& sf);
    void setCurrentFunction(int);

private slots:
    void CurrentFunctionChangedSlot(const QString &newFunction);                 // We will connect this slot to the built-in index changed, and emit our custom signals

private:
  OP_QMaps *OPQMap;
  QMap<_special_function, QString> SFQMap;
  QMap<_special_function, QString> SFDigitalQMap;
  QMap<_special_function, QString> SFAnalogQMap;
  boolean _EOA_Present = false;
  boolean _EOB_Present = false;
  boolean _Servo1_Present = false;
  boolean _Servo2_Present = false;
  boolean _Servo3_Present = false;
  boolean _Servo4_Present = false;
};

#endif // SPECIALFUNCTIONCOMBOBOX_H


