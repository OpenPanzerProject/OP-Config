#ifndef OP_EEPROM_VARINFO
#define OP_EEPROM_VARINFO

#include <arduino_compat.h>         // Gives us Arduino-like data type names

//--------------------------------------------------------------------------------------------------------------------------------------->>
//=======================================================================================================================================>>
// VERY IMPORTANT !
//=======================================================================================================================================>>
// You must make sure this number equals the number of variables defined in the __eeprom_data struct (including the first var FirstVar)
//
    #define NUM_STORED_VARS			333

//
// The definition above, as well as the PROGMEM array below, can be generated from the Excel reference sheet
//=======================================================================================================================================>>
//--------------------------------------------------------------------------------------------------------------------------------------->>


#define RADIO_SETTINGS_START_ID     1011    // Radio settings begin with this var ID
#define RADIO_SETTINGS_END_ID       1294    // Radio settings will not exceed this var ID
#define FUNCTION_TRIGGERS_START_ID  1411    // Function triggers begin with this var ID

// Data types that we are using. Currently we have no need for floats
typedef uint8_t _vartype;
#define varNULL      0
#define varBOOL      1
#define varCHAR      2
#define varINT8      3
#define varUINT8	 4
#define varINT16     5
#define varUINT16	 6
#define varINT32     7
#define varUINT32    8
#define LAST_VARTYPE varUINT32


// Meta-data we want to know for each storage/eeprom variable,
// as well as the actual literal data (Data)
struct _storage_var_info {
    uint16_t varID;             // Arbitrary ID set by the software developer
    uint16_t varOffset;         // Offset of this variable within the _eeprom_data structure
    _vartype varType;           // Type of variable. This will let us determine bytes and sign.
    QByteArray defaultValue;    // Value as a string of chars - these are the default values, and will be constant
};


// An array of meta-data about every variable in the _eeprom_data struct
// The _storage_var_info struct has four members: ID, Offset, VarType, and the actual Data
// We initialize the first three which we already know and can generated automatically by the reference Excel sheet
// The Data will be read in from either an XML file or the device itself.
const _storage_var_info STORAGEVARS[NUM_STORED_VARS] = {
    {0, 0, varUINT8, "0"},        // FirstVar
    {1011, 1, varUINT8, "2"},        // ThrottleSettings.channelNum
    {1012, 2, varUINT16, "1000"},        // ThrottleSettings.pulseMin
    {1013, 4, varUINT16, "2000"},        // ThrottleSettings.pulseMax
    {1014, 6, varUINT16, "1500"},        // ThrottleSettings.pulseCenter
    {1015, 8, varUINT8, "15"},        // ThrottleSettings.deadband
    {1016, 9, varBOOL, "0"},        // ThrottleSettings.reversed
    {1017, 10, varUINT8, "4"},        // TurnSettings.channelNum
    {1018, 11, varUINT16, "1000"},        // TurnSettings.pulseMin
    {1019, 13, varUINT16, "2000"},        // TurnSettings.pulseMax
    {1020, 15, varUINT16, "1500"},        // TurnSettings.pulseCenter
    {1021, 17, varUINT8, "15"},        // TurnSettings.deadband
    {1022, 18, varBOOL, "0"},        // TurnSettings.reversed
    {1023, 19, varUINT8, "3"},        // ElevationSettings.channelNum
    {1024, 20, varUINT16, "1000"},        // ElevationSettings.pulseMin
    {1025, 22, varUINT16, "2000"},        // ElevationSettings.pulseMax
    {1026, 24, varUINT16, "1500"},        // ElevationSettings.pulseCenter
    {1027, 26, varUINT8, "15"},        // ElevationSettings.deadband
    {1028, 27, varBOOL, "0"},        // ElevationSettings.reversed
    {1029, 28, varUINT8, "1"},        // AzimuthSettings.channelNum
    {1030, 29, varUINT16, "1000"},        // AzimuthSettings.pulseMin
    {1031, 31, varUINT16, "2000"},        // AzimuthSettings.pulseMax
    {1032, 33, varUINT16, "1500"},        // AzimuthSettings.pulseCenter
    {1033, 35, varUINT8, "15"},        // AzimuthSettings.deadband
    {1034, 36, varBOOL, "0"},        // AzimuthSettings.reversed
    {1211, 37, varUINT8, "5"},        // Aux1_ChannelSettings.channelNum
    {1212, 38, varUINT16, "1000"},        // Aux1_ChannelSettings.pulseMin
    {1213, 40, varUINT16, "2000"},        // Aux1_ChannelSettings.pulseMax
    {1214, 42, varUINT16, "1500"},        // Aux1_ChannelSettings.pulseCenter
    {1215, 44, varBOOL, "1"},        // Aux1_ChannelSettings.Digital
    {1216, 45, varUINT8, "2"},        // Aux1_ChannelSettings.NumPositions
    {1217, 46, varBOOL, "0"},        // Aux1_ChannelSettings.reversed
    {1218, 47, varUINT8, "6"},        // Aux2_ChannelSettings.channelNum
    {1219, 48, varUINT16, "1000"},        // Aux2_ChannelSettings.pulseMin
    {1220, 50, varUINT16, "2000"},        // Aux2_ChannelSettings.pulseMax
    {1221, 52, varUINT16, "1500"},        // Aux2_ChannelSettings.pulseCenter
    {1222, 54, varBOOL, "1"},        // Aux2_ChannelSettings.Digital
    {1223, 55, varUINT8, "2"},        // Aux2_ChannelSettings.NumPositions
    {1224, 56, varBOOL, "0"},        // Aux2_ChannelSettings.reversed
    {1225, 57, varUINT8, "7"},        // Aux3_ChannelSettings.channelNum
    {1226, 58, varUINT16, "1000"},        // Aux3_ChannelSettings.pulseMin
    {1227, 60, varUINT16, "2000"},        // Aux3_ChannelSettings.pulseMax
    {1228, 62, varUINT16, "1500"},        // Aux3_ChannelSettings.pulseCenter
    {1229, 64, varBOOL, "1"},        // Aux3_ChannelSettings.Digital
    {1230, 65, varUINT8, "2"},        // Aux3_ChannelSettings.NumPositions
    {1231, 66, varBOOL, "0"},        // Aux3_ChannelSettings.reversed
    {1232, 67, varUINT8, "8"},        // Aux4_ChannelSettings.channelNum
    {1233, 68, varUINT16, "1000"},        // Aux4_ChannelSettings.pulseMin
    {1234, 70, varUINT16, "2000"},        // Aux4_ChannelSettings.pulseMax
    {1235, 72, varUINT16, "1500"},        // Aux4_ChannelSettings.pulseCenter
    {1236, 74, varBOOL, "1"},        // Aux4_ChannelSettings.Digital
    {1237, 75, varUINT8, "2"},        // Aux4_ChannelSettings.NumPositions
    {1238, 76, varBOOL, "0"},        // Aux4_ChannelSettings.reversed
    {1239, 77, varUINT8, "9"},        // Aux5_ChannelSettings.channelNum
    {1240, 78, varUINT16, "1000"},        // Aux5_ChannelSettings.pulseMin
    {1241, 80, varUINT16, "2000"},        // Aux5_ChannelSettings.pulseMax
    {1242, 82, varUINT16, "1500"},        // Aux5_ChannelSettings.pulseCenter
    {1243, 84, varBOOL, "1"},        // Aux5_ChannelSettings.Digital
    {1244, 85, varUINT8, "2"},        // Aux5_ChannelSettings.NumPositions
    {1245, 86, varBOOL, "0"},        // Aux5_ChannelSettings.reversed
    {1246, 87, varUINT8, "10"},        // Aux6_ChannelSettings.channelNum
    {1247, 88, varUINT16, "1000"},        // Aux6_ChannelSettings.pulseMin
    {1248, 90, varUINT16, "2000"},        // Aux6_ChannelSettings.pulseMax
    {1249, 92, varUINT16, "1500"},        // Aux6_ChannelSettings.pulseCenter
    {1250, 94, varBOOL, "1"},        // Aux6_ChannelSettings.Digital
    {1251, 95, varUINT8, "2"},        // Aux6_ChannelSettings.NumPositions
    {1252, 96, varBOOL, "0"},        // Aux6_ChannelSettings.reversed
    {1253, 97, varUINT8, "11"},        // Aux7_ChannelSettings.channelNum
    {1254, 98, varUINT16, "1000"},        // Aux7_ChannelSettings.pulseMin
    {1255, 100, varUINT16, "2000"},        // Aux7_ChannelSettings.pulseMax
    {1256, 102, varUINT16, "1500"},        // Aux7_ChannelSettings.pulseCenter
    {1257, 104, varBOOL, "1"},        // Aux7_ChannelSettings.Digital
    {1258, 105, varUINT8, "2"},        // Aux7_ChannelSettings.NumPositions
    {1259, 106, varBOOL, "0"},        // Aux7_ChannelSettings.reversed
    {1260, 107, varUINT8, "12"},        // Aux8_ChannelSettings.channelNum
    {1261, 108, varUINT16, "1000"},        // Aux8_ChannelSettings.pulseMin
    {1262, 110, varUINT16, "2000"},        // Aux8_ChannelSettings.pulseMax
    {1263, 112, varUINT16, "1500"},        // Aux8_ChannelSettings.pulseCenter
    {1264, 114, varBOOL, "1"},        // Aux8_ChannelSettings.Digital
    {1265, 115, varUINT8, "2"},        // Aux8_ChannelSettings.NumPositions
    {1266, 116, varBOOL, "0"},        // Aux8_ChannelSettings.reversed
    {1267, 117, varUINT8, "13"},        // Aux9_ChannelSettings.channelNum
    {1268, 118, varUINT16, "1000"},        // Aux9_ChannelSettings.pulseMin
    {1269, 120, varUINT16, "2000"},        // Aux9_ChannelSettings.pulseMax
    {1270, 122, varUINT16, "1500"},        // Aux9_ChannelSettings.pulseCenter
    {1271, 124, varBOOL, "1"},        // Aux9_ChannelSettings.Digital
    {1272, 125, varUINT8, "2"},        // Aux9_ChannelSettings.NumPositions
    {1273, 126, varBOOL, "0"},        // Aux9_ChannelSettings.reversed
    {1274, 127, varUINT8, "14"},        // Aux10_ChannelSettings.channelNum
    {1275, 128, varUINT16, "1000"},        // Aux10_ChannelSettings.pulseMin
    {1276, 130, varUINT16, "2000"},        // Aux10_ChannelSettings.pulseMax
    {1277, 132, varUINT16, "1500"},        // Aux10_ChannelSettings.pulseCenter
    {1278, 134, varBOOL, "1"},        // Aux10_ChannelSettings.Digital
    {1279, 135, varUINT8, "2"},        // Aux10_ChannelSettings.NumPositions
    {1280, 136, varBOOL, "0"},        // Aux10_ChannelSettings.reversed
    {1281, 137, varUINT8, "15"},        // Aux11_ChannelSettings.channelNum
    {1282, 138, varUINT16, "1000"},        // Aux11_ChannelSettings.pulseMin
    {1283, 140, varUINT16, "2000"},        // Aux11_ChannelSettings.pulseMax
    {1284, 142, varUINT16, "1500"},        // Aux11_ChannelSettings.pulseCenter
    {1285, 144, varBOOL, "1"},        // Aux11_ChannelSettings.Digital
    {1286, 145, varUINT8, "2"},        // Aux11_ChannelSettings.NumPositions
    {1287, 146, varBOOL, "0"},        // Aux11_ChannelSettings.reversed
    {1288, 147, varUINT8, "16"},        // Aux12_ChannelSettings.channelNum
    {1289, 148, varUINT16, "1000"},        // Aux12_ChannelSettings.pulseMin
    {1290, 150, varUINT16, "2000"},        // Aux12_ChannelSettings.pulseMax
    {1291, 152, varUINT16, "1500"},        // Aux12_ChannelSettings.pulseCenter
    {1292, 154, varBOOL, "1"},        // Aux12_ChannelSettings.Digital
    {1293, 155, varUINT8, "2"},        // Aux12_ChannelSettings.NumPositions
    {1294, 156, varBOOL, "0"},        // Aux12_ChannelSettings.reversed
    {1311, 157, varUINT8, "0"},        // PortA_Settings.dataDirection
    {1312, 158, varUINT8, "1"},        // PortA_Settings.dataType
    {1313, 159, varUINT8, "0"},        // PortB_Settings.dataDirection
    {1314, 160, varUINT8, "1"},        // PortB_Settings.dataType
    {1315, 161, varUINT16, "650"},        // IOBlinkOnTime_mS
    {1316, 163, varUINT16, "650"},        // IOBlinkOffTime_mS
    {1317, 165, varUINT16, "300"},        // IOPulseOnTime_mS
    {1411, 167, varUINT16, "36"},        // SF_Trigger[0].TriggerID
    {1412, 169, varUINT8, "1"},        // SF_Trigger[0].specialFunction
    {1413, 170, varUINT16, "12"},        // SF_Trigger[1].TriggerID
    {1414, 172, varUINT8, "4"},        // SF_Trigger[1].specialFunction
    {1415, 173, varUINT16, "33"},        // SF_Trigger[2].TriggerID
    {1416, 175, varUINT8, "7"},        // SF_Trigger[2].specialFunction
    {1417, 176, varUINT16, "9"},        // SF_Trigger[3].TriggerID
    {1418, 178, varUINT8, "16"},        // SF_Trigger[3].specialFunction
    {1419, 179, varUINT16, "0"},        // SF_Trigger[4].TriggerID
    {1420, 181, varUINT8, "0"},        // SF_Trigger[4].specialFunction
    {1421, 182, varUINT16, "0"},        // SF_Trigger[5].TriggerID
    {1422, 184, varUINT8, "0"},        // SF_Trigger[5].specialFunction
    {1423, 185, varUINT16, "0"},        // SF_Trigger[6].TriggerID
    {1424, 187, varUINT8, "0"},        // SF_Trigger[6].specialFunction
    {1425, 188, varUINT16, "0"},        // SF_Trigger[7].TriggerID
    {1426, 190, varUINT8, "0"},        // SF_Trigger[7].specialFunction
    {1427, 191, varUINT16, "0"},        // SF_Trigger[8].TriggerID
    {1428, 193, varUINT8, "0"},        // SF_Trigger[8].specialFunction
    {1429, 194, varUINT16, "0"},        // SF_Trigger[9].TriggerID
    {1430, 196, varUINT8, "0"},        // SF_Trigger[9].specialFunction
    {1431, 197, varUINT16, "0"},        // SF_Trigger[10].TriggerID
    {1432, 199, varUINT8, "0"},        // SF_Trigger[10].specialFunction
    {1433, 200, varUINT16, "0"},        // SF_Trigger[11].TriggerID
    {1434, 202, varUINT8, "0"},        // SF_Trigger[11].specialFunction
    {1435, 203, varUINT16, "0"},        // SF_Trigger[12].TriggerID
    {1436, 205, varUINT8, "0"},        // SF_Trigger[12].specialFunction
    {1437, 206, varUINT16, "0"},        // SF_Trigger[13].TriggerID
    {1438, 208, varUINT8, "0"},        // SF_Trigger[13].specialFunction
    {1439, 209, varUINT16, "0"},        // SF_Trigger[14].TriggerID
    {1440, 211, varUINT8, "0"},        // SF_Trigger[14].specialFunction
    {1441, 212, varUINT16, "0"},        // SF_Trigger[15].TriggerID
    {1442, 214, varUINT8, "0"},        // SF_Trigger[15].specialFunction
    {1443, 215, varUINT16, "0"},        // SF_Trigger[16].TriggerID
    {1444, 217, varUINT8, "0"},        // SF_Trigger[16].specialFunction
    {1445, 218, varUINT16, "0"},        // SF_Trigger[17].TriggerID
    {1446, 220, varUINT8, "0"},        // SF_Trigger[17].specialFunction
    {1447, 221, varUINT16, "0"},        // SF_Trigger[18].TriggerID
    {1448, 223, varUINT8, "0"},        // SF_Trigger[18].specialFunction
    {1449, 224, varUINT16, "0"},        // SF_Trigger[19].TriggerID
    {1450, 226, varUINT8, "0"},        // SF_Trigger[19].specialFunction
    {1451, 227, varUINT16, "0"},        // SF_Trigger[20].TriggerID
    {1452, 229, varUINT8, "0"},        // SF_Trigger[20].specialFunction
    {1453, 230, varUINT16, "0"},        // SF_Trigger[21].TriggerID
    {1454, 232, varUINT8, "0"},        // SF_Trigger[21].specialFunction
    {1455, 233, varUINT16, "0"},        // SF_Trigger[22].TriggerID
    {1456, 235, varUINT8, "0"},        // SF_Trigger[22].specialFunction
    {1457, 236, varUINT16, "0"},        // SF_Trigger[23].TriggerID
    {1458, 238, varUINT8, "0"},        // SF_Trigger[23].specialFunction
    {1459, 239, varUINT16, "0"},        // SF_Trigger[24].TriggerID
    {1460, 241, varUINT8, "0"},        // SF_Trigger[24].specialFunction
    {1461, 242, varUINT16, "0"},        // SF_Trigger[25].TriggerID
    {1462, 244, varUINT8, "0"},        // SF_Trigger[25].specialFunction
    {1463, 245, varUINT16, "0"},        // SF_Trigger[26].TriggerID
    {1464, 247, varUINT8, "0"},        // SF_Trigger[26].specialFunction
    {1465, 248, varUINT16, "0"},        // SF_Trigger[27].TriggerID
    {1466, 250, varUINT8, "0"},        // SF_Trigger[27].specialFunction
    {1467, 251, varUINT16, "0"},        // SF_Trigger[28].TriggerID
    {1468, 253, varUINT8, "0"},        // SF_Trigger[28].specialFunction
    {1469, 254, varUINT16, "0"},        // SF_Trigger[29].TriggerID
    {1470, 256, varUINT8, "0"},        // SF_Trigger[29].specialFunction
    {1471, 257, varUINT16, "0"},        // SF_Trigger[30].TriggerID
    {1472, 259, varUINT8, "0"},        // SF_Trigger[30].specialFunction
    {1473, 260, varUINT16, "0"},        // SF_Trigger[31].TriggerID
    {1474, 262, varUINT8, "0"},        // SF_Trigger[31].specialFunction
    {1475, 263, varUINT16, "0"},        // SF_Trigger[32].TriggerID
    {1476, 265, varUINT8, "0"},        // SF_Trigger[32].specialFunction
    {1477, 266, varUINT16, "0"},        // SF_Trigger[33].TriggerID
    {1478, 268, varUINT8, "0"},        // SF_Trigger[33].specialFunction
    {1479, 269, varUINT16, "0"},        // SF_Trigger[34].TriggerID
    {1480, 271, varUINT8, "0"},        // SF_Trigger[34].specialFunction
    {1481, 272, varUINT16, "0"},        // SF_Trigger[35].TriggerID
    {1482, 274, varUINT8, "0"},        // SF_Trigger[35].specialFunction
    {1483, 275, varUINT16, "0"},        // SF_Trigger[36].TriggerID
    {1484, 277, varUINT8, "0"},        // SF_Trigger[36].specialFunction
    {1485, 278, varUINT16, "0"},        // SF_Trigger[37].TriggerID
    {1486, 280, varUINT8, "0"},        // SF_Trigger[37].specialFunction
    {1487, 281, varUINT16, "0"},        // SF_Trigger[38].TriggerID
    {1488, 283, varUINT8, "0"},        // SF_Trigger[38].specialFunction
    {1489, 284, varUINT16, "0"},        // SF_Trigger[39].TriggerID
    {1490, 286, varUINT8, "0"},        // SF_Trigger[39].specialFunction
    {1611, 287, varUINT8, "10"},        // DriveMotors
    {1612, 288, varUINT8, "11"},        // TurretRotationMotor
    {1613, 289, varUINT8, "11"},        // TurretElevationMotor
    {1811, 290, varINT16, "1000"},        // TurretElevation_EPMin
    {1812, 292, varINT16, "2000"},        // TurretElevation_EPMax
    {1813, 294, varBOOL, "0"},        // TurretElevation_Reversed
    {1814, 295, varUINT8, "100"},        // TurretElevation_MaxSpeedPct
    {1815, 296, varUINT8, "100"},        // TurretRotation_MaxSpeedPct
    {1816, 297, varINT16, "1000"},        // TurretRotation_EPMin
    {1817, 299, varINT16, "2000"},        // TurretRotation_EPMax
    {1818, 301, varBOOL, "0"},        // TurretRotation_Reversed
    {1911, 302, varINT16, "1000"},        // SteeringServo_EPMin
    {1912, 304, varINT16, "2000"},        // SteeringServo_EPMax
    {1913, 306, varBOOL, "0"},        // SteeringServo_Reversed
    {2011, 307, varBOOL, "0"},        // Airsoft
    {2012, 308, varBOOL, "1"},        // MechanicalBarrelWithCannon
    {2013, 309, varINT16, "0"},        // RecoilDelay
    {2014, 311, varBOOL, "1"},        // RecoilReversed
    {2015, 312, varBOOL, "1"},        // ServoRecoilWithCannon
    {2016, 313, varINT16, "200"},        // RecoilServo_Recoil_mS
    {2017, 315, varINT16, "800"},        // RecoilServo_Return_mS
    {2018, 317, varINT16, "1000"},        // RecoilServo_EPMin
    {2019, 319, varINT16, "2000"},        // RecoilServo_EPMax
    {2020, 321, varUINT8, "0"},        // RecoilServo_PresetNum
    {2211, 322, varBOOL, "1"},        // SmokerControlAuto
    {2212, 323, varINT16, "89"},        // SmokerIdleSpeed
    {2213, 325, varINT16, "128"},        // SmokerFastIdleSpeed
    {2214, 327, varINT16, "255"},        // SmokerMaxSpeed
    {2215, 329, varINT16, "255"},        // SmokerDestroyedSpeed
    {2216, 331, varUINT8, "0"},        // SmokerDeviceType
    {2217, 332, varUINT8, "0"},        // SmokerPreHeat_Sec
    {2218, 333, varINT16, "255"},        // SmokerHeatIdleAmt
    {2219, 335, varINT16, "255"},        // SmokerHeatFastIdleAmt
    {2220, 337, varINT16, "255"},        // SmokerHeatMaxAmt
    {2221, 339, varUINT8, "0"},        // HotStartTimeout_Sec
    {2411, 340, varBOOL, "1"},        // AccelRampEnabled_1
    {2412, 341, varUINT8, "4"},        // AccelSkipNum_1
    {2413, 342, varUINT8, "0"},        // AccelPreset_1
    {2414, 343, varBOOL, "1"},        // DecelRampEnabled_1
    {2415, 344, varUINT8, "4"},        // DecelSkipNum_1
    {2416, 345, varUINT8, "0"},        // DecelPreset_1
    {2417, 346, varBOOL, "0"},        // AccelRampEnabled_2
    {2418, 347, varUINT8, "1"},        // AccelSkipNum_2
    {2419, 348, varUINT8, "0"},        // AccelPreset_2
    {2420, 349, varBOOL, "0"},        // DecelRampEnabled_2
    {2421, 350, varUINT8, "1"},        // DecelSkipNum_2
    {2422, 351, varUINT8, "0"},        // DecelPreset_2
    {2423, 352, varUINT8, "40"},        // BrakeSensitivityPct
    {2424, 353, varUINT16, "1000"},        // TimeToShift_mS
    {2425, 355, varUINT16, "1000"},        // EnginePauseTime_mS
    {2426, 357, varUINT16, "2000"},        // TransmissionDelay_mS
    {2427, 359, varBOOL, "1"},        // NeutralTurnAllowed
    {2428, 360, varUINT8, "50"},        // NeutralTurnPct
    {2429, 361, varUINT8, "2"},        // TurnMode
    {2430, 362, varUINT8, "1"},        // DriveType
    {2431, 363, varUINT8, "100"},        // MaxForwardSpeedPct
    {2432, 364, varUINT8, "70"},        // MaxReverseSpeedPct
    {2433, 365, varUINT8, "50"},        // HalftrackTreadTurnPct
    {2434, 366, varBOOL, "0"},        // EngineAutoStart
    {2435, 367, varINT32, "0"},        // EngineAutoStopTime_mS
    {2436, 371, varUINT8, "0"},        // MotorNudgePct
    {2437, 372, varUINT16, "250"},        // NudgeTime_mS
    {2438, 374, varBOOL, "0"},        // DragInnerTrack
    {2439, 375, varBOOL, "0"},        // EnableTrackRecoil
    {2440, 376, varUINT8, "100"},        // TrackRecoilKickbackSpeed
    {2441, 377, varUINT8, "100"},        // TrackRecoilDecelerateFactor
    {2511, 378, varBOOL, "0"},        // EnableBarrelStabilize
    {2512, 379, varUINT8, "50"},        // BarrelSensitivity
    {2513, 380, varBOOL, "0"},        // EnableHillPhysics
    {2514, 381, varUINT8, "50"},        // HillSensitivity
    {2711, 382, varINT16, "350"},        // IgnoreTurretDelay_mS
    {2811, 384, varUINT8, "0"},        // SoundDevice
    {2812, 385, varUINT16, "1500"},        // Squeak1_MinInterval_mS
    {2813, 387, varUINT16, "4000"},        // Squeak1_MaxInterval_mS
    {2814, 389, varUINT16, "2000"},        // Squeak2_MinInterval_mS
    {2815, 391, varUINT16, "5000"},        // Squeak2_MaxInterval_mS
    {2816, 393, varUINT16, "3000"},        // Squeak3_MinInterval_mS
    {2817, 395, varUINT16, "8000"},        // Squeak3_MaxInterval_mS
    {2818, 397, varBOOL, "0"},        // Squeak1_Enabled
    {2819, 398, varBOOL, "0"},        // Squeak2_Enabled
    {2820, 399, varBOOL, "0"},        // Squeak3_Enabled
    {2821, 400, varUINT8, "25"},        // MinSqueakSpeed
    {2822, 401, varBOOL, "1"},        // HeadlightSound_Enabled
    {2823, 402, varBOOL, "1"},        // TurretSound_Enabled
    {2824, 403, varBOOL, "1"},        // BarrelSound_Enabled
    {2825, 404, varUINT16, "1000"},        // Squeak4_MinInterval_mS
    {2826, 406, varUINT16, "2000"},        // Squeak4_MaxInterval_mS
    {2827, 408, varUINT16, "3000"},        // Squeak5_MinInterval_mS
    {2828, 410, varUINT16, "4000"},        // Squeak5_MaxInterval_mS
    {2829, 412, varUINT16, "5000"},        // Squeak6_MinInterval_mS
    {2830, 414, varUINT16, "6000"},        // Squeak6_MaxInterval_mS
    {2831, 416, varBOOL, "0"},        // Squeak4_Enabled
    {2832, 417, varBOOL, "0"},        // Squeak5_Enabled
    {2833, 418, varBOOL, "0"},        // Squeak6_Enabled
    {2834, 419, varUINT8, "50"},        // VolumeEngine
    {2835, 420, varUINT8, "50"},        // VolumeTrackOverlay
    {2836, 421, varUINT8, "50"},        // VolumeEffects
    {2837, 422, varBOOL, "0"},        // HeadlightSound2_Enabled
    {2838, 423, varBOOL, "0"},        // SoundBankA_Loop
    {2839, 424, varBOOL, "0"},        // SoundBankB_Loop
    {3011, 425, varUINT8, "1"},        // IR_FireProtocol
    {3012, 426, varUINT8, "0"},        // IR_HitProtocol_2
    {3013, 427, varUINT8, "10"},        // IR_RepairProtocol
    {3014, 428, varUINT8, "0"},        // IR_MGProtocol
    {3015, 429, varBOOL, "0"},        // Use_MG_Protocol
    {3016, 430, varBOOL, "0"},        // Accept_MG_Damage
    {3017, 431, varUINT8, "0"},        // DamageProfile
    {3018, 432, varUINT16, "1500"},        // CustomClassSettings.reloadTime
    {3019, 434, varUINT16, "8000"},        // CustomClassSettings.recoveryTime
    {3020, 436, varUINT8, "1"},        // CustomClassSettings.maxHits
    {3021, 437, varUINT8, "10"},        // CustomClassSettings.maxMGHits
    {3022, 438, varBOOL, "0"},        // SendTankID
    {3023, 439, varUINT16, "1"},        // TankID
    {3024, 441, varUINT8, "0"},        // IR_Team
    {3211, 442, varUINT32, "115200"},        // USBSerialBaud
    {3212, 446, varUINT32, "115200"},        // AuxSerialBaud
    {3213, 450, varUINT32, "38400"},        // MotorSerialBaud
    {3214, 454, varUINT32, "38400"},        // Serial3TxBaud
    {3215, 458, varBOOL, "0"},        // LVC_Enabled
    {3216, 459, varUINT16, "6400"},        // LVC_Cutoff_mV
    {3411, 461, varBOOL, "0"},        // RunningLightsAlwaysOn
    {3412, 462, varUINT8, "30"},        // RunningLightsDimLevelPct
    {3413, 463, varBOOL, "0"},        // BrakesAutoOnAtStop
    {3414, 464, varUINT16, "30"},        // AuxLightFlashTime_mS
    {3415, 466, varUINT16, "30"},        // AuxLightBlinkOnTime_mS
    {3416, 468, varUINT16, "30"},        // AuxLightBlinkOffTime_mS
    {3417, 470, varUINT8, "30"},        // AuxLightPresetDim
    {3418, 471, varUINT8, "30"},        // MGLightBlink_mS
    {3419, 472, varBOOL, "1"},        // FlashLightsWhenSignalLost
    {3420, 473, varBOOL, "1"},        // HiFlashWithCannon
    {3421, 474, varBOOL, "0"},        // AuxFlashWithCannon
    {3422, 475, varUINT8, "30"},        // SecondMGLightBlink_mS
    {3423, 476, varBOOL, "1"},        // CannonReloadBlink
    {3424, 477, varBOOL, "0"},        // FlickerLightsOnEngineStart
    {3611, 478, varUINT8, "12"},        // ScoutCurrentLimit
    {9011, 479, varBOOL, "1"},        // PrintDebug
    {9999, 480, varUINT32, "52641"}        // InitStamp
};


#endif	// Define OP_EEPROM_VARINFO_H
