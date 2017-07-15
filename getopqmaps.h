#ifndef GET_OP_QMAPS_H
#define GET_OP_QMAPS_H

#include <QMap>
#include <QString>
#include <op_defines.h>

class OP_QMaps
{
public:
    OP_QMaps();

    // Special functions
    QMap<_special_function, QString> getAllSpecialFunctionsQMap();
    QMap<_special_function, QString> getDigitalSpecialFunctionsQMap();
    QMap<_special_function, QString> getAnalogSpecialFunctionsQMap();
    QMap<_special_function, QString> getEmptySpecialFunctionsQMap();
    boolean isSpecialFunctionDigital(_special_function sf);
    uint8_t GetSpecialFunctionExternalPortNum(_special_function sf);

    // Trigger sources
    QMap<_trigger_source, QString> getAllTriggerSourcesQMap();
    QMap<_trigger_source, QString> getDigitalTriggerSourcesQMap();
    QMap<_trigger_source, QString> getAnalogTriggerSourcesQMap();
    QMap<_trigger_source, QString> getAuxChannelTriggerSourcesQMap();
    QMap<_trigger_source, QString> getEmptyTriggerSourcesQMap();
    boolean isTriggerSourceAuxChannel(_trigger_source);
    QString getTriggerDescription(_trigger_source);

    // Trigger actions
    QMap<turretStick_positions, QString> getTurretStickSpecialPositionsQMap();


private:
    // Special functions
    QMap<_special_function, QString> _SF_ALL_QMAP;
    QMap<_special_function, QString> _SF_DIGITAL_QMAP;
    QMap<_special_function, QString> _SF_ANALOG_QMAP;
    QMap<_special_function, QString> _SF_PORTS_QMAP;
    QMap<_special_function, QString> _SF_EMPTY_QMAP;

    // Trigger sources
    QMap<_trigger_source, QString> _OPT_ALL_QMAP;
    QMap<_trigger_source, QString> _OPT_DIGITAL_QMAP;
    QMap<_trigger_source, QString> _OPT_ANALOG_QMAP;
    QMap<_trigger_source, QString> _OPT_AUX_QMAP;
    QMap<_trigger_source, QString> _OPT_EMPTY_QMAP;

    // Turret stick special positions
    QMap<turretStick_positions, QString> _SP_TURRET_STICK;
};

#endif
