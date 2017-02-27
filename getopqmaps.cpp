#include "getopqmaps.h"

OP_QMaps::OP_QMaps()
{
}

// ---------------------------------------------------------------------------------------------------------->>
// SPECIAL FUNCTIONS
// ---------------------------------------------------------------------------------------------------------->>
boolean OP_QMaps::isSpecialFunctionDigital(_special_function sf)
{
    // Check this function against all in the digital list
    QMap<_special_function, QString> DSF;
    DSF = getDigitalSpecialFunctionsQMap();
    QMapIterator<_special_function, QString> i(DSF);
    while (i.hasNext())
    {
        i.next();
        if (i.key() == sf) return true;
    }
    return false;
}

uint8_t OP_QMaps::GetSpecialFunctionExternalPortNum(_special_function sf)
{
    // If this function is an external port output function,
    // return the port number (A=1, B=2)
    // This is just hard-coded, so it's one more thing to maintain, in addition to this whole page.
    switch (sf)
    {
        case SF_OUTPUT_A_TOGGLE:
        case SF_OUTPUT_A_ON:
        case SF_OUTPUT_A_OFF:
            return 1;
            break;
        case SF_OUTPUT_B_TOGGLE:
        case SF_OUTPUT_B_ON:
        case SF_OUTPUT_B_OFF:
            return 2;
            break;

        default:
            return 0;
    }

}

QMap<_special_function, QString> OP_QMaps::getAllSpecialFunctionsQMap()
{
    // Create the full Special Function list
    // These do not have to be in any specific order, unlike the list in op_defines.h
    _SF_ALL_QMAP.insert(SF_NULL_FUNCTION, "");  // No function
    _SF_ALL_QMAP.insert(SF_ENGINE_TOGGLE, "Engine - Toggle On/Off");
    _SF_ALL_QMAP.insert(SF_ENGINE_ON, "Engine - Turn On");
    _SF_ALL_QMAP.insert(SF_ENGINE_OFF, "Engine - Turn Off");
    _SF_ALL_QMAP.insert(SF_TRANS_TOGGLE, "Transmission - Toggle On/Off");
    _SF_ALL_QMAP.insert(SF_TRANS_ON, "Transmission - Turn On");
    _SF_ALL_QMAP.insert(SF_TRANS_OFF, "Transmission - Turn Off");
    _SF_ALL_QMAP.insert(SF_CANNON_FIRE, "Cannon Fire");
    _SF_ALL_QMAP.insert(SF_MECH_BARREL, "Fire Airsoft / Mechanical Recoil Unit");
    _SF_ALL_QMAP.insert(SF_RECOIL_SERVO, "Recoil Servo");
    _SF_ALL_QMAP.insert(SF_HI_FLASH, "High Intensity Flash");
    _SF_ALL_QMAP.insert(SF_MG_FIRE, "Machine Gun - Fire");
    _SF_ALL_QMAP.insert(SF_MG_OFF, "Machine Gun - Stop");
    _SF_ALL_QMAP.insert(SF_BARREL_ENABLE, "Airsoft/Mech Recoil - Enable");
    _SF_ALL_QMAP.insert(SF_BARREL_DISABLE, "Airsoft/Mech Recoil - Disable");
    _SF_ALL_QMAP.insert(SF_BARREL_TOGGLE, "Airsoft/Mech Recoil - Toggle");
    _SF_ALL_QMAP.insert(SF_LIGHT1_TOGGLE, "Light 1 (Headlights) - Toggle On/Off");
    _SF_ALL_QMAP.insert(SF_LIGHT1_ON, "Light 1 (Headlights) - Turn On");
    _SF_ALL_QMAP.insert(SF_LIGHT1_OFF, "Light 1 (Headlights) - Turn Off");
    _SF_ALL_QMAP.insert(SF_LIGHT2_TOGGLE, "Light 2 - Toggle On/Off");
    _SF_ALL_QMAP.insert(SF_LIGHT2_ON, "Light 2 - Turn On");
    _SF_ALL_QMAP.insert(SF_LIGHT2_OFF, "Light 2 - Turn Off");
    _SF_ALL_QMAP.insert(SF_RUNNINGLIGHTS_TOGGLE, "Running Lights - Toggle On/Off");
    _SF_ALL_QMAP.insert(SF_RUNNINGLIGHTS_ON, "Running Lights - Turn On");
    _SF_ALL_QMAP.insert(SF_RUNNINGLIGHTS_OFF, "Running Lights - Turn Off");
    _SF_ALL_QMAP.insert(SF_AUXOUT_TOGGLE, "Aux Output - Toggle On/Off");
    _SF_ALL_QMAP.insert(SF_AUXOUT_ON, "Aux Output - Turn On");
    _SF_ALL_QMAP.insert(SF_AUXOUT_OFF, "Aux Output - Turn Off");
    _SF_ALL_QMAP.insert(SF_AUXOUT_LEVEL, "Aux Output - Set Level");                 // Analog
    _SF_ALL_QMAP.insert(SF_AUXOUT_PRESETDIM, "Aux Output - Preset Dim Level");
    _SF_ALL_QMAP.insert(SF_AUXOUT_FLASH, "Aux Output - Flash");
    _SF_ALL_QMAP.insert(SF_AUXOUT_BLINK, "Aux Output - Blink");
    _SF_ALL_QMAP.insert(SF_AUXOUT_TOGGLEBLINK, "Aux Output - Toggle Blink");
    _SF_ALL_QMAP.insert(SF_AUXOUT_REVOLVE, "Aux Output - Revolving Light");
    _SF_ALL_QMAP.insert(SF_AUXOUT_TOGGLEREVOLVE, "Aux Output - Toggle Revolving Light");
    _SF_ALL_QMAP.insert(SF_SET_VOLUME, "Sound Card - Set Volume");
    _SF_ALL_QMAP.insert(SF_INCR_VOLUME, "Sound Card - Start Increasing Volume");
    _SF_ALL_QMAP.insert(SF_DECR_VOLUME, "Sound Card - Start Decreasing Volume");
    _SF_ALL_QMAP.insert(SF_STOP_VOLUME, "Sound Card - Stop Changing Volume");
    _SF_ALL_QMAP.insert(SF_USER_SOUND1_ONCE, "User Sound 1 - Play once");
    _SF_ALL_QMAP.insert(SF_USER_SOUND1_RPT, "User Sound 1 - Repeat");
    _SF_ALL_QMAP.insert(SF_USER_SOUND1_OFF, "User Sound 1 - Stop");
    _SF_ALL_QMAP.insert(SF_USER_SOUND2_ONCE, "User Sound 2 - Play once");
    _SF_ALL_QMAP.insert(SF_USER_SOUND2_RPT, "User Sound 2 - Repeat");
    _SF_ALL_QMAP.insert(SF_USER_SOUND2_OFF, "User Sound 2 - Stop");
    _SF_ALL_QMAP.insert(SF_USER_SOUND3_ONCE, "User Sound 3 - Play once");
    _SF_ALL_QMAP.insert(SF_USER_SOUND3_RPT, "User Sound 3 - Repeat");
    _SF_ALL_QMAP.insert(SF_USER_SOUND3_OFF, "User Sound 3 - Stop");
    _SF_ALL_QMAP.insert(SF_USER_SOUND4_ONCE, "User Sound 4 - Play once");
    _SF_ALL_QMAP.insert(SF_USER_SOUND4_RPT, "User Sound 4 - Repeat");
    _SF_ALL_QMAP.insert(SF_USER_SOUND4_OFF, "User Sound 4 - Stop");
    _SF_ALL_QMAP.insert(SF_OUTPUT_A_TOGGLE, "External Output A - Toggle");
    _SF_ALL_QMAP.insert(SF_OUTPUT_A_ON, "External Output A - Turn On");
    _SF_ALL_QMAP.insert(SF_OUTPUT_A_OFF, "External Output A - Turn Off");
    _SF_ALL_QMAP.insert(SF_OUTPUT_B_TOGGLE, "External Output B - Toggle");
    _SF_ALL_QMAP.insert(SF_OUTPUT_B_ON, "External Output B - Turn On");
    _SF_ALL_QMAP.insert(SF_OUTPUT_B_OFF, "External Output B - Turn Off");
    _SF_ALL_QMAP.insert(SF_ACCEL_LEVEL, "Set Acceleration Level");                  // Analog
    _SF_ALL_QMAP.insert(SF_DECEL_LEVEL, "Set Deceleration Level");                  // Analog
    _SF_ALL_QMAP.insert(SF_TURNMODE_1, "Set Turn Mode = 1");
    _SF_ALL_QMAP.insert(SF_TURNMODE_2, "Set Turn Mode = 2");
    _SF_ALL_QMAP.insert(SF_TURNMODE_3, "Set Turn Mode = 3");
    _SF_ALL_QMAP.insert(SF_SMOKER, "Smoker - Manual Speed");                      // Analog
    _SF_ALL_QMAP.insert(SF_SMOKER_ON, "Smoker - Manual On");
    _SF_ALL_QMAP.insert(SF_SMOKER_OFF, "Smoker - Manual Off");
    _SF_ALL_QMAP.insert(SF_MOTOR_A, "Motor A - Manual Control");                    // Analog
    _SF_ALL_QMAP.insert(SF_MOTOR_B, "Motor B - Manual Control");                    // Analog
    _SF_ALL_QMAP.insert(SF_RC1_PASS, "RC Output 1 - Pass-through");                 // Analog   // No passthrough for 5 - that is always reserved for recoil
    _SF_ALL_QMAP.insert(SF_RC2_PASS, "RC Output 2 - Pass-through");                 // Analog
    _SF_ALL_QMAP.insert(SF_RC3_PASS, "RC Output 3 - Pass-through");                 // Analog
    _SF_ALL_QMAP.insert(SF_RC4_PASS, "RC Output 4 - Pass-through");                 // Analog
    _SF_ALL_QMAP.insert(SF_RC6_PASS, "RC Output 6 - Pass-through");                 // Analog
    _SF_ALL_QMAP.insert(SF_RC7_PASS, "RC Output 7 - Pass-through");                 // Analog
    _SF_ALL_QMAP.insert(SF_RC8_PASS, "RC Output 8 - Pass-through");                 // Analog
    _SF_ALL_QMAP.insert(SF_RC1_PASS_PAN, "RC Output 1 - Pan Servo");                // Analog
    _SF_ALL_QMAP.insert(SF_RC2_PASS_PAN, "RC Output 2 - Pan Servo");                // Analog
    _SF_ALL_QMAP.insert(SF_RC3_PASS_PAN, "RC Output 3 - Pan Servo");                // Analog
    _SF_ALL_QMAP.insert(SF_RC4_PASS_PAN, "RC Output 4 - Pan Servo");                // Analog
    _SF_ALL_QMAP.insert(SF_RC6_PASS_PAN, "RC Output 6 - Pan Servo");                // Analog
    _SF_ALL_QMAP.insert(SF_RC7_PASS_PAN, "RC Output 7 - Pan Servo");                // Analog
    _SF_ALL_QMAP.insert(SF_RC8_PASS_PAN, "RC Output 8 - Pan Servo");                // Analog
    // DISABLED FOR NOW
//    _SF_ALL_QMAP.insert(SF_BARREL_ON, "Barrel Stabilization - Turn On");
//    _SF_ALL_QMAP.insert(SF_BARREL_OFF, "Barrel Stabilization - Turn Off");
//    _SF_ALL_QMAP.insert(SF_BARREL_TOGGLE, "Barrel Stabilization - Toggle");
//    _SF_ALL_QMAP.insert(SF_BARREL_LEVEL, "Barrel Stabilization - Set Sensitivity"); // Analog
//    _SF_ALL_QMAP.insert(SF_HILLS_ON, "Hill Physics - Turn On");
//    _SF_ALL_QMAP.insert(SF_HILLS_OFF, "Hill Physics - Turn Off");
//    _SF_ALL_QMAP.insert(SF_HILLS_TOGGLE, "Hill Physics - Toggle");
//    _SF_ALL_QMAP.insert(SF_HILLS_LEVEL, "Hill Physics - Set Sensitivity");        // Analog
    _SF_ALL_QMAP.insert(SF_USER_FUNC_1, "User Function 1");
    _SF_ALL_QMAP.insert(SF_USER_FUNC_2, "User Function 2");
    _SF_ALL_QMAP.insert(SF_USER_ANLG_1, "Analog User Function 1");                  // Analog
    _SF_ALL_QMAP.insert(SF_USER_ANLG_2, "Analog User Function 2");                  // Analog
    _SF_ALL_QMAP.insert(SF_DUMP_DEBUG, "Dump Settings");
    _SF_ALL_QMAP.insert(SF_NT_ENABLE, "Neutral Turn - Enable");
    _SF_ALL_QMAP.insert(SF_NT_DISABLE, "Neutral Turn - Disable");
    _SF_ALL_QMAP.insert(SF_NT_TOGGLE, "Neutral Turn - Toggle");
    _SF_ALL_QMAP.insert(SF_DRIVEPROFILE_1, "Drive Profile - Set to 1");
    _SF_ALL_QMAP.insert(SF_DRIVEPROFILE_2, "Drive Profile - Set to 2");
    _SF_ALL_QMAP.insert(SF_DRIVEPROFILE_TOGGLE, "Drive Profile - Toggle");
    _SF_ALL_QMAP.insert(SF_SMOKER_ENABLE, "Smoker - Enable");
    _SF_ALL_QMAP.insert(SF_SMOKER_DISABLE, "Smoker - Disable");
    _SF_ALL_QMAP.insert(SF_SMOKER_TOGGLE, "Smoker - Toggle");

    return _SF_ALL_QMAP;
}

QMap<_special_function, QString> OP_QMaps::getDigitalSpecialFunctionsQMap()
{
    // Return a list of digital special functions (not analog)
    _SF_DIGITAL_QMAP.insert(SF_NULL_FUNCTION, "");  // No function
    _SF_DIGITAL_QMAP.insert(SF_ENGINE_TOGGLE, "Engine - Toggle On/Off");
    _SF_DIGITAL_QMAP.insert(SF_ENGINE_ON, "Engine - Turn On");
    _SF_DIGITAL_QMAP.insert(SF_ENGINE_OFF, "Engine - Turn Off");
    _SF_DIGITAL_QMAP.insert(SF_TRANS_TOGGLE, "Transmission - Toggle On/Off");
    _SF_DIGITAL_QMAP.insert(SF_TRANS_ON, "Transmission - Turn On");
    _SF_DIGITAL_QMAP.insert(SF_TRANS_OFF, "Transmission - Turn Off");
    _SF_DIGITAL_QMAP.insert(SF_CANNON_FIRE, "Cannon Fire");
    _SF_DIGITAL_QMAP.insert(SF_MECH_BARREL, "Fire Airsoft / Mechanical Recoil Unit");
    _SF_DIGITAL_QMAP.insert(SF_RECOIL_SERVO, "Recoil Servo");
    _SF_DIGITAL_QMAP.insert(SF_HI_FLASH, "High Intensity Flash");
    _SF_DIGITAL_QMAP.insert(SF_MG_FIRE, "Machine Gun - Fire");
    _SF_DIGITAL_QMAP.insert(SF_MG_OFF, "Machine Gun - Stop");
    _SF_DIGITAL_QMAP.insert(SF_BARREL_ENABLE, "Airsoft/Mech Recoil - Enable");
    _SF_DIGITAL_QMAP.insert(SF_BARREL_DISABLE, "Airsoft/Mech Recoil - Disable");
    _SF_DIGITAL_QMAP.insert(SF_BARREL_TOGGLE, "Airsoft/Mech Recoil - Toggle");
    _SF_DIGITAL_QMAP.insert(SF_LIGHT1_TOGGLE, "Light 1 (Headlights) - Toggle On/Off");
    _SF_DIGITAL_QMAP.insert(SF_LIGHT1_ON, "Light 1 (Headlights) - Turn On");
    _SF_DIGITAL_QMAP.insert(SF_LIGHT1_OFF, "Light 1 (Headlights) - Turn Off");
    _SF_DIGITAL_QMAP.insert(SF_LIGHT2_TOGGLE, "Light 2 - Toggle On/Off");
    _SF_DIGITAL_QMAP.insert(SF_LIGHT2_ON, "Light 2 - Turn On");
    _SF_DIGITAL_QMAP.insert(SF_LIGHT2_OFF, "Light 2 - Turn Off");
    _SF_DIGITAL_QMAP.insert(SF_RUNNINGLIGHTS_TOGGLE, "Running Lights - Toggle On/Off");
    _SF_DIGITAL_QMAP.insert(SF_RUNNINGLIGHTS_ON, "Running Lights - Turn On");
    _SF_DIGITAL_QMAP.insert(SF_RUNNINGLIGHTS_OFF, "Running Lights - Turn Off");
    _SF_DIGITAL_QMAP.insert(SF_AUXOUT_TOGGLE, "Aux Output - Toggle On/Off");
    _SF_DIGITAL_QMAP.insert(SF_AUXOUT_ON, "Aux Output - Turn On");
    _SF_DIGITAL_QMAP.insert(SF_AUXOUT_OFF, "Aux Output - Turn Off");
    _SF_DIGITAL_QMAP.insert(SF_AUXOUT_PRESETDIM, "Aux Output - Preset Dim Level");
    _SF_DIGITAL_QMAP.insert(SF_AUXOUT_FLASH, "Aux Output - Flash");
    _SF_DIGITAL_QMAP.insert(SF_AUXOUT_BLINK, "Aux Output - Blink");
    _SF_DIGITAL_QMAP.insert(SF_AUXOUT_TOGGLEBLINK, "Aux Output - Toggle Blink");
    _SF_DIGITAL_QMAP.insert(SF_AUXOUT_REVOLVE, "Aux Output - Revolving Light");
    _SF_DIGITAL_QMAP.insert(SF_AUXOUT_TOGGLEREVOLVE, "Aux Output - Toggle Revolving Light");
    _SF_DIGITAL_QMAP.insert(SF_INCR_VOLUME, "Sound Card - Start Increasing Volume");
    _SF_DIGITAL_QMAP.insert(SF_DECR_VOLUME, "Sound Card - Start Decreasing Volume");
    _SF_DIGITAL_QMAP.insert(SF_STOP_VOLUME, "Sound Card - Stop Changing Volume");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND1_ONCE, "User Sound 1 - Play once");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND1_RPT, "User Sound 1 - Repeat");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND1_OFF, "User Sound 1 - Stop");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND2_ONCE, "User Sound 2 - Play once");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND2_RPT, "User Sound 2 - Repeat");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND2_OFF, "User Sound 2 - Stop");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND3_ONCE, "User Sound 3 - Play once");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND3_RPT, "User Sound 3 - Repeat");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND3_OFF, "User Sound 3 - Stop");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND4_ONCE, "User Sound 4 - Play once");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND4_RPT, "User Sound 4 - Repeat");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND4_OFF, "User Sound 4 - Stop");
    _SF_DIGITAL_QMAP.insert(SF_OUTPUT_A_TOGGLE, "External Output A - Toggle");
    _SF_DIGITAL_QMAP.insert(SF_OUTPUT_A_ON, "Logic Level Output A - Turn On");
    _SF_DIGITAL_QMAP.insert(SF_OUTPUT_A_OFF, "Logic Level Output A - Turn Off");
    _SF_DIGITAL_QMAP.insert(SF_OUTPUT_B_TOGGLE, "Logic Level Output B - Toggle");
    _SF_DIGITAL_QMAP.insert(SF_OUTPUT_B_ON, "Logic Level Output B - Turn On");
    _SF_DIGITAL_QMAP.insert(SF_OUTPUT_B_OFF, "Logicl Level Output B - Turn Off");
    _SF_DIGITAL_QMAP.insert(SF_TURNMODE_1, "Set Turn Mode = 1");
    _SF_DIGITAL_QMAP.insert(SF_TURNMODE_2, "Set Turn Mode = 2");
    _SF_DIGITAL_QMAP.insert(SF_TURNMODE_3, "Set Turn Mode = 3");
    _SF_DIGITAL_QMAP.insert(SF_SMOKER_ON, "Smoker - Manual On");
    _SF_DIGITAL_QMAP.insert(SF_SMOKER_OFF, "Smoker - Manual Off");
// DISABLED FOR NOW
//    _SF_DIGITAL_QMAP.insert(SF_BARREL_ON, "Barrel Stabilization - Turn On");
//    _SF_DIGITAL_QMAP.insert(SF_BARREL_OFF, "Barrel Stabilization - Turn Off");
//    _SF_DIGITAL_QMAP.insert(SF_BARREL_TOGGLE, "Barrel Stabilization - Toggle");
//    _SF_DIGITAL_QMAP.insert(SF_HILLS_ON, "Hill Physics - Turn On");
//    _SF_DIGITAL_QMAP.insert(SF_HILLS_OFF, "Hill Physics - Turn Off");
//    _SF_DIGITAL_QMAP.insert(SF_HILLS_TOGGLE, "Hill Physics - Toggle");
    _SF_DIGITAL_QMAP.insert(SF_USER_FUNC_1, "User Function 1");
    _SF_DIGITAL_QMAP.insert(SF_USER_FUNC_2, "User Function 2");
    _SF_DIGITAL_QMAP.insert(SF_DUMP_DEBUG, "Dump Settings");
    _SF_DIGITAL_QMAP.insert(SF_NT_ENABLE, "Neutral Turn - Enable");
    _SF_DIGITAL_QMAP.insert(SF_NT_DISABLE, "Neutral Turn - Disable");
    _SF_DIGITAL_QMAP.insert(SF_NT_TOGGLE, "Neutral Turn - Toggle");
    _SF_DIGITAL_QMAP.insert(SF_DRIVEPROFILE_1, "Drive Profile - Set to 1");
    _SF_DIGITAL_QMAP.insert(SF_DRIVEPROFILE_2, "Drive Profile - Set to 2");
    _SF_DIGITAL_QMAP.insert(SF_DRIVEPROFILE_TOGGLE, "Drive Profile - Toggle");
    _SF_DIGITAL_QMAP.insert(SF_SMOKER_ENABLE, "Smoker - Enable");
    _SF_DIGITAL_QMAP.insert(SF_SMOKER_DISABLE, "Smoker - Disable");
    _SF_DIGITAL_QMAP.insert(SF_SMOKER_TOGGLE, "Smoker - Toggle");
    return _SF_DIGITAL_QMAP;
}

QMap<_special_function, QString> OP_QMaps::getAnalogSpecialFunctionsQMap()
{
    // Return a list of analog special functions (not digital)
    _SF_ANALOG_QMAP.insert(SF_NULL_FUNCTION, "");  // No function
    _SF_ANALOG_QMAP.insert(SF_AUXOUT_LEVEL, "Aux Output - Set Level");
    _SF_ANALOG_QMAP.insert(SF_ACCEL_LEVEL, "Set Acceleration Level");
    _SF_ANALOG_QMAP.insert(SF_DECEL_LEVEL, "Set Deceleration Level");
    _SF_ANALOG_QMAP.insert(SF_RC1_PASS, "RC Output 1 - Pass-through"); // No passthrough for 5 - that is always reserved for recoil
    _SF_ANALOG_QMAP.insert(SF_RC2_PASS, "RC Output 2 - Pass-through");
    _SF_ANALOG_QMAP.insert(SF_RC3_PASS, "RC Output 3 - Pass-through");
    _SF_ANALOG_QMAP.insert(SF_RC4_PASS, "RC Output 4 - Pass-through");
    _SF_ANALOG_QMAP.insert(SF_RC6_PASS, "RC Output 6 - Pass-through");
    _SF_ANALOG_QMAP.insert(SF_RC7_PASS, "RC Output 7 - Pass-through");
    _SF_ANALOG_QMAP.insert(SF_RC8_PASS, "RC Output 8 - Pass-through");
    _SF_ANALOG_QMAP.insert(SF_RC1_PASS_PAN, "RC Output 1 - Pan Servo");
    _SF_ANALOG_QMAP.insert(SF_RC2_PASS_PAN, "RC Output 2 - Pan Servo");
    _SF_ANALOG_QMAP.insert(SF_RC3_PASS_PAN, "RC Output 3 - Pan Servo");
    _SF_ANALOG_QMAP.insert(SF_RC4_PASS_PAN, "RC Output 4 - Pan Servo");
    _SF_ANALOG_QMAP.insert(SF_RC6_PASS_PAN, "RC Output 6 - Pan Servo");
    _SF_ANALOG_QMAP.insert(SF_RC7_PASS_PAN, "RC Output 7 - Pan Servo");
    _SF_ANALOG_QMAP.insert(SF_RC8_PASS_PAN, "RC Output 8 - Pan Servo");
    _SF_ANALOG_QMAP.insert(SF_SMOKER, "Smoker - Manual Speed");
    _SF_ANALOG_QMAP.insert(SF_MOTOR_A, "Motor A - Manual Control");
    _SF_ANALOG_QMAP.insert(SF_MOTOR_B, "Motor B - Manual Control");
// DISABLED FOR NOW
//    _SF_ANALOG_QMAP.insert(SF_BARREL_LEVEL, "Barrel Stabilization - Set Sensitivity");
//    _SF_ANALOG_QMAP.insert(SF_HILLS_LEVEL, "Hill Physics - Set Sensitivity");
    _SF_ANALOG_QMAP.insert(SF_USER_ANLG_1, "Analog User Function 1");
    _SF_ANALOG_QMAP.insert(SF_USER_ANLG_2, "Analog User Function 2");
    _SF_ANALOG_QMAP.insert(SF_SET_VOLUME, "Sound Card - Set Volume");
    return _SF_ANALOG_QMAP;
}

QMap<_special_function, QString> OP_QMaps::getExternalPortSpecialFunctionsQMap()
{
    // Return a list of special functions related to the external outputs
    _SF_PORTS_QMAP.insert(SF_NULL_FUNCTION, "");  // No function
    _SF_PORTS_QMAP.insert(SF_OUTPUT_A_TOGGLE, "Logic Level Output A - Toggle");
    _SF_PORTS_QMAP.insert(SF_OUTPUT_A_ON, "Logic Level Output A - Turn On");
    _SF_PORTS_QMAP.insert(SF_OUTPUT_A_OFF, "Logic Level Output A - Turn Off");
    _SF_PORTS_QMAP.insert(SF_OUTPUT_B_TOGGLE, "Logic Level Output B - Toggle");
    _SF_PORTS_QMAP.insert(SF_OUTPUT_B_ON, "Logic Level Output B - Turn On");
    _SF_PORTS_QMAP.insert(SF_OUTPUT_B_OFF, "Logic Level Output B - Turn Off");
    return _SF_PORTS_QMAP;
}


QMap<_special_function, QString> OP_QMaps::getEmptySpecialFunctionsQMap()
{
    // Just give a single blank value
    _SF_EMPTY_QMAP.insert(SF_NULL_FUNCTION, "");  // No function
    return _SF_EMPTY_QMAP;
}


// ---------------------------------------------------------------------------------------------------------->>
// TRIGGER SOURCES
// ---------------------------------------------------------------------------------------------------------->>
boolean OP_QMaps::isTriggerSourceAuxChannel(_trigger_source ts)
{
    // Check this function against all in the digital list
    QMap<_trigger_source, QString> TSA;
    TSA = getAuxChannelTriggerSourcesQMap();
    QMapIterator<_trigger_source, QString> i(TSA);
    while (i.hasNext())
    {
        i.next();
        if (i.key() == ts) return true;
    }
    return false;
}

QMap<_trigger_source, QString> OP_QMaps::getAllTriggerSourcesQMap()
{
    // Create the trigger list
    _OPT_ALL_QMAP.insert(TS_NULL_TRIGGER, "");                 // no trigger
    _OPT_ALL_QMAP.insert(TS_TURRET_STICK, "Turret Stick");     // Turret stick
    _OPT_ALL_QMAP.insert(TS_AUX1, "Aux Channel 1");            // Aux channel 1
    _OPT_ALL_QMAP.insert(TS_AUX2, "Aux Channel 2");            // Aux channel 2
    _OPT_ALL_QMAP.insert(TS_AUX3, "Aux Channel 3");            // Aux channel 3
    _OPT_ALL_QMAP.insert(TS_AUX4, "Aux Channel 4");            // Aux channel 4
    _OPT_ALL_QMAP.insert(TS_AUX5, "Aux Channel 5");            // Aux channel 5
    _OPT_ALL_QMAP.insert(TS_AUX6, "Aux Channel 6");            // Aux channel 6
    _OPT_ALL_QMAP.insert(TS_AUX7, "Aux Channel 7");            // Aux channel 7
    _OPT_ALL_QMAP.insert(TS_AUX8, "Aux Channel 8");            // Aux channel 8
    _OPT_ALL_QMAP.insert(TS_AUX9, "Aux Channel 9");            // Aux channel 9
    _OPT_ALL_QMAP.insert(TS_AUX10, "Aux Channel 10");          // Aux channel 10
    _OPT_ALL_QMAP.insert(TS_AUX11, "Aux Channel 11");          // Aux channel 11
    _OPT_ALL_QMAP.insert(TS_AUX12, "Aux Channel 12");          // Aux channel 12
    _OPT_ALL_QMAP.insert(TS_INPUT_A, "External Input A");      // External input A (if set to input)
    _OPT_ALL_QMAP.insert(TS_INPUT_B, "External Input B");      // External input B (if set to input)
    return _OPT_ALL_QMAP;
}

QMap<_trigger_source, QString> OP_QMaps::getDigitalTriggerSourcesQMap()
{
    // Create the trigger list, digital only.
    _OPT_DIGITAL_QMAP.insert(TS_NULL_TRIGGER, "");                 // no trigger
    _OPT_DIGITAL_QMAP.insert(TS_TURRET_STICK, "Turret Stick");     // Turret stick
    _OPT_DIGITAL_QMAP.insert(TS_AUX1, "Aux Channel 1");            // Aux channel 1
    _OPT_DIGITAL_QMAP.insert(TS_AUX2, "Aux Channel 2");            // Aux channel 2
    _OPT_DIGITAL_QMAP.insert(TS_AUX3, "Aux Channel 3");            // Aux channel 3
    _OPT_DIGITAL_QMAP.insert(TS_AUX4, "Aux Channel 4");            // Aux channel 4
    _OPT_DIGITAL_QMAP.insert(TS_AUX5, "Aux Channel 5");            // Aux channel 5
    _OPT_DIGITAL_QMAP.insert(TS_AUX6, "Aux Channel 6");            // Aux channel 6
    _OPT_DIGITAL_QMAP.insert(TS_AUX7, "Aux Channel 7");            // Aux channel 7
    _OPT_DIGITAL_QMAP.insert(TS_AUX8, "Aux Channel 8");            // Aux channel 8
    _OPT_DIGITAL_QMAP.insert(TS_AUX9, "Aux Channel 9");            // Aux channel 9
    _OPT_DIGITAL_QMAP.insert(TS_AUX10, "Aux Channel 10");          // Aux channel 10
    _OPT_DIGITAL_QMAP.insert(TS_AUX11, "Aux Channel 11");          // Aux channel 11
    _OPT_DIGITAL_QMAP.insert(TS_AUX12, "Aux Channel 12");          // Aux channel 12
    _OPT_DIGITAL_QMAP.insert(TS_INPUT_A, "External Input A");      // External input A (if set to input)
    _OPT_DIGITAL_QMAP.insert(TS_INPUT_B, "External Input B");      // External input B (if set to input)
    return _OPT_DIGITAL_QMAP;
}

QMap<_trigger_source, QString> OP_QMaps::getAnalogTriggerSourcesQMap()
{
    // Create the trigger list
    _OPT_ANALOG_QMAP.insert(TS_NULL_TRIGGER, "");                 // no trigger
    //_OPT_ANALOG_QMAP.insert(TS_TURRET_STICK, "Turret Stick");     // Turret stick - can't be analog
    _OPT_ANALOG_QMAP.insert(TS_AUX1, "Aux Channel 1");            // Aux channel 1
    _OPT_ANALOG_QMAP.insert(TS_AUX2, "Aux Channel 2");            // Aux channel 2
    _OPT_ANALOG_QMAP.insert(TS_AUX3, "Aux Channel 3");            // Aux channel 3
    _OPT_ANALOG_QMAP.insert(TS_AUX4, "Aux Channel 4");            // Aux channel 4
    _OPT_ANALOG_QMAP.insert(TS_AUX5, "Aux Channel 5");            // Aux channel 5
    _OPT_ANALOG_QMAP.insert(TS_AUX6, "Aux Channel 6");            // Aux channel 6
    _OPT_ANALOG_QMAP.insert(TS_AUX7, "Aux Channel 7");            // Aux channel 7
    _OPT_ANALOG_QMAP.insert(TS_AUX8, "Aux Channel 8");            // Aux channel 8
    _OPT_ANALOG_QMAP.insert(TS_AUX9, "Aux Channel 9");            // Aux channel 9
    _OPT_ANALOG_QMAP.insert(TS_AUX10, "Aux Channel 10");          // Aux channel 10
    _OPT_ANALOG_QMAP.insert(TS_AUX11, "Aux Channel 11");          // Aux channel 11
    _OPT_ANALOG_QMAP.insert(TS_AUX12, "Aux Channel 12");          // Aux channel 12
    _OPT_ANALOG_QMAP.insert(TS_INPUT_A, "External Input A");      // External input A (if set to input)
    _OPT_ANALOG_QMAP.insert(TS_INPUT_B, "External Input B");      // External input B (if set to input)
    return _OPT_ANALOG_QMAP;
}

QMap<_trigger_source, QString> OP_QMaps::getAuxChannelTriggerSourcesQMap()
{
    // Create the trigger list, digital only.
    _OPT_AUX_QMAP.insert(TS_AUX1, "Aux Channel 1");            // Aux channel 1
    _OPT_AUX_QMAP.insert(TS_AUX2, "Aux Channel 2");            // Aux channel 2
    _OPT_AUX_QMAP.insert(TS_AUX3, "Aux Channel 3");            // Aux channel 3
    _OPT_AUX_QMAP.insert(TS_AUX4, "Aux Channel 4");            // Aux channel 4
    _OPT_AUX_QMAP.insert(TS_AUX5, "Aux Channel 5");            // Aux channel 5
    _OPT_AUX_QMAP.insert(TS_AUX6, "Aux Channel 6");            // Aux channel 6
    _OPT_AUX_QMAP.insert(TS_AUX7, "Aux Channel 7");            // Aux channel 7
    _OPT_AUX_QMAP.insert(TS_AUX8, "Aux Channel 8");            // Aux channel 8
    _OPT_AUX_QMAP.insert(TS_AUX9, "Aux Channel 9");            // Aux channel 9
    _OPT_AUX_QMAP.insert(TS_AUX10, "Aux Channel 10");          // Aux channel 10
    _OPT_AUX_QMAP.insert(TS_AUX11, "Aux Channel 11");          // Aux channel 11
    _OPT_AUX_QMAP.insert(TS_AUX12, "Aux Channel 12");          // Aux channel 12
    return _OPT_AUX_QMAP;
}

QMap<_trigger_source, QString> OP_QMaps::getEmptyTriggerSourcesQMap()
{
    // Create the trigger list
    _OPT_EMPTY_QMAP.insert(TS_NULL_TRIGGER, "");                 // no trigger
    return _OPT_EMPTY_QMAP;
}


// ---------------------------------------------------------------------------------------------------------->>
// TRIGGER ACTIONS
// ---------------------------------------------------------------------------------------------------------->>
QMap<turretStick_positions, QString> OP_QMaps::getTurretStickSpecialPositionsQMap()
{
    // Create the trigger action list
    _SP_TURRET_STICK.insert(SP_TL, "Top Left");
    _SP_TURRET_STICK.insert(SP_TC, "Top Center");
    _SP_TURRET_STICK.insert(SP_TR, "Top Right");
    _SP_TURRET_STICK.insert(SP_ML, "Middle Left");
    _SP_TURRET_STICK.insert(SP_MC, "Middle Center");
    _SP_TURRET_STICK.insert(SP_MR, "Middle Right");
    _SP_TURRET_STICK.insert(SP_BL, "Bottom Left");
    _SP_TURRET_STICK.insert(SP_BC, "Bottom Center");
    _SP_TURRET_STICK.insert(SP_BR, "Bottom Right");
    return _SP_TURRET_STICK;
}

