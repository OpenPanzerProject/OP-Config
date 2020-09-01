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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "winsparkle.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Window icon
    setWindowIcon(QIcon(":/icons/images/OP_Icon_32.png"));

    // Application-specific settings - last place the user saved/opened a file
    QCoreApplication::setOrganizationName("Open Panzer");
    QCoreApplication::setOrganizationDomain("OpenPanzer.org");
    QCoreApplication::setApplicationName("OP Config");

    // Get the path of the last location the user read/opened a file
    LastPath = GetLastPath();

    // See if we should show or hide the header based on the user's last selection. If the setting hasn't
    // been written yet, default to show
    if (ProgIni.value("ShowHeader").toString() == "" || ProgIni.value("ShowHeader").toBool()) ShowHeader();
    else                                                                                      HideHeader();

    // Create our assistant for help documentation
    assistant = new Assistant;

    // This fills our combo box with the list of detected COM ports
    fillPortsInfo();
    // We also create a timer to periodically update the list so as new devices are plugged in they automatically get added to the list (or removed)
    COMCheckTimer = new QTimer(this);
    connect(COMCheckTimer, SIGNAL(timeout()), this, SLOT(pollCOMPorts())); // Every time the COMCheckTimer pings, update the list of COM ports
    startCOMChecker(); // This starts the timer

    // We also initialize the baud rate combo. Note this baud rate is what the desktop app uses to communicate with the device,
    // but changing this will NOT change the device's baud rate.
    ui->cboConsoleBaud->setCategory(bcConsole);
    ui->cboConsoleBaud->setCurrentIndex(ui->cboConsoleBaud->findData(USB_DEFAULT_BAUD_RATE));  // See OpenPanzerComm.h for the value of default

    // Begin the OpenPanzer Communication object
    comm = new OpenPanzerComm();
    comm->begin();

    // Pass the OpenPanzer Communication object the selected com port
    setCOMPort();
    setBaudRate();

    // We are not yet trying to connect
    AttemptConnect = false;
    CountFailConnection = 0; // How many times have we tried to connect and failed
    HideConnectAssistMsg = false;

    // Message Box
    // ---------------------------------------------------------------------------------------------------------------------------------->>
    // We want a messagebox formatted with our specific CSS (qss) so we create one here to use throughout MainWindow
    mb = new QMessageBox(this);
    QFile file(":/css/msgbox.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        mb->setStyleSheet(file.readAll());
        file.close();
    }

    // LIST OF TABS
    // ---------------------------------------------------------------------------------------------------------------------------------->>
    // List views are only representations of data models. In the h file we created a pointer to the QStringListModel class
    // which we now instantiate
    listViewWestModel = new QStringListModel(this);
    // Make data list
    QStringList strList;
    strList << "Radio" << "Motors" << "Lights & IO" << "Functions" << "Driving" << "Battle" << "Sounds" << "Misc" << "Firmware";
    // Populate our model
    listViewWestModel->setStringList(strList);
    // Glue model and view together
    ui->listViewWest->setModel(listViewWestModel);
    // Select the first item. WOW! No chance of using a simple integer here. We must pass it a const QModelIndex type
    // We just pull it from our model, row 0, column 0
    ui->listViewWest->setCurrentIndex(listViewWestModel->index(0,0));

    // Help Buttons
    // ---------------------------------------------------------------------------------------------------------------------------------->>
    SetupHelpButtons();


    // ABSTRACT ACTIONS
    // ---------------------------------------------------------------------------------------------------------------------------------->>
    // These can show up in  menus, toolbars, etc...
    initActionsConnections();


    // CONNECTIONS
    // ---------------------------------------------------------------------------------------------------------------------------------->>
    // Let's connect the listview and stacked widget. What a convoluted nightmare this is, about three hours of work for these two lines.
    // QListView really doesn't have any signals that are worth a damn. Nor can we use a signal from QStringListModel object. Instead
    // we must use a signal from the more generic QItemSelectionModel which we point to our list view selection model
    // Now this signal works and passes both current and previous index numbers to our created function called changeStackedWidget.
    // We only need to use the new "current" index and set the stacked widget to that same index.
    QItemSelectionModel *selectionModel = ui->listViewWest->selectionModel();
    connect(selectionModel, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(changeStackedWidget(QModelIndex,QModelIndex)));
    // Uncomment the below if compiling with Qt 5.6
    // In Qt 5.6 whenever we click on the list view, it would select two items - the one you wanted to select, and the next one too.
    // This doesn't look right. If we use this second signal to re-assert the listView selected item, we can sort of work around it.
    // You get some flickering but it does work.
    //connect(ui->listViewWest, SIGNAL(clicked(QModelIndex)), this, SLOT(changeStackedWidget56Fix(QModelIndex)));

    // When we change items in the COM port or Baud rate drop-downs, update our port settings
    connect(ui->cboCOMPorts, SIGNAL(currentIndexChanged(int)), this, SLOT(setCOMPort()));
    connect(ui->cboConsoleBaud, SIGNAL(currentIndexChanged(int)), this, SLOT(setBaudRate()));

    // This button will refresh the COM port list (for when you plug in a device after the program has already loaded)
    connect(ui->cmdRefreshCOMs, SIGNAL(clicked(bool)), this, SLOT(fillPortsInfo()));

    // Connect cmdTest1 and cmdTest2 buttons
    connect(ui->cmdTest1, SIGNAL(clicked(bool)), this, SLOT(cmdTest1_Click()));
    connect(ui->cmdTest2, SIGNAL(clicked(bool)), this, SLOT(cmdTest2_Click()));
    // Hide them if we're not using them for testing
    ui->cmdTest1->hide();
    ui->cmdTest2->hide();

    // Connect/Read/Write buttons
    ui->cmdConnect->setChecked(false);      // Start not connected
    ui->cmdReadDevice->setEnabled(true);    // We actually allow the user to click Read even if not connected, but it will try to connect first
    oneClickRead = false;                   // We call this oneClickRead and this flag indicates we are in the midst of that process. Initialize to false.
    ui->cmdWriteDevice->setEnabled(false);  // Can't write until connected
    connect(ui->cmdConnect, SIGNAL(clicked(bool)), this, SLOT(toggleDeviceConnection()));
    connect(ui->cmdReadDevice, SIGNAL(clicked(bool)), this, SLOT(readSettingsFromDevice()));
    connect(ui->cmdWriteDevice, SIGNAL(clicked(bool)), this, SLOT(writeAllSettingsToDevice()));

    // Connect HideHeader button
    connect(ui->cmdHideHeader, SIGNAL(clicked(bool)), this, SLOT(ShowHideHeader()));

    // Connections to the OpenPanzerComm object (there are some other set on SetupControls_FirmwareTab for snooping/console features)
    connect(comm, SIGNAL(ConnectionChanged(boolean)), this, SLOT (ShowConnectionStatus(boolean)));
    connect(comm, SIGNAL(HereIsFirmwareVersion(QString)), this, SLOT(SerialStatus_displayFirmware(QString)));
    connect(comm, SIGNAL(HereIsHardwareVersion(uint8_t)), this, SLOT(SerialStatus_displayHardware(uint8_t)));
    connect(comm, SIGNAL(HereIsMinOPCVersion(QString)), this, SLOT(ProcessMinOPCVersion(QString)));
    connect(comm, SIGNAL(HereIsValue(uint16_t, QByteArray, boolean)), this, SLOT(updateVarArray_fromSerial(uint16_t, QByteArray, boolean)));
    connect(comm, SIGNAL(NextSentence(boolean)), this, SLOT(processNextSentence(boolean)));
    connect(comm, SIGNAL(CommError(QString, QSerialPort::SerialPortError)), this, SLOT(ProcessCommError(QString, QSerialPort::SerialPortError)));
    connect(comm, SIGNAL(HereAreNumChannels(uint8_t)), this, SLOT(SaveNumUtilizedChannels(uint8_t)));
    connect(comm, SIGNAL(HereArePulseWidths(int16_t*)), this, SLOT(ReadPulseWidths(int16_t*)));
    connect(comm, SIGNAL(RadioNotReady()), this, SLOT(RadioNotReady()));
    connect(comm, SIGNAL(RadioStreamingChanged(boolean)), this, SLOT(SetRadioStreamStatus(boolean)));

    // WinSparkle init. WinSparkle is an application we use to update the program. But we don't want it to start until
    // after the main window has shown
    connect(this, SIGNAL(windowWasShown()), this, SLOT(initWinSparkle()), Qt::ConnectionType(Qt::QueuedConnection | Qt::UniqueConnection));


    // Reading/writing to device initialize
    resetReadWriteProcess();


    // STATUS BAR   see: http://www.bogotobogo.com/Qt/Qt5_QStatusBar.php
    // ---------------------------------------------------------------------------------------------------------------------------------->>
    // We can't align individual widgets on the status bar, so instead, put them all in a single widget in the order we want, then add the
    // single widget to the status bar.
    QHBoxLayout *layout = new QHBoxLayout;
    // Left - Index 0: Serial status label
    serialStatusLabel = new QLabel(this);
    serialStatusLabel->setText("Not connected");
    serialStatusLabel->setMinimumWidth(320);
    serialStatusLabel->setMaximumWidth(320);
    layout->addWidget(serialStatusLabel,0,Qt::AlignLeft);       // Index 0 - Serial status label
    layout->insertSpacing(1,20);                                // Index 1 - spacing
    // Next - Index 2: Other status label
    otherStatusLabel = new QLabel(this);
    otherStatusLabel->setMinimumWidth(200);
    otherStatusLabel->setMaximumWidth(200);
    otherStatusLabel->setMinimumHeight(20);
    otherStatusLabel->setMaximumHeight(20);
    otherStatusLabel->setAlignment(Qt::AlignVCenter);
    otherStatusLabel->setAlignment(Qt::AlignHCenter);
    otherStatusLabel->setText("");
    layout->addWidget(otherStatusLabel,0,Qt::AlignLeft);        // Index 2 - Other status label
    layout->insertSpacing(3,20);                                // Index 3 - spacing
    layout->insertStretch(-1,1);                                // Index 5 - spacing
    // Next - Index 4: Progress bar
    statusProgressBar = new QProgressBar(this);
    statusProgressBar->setTextVisible(false);
    statusProgressBar->setMaximumHeight(20);
    layout->addWidget(statusProgressBar,9);                     // Index 4 - Progress bar
    //layout->insertStretch(-1,1);                                // Index 5 - spacing
    layout->addStrut(30);                                       // Sets the perpendicular dimension to a minimum size
    // This will be a little red/green box to visually represent connection status
    connectFrame = new QFrame(this);
    connectFrame->setStyleSheet("QFrame { background-color: #FF0632; border: 1px solid white; border-radius: 2px; }");
    connectFrame->setMinimumWidth(25);
    connectFrame->setMaximumWidth(25);
    connectFrame->setMinimumHeight(15);
    connectFrame->setMaximumHeight(15);
    layout->insertWidget(0,connectFrame,0,Qt::AlignLeft);
    statusProgressBar->hide();  // Don't show for now
        qApp->processEvents();  // Equivalent of VB DoEvents()
    layout->setContentsMargins(10,0,0,0);   // Left, top, right, bottom - NOT the same as CSS! This puts a bit of padding to the left
    QWidget *container = new QWidget;
    container->setLayout(layout);
    ui->statusBar->addPermanentWidget(container,1);


    // SETUP THE TABS
    // ---------------------------------------------------------------------------------------------------------------------------------->>
      FT_TableModel = new FunctionTriggerTableModel;    // We will need this created first
      SetupStatusBarLabel();
      SetupControls_RadioTab();
      SetupControls_MotorTab();
      SetupControls_LightsIOTab();
      SetupControls_FunctionsTab();
      SetupControls_DrivingTab();
      SetupControls_BattleTab();
      SetupControls_SoundTab();
      SetupControls_MiscTab();
      SetupControls_FirmwareTab();


    // Var Array - do this after all setups are done
    // ---------------------------------------------------------------------------------------------------------------------------------->>
      loadVarArrayDefaults();       // Load defaults into our VarArray
      VarArray_to_Variables();      // Copy VarArray into our named variables
      Variables_to_Controls();      // Now assign the named variables to our controls


    // Go back to first tab of listview in case we got off it during setup
    // ---------------------------------------------------------------------------------------------------------------------------------->>
    // You actually have to set two things - the listview along the side (why I called it West), but programmatically that won't automatically
    // trigger the stacked widget change the way a click will. So we also set the stacked widget explicitly.
      ui->listViewWest->setCurrentIndex(listViewWestModel->index(0,0));
      ui->stackedWidgetMain->setCurrentIndex(0);
      qApp->processEvents();  // Equivalent of VB DoEvents()


    // Finally, now we're all loaded and cozy-comfy: parse any command line arguments
    // ---------------------------------------------------------------------------------------------------------------------------------->>
      // But wait! Don't process them until the window has loaded.
      // "A QTimer with a timeout of 0 will time out as soon as all the events in the window system's event queue have been processed"
      QTimer::singleShot(0, this, SLOT(ProcessCommandLineArgs()));

}


//------------------------------------------------------------------------------------------------------------------------>>
// COMMAND LINE ARGUMENTS
//------------------------------------------------------------------------------------------------------------------------>>
void MainWindow::ProcessCommandLineArgs()
{
    // At present we don't have much in the way of command line options configured, and there really isn't much need.
    // But our Windows installer will associate ".opz" files with the OPConfig application. Opz files are XML settings files
    // used to save TCB settings to a computer as backup. What we have done in the installer (Inno Setup) is to cause any
    // double-click on an .opz file in Windows to execute opconfig.exe with a command line option -f followed by the path and
    // name of the opz file. For example, clicking on C:\mysettings.opz would execute:
    // opconfig -f C:\mysettings.opz

    // So we do want to parse the -f option, get the file name, and pass it to our readSettingsFromFile routine (mainwindow_file_rw.cpp)

    // If future command line arguments are created in the future, we would check for their presence here and create whatever logic
    // is needed to handle them.

    // The QCommandLineParser adds some convenient functionality for checking command line flags and values. We will only be using
    // a very small portion of what it can actually do, which includes command line help, etc...
    // QCommandLineParser: http://doc.qt.io/qt-5/qcommandlineparser.html
    // QCommandLineOption: http://doc.qt.io/qt-5/qcommandlineoption.html
    QCommandLineParser parser;

    // Create an -f option with a value (filename) and call it loadSettingsFileOption. They can use syntax "-f" or "--file"
    // - First argument of this version of QCommandLineOption is a string list of the various ways they can write the option (f or file)
    // - Second is the description ("Read settings from file.")
    // - Third is the name we give to the value the user will pass for this option (filename)
    QCommandLineOption loadSettingsFileOption(QStringList() << "f" << "file",
                                              "Read settings from file.",
                                              "filename");

    // Now add this option to our parser
    parser.addOption(loadSettingsFileOption);

    // Process the actual command line arguments given by the user. Here we could pass the app (if we were in main.cpp),
    // or it also allows us to simply pass a QStringList of arguments.
    parser.process(QCoreApplication::arguments());

    // Check if the -f flag was even used (we named it loadSettingsFileOption)
    if (parser.isSet(loadSettingsFileOption))
    {
        // It was, now retrieve the value that came with it.
        QString filename = (parser.value(loadSettingsFileOption));
        filename.simplified(); // trim white space

        // Ok - if they passed a file name, send it to the readSettingsFromFile function (mainwindow_file_rw.cpp)
        if (filename != "")
        {
            readSettingsFromFile(filename, true);
        }
    }
}

//------------------------------------------------------------------------------------------------------------------------>>
// FORM - WINSPARKLE AUTO UPDATER
//------------------------------------------------------------------------------------------------------------------------>>
// WinSparkle is an application used to check for and install updates
// https://github.com/vslavik/winsparkle
void MainWindow::initWinSparkle()
{
    // Setup updates feed. This must be done before win_sparkle_init(), but
    // could also be accomplished more conveniently using a Windows resource file (.rc)
    // We use resources.rc (look for it in the project directory, or in the headers section of Qt Creator)

    //If these functions aren't called by the app, the URL is obtained from
    //Windows resource named "FeedURL" of type "APPCAST".
//    win_sparkle_set_appcast_url("http://openpanzer.org/downloads/opconfig/latestrelease/appcast.xml");
//    win_sparkle_set_app_details(L"openpanzer.org", L"OP Config Update Example", L"1.0");

    // This specifies whether automatic checks should occur. We do not want automatic checks because it
    // is a nuisance to the user. Instead they can check manually using the option in the help menu.
    win_sparkle_set_automatic_check_for_updates(0);

    // Give it the callback function that lets it know if it's safe to shutdown the application
    win_sparkle_set_can_shutdown_callback(&canShutdown);

    // Give it the callback function that *will* shutdown the app
    win_sparkle_set_shutdown_request_callback(&shutDown);

    // Initialize the updater and possibly show some UI
    win_sparkle_init();
}
void MainWindow::checkForUpdates()
{   // This does the actual update check.
    // We use the "without" version. It differs from the "with" option only in that
    // it doesn't give the user to "skip this update." Of course they can always cancel it
    // and do it later. EDIT: actually doesn't seem to make any difference, the option is still
    // there. I think it's confusing but whatever.
    win_sparkle_check_update_with_ui();
}
void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);

    // showEvent() is called right *before* the window is shown, but WinSparkle
    // requires that the main UI of the application is already shown when
    // calling win_sparkle_init() (otherwise it could show its updates UI
    // behind the app instead of at top). By using a helper signal, we delay
    // calling initWinSparkle() until after the window was shown.

    // The windowWasShown signal is connected to the initWinSparkle() function in the constructor of MainWindow
    emit windowWasShown();
}
int MainWindow::canShutdown()
{
    // We always return true because there's nothing to wait on.
    return 1;
}
void MainWindow::shutDown()
{
    QApplication::quit();
}


//------------------------------------------------------------------------------------------------------------------------>>
// FORM - GENERAL
//------------------------------------------------------------------------------------------------------------------------>>
MainWindow::~MainWindow()
{   // Destructor. Cleanup WinSparkle too.
    win_sparkle_cleanup();
    delete ui;
}
void MainWindow::changeStackedWidget(const QModelIndex& current, const QModelIndex& )
{
    // This function changes the current tab when the user clicks on an item on the left

    // EDIT: Although we can prevent the user from leaving the tab, due to the CSS on the listView
    // I can't figure out how to prevent the other tabs from being highlighted, which results in a
    // confusing condition where the tab we are on is not the tab highlighted...
    // I guess I will leave it and let the user change tabs during flashing. There isn't too much they can get in
    // trouble with, and the flashing doesn't care what tab you're on.
/*    // If we are in the midst of a flashing operation, do not change
    if (AttemptFlash && current.row() != TAB_INDEX_FIRMWARE)
    {
        ui->listViewWest->setCurrentIndex(listViewWestModel->index(TAB_INDEX_FIRMWARE,0));
        // Now we simply exit without changing the stackedWidget
        return;
    }
*/
    // Set the stacked widget to the page passed by current index
    ui->stackedWidgetMain->setCurrentIndex(current.row());
    // Set focus to any old thing so there isn't an ugly looking square around the text we just clicked
    ui->stackedWidgetMain->setFocus();
    // Anytime we change tabs, let's also clear the special function combo on the Functions tab
    ui->cboSelectFunction->clearCurrentFunction();
    // We also check if we're moving off the radio tab, and if so, and if we were streaming, stop the streaming
    if (ui->stackedWidgetMain->currentIndex() != TAB_INDEX_RADIO && comm->isRadioStreaming())
    {
        comm->stopStreamRadio();
    }
    // Likewise if wer'e moving off the Firmware tab and we were snooping, we stop the snooping because it's of no use
    // if we can't see it, and while snooping is enabled we can't connect, which is annoying if you are on another tab
    // and want to connect
    if (ui->stackedWidgetMain->currentIndex() != TAB_INDEX_FIRMWARE && comm->isSnooping())
    {
        comm->closeSerial();
    }
}
// Uncomment the below if compiling in Qt 5.6
/*void MainWindow::changeStackedWidget56Fix(const QModelIndex& current)
{
    // In Qt 5.6, there is a bug that will highlight both the current listView item and the one after it, whenever
    // you click on it. I was able to work around this by adding a second signal from listViewWest clicked that
    // calls this slot. It causes a flicker because the second item is still selected, but then this one de-selects it.
    ui->listViewWest->setCurrentIndex(current);
    qApp->processEvents();  // Equivalent of VB DoEvents()
}*/
void MainWindow::ShowHideHeader()
{   // Toggle the header
    if (ui->frmHeader->isHidden())  ShowHeader();
    else                            HideHeader();
}
void MainWindow::ShowHeader()
{
    ui->frmHeader->show();
    setMinimumHeight(788);
    resize(width(), 788);
    ProgIni.setValue("ShowHeader",true);    // Save setting
}
void MainWindow::HideHeader()
{
    // Hide the "OPEN PANZER OP CONFIG" header bar along the top of the application window. This can be useful
    // for those with small screens
    ui->frmHeader->hide();
    setMinimumHeight(733);
    resize(width(), 733);
    ProgIni.setValue("ShowHeader",false);     // Save setting
}
void MainWindow::cmdTest1_Click()
{
    qDebug() << "Test 1 button clicked";
}
void MainWindow::cmdTest2_Click()
{
    qDebug() << "Test 2 button clicked";
}


//------------------------------------------------------------------------------------------------------------------------>>
// FORM CONTROLS - TOP SECTION - COM, BAUD
//------------------------------------------------------------------------------------------------------------------------>>
void MainWindow::startCOMChecker(void)
{   // This is a repetitive timer that will keep triggering over and over until stopped
    // Each time it trips it will run the pollCOMPorts() function below (setup by signals and slots
    // in MainWindow:MainWindow constructor)
    if (COMCheckTimer->isActive() == false)
    {
        COMCheckTimer->start(CHECK_COM_PORTS_TIME);
    }
}
void MainWindow::stopCOMChecker(void)
{
    COMCheckTimer->stop();
}
void MainWindow::pollCOMPorts()
{
    // We only update the COM ports list while not connected
    if (!comm->isConnected()) fillPortsInfo();
}
void MainWindow::fillPortsInfo()
{
    // This updates the COM port dropdown with all the detected COM ports. The user can refresh the list by clicking the
    // button next to the COM port box.
    QString currentCOM = ui->cboCOMPorts->currentText();

    ui->cboCOMPorts->clear();
    ui->cboCOMPorts->setInsertPolicy(QComboBox::InsertAlphabetically);

    QStringList list;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        list.append(info.portName());
    }
    list.sort();    // Keep them in order
    for (int i = 0; i < list.size(); ++i)
        ui->cboCOMPorts->addItem(list.at(i));

    // Set the selection back to the previous entry if it still exists
    if (currentCOM != "" && ui->cboCOMPorts->findText(currentCOM) != -1)
    {
        ui->cboCOMPorts->setCurrentIndex(ui->cboCOMPorts->findText(currentCOM));
    }
}
void MainWindow::setCOMPort()
{   // Whenever the COM port changes, update the comm object
    // We also include the baud rate
    QSerialPort::BaudRate br = static_cast<QSerialPort::BaudRate>(ui->cboConsoleBaud->itemData(ui->cboConsoleBaud->currentIndex()).toInt());
    comm->updatePortSettings(ui->cboCOMPorts->currentText(),  br);
}
void MainWindow::setBaudRate()
{   // Whenever the Baud rate changes, update the comm object
    // We also include the COM port
    QSerialPort::BaudRate br = static_cast<QSerialPort::BaudRate>(ui->cboConsoleBaud->itemData(ui->cboConsoleBaud->currentIndex()).toInt());
    comm->updatePortSettings(ui->cboCOMPorts->currentText(), br);
}



//------------------------------------------------------------------------------------------------------------------------>>
// FORM CONTROLS - SERIAL STATUS LABEL (In bottom status bar), INITIAL CONNECTION FIRMWARE CHECKS
//------------------------------------------------------------------------------------------------------------------------>>

void MainWindow::SerialStatus_SetAttemptConnect()
{
    serialStatusLabel->setText(tr("Attempting to connect to %1 (%2)...") .arg(comm->currentPortSettings.name).arg(comm->currentPortSettings.stringBaudRate));
        qApp->processEvents();  // Equivalent of VB DoEvents()
}
void MainWindow::SerialStatus_SetNotConnected()
{
    serialStatusLabel->setText(tr("Not connected"));
    // Red box
    connectFrame->setStyleSheet("QFrame { background-color: #FF0632; border: 1px solid white; border-radius: 2px; }");


    // Increment the failed connection count
    CountFailConnection += 1;

    // If they haven't disabled the connection assist message, check the number of times we've failed
    // and if over a certain number show the help message
    if (HideConnectAssistMsg == false && CountFailConnection >= CountConnectionFailuresToShowHelp)
    {
        CountFailConnection = 0;
        ConnectAssistMsgBox();
    }
}
void MainWindow::SerialStatus_SetConnected()
{
    serialStatusLabel->setText(tr("Connected to %1 (%2)") .arg(comm->currentPortSettings.name).arg(comm->currentPortSettings.stringBaudRate));
    // Green box
    connectFrame->setStyleSheet("QFrame { background-color: #01D826; border: 1px solid white; border-radius: 2px; }");
    // Reset the running failed connection attempt count
    CountFailConnection = 0;
}
void MainWindow::SerialStatus_displayFirmware(QString version)
{
    // This slot gets called after the TCB returns to us its version number, which is the first request we send to it
    // after connecting. Subsequently we send several other requests, such as what is the minimum version of OP Config the
    // device is expecting, and also what hardware the device actually is

    CurrentFirmware = version;  // Save this for a slightly later step when it will be displayed in the serialStatusLabel

    // We also want to check the TCB version against the minimum TCB version this version of OP Config expects to work with.
    // This minimum TCB version is defined in version.h
    FirmwareVersion FVCurrent = DecodeVersion(version);   // This is the version of TCB firmware it just told us it has
    FirmwareVersion FVReqd = GetMinTCBVersion();          // This is the minimum version of TCB firmware we want to use
    if (FirmwareGreaterThanComparison(FVReqd, FVCurrent))
    {   // OP Config needs the TCB to be a later version. Warn the user
        QString warn = "Your device firmware needs to be updated!<br /><br />";
        warn.append("Please go to the Firmware tab, download the<br />");
        warn.append("latest release, and flash it to your device.<br /><br />");
        warn.append("Or you can use an older version of OP Config,<br />");
        warn.append("prior releases are available on the Downloads<br />");
        warn.append("page at OpenPanzer.org");
        warn.append("<hr />");
        warn.append("<span style='font-size: 12px;'>");
        warn.append("<table><tr>");
        warn.append("<td>Current TCB Firmware: </td><td>");
        warn.append(version);
        warn.append("</td></tr>");
        warn.append("<tr><td>Minimum device version required:&nbsp;&nbsp;</td><td>");
        warn.append(static_cast<QString>(VER_MINTCB_STR));
        warn.append("</td></tr></table></span>");
        msgBox(warn, vbOkOnly, "Device Update Required", vbExclamation);

        // Also, if we had connected with the intent of reading immediately, we cancel the read.
        // The user can still read but they will have to click the read button a second time
        ResetOneClickRead();    // See mainwindow_device_rw.cpp
    }

    // The next thing we do is ask the TCB/CM/device to tell us what version of OP Config it expects.
    // But we only send the request if TCB/CM/device firmware is greater than 00.90.99 because the
    // the TCB only obtained the capability of responding to this request with 00.91.
    FirmwareVersion FVStart;
    FVStart.Major = 0;
    FVStart.Minor = 90;
    FVStart.Patch = 99;
    if (FirmwareGreaterThanComparison(FVCurrent, FVStart))
    {
        comm->requestMinOPCVersion();
    }
    else
    {
        // If we don't need to check the min OP Config version, we next ask what kind of hardware is communicating with us
        comm->requestHardwareVersion();
    }
}
void MainWindow::ProcessMinOPCVersion(QString version)
{
    // The TCB will tell us the minimum version of OP Config that it requires
    // If that minimum version is greater than the version of OP Config we are using now,
    // request the user to update.

    FirmwareVersion FVReqd = DecodeVersion(version);
    FirmwareVersion FVCurrent = DecodeVersion(static_cast<QString>(VER_PRODUCTVERSION_STR));  // This is our OP Config version from version.h
    if (FirmwareGreaterThanComparison(FVReqd, FVCurrent))
    {   // OP Config needs to be updated. Warn the user
        QString warn = "<b>OP Config needs to be updated!</b><br /><br />";
        warn.append("Your TCB expects a newer version of OP Config.<br />");
        warn.append(" Would you like to check for an update now?");
        warn.append("<hr />");
        warn.append("<span style='font-size: 12px;'>");
        warn.append("<table><tr>");
        warn.append("<td>Current OP Config version: </td><td>");
        warn.append(static_cast<QString>(VER_PRODUCTVERSION_STR));
        warn.append("</td></tr>");
        warn.append("<tr><td>Minimum OP Config version required:&nbsp;&nbsp;</td><td>");
        warn.append(version);
        warn.append("</td></tr></table></span>");

        if (msgBox(warn, vbYesNo, "OP Config Update Required", vbExclamation) == QMessageBox::Yes)
        {
            comm->closeSerial();                        // Close the serial port
            ui->actionCheck_for_Updates->trigger();     // Go check for updates
        }

        // If we had connected with the intent of reading immediately, we cancel the read.
        // The user can still read but they will have to click the read button a second time
        ResetOneClickRead();    // See mainwindow_device_rw.cpp
    }

    // Next we ask for the hardware version of the device communicating with us
    comm->requestHardwareVersion();

}
void MainWindow::SerialStatus_displayHardware(uint8_t hardware)
{
    // This is the response from the final request (after firmware version and expected minimum OP Config version),
    // now the device is telling us what hardware it actually is since we now support multiple boards.

    // Save the hardware version in our global variable:
    CurrentDevice = hardware;

    // We might also ultimately need to change some settings within OP Config to adapt to different devices,
    // that would probably be kicked off here.

    // We now can finally display the firmware and hardware information in the status area at the bottom
    // of the screen as well as the fact we are connected.
    QString hw;
    switch(hardware)
    {
        case DEVICE_TCB_MKI:        hw = "TCB";         break;
        case DEVICE_TCB_MKII:       hw = "TCB MkII";    break;
        case DEVICE_HECLO_SHIELD:   hw = "Heclo Shield";    break;
        case DEVICE_AT_MKI:         hw = "AT";          break;
        default:                    hw = "";            break;
    }
    serialStatusLabel->setText(tr("Connected to %1 (%2)   %3 Firmware: %4") .arg(comm->currentPortSettings.name).arg(comm->currentPortSettings.stringBaudRate).arg(hw).arg(CurrentFirmware));

    // If we're done connecting, and the user wanted to perform a read, kick it off
    if (oneClickRead) readSettingsFromDevice();
}
void MainWindow::SerialStatus_SetAttemptFlash()
{
    serialStatusLabel->setText(tr("Attempting to flash..."));
    // Neutral box - we don't know yet if successful or not
    connectFrame->setStyleSheet("QFrame { background-color: #E1E3E3; border: 1px solid white; border-radius: 2px; }");
            qApp->processEvents();  // Equivalent of VB DoEvents()
}



//------------------------------------------------------------------------------------------------------------------------>>
// FORM - "OTHER" STATUS LABEL (in bottom status bar)
//------------------------------------------------------------------------------------------------------------------------>>
void MainWindow::SetupStatusBarLabel()
{
    // We need a timer for the status label
    statusLabelShowTimer = new QTimer(this);

    // When the timer expires, fade out the status label
    connect(statusLabelShowTimer, SIGNAL(timeout()), this, SLOT(FadeOutStatusLabel()));
}
void MainWindow::SetStatusLabel(QString t, StatusLabelStatus status=slNeutral)
{
    // This function sets the text of the label and the background color (green for good, red for bad), then
    // it fades in the label, shows it for some length of time, and finally fades it back out.

    // Set the text of the status label
    otherStatusLabel->setText(t);
        qApp->processEvents();

    // Set the background color
    switch (status)
    {
        case slGood:    // Green
            otherStatusLabel->setStyleSheet("background: #006600; border: 1px solid #000; color: #FFF; padding-top: 2px;");
            break;

        case slBad:     // Red
            otherStatusLabel->setStyleSheet("background: #990000; border: 1px solid #000; color: #FFF; padding-top: 2px;");
            break;

        case slNeutral: // No background
        default:
            otherStatusLabel->setStyleSheet("background: transparent; border: 1px solid #FFF; color: #FFF; padding-top: 2px;");
    }

    // Fade it in slowly
    QWidget *w = otherStatusLabel;
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    w->setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(STATUS_LABEL_FADEIN_TIME);
    a->setStartValue(0);
    a->setEndValue(1);
    a->setEasingCurve(QEasingCurve::InBack);
    w->show();
    a->start(QPropertyAnimation::DeleteWhenStopped);
    connect(a,SIGNAL(finished()),this,SLOT(StartStatusLabelOnDelay()));
}
void MainWindow::StartStatusLabelOnDelay()
{
    statusLabelShowTimer->setSingleShot(true);
    statusLabelShowTimer->start(STATUS_LABEL_ON_DELAY);
}
void MainWindow::FadeOutStatusLabel()
{
    // Fade out the label
    QWidget *w = otherStatusLabel;
    QGraphicsOpacityEffect *eff = new QGraphicsOpacityEffect(this);
    w->setGraphicsEffect(eff);
    QPropertyAnimation *a = new QPropertyAnimation(eff,"opacity");
    a->setDuration(STATUS_LABEL_FADEOUT_TIME);
    a->setStartValue(1);
    a->setEndValue(0);
    a->setEasingCurve(QEasingCurve::OutBack);
    a->start(QPropertyAnimation::DeleteWhenStopped);
}



//------------------------------------------------------------------------------------------------------------------------>>
// DEVICE - DEPENDENT (changes related to which device is being used. Not presently implemented but some day if we have
//                     other devices besides the Tank Control Board (TCB) we would expand this section - not to mention
//                     re-write half the rest of the program)
//------------------------------------------------------------------------------------------------------------------------>>
//void MainWindow::setDevice(OP_device_name OPD)
//{
//    this->CurrentDevice = OPD;

    // But we are not currently using this stuff
/* It works!
    QMessageBox msgBox;
    if (_d == TCB) {
        msgBox.setText("TCB");
    }
    else if (_d == MiniTCB) {
        msgBox.setText("Mini TCB");
    }
    else if (_d == ScoutESC) {
        msgBox.setText("Scout ESC");
    }
    msgBox.exec();
*/
//}



//------------------------------------------------------------------------------------------------------------------------>>
// ABSTRACT ACTIONS
//------------------------------------------------------------------------------------------------------------------------>>
void MainWindow::initActionsConnections()
{
    // File Menu
    ui->actionOpenFile->setEnabled(true);
    ui->actionOpenFile->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    ui->actionSaveFile->setEnabled(true);
    ui->actionSaveFile->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    ui->actionExit->setEnabled(true);
    ui->actionExit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    connect(ui->actionOpenFile, SIGNAL(triggered()), this, SLOT(actionReadSettingsFromFile()));
    connect(ui->actionSaveFile, SIGNAL(triggered()), this, SLOT(writeSettingsToFile()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));

    // Tools Menu
    ui->actionResetAllVals->setEnabled(true);
    connect(ui->actionResetAllVals, SIGNAL(triggered()), this, SLOT(ResetAllValues()));
    ui->actionShowHeader->setEnabled(true);
    connect(ui->actionShowHeader, SIGNAL(triggered()), this, SLOT(ShowHideHeader()));

    // Device Menu
    ui->actionConnect->setEnabled(true);
    ui->actionConnect->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    ui->actionDisconnect->setEnabled(false);
    ui->actionDisconnect->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
    ui->actionRead->setEnabled(false);      // Can't read or write until connected
    ui->actionRead->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    ui->actionWrite->setEnabled(false);     //
    ui->actionWrite->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_W));
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(connectToDevice()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(disconnectFromDevice()));
    connect(ui->actionRead, SIGNAL(triggered()), this, SLOT(readSettingsFromDevice()));
    connect(ui->actionWrite, SIGNAL(triggered()), this, SLOT(writeAllSettingsToDevice()));

    // Help Menu
    ui->actionHelp_Contents->setEnabled(true);
    ui->actionHelp_Contents->setShortcut(QKeySequence::HelpContents);   // F1 is the shortcut key
    connect(ui->actionHelp_Contents, SIGNAL(triggered()), this, SLOT(showDocumentation()));

    ui->actionCheck_for_Updates->setEnabled(true);
    connect(ui->actionCheck_for_Updates, SIGNAL(triggered(bool)), this, SLOT(checkForUpdates()));

    ui->actionAbout_OP_Config->setEnabled(true);
    connect(ui->actionAbout_OP_Config, SIGNAL(triggered()), this, SLOT(AboutOP()));

}



//------------------------------------------------------------------------------------------------------------------------>>
// ABSTRACT ACTIONS
//------------------------------------------------------------------------------------------------------------------------>>
void MainWindow::ResetAllValues()
{
    // This sets all controls to the same defaults the program is initalized with on open.
    if (msgBox("Are you sure you want to reset every setting to default?", vbYesNo, "Reset all Settings?", vbQuestion) == QMessageBox::Yes)
    {
        loadVarArrayDefaults();       // Load defaults into our VarArray
        VarArray_to_Variables();      // Copy VarArray into our named variables
        Variables_to_Controls();      // Now assign the named variables to our controls
    }
}



//------------------------------------------------------------------------------------------------------------------------>>
// ASSISTANT - HELP DOCUMENTATION
//------------------------------------------------------------------------------------------------------------------------>>
void MainWindow::showDocumentation()
{   // This opens the assistant to the start page
    assistant->showDocumentation("index.html");
}
void MainWindow::showPageDocumentation(QString file)
{   // This opens the assistant to the specified link
    assistant->showDocumentation(file);
}
// This function will map all our help buttons to specific locations in the help files
void MainWindow::SetupHelpButtons()
{
    ptrHelpButton = ui->hpbRadio;               // Point to any one of our help buttons
    ptrHelpButton->PassAssistant(assistant);    // Pass a pointer to the assistant object to our ptrHelpButton, only needs to be done once.

    // Create a signal mapper so we can map the released() signal of each button to another signal that includes a string value
    // This mapped signal will be connected to the showPageDocumentation function which takes a string address value to open
    // the documentation to a specific location
    QSignalMapper *signalMapper = new QSignalMapper(this);

    // Connect all the help buttons to the signal mapper
    // Radio tab
        connect(ui->hpbRadio, SIGNAL(released()), signalMapper, SLOT(map()));               // Radio setup
    // Motors Tab
        connect(ui->hpbMotorSelection, SIGNAL(released()), signalMapper, SLOT(map()));      // Motor selection
        connect(ui->hpbBarrel, SIGNAL(released()), signalMapper, SLOT(map()));              // Mechanical barrel
        connect(ui->hpbTurret, SIGNAL(released()), signalMapper, SLOT(map()));              // Turret settings
        connect(ui->hpbSmoker, SIGNAL(released()), signalMapper, SLOT(map()));              // Mechanical Smoker
        connect(ui->hpbRecoilServo, SIGNAL(released()), signalMapper, SLOT(map()));         // Recoil Servo
    // Lights & IO
        connect(ui->hpbBrakeLights, SIGNAL(released()), signalMapper, SLOT(map()));         // Brake and running lights
        connect(ui->hpbMachineGun, SIGNAL(released()), signalMapper, SLOT(map()));          // Machine gun light
        connect(ui->hpbAuxOutput, SIGNAL(released()), signalMapper, SLOT(map()));           // Aux Output settings
        connect(ui->hpbPortsAB, SIGNAL(released()), signalMapper, SLOT(map()));             // I/O Ports
        connect(ui->hpbIndicatorLights, SIGNAL(released()), signalMapper, SLOT(map()));     // Indicator light settings
        connect(ui->hpbHiFlash, SIGNAL(released()), signalMapper, SLOT(map()));             // High-Intensity Flash settings
    // Functions tab
        connect(ui->hpbFunctions, SIGNAL(released()), signalMapper, SLOT(map()));           // Functions
        connect(ui->hpbIgnoreTurret, SIGNAL(released()), signalMapper, SLOT(map()));        // Ignore turret stick movement time
    // Driving tab
        connect(ui->hpbDriving, SIGNAL(released()), signalMapper, SLOT(map()));             // Driving
        connect(ui->hpbTurning, SIGNAL(released()), signalMapper, SLOT(map()));             // Turning
        connect(ui->hpbAccelDecel, SIGNAL(released()), signalMapper, SLOT(map()));          // Acceleration/deceleration
        connect(ui->hpbTrackRecoil, SIGNAL(released()), signalMapper, SLOT(map()));         // Track recoil
        connect(ui->hpbFreewheel, SIGNAL(released()), signalMapper, SLOT(map()));           // Freewheeling gearbox options
    // Battle tab
        connect(ui->hpbWeightClass, SIGNAL(released()), signalMapper, SLOT(map()));         // Custom weight class
        connect(ui->hpbCannonIR, SIGNAL(released()), signalMapper, SLOT(map()));            // Cannon IR
        connect(ui->hpbMGIR, SIGNAL(released()), signalMapper, SLOT(map()));                // Machine Gun IR
        connect(ui->hpbRepairIR, SIGNAL(released()), signalMapper, SLOT(map()));            // Repair IR
        connect(ui->hpbDamage, SIGNAL(released()), signalMapper, SLOT(map()));              // Damage settings
    // Sounds tab
        connect(ui->hpbGeneralSound, SIGNAL(released()), signalMapper, SLOT(map()));        // General sound options
        connect(ui->hpbSoundSqueaks, SIGNAL(released()), signalMapper, SLOT(map()));        // Squeak section
        connect(ui->hpbSoundVolumes, SIGNAL(released()), signalMapper, SLOT(map()));        // Relative volumes
        connect(ui->hpbSoundBank, SIGNAL(released()), signalMapper, SLOT(map()));           // Sound bank loop settings
    // Misc tab
        connect(ui->hpbLVC, SIGNAL(released()), signalMapper, SLOT(map()));                 // Low voltage cutoff
        connect(ui->hpbBaud, SIGNAL(released()), signalMapper, SLOT(map()));                // Baud rates
        connect(ui->hpbDebug, SIGNAL(released()), signalMapper, SLOT(map()));               // Debug
        connect(ui->hpbSabertooth, SIGNAL(released()), signalMapper, SLOT(map()));          // Sabertooth configuration
        connect(ui->hpbPololu, SIGNAL(released()), signalMapper, SLOT(map()));              // Pololu configuration
        connect(ui->hpbScoutSettings, SIGNAL(released()), signalMapper, SLOT(map()));       // Scout ESC configuration
        connect(ui->hpbIMU, SIGNAL(released()), signalMapper, SLOT(map()));                 // IMU
    // Firmware tab
        connect(ui->hpbFirmware, SIGNAL(released()), signalMapper, SLOT(map()));            // Firmware
        connect(ui->hpbConsole, SIGNAL(released()), signalMapper, SLOT(map()));             // Console


    // Now set the individual string values (html pages) to map each button to
    // Radio tab
        signalMapper->setMapping(ui->hpbRadio, "radio.html");                               // Radio setup
    // Motors tab
        signalMapper->setMapping(ui->hpbMotorSelection, "motors.html#drivemotors");         // Drive motors
        signalMapper->setMapping(ui->hpbBarrel, "motors.html#barrel");                      // Mechanical Barrel
        signalMapper->setMapping(ui->hpbTurret, "motors.html#turretspeed");                 // Turret Settings
        signalMapper->setMapping(ui->hpbRecoilServo, "motors.html#servorecoil");            // Recoil Servo
        signalMapper->setMapping(ui->hpbSmoker, "motors.html#smoker");                      // Smoker
    // Lights & IO
        signalMapper->setMapping(ui->hpbBrakeLights, "lightsio.html#brake");                // Brake and running lights
        signalMapper->setMapping(ui->hpbMachineGun, "lightsio.html#mg");                    // Machine gun light
        signalMapper->setMapping(ui->hpbAuxOutput, "lightsio.html#aux");                    // Aux Output settings
        signalMapper->setMapping(ui->hpbPortsAB, "lightsio.html#io");                       // I/O Ports
        signalMapper->setMapping(ui->hpbIndicatorLights, "lightsio.html#indicator");        // Indicator light settings
        signalMapper->setMapping(ui->hpbHiFlash, "lightsio.html#hiflash");                  // High-Intensity Flash settings
    // Functions
        signalMapper->setMapping(ui->hpbFunctions, "functions.html");                       // Functions
        signalMapper->setMapping(ui->hpbIgnoreTurret, "functions.html#turret");             // Ignore turret stick movement time
    // Driving
        signalMapper->setMapping(ui->hpbDriving, "driving.html#driving");                   // Driving
        signalMapper->setMapping(ui->hpbTurning, "driving.html#turning");                   // Turning
        signalMapper->setMapping(ui->hpbAccelDecel, "driving.html#acceldecel");             // Acceleration/deceleration
        signalMapper->setMapping(ui->hpbTrackRecoil, "driving.html#trackrecoil");           // Track recoil
        signalMapper->setMapping(ui->hpbFreewheel, "driving.html#freewheel");               // Freewheeling gearbox options
    // Battle
        signalMapper->setMapping(ui->hpbWeightClass, "battle.html#weightclass");            // Custom weight class
        signalMapper->setMapping(ui->hpbCannonIR, "battle.html#cannon");                    // Cannon IR
        signalMapper->setMapping(ui->hpbMGIR, "battle.html#mg");                            // Machine Gun IR
        signalMapper->setMapping(ui->hpbRepairIR, "battle.html#repair");                    // Repair IR
        signalMapper->setMapping(ui->hpbDamage, "battle.html#damage");                      // Damage settings
    // Sounds
        signalMapper->setMapping(ui->hpbGeneralSound, "sounds.html");                       // Sound tab
        signalMapper->setMapping(ui->hpbSoundSqueaks, "sounds.html#squeaks");               // Squeak settings
        signalMapper->setMapping(ui->hpbSoundVolumes, "sounds.html#volumes");               // Relative volumes
        signalMapper->setMapping(ui->hpbSoundBank, "sounds.html#soundbank");                // Sound bank loop settings
    // Misc
        signalMapper->setMapping(ui->hpbLVC, "misc.html#lvc");                              // Low voltage cutoff
        signalMapper->setMapping(ui->hpbBaud, "misc.html#baud");                            // Baud rates
        signalMapper->setMapping(ui->hpbDebug, "misc.html#debug");                          // Debug
        signalMapper->setMapping(ui->hpbSabertooth, "misc.html#sabertooth");                // Sabertooth configuration
        signalMapper->setMapping(ui->hpbPololu, "misc.html#pololu");                        // Pololu configuration
        signalMapper->setMapping(ui->hpbScoutSettings, "misc.html#scout");                  // Scout ESC configuration
        signalMapper->setMapping(ui->hpbIMU, "misc.html#imu");                              // IMU
    // Firmware
        signalMapper->setMapping(ui->hpbFirmware, "firmware.html#flash");                   // Firmware
        signalMapper->setMapping(ui->hpbConsole, "firmware.html#console");                  // Console

    // Now connect the mapped signals to the showPageDocumentation() function
    connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(showPageDocumentation(QString)));

    // Not really a help button, but we also map the link in this text warning label to a section of the help documentation.
    connect(ui->lblESCWarningHelp, SIGNAL(linkActivated(QString)), this, SLOT(showPageDocumentation(QString)));
}



//------------------------------------------------------------------------------------------------------------------------>>
// FORM - MESSAGE BOX
//------------------------------------------------------------------------------------------------------------------------>>
// The typing required to display a simple message box is ridiculous. This function along with the enums defined at the top
// of mainwindow.h make it much quicker for most options
int MainWindow::msgBox(QString msg, ButtonCollection buttons=vbOkOnly, QString title="Title", IconCollection icon=vbNoIcon)
{
    switch (buttons)
    {
        case vbYesNo:
            mb->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
            break;
        case vbYesNoCancel:
            mb->setStandardButtons(QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
            break;
        case vbOkCancel:
            mb->setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
            break;
        default:
            mb->setStandardButtons(QMessageBox::Ok);
    }

    switch (icon)
    {
        case vbInformation:
            mb->setIcon(QMessageBox::Information);
            break;
        case vbCritical:
            mb->setIcon(QMessageBox::Critical);
            break;
        case vbWarning:
        case vbExclamation:
            mb->setIcon(QMessageBox::Warning);
            break;
        case vbQuestion:
            mb->setIcon(QMessageBox::Question);
            break;
        default:
            mb->setIcon(QMessageBox::NoIcon);
    }
    QString finaltitle = " ";   // we add a space at the beginning of the title to move it away a bit from the icon
    finaltitle.append(title);
    mb->setWindowTitle(finaltitle);
    // For some ridiculous reason, you can not style message box text using CSS as you can with the other properties.
    // We have to create an HTML element around the text to set font color.
    QString mText;
    mText = "<p style=""color:#000;"">";
        mText.append(msg);
    mText.append("</p>");
    mb->setText(mText);
    return mb->exec();
}
void MainWindow::RemovedFunctionTriggersMsgBox(void)
{
    msgBox("Some function triggers were removed as a result of this change.",vbOkOnly,"Function Triggers",vbExclamation);
    SetStatusLabel("Function triggers changed",slNeutral);
}
void MainWindow::ConnectAssistMsgBox(void)
{
    QMessageBox assist;
    QCheckBox *cb = new QCheckBox("Don't show this message again");

    QFile file(":/css/msgbox.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        assist.setStyleSheet(file.readAll());
        cb->setStyleSheet(file.readAll());  // This seems to work for the text size of the QCheckbox
        file.close();
    }

    // Even though I apply a css stylesheet, it seems to have limited effect, mostly on the existing objects
    // (buttons, QCheckbox), so I also use inline-styles.
    QString helpText;
    helpText.append("<html><head><style>");
        helpText.append("body {font-size: 13px;}");
        helpText.append("li {margin-top: 0px; padding-top: 0px; margin-bottom: 5px;}");
        helpText.append("ul {margin-top: 0px; padding-top: 0px; margin-bottom: 0px;}");
    helpText.append("</style></head><body>");

    helpText.append("<p><strong>Having problems connecting? Try these suggestions:</strong></p>");
    helpText.append("<ul>");
    helpText.append("<li>Make sure Dipswitch 5 on the TCB is in the ON position</li>");
    helpText.append("<li>Make sure you have the correct COM Port selected</li>");
    helpText.append("<li>Try the alternate connection method:");
        helpText.append("<ul>");
            helpText.append("<li>Go to the Firmware tab and click the Snoop button</li>");
            helpText.append("<li>If Snoop connection is successful wait until TCB is done spitting out debug information to the console window</li>");
            helpText.append("<li>Now click the Connect button and the full communication mode should be successful</li></ul>");
        helpText.append("</ul>");
    helpText.append("</ul>");
    helpText.append("<hr>");
    helpText.append("<p>For more troubleshooting help, <a href='http://openpanzer.org/wiki/doku.php?id=wiki:tcb:operation:troubleshooting' style='color: #330055; border-bottom: 1px solid #330055; background: #E7E0EB;'>see the Open Panzer website</a><br/></p>");
    helpText.append("</body></html>");

    assist.setWindowTitle("  Connection Assistance");
    mb->setTextFormat(Qt::RichText);   //this is what makes the links clickable
    assist.setText(helpText);
    assist.setCheckBox(cb);
    assist.setStandardButtons(QMessageBox::Ok);
    assist.setDefaultButton(QMessageBox::Ok);
    assist.setIcon(QMessageBox::Question);
    assist.show();

    // Here we create a connection to the checkbox on the popup, if they check it we will not show this message again
    QObject::connect(cb, &QCheckBox::stateChanged, [this](int state)
    {
        if (static_cast<Qt::CheckState>(state) == Qt::CheckState::Checked)
        {
            HideConnectAssistMsg = true;
        }
    });

    assist.exec();
}


//------------------------------------------------------------------------------------------------------------------------>>
// ABOUT DIALOG
//------------------------------------------------------------------------------------------------------------------------>>
void MainWindow::AboutOP()
{   // Using the "about" message box shows the application icon, which however is very tiny.
    // Better to write some HTML and include a link to an image in your resource file.
//    QMessageBox::about(this, tr("About OP Config"),
//                       tr("This is some example\n"
//                          "text while I figure out the \n"
//                          "real stuff."));

    QMessageBox about;

    QFile file(":/css/msgbox.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        about.setStyleSheet(file.readAll());
        file.close();
    }

    // Even though I apply a css stylesheet, it seems to have limited effect, so I also use inline-styles below.
    // The version info comes from version.h
    QString infoText = "<span style='font-size: 12px;'>Version ";
    infoText.append(VER_PRODUCTVERSION_STR);
    // infoText.append("&nbsp;&nbsp;<b>[TEST]</b><br /><br />&#169; "); // Use for test versions instead of next line
    infoText.append("<br /><br />&#169; ");
    infoText.append(VER_COPYRIGHT_YEAR_STR);
    infoText.append(" <a href='http://www.openpanzer.org/' style='color: #330055; border-bottom: 1px solid #330055; background: #E7E0EB;'>OpenPanzer.org</a></span>");

    about.setWindowTitle("  OP Config");
    about.setTextFormat(Qt::RichText);   //this is what makes the links clickable
    about.setText("<img src=':/images/opconfig.png'></img><br />A desktop configuration program &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<br />for Open Panzer devices.");
    //about.setInformativeText("<span style='font-size: 12px;'>Version 1.0<br /><br />&#169; 2016 <a href='http://www.openpanzer.org/' style='color: #330055; border-bottom: 1px solid #330055; background: #E7E0EB;'>OpenPanzer.org</a></span>");
    about.setInformativeText(infoText);
    about.setStandardButtons(QMessageBox::Ok);
    about.setIconPixmap(QPixmap(":/images/AboutIcon.png"));
    about.setDefaultButton(QMessageBox::Ok);
    about.show();
    about.exec();
}



//------------------------------------------------------------------------------------------------------------------------>>
// MOUSE ICON
//------------------------------------------------------------------------------------------------------------------------>>
void MainWindow::MouseWait(void)
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
}

void MainWindow::MouseRestore(void)
{
    QApplication::restoreOverrideCursor();
}



