#ifndef OP_DEFINES
#define OP_DEFINES

#include <arduino_compat.h>

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
#define LAST_DT			DT_CAR

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
#define IR_TAIGEN	   		5
#define IR_FOV 	       		6		// No longer being sold. Imex/Taigen is going to re-issue them but it's still not clear if they will keep the same protocol
#define IR_VSTANK      		7
#define IR_OPENPANZER  		8		// Not yet implemented. For future custom IR codes.
#define IR_RPR_CLARK   		9		// Repair signal: Clark TK-20, 22, and 60 repair protocol
#define IR_RPR_IBU 	   		10		// Repair signal: Italian Battle Unit
#define IR_RPR_RCTA	   		11		// Repair signal: RC Tanks Australia. Theoretically this is the same as IBU, but untested.
#define IR_MG_CLARK			12		// Machine gun: Clark protocol (Sony)
#define IR_MG_RCTA			13		// Machine gun: RCTA protocol
#define IR_SONY				14		// For general purpose Sony codes

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
SERVO_RECOIL = 14
};


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
//#define ADDITIONAL (number)
#define LAST_DAMAGE_PROFILE OPENPANZER_DAMAGE

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
#define trigger_id_multiplier_auxchannel 	1000		// Aux channel trigger ID is defined as:
                                                        // (multiplier * channel number) + (number of switch positions * switch_pos_multiplier) + switch position (1-5)
#define trigger_id_multiplier_ports         100         // External ports input trigger ID is defined as:
                                                        // (multipler * port number) + 0/1 (off/on)
#define switch_pos_multiplier               10          // Move the number of switch positions to the tens slot

const byte COUNT_SPECFUNCTIONS  = 79;	// Count of special functions (1 more than max number below because we count the 0)
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
    SF_AUXOUT_FLASH     = 30,       // 30
    SF_AUXOUT_BLINK     = 31,       // 31
    SF_AUXOUT_TOGGLEBLINK = 32,     // 32
    SF_AUXOUT_REVOLVE   = 33,       // 33
    SF_AUXOUT_TOGGLEREVOLVE = 34,   // 34
    SF_USER_SOUND1_ONCE = 35,       // 35
    SF_USER_SOUND1_RPT  = 36,       // 36
    SF_USER_SOUND1_OFF  = 37,       // 37
    SF_USER_SOUND2_ONCE = 38,       // 38
    SF_USER_SOUND2_RPT  = 39,       // 39
    SF_USER_SOUND2_OFF  = 40,       // 40
    SF_OUTPUT_A_TOGGLE  = 41,       // 41
    SF_OUTPUT_A_ON      = 42,       // 42
    SF_OUTPUT_A_OFF     = 43,       // 43
    SF_OUTPUT_B_TOGGLE  = 44,       // 44
    SF_OUTPUT_B_ON      = 45,       // 45
    SF_OUTPUT_B_OFF     = 46,       // 46
    SF_ACCEL_LEVEL      = 47,       // 47   -- analog function
    SF_DECEL_LEVEL      = 48,       // 48   -- analog function
    SF_TURNMODE_1       = 49,       // 49
    SF_TURNMODE_2       = 50,       // 50
    SF_TURNMODE_3       = 51,       // 51
    SF_SMOKER           = 52,       // 52   -- analog function
    SF_MOTOR_A          = 53,       // 53   -- analog function
    SF_MOTOR_B          = 54,       // 54   -- analog function
    SF_RC1_PASS         = 55,       // 55   -- analog function ("PASS" for pass-through)
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
    SF_NT_TOGGLE        = 78        // 78
};

#define MAX_FUNCTION_TRIGGERS 40    // Maximum number of triggers we can save

struct _functionTrigger {
    uint16_t TriggerID;
    _special_function specialFunction;
};

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
    TS_INPUT_B             // External input B (if set to input)
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
    SP_POS5
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
    boolean Digital;		// If input, is this on/off or analog
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
enum sound_devices : byte {
    SD_BENEDINI_TBSMINI = 0,
    SD_BEIER_USMRC2
};


//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
// IMU (Bosch BNO055)
// From OP_BNO055.h
//-------------------------------------------------------------------------------------------------------------------------------------------------------------->>
#define NUM_BNO055_OFFSET_REGISTERS 22


#endif // OP_DEFINES


