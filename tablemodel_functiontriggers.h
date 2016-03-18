#ifndef FUNCTIONTRIGGERTABLEMODEL_H
#define FUNCTIONTRIGGERTABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QList>
#include <op_defines.h>
#include <getopqmaps.h>
#include <QDebug>

struct functionTriggerData{
    _functionTrigger functionTrigger;
    QString FunctionDescription;
    QString TriggerDescription;
};

class FunctionTriggerTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    FunctionTriggerTableModel(QObject *parent=0);
    FunctionTriggerTableModel(QList< functionTriggerData > ftdata, QObject *parent=0);

    // These are required functions for subclassing
    int rowCount(const QModelIndex &index=QModelIndex()) const;
    int columnCount(const QModelIndex &index=QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
    bool insertRows(int position, int rows, const QModelIndex &index=QModelIndex());
    bool insertRow(int position, const QModelIndex &index=QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex());
    bool removeRow(int position, const QModelIndex &index=QModelIndex());

    // These are custom functions
    QList< functionTriggerData > getList();
    bool insertFunctionTrigger(_special_function SpecialFunction, uint16_t TriggerID); // Allows us to add a row just by passing trigger ID and function ID
    QString errorText();
    bool ClearModel();
    QString getTriggerDescription(_special_function sf, uint16_t TriggerID);
    uint8_t getNumPositionsFromTriggerID(uint16_t TriggerID);
    uint8_t getTriggerActionFromTriggerID(uint16_t TriggerID);
    uint8_t getAuxChannelNumberFromTriggerID(uint16_t TriggerID);
    uint8_t getExternalPortNumberFromTriggerID(uint16_t TriggerID);
    boolean removeAuxTriggers(int AuxChannelNum);
    boolean checkAuxChannelTypesAgainstFunctionTriggers(int AuxChannelNum, boolean isDigital);
    boolean checkAuxChannelPositionsAgainstFunctionTriggers(int AuxChannelNum, int NumPositions);
    boolean checkExternalPortDirectionAgainstFunctionTriggers(int PortNum, boolean PortIsOutput);
    boolean checkExternalPortInputTypeAgainstFunctionTriggers(int PortNum, boolean isDigital);
    uint16_t TriggerIDAtRow(int row);
    _special_function SpecialFunctionAtRow(int row);
    boolean isTurretStickPresent(void);
    boolean removeFunctionFromList(_special_function sf);

private:
    void setErrorText(QString err_text);

    OP_QMaps *OPQMap;
    QMap<_special_function, QString> SFQMap;        // Used to get special function descriptions
    QMap<_trigger_source, QString> TSQMap;          // Used to help construct trigger description (this gives us the source, but not the action)
    QMap<turretStick_positions, QString> TurretPositionsQMap;  // Used to help construct the trigger description (turret stick actions)
    QList< functionTriggerData > listOfTriggerData; // This is actually our data model
    QString _error_text;

private slots:
    void CustomChangeSlot();

signals:
    void TurretStickPresent(boolean);
    void functionTriggerCount(int);
};

#endif // FUNCTIONTRIGGERTABLEMODEL_H

