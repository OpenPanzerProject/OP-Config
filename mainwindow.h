/* OPConfig 		Configuration program for the Open Panzer TCB (Tank Control Board)
 * Source: 			openpanzer.org
 * Authors:    		Luke Middleton
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QLabel>
#include <QFrame>
#include <QDebug>
#include <QLineEdit>
#include <QProgressBar>
#include <QStringList>                              // Class of string lists
#include <QStringListModel>                         // String list model, for creating simple text models to populate listviews, etc.
#include <QAbstractItemView>
#include <QtSerialPort/QSerialPortInfo>             // Serial port info, used to populate the drop-down list of COM Ports
#include <QFileDialog.h>
#include <QSignalMapper>
#include <QSortFilterProxyModel>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QTimer>
#include <QProcess>
#include <QScrollBar>
#include <QFileInfo>
#include <QPixmap>
#include <QCommandLineParser>
#include <combo_drivetype.h>                        // My custom drive type combo box
#include <combo_channelorder.h>
#include <combo_baudrates.h>
#include <combo_specialfunction.h>
#include <combo_analogdigital.h>
#include <combo_auxchannelpositions.h>
#include <tablemodel_functiontriggers.h>
#include <getopqmaps.h>
#include <helpbutton.h>                             // Custom push button for help files
#include <qxmlstream.h>
#include <devices.h>                                // My file that defines the different devices we can configure
#include <openpanzercomm.h>                         // OpenPanzer communication library
#include <op_eeprom_varinfo.h>
#include <assistant.h>
#include <downloader.h>
#include <console.h>
#include <version.h>
#include <winsparkle.h>

// We use this to more quickly create message boxes
enum ButtonCollection{vbYesNo, vbYesNoCancel, vbOkCancel, vbOkOnly};
enum IconCollection{vbCritical, vbInformation, vbQuestion, vbWarning, vbExclamation, vbNoIcon};

// Settings for the status label that we fade in and out
#define STATUS_LABEL_ON_DELAY       3000            // How long to show status messages in the bottom status bar
#define STATUS_LABEL_FADEOUT_TIME   2000            // How long does the fade out effect take
#define STATUS_LABEL_FADEIN_TIME    350             // How long does the fade in effect take
enum StatusLabelStatus{slGood, slBad, slNeutral};   // We use these to decide what color the label should have

// Settings for the radio streaming frame tha we also fade in and out
#define RADIO_STREAM_FADEOUT_TIME   4000            // How long does the fade out effect take
#define RADIO_STREAM_FADEIN_TIME    150             // How long does the fade in effect take

// Define the index numbers of the various tabs
#define TAB_INDEX_RADIO             0
#define TAB_INDEX_MOTORS            1
#define TAB_INDEX_LIGHTS            2
#define TAB_INDEX_FUNCTIONS         3
#define TAB_INDEX_DRIVING           4
#define TAB_INDEX_BATTLE            5
#define TAB_INDEX_SOUNDS            6
#define TAB_INDEX_MISC              7
#define TAB_INDEX_FIRMWARE          8

// Not very sophisticated. Here we store the URLs to the TCB latest release hex and version files, and we
// assume they will never change in a million years.
#define LATEST_RELEASE_VERSION_URL  "http://openpanzer.org/downloads/tcbmk1/firmware/version.txt"
#define LATEST_RELEASE_HEX_URL      "http://openpanzer.org/downloads/tcbmk1/firmware/tcbmk1.hex"

// Struct for firmware version info
struct FirmwareVersion{
    uint8_t Major;
    uint8_t Minor;
    uint8_t Patch;
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

// ------------------------------------------------------------------------------------------------------------------------------------------------>>
// PUBLIC
// ------------------------------------------------------------------------------------------------------------------------------------------------>>
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    virtual void showEvent(QShowEvent *event);      // We need this event so we can wait until the main form loads to show WinSparkle

    // These functions will be used as callbacks for the WinSparkle dll and need to be static.
    // WinSparkle is a program we use to check for OP Config updates
    static int canShutdown();                       // Are we ready to shutdown?
    static void shutDown();                         // Shutdown

// ------------------------------------------------------------------------------------------------------------------------------------------------>>
// PUBLIC SLOTS
// ------------------------------------------------------------------------------------------------------------------------------------------------>>
public slots:



    // Set the current device. This function will be called by the deviceselect dialog form when the project first opens.
    void setDevice(OP_device_name);

    // WinSparkle updater.
    void initWinSparkle();                          // Initialize the WinSparkle app
    void checkForUpdates();                         // The check for updates function

    // Slot for processing command line arguments. Better as a slot because we can assign a signal to it that will only call it
    // after the main loop has started. Also make it public so QApplication (or in our case, SingleApplication) can call it.
    // ---------------------------------------------------------------------------------------------------->>
      void ProcessCommandLineArgs();                // If the app is opened with command line arguments, we process them (MainWindow.cpp)


// -------------------------------------------------------------------------------------------------------->>
// SIGNALS
// -------------------------------------------------------------------------------------------------------->>
signals:
    void PulseCentersSaved(boolean);
    void windowWasShown();                          // Has main form finished loading

    // -------------------------------------------------------------------------------------------------------->>
// PRIVATE SLOTS
// -------------------------------------------------------------------------------------------------------->>
private slots:
    // These are functions that will be called if we connect them to a signal
    void changeStackedWidget(const QModelIndex&, const QModelIndex&);
    // Uncomment the below if compiling with Qt 5.6. See bug report: https://bugreports.qt.io/browse/QTBUG-53186
    // A fix for the dual-select bug in Qt 5.6
    //void changeStackedWidget56Fix(const QModelIndex&);

    // Slots for the Assistant (help documentation) and the About menu
    // ---------------------------------------------------------------------------------------------------->>
      void showDocumentation();
      void AboutOP();
      void showPageDocumentation(QString file);

    // Slots for the Tools menu
    // ---------------------------------------------------------------------------------------------------->>
      void ResetAllValues();

    // Slots for the two test buttons on the Radio tab
    // ---------------------------------------------------------------------------------------------------->>
      void cmdTest1_Click();                        // These slots are in the mainwindow.cpp file under FORM-GENERAL
      void cmdTest2_Click();                        // And the connections are made in the MainWindow constructor


    // Slots for connecting/disconnecting/error handling the device
    // ---------------------------------------------------------------------------------------------------->>
      void fillPortsInfo();                         // Updates the list of detected COM ports
      void setCOMPort();                            // Sets the current COM port
      void setBaudRate();                           // Sets the current baud rate
      void toggleDeviceConnection();                // Connect/disconnect from device
      void connectToDevice();                       // Connect to device
      void disconnectFromDevice();                  // Disconnect from device
      void ShowConnectionStatus(boolean connected); // When the device responds or is disconnected, this slot will get called
      void ShowSnoopStatus(boolean connected);      // If the port is open or closed for snooping, this will get called
      void ProcessCommError(QString, QSerialPort::SerialPortError);    // Display communication error message box

    // Slots for reading/writing the device
    // ---------------------------------------------------------------------------------------------------->>
      void readSettingsFromDevice();                // Read all settings from device
      void writeAllSettingsToDevice();              // Write all settings to device
      void writeSomeSettingsToDevice(uint16_t startID, uint16_t endID);   // Write some settings to device
      void SerialStatus_displayFirmware(QString version);      // Display device firmware version in status bar
      void ProcessMinOPCVersion(QString);           // The TCB will tell us the minimum OP Config version it requires, if it is greater than this version ask user to update.
      void updateVarArray_fromSerial(uint16_t ID, QByteArray Value, boolean found);  // Process return message from device after requesting value.
      void processNextSentence(boolean);            // When the device responds with a SERID_NEXT_SENTENCE request

    // Slots for reading/writing to XML file
    // ---------------------------------------------------------------------------------------------------->>
      void actionReadSettingsFromFile();            // Read all settings from a file - this slot actually only gets the file name, which
                                                    // it then passes to the real readSettingsFromFile(Qstring) private function
      void writeSettingsToFile();                   // Save all settings to a file

    // Form control slots
    // ---------------------------------------------------------------------------------------------------->>
      // Radio tab
      void ValidateChannelOrder(QString priorChan, QString newChan, ChannelOrderComboBox *changedCombo);
      void SaveChannelNum(QString, QString, ChannelOrderComboBox*, int);
      void SaveChannelReversed(bool checked, int);
      void SaveAuxChannelType(AnalogDigitalComboBox *, int);
      void SaveAuxChannelPositions(AuxChannelPositionsCombo *, int);
      void SaveThrottleDeadband(int value);
      void SaveTurnDeadband(int value);
      void SaveElevationDeadband(int value);
      void SaveAzimuthDeadband(int value);
      void checkAuxChannelsAgainstFunctionTriggers();
      void SaveNumUtilizedChannels(uint8_t numChannels);
      void ReadPulseWidths(int16_t *pulseWidths);
      void RadioNotReady(void);
      void cmdSaveMinMax_Click();
      void cmdSaveCenters_Click();
      void ConfirmCentersSaved(boolean);
      void cmdToggleRadioStream_Click();
      void SetRadioStreamStatus(boolean streaming);

      // Motor tab
      void ValidateMotorSelections();
      void ShowHideRecoilDelay();
      void SetMechBarrelAuto(bool);
      void SetRecoilServoAuto(bool);
      void ShowHideSmokerSettings();

      // Lights & IO tab
      void SetHiFlashAuto(bool);
      void ShowHideInputAType(int);
      void ShowHideInputBType(int);
      void SavePortA_InputType(int);
      void SavePortB_InputType(int);
      void SetupPortAFunctionTrigger(int);
      void SetupPortBFunctionTrigger(int);

      // Functions tab
      void SetupTriggerSources(_special_function,boolean);  // When they select a function from the drop-down, then we set up the appropriate triggers that can be applied
      void SetupTriggerActions(int);                        // When they select a trigger from teh drop-down, then we set up the appropriate actions for that trigger
      void cmdAddFunctionTrigger_clicked(bool checked);
      void cmdRemoveFunctionTrigger_clicked(bool checked);
      void UpdateTurretStickDelayOptions(boolean);
      void UpdateFunctionTriggerCount(int);

      // Driving tab
      void ShowHideNudgeTime(int);
      void ShowHideNeutralTurnPct(bool);
      void ShowHideNeutralTurnAllowed(int);
      void ShowHideHalftrackTurn(int);
      void ShowHideAccelOptions_1(bool);        // Profile 1
      void ShowHideDecelOptions_1(bool);
      void ShowHideAccelOptions_2(bool);        // Profile 2
      void ShowHideDecelOptions_2(bool);
      void ShowHideBarrelStabilization(bool);
      void ShowHideBarrelSensitivity(bool);
      void ShowHideHillSensitivity(bool);

      // Battle tab
      void ShowHideCannonIRSettings(int);
      void SetupSecondaryCannonIR(int);
      void SetupIRTeamList(int);
      void ShowHideMGIRSettings(int);
      void ShowHideMGHits(bool);
      void ShowHideOtherBattleSettings(int);
      void ShowHideTankIDSettings(bool);

      // Sound tab
      void ShowHideSoundCardSettings();
      void ShowHideHeadlightSoundNote(bool);
      void ShowHideSqueak1Settings(bool);
      void ShowHideSqueak2Settings(bool);
      void ShowHideSqueak3Settings(bool);
      void ShowHideSqueak4Settings(bool);
      void ShowHideSqueak5Settings(bool);
      void ShowHideSqueak6Settings(bool);
      void ShowHideOtherSqueakSettings();

      // Misc tab
      void updateSabertoothBaudLabel(void);
      void cmdSetSabertoothBaud_clicked(void);
      void cmdConfigurePololuDrive_clicked(void);
      void cmdConfigurePololuTurret_clicked(void);

      // Firmware tab - hex flashing
      void cmdFlashHex_clicked();
      void flashStarted();
      void flashFinished();
      void readyReadStandardOutput();
      void readyReadStandardError();                // Won't be using this one after all
      void getLocalHex();
      void getWebHex();
      void checkHexVersion();
      void SaveWebHexToLocal();
      void SaveWebHexFailed();

      // Firmware tab - console
      void ClearConsole();
      void toggleSnoop();
      void putDataToConsole(const QByteArray &data);

      // Status bar (along the bottom)
      void StartStatusLabelOnDelay(void);           // During this delay, the status label is visible
      void FadeOutStatusLabel();                    // This slot fades out the status label


// ------------------------------------------------------------------------------------------------------------------------------------------------>>
// PRIVATE
// ------------------------------------------------------------------------------------------------------------------------------------------------>>
private:
    // Forms
    // ---------------------------------------------------------------------------------------------------->>
      Ui::MainWindow *ui;                           // This form

    // Mouse
    // ---------------------------------------------------------------------------------------------------->>
      void MouseWait();                             // Sets the mouse to hourglass
      void MouseRestore();                          // Returns the mouse to a pointer

    // QT Assistant
    // ---------------------------------------------------------------------------------------------------->>
      Assistant *assistant;

    // Help Buttons
    // ---------------------------------------------------------------------------------------------------->>
      HelpButton *ptrHelpButton;                    // We create a pointer to one so we can pass the reference to Assistant
      QSignalMapper *signalMapper;                  // We'll use a signal mapper to map a string output from each button's released event
      void SetupHelpButtons(void);                  // This will map all the help buttons to the specific location in the help files

    // Message box helper
    // ---------------------------------------------------------------------------------------------------->>
      int msgBox(QString msg, ButtonCollection buttons, QString title, IconCollection icon);
      QMessageBox *mb;

    // Form stuff
    // ---------------------------------------------------------------------------------------------------->>
      void initActionsConnections();                // Set up abstract actions
      QLabel *serialStatusLabel;                    // References to labels and ProgressBar in the Status Bar
      QLabel *otherStatusLabel;
      QFrame *connectFrame;
      QProgressBar *statusProgressBar;
      QStringListModel *listViewWestModel;          // This is a class that provides a model that supplies strings to views (we can use views in listboxes, combo boxes, whatever)

    // Status bar
      void SetupStatusBarLabel();
      void SetStatusLabel(QString, StatusLabelStatus);      // Sets the text and background color, handles the fade-in and fade-out
      QTimer *statusLabelShowTimer;                         // Timer to show the status label

    // Serial status label and colored box
      void SerialStatus_SetAttemptConnect();
      void SerialStatus_SetConnected();
      void SerialStatus_SetNotConnected();
      void SerialStatus_SetAttemptFlash();

    // Tab-specific
    // ---------------------------------------------------------------------------------------------------->>
      // Radio tab
        #define SLIDER_CENTER_ADJUST 10
        void SetupControls_RadioTab(void);
        QString calculateStickDirection(uint8_t StickNum, int16_t Pulse);
        uint8_t calculateAuxSwitchPos(int16_t Pulse, uint8_t NumPositions, boolean Reversed);
        ChannelOrderComboBox *channelOrderCombo[COUNT_OP_CHANNELS];
        AnalogDigitalComboBox *auxTypeCombo[AUXCHANNELS];
        AuxChannelPositionsCombo *auxSwitchPosCombo[AUXCHANNELS];
        QCheckBox *stickReversedCheck[STICKCHANNELS];
        QCheckBox *auxReversedCheck[AUXCHANNELS];
        uint8_t NumUtilizedChannels;
        void UpdateChannelControls_MinMaxCenter(void);  // Will set sliders/min/max controls to whatever is stored in variables
        void ShowHidePulsesPositions(boolean show);
        QSlider *lowSlider[COUNT_OP_CHANNELS];
        QSlider *highSlider[COUNT_OP_CHANNELS];
        QLabel *lblChannelMin[COUNT_OP_CHANNELS];
        QLabel *lblChannelMax[COUNT_OP_CHANNELS];
        QLabel *lblChannelPulse[COUNT_OP_CHANNELS];
        QLabel *lblChannelPosition[COUNT_OP_CHANNELS];
        common_channel_settings ChannelSettings[COUNT_OP_CHANNELS];
        boolean Flag_StartRadioStream;
        boolean Flag_SaveCenterValues;
        boolean Flag_SaveMinMaxValues;
        boolean Flag_RadioValuesChanged;            // If while streaming the user saves the center or min/max values, this flag will get set to true
        void FadeInRadioStreaming(void);
        void FadeOutRadioStreaming(void);
      // Motor tab
        void SetupControls_MotorTab(void);
        void ValidateRCPassthroughs(void);
      // Lights & IO tab
        void SetupControls_LightsIOTab(void);
      // Functions tab
        FunctionTriggerTableModel *FT_TableModel;
        QSortFilterProxyModel *FT_ProxyModel;
        void SetupControls_FunctionsTab(void);
        void RemovedFunctionTriggersMsgBox(void);
      // Driving tab
        void SetupControls_DrivingTab(void);
      // Battle tab
        void SetupControls_BattleTab(void);
      // Sound tab
        void SetupControls_SoundTab(void);
        void EnableBarrelSoundSetting(void);
        void DisableBarrelSoundSetting(void);
        void EnableHeadlightSoundSetting(void);
        void DisableHeadlightSoundSetting(void);
        void AddVolumeFunction(void);
        void AddUserSoundFunctions1_4(void);
        void AddUserSoundFunctions1_2(void);
        void RemoveVolumeUserSoundFunctions1_4(void);
        void RemoveVolumeUserSoundFunctions3_4(void);
        void EnableSqueaks1_3(void);
        void EnableSqueaks4_6(void);
        void DisableSqueaks1_3(void);
        void DisableSqueaks4_6(void);
        void EnableMinSqueakSpeed(void);
        void DisableMinSqueakSpeed(void);
      // Misc tab
        void SetupControls_MiscTab(void);
      // Firmware tab
        void SetupControls_FirmwareTab(void);
        FirmwareVersion DownloadedVersion;
        QString DownloadedVersionDate;
        void ClearFirmwareVersion(FirmwareVersion);
        FirmwareVersion DecodeVersion(QString);
        FirmwareVersion DecodeVersion(QByteArray);
        QString FirmwareVersionToString(FirmwareVersion);
        boolean isFirmwareVersionEmpty(FirmwareVersion);
        FirmwareVersion GetMinTCBVersion(void);
        boolean FirmwareGreaterThanComparison(FirmwareVersion, FirmwareVersion);
        Downloader *VersionDownloader;
        Downloader *HexDownloader;
        boolean AttemptFlash;
        QString strAVRDUDEOutput;
        QProcess *AVRDUDEProcess;
        boolean GotWebHex;                          // If we've downloaded a hex from the web set this flag, so if the user tries again it's instantaneous
        QString WebHexFilePath;                     // If we've downloaded the hex from the web, this is the full path (including file name) where we saved it.
        boolean isCharNumeric(char);                // Is this a character from 0 to 9

    // Var Array (from op_eeprom_varinfo.h) - searching, reading, updating
    // ---------------------------------------------------------------------------------------------------->>
      QMap<uint16_t, QByteArray> VarArray;          // QMap is a generic key/value list container, the key and value can be of any type. Very convenient for us.
      void loadVarArrayDefaults(void);              // Copies default values from STORAGEVARS to VarArray
      boolean updateVarArray_byID(uint16_t ID, QByteArray Value);
      boolean updateVarArray_byPos(uint16_t arrayPos, QByteArray value);
      boolean getStorageVarInfo_byID(_storage_var_info &svi, uint16_t findID);
      boolean getStorageVarInfo_byPos(_storage_var_info & svi, uint16_t arrayPos);
      uint16_t findStorageArrayPosition(uint16_t findID);
      void VarArray_to_Variables(void);             // These two functions are really the critical ones in terms of mapping all our variables to the VarArray
      void Variables_to_VarArray(void);             // Mess these up, and you are in trouble, as they are hard-coded.

    // Variables to Controls and back
    // ---------------------------------------------------------------------------------------------------->>
      void Variables_to_Controls(void);             // These update all the controls with values stored in named variables
      void Controls_to_Variables(void);             // These copy all control values to named variables


    // Named vars (as opposed to numbered variables)
    // ---------------------------------------------------------------------------------------------------->>
      _device_data DeviceData;                      // This struct holds a named version of every piece of information we may want from the device


    // Physical Device Settings
    // ---------------------------------------------------------------------------------------------------->>
      OP_device_name CurrentDevice;                 // The name of the Open Panzer device we will be communicating with
      OpenPanzerComm *comm;                         // Our OpenPanzer Communication object
      boolean AttemptConnect;                       // This will only be true while the connection attempt is in process. Once we are
                                                    // connected or disconnected it will become false, and connection status can be obtained
                                                    // from comm->isConnected()

    // Reading from and Writing to Device
    // ---------------------------------------------------------------------------------------------------->>
      void readSettingsFromFile(QString, boolean);  // Give a file path, it verifies the file exists and tries to read it in. If the second arg is true, will provide confirmation message
      void sendReadCommand_byPos(uint16_t VarPos);  // Read variable from device by VarArray position
      void sendWriteCommand_byPos(uint16_t VarPos); // Write variable to device by VarArray position
      boolean readAllSettings;                      // Flags
      boolean writeAllSettings;
      boolean writeSomeSettings;
      boolean setSabertoothBaudRate;                // Flag set during Sabertooth configuration
      boolean configurePololuDrive;                 // Flags set during Pololu configuration
      boolean configurePololuTurret;
      uint16_t nextVarPos;                          // What position in the VarArray are we going to read/write next
      uint16_t startVarPos;                         // Sometimes we may only want to write a subset of variables. This will be the start variable,
      uint16_t endVarPos;                           // and this will be the end variable.
      void DisableDeviceActionsDuringReadWrite(void); // We disable some stuff during read/write operations (see mainwindow_device_rw.cpp)
      void EnableDeviceActionsAfterReadWrite(void); // This re-enables the same stuff
      void resetReadWriteProcess();                 // This sets the read and write flags to false

      void DisableDeviceActionsDuringRadioStream(void); // Disable some actions when the radio is streaming (see mainwindow_tab_radio.cpp)
      void EnableDeviceActionsAfterRadioStream(void); // This re-enables the same stuff


    // XML File Reading/Writing
    // ---------------------------------------------------------------------------------------------------->>
      QXmlStreamReader xmlReader;

};

#endif // MAINWINDOW_H
