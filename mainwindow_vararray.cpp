#include "mainwindow.h"
#include "ui_mainwindow.h"

// See bottom of this file for array searching functions

//------------------------------------------------------------------------------------------------------------------------>>
// NAMED VARIABLES TO VARARRAY & VARARRAY TO NAMED VARIABLES
//------------------------------------------------------------------------------------------------------------------------>>
// We create typed, named variables for every setting where possible, using the same names as in the Open Panzer device code.
// While it is easy to write our VarArray to a file or the device, or read into from the same, there is no way around a long,
// hard-coded list when it comes to converting all the values in VarArray into their named variable equivalents.
// It is therefore crucial the two functions below are correct: any typos here will cause problems.

// Copy all values from VarArray to named variables
void MainWindow::VarArray_to_Variables(void)
{
    // THIS IS ALL HARD-CODED. I DON'T REALLY KNOW A GOOD WAY TO AUTOMATE IT.
    // OBVIOUSLY IF YOU SCREW UP SOMETHING HERE, BAD NEWS

    // Recall, all values in VarArray are in QByteArray format. It has no idea of the variable type.
    // Therefore as each VarArray value gets applied to a variable, it has to be cast to the appropriate type.
    // Almost everything can be taken care of with a conversion to Int or UInt. Boolean can be converted with UInt.
    // But it is easy to miss the difference between "toInt()" and "toUInt()" so watch out and make sure they're right!
    // The only time you need to use toInt is when the variable is signed.

    // Linear Channel Settings - 10xx
    DeviceData.Sticks.Throttle.Settings.channelNum = VarArray.value(1011).toUInt();         // 1011 - Throttle channel number
    DeviceData.Sticks.Throttle.Settings.pulseMin = VarArray.value(1012).toUInt();           // 1012 - Throttle pulse min
    DeviceData.Sticks.Throttle.Settings.pulseMax = VarArray.value(1013).toUInt();           // 1013 - Throttle pulse max
    DeviceData.Sticks.Throttle.Settings.pulseCenter = VarArray.value(1014).toUInt();        // 1014 - Throttle pulse center
    DeviceData.Sticks.Throttle.Settings.deadband = VarArray.value(1015).toUInt();           // 1015 - Throttle deadband
    DeviceData.Sticks.Throttle.Settings.reversed = VarArray.value(1016).toUInt();           // 1016 - Throttle reversed

    DeviceData.Sticks.Turn.Settings.channelNum = VarArray.value(1017).toUInt();             // 1017 - Turn channel number
    DeviceData.Sticks.Turn.Settings.pulseMin = VarArray.value(1018).toUInt();               // 1018 - Turn pulse min
    DeviceData.Sticks.Turn.Settings.pulseMax = VarArray.value(1019).toUInt();               // 1019 - Turn pulse max
    DeviceData.Sticks.Turn.Settings.pulseCenter = VarArray.value(1020).toUInt();            // 1020 - Turn pulse center
    DeviceData.Sticks.Turn.Settings.deadband = VarArray.value(1021).toUInt();               // 1021 - Turn deadband
    DeviceData.Sticks.Turn.Settings.reversed = VarArray.value(1022).toUInt();               // 1022 - Turn reversed

    DeviceData.Sticks.Elevation.Settings.channelNum = VarArray.value(1023).toUInt();        // 1023 - Elevation channel number
    DeviceData.Sticks.Elevation.Settings.pulseMin = VarArray.value(1024).toUInt();          // 1024 - Elevation pulse min
    DeviceData.Sticks.Elevation.Settings.pulseMax = VarArray.value(1025).toUInt();          // 1025 - Elevation pulse max
    DeviceData.Sticks.Elevation.Settings.pulseCenter = VarArray.value(1026).toUInt();       // 1026 - Elevation pulse center
    DeviceData.Sticks.Elevation.Settings.deadband = VarArray.value(1027).toUInt();          // 1027 - Elevation deadband
    DeviceData.Sticks.Elevation.Settings.reversed = VarArray.value(1028).toUInt();          // 1028 - Elevation reversed

    DeviceData.Sticks.Azimuth.Settings.channelNum = VarArray.value(1029).toUInt();          // 1029 - Azimuth channel number
    DeviceData.Sticks.Azimuth.Settings.pulseMin = VarArray.value(1030).toUInt();            // 1030 - Azimuth pulse min
    DeviceData.Sticks.Azimuth.Settings.pulseMax = VarArray.value(1031).toUInt();            // 1031 - Azimuth pulse max
    DeviceData.Sticks.Azimuth.Settings.pulseCenter = VarArray.value(1032).toUInt();         // 1032 - Azimuth pulse center
    DeviceData.Sticks.Azimuth.Settings.deadband = VarArray.value(1033).toUInt();            // 1032 - Azimuth deadband
    DeviceData.Sticks.Azimuth.Settings.reversed = VarArray.value(1034).toUInt();            // 1034 - Azimuth reversed

    // Aux Channel Settings - 12xx
    DeviceData.AuxChannel[0].Settings.channelNum = VarArray.value(1211).toUInt();           // 1211 - Aux 1 channel number
    DeviceData.AuxChannel[0].Settings.pulseMin = VarArray.value(1212).toUInt();             // 1212 - Aux 1 pulse min
    DeviceData.AuxChannel[0].Settings.pulseMax = VarArray.value(1213).toUInt();             // 1213 - Aux 1 pulse max
    DeviceData.AuxChannel[0].Settings.pulseCenter = VarArray.value(1214).toUInt();          // 1214 - Aux 1 pulse center
    DeviceData.AuxChannel[0].Settings.Digital = VarArray.value(1215).toUInt();              // 1215 - Aux 1 digital
    DeviceData.AuxChannel[0].Settings.numPositions = VarArray.value(1216).toUInt();         // 1216 - Aux 1 number of switch positions (if digital)
    DeviceData.AuxChannel[0].Settings.reversed = VarArray.value(1217).toUInt();             // 1217 - Aux 1 reversed

    DeviceData.AuxChannel[1].Settings.channelNum = VarArray.value(1218).toUInt();           // 1218 - Aux 2 channel number
    DeviceData.AuxChannel[1].Settings.pulseMin = VarArray.value(1219).toUInt();             // 1219 - Aux 2 pulse min
    DeviceData.AuxChannel[1].Settings.pulseMax = VarArray.value(1220).toUInt();             // 1220 - Aux 2 pulse max
    DeviceData.AuxChannel[1].Settings.pulseCenter = VarArray.value(1221).toUInt();          // 1221 - Aux 2 pulse center
    DeviceData.AuxChannel[1].Settings.Digital = VarArray.value(1222).toUInt();              // 1222 - Aux 2 digital
    DeviceData.AuxChannel[1].Settings.numPositions = VarArray.value(1223).toUInt();         // 1223 - Aux 2 number of switch positions (if digital)
    DeviceData.AuxChannel[1].Settings.reversed = VarArray.value(1224).toUInt();             // 1224 - Aux 2 reversed

    DeviceData.AuxChannel[2].Settings.channelNum = VarArray.value(1225).toUInt();           // 1225 - Aux 3 channel number
    DeviceData.AuxChannel[2].Settings.pulseMin = VarArray.value(1226).toUInt();             // 1226 - Aux 3 pulse min
    DeviceData.AuxChannel[2].Settings.pulseMax = VarArray.value(1227).toUInt();             // 1227 - Aux 3 pulse max
    DeviceData.AuxChannel[2].Settings.pulseCenter = VarArray.value(1228).toUInt();          // 1228 - Aux 3 pulse center
    DeviceData.AuxChannel[2].Settings.Digital = VarArray.value(1229).toUInt();              // 1229 - Aux 3 digital
    DeviceData.AuxChannel[2].Settings.numPositions = VarArray.value(1230).toUInt();         // 1230 - Aux 3 number of switch positions (if digital)
    DeviceData.AuxChannel[2].Settings.reversed = VarArray.value(1231).toUInt();             // 1231 - Aux 3 reversed

    DeviceData.AuxChannel[3].Settings.channelNum = VarArray.value(1232).toUInt();           // 1232 - Aux 4 channel number
    DeviceData.AuxChannel[3].Settings.pulseMin = VarArray.value(1233).toUInt();             // 1233 - Aux 4 pulse min
    DeviceData.AuxChannel[3].Settings.pulseMax = VarArray.value(1234).toUInt();             // 1234 - Aux 4 pulse max
    DeviceData.AuxChannel[3].Settings.pulseCenter = VarArray.value(1235).toUInt();          // 1235 - Aux 4 pulse center
    DeviceData.AuxChannel[3].Settings.Digital = VarArray.value(1236).toUInt();              // 1236 - Aux 4 digital
    DeviceData.AuxChannel[3].Settings.numPositions = VarArray.value(1237).toUInt();         // 1237 - Aux 4 number of switch positions (if digital)
    DeviceData.AuxChannel[3].Settings.reversed = VarArray.value(1238).toUInt();             // 1238 - Aux 4 reversed

    DeviceData.AuxChannel[4].Settings.channelNum = VarArray.value(1239).toUInt();           // 1239 - Aux 5 channel number
    DeviceData.AuxChannel[4].Settings.pulseMin = VarArray.value(1240).toUInt();             // 1240 - Aux 5 pulse min
    DeviceData.AuxChannel[4].Settings.pulseMax = VarArray.value(1241).toUInt();             // 1241 - Aux 5 pulse max
    DeviceData.AuxChannel[4].Settings.pulseCenter = VarArray.value(1242).toUInt();          // 1242 - Aux 5 pulse center
    DeviceData.AuxChannel[4].Settings.Digital = VarArray.value(1243).toUInt();              // 1243 - Aux 5 digital
    DeviceData.AuxChannel[4].Settings.numPositions = VarArray.value(1244).toUInt();         // 1244 - Aux 5 number of switch positions (if digital)
    DeviceData.AuxChannel[4].Settings.reversed = VarArray.value(1245).toUInt();             // 1245 - Aux 5 reversed

    DeviceData.AuxChannel[5].Settings.channelNum = VarArray.value(1246).toUInt();           // 1246 - Aux 6 channel number
    DeviceData.AuxChannel[5].Settings.pulseMin = VarArray.value(1247).toUInt();             // 1247 - Aux 6 pulse min
    DeviceData.AuxChannel[5].Settings.pulseMax = VarArray.value(1248).toUInt();             // 1248 - Aux 6 pulse max
    DeviceData.AuxChannel[5].Settings.pulseCenter = VarArray.value(1249).toUInt();          // 1249 - Aux 6 pulse center
    DeviceData.AuxChannel[5].Settings.Digital = VarArray.value(1250).toUInt();              // 1250 - Aux 6 digital
    DeviceData.AuxChannel[5].Settings.numPositions = VarArray.value(1251).toUInt();         // 1251 - Aux 6 number of switch positions (if digital)
    DeviceData.AuxChannel[5].Settings.reversed = VarArray.value(1252).toUInt();             // 1252 - Aux 6 reversed

    DeviceData.AuxChannel[6].Settings.channelNum = VarArray.value(1253).toUInt();           // 1253 - Aux 7 channel number
    DeviceData.AuxChannel[6].Settings.pulseMin = VarArray.value(1254).toUInt();             // 1254 - Aux 7 pulse min
    DeviceData.AuxChannel[6].Settings.pulseMax = VarArray.value(1255).toUInt();             // 1255 - Aux 7 pulse max
    DeviceData.AuxChannel[6].Settings.pulseCenter = VarArray.value(1256).toUInt();          // 1256 - Aux 7 pulse center
    DeviceData.AuxChannel[6].Settings.Digital = VarArray.value(1257).toUInt();              // 1257 - Aux 7 digital
    DeviceData.AuxChannel[6].Settings.numPositions = VarArray.value(1258).toUInt();         // 1258 - Aux 7 number of switch positions (if digital)
    DeviceData.AuxChannel[6].Settings.reversed = VarArray.value(1259).toUInt();             // 1259 - Aux 7 reversed

    DeviceData.AuxChannel[7].Settings.channelNum = VarArray.value(1260).toUInt();           // 1260 - Aux 8 channel number
    DeviceData.AuxChannel[7].Settings.pulseMin = VarArray.value(1261).toUInt();             // 1261 - Aux 8 pulse min
    DeviceData.AuxChannel[7].Settings.pulseMax = VarArray.value(1262).toUInt();             // 1262 - Aux 8 pulse max
    DeviceData.AuxChannel[7].Settings.pulseCenter = VarArray.value(1263).toUInt();          // 1263 - Aux 8 pulse center
    DeviceData.AuxChannel[7].Settings.Digital = VarArray.value(1264).toUInt();              // 1264 - Aux 8 digital
    DeviceData.AuxChannel[7].Settings.numPositions = VarArray.value(1265).toUInt();         // 1265 - Aux 8 number of switch positions (if digital)
    DeviceData.AuxChannel[7].Settings.reversed = VarArray.value(1266).toUInt();             // 1266 - Aux 8 reversed

    DeviceData.AuxChannel[8].Settings.channelNum = VarArray.value(1267).toUInt();           // 1267 - Aux 9 channel number
    DeviceData.AuxChannel[8].Settings.pulseMin = VarArray.value(1268).toUInt();             // 1268 - Aux 9 pulse min
    DeviceData.AuxChannel[8].Settings.pulseMax = VarArray.value(1269).toUInt();             // 1269 - Aux 9 pulse max
    DeviceData.AuxChannel[8].Settings.pulseCenter = VarArray.value(1270).toUInt();          // 1270 - Aux 9 pulse center
    DeviceData.AuxChannel[8].Settings.Digital = VarArray.value(1271).toUInt();              // 1271 - Aux 9 digital
    DeviceData.AuxChannel[8].Settings.numPositions = VarArray.value(1272).toUInt();         // 1272 - Aux 9 number of switch positions (if digital)
    DeviceData.AuxChannel[8].Settings.reversed = VarArray.value(1273).toUInt();             // 1273 - Aux 9 reversed

    DeviceData.AuxChannel[9].Settings.channelNum = VarArray.value(1274).toUInt();           // 1274 - Aux 10 channel number
    DeviceData.AuxChannel[9].Settings.pulseMin = VarArray.value(1275).toUInt();             // 1275 - Aux 10 pulse min
    DeviceData.AuxChannel[9].Settings.pulseMax = VarArray.value(1276).toUInt();             // 1276 - Aux 10 pulse max
    DeviceData.AuxChannel[9].Settings.pulseCenter = VarArray.value(1277).toUInt();          // 1277 - Aux 10 pulse center
    DeviceData.AuxChannel[9].Settings.Digital = VarArray.value(1278).toUInt();              // 1278 - Aux 10 digital
    DeviceData.AuxChannel[9].Settings.numPositions = VarArray.value(1279).toUInt();         // 1279 - Aux 10 number of switch positions (if digital)
    DeviceData.AuxChannel[9].Settings.reversed = VarArray.value(1280).toUInt();             // 1280 - Aux 10 reversed

    DeviceData.AuxChannel[10].Settings.channelNum = VarArray.value(1281).toUInt();          // 1281 - Aux 11 channel number
    DeviceData.AuxChannel[10].Settings.pulseMin = VarArray.value(1282).toUInt();            // 1282 - Aux 11 pulse min
    DeviceData.AuxChannel[10].Settings.pulseMax = VarArray.value(1283).toUInt();            // 1283 - Aux 11 pulse max
    DeviceData.AuxChannel[10].Settings.pulseCenter = VarArray.value(1284).toUInt();         // 1284 - Aux 11 pulse center
    DeviceData.AuxChannel[10].Settings.Digital = VarArray.value(1285).toUInt();             // 1285 - Aux 11 digital
    DeviceData.AuxChannel[10].Settings.numPositions = VarArray.value(1286).toUInt();        // 1286 - Aux 11 number of switch positions (if digital)
    DeviceData.AuxChannel[10].Settings.reversed = VarArray.value(1287).toUInt();            // 1287 - Aux 11 reversed

    DeviceData.AuxChannel[11].Settings.channelNum = VarArray.value(1288).toUInt();          // 1288 - Aux 12 channel number
    DeviceData.AuxChannel[11].Settings.pulseMin = VarArray.value(1289).toUInt();            // 1289 - Aux 12 pulse min
    DeviceData.AuxChannel[11].Settings.pulseMax = VarArray.value(1290).toUInt();            // 1290 - Aux 12 pulse max
    DeviceData.AuxChannel[11].Settings.pulseCenter = VarArray.value(1291).toUInt();         // 1291 - Aux 12 pulse center
    DeviceData.AuxChannel[11].Settings.Digital = VarArray.value(1292).toUInt();             // 1292 - Aux 12 digital
    DeviceData.AuxChannel[11].Settings.numPositions = VarArray.value(1293).toUInt();        // 1293 - Aux 12 number of switch positions (if digital)
    DeviceData.AuxChannel[11].Settings.reversed = VarArray.value(1294).toUInt();            // 1294 - Aux 12 reversed

    // External I/O Ports
    DeviceData.PortA.Settings.dataDirection = VarArray.value(1311).toUInt();                // 1311 - PortA data direction
    DeviceData.PortA.Settings.dataType = VarArray.value(1312).toUInt();                     // 1312 - PortA digital true/false if input, normally high/low if output
    DeviceData.PortB.Settings.dataDirection = VarArray.value(1313).toUInt();                // 1313 - PortB data direction
    DeviceData.PortB.Settings.dataType = VarArray.value(1314).toUInt();                     // 1314 - PortB digital true/false if input, normally high/low if output

    // Special Function Triggers - 14xx
    int j = 0;
    int startVal = 1411;
    for (int i=0; i<MAX_FUNCTION_TRIGGERS; i++)
    {
        DeviceData.SF_Trigger[i].TriggerID = VarArray.value(startVal + j).toUInt();                                           // 14xx - Special Function trigger i
        DeviceData.SF_Trigger[i].specialFunction = static_cast<_special_function>(VarArray.value(startVal + j + 1).toUInt()); // 14xx - Special Function function i
        j += 2;
    }

    // Motor Drive Types - 16xx
    DeviceData.DriveMotors = static_cast<Drive_t>(VarArray.value(1611).toUInt());           // 1611 - Drive motor type
    DeviceData.TurretRotationMotor = static_cast<Drive_t>(VarArray.value(1612).toUInt());   // 1612 - Turret rotation motor type
    DeviceData.TurretElevationMotor = static_cast<Drive_t>(VarArray.value(1613).toUInt());  // 1613 - Turret elevation motor type

    // Elevation Motor settings - 18xx
    DeviceData.TurretElevation_EPMin = VarArray.value(1811).toInt();                        // 1811 - Turret elevation end-point minimum
    DeviceData.TurretElevation_EPMax = VarArray.value(1812).toInt();                        // 1812 - Turret elevation end-point maximum
    DeviceData.TurretElevation_Reversed = VarArray.value(1813).toUInt();                    // 1813 - Turret elevation motor reversed
    DeviceData.TurretElevation_MaxSpeedPct = VarArray.value(1814).toUInt();                 // 1814 - Barrel elevation motor speed as percent of maximum
    DeviceData.TurretRotation_MaxSpeedPct = VarArray.value(1815).toUInt();                  // 1815 - Turret rotation motor speed as percent of maximum
    DeviceData.TurretRotation_EPMin = VarArray.value(1816).toInt();                         // 1816 - Turret rotation end-point minimum
    DeviceData.TurretRotation_EPMax = VarArray.value(1817).toInt();                         // 1817 - Turret rotation end-point maximum
    DeviceData.TurretRotation_Reversed = VarArray.value(1818).toUInt();                     // 1818 - Turret rotation motor reversed

    // Mechanical Barrel and Recoil Servo settings - 20xx
    DeviceData.Airsoft = VarArray.value(2011).toUInt();                                     // 2011 - Airsoft true/false
    DeviceData.MechanicalBarrelWithCannon = VarArray.value(2012).toUInt();                  // 2012 - Link mechanical barrel to cannon fire
    DeviceData.RecoilDelay = VarArray.value(2013).toInt();                                  // 2013 - Recoil delay (between physical recoil action, and flash/sound)
    DeviceData.RecoilReversed = VarArray.value(2014).toUInt();                              // 2014 - Recoil reversed
    DeviceData.ServoRecoilWithCannon = VarArray.value(2015).toUInt();                       // 2015 - Link servo recoil to cannon fire
    DeviceData.RecoilServo_Recoil_mS = VarArray.value(2016).toInt();                        // 2016 - Time in milliseconds for barrel to recoil
    DeviceData.RecoilServo_Return_mS = VarArray.value(2017).toInt();                        // 2017 - Time in milliseconds for barrel to return
    DeviceData.RecoilServo_EPMin = VarArray.value(2018).toInt();                            // 2018 - Recoil servo endpoint adjustments. Min will be recoiled position
    DeviceData.RecoilServo_EPMax = VarArray.value(2019).toInt();                            // 2019 - Max will be returned position

    // On board smoker output - 22xx
    DeviceData.SmokerControlAuto = VarArray.value(2211).toUInt();                           // 2211 - Smoker speed controlled by engine speed
    DeviceData.SmokerIdleSpeed = VarArray.value(2212).toInt();                              // 2212 - Smoker idle speed
    DeviceData.SmokerFastIdleSpeed = VarArray.value(2213).toInt();                          // 2213 - Smoker fast idle speed (when transmission disengaged)
    DeviceData.SmokerMaxSpeed = VarArray.value(2214).toInt();                               // 2214 - Max smoker speed
    DeviceData.SmokerDestroyedSpeed = VarArray.value(2215).toInt();                         // 2215 - Smoker speed when tank destroyed

    // Driving adjustments - 24xx
    DeviceData.AccelRampEnabled_1 = VarArray.value(2411).toUInt();                          // 2411 - Accel ramp enabled (profile 1)
    DeviceData.AccelSkipNum_1 = VarArray.value(2412).toUInt();                              // 2412 - Accel skip num (profile 1)
    DeviceData.AccelPreset_1 = VarArray.value(2413).toUInt();                               // 2413 - Accel preset (profile 1)
    DeviceData.DecelRampEnabled_1 = VarArray.value(2414).toUInt();                          // 2414 - Decel ramp enabled (profile 1)
    DeviceData.DecelSkipNum_1 = VarArray.value(2415).toUInt();                              // 2415 - Decel skip num (profile 1)
    DeviceData.DecelPreset_1 = VarArray.value(2416).toUInt();                               // 2416 - Decel preset (profile 1)
    DeviceData.AccelRampEnabled_2 = VarArray.value(2417).toUInt();                          // 2417 - Accel ramp enabled (profile 2)
    DeviceData.AccelSkipNum_2 = VarArray.value(2418).toUInt();                              // 2418 - Accel skip num (profile 2)
    DeviceData.AccelPreset_2 = VarArray.value(2419).toUInt();                               // 2419 - Accel preset (profile 2)
    DeviceData.DecelRampEnabled_2 = VarArray.value(2420).toUInt();                          // 2420 - Decel ramp enabled (profile 2)
    DeviceData.DecelSkipNum_2 = VarArray.value(2421).toUInt();                              // 2421 - Decel skip num (profile 2)
    DeviceData.DecelPreset_2 = VarArray.value(2422).toUInt();                               // 2422 - Decel preset (profile 2)
    DeviceData.BrakeSensitivityPct = VarArray.value(2423).toUInt();                         // 2423 - Brake sensitivity percent
    DeviceData.TimeToShift_mS = VarArray.value(2424).toUInt();                              // 2424 - Time to shift in milliseconds
    DeviceData.EnginePauseTime_mS = VarArray.value(2425).toUInt();                          // 2425 - Engine pause time
    DeviceData.TransmissionDelay_mS = VarArray.value(2426).toUInt();                        // 2426 - Transmission delay (length of time for engine startup sound)
    DeviceData.NeutralTurnAllowed = VarArray.value(2427).toUInt();                          // 2427 - Neutral turn
    DeviceData.NeutralTurnPct = VarArray.value(2428).toUInt();                              // 2428 - Neutral turn speed as percent of drive speed
    DeviceData.TurnMode = VarArray.value(2429).toUInt();                                    // 2429 - Turn mode
    DeviceData.DriveType = VarArray.value(2430).toUInt();                                   // 2430 - Drive type
    DeviceData.MaxForwardSpeedPct = VarArray.value(2431).toUInt();                          // 2431 - Max forward speed
    DeviceData.MaxReverseSpeedPct = VarArray.value(2432).toUInt();                          // 2432 - Max reverse speed
    DeviceData.HalftrackTreadTurnPct = VarArray.value(2433).toUInt();                       // 2433 - Pct of turn applied to halftrack treads
    DeviceData.EngineAutoStart = VarArray.value(2434).toUInt();                             // 2434 - Auto-start engine with throttle
    DeviceData.EngineAutoStopTime_mS = VarArray.value(2435).toInt();                        // 2435 - Auto-stop engine after idle time
    DeviceData.MotorNudgePct = VarArray.value(2436).toUInt();                               // 2436 - Motor nudge percent
    DeviceData.NudgeTime_mS = VarArray.value(2437).toUInt();                                // 2437 - Nudge time in milliseconds
    DeviceData.DragInnerTrack = VarArray.value(2438).toUInt();                              // 2438 - Drag inner track (OP Scout only)

    // "Physics" Settings - 25xx
    DeviceData.EnableBarrelStabilize = VarArray.value(2511).toUInt();                       // 2511 - Enable barrel stabilization
    DeviceData.BarrelSensitivity = VarArray.value(2512).toUInt();                           // 2512 - Barrel stabilization sensitivity
    DeviceData.EnableHillPhysics = VarArray.value(2513).toUInt();                           // 2513 - Enable "hill physics"
    DeviceData.HillSensitivity = VarArray.value(2514).toUInt();                             // 2514 - "Hill physics" sensitivity

    // Bosch BNO055 Settings - 26xx
    // THESE HAVE BEEN REMOVED FOR NOW
//    startVal = 2611;
//    for (int i=0; i<NUM_BNO055_OFFSET_REGISTERS; i++)
//    {
//        DeviceData.offsetData[i] = VarArray.value(startVal + i).toUInt();                   // 26xx - BNO055 offset data
//    }

    // Turret stick adjustments - 27xx
    DeviceData.IgnoreTurretDelay_mS = VarArray.value(2711).toInt();                         // 2711 - How long to ignore turret stick when first moved from center.

    // Sound settings - 28xx
    DeviceData.SoundDevice = VarArray.value(2811).toUInt();                                 // 2811 - Sound Device (Benedini TBS-Mini, etc...)
    DeviceData.Squeak1_MinInterval_mS = VarArray.value(2812).toUInt();                      // 2812 - Minimum length of time between Squeak 1 intervals
    DeviceData.Squeak1_MaxInterval_mS = VarArray.value(2813).toUInt();                      // 2813 - Maximum length of time between Squeak 1 intervals
    DeviceData.Squeak2_MinInterval_mS = VarArray.value(2814).toUInt();                      // 2814 - Minimum length of time between Squeak 2 intervals
    DeviceData.Squeak2_MaxInterval_mS = VarArray.value(2815).toUInt();                      // 2815 - Maximum length of time between Squeak 2 intervals
    DeviceData.Squeak3_MinInterval_mS = VarArray.value(2816).toUInt();                      // 2816 - Minimum length of time between Squeak 3 intervals
    DeviceData.Squeak3_MaxInterval_mS = VarArray.value(2817).toUInt();                      // 2817 - Maximum length of time between Squeak 3 intervals
    DeviceData.Squeak1_Enabled = VarArray.value(2818).toUInt();                             // 2818 - Squeak1 enabled or not
    DeviceData.Squeak2_Enabled = VarArray.value(2819).toUInt();                             // 2819 - Squeak2 enabled or not
    DeviceData.Squeak3_Enabled = VarArray.value(2820).toUInt();                             // 2820 - Squeak3 enabled or not
    DeviceData.MinSqueakSpeedPct = VarArray.value(2821).toUInt();                           // 2821 - Min vehicle movement before squeaks can begin
    DeviceData.HeadlightSound_Enabled = VarArray.value(2822).toUInt();                      // 2822 - Headlight sound enabled or not
    DeviceData.TurretSound_Enabled = VarArray.value(2823).toUInt();                         // 2823 - Turret rotation sound enabled or not
    DeviceData.BarrelSound_Enabled = VarArray.value(2824).toUInt();                         // 2824 - Barrel elevation sound enabled or not
    DeviceData.Squeak4_MinInterval_mS = VarArray.value(2825).toUInt();                      // 2825 - Minimum length of time between Squeak 4 intervals
    DeviceData.Squeak4_MaxInterval_mS = VarArray.value(2826).toUInt();                      // 2826 - Maximum length of time between Squeak 4 intervals
    DeviceData.Squeak5_MinInterval_mS = VarArray.value(2827).toUInt();                      // 2827 - Minimum length of time between Squeak 5 intervals
    DeviceData.Squeak5_MaxInterval_mS = VarArray.value(2828).toUInt();                      // 2828 - Maximum length of time between Squeak 5 intervals
    DeviceData.Squeak6_MinInterval_mS = VarArray.value(2829).toUInt();                      // 2829 - Minimum length of time between Squeak 6 intervals
    DeviceData.Squeak6_MaxInterval_mS = VarArray.value(2830).toUInt();                      // 2830 - Maximum length of time between Squeak 6 intervals
    DeviceData.Squeak4_Enabled = VarArray.value(2831).toUInt();                             // 2831 - Squeak4 enabled or not
    DeviceData.Squeak5_Enabled = VarArray.value(2832).toUInt();                             // 2832 - Squeak5 enabled or not
    DeviceData.Squeak6_Enabled = VarArray.value(2833).toUInt();                             // 2833 - Squeak6 enabled or not


    // Battle settings - 30xx
    DeviceData.IR_FireProtocol = VarArray.value(3011).toUInt();                             // 3011 - IR protocol to send when firing cannon
    DeviceData.IR_HitProtocol_2 = VarArray.value(3012).toUInt();                            // 3012 - Optional secondary IR protocol to receive hits from
    DeviceData.IR_RepairProtocol = VarArray.value(3013).toUInt();                           // 3013 - Repair protocol (same for sending/receiving)
    DeviceData.IR_MGProtocol = VarArray.value(3014).toUInt();                               // 3014 - Machine gun protocol (same for sending/receiving)
    DeviceData.Use_MG_Protocol = VarArray.value(3015).toUInt();                             // 3015 - Send MG code when firing MG
    DeviceData.Accept_MG_Damage = VarArray.value(3016).toUInt();                            // 3016 - susceptible to machine gun damage
    DeviceData.DamageProfile = VarArray.value(3017).toUInt();                               // 3017 - Damage profile
    DeviceData.CustomClassSettings.reloadTime = VarArray.value(3018).toUInt();              // 3018 - Custom weight class - reload time
    DeviceData.CustomClassSettings.recoveryTime = VarArray.value(3019).toUInt();            // 3019 - Custom weight class - recovery time
    DeviceData.CustomClassSettings.maxHits = VarArray.value(3020).toUInt();                 // 3020 - Custom weight class - max hits
    DeviceData.CustomClassSettings.maxMGHits = VarArray.value(3021).toUInt();               // 3021 - Custom weight class - max machine gun hits
    DeviceData.SendTankID = VarArray.value(3022).toUInt();                                  // 3022 - Send Tank ID with cannon fire IR transmission
    DeviceData.TankID = VarArray.value(3023).toUInt();                                      // 3023 - Tank ID number
    DeviceData.IR_Team = VarArray.value(3024).toUInt();                                     // 3024 - Team

    // Board settings - 32xx
    DeviceData.USBSerialBaud = VarArray.value(3211).toULong();                              // 3211 - Hardware Serial 0
    DeviceData.AuxSerialBaud = VarArray.value(3212).toULong();                              // 3212 - Hardware Serial 1
    DeviceData.MotorSerialBaud = VarArray.value(3213).toULong();                            // 3213 - Hardware Serial 2
    DeviceData.Serial3TxBaud = VarArray.value(3214).toULong();                              // 3214 - Hardware Serial 3
    DeviceData.LVC_Enabled = VarArray.value(3215).toUInt();                                 // 3215 - LVC enabled
    DeviceData.LVC_Cutoff_mV = VarArray.value(3216).toUInt();                               // 3216 - Low voltage cutoff in milliVolts

    // Light settings - 34xx
    DeviceData.RunningLightsAlwaysOn = VarArray.value(3411).toUInt();                       // 3411 - Running lights always on
    DeviceData.RunningLightsDimLevelPct = VarArray.value(3412).toUInt();                    // 3412 - Running lights dim level
    DeviceData.BrakesAutoOnAtStop = VarArray.value(3413).toUInt();                          // 3413 - Brake auto-on at stop
    DeviceData.AuxLightFlashTime_mS = VarArray.value(3414).toUInt();                        // 3414 - Aux light flash time
    DeviceData.AuxLightBlinkOnTime_mS = VarArray.value(3415).toUInt();                      // 3415 - Aux blinker on time
    DeviceData.AuxLightBlinkOffTime_mS = VarArray.value(3416).toUInt();                     // 3416 - Aux blinker off time
    DeviceData.AuxLightPresetDim = VarArray.value(3417).toUInt();                           // 3417 - Aux light preset dim level
    DeviceData.MGLightBlink_mS = VarArray.value(3418).toUInt();                             // 3418 - Machine gun blink interval
    DeviceData.FlashLightsWhenSignalLost = VarArray.value(3419).toUInt();                   // 3419 - Flash lights if radio signal lost
    DeviceData.HiFlashWithCannon = VarArray.value(3420).toUInt();                           // 3420 - Trigger high-intensity flash with cannon
    DeviceData.AuxFlashWithCannon = VarArray.value(3421).toUInt();                          // 3421 - Trigger aux light output with cannon

    // Program setting - 90xx
    DeviceData.PrintDebug = VarArray.value(9011).toUInt();                                  // 9011 - Debug
}


// Now we have a function to go the other way - save all named variables into the
// correct position in VarArray
void MainWindow::Variables_to_VarArray(void)
{
    // THIS IS ALL HARD-CODED. I DON'T REALLY KNOW A GOOD WAY TO AUTOMATE IT.
    // OBVIOUSLY IF YOU SCREW UP SOMETHING HERE, BAD NEWS

    // Recall, all values in VarArray are in QByteArray format. It has no idea of the variable type.
    // Therefore each variable must be converted to a QByteArray.

    // Linear Channel Settings - 10xx
    VarArray.insert(1011, QByteArray::number(DeviceData.Sticks.Throttle.Settings.channelNum));      // 1011 - Throttle channel number
    VarArray.insert(1012, QByteArray::number(DeviceData.Sticks.Throttle.Settings.pulseMin));        // 1012 - Throttle pulse min
    VarArray.insert(1013, QByteArray::number(DeviceData.Sticks.Throttle.Settings.pulseMax));        // 1013 - Throttle pulse max
    VarArray.insert(1014, QByteArray::number(DeviceData.Sticks.Throttle.Settings.pulseCenter));     // 1014 - Throttle pulse center
    VarArray.insert(1015, QByteArray::number(DeviceData.Sticks.Throttle.Settings.deadband));        // 1015 - Throttle deadband
    VarArray.insert(1016, QByteArray::number(DeviceData.Sticks.Throttle.Settings.reversed));        // 1016 - Throttle reversed

    VarArray.insert(1017, QByteArray::number(DeviceData.Sticks.Turn.Settings.channelNum));          // 1017 - Turn channel number
    VarArray.insert(1018, QByteArray::number(DeviceData.Sticks.Turn.Settings.pulseMin));            // 1018 - Turn pulse min
    VarArray.insert(1019, QByteArray::number(DeviceData.Sticks.Turn.Settings.pulseMax));            // 1019 - Turn pulse max
    VarArray.insert(1020, QByteArray::number(DeviceData.Sticks.Turn.Settings.pulseCenter));         // 1020 - Turn pulse center
    VarArray.insert(1021, QByteArray::number(DeviceData.Sticks.Turn.Settings.deadband));            // 1021 - Turn deadband
    VarArray.insert(1022, QByteArray::number(DeviceData.Sticks.Turn.Settings.reversed));            // 1022 - Turn reversed

    VarArray.insert(1023, QByteArray::number(DeviceData.Sticks.Elevation.Settings.channelNum));     // 1023 - Elevation channel number
    VarArray.insert(1024, QByteArray::number(DeviceData.Sticks.Elevation.Settings.pulseMin));       // 1024 - Elevation pulse min
    VarArray.insert(1025, QByteArray::number(DeviceData.Sticks.Elevation.Settings.pulseMax));       // 1025 - Elevation pulse max
    VarArray.insert(1026, QByteArray::number(DeviceData.Sticks.Elevation.Settings.pulseCenter));    // 1026 - Elevation pulse center
    VarArray.insert(1027, QByteArray::number(DeviceData.Sticks.Elevation.Settings.deadband));       // 1027 - Elevation deadband
    VarArray.insert(1028, QByteArray::number(DeviceData.Sticks.Elevation.Settings.reversed));       // 1028 - Elevation reversed

    VarArray.insert(1029, QByteArray::number(DeviceData.Sticks.Azimuth.Settings.channelNum));       // 1029 - Azimuth channel number
    VarArray.insert(1030, QByteArray::number(DeviceData.Sticks.Azimuth.Settings.pulseMin));         // 1030 - Azimuth pulse min
    VarArray.insert(1031, QByteArray::number(DeviceData.Sticks.Azimuth.Settings.pulseMax));         // 1031 - Azimuth pulse max
    VarArray.insert(1032, QByteArray::number(DeviceData.Sticks.Azimuth.Settings.pulseCenter));      // 1032 - Azimuth pulse center
    VarArray.insert(1033, QByteArray::number(DeviceData.Sticks.Azimuth.Settings.deadband));         // 1033 - Azimuth deadband
    VarArray.insert(1034, QByteArray::number(DeviceData.Sticks.Azimuth.Settings.reversed));         // 1034 - Azimuth reversed

    // Aux Channel Settings - 12xx
    VarArray.insert(1211, QByteArray::number(DeviceData.AuxChannel[0].Settings.channelNum));        // 1211 - Aux 1 channel number
    VarArray.insert(1212, QByteArray::number(DeviceData.AuxChannel[0].Settings.pulseMin));          // 1212 - Aux 1 pulse min
    VarArray.insert(1213, QByteArray::number(DeviceData.AuxChannel[0].Settings.pulseMax));          // 1213 - Aux 1 pulse max
    VarArray.insert(1214, QByteArray::number(DeviceData.AuxChannel[0].Settings.pulseCenter));       // 1214 - Aux 1 pulse center
    VarArray.insert(1215, QByteArray::number(DeviceData.AuxChannel[0].Settings.Digital));           // 1215 - Aux 1 digital
    VarArray.insert(1216, QByteArray::number(DeviceData.AuxChannel[0].Settings.numPositions));      // 1216 - Aux 1 number of switch positions (if digital)
    VarArray.insert(1217, QByteArray::number(DeviceData.AuxChannel[0].Settings.reversed));          // 1217 - Aux 1 reversed

    VarArray.insert(1218, QByteArray::number(DeviceData.AuxChannel[1].Settings.channelNum));        // 1218 - Aux 2 channel number
    VarArray.insert(1219, QByteArray::number(DeviceData.AuxChannel[1].Settings.pulseMin));          // 1219 - Aux 2 pulse min
    VarArray.insert(1220, QByteArray::number(DeviceData.AuxChannel[1].Settings.pulseMax));          // 1220 - Aux 2 pulse max
    VarArray.insert(1221, QByteArray::number(DeviceData.AuxChannel[1].Settings.pulseCenter));       // 1221 - Aux 2 pulse center
    VarArray.insert(1222, QByteArray::number(DeviceData.AuxChannel[1].Settings.Digital));           // 1222 - Aux 2 digital
    VarArray.insert(1223, QByteArray::number(DeviceData.AuxChannel[1].Settings.numPositions));      // 1223 - Aux 2 number of switch positions (if digital)
    VarArray.insert(1224, QByteArray::number(DeviceData.AuxChannel[1].Settings.reversed));          // 1224 - Aux 2 reversed

    VarArray.insert(1225, QByteArray::number(DeviceData.AuxChannel[2].Settings.channelNum));        // 1225 - Aux 3 channel number
    VarArray.insert(1226, QByteArray::number(DeviceData.AuxChannel[2].Settings.pulseMin));          // 1226 - Aux 3 pulse min
    VarArray.insert(1227, QByteArray::number(DeviceData.AuxChannel[2].Settings.pulseMax));          // 1227 - Aux 3 pulse max
    VarArray.insert(1228, QByteArray::number(DeviceData.AuxChannel[2].Settings.pulseCenter));       // 1228 - Aux 3 pulse center
    VarArray.insert(1229, QByteArray::number(DeviceData.AuxChannel[2].Settings.Digital));           // 1229 - Aux 3 digital
    VarArray.insert(1230, QByteArray::number(DeviceData.AuxChannel[2].Settings.numPositions));      // 1230 - Aux 3 number of switch positions (if digital)
    VarArray.insert(1231, QByteArray::number(DeviceData.AuxChannel[2].Settings.reversed));          // 1231 - Aux 3 reversed

    VarArray.insert(1232, QByteArray::number(DeviceData.AuxChannel[3].Settings.channelNum));        // 1232 - Aux 4 channel number
    VarArray.insert(1233, QByteArray::number(DeviceData.AuxChannel[3].Settings.pulseMin));          // 1233 - Aux 4 pulse min
    VarArray.insert(1234, QByteArray::number(DeviceData.AuxChannel[3].Settings.pulseMax));          // 1234 - Aux 4 pulse max
    VarArray.insert(1235, QByteArray::number(DeviceData.AuxChannel[3].Settings.pulseCenter));       // 1235 - Aux 4 pulse center
    VarArray.insert(1236, QByteArray::number(DeviceData.AuxChannel[3].Settings.Digital));           // 1236 - Aux 4 digital
    VarArray.insert(1237, QByteArray::number(DeviceData.AuxChannel[3].Settings.numPositions));      // 1237 - Aux 4 number of switch positions (if digital)
    VarArray.insert(1238, QByteArray::number(DeviceData.AuxChannel[3].Settings.reversed));          // 1238 - Aux 4 reversed

    VarArray.insert(1239, QByteArray::number(DeviceData.AuxChannel[4].Settings.channelNum));        // 1239 - Aux 5 channel number
    VarArray.insert(1240, QByteArray::number(DeviceData.AuxChannel[4].Settings.pulseMin));          // 1240 - Aux 5 pulse min
    VarArray.insert(1241, QByteArray::number(DeviceData.AuxChannel[4].Settings.pulseMax));          // 1241 - Aux 5 pulse max
    VarArray.insert(1242, QByteArray::number(DeviceData.AuxChannel[4].Settings.pulseCenter));       // 1242 - Aux 5 pulse center
    VarArray.insert(1243, QByteArray::number(DeviceData.AuxChannel[4].Settings.Digital));           // 1243 - Aux 5 digital
    VarArray.insert(1244, QByteArray::number(DeviceData.AuxChannel[4].Settings.numPositions));      // 1244 - Aux 5 number of switch positions (if digital)
    VarArray.insert(1245, QByteArray::number(DeviceData.AuxChannel[4].Settings.reversed));          // 1245 - Aux 5 reversed

    VarArray.insert(1246, QByteArray::number(DeviceData.AuxChannel[5].Settings.channelNum));        // 1246 - Aux 6 channel number
    VarArray.insert(1247, QByteArray::number(DeviceData.AuxChannel[5].Settings.pulseMin));          // 1247 - Aux 6 pulse min
    VarArray.insert(1248, QByteArray::number(DeviceData.AuxChannel[5].Settings.pulseMax));          // 1248 - Aux 6 pulse max
    VarArray.insert(1249, QByteArray::number(DeviceData.AuxChannel[5].Settings.pulseCenter));       // 1249 - Aux 6 pulse center
    VarArray.insert(1250, QByteArray::number(DeviceData.AuxChannel[5].Settings.Digital));           // 1250 - Aux 6 digital
    VarArray.insert(1251, QByteArray::number(DeviceData.AuxChannel[5].Settings.numPositions));      // 1251 - Aux 6 number of switch positions (if digital)
    VarArray.insert(1252, QByteArray::number(DeviceData.AuxChannel[5].Settings.reversed));          // 1252 - Aux 6 reversed

    VarArray.insert(1253, QByteArray::number(DeviceData.AuxChannel[6].Settings.channelNum));        // 1253 - Aux 7 channel number
    VarArray.insert(1254, QByteArray::number(DeviceData.AuxChannel[6].Settings.pulseMin));          // 1254 - Aux 7 pulse min
    VarArray.insert(1255, QByteArray::number(DeviceData.AuxChannel[6].Settings.pulseMax));          // 1255 - Aux 7 pulse max
    VarArray.insert(1256, QByteArray::number(DeviceData.AuxChannel[6].Settings.pulseCenter));       // 1256 - Aux 7 pulse center
    VarArray.insert(1257, QByteArray::number(DeviceData.AuxChannel[6].Settings.Digital));           // 1257 - Aux 7 digital
    VarArray.insert(1258, QByteArray::number(DeviceData.AuxChannel[6].Settings.numPositions));      // 1258 - Aux 7 number of switch positions (if digital)
    VarArray.insert(1259, QByteArray::number(DeviceData.AuxChannel[6].Settings.reversed));          // 1259 - Aux 7 reversed

    VarArray.insert(1260, QByteArray::number(DeviceData.AuxChannel[7].Settings.channelNum));        // 1260 - Aux 8 channel number
    VarArray.insert(1261, QByteArray::number(DeviceData.AuxChannel[7].Settings.pulseMin));          // 1261 - Aux 8 pulse min
    VarArray.insert(1262, QByteArray::number(DeviceData.AuxChannel[7].Settings.pulseMax));          // 1262 - Aux 8 pulse max
    VarArray.insert(1263, QByteArray::number(DeviceData.AuxChannel[7].Settings.pulseCenter));       // 1263 - Aux 8 pulse center
    VarArray.insert(1264, QByteArray::number(DeviceData.AuxChannel[7].Settings.Digital));           // 1264 - Aux 8 digital
    VarArray.insert(1265, QByteArray::number(DeviceData.AuxChannel[7].Settings.numPositions));      // 1265 - Aux 8 number of switch positions (if digital)
    VarArray.insert(1266, QByteArray::number(DeviceData.AuxChannel[7].Settings.reversed));          // 1266 - Aux 8 reversed

    VarArray.insert(1267, QByteArray::number(DeviceData.AuxChannel[8].Settings.channelNum));        // 1267 - Aux 9 channel number
    VarArray.insert(1268, QByteArray::number(DeviceData.AuxChannel[8].Settings.pulseMin));          // 1268 - Aux 9 pulse min
    VarArray.insert(1269, QByteArray::number(DeviceData.AuxChannel[8].Settings.pulseMax));          // 1269 - Aux 9 pulse max
    VarArray.insert(1270, QByteArray::number(DeviceData.AuxChannel[8].Settings.pulseCenter));       // 1270 - Aux 9 pulse center
    VarArray.insert(1271, QByteArray::number(DeviceData.AuxChannel[8].Settings.Digital));           // 1271 - Aux 9 digital
    VarArray.insert(1272, QByteArray::number(DeviceData.AuxChannel[8].Settings.numPositions));      // 1272 - Aux 9 number of switch positions (if digital)
    VarArray.insert(1273, QByteArray::number(DeviceData.AuxChannel[8].Settings.reversed));          // 1273 - Aux 9 reversed

    VarArray.insert(1274, QByteArray::number(DeviceData.AuxChannel[9].Settings.channelNum));        // 1274 - Aux 10 channel number
    VarArray.insert(1275, QByteArray::number(DeviceData.AuxChannel[9].Settings.pulseMin));          // 1275 - Aux 10 pulse min
    VarArray.insert(1276, QByteArray::number(DeviceData.AuxChannel[9].Settings.pulseMax));          // 1276 - Aux 10 pulse max
    VarArray.insert(1277, QByteArray::number(DeviceData.AuxChannel[9].Settings.pulseCenter));       // 1277 - Aux 10 pulse center
    VarArray.insert(1278, QByteArray::number(DeviceData.AuxChannel[9].Settings.Digital));           // 1278 - Aux 10 digital
    VarArray.insert(1279, QByteArray::number(DeviceData.AuxChannel[9].Settings.numPositions));      // 1279 - Aux 10 number of switch positions (if digital)
    VarArray.insert(1280, QByteArray::number(DeviceData.AuxChannel[9].Settings.reversed));          // 1280 - Aux 10 reversed

    VarArray.insert(1281, QByteArray::number(DeviceData.AuxChannel[10].Settings.channelNum));       // 1281 - Aux 11 channel number
    VarArray.insert(1282, QByteArray::number(DeviceData.AuxChannel[10].Settings.pulseMin));         // 1282 - Aux 11 pulse min
    VarArray.insert(1283, QByteArray::number(DeviceData.AuxChannel[10].Settings.pulseMax));         // 1283 - Aux 11 pulse max
    VarArray.insert(1284, QByteArray::number(DeviceData.AuxChannel[10].Settings.pulseCenter));      // 1284 - Aux 11 pulse center
    VarArray.insert(1285, QByteArray::number(DeviceData.AuxChannel[10].Settings.Digital));          // 1285 - Aux 11 digital
    VarArray.insert(1286, QByteArray::number(DeviceData.AuxChannel[10].Settings.numPositions));     // 1286 - Aux 11 number of switch positions (if digital)
    VarArray.insert(1287, QByteArray::number(DeviceData.AuxChannel[10].Settings.reversed));         // 1287 - Aux 11 reversed

    VarArray.insert(1288, QByteArray::number(DeviceData.AuxChannel[11].Settings.channelNum));       // 1288 - Aux 12 channel number
    VarArray.insert(1289, QByteArray::number(DeviceData.AuxChannel[11].Settings.pulseMin));         // 1289 - Aux 12 pulse min
    VarArray.insert(1290, QByteArray::number(DeviceData.AuxChannel[11].Settings.pulseMax));         // 1290 - Aux 12 pulse max
    VarArray.insert(1291, QByteArray::number(DeviceData.AuxChannel[11].Settings.pulseCenter));      // 1291 - Aux 12 pulse center
    VarArray.insert(1292, QByteArray::number(DeviceData.AuxChannel[11].Settings.Digital));          // 1292 - Aux 12 digital
    VarArray.insert(1293, QByteArray::number(DeviceData.AuxChannel[11].Settings.numPositions));     // 1293 - Aux 12 number of switch positions (if digital)
    VarArray.insert(1294, QByteArray::number(DeviceData.AuxChannel[11].Settings.reversed));         // 1294 - Aux 12 reversed

    // External I/O Ports
    VarArray.insert(1311, QByteArray::number(DeviceData.PortA.Settings.dataDirection));             // 1311 - PortA data direction
    VarArray.insert(1312, QByteArray::number(DeviceData.PortA.Settings.dataType));                  // 1312 - PortA digital true/false if input, normally high/low if output
    VarArray.insert(1313, QByteArray::number(DeviceData.PortB.Settings.dataDirection));             // 1313 - PortB data direction
    VarArray.insert(1314, QByteArray::number(DeviceData.PortB.Settings.dataType));                  // 1314 - PortB digital true/false if input, normally high/low if output

    // Special Function Triggers - 14xx
    int j = 0;
    int startVal = 1411;
    for (int i=0; i<MAX_FUNCTION_TRIGGERS; i++)
    {
        VarArray.insert(startVal + j, QByteArray::number(DeviceData.SF_Trigger[i].TriggerID));           // 14xx - Special Function trigger i
        VarArray.insert(startVal + j + 1, QByteArray::number(DeviceData.SF_Trigger[i].specialFunction)); // 14xx - Special Function function i
        j += 2;
    }

    // Motor Drive Types - 16xx
    VarArray.insert(1611, QByteArray::number(DeviceData.DriveMotors));                              // 1611 - Drive motor type
    VarArray.insert(1612, QByteArray::number(DeviceData.TurretRotationMotor));                      // 1612 - Turret rotation motor type
    VarArray.insert(1613, QByteArray::number(DeviceData.TurretElevationMotor));                     // 1613 - Turret elevation motor type

    // Elevation Motor settings - 18xx
    VarArray.insert(1811, QByteArray::number(DeviceData.TurretElevation_EPMin));                    // 1811 - Turret elevation end-point minimum
    VarArray.insert(1812, QByteArray::number(DeviceData.TurretElevation_EPMax));                    // 1812 - Turret elevation end-point maximum
    VarArray.insert(1813, QByteArray::number(DeviceData.TurretElevation_Reversed));                 // 1813 - Turret elevation motor reversed
    VarArray.insert(1814, QByteArray::number(DeviceData.TurretElevation_MaxSpeedPct));              // 1814 - Barrel elevation motor speed as percent of maximum
    VarArray.insert(1815, QByteArray::number(DeviceData.TurretRotation_MaxSpeedPct));               // 1815 - Turret rotation motor speed as percent of maximum
    VarArray.insert(1816, QByteArray::number(DeviceData.TurretRotation_EPMin));                     // 1816 - Turret rotation end-point minimum
    VarArray.insert(1817, QByteArray::number(DeviceData.TurretRotation_EPMax));                     // 1817 - Turret rotation end-point maximum
    VarArray.insert(1818, QByteArray::number(DeviceData.TurretRotation_Reversed));                  // 1818 - Turret rotation motor reversed

    // Mechanical Barrel and Recoil Servo settings - 20xx
    VarArray.insert(2011, QByteArray::number(DeviceData.Airsoft));                                  // 2011 - Airsoft true/false
    VarArray.insert(2012, QByteArray::number(DeviceData.MechanicalBarrelWithCannon));               // 2012 - Link mechanical barrel to cannon fire
    VarArray.insert(2013, QByteArray::number(DeviceData.RecoilDelay));                              // 2013 - Recoil delay (between physical recoil action, and flash/sound)
    VarArray.insert(2014, QByteArray::number(DeviceData.RecoilReversed));                           // 2014 - Recoil reversed
    VarArray.insert(2015, QByteArray::number(DeviceData.ServoRecoilWithCannon));                    // 2015 - Link recoil servo to cannon fire
    VarArray.insert(2016, QByteArray::number(DeviceData.RecoilServo_Recoil_mS));                    // 2016 - Time in milliseconds for barrel to recoil
    VarArray.insert(2017, QByteArray::number(DeviceData.RecoilServo_Return_mS));                    // 2017 - Time in milliseconds for barrel to return
    VarArray.insert(2018, QByteArray::number(DeviceData.RecoilServo_EPMin));                        // 2018 - Recoil servo endpoint adjustments. Min will be recoiled position
    VarArray.insert(2019, QByteArray::number(DeviceData.RecoilServo_EPMax));                        // 2019 - Max will be returned position

    // On board smoker output - 22xx
    VarArray.insert(2211, QByteArray::number(DeviceData.SmokerControlAuto));                        // 2211 - Smoker controlled by engine speed
    VarArray.insert(2212, QByteArray::number(DeviceData.SmokerIdleSpeed));                          // 2212 - Smoker idle speed
    VarArray.insert(2213, QByteArray::number(DeviceData.SmokerFastIdleSpeed));                      // 2213 - Smoker fast idle speed (when transmission disengaged)
    VarArray.insert(2214, QByteArray::number(DeviceData.SmokerMaxSpeed));                           // 2214 - Max smoker speed
    VarArray.insert(2215, QByteArray::number(DeviceData.SmokerDestroyedSpeed));                     // 2215 - Smoker speed when tank destroyed

    // Driving adjustments - 24xx
    VarArray.insert(2411, QByteArray::number(DeviceData.AccelRampEnabled_1));                       // 2411 - Accel ramp enabled (profile 1)
    VarArray.insert(2412, QByteArray::number(DeviceData.AccelSkipNum_1));                           // 2412 - Accel skip num (profile 1)
    VarArray.insert(2413, QByteArray::number(DeviceData.AccelPreset_1));                            // 2413 - Accel preset (profile 1)
    VarArray.insert(2414, QByteArray::number(DeviceData.DecelRampEnabled_1));                       // 2414 - Decel ramp enabled (profile 1)
    VarArray.insert(2415, QByteArray::number(DeviceData.DecelSkipNum_1));                           // 2415 - Decel skip num (profile 1)
    VarArray.insert(2416, QByteArray::number(DeviceData.DecelPreset_1));                            // 2416 - Decel preset (profile 1)
    VarArray.insert(2417, QByteArray::number(DeviceData.AccelRampEnabled_2));                       // 2417 - Accel ramp enabled (profile 2)
    VarArray.insert(2418, QByteArray::number(DeviceData.AccelSkipNum_2));                           // 2418 - Accel skip num (profile 2)
    VarArray.insert(2419, QByteArray::number(DeviceData.AccelPreset_2));                            // 2419 - Accel preset (profile 2)
    VarArray.insert(2420, QByteArray::number(DeviceData.DecelRampEnabled_2));                       // 2420 - Decel ramp enabled (profile 2)
    VarArray.insert(2421, QByteArray::number(DeviceData.DecelSkipNum_2));                           // 2421 - Decel skip num (profile 2)
    VarArray.insert(2422, QByteArray::number(DeviceData.DecelPreset_2));                            // 2422 - Decel preset (profile 2)
    VarArray.insert(2423, QByteArray::number(DeviceData.BrakeSensitivityPct));                      // 2423 - Brake sensitivity percent
    VarArray.insert(2424, QByteArray::number(DeviceData.TimeToShift_mS));                           // 2424 - Time to shift in milliseconds
    VarArray.insert(2425, QByteArray::number(DeviceData.EnginePauseTime_mS));                       // 2425 - Engine pause time
    VarArray.insert(2426, QByteArray::number(DeviceData.TransmissionDelay_mS));                     // 2426 - Transmission delay (length of time for engine startup sound)
    VarArray.insert(2427, QByteArray::number(DeviceData.NeutralTurnAllowed));                       // 2427 - Neutral turn
    VarArray.insert(2428, QByteArray::number(DeviceData.NeutralTurnPct));                           // 2428 - Neutral turn speed as percent of drive speed
    VarArray.insert(2429, QByteArray::number(DeviceData.TurnMode));                                 // 2429 - Turn mode
    VarArray.insert(2430, QByteArray::number(DeviceData.DriveType));                                // 2430 - Drive type
    VarArray.insert(2431, QByteArray::number(DeviceData.MaxForwardSpeedPct));                       // 2431 - Max forward speed
    VarArray.insert(2432, QByteArray::number(DeviceData.MaxReverseSpeedPct));                       // 2432 - Max reverse speed
    VarArray.insert(2433, QByteArray::number(DeviceData.HalftrackTreadTurnPct));                    // 2433 - Pct of turn applied to halftrack treads
    VarArray.insert(2434, QByteArray::number(DeviceData.EngineAutoStart));                          // 2434 - Auto-start engine with throttle
    VarArray.insert(2435, QByteArray::number(DeviceData.EngineAutoStopTime_mS));                    // 2435 - Auto-stop engine after idle time
    VarArray.insert(2436, QByteArray::number(DeviceData.MotorNudgePct));                            // 2436 - Motor nudge percent
    VarArray.insert(2437, QByteArray::number(DeviceData.NudgeTime_mS));                             // 2437 - Nudge time in milliseconds
    VarArray.insert(2438, QByteArray::number(DeviceData.DragInnerTrack));                           // 2438 - Drag inner track (OP Scout only)

    // Accelerometer Settings - 25xx
    VarArray.insert(2511, QByteArray::number(DeviceData.EnableBarrelStabilize));                    // 2511 - Enable barrel stabilization
    VarArray.insert(2512, QByteArray::number(DeviceData.BarrelSensitivity));                        // 2512 - Barrel stabilization sensitivity
    VarArray.insert(2513, QByteArray::number(DeviceData.EnableHillPhysics));                        // 2513 - Enable "hill physics"
    VarArray.insert(2514, QByteArray::number(DeviceData.HillSensitivity));                          // 2514 - "Hill physics" sensitivity

    // Bosch BNO055 Settings - 26xx
    // THESE HAVE BEEN REMOVED FOR NOW
//    startVal = 2611;
//    for (int i=0; i<NUM_BNO055_OFFSET_REGISTERS; i++)
//    {
//        VarArray.insert(startVal + i, QByteArray::number(DeviceData.offsetData[i]));                // 26xx - BNO055 offset data
//    }

    // Turret stick adjustments - 27xx
    VarArray.insert(2711, QByteArray::number(DeviceData.IgnoreTurretDelay_mS));                     // 2711 - How long to ignore turret stick when first moved from center.

    // Sound settings - 28xx
    VarArray.insert(2811, QByteArray::number(DeviceData.SoundDevice));                              // 2811 - Sound Device (Benedini TBS-Mini, etc...)
    VarArray.insert(2812, QByteArray::number(DeviceData.Squeak1_MinInterval_mS));                   // 2812 - Minimum length of time between Squeak 1 intervals
    VarArray.insert(2813, QByteArray::number(DeviceData.Squeak1_MaxInterval_mS));                   // 2813 - Maximum length of time between Squeak 1 intervals
    VarArray.insert(2814, QByteArray::number(DeviceData.Squeak2_MinInterval_mS));                   // 2814 - Minimum length of time between Squeak 2 intervals
    VarArray.insert(2815, QByteArray::number(DeviceData.Squeak2_MaxInterval_mS));                   // 2815 - Maximum length of time between Squeak 2 intervals
    VarArray.insert(2816, QByteArray::number(DeviceData.Squeak3_MinInterval_mS));                   // 2816 - Minimum length of time between Squeak 3 intervals
    VarArray.insert(2817, QByteArray::number(DeviceData.Squeak3_MaxInterval_mS));                   // 2817 - Maximum length of time between Squeak 3 intervals
    VarArray.insert(2818, QByteArray::number(DeviceData.Squeak1_Enabled));                          // 2818 - Squeak1 enabled or not
    VarArray.insert(2819, QByteArray::number(DeviceData.Squeak2_Enabled));                          // 2819 - Squeak2 enabled or not
    VarArray.insert(2820, QByteArray::number(DeviceData.Squeak3_Enabled));                          // 2820 - Squeak3 enabled or not
    VarArray.insert(2821, QByteArray::number(DeviceData.MinSqueakSpeedPct));                        // 2821 - Min vehicle movement before squeaks can begin
    VarArray.insert(2822, QByteArray::number(DeviceData.HeadlightSound_Enabled));                   // 2822 - Headlight sound enabled or not
    VarArray.insert(2823, QByteArray::number(DeviceData.TurretSound_Enabled));                      // 2823 - Turret rotation sound enabled or not
    VarArray.insert(2824, QByteArray::number(DeviceData.BarrelSound_Enabled));                      // 2824 - Barrel elevation sound enabled or not
    VarArray.insert(2825, QByteArray::number(DeviceData.Squeak4_MinInterval_mS));                   // 2825 - Minimum length of time between Squeak 4 intervals
    VarArray.insert(2826, QByteArray::number(DeviceData.Squeak4_MaxInterval_mS));                   // 2826 - Maximum length of time between Squeak 4 intervals
    VarArray.insert(2827, QByteArray::number(DeviceData.Squeak5_MinInterval_mS));                   // 2827 - Minimum length of time between Squeak 5 intervals
    VarArray.insert(2828, QByteArray::number(DeviceData.Squeak5_MaxInterval_mS));                   // 2828 - Maximum length of time between Squeak 5 intervals
    VarArray.insert(2829, QByteArray::number(DeviceData.Squeak6_MinInterval_mS));                   // 2829 - Minimum length of time between Squeak 6 intervals
    VarArray.insert(2830, QByteArray::number(DeviceData.Squeak6_MaxInterval_mS));                   // 2830 - Maximum length of time between Squeak 6 intervals
    VarArray.insert(2831, QByteArray::number(DeviceData.Squeak4_Enabled));                          // 2831 - Squeak4 enabled or not
    VarArray.insert(2832, QByteArray::number(DeviceData.Squeak5_Enabled));                          // 2832 - Squeak5 enabled or not
    VarArray.insert(2833, QByteArray::number(DeviceData.Squeak6_Enabled));                          // 2833 - Squeak6 enabled or not

    // Battle settings - 30xx
    VarArray.insert(3011, QByteArray::number(DeviceData.IR_FireProtocol));                          // 3011 - IR protocol to send when firing cannon
    VarArray.insert(3012, QByteArray::number(DeviceData.IR_HitProtocol_2));                         // 3012 - Optional secondary IR protocol to receive hits from
    VarArray.insert(3013, QByteArray::number(DeviceData.IR_RepairProtocol));                        // 3013 - Repair protocol (same for sending/receiving)
    VarArray.insert(3014, QByteArray::number(DeviceData.IR_MGProtocol));                            // 3014 - Machine gun protocol (same for sending/receiving)
    VarArray.insert(3015, QByteArray::number(DeviceData.Use_MG_Protocol));                          // 3015 - Send MG code when firing MG
    VarArray.insert(3016, QByteArray::number(DeviceData.Accept_MG_Damage));                         // 3016 - susceptible to machine gun damage
    VarArray.insert(3017, QByteArray::number(DeviceData.DamageProfile));                            // 3017 - Damage profile
    VarArray.insert(3018, QByteArray::number(DeviceData.CustomClassSettings.reloadTime));           // 3018 - Custom weight class - reload time
    VarArray.insert(3019, QByteArray::number(DeviceData.CustomClassSettings.recoveryTime));         // 3019 - Custom weight class - recovery time
    VarArray.insert(3020, QByteArray::number(DeviceData.CustomClassSettings.maxHits));              // 3020 - Custom weight class - max hits
    VarArray.insert(3021, QByteArray::number(DeviceData.CustomClassSettings.maxMGHits));            // 3021 - Custom weight class - max machine gun hits
    VarArray.insert(3022, QByteArray::number(DeviceData.SendTankID));                               // 3022 - Send Tank ID with cannon fire IR transmission
    VarArray.insert(3023, QByteArray::number(DeviceData.TankID));                                   // 3023 - Tank ID number
    VarArray.insert(3024, QByteArray::number(DeviceData.IR_Team));                                  // 3024 - Team

    // Board settings - 32xx
    VarArray.insert(3211, QByteArray::number(DeviceData.USBSerialBaud));                            // 3211 - Hardware Serial 0
    VarArray.insert(3212, QByteArray::number(DeviceData.AuxSerialBaud));                            // 3212 - Hardware Serial 1
    VarArray.insert(3213, QByteArray::number(DeviceData.MotorSerialBaud));                          // 3213 - Hardware Serial 2
    VarArray.insert(3214, QByteArray::number(DeviceData.Serial3TxBaud));                            // 3214 - Hardware Serial 3
    VarArray.insert(3215, QByteArray::number(DeviceData.LVC_Enabled));                              // 3215 - LVC enabled
    VarArray.insert(3216, QByteArray::number(DeviceData.LVC_Cutoff_mV));                            // 3216 - Low voltage cutoff in milliVolts

    // Light settings - 34xx
    VarArray.insert(3411, QByteArray::number(DeviceData.RunningLightsAlwaysOn));                    // 3411 - Running lights always on
    VarArray.insert(3412, QByteArray::number(DeviceData.RunningLightsDimLevelPct));                 // 3412 - Running lights dim level
    VarArray.insert(3413, QByteArray::number(DeviceData.BrakesAutoOnAtStop));                       // 3413 - Brake auto-on at stop
    VarArray.insert(3414, QByteArray::number(DeviceData.AuxLightFlashTime_mS));                     // 3414 - Aux light Flash time
    VarArray.insert(3415, QByteArray::number(DeviceData.AuxLightBlinkOnTime_mS));                   // 3415 - Aux blinker on time
    VarArray.insert(3416, QByteArray::number(DeviceData.AuxLightBlinkOffTime_mS));                  // 3416 - Aux blinker off time
    VarArray.insert(3417, QByteArray::number(DeviceData.AuxLightPresetDim));                        // 3417 - Aux light preset dim level
    VarArray.insert(3418, QByteArray::number(DeviceData.MGLightBlink_mS));                          // 3418 - Machine gun blink interval
    VarArray.insert(3419, QByteArray::number(DeviceData.FlashLightsWhenSignalLost));                // 3419 - Flash lights if radio signal lost
    VarArray.insert(3420, QByteArray::number(DeviceData.HiFlashWithCannon));                        // 3420 - Trigger high-intensity flash with cannon
    VarArray.insert(3421, QByteArray::number(DeviceData.AuxFlashWithCannon));                       // 3421 - Trigger aux light output with cannon

    // Program setting - 90xx
    VarArray.insert(9011, QByteArray::number(DeviceData.PrintDebug));                                // 9011 - Debug
}


//------------------------------------------------------------------------------------------------------------------------>>
// ARRAY - SEARCHING AND OTHER HANDLING
//------------------------------------------------------------------------------------------------------------------------>>
void MainWindow::loadVarArrayDefaults(void)
{
    VarArray.clear();

    for (int i=0; i<NUM_STORED_VARS; i++)
    {
        VarArray.insert(STORAGEVARS[i].varID, STORAGEVARS[i].defaultValue);
    }
}
boolean MainWindow::updateVarArray_byID(uint16_t findID, QByteArray value)
{
    // We don't have to search for the position in the map, just give it the key
    // and it will figure it out.
    if (VarArray.contains(findID))
    {
        VarArray.insert(findID, value);    // Using insert on an existing key will replace that key's value
        return true;
    }
    else
    {
        return false;
    }
}
boolean MainWindow::getStorageVarInfo_byID(_storage_var_info &svi, uint16_t findID)
{
    uint16_t arrayPos = 0;

    // If found, fill in the _storage_var struct that was passed
    arrayPos = findStorageArrayPosition(findID);
    if (arrayPos > 0)
    {
        svi.varOffset = STORAGEVARS[arrayPos].varOffset;
        svi.varType = STORAGEVARS[arrayPos].varType;
        svi.defaultValue = STORAGEVARS[arrayPos].defaultValue;
        return true;
    }
    else
    {
        return false;
    }
}
boolean MainWindow::getStorageVarInfo_byPos(_storage_var_info &svi, uint16_t arrayPos)
{
    if (arrayPos > 0 && arrayPos <= NUM_STORED_VARS)
    {
        svi.varOffset = (STORAGEVARS[arrayPos].varOffset);
        svi.varType = (STORAGEVARS[arrayPos].varType);
        svi.defaultValue = STORAGEVARS[arrayPos].defaultValue;
        return true;
    }
    else
    {
        return false;
    }
}
uint16_t MainWindow::findStorageArrayPosition(uint16_t findID)
{
    static uint16_t lastArrayPos = 0;
    int i;
    boolean found = false;

    // Start searching from the position after the last one we found
    for (i=(lastArrayPos+1); i<=NUM_STORED_VARS; i++)
    {
        if (findID == (STORAGEVARS[i].varID))
        {
            found = true;
            break;
        }
    }

    // If that didn't find it, wrap around back to the beginning and
    // search the first half too. Position 0 doesn't count.
    if (!found)
    {
        for (i=1; i<=lastArrayPos; i++)
        {
            if (findID == (STORAGEVARS[i].varID))
            {
                found = true;
                break;
            }
        }
    }

    // If found return the array position
    if (found)
    {
        return i;
    }
    else
    {
        // If not found, return 0
        return 0;
    }
}


