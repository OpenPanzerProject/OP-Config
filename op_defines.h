#ifndef OP_DEFINES
#define OP_DEFINES

#include <arduino_compat.h>

//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
// DEVICES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
typedef unsigned char DEVICE;           // Devices that we can program using OP Config
#define DEVICE_UNKNOWN      0
#define DEVICE_TCB_MKI      1
#define DEVICE_TCB_MKII     2
#define DEVICE_TCB_DIY      3           // DIY version of the TCB firmware, moves a few pins around for compatibility with stock Arduino MEGA boards
#define DEVICE_SCOUT        4           // Scout board versions R11 and later
#define DEVICE_SCOUT_R10    5           // Scout board versions R10 and earlier
#define DEVICE_TEENSYSOUND  6
#define DEVICE_ATMEGA328    7           // For generic Arduino 328 devices
#define DEVICE_TEENSY32     8           // For generic Teensy 3.2 devices
#define DEVICE_AT_MKI       9
#define DEVICE_HECLO_SHIELD 10
#define DEVICE_ATMEGA2560   11          // For generic ATmega2560 devices

// Not very sophisticated. Here we store the URLs to the latest release hex and version files, and we
// assume the URLs and filenames will never change in a million years.
// TCB firmware
#define LATEST_RELEASE_VERSION_URL_TCB          "http://openpanzer.org/downloads/tcbmk1/firmware/version.txt"
#define LATEST_RELEASE_HEX_URL_TCB              "http://openpanzer.org/downloads/tcbmk1/firmware/tcbmk1.hex"
#define LATEST_RELEASE_HEX_URL_TCB_DIY          "http://openpanzer.org/downloads/tcbmk1/firmware/tcbmk1_diy.hex"

// TCB Heclo Shield firmware
#define LATEST_RELEASE_VERSION_URL_HECLO_SHIELD "http://openpanzer.org/downloads/members/hecloshield/firmware/version.txt"
#define LATEST_RELEASE_HEX_URL_HECLO_SHIELD     "http://openpanzer.org/downloads/members/hecloshield/firmware/hecloshield.hex"

// TCB MkII firmware
#define LATEST_RELEASE_VERSION_URL_TCB_MKII     "http://openpanzer.org/downloads/tcbmk2/firmware/version.txt"
#define LATEST_RELEASE_HEX_URL_TCB_MKII         "http://openpanzer.org/downloads/tcbmk2/firmware/tcbmk2.hex"

// Armortek MkI firmware
#define LATEST_RELEASE_VERSION_URL_AT_MKI       "http://openpanzer.org/downloads/atmk1/firmware/version.txt"
#define LATEST_RELEASE_HEX_URL_AT_MKI           "http://openpanzer.org/downloads/atmk1/firmware/atmk1.hex"

// Scout firmware for Rev 11 boards and later (VNH5019 motor driver chips)
#define LATEST_RELEASE_VERSION_URL_SCOUT        "http://openpanzer.org/downloads/scout/firmware/version.txt"
#define LATEST_RELEASE_HEX_URL_SCOUT            "http://openpanzer.org/downloads/scout/firmware/opscout.hex"

// Scout firmware for Rev 10 boards and earlier (VNH2SP30 motor driver chips)
#define LATEST_RELEASE_VERSION_URL_SCOUT_R10    "http://openpanzer.org/downloads/scout/firmware_r10/version.txt"
#define LATEST_RELEASE_HEX_URL_SCOUT_R10        "http://openpanzer.org/downloads/scout/firmware_r10/opscout_rev10.hex"

// Sound card firmware
#define LATEST_RELEASE_VERSION_URL_TEENSYSOUND  "http://openpanzer.org/downloads/soundcard/firmware/version.txt"
#define LATEST_RELEASE_HEX_URL_TEENSYSOUND      "http://openpanzer.org/downloads/soundcard/firmware/opsound.hex"



//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
// GENERAL
// From OP_Config.h
//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
#define DEFAULTBAUDRATE				 38400  // This is NOT the default baud rate for USB coms, but for all the other serial ports
#define MOTOR_MAX_FWDSPEED 	     	 255
#define MOTOR_MAX_REVSPEED  		-255
#define MOTOR_MAX_FWDSPEED_DBL     	 255.0
#define MOTOR_MAX_REVSPEED_DBL 		-255.0

#define SERVONUM_LEFTTREAD			1	// This is the left-most servo output on the board, looking from the top. Servo 1 on the TCB board
#define SERVONUM_RIGHTTREAD			2	// Servo 2 is right tread
#define SERVONUM_TURRETROTATION		3	// Servo 3 is turret rotation
#define SERVONUM_TURRETELEVATION	4	// Servo 4 is turret elevation

//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
// DRIVING
// From OP_Driver.h
//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
typedef char DRIVETYPE;
#define DT_UNKNOWN		0
#define DT_TANK		 	1
#define DT_HALFTRACK	2
#define DT_CAR			3
#define DT_DKLM         4           // For the unusual DKLM gearboxes that use a single motor for propulsion and a second motor for steering. Basically same as a car, but we give it a unique drive type.
#define DT_DMD          5           // For the Tamiya DMD integrated ESCs and mixer units
#define DT_DIRECT		6			// Direct drive of each tread using individual radio channels
#define LAST_DT         DT_DIRECT

#define NUM_TURN_MODES			3	// How many turn modes are configured
#define MAX_SKIP_NUM 			14  // What is the max accel/decel level (14 = 7 seconds - is that slow enough?)

// Accel/decel presets
typedef char ACCEL_DRIVE_PRESET;
#define ADP_NONE        0				// This preset does nothing. The constraint is set by the user-selected level (skip num)
#define ADP_PRESET_1    1				// Accel preset 1
#define ADP_PRESET_2    2				// Accel preset 2
#define ADP_PRESET_3    3				// Accel preset 3
#define NUM_ACCEL_PRESETS 4             // Remember to count none
typedef char DECEL_DRIVE_PRESET;
#define DDP_NONE        0				// This preset does nothing. The constraint is set by the user-selected level (skip num)
#define DDP_PRESET_1	1				// Experimental decel preset 1
#define DDP_PRESET_2	2				// Experimental decel preset 2
#define DDP_PRESET_3	3				// Experimental decel preset 3
#define NUM_DECEL_PRESETS 4             // Remember to count none

//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
// IR
// From OP_IRLib.h
//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
typedef char IRTYPES;
#define IR_UNKNOWN     		0		// Unknown and disabled are the same value!
#define IR_DISABLED			0		// Unknown and disabled are the same value!
#define IR_TAMIYA	   		1		// Tamiya should always be number 1
#define IR_TAMIYA_2SHOT		2		// Tamiya 2-shot kill code
#define IR_TAMIYA_35   		3
#define IR_HENGLONG    		4
#define IR_TAIGEN_V1   		5       // Taigen V1
#define IR_FOV 	       		6		// No longer being sold. Imex/Taigen is going to re-issue them but it's still not clear if they will keep the same protocol
#define IR_VSTANK      		7
#define IR_OPENPANZER  		8		// Not yet implemented. For future custom IR codes.
#define IR_RPR_CLARK   		9		// Repair signal: Clark TK-20, 22, and 60 repair protocol
#define IR_RPR_IBU 	   		10		// Repair signal: Italian Battle Unit
#define IR_RPR_RCTA	   		11		// Repair signal: RC Tanks Australia. Theoretically this is the same as IBU, but untested.
#define IR_MG_CLARK			12		// Machine gun: Clark protocol (Sony)
#define IR_MG_RCTA			13		// Machine gun: RCTA protocol
#define IR_SONY				14		// For general purpose Sony codes
#define IR_TAIGEN           15      // Taigen V2/V3

typedef char IRTEAMS;
#define IR_TEAM_NONE           0
#define IR_TEAM_FOV_1          0	// FOV Team 1 we treat as TEAM_NONE. We can use IR_TEAM_FOV_1 in code but it will equal IR_TEAM_NONE
#define IR_TEAM_FOV_2          1
#define IR_TEAM_FOV_3          2
#define IR_TEAM_FOV_4          3



//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
// MOTORS
// From OP_Motors.h
//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
enum ESC_POS_t : byte
{	SERVO_8 = 0,
    SERVO_7 = 1,
    SERVO_6 = 2,
    SERVO_5 = 3,
    SERVO_4 = 4,
    SERVO_3 = 5,
    SERVO_2 = 6,
    SERVO_1 = 7,
    SIDEA,
    SIDEB
};
enum Drive_t : byte
{
SERVO8       = 0,
SERVO7 		 = 1,
SERVO6 		 = 2,
SERVO5 		 = 3,
SERVO4 		 = 4,
SERVO3 		 = 5,
SERVO2		 = 6,
SERVO1		 = 7,
POLOLU 		 = 8,
SABERTOOTH 	 = 9,
OP_SCOUT     = 10,
ONBOARD      = 11,
SERVO_ESC    = 12,
SERVO_PAN    = 13,
SERVO_RECOIL = 14,
DRIVE_DETACHED = 15,
ONBOARD_CD	 = 16
};

//Recoil servo presets
typedef char RecoilPreset;
#define RS_PRESET_NONE                  0
#define RS_PRESET_TAIGEN_TIGER1         1


//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
// SMOKER
// From OP_Smoker.h
//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
typedef char Smoker_t;
#define SMOKERTYPE_ONBOARD_STANDARD     0
#define SMOKERTYPE_ONBOARD_SEPARATE     1
#define SMOKERTYPE_SERIAL               2


//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
// SABERTOOTH SETTINGS
// From OP_Sabertooth.h
//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
#define SABERTOOTH_BAUD_2400        1       // Sabertooth baud value byte for 2400
#define SABERTOOTH_BAUD_9600        2       // Sabertooth baud value byte for 9600
#define SABERTOOTH_BAUD_19200       3       // Sabertooth baud value byte for 19200
#define SABERTOOTH_BAUD_38400       4       // Sabertooth baud value byte for 38400
#define SABERTOOTH_BAUD_115200      5       // Sabertooth baud value byte for 115200



//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
// WEIGHT CLASS, DAMAGE SETTINGS
// From OP_Tank.h
//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
typedef char TANKCLASSTYPES;
#define ULTRALIGHT  0
#define LIGHT		1
#define MEDIUM		2
#define HEAVY		3
//#define ADDITIONAL (number)
#define LAST_WEIGHT_CLASS 	HEAVY

typedef char DAMAGEPROFILES;
#define TAMIYA_DAMAGE   	0		// Stock Tamiya damage profile
#define OPENPANZER_DAMAGE	1		// Open Panzer damage profile
#define NO_DAMAGE           2       // No damage
//#define ADDITIONAL (number)
#define LAST_DAMAGE_PROFILE NO_DAMAGE

struct weightClassSettings{
    uint16_t reloadTime;		// How long (in mS) does it take to reload the cannon. Depends on weight class
    uint16_t recoveryTime;		// How long does recovery mode last (time when tank is regenerating after being destroyed). Class-dependent.
    uint8_t maxHits;			// How many hits can the tank sustain before being destroyed. Depends on weight class
    uint8_t maxMGHits;			// How many hits can the tank sustain from machine gun fire before being destroyed. Only applies to custom weight classes,
                                // and only if Accept_MG_Damage = TRUE
};


//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
// SPECIAL FUNCTIONS
// From OP_FunctionsTriggers.h
//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
const byte COUNT_SPECFUNCTIONS  = 166;	// Count of special functions (1 more than max number below because we count the 0)
enum _special_function : byte {
    SF_NULL_FUNCTION 	= 0,		// 0    -- no function assigned
    SF_ENGINE_TOGGLE 	= 1,   		// 1
    SF_ENGINE_ON 		= 2,    	// 2
    SF_ENGINE_OFF		= 3,    	// 3
    SF_TRANS_TOGGLE 	= 4,    	// 4
    SF_TRANS_ON			= 5,    	// 5
    SF_TRANS_OFF		= 6,    	// 6
    SF_CANNON_FIRE		= 7,    	// 7
    SF_MECH_BARREL	    = 8,		// 8
    SF_RECOIL_SERVO		= 9,		// 9
    SF_HI_FLASH			= 10,		// 10
    SF_MG_FIRE 			= 11,    	// 11
    SF_MG_OFF           = 12,       // 12
    SF_BARREL_ENABLE    = 13,       // 13
    SF_BARREL_DISABLE   = 14,       // 14
    SF_BARREL_TOGGLE    = 15,       // 15
    SF_LIGHT1_TOGGLE    = 16,       // 16
    SF_LIGHT1_ON        = 17,       // 17
    SF_LIGHT1_OFF       = 18,       // 18
    SF_LIGHT2_TOGGLE    = 19,       // 19
    SF_LIGHT2_ON        = 20,       // 20
    SF_LIGHT2_OFF       = 21,       // 21
    SF_RUNNINGLIGHTS_TOGGLE = 22,   // 22
    SF_RUNNINGLIGHTS_ON = 23,       // 23
    SF_RUNNINGLIGHTS_OFF= 24,       // 24
    SF_AUXOUT_TOGGLE    = 25,       // 25
    SF_AUXOUT_ON        = 26,       // 26
    SF_AUXOUT_OFF       = 27,       // 27
    SF_AUXOUT_LEVEL     = 28,       // 28   -- analog function
    SF_AUXOUT_PRESETDIM = 29,       // 29
    SF_AUXOUT_FLASH     = 30,       // 30   -- see also 111 for inverse flash
    SF_AUXOUT_BLINK     = 31,       // 31
    SF_AUXOUT_TOGGLEBLINK = 32,     // 32
    SF_AUXOUT_REVOLVE   = 33,       // 33
    SF_AUXOUT_TOGGLEREVOLVE = 34,   // 34
    SF_USER_SOUND1_ONCE = 35,       // 35   -- see also 86-91 for user sounds 3 & 4 and 103-108 for user sounds 5 & 6
    SF_USER_SOUND1_RPT  = 36,       // 36
    SF_USER_SOUND1_OFF  = 37,       // 37
    SF_USER_SOUND2_ONCE = 38,       // 38
    SF_USER_SOUND2_RPT  = 39,       // 39
    SF_USER_SOUND2_OFF  = 40,       // 40
    SF_OUTPUT_A_TOGGLE  = 41,       // 41   -- see also 109 for pulse and 156 for blink
    SF_OUTPUT_A_ON      = 42,       // 42
    SF_OUTPUT_A_OFF     = 43,       // 43
    SF_OUTPUT_B_TOGGLE  = 44,       // 44   -- see also 110 for pulse and 157 for blink
    SF_OUTPUT_B_ON      = 45,       // 45
    SF_OUTPUT_B_OFF     = 46,       // 46
    SF_ACCEL_LEVEL      = 47,       // 47   -- analog function
    SF_DECEL_LEVEL      = 48,       // 48   -- analog function
    SF_TURNMODE_1       = 49,       // 49
    SF_TURNMODE_2       = 50,       // 50
    SF_TURNMODE_3       = 51,       // 51
    SF_SMOKER           = 52,       // 52   -- analog function, sets the speed of the smoker manually -- see also 101-102 & 161 for manual on/off/toggle digital functions. See 82-84 for control of auto smoker.
    SF_MOTOR_A          = 53,       // 53   -- analog function
    SF_MOTOR_B          = 54,       // 54   -- analog function
    SF_RC1_PASS         = 55,       // 55   -- analog function ("PASS" for pass-through) -- see also 92-97 for pass-throughs 6-8
    SF_RC2_PASS         = 56,       // 56   -- analog function
    SF_RC3_PASS         = 57,       // 57   -- analog function
    SF_RC4_PASS         = 58,       // 58   -- analog function
    SF_RC1_PASS_PAN     = 59,       // 59   -- analog function (Pan servo passthrough signal)
    SF_RC2_PASS_PAN     = 60,       // 60   -- analog function
    SF_RC3_PASS_PAN     = 61,       // 61   -- analog function
    SF_RC4_PASS_PAN     = 62,       // 62   -- analog function
    SF_BARREL_STAB_ON   = 63,       // 63
    SF_BARREL_STAB_OFF  = 64,       // 64
    SF_BARREL_STAB_TOGGLE = 65,     // 65
    SF_BARREL_STAB_LEVEL= 66,       // 66   -- analog function
    SF_HILLS_ON         = 67,       // 67
    SF_HILLS_OFF        = 68,       // 68
    SF_HILLS_TOGGLE     = 69,       // 69
    SF_HILLS_LEVEL      = 70,       // 70   -- analog function
    SF_USER_FUNC_1      = 71,       // 71
    SF_USER_FUNC_2      = 72,       // 72
    SF_USER_ANLG_1      = 73,       // 73   -- analog function
    SF_USER_ANLG_2      = 74,       // 74   -- analog function
    SF_DUMP_DEBUG       = 75,       // 75
    SF_NT_ENABLE        = 76,       // 76
    SF_NT_DISABLE       = 77,       // 77
    SF_NT_TOGGLE        = 78,       // 78
    SF_DRIVEPROFILE_1   = 79,       // 79
    SF_DRIVEPROFILE_2   = 80,       // 80
    SF_DRIVEPROFILE_TOGGLE = 81,    // 81
    SF_SMOKER_ENABLE    = 82,       // 82   -- For control of _auto_ smoker functionality
    SF_SMOKER_DISABLE   = 83,       // 83
    SF_SMOKER_TOGGLE    = 84,       // 84
    SF_SET_VOLUME       = 85,       // 85
    SF_USER_SOUND3_ONCE = 86,       // 86   -- see also 35-40 for user sounds 1 & 2 and 103-108 for user sounds 5 & 6
    SF_USER_SOUND3_RPT  = 87,       // 87
    SF_USER_SOUND3_OFF  = 88,       // 88
    SF_USER_SOUND4_ONCE = 89,       // 89
    SF_USER_SOUND4_RPT  = 90,       // 90
    SF_USER_SOUND4_OFF  = 91,       // 91
    SF_RC6_PASS         = 92,       // 92   -- analog function ("PASS" for pass-through) -- see also 55-62 for pass-throughs 1-4
    SF_RC7_PASS         = 93,       // 93   -- analog function
    SF_RC8_PASS         = 94,       // 94   -- analog function
    SF_RC6_PASS_PAN     = 95,       // 95   -- analog function (Pan servo passthrough signal)
    SF_RC7_PASS_PAN     = 96,       // 96   -- analog function
    SF_RC8_PASS_PAN     = 97,       // 97   -- analog function
    SF_INCR_VOLUME      = 98,       // 98
    SF_DECR_VOLUME      = 99,       // 99
    SF_STOP_VOLUME      = 100,      // 100
    SF_SMOKER_ON        = 101,      // 101  -- functions for controlling smoker manually, see also 52 for analog manual control of smoker output, and 161 for toggle. See 82-84 for control of auto smoker.
    SF_SMOKER_OFF       = 102,      // 102
    SF_USER_SOUND5_ONCE = 103,      // 103  -- see also 35-40 for user sounds 1 & 2 and 86-91 for user sounds 3 & 4
    SF_USER_SOUND5_RPT  = 104,      // 104
    SF_USER_SOUND5_OFF  = 105,      // 105
    SF_USER_SOUND6_ONCE = 106,      // 106
    SF_USER_SOUND6_RPT  = 107,      // 107
    SF_USER_SOUND6_OFF  = 108,      // 108
    SF_OUTPUT_A_PULSE   = 109,      // 109   -- see also 41-43 for other OUTPUT_A functions
    SF_OUTPUT_B_PULSE   = 110,      // 110   -- see also 44-46 for other OUTPUT_B functions
    SF_AUXOUT_INV_FLASH = 111,      // 111   -- see also 30 for regular flash
    SF_MG2_FIRE         = 112,      // 112   -- Second machine gun (L2 output)
    SF_MG2_OFF          = 113,      // 113
    SF_OVERLAY_ENABLE   = 114,      // 114
    SF_OVERLAY_DISABLE  = 115,      // 115
    SF_MANTRANS_FWD     = 116,      // 116
    SF_MANTRANS_REV     = 117,      // 117
    SF_MANTRANS_NEUTRAL = 118,      // 118
    SF_AUXOUT_TOGGLEDIM = 119,      // 119
    SF_MOTOR_A_ON       = 120,      // 120
    SF_MOTOR_A_OFF      = 121,      // 121
    SF_MOTOR_A_TOGGLE   = 122,      // 122
    SF_MOTOR_B_ON       = 123,      // 123
    SF_MOTOR_B_OFF      = 124,      // 124
    SF_MOTOR_B_TOGGLE   = 125,      // 125
    SF_USER_SOUND7_ONCE = 126,      // 126  -- see also 35-40 for user sounds 1 & 2, 86-91 for user sounds 3 & 4, 103-108 for user sounds 5 & 6
    SF_USER_SOUND7_RPT  = 127,      // 127  -- PEOPLE WANT SHIT TONS OF SOUNDS I GUESS
    SF_USER_SOUND7_OFF  = 128,      // 128
    SF_USER_SOUND8_ONCE = 129,      // 129
    SF_USER_SOUND8_RPT  = 130,      // 130
    SF_USER_SOUND8_OFF  = 131,      // 131
    SF_USER_SOUND9_ONCE = 132,      // 132
    SF_USER_SOUND9_RPT  = 133,      // 133
    SF_USER_SOUND9_OFF  = 134,      // 134
    SF_USER_SOUND10_ONCE= 135,      // 135
    SF_USER_SOUND10_RPT = 136,      // 136
    SF_USER_SOUND10_OFF = 137,      // 137
    SF_USER_SOUND11_ONCE= 138,      // 138
    SF_USER_SOUND11_RPT = 139,      // 139
    SF_USER_SOUND11_OFF = 140,      // 140
    SF_USER_SOUND12_ONCE= 141,      // 141
    SF_USER_SOUND12_RPT = 142,      // 142
    SF_USER_SOUND12_OFF = 143,      // 143
    SF_SBA_PLAYSTOP     = 144,      // 144
    SF_SBA_NEXT         = 145,      // 145
    SF_SBA_PREVIOUS     = 146,      // 146
    SF_SBA_RANDOM       = 147,      // 147
    SF_SBB_PLAYSTOP     = 148,      // 148
    SF_SBB_NEXT         = 149,      // 149
    SF_SBB_PREVIOUS     = 150,      // 150
    SF_SBB_RANDOM       = 151,      // 151
    SF_SPEED_25         = 152,      // 152
    SF_SPEED_50         = 153,      // 153
    SF_SPEED_75         = 154,      // 154
    SF_SPEED_RESTORE    = 155,      // 155
    SF_OUTPUT_A_BLINK   = 156,      // 156
    SF_OUTPUT_B_BLINK   = 157,      // 157
    SF_IR_ENABLE        = 158,      // 158
    SF_IR_DISABLE       = 159,      // 159
    SF_IR_TOGGLE        = 160,      // 160
    SF_SMOKER_MANTOGGLE = 161,      // 161  -- see also 52 for analog manual control of smoker output and 101-102 for on/off
    SF_USER_SOUND_ALL_OFF = 162,    // 162
    SF_SMOKE_PREHEAT_ON = 163,      // 163
    SF_SMOKE_PREHEAT_OFF= 164,      // 164
    SF_SMOKE_PREHEAT_TOGGLE = 165   // 165
};

#define MAX_FUNCTION_TRIGGERS 40    // Maximum number of triggers we can save

struct _functionTrigger {
    uint16_t TriggerID;
    _special_function specialFunction;
};

//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
// TRIGGERS
// From OP_FunctionsTriggers.h
//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
// Some range definitions
#define trigger_id_multiplier_ports         100         // External ports input trigger ID is defined as: (multipler_ports * port number) + 0/1 (off/on)

#define trigger_id_multiplier_auxchannel    1000        // Aux channel trigger ID is defined as:
                                                        // (multiplier_auxchannel * channel number) + (number of switch positions * switch_pos_multiplier) + switch position
#define switch_pos_multiplier               10          // Move the number of switch positions to the tens slot

#define trigger_id_adhoc_start              19000       // Trigger IDs for ad-hoc events. Range FROM trigger_id_adhoc_start TO (trigger_id_adhoc_start + trigger_id_adhoc_range - 1)
#define trigger_id_adhoc_range              1000

#define trigger_id_speed_increase           20000       // Trigger IDs for speed rising above  a set level. Range FROM trigger_id_speed_increase TO (trigger_id_speed_increase + trigger_id_speed_range - 1)
#define trigger_id_speed_decrease           21000       // Trigger IDs for speed falling below a set level. Range FROM trigger_id_speed_decrease TO (trigger_id_speed_decrease + trigger_id_speed_range - 1)
#define trigger_id_speed_range              1000

#define trigger_id_throttle_command         22001       // Variable trigger synchronous with actual throttle stick position
#define trigger_id_engine_speed             22002       // Variable trigger synchronous with engine speed (modified/massaged throttle command)
#define trigger_id_vehicle_speed            22003       // Variable trigger synchronous with vehicle movement speed
#define trigger_id_steering_command         22004       // Variable trigger synchronous with steering input (stick position)
#define trigger_id_rotation_command         22005       // Variable trigger synchronous with turret rotation (stick position)
#define trigger_id_elevation_command        22006       // Variable trigger synchronous with barrel elevation (stick position)

#define COUNT_ADHOC_TRIGGERS            12              // This number can not get higher than 16 unless you want to change some methods in the sketch
// Ad-Hoc trigger Flag Masks
#define ADHOCT_BIT_BRAKES_APPLIED       0               // Brakes just applied
#define ADHOCT_BIT_CANNON_HIT           1               // Vehicle received cannon hit
#define ADHOCT_BIT_VEHICLE_DESTROYED    2               // Vehicle destroyed
#define ADHOCT_BIT_CANNON_RELOADED      3               // Cannon reloaded
#define ADHOCT_BIT_ENGINE_START         4               // Engine started
#define ADHOCT_BIT_ENGINE_STOP          5               // Engine stopped
#define ADHOCT_BIT_MOVE_FORWARD         6               // Forward movement begun
#define ADHOCT_BIT_MOVE_REVERSE         7               // Reverse movement begun
#define ADHOCT_BIT_VEHICLE_STOP         8               // Vehicle has come to a stop
#define ADHOCT_BIT_RIGHT_TURN           9               // Right turn begun
#define ADHOCT_BIT_LEFT_TURN            10              // Left turn begun
#define ADHOCT_BIT_NO_TURN              11              // Vehicle is no longer turning

// Ad-Hoc trigger Triggger IDs
#define ADHOC_TRIGGER_BRAKES_APPLIED    trigger_id_adhoc_start + ADHOCT_BIT_BRAKES_APPLIED      // Ad-Hoc Trigger ID  1 - brakes just applied   19000
#define ADHOC_TRIGGER_CANNON_HIT        trigger_id_adhoc_start + ADHOCT_BIT_CANNON_HIT          // Ad-Hoc Trigger ID  2 - received cannon hit   19001
#define ADHOC_TRIGGER_VEHICLE_DESTROYED trigger_id_adhoc_start + ADHOCT_BIT_VEHICLE_DESTROYED   // Ad-Hoc Trigger ID  3 - vehicle destroyed     19002
#define ADHOC_TRIGGER_CANNON_RELOADED   trigger_id_adhoc_start + ADHOCT_BIT_CANNON_RELOADED     // Ad-Hoc Trigger ID  4 - cannon reloaded       19003
#define ADHOC_TRIGGER_ENGINE_START      trigger_id_adhoc_start + ADHOCT_BIT_ENGINE_START        // Ad-Hoc Trigger ID  5 - engine start          19004
#define ADHOC_TRIGGER_ENGINE_STOP       trigger_id_adhoc_start + ADHOCT_BIT_ENGINE_STOP         // Ad-Hoc Trigger ID  6 - engine stop           19005
#define ADHOC_TRIGGER_MOVE_FORWARD      trigger_id_adhoc_start + ADHOCT_BIT_MOVE_FORWARD        // Ad-Hoc Trigger ID  7 - forward movement      19006
#define ADHOC_TRIGGER_MOVE_REVERSE      trigger_id_adhoc_start + ADHOCT_BIT_MOVE_REVERSE        // Ad-Hoc Trigger ID  8 - reverse movement      19007
#define ADHOC_TRIGGER_VEHICLE_STOP      trigger_id_adhoc_start + ADHOCT_BIT_VEHICLE_STOP        // Ad-Hoc Trigger ID  9 - vehicle stopped       19008
#define ADHOC_TRIGGER_RIGHT_TURN        trigger_id_adhoc_start + ADHOCT_BIT_RIGHT_TURN          // Ad-Hoc Trigger ID 10 - right turn            19009
#define ADHOC_TRIGGER_LEFT_TURN         trigger_id_adhoc_start + ADHOCT_BIT_LEFT_TURN           // Ad-Hoc Trigger ID 11 - left turn             19010
#define ADHOC_TRIGGER_NO_TURN           trigger_id_adhoc_start + ADHOCT_BIT_NO_TURN             // Ad-Hoc Trigger ID 12 - no turn               19011

enum _trigger_source : byte {
    TS_NULL_TRIGGER = 0,   // no trigger
    TS_TURRET_STICK = 1,   // Turret stick
    TS_AUX1,               // Aux channel 1
    TS_AUX2,               // Aux channel 2
    TS_AUX3,               // Aux channel 3
    TS_AUX4,               // Aux channel 4
    TS_AUX5,               // Aux channel 5
    TS_AUX6,               // Aux channel 6
    TS_AUX7,               // Aux channel 7
    TS_AUX8,               // Aux channel 8
    TS_AUX9,               // Aux channel 9
    TS_AUX10,              // Aux channel 10
    TS_AUX11,              // Aux channel 11
    TS_AUX12,              // Aux channel 12
    TS_INPUT_A,            // External input A (if set to input)
    TS_INPUT_B,            // External input B (if set to input)
    TS_SPEED_INCR,         // Vehicle speed increases beyond a set point
    TS_SPEED_DECR,         // Vehicle speed decreased below  a set point
    TS_THROTTLE_COMMAND,   // Throttle command (variable)
    TS_ENGINE_SPEED,       // Engine speed (variable)
    TS_VEHICLE_SPEED,      // Vehicle speed (variable)
    TS_STEERING_COMMAND,   // Steering input (variable)
    TS_ROTATION_COMMAND,   // Turrent rotation input (variable)
    TS_ELEVATION_COMMAND,  // Barrel elevation input (variable)
    TS_ADHC_BRAKES,        // Ad-hoc - brakes applied
    TS_ADHC_CANNONHIT,     // Ad-hoc - received cannon hit
    TS_ADHC_DESTROYED,     // Ad-hoc - vehicle destroyed
    TS_ADHC_CANNONRELOAD,  // Ad-hoc - cannon reloaded
    TS_ADHC_ENGINE_START,  // Ad-hoc - engine start
    TS_ADHC_ENGINE_STOP,   // Ad-hoc - engine stop
    TS_ADHC_MOVE_FWD,      // Ad-hoc - forward movement started
    TS_ADHC_MOVE_REV,      // Ad-hoc - reverse movement started
    TS_ADHC_VEHICLE_STOP,  // Ad-hoc - vehicle stopped
    TS_ADHC_RIGHT_TURN,    // Ad-hoc - right turn started
    TS_ADHC_LEFT_TURN,     // Ad-hoc - left turn started
    TS_ADHC_NO_TURN,       // Ad-hoc - no turn
    TS_ADHC_UNUSED_13,     // Ad-hoc - unused
    TS_ADHC_UNUSED_14,     // Ad-hoc - unused
    TS_ADHC_UNUSED_15,     // Ad-hoc - unused
    TS_ADHC_UNUSED_16      // Ad-hoc - unused
};


//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
// RADIO
// From OP_RadioDefines.h and OP_PPMDecode.h
//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
#define MAX_PPM_CHANNELS        10      // Maximum number of channels we can read, from OP_PPMDecode.h
#define MAX_POSSIBLE_PULSE      2150    // Reasonable pulsewidths
#define MIN_POSSIBLE_PULSE      850
#define DEFAULT_PULSE_CENTER    1500

const byte COUNT_OP_CHANNELS	= 16;	// Total number of channels possible to use.
const byte STICKCHANNELS		= 4;	// There are 4 channels associated with the two transmitter sticks
const byte AUXCHANNELS 			= 12;	// There can be (up to) 12 aux channels

// Stick channels
struct stick_channel_settings{// Settings are saved to EEPROM
    uint8_t channelNum;		// Which number are we in the PPM input stream
    int16_t pulseMin;		// PPM pulse min
    int16_t pulseMax;		// PPM pulse max
    int16_t pulseCenter;	// PPM pulse center
    uint8_t deadband;		// Pulse values below deadband are ignored
    boolean reversed;		// Is the channel reversed
};
struct stick_channel {
    boolean present;		// Is this channel present? It should be.
    boolean updated;		// Has the command changed since last check
    boolean started;		// If the prior command was Zero (nothing), and this command is Something, set started = true
    boolean ignore;			// Ignore the command. Only implemented on turret sticks (elevation and azimuth)
    int16_t pulse;          // Current PPM pulse
    int16_t command;        // scaled command
    stick_channel_settings Settings;	// Common settings
};
struct stick_channels {
    stick_channel Throttle;
    stick_channel Turn;
    stick_channel Elevation;
    stick_channel Azimuth;
};

// Aux channels
enum switch_positions : byte {
    SP_NULLPOS = 0,
    SP_POS1,
    SP_POS2,
    SP_POS3,
    SP_POS4,
    SP_POS5,
    SP_POS6,
    SP_POS7,
    SP_POS8,
    SP_POS9,
    SP_POS10,
    SP_POS11,
    SP_POS12
};
struct aux_channel_settings{
    uint8_t channelNum;				// Which number are we in the PPM input stream
    int16_t pulseMin;				// PPM pulse min
    int16_t pulseMax;				// PPM pulse max
    int16_t pulseCenter;            // PPM pulse center
    boolean Digital;				// Is this a digital channel (switch input) or an analog knob input?
    uint8_t numPositions;			// If digital, how many positions does this switch have (not really used in Arduino, but we need to save it for the Desktop app)
    boolean reversed;				// Is the channel reversed
};
struct aux_channels {
    boolean present;				// Is this channel connected or present?
    boolean updated;				// Has the value changed since last time?
    int16_t pulse;					// PPM pulse for this channel - if channel is analog input
    switch_positions switchPos;		// Current switch position, calculated from PPM pulse
    aux_channel_settings Settings;
};

#define RC_MULTISWITCH_START_POS    1000
const int16_t MultiSwitch_MatchArray2[2] = {
    1000,  // 0
    2000   // 1
};
const int16_t MultiSwitch_MatchArray3[3] = {
    1000,  // 0
    1500,  // 1
    2000   // 2
};
const int16_t MultiSwitch_MatchArray4[4] = {
    1000,  // 0
    1333,  // 1
    1667,  // 2
    1800   // 3
};
const int16_t MultiSwitch_MatchArray5[5] = {
    1000,  // 0
    1250,  // 1
    1500,  // 2
    1750,  // 3
    1800   // 4
};
const int16_t MultiSwitch_MatchArray6[6] = {
    1000,  // 0
    1200,  // 1
    1400,  // 2
    1600,  // 3
    1800,  // 4
    2000   // 5
};

// Common channel settings
//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
// This is actually not the same struct that is defined in OP_RadioDefines.h, it is tailored for this program specifically.
struct common_channel_settings {
    uint8_t *channelNum;				// Which number is this in the PPM stream
    int16_t *pulse;
    int16_t *pulseMin;
    int16_t *pulseMax;
    int16_t *pulseCenter;
    boolean *reversed;
    uint8_t *deadband;                  // Pulse values below deadband are ignored. Only applies to stick channels
};


// Turret stick special positions
const byte SPECIALPOSITIONS 	= 9;	// There are 9 special positions on the left stick (TL, TC, TR, ML, MC, MR, BL, BC, BR)
#define MAX_SPEC_POS            36      // The highest number of any special position
enum turretStick_positions : byte {
    SP_TL = 36,
    SP_TC = 34,
    SP_TR = 33,
    SP_ML = 20,
    SP_MC = 18,
    SP_MR = 17,
    SP_BL = 12,
    SP_BC = 10,
    SP_BR = 9
};




//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
// EXTERNAL I/O PORTS
// From OP_IO.h
//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
#define NUM_IO_PORTS 2
#define DD_INPUT 0
#define DD_OUTPUT 1

struct external_io_settings{
    uint8_t dataDirection;	// 1 = output, 0 = input
    uint8_t dataType;		// If input, 1 = "digital" (on/off only), 0 = analog (variable), default to digital. If Output, 1 = normally high, 0 = normally low, default normally high.
};

struct external_io{
    uint16_t inputValue;	// If input, what is the analog reading (0-1023 if analog) or digital reading (0/1 if digital)
    boolean updated;		// If input, has the input value changed since last time?
    boolean outputHigh; 	// if output, is it currently high (1) or low (0) (may not need this)
    external_io_settings Settings;	// Settings
};



//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
// SOUND
// From OP_Sound.h
//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
typedef char SOUND_DEVICE;
#define SD_BENEDINI_TBSMINI     0
#define SD_OP_SOUND_CARD        1
#define SD_TAIGEN_SOUND         2
#define SD_BEIER_USMRC2         3
#define SD_BENEDINI_TBSMICRO    4       // Added December 2017
#define SD_ONBOARD              5       // Added July 2019

#define SD_FIRST_SD             SD_BENEDINI_TBSMINI
#define SD_LAST_SD              SD_ONBOARD


//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
// IMU (Bosch BNO055)
// From OP_BNO055.h
//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
#define NUM_BNO055_OFFSET_REGISTERS 22


#endif // OP_DEFINES


