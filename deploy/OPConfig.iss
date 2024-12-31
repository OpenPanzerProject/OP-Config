; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppExeName "OPConfig.exe"
#define MyAppName "OP Config"
#define MyAppVersion "0.94.0"
#define MyAppPublisher "Open Panzer"
#define MyAppURL "http://www.openpanzer.org"
#define WikiURL "http://wiki.openpanzer.org"
#define WikiURLText "Open Panzer Wiki"
#define SourceFiles "InstallFiles\*"
#define FinalOutputDir "."


[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{221509E5-0623-490C-8ABF-C73EE6D9634F}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
; One of these no doubt ends up as the "OP Config on the Web" hyperlink that gets included in the install folder. It would be nice to remove it, 
; we already include a link to the wiki, or at least rename it because it doesn't actually take you to "OP Config" on the web, it takes you to openpanzer.org. 
; But in fact according to the documentation they also provide links in add/remove programs, though I can't see it.
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\OpenPanzer/OPConfig
DefaultGroupName=Open Panzer\OP Config
; If yes, Setup displays as "Don't create a Start Menu folder" checkbox option on the Select Start Menu Folder wizard page. 
AllowNoIcons=yes
OutputDir={#FinalOutputDir}
OutputBaseFilename=OPConfig_Setup
Compression=lzma
SolidCompression=yes
; We want to show the welcome page. It just says welcome, and then they click next.
DisableWelcomePage=no
; This is the image on the left side of the installer form, we can replace it with our own 164x314px 32-bit bitmap
WizardImageFile=InnoExtraFiles\InstallerBackground.bmp
; This will create the registry keys we will specify below to associate this program with certain file type extensions (namely .opz)
ChangesAssociations=yes
; This will be the icon used for the installer package itself. This one has nothing to do with the compiled application and is part only of the installation package.
; I put this icon directly in my InstallPackage folder so that InnoSetup can find it. 
SetupIconFile=InnoExtraFiles\openpanzer.ico
; You could also specify an uninstaller icon
;UninstallIconFile=
; This icon will be used in the Add/Remove programs (or Programs and Features as it's called in Win7)
; The ,n after the name allows us to select the zero-based index of the image within the ico file that we want to use, since there can be more than one 
; icon in the rc file embedded into the exe (note this is not the same as multiple versions/sizes of the same image within a single ico - there can actually be multiple icos too)
; I defined two icons in my RC file, the first is for the application and the second is for settings files. Here I will specify the first. 
; See here I am not specifying an icon per se, but the actual exe file that we have compiled. Windows can draw that icon from the exe and display it in Add/Remove Programs.
; See here: http://www.jrsoftware.org/ishelp/index.php?topic=setup_uninstalldisplayicon
UninstallDisplayIcon={app}\{#MyAppExeName},0


[Registry]
; ".opz" is the extension we're associating. "OpenPanzerSetting" is the internal name for the file type as stored in the registry. 
; Make sure you use a unique name for this so you don't inadvertently overwrite another application's registry key.
Root: HKCR; Subkey: ".opz"; ValueType: string; ValueName: ""; ValueData: "OpenPanzerSettings"; Flags: uninsdeletevalue
; The second "Open Panzer Settings" (with spaces) below is the name for the file type as shown in Explorer.
Root: HKCR; Subkey: "OpenPanzerSettings"; ValueType: string; ValueName: ""; ValueData: "Open Panzer Settings"; Flags: uninsdeletekey
; "DefaultIcon" is the registry key that specifies the filename containing the icon to associate with the file type. 
; ",0" tells Explorer to use the first icon from OPConfig.exe (",1" would mean the second icon.)  I defined two icons in my RC file, the 
; second one is for settings.
Root: HKCR; Subkey: "OpenPanzerSettings\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\{#MyAppExeName},1"
; "shell\open\command" is the registry key that specifies the program to execute when a file of the type is double-clicked in Explorer. 
; The surrounding quotes are in the command line so it handles long filenames correctly. The sample for this line just had ""%1"" but in Qt
; I have created a command line parser that will look for the -f flag (for file), so I've added here the -f before the %1 arg.
Root: HKCR; Subkey: "OpenPanzerSettings\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\{#MyAppExeName}"" ""-f %1"""
                                                                                                                                         
[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
; cm means custom messages. These are just pre-defined defaults that will be automatically translated depending on the user's regional settings, 
; but there is nothing stopping you from typing in whatever, and the fact there is a {cm:} doesn't mean any special action is occuring
; So basically this creates two tasks with checkboxes next to them that are by default unchecked. But these tasks don't execute anything unless
; you tie it to an entry in the icons section below. 
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
; We don't make this an option, we just do it automatically above in the regisry
; Name: "associate"; Description: "&Associate OP Config with .opz settings files"; GroupDescription: "Other tasks:"; Flags: unchecked

[Files]
; NOTE: Don't use "Flags: ignoreversion" on any shared system files
Source: {#SourceFiles}; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
; This is a url in the install folder
;Source: "OpenPanzerWiki.url"; DestDir: "{app}"

[Icons]
; Icons are really just shortcuts that will be created in various locations that you want. 
; This will create icons in the start menu if the user doesn't skip that option
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
; Name: "{group}\Visit OpenPanzer.org"; Filename: "{#MyAppURL}"   ; too many urls in the install directory...
Name: "{group}\Visit the Open Panzer Wiki"; Filename: "{#WikiURL}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
; Note this one has a tasks: parameter with it associated with the task named "desktopicon". If the user checks that option from the
; tasks above, then  it will create a destktop shortcut with MyApp name pointing to MyAppExeName
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
; Here again we associate this with a task above named "quicklaunchicon" and if the user checks it, we install a shortcut in the quick launch area. 
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon
                              
[Messages]
; If we want to create custom messages on any page, we have to look up the label name in the C:\Program Files (x86)\Inno Setup 5\Default.isl file. 
; I want adjust slightly the text on the welcome page
WelcomeLabel1=Welcome to the Open Panzer [name] Setup Wizard
WelcomeLabel2=This will install [name/ver] on your computer. 
; I want a message on the last page that lets the user click on a link and go to the Wiki
FinishedLabel=Setup has finished installing [name] on your computer.%n%n


[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

[UninstallDelete]
Type: filesandordirs; Name: "{app}\help_files\*"
Type: filesandordirs; Name: "{app}\firmware\*"

;-------------------------------------------------------------------------------

; This sample script was created by Andres Cabezas ( http://wwww.domador.net )

; It is based on another sample script, created by Vincenzo Giordano, found at 
; http://www.vincenzo.net/isxkb/index.php?title=Call_psvince.dll_on_install_and_uninstall

; To clarify your freedom to use this code, I've appended a license at the end,
; an even-more-permissive version of the already-permissive Expat license.

; My note: combine with psvince.dll this makes sure the installer closes any open
; instance of OP Config before proceeding to install an updated. 

;-------------------------------------------------------------------------------

[Code]

////////// Customize the following constants to suit your own program //////////

const

// Name of the application that should be closed and name of its executable

  ProgramName = 'OP Config';
  ProgramExeName = 'OPConfig.exe';

// Messages user will see if the application is running.  
// (It may be a good idea to give instructions on HOW to close your application,
// if it's not obvious to the user (e.g., in the case of background applications)

  ProgramRunningOnInstallMessage = ProgramName + ' is currently running. ' + #13 + #13 +
      'Please close it and then click on ''Retry'' to proceed with the installation.';
  InstallationCanceledMessage = 'The installation was canceled.';

  ProgramRunningOnUninstallMessage = ProgramName + ' is currently running. ' + #13 + #13 +
      'Please close it and then click on ''Retry'' to proceed.';
  UninstallationCanceledMessage = 'The uninstallation process was canceled.';

////////////////////// end of basic-customization section //////////////////////

//------------------------------------------------------------------------------

// IsModuleLoadedI - function to call at install time
// Also added setuponly flag
function IsModuleLoadedI(modulename: String ):  Boolean;
external 'IsModuleLoaded@files:psvince.dll stdcall setuponly';

// IsModuleLoadedU - function to call at uninstall time
// Also added uninstallonly flag
function IsModuleLoadedU(modulename: String ):  Boolean;
external 'IsModuleLoaded@{app}\psvince.dll stdcall uninstallonly' ;

//------------------------------------------------------------------------------

// Calls IsModuleLoadedI or IsModuleLoadedU as appropriate

function IsModuleLoaded( modulename: String; isUninstallation: Boolean ): Boolean;
begin
  if isUninstallation then
    Result := IsModuleLoadedU( modulename )
  else
    Result := IsModuleLoadedI( modulename );
end;

//------------------------------------------------------------------------------

// Prompt the user to close a program that's still running.
// Finish when the executable is closed or the user cancels the process.

//  -> message : A message to show the user to prompt them to close 
//  -> isUninstallation : Whether this is an uninstallation (to call the right function.)
// <-  True if the program was closed (or was not running),
//     False if the user clicked on the Cancel button and didn't close the program

function PromptUntilProgramClosedOrInstallationCanceled( 
              message: String; 
              isUninstallation: Boolean ): Boolean;
var
  ButtonPressed : Integer;
begin
  ButtonPressed := IDRETRY;

  // Check if the program is running or if the user has pressed the cancel button
  while IsModuleLoaded( ProgramExeName, isUninstallation ) and ( ButtonPressed <> IDCANCEL ) do
  begin
    ButtonPressed := MsgBox( message , mbError, MB_RETRYCANCEL );    
  end;

  // Has the program been closed?
  Result := Not IsModuleLoaded( ProgramExeName, isUninstallation );
end;

//------------------------------------------------------------------------------

function InitializeSetup(): Boolean;
begin
  Result := PromptUntilProgramClosedOrInstallationCanceled( ProgramRunningOnInstallMessage, False );

  if Not Result then
  begin
    MsgBox( InstallationCanceledMessage, mbInformation, MB_OK );
  end;
end;

//------------------------------------------------------------------------------

function InitializeUninstall(): Boolean;
begin
  Result := PromptUntilProgramClosedOrInstallationCanceled( ProgramRunningOnUninstallMessage, True );

  // Unload the DLL, otherwise the dll psvince is not deleted
  UnloadDLL(ExpandConstant('{app}\psvince.dll'));

  if not Result then
  begin
    MsgBox( UninstallationCanceledMessage, mbInformation, MB_OK );
  end;  
end;


//------------------------------------------------------------------------------
// I found this on the internet. It adds a link in the lower left corner of all screens except the license scree (last bit),
// but I'm not showing a license screen anyway and that could be changed, but I'm leaving it so you can see how it was done. 
var
  WikiLinkLabel: TLabel;

procedure WikiLinkClick(Sender: TObject);
var
  ErrorCode: Integer;
begin
  ShellExec('', '{#WikiURL}', '', '', SW_SHOW, ewNoWait, 
    ErrorCode);
end;

procedure InitializeWizard;
begin
  WikiLinkLabel := TLabel.Create(WizardForm);
  WikiLinkLabel.Parent := WizardForm;
  WikiLinkLabel.Left := 12;
  WikiLinkLabel.Top := WizardForm.ClientHeight - WikiLinkLabel.ClientHeight - 16;
  WikiLinkLabel.Cursor := crHand;
  //WikiLinkLabel.Font.Color := clBlue;
  // Swap the first two numbers of the standard HTML color to get the correct one here
  // So if HTML color was CC0022 you would enter here 2200CC
  WikiLinkLabel.Font.Color := $63123F;   
  WikiLinkLabel.Font.Style := [fsUnderline];
  WikiLinkLabel.Caption := '{#WikiURLText}';
  WikiLinkLabel.OnClick := @WikiLinkClick;
end;

procedure CurPageChanged(CurPageID: Integer);
begin
  WikiLinkLabel.Visible := CurPageID <> wpLicense;
end;
