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
        case SF_OUTPUT_A_PULSE:
            return 1;
            break;
        case SF_OUTPUT_B_TOGGLE:
        case SF_OUTPUT_B_ON:
        case SF_OUTPUT_B_OFF:
        case SF_OUTPUT_B_PULSE:
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
    // UNFORUNATELY - The order you place them in here is not the order in which they will
    // appear, since all QMaps sort by index and you can't change that. Probably should have used QHash.
    // See below for the sorted QList
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
    _SF_ALL_QMAP.insert(SF_MG2_FIRE, "2nd Machine Gun - Fire");
    _SF_ALL_QMAP.insert(SF_MG2_OFF, "2nd Machine Gun - Stop");
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
    _SF_ALL_QMAP.insert(SF_AUXOUT_TOGGLEDIM, "Aux Output - Toggle Dim Level");
    _SF_ALL_QMAP.insert(SF_AUXOUT_FLASH, "Aux Output - Flash");
    _SF_ALL_QMAP.insert(SF_AUXOUT_INV_FLASH, "Aux Output - Inverse Flash");
    _SF_ALL_QMAP.insert(SF_AUXOUT_BLINK, "Aux Output - Blink");
    _SF_ALL_QMAP.insert(SF_AUXOUT_TOGGLEBLINK, "Aux Output - Toggle Blink");
    _SF_ALL_QMAP.insert(SF_AUXOUT_REVOLVE, "Aux Output - Revolving Light");
    _SF_ALL_QMAP.insert(SF_AUXOUT_TOGGLEREVOLVE, "Aux Output - Toggle Revolving Light");
    _SF_ALL_QMAP.insert(SF_SET_VOLUME, "Sound Card - Set Volume");
    _SF_ALL_QMAP.insert(SF_INCR_VOLUME, "Sound Card - Start Increasing Volume");
    _SF_ALL_QMAP.insert(SF_DECR_VOLUME, "Sound Card - Start Decreasing Volume");
    _SF_ALL_QMAP.insert(SF_STOP_VOLUME, "Sound Card - Stop Changing Volume");
    _SF_ALL_QMAP.insert(SF_OVERLAY_ENABLE, "Sound Card - Enable Track Sounds");
    _SF_ALL_QMAP.insert(SF_OVERLAY_DISABLE, "Sound Card - Disable Track Sounds");
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
    _SF_ALL_QMAP.insert(SF_USER_SOUND5_ONCE, "User Sound 5 - Play once");
    _SF_ALL_QMAP.insert(SF_USER_SOUND5_RPT, "User Sound 5 - Repeat");
    _SF_ALL_QMAP.insert(SF_USER_SOUND5_OFF, "User Sound 5 - Stop");
    _SF_ALL_QMAP.insert(SF_USER_SOUND6_ONCE, "User Sound 6 - Play once");
    _SF_ALL_QMAP.insert(SF_USER_SOUND6_RPT, "User Sound 6 - Repeat");
    _SF_ALL_QMAP.insert(SF_USER_SOUND6_OFF, "User Sound 6 - Stop");
    _SF_ALL_QMAP.insert(SF_USER_SOUND7_ONCE, "User Sound 7 - Play once");
    _SF_ALL_QMAP.insert(SF_USER_SOUND7_RPT, "User Sound 7 - Repeat");
    _SF_ALL_QMAP.insert(SF_USER_SOUND7_OFF, "User Sound 7 - Stop");
    _SF_ALL_QMAP.insert(SF_USER_SOUND8_ONCE, "User Sound 8 - Play once");
    _SF_ALL_QMAP.insert(SF_USER_SOUND8_RPT, "User Sound 8 - Repeat");
    _SF_ALL_QMAP.insert(SF_USER_SOUND8_OFF, "User Sound 8 - Stop");
    _SF_ALL_QMAP.insert(SF_USER_SOUND9_ONCE, "User Sound 9 - Play once");
    _SF_ALL_QMAP.insert(SF_USER_SOUND9_RPT, "User Sound 9 - Repeat");
    _SF_ALL_QMAP.insert(SF_USER_SOUND9_OFF, "User Sound 9 - Stop");
    _SF_ALL_QMAP.insert(SF_USER_SOUND10_ONCE, "User Sound 10 - Play once");
    _SF_ALL_QMAP.insert(SF_USER_SOUND10_RPT, "User Sound 10 - Repeat");
    _SF_ALL_QMAP.insert(SF_USER_SOUND10_OFF, "User Sound 10 - Stop");
    _SF_ALL_QMAP.insert(SF_USER_SOUND11_ONCE, "User Sound 11 - Play once");
    _SF_ALL_QMAP.insert(SF_USER_SOUND11_RPT, "User Sound 11 - Repeat");
    _SF_ALL_QMAP.insert(SF_USER_SOUND11_OFF, "User Sound 11 - Stop");
    _SF_ALL_QMAP.insert(SF_USER_SOUND12_ONCE, "User Sound 12 - Play once");
    _SF_ALL_QMAP.insert(SF_USER_SOUND12_RPT, "User Sound 12 - Repeat");
    _SF_ALL_QMAP.insert(SF_USER_SOUND12_OFF, "User Sound 12 - Stop");
    _SF_ALL_QMAP.insert(SF_SBA_PLAYSTOP, "Sound Bank A - Play/Stop");
    _SF_ALL_QMAP.insert(SF_SBA_NEXT, "Sound Bank A - Play Next");
    _SF_ALL_QMAP.insert(SF_SBA_PREVIOUS, "Sound Bank A - Play Previous");
    _SF_ALL_QMAP.insert(SF_SBA_RANDOM, "Sound Bank A - Play Random");
    _SF_ALL_QMAP.insert(SF_SBB_PLAYSTOP, "Sound Bank B - Play/Stop");
    _SF_ALL_QMAP.insert(SF_SBB_NEXT, "Sound Bank B - Play Next");
    _SF_ALL_QMAP.insert(SF_SBB_PREVIOUS, "Sound Bank B - Play Previous");
    _SF_ALL_QMAP.insert(SF_SBB_RANDOM, "Sound Bank B - Play Random");
    _SF_ALL_QMAP.insert(SF_OUTPUT_A_TOGGLE, "External Output A - Toggle");
    _SF_ALL_QMAP.insert(SF_OUTPUT_A_ON, "External Output A - Turn On");
    _SF_ALL_QMAP.insert(SF_OUTPUT_A_OFF, "External Output A - Turn Off");
    _SF_ALL_QMAP.insert(SF_OUTPUT_A_PULSE, "External Output A - Pulse");
    _SF_ALL_QMAP.insert(SF_OUTPUT_A_BLINK, "External Output A - Blink");
    _SF_ALL_QMAP.insert(SF_OUTPUT_B_TOGGLE, "External Output B - Toggle");
    _SF_ALL_QMAP.insert(SF_OUTPUT_B_ON, "External Output B - Turn On");
    _SF_ALL_QMAP.insert(SF_OUTPUT_B_OFF, "External Output B - Turn Off");
    _SF_ALL_QMAP.insert(SF_OUTPUT_B_PULSE, "External Output B - Pulse");
    _SF_ALL_QMAP.insert(SF_OUTPUT_B_BLINK, "External Output B - Blink");
    _SF_ALL_QMAP.insert(SF_ACCEL_LEVEL, "Set Acceleration Level");                  // Analog
    _SF_ALL_QMAP.insert(SF_DECEL_LEVEL, "Set Deceleration Level");                  // Analog
    _SF_ALL_QMAP.insert(SF_TURNMODE_1, "Set Turn Mode = 1");
    _SF_ALL_QMAP.insert(SF_TURNMODE_2, "Set Turn Mode = 2");
    _SF_ALL_QMAP.insert(SF_TURNMODE_3, "Set Turn Mode = 3");
    _SF_ALL_QMAP.insert(SF_SMOKER, "Smoker - Manual Speed");                      // Analog
    _SF_ALL_QMAP.insert(SF_SMOKER_ON, "Smoker - Manual On");
    _SF_ALL_QMAP.insert(SF_SMOKER_OFF, "Smoker - Manual Off");
    _SF_ALL_QMAP.insert(SF_MOTOR_A, "Motor A - Manual Control");                    // Analog
    _SF_ALL_QMAP.insert(SF_MOTOR_A_ON, "Motor A - On");
    _SF_ALL_QMAP.insert(SF_MOTOR_A_OFF, "Motor A - Off");
    _SF_ALL_QMAP.insert(SF_MOTOR_A_TOGGLE, "Motor A - Toggle On/Off");
    _SF_ALL_QMAP.insert(SF_MOTOR_B, "Motor B - Manual Control");                    // Analog
    _SF_ALL_QMAP.insert(SF_MOTOR_B_ON, "Motor B - On");
    _SF_ALL_QMAP.insert(SF_MOTOR_B_OFF, "Motor B - Off");
    _SF_ALL_QMAP.insert(SF_MOTOR_B_TOGGLE, "Motor B - Toggle On/Off");
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
    _SF_ALL_QMAP.insert(SF_SPEED_75, "Reduce Speed to 75%");
    _SF_ALL_QMAP.insert(SF_SPEED_50, "Reduce Speed to 50%");
    _SF_ALL_QMAP.insert(SF_SPEED_25, "Reduce Speed to 25%");
    _SF_ALL_QMAP.insert(SF_SPEED_RESTORE, "Restore Speed");
    _SF_ALL_QMAP.insert(SF_SMOKER_ENABLE, "Smoker - Enable");
    _SF_ALL_QMAP.insert(SF_SMOKER_DISABLE, "Smoker - Disable");
    _SF_ALL_QMAP.insert(SF_SMOKER_TOGGLE, "Smoker - Toggle");
    _SF_ALL_QMAP.insert(SF_MANTRANS_FWD, "Manual Transmission - Forward");
    _SF_ALL_QMAP.insert(SF_MANTRANS_REV, "Manual Transmission - Reverse");
    _SF_ALL_QMAP.insert(SF_MANTRANS_NEUTRAL, "Manual Transmission - Neutral");
    return _SF_ALL_QMAP;
}

QList<_special_function> OP_QMaps::getAllSpecialFunctionsSortOrder()
{
    // To work around the issue of QMaps being impossible to sort arbitrarily, we've created yet
    // _another_ list, this time a QList of _special_functions. This must be a comprehensive list
    // but you can organize them in any order you want. The first int or iterator is the order they
    // will be displayed in (before post-hoc adjustments that are made to account for the presence or
    // absence of certain functions based on other TCB settings)
    _SF_ALL_QMAP_SORT.insert(0, SF_NULL_FUNCTION);
    _SF_ALL_QMAP_SORT.insert(1, SF_ENGINE_TOGGLE);
    _SF_ALL_QMAP_SORT.insert(2, SF_ENGINE_ON);
    _SF_ALL_QMAP_SORT.insert(3, SF_ENGINE_OFF);
    _SF_ALL_QMAP_SORT.insert(4, SF_TRANS_TOGGLE);
    _SF_ALL_QMAP_SORT.insert(5, SF_TRANS_ON);
    _SF_ALL_QMAP_SORT.insert(6, SF_TRANS_OFF);
    _SF_ALL_QMAP_SORT.insert(7, SF_MANTRANS_FWD);
    _SF_ALL_QMAP_SORT.insert(8, SF_MANTRANS_REV);
    _SF_ALL_QMAP_SORT.insert(9, SF_MANTRANS_NEUTRAL);
    _SF_ALL_QMAP_SORT.insert(10, SF_CANNON_FIRE);
    _SF_ALL_QMAP_SORT.insert(11, SF_MECH_BARREL);
    _SF_ALL_QMAP_SORT.insert(12, SF_RECOIL_SERVO);
    _SF_ALL_QMAP_SORT.insert(13, SF_HI_FLASH);
    _SF_ALL_QMAP_SORT.insert(14, SF_MG_FIRE);
    _SF_ALL_QMAP_SORT.insert(15, SF_MG_OFF);
    _SF_ALL_QMAP_SORT.insert(16, SF_MG2_FIRE);
    _SF_ALL_QMAP_SORT.insert(17, SF_MG2_OFF);
    _SF_ALL_QMAP_SORT.insert(18, SF_BARREL_ENABLE);
    _SF_ALL_QMAP_SORT.insert(19, SF_BARREL_DISABLE);
    _SF_ALL_QMAP_SORT.insert(20, SF_BARREL_TOGGLE);
    _SF_ALL_QMAP_SORT.insert(21, SF_LIGHT1_TOGGLE);
    _SF_ALL_QMAP_SORT.insert(22, SF_LIGHT1_ON);
    _SF_ALL_QMAP_SORT.insert(23, SF_LIGHT1_OFF);
    _SF_ALL_QMAP_SORT.insert(24, SF_LIGHT2_TOGGLE);
    _SF_ALL_QMAP_SORT.insert(25, SF_LIGHT2_ON);
    _SF_ALL_QMAP_SORT.insert(26, SF_LIGHT2_OFF);
    _SF_ALL_QMAP_SORT.insert(27, SF_RUNNINGLIGHTS_TOGGLE);
    _SF_ALL_QMAP_SORT.insert(28, SF_RUNNINGLIGHTS_ON);
    _SF_ALL_QMAP_SORT.insert(29, SF_RUNNINGLIGHTS_OFF);
    _SF_ALL_QMAP_SORT.insert(30, SF_AUXOUT_TOGGLE);
    _SF_ALL_QMAP_SORT.insert(31, SF_AUXOUT_ON);
    _SF_ALL_QMAP_SORT.insert(32, SF_AUXOUT_OFF);
    _SF_ALL_QMAP_SORT.insert(33, SF_AUXOUT_LEVEL);
    _SF_ALL_QMAP_SORT.insert(34, SF_AUXOUT_PRESETDIM);
    _SF_ALL_QMAP_SORT.insert(35, SF_AUXOUT_TOGGLEDIM);
    _SF_ALL_QMAP_SORT.insert(36, SF_AUXOUT_FLASH);
    _SF_ALL_QMAP_SORT.insert(37, SF_AUXOUT_INV_FLASH);
    _SF_ALL_QMAP_SORT.insert(38, SF_AUXOUT_BLINK);
    _SF_ALL_QMAP_SORT.insert(39, SF_AUXOUT_TOGGLEBLINK);
    _SF_ALL_QMAP_SORT.insert(40, SF_AUXOUT_REVOLVE);
    _SF_ALL_QMAP_SORT.insert(41, SF_AUXOUT_TOGGLEREVOLVE);
    _SF_ALL_QMAP_SORT.insert(42, SF_OUTPUT_A_TOGGLE);
    _SF_ALL_QMAP_SORT.insert(43, SF_OUTPUT_A_ON);
    _SF_ALL_QMAP_SORT.insert(44, SF_OUTPUT_A_OFF);
    _SF_ALL_QMAP_SORT.insert(45, SF_OUTPUT_A_PULSE);
    _SF_ALL_QMAP_SORT.insert(46, SF_OUTPUT_A_BLINK);
    _SF_ALL_QMAP_SORT.insert(47, SF_OUTPUT_B_TOGGLE);
    _SF_ALL_QMAP_SORT.insert(48, SF_OUTPUT_B_ON);
    _SF_ALL_QMAP_SORT.insert(49, SF_OUTPUT_B_OFF);
    _SF_ALL_QMAP_SORT.insert(50, SF_OUTPUT_B_PULSE);
    _SF_ALL_QMAP_SORT.insert(51, SF_OUTPUT_B_BLINK);
    _SF_ALL_QMAP_SORT.insert(52, SF_ACCEL_LEVEL);
    _SF_ALL_QMAP_SORT.insert(53, SF_DECEL_LEVEL);
    _SF_ALL_QMAP_SORT.insert(54, SF_TURNMODE_1);
    _SF_ALL_QMAP_SORT.insert(55, SF_TURNMODE_2);
    _SF_ALL_QMAP_SORT.insert(56, SF_TURNMODE_3);
    _SF_ALL_QMAP_SORT.insert(57, SF_NT_ENABLE);
    _SF_ALL_QMAP_SORT.insert(58, SF_NT_DISABLE);
    _SF_ALL_QMAP_SORT.insert(59, SF_NT_TOGGLE);
    _SF_ALL_QMAP_SORT.insert(60, SF_DRIVEPROFILE_1);
    _SF_ALL_QMAP_SORT.insert(61, SF_DRIVEPROFILE_2);
    _SF_ALL_QMAP_SORT.insert(62, SF_DRIVEPROFILE_TOGGLE);
    _SF_ALL_QMAP_SORT.insert(63, SF_SPEED_75);
    _SF_ALL_QMAP_SORT.insert(64, SF_SPEED_50);
    _SF_ALL_QMAP_SORT.insert(65, SF_SPEED_25);
    _SF_ALL_QMAP_SORT.insert(66, SF_SPEED_RESTORE);
    _SF_ALL_QMAP_SORT.insert(67, SF_SMOKER);
    _SF_ALL_QMAP_SORT.insert(68, SF_SMOKER_ON);
    _SF_ALL_QMAP_SORT.insert(69, SF_SMOKER_OFF);
    _SF_ALL_QMAP_SORT.insert(70, SF_SMOKER_ENABLE);
    _SF_ALL_QMAP_SORT.insert(71, SF_SMOKER_DISABLE);
    _SF_ALL_QMAP_SORT.insert(72, SF_SMOKER_TOGGLE);
    _SF_ALL_QMAP_SORT.insert(73, SF_MOTOR_A);
    _SF_ALL_QMAP_SORT.insert(74, SF_MOTOR_A_ON);
    _SF_ALL_QMAP_SORT.insert(75, SF_MOTOR_A_OFF);
    _SF_ALL_QMAP_SORT.insert(76, SF_MOTOR_A_TOGGLE);
    _SF_ALL_QMAP_SORT.insert(77, SF_MOTOR_B);
    _SF_ALL_QMAP_SORT.insert(78, SF_MOTOR_B_ON);
    _SF_ALL_QMAP_SORT.insert(79, SF_MOTOR_B_OFF);
    _SF_ALL_QMAP_SORT.insert(80, SF_MOTOR_B_TOGGLE);
    _SF_ALL_QMAP_SORT.insert(81, SF_SET_VOLUME);
    _SF_ALL_QMAP_SORT.insert(82, SF_INCR_VOLUME);
    _SF_ALL_QMAP_SORT.insert(83, SF_DECR_VOLUME);
    _SF_ALL_QMAP_SORT.insert(84, SF_STOP_VOLUME);
    _SF_ALL_QMAP_SORT.insert(85, SF_OVERLAY_ENABLE);
    _SF_ALL_QMAP_SORT.insert(86, SF_OVERLAY_DISABLE);
    _SF_ALL_QMAP_SORT.insert(87, SF_USER_SOUND1_ONCE);
    _SF_ALL_QMAP_SORT.insert(88, SF_USER_SOUND1_RPT);
    _SF_ALL_QMAP_SORT.insert(89, SF_USER_SOUND1_OFF);
    _SF_ALL_QMAP_SORT.insert(90, SF_USER_SOUND2_ONCE);
    _SF_ALL_QMAP_SORT.insert(91, SF_USER_SOUND2_RPT);
    _SF_ALL_QMAP_SORT.insert(92, SF_USER_SOUND2_OFF);
    _SF_ALL_QMAP_SORT.insert(93, SF_USER_SOUND3_ONCE);
    _SF_ALL_QMAP_SORT.insert(94, SF_USER_SOUND3_RPT);
    _SF_ALL_QMAP_SORT.insert(95, SF_USER_SOUND3_OFF);
    _SF_ALL_QMAP_SORT.insert(96, SF_USER_SOUND4_ONCE);
    _SF_ALL_QMAP_SORT.insert(97, SF_USER_SOUND4_RPT);
    _SF_ALL_QMAP_SORT.insert(98, SF_USER_SOUND4_OFF);
    _SF_ALL_QMAP_SORT.insert(99, SF_USER_SOUND5_ONCE);
    _SF_ALL_QMAP_SORT.insert(100, SF_USER_SOUND5_RPT);
    _SF_ALL_QMAP_SORT.insert(101, SF_USER_SOUND5_OFF);
    _SF_ALL_QMAP_SORT.insert(102, SF_USER_SOUND6_ONCE);
    _SF_ALL_QMAP_SORT.insert(103, SF_USER_SOUND6_RPT);
    _SF_ALL_QMAP_SORT.insert(104, SF_USER_SOUND6_OFF);
    _SF_ALL_QMAP_SORT.insert(105, SF_USER_SOUND7_ONCE);
    _SF_ALL_QMAP_SORT.insert(106, SF_USER_SOUND7_RPT);
    _SF_ALL_QMAP_SORT.insert(107, SF_USER_SOUND7_OFF);
    _SF_ALL_QMAP_SORT.insert(108, SF_USER_SOUND8_ONCE);
    _SF_ALL_QMAP_SORT.insert(109, SF_USER_SOUND8_RPT);
    _SF_ALL_QMAP_SORT.insert(110, SF_USER_SOUND8_OFF);
    _SF_ALL_QMAP_SORT.insert(111, SF_USER_SOUND9_ONCE);
    _SF_ALL_QMAP_SORT.insert(112, SF_USER_SOUND9_RPT);
    _SF_ALL_QMAP_SORT.insert(113, SF_USER_SOUND9_OFF);
    _SF_ALL_QMAP_SORT.insert(114, SF_USER_SOUND10_ONCE);
    _SF_ALL_QMAP_SORT.insert(115, SF_USER_SOUND10_RPT);
    _SF_ALL_QMAP_SORT.insert(116, SF_USER_SOUND10_OFF);
    _SF_ALL_QMAP_SORT.insert(117, SF_USER_SOUND11_ONCE);
    _SF_ALL_QMAP_SORT.insert(118, SF_USER_SOUND11_RPT);
    _SF_ALL_QMAP_SORT.insert(119, SF_USER_SOUND11_OFF);
    _SF_ALL_QMAP_SORT.insert(120, SF_USER_SOUND12_ONCE);
    _SF_ALL_QMAP_SORT.insert(121, SF_USER_SOUND12_RPT);
    _SF_ALL_QMAP_SORT.insert(122, SF_USER_SOUND12_OFF);
    _SF_ALL_QMAP_SORT.insert(123, SF_SBA_PLAYSTOP);
    _SF_ALL_QMAP_SORT.insert(124, SF_SBA_NEXT);
    _SF_ALL_QMAP_SORT.insert(125, SF_SBA_PREVIOUS);
    _SF_ALL_QMAP_SORT.insert(126, SF_SBA_RANDOM);
    _SF_ALL_QMAP_SORT.insert(127, SF_SBB_PLAYSTOP);
    _SF_ALL_QMAP_SORT.insert(128, SF_SBB_NEXT);
    _SF_ALL_QMAP_SORT.insert(129, SF_SBB_PREVIOUS);
    _SF_ALL_QMAP_SORT.insert(130, SF_SBB_RANDOM);
    _SF_ALL_QMAP_SORT.insert(131, SF_RC1_PASS);
    _SF_ALL_QMAP_SORT.insert(132, SF_RC2_PASS);
    _SF_ALL_QMAP_SORT.insert(133, SF_RC3_PASS);
    _SF_ALL_QMAP_SORT.insert(134, SF_RC4_PASS);
    _SF_ALL_QMAP_SORT.insert(135, SF_RC6_PASS);
    _SF_ALL_QMAP_SORT.insert(136, SF_RC7_PASS);
    _SF_ALL_QMAP_SORT.insert(137, SF_RC8_PASS);
    _SF_ALL_QMAP_SORT.insert(138, SF_RC1_PASS_PAN);
    _SF_ALL_QMAP_SORT.insert(139, SF_RC2_PASS_PAN);
    _SF_ALL_QMAP_SORT.insert(140, SF_RC3_PASS_PAN);
    _SF_ALL_QMAP_SORT.insert(141, SF_RC4_PASS_PAN);
    _SF_ALL_QMAP_SORT.insert(142, SF_RC6_PASS_PAN);
    _SF_ALL_QMAP_SORT.insert(143, SF_RC7_PASS_PAN);
    _SF_ALL_QMAP_SORT.insert(144, SF_RC8_PASS_PAN);
    _SF_ALL_QMAP_SORT.insert(145, SF_BARREL_STAB_ON);
    _SF_ALL_QMAP_SORT.insert(146, SF_BARREL_STAB_OFF);
    _SF_ALL_QMAP_SORT.insert(147, SF_BARREL_STAB_TOGGLE);
    _SF_ALL_QMAP_SORT.insert(148, SF_BARREL_STAB_LEVEL);
    _SF_ALL_QMAP_SORT.insert(149, SF_HILLS_ON);
    _SF_ALL_QMAP_SORT.insert(150, SF_HILLS_OFF);
    _SF_ALL_QMAP_SORT.insert(151, SF_HILLS_TOGGLE);
    _SF_ALL_QMAP_SORT.insert(152, SF_HILLS_LEVEL);
    _SF_ALL_QMAP_SORT.insert(153, SF_USER_FUNC_1);
    _SF_ALL_QMAP_SORT.insert(154, SF_USER_FUNC_2);
    _SF_ALL_QMAP_SORT.insert(155, SF_USER_ANLG_1);
    _SF_ALL_QMAP_SORT.insert(156, SF_USER_ANLG_2);
    _SF_ALL_QMAP_SORT.insert(157, SF_DUMP_DEBUG);

    return _SF_ALL_QMAP_SORT;
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
    _SF_DIGITAL_QMAP.insert(SF_MG2_FIRE, "2nd Machine Gun - Fire");
    _SF_DIGITAL_QMAP.insert(SF_MG2_OFF, "2nd Machine Gun - Stop");
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
    _SF_DIGITAL_QMAP.insert(SF_AUXOUT_TOGGLEDIM, "Aux Output - Toggle Dim Level");
    _SF_DIGITAL_QMAP.insert(SF_AUXOUT_FLASH, "Aux Output - Flash");
    _SF_DIGITAL_QMAP.insert(SF_AUXOUT_INV_FLASH, "Aux Output - Inverse Flash");
    _SF_DIGITAL_QMAP.insert(SF_AUXOUT_BLINK, "Aux Output - Blink");
    _SF_DIGITAL_QMAP.insert(SF_AUXOUT_TOGGLEBLINK, "Aux Output - Toggle Blink");
    _SF_DIGITAL_QMAP.insert(SF_AUXOUT_REVOLVE, "Aux Output - Revolving Light");
    _SF_DIGITAL_QMAP.insert(SF_AUXOUT_TOGGLEREVOLVE, "Aux Output - Toggle Revolving Light");
    _SF_DIGITAL_QMAP.insert(SF_INCR_VOLUME, "Sound Card - Start Increasing Volume");
    _SF_DIGITAL_QMAP.insert(SF_DECR_VOLUME, "Sound Card - Start Decreasing Volume");
    _SF_DIGITAL_QMAP.insert(SF_STOP_VOLUME, "Sound Card - Stop Changing Volume");
    _SF_DIGITAL_QMAP.insert(SF_OVERLAY_ENABLE, "Sound Card - Enable Track Sounds");
    _SF_DIGITAL_QMAP.insert(SF_OVERLAY_DISABLE, "Sound Card - Disable Track Sounds");
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
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND5_ONCE, "User Sound 5 - Play once");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND5_RPT, "User Sound 5 - Repeat");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND5_OFF, "User Sound 5 - Stop");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND6_ONCE, "User Sound 6 - Play once");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND6_RPT, "User Sound 6 - Repeat");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND6_OFF, "User Sound 6 - Stop");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND7_ONCE, "User Sound 7 - Play once");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND7_RPT, "User Sound 7 - Repeat");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND7_OFF, "User Sound 7 - Stop");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND8_ONCE, "User Sound 8 - Play once");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND8_RPT, "User Sound 8 - Repeat");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND8_OFF, "User Sound 8 - Stop");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND9_ONCE, "User Sound 9 - Play once");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND9_RPT, "User Sound 9 - Repeat");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND9_OFF, "User Sound 9 - Stop");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND10_ONCE, "User Sound 10 - Play once");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND10_RPT, "User Sound 10 - Repeat");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND10_OFF, "User Sound 10 - Stop");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND11_ONCE, "User Sound 11 - Play once");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND11_RPT, "User Sound 11 - Repeat");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND11_OFF, "User Sound 11 - Stop");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND12_ONCE, "User Sound 12 - Play once");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND12_RPT, "User Sound 12 - Repeat");
    _SF_DIGITAL_QMAP.insert(SF_USER_SOUND12_OFF, "User Sound 12 - Stop");
    _SF_DIGITAL_QMAP.insert(SF_SBA_PLAYSTOP, "Sound Bank A - Play/Stop");
    _SF_DIGITAL_QMAP.insert(SF_SBA_NEXT, "Sound Bank A - Play Next");
    _SF_DIGITAL_QMAP.insert(SF_SBA_PREVIOUS, "Sound Bank A - Play Previous");
    _SF_DIGITAL_QMAP.insert(SF_SBA_RANDOM, "Sound Bank A - Play Random");
    _SF_DIGITAL_QMAP.insert(SF_SBB_PLAYSTOP, "Sound Bank B - Play/Stop");
    _SF_DIGITAL_QMAP.insert(SF_SBB_NEXT, "Sound Bank B - Play Next");
    _SF_DIGITAL_QMAP.insert(SF_SBB_PREVIOUS, "Sound Bank B - Play Previous");
    _SF_DIGITAL_QMAP.insert(SF_SBB_RANDOM, "Sound Bank B - Play Random");
    _SF_DIGITAL_QMAP.insert(SF_OUTPUT_A_TOGGLE, "External Output A - Toggle");
    _SF_DIGITAL_QMAP.insert(SF_OUTPUT_A_ON, "Logic Level Output A - Turn On");
    _SF_DIGITAL_QMAP.insert(SF_OUTPUT_A_OFF, "Logic Level Output A - Turn Off");
    _SF_DIGITAL_QMAP.insert(SF_OUTPUT_A_PULSE, "External Output A - Pulse");
    _SF_DIGITAL_QMAP.insert(SF_OUTPUT_A_BLINK, "External Output A - Blink");
    _SF_DIGITAL_QMAP.insert(SF_OUTPUT_B_TOGGLE, "Logic Level Output B - Toggle");
    _SF_DIGITAL_QMAP.insert(SF_OUTPUT_B_ON, "Logic Level Output B - Turn On");
    _SF_DIGITAL_QMAP.insert(SF_OUTPUT_B_OFF, "Logicl Level Output B - Turn Off");
    _SF_DIGITAL_QMAP.insert(SF_OUTPUT_B_PULSE, "External Output B - Pulse");
    _SF_DIGITAL_QMAP.insert(SF_OUTPUT_B_BLINK, "External Output B - Blink");
    _SF_DIGITAL_QMAP.insert(SF_MOTOR_A_ON, "Motor A - On");
    _SF_DIGITAL_QMAP.insert(SF_MOTOR_A_OFF, "Motor A - Off");
    _SF_DIGITAL_QMAP.insert(SF_MOTOR_A_TOGGLE, "Motor A - Toggle On/Off");
    _SF_DIGITAL_QMAP.insert(SF_MOTOR_B_ON, "Motor B - On");
    _SF_DIGITAL_QMAP.insert(SF_MOTOR_B_OFF, "Motor B - Off");
    _SF_DIGITAL_QMAP.insert(SF_MOTOR_B_TOGGLE, "Motor B - Toggle On/Off");
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
    _SF_DIGITAL_QMAP.insert(SF_SPEED_75, "Reduce Speed to 75%");
    _SF_DIGITAL_QMAP.insert(SF_SPEED_50, "Reduce Speed to 50%");
    _SF_DIGITAL_QMAP.insert(SF_SPEED_25, "Reduce Speed to 25%");
    _SF_DIGITAL_QMAP.insert(SF_SPEED_RESTORE, "Restore Speed");
    _SF_DIGITAL_QMAP.insert(SF_SMOKER_ENABLE, "Smoker - Enable");
    _SF_DIGITAL_QMAP.insert(SF_SMOKER_DISABLE, "Smoker - Disable");
    _SF_DIGITAL_QMAP.insert(SF_SMOKER_TOGGLE, "Smoker - Toggle");
    _SF_DIGITAL_QMAP.insert(SF_MANTRANS_FWD, "Manual Transmission - Forward");
    _SF_DIGITAL_QMAP.insert(SF_MANTRANS_REV, "Manual Transmission - Reverse");
    _SF_DIGITAL_QMAP.insert(SF_MANTRANS_NEUTRAL, "Manual Transmission - Neutral");
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

QMap<_special_function, QString> OP_QMaps::getEmptySpecialFunctionsQMap()
{
    // Just give a single blank value
    _SF_EMPTY_QMAP.insert(SF_NULL_FUNCTION, "");  // No function
    return _SF_EMPTY_QMAP;
}


// ---------------------------------------------------------------------------------------------------------->>
// TRIGGER SOURCES
// ---------------------------------------------------------------------------------------------------------->>
QMap<_trigger_source, QString> OP_QMaps::getAllTriggerSourcesQMap()
{
    // Create the trigger list
    _OPT_ALL_QMAP.insert(TS_NULL_TRIGGER, "");                                  // no trigger
    _OPT_ALL_QMAP.insert(TS_TURRET_STICK, "Turret Stick");                      // Turret stick
    _OPT_ALL_QMAP.insert(TS_AUX1, "Aux Channel 1");                             // Aux channel 1
    _OPT_ALL_QMAP.insert(TS_AUX2, "Aux Channel 2");                             // Aux channel 2
    _OPT_ALL_QMAP.insert(TS_AUX3, "Aux Channel 3");                             // Aux channel 3
    _OPT_ALL_QMAP.insert(TS_AUX4, "Aux Channel 4");                             // Aux channel 4
    _OPT_ALL_QMAP.insert(TS_AUX5, "Aux Channel 5");                             // Aux channel 5
    _OPT_ALL_QMAP.insert(TS_AUX6, "Aux Channel 6");                             // Aux channel 6
    _OPT_ALL_QMAP.insert(TS_AUX7, "Aux Channel 7");                             // Aux channel 7
    _OPT_ALL_QMAP.insert(TS_AUX8, "Aux Channel 8");                             // Aux channel 8
    _OPT_ALL_QMAP.insert(TS_AUX9, "Aux Channel 9");                             // Aux channel 9
    _OPT_ALL_QMAP.insert(TS_AUX10, "Aux Channel 10");                           // Aux channel 10
    _OPT_ALL_QMAP.insert(TS_AUX11, "Aux Channel 11");                           // Aux channel 11
    _OPT_ALL_QMAP.insert(TS_AUX12, "Aux Channel 12");                           // Aux channel 12
    _OPT_ALL_QMAP.insert(TS_INPUT_A, "External Input A");                       // External input A (if set to input)
    _OPT_ALL_QMAP.insert(TS_INPUT_B, "External Input B");                       // External input B (if set to input)
    _OPT_ALL_QMAP.insert(TS_SPEED_INCR, "Vehicle Speed Increases Above:");      // Speed increases above level trigger
    _OPT_ALL_QMAP.insert(TS_SPEED_INCR, "Vehicle Speed Decreases Below:");      // Speed falls below level trigger
    _OPT_ALL_QMAP.insert(TS_THROTTLE_COMMAND, "Throttle Command");              // Variable - throttle command
    _OPT_ALL_QMAP.insert(TS_ENGINE_SPEED, "Engine Speed");                      // Variable - engine speed
    _OPT_ALL_QMAP.insert(TS_VEHICLE_SPEED, "Vehicle Speed");                    // Variable - vehicle speed
    _OPT_ALL_QMAP.insert(TS_STEERING_COMMAND, "Steering Command");              // Variable - steering command
    _OPT_ALL_QMAP.insert(TS_ROTATION_COMMAND, "Turret Rotation Command");       // Variable - rotation command
    _OPT_ALL_QMAP.insert(TS_ELEVATION_COMMAND, "Barrel Elevation Command");     // Variable - elevation command
    _OPT_ALL_QMAP.insert(TS_ADHC_BRAKES, "Brakes Applied");                     // Ad-Hoc - brakes applied
    _OPT_ALL_QMAP.insert(TS_ADHC_CANNONHIT, "Cannon Hit");                      // Ad-Hoc - received cannon hit
    _OPT_ALL_QMAP.insert(TS_ADHC_CANNONRELOAD, "Cannon Reloaded");              // Ad-Hoc - cannon reloaded
    _OPT_ALL_QMAP.insert(TS_ADHC_DESTROYED, "Vehicle Destroyed");               // Ad-Hoc - vehicle destroyed
    _OPT_ALL_QMAP.insert(TS_ADHC_ENGINE_START, "Engine Start");                 // Ad-Hoc - engine start
    _OPT_ALL_QMAP.insert(TS_ADHC_ENGINE_STOP, "Engine Stop");                   // Ad-Hoc - engine stop
    _OPT_ALL_QMAP.insert(TS_ADHC_MOVE_FWD, "Moving Forward");                   // Ad-Hoc - forward movement started
    _OPT_ALL_QMAP.insert(TS_ADHC_MOVE_REV, "Moving Reverse");                   // Ad-Hoc - reverse movement started
    _OPT_ALL_QMAP.insert(TS_ADHC_VEHICLE_STOP, "Vehicle Stopped");              // Ad-Hoc - vehicle has come to a stop
    _OPT_ALL_QMAP.insert(TS_ADHC_RIGHT_TURN, "Right Turn");                     // Ad-Hoc - right turn started
    _OPT_ALL_QMAP.insert(TS_ADHC_LEFT_TURN, "Left Turn");                       // Ad-Hoc - left turn started
    _OPT_ALL_QMAP.insert(TS_ADHC_NO_TURN, "Turn Stopped");                      // Ad-Hoc - turn command ceased
    return _OPT_ALL_QMAP;
}

QMap<_trigger_source, QString> OP_QMaps::getDigitalTriggerSourcesQMap()
{
    // Create the trigger list, digital only.
    _OPT_DIGITAL_QMAP.insert(TS_NULL_TRIGGER, "");                              // no trigger
    _OPT_DIGITAL_QMAP.insert(TS_TURRET_STICK, "Turret Stick");                  // Turret stick
    _OPT_DIGITAL_QMAP.insert(TS_AUX1, "Aux Channel 1");                         // Aux channel 1
    _OPT_DIGITAL_QMAP.insert(TS_AUX2, "Aux Channel 2");                         // Aux channel 2
    _OPT_DIGITAL_QMAP.insert(TS_AUX3, "Aux Channel 3");                         // Aux channel 3
    _OPT_DIGITAL_QMAP.insert(TS_AUX4, "Aux Channel 4");                         // Aux channel 4
    _OPT_DIGITAL_QMAP.insert(TS_AUX5, "Aux Channel 5");                         // Aux channel 5
    _OPT_DIGITAL_QMAP.insert(TS_AUX6, "Aux Channel 6");                         // Aux channel 6
    _OPT_DIGITAL_QMAP.insert(TS_AUX7, "Aux Channel 7");                         // Aux channel 7
    _OPT_DIGITAL_QMAP.insert(TS_AUX8, "Aux Channel 8");                         // Aux channel 8
    _OPT_DIGITAL_QMAP.insert(TS_AUX9, "Aux Channel 9");                         // Aux channel 9
    _OPT_DIGITAL_QMAP.insert(TS_AUX10, "Aux Channel 10");                       // Aux channel 10
    _OPT_DIGITAL_QMAP.insert(TS_AUX11, "Aux Channel 11");                       // Aux channel 11
    _OPT_DIGITAL_QMAP.insert(TS_AUX12, "Aux Channel 12");                       // Aux channel 12
    _OPT_DIGITAL_QMAP.insert(TS_INPUT_A, "External Input A");                   // External input A (if set to input)
    _OPT_DIGITAL_QMAP.insert(TS_INPUT_B, "External Input B");                   // External input B (if set to input)
    _OPT_DIGITAL_QMAP.insert(TS_SPEED_INCR, "Vehicle Speed Increases Above:");  // Speed increases above level trigger
    _OPT_DIGITAL_QMAP.insert(TS_SPEED_INCR, "Vehicle Speed Decreases Below:");  // Speed falls below level trigger
    _OPT_DIGITAL_QMAP.insert(TS_ADHC_BRAKES, "Brakes Applied");                 // Ad-Hoc - brakes applied
    _OPT_DIGITAL_QMAP.insert(TS_ADHC_CANNONHIT, "Cannon Hit");                  // Ad-Hoc - received cannon hit
    _OPT_DIGITAL_QMAP.insert(TS_ADHC_CANNONRELOAD, "Cannon Reloaded");          // Ad-Hoc - cannon reloaded
    _OPT_DIGITAL_QMAP.insert(TS_ADHC_DESTROYED, "Vehicle Destroyed");           // Ad-Hoc - vehicle destroyed
    _OPT_DIGITAL_QMAP.insert(TS_ADHC_ENGINE_START, "Engine Start");             // Ad-Hoc - engine start
    _OPT_DIGITAL_QMAP.insert(TS_ADHC_ENGINE_STOP, "Engine Stop");               // Ad-Hoc - engine stop
    _OPT_DIGITAL_QMAP.insert(TS_ADHC_MOVE_FWD, "Moving Forward");               // Ad-Hoc - forward movement started
    _OPT_DIGITAL_QMAP.insert(TS_ADHC_MOVE_REV, "Moving Reverse");               // Ad-Hoc - reverse movement started
    _OPT_DIGITAL_QMAP.insert(TS_ADHC_VEHICLE_STOP, "Vehicle Stopped");          // Ad-Hoc - vehicle has come to a stop
    _OPT_DIGITAL_QMAP.insert(TS_ADHC_RIGHT_TURN, "Right Turn");                 // Ad-Hoc - right turn started
    _OPT_DIGITAL_QMAP.insert(TS_ADHC_LEFT_TURN, "Left Turn");                   // Ad-Hoc - left turn started
    _OPT_DIGITAL_QMAP.insert(TS_ADHC_NO_TURN, "Turn Stopped");                  // Ad-Hoc - turn command ceased
    return _OPT_DIGITAL_QMAP;
}

QMap<_trigger_source, QString> OP_QMaps::getAnalogTriggerSourcesQMap()
{
    // Create the trigger list
    _OPT_ANALOG_QMAP.insert(TS_NULL_TRIGGER, "");                               // no trigger
    _OPT_ANALOG_QMAP.insert(TS_AUX1, "Aux Channel 1");                          // Aux channel 1
    _OPT_ANALOG_QMAP.insert(TS_AUX2, "Aux Channel 2");                          // Aux channel 2
    _OPT_ANALOG_QMAP.insert(TS_AUX3, "Aux Channel 3");                          // Aux channel 3
    _OPT_ANALOG_QMAP.insert(TS_AUX4, "Aux Channel 4");                          // Aux channel 4
    _OPT_ANALOG_QMAP.insert(TS_AUX5, "Aux Channel 5");                          // Aux channel 5
    _OPT_ANALOG_QMAP.insert(TS_AUX6, "Aux Channel 6");                          // Aux channel 6
    _OPT_ANALOG_QMAP.insert(TS_AUX7, "Aux Channel 7");                          // Aux channel 7
    _OPT_ANALOG_QMAP.insert(TS_AUX8, "Aux Channel 8");                          // Aux channel 8
    _OPT_ANALOG_QMAP.insert(TS_AUX9, "Aux Channel 9");                          // Aux channel 9
    _OPT_ANALOG_QMAP.insert(TS_AUX10, "Aux Channel 10");                        // Aux channel 10
    _OPT_ANALOG_QMAP.insert(TS_AUX11, "Aux Channel 11");                        // Aux channel 11
    _OPT_ANALOG_QMAP.insert(TS_AUX12, "Aux Channel 12");                        // Aux channel 12
    _OPT_ANALOG_QMAP.insert(TS_INPUT_A, "External Input A");                    // External input A (if set to input)
    _OPT_ANALOG_QMAP.insert(TS_INPUT_B, "External Input B");                    // External input B (if set to input)
    _OPT_ANALOG_QMAP.insert(TS_THROTTLE_COMMAND, "Throttle Command");           // Variable - throttle command
    _OPT_ANALOG_QMAP.insert(TS_ENGINE_SPEED, "Engine Speed");                   // Variable - engine speed
    _OPT_ANALOG_QMAP.insert(TS_VEHICLE_SPEED, "Vehicle Speed");                 // Variable - vehicle speed
    _OPT_ANALOG_QMAP.insert(TS_STEERING_COMMAND, "Steering Command");           // Variable - steering command
    _OPT_ANALOG_QMAP.insert(TS_ROTATION_COMMAND, "Turret Rotation Command");    // Variable - rotation command
    _OPT_ANALOG_QMAP.insert(TS_ELEVATION_COMMAND, "Barrel Elevation Command");  // Variable - elevation command
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

boolean OP_QMaps::isTriggerSourceAuxChannel(_trigger_source ts)
{
    // Check this function against all in the aux channel list
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

