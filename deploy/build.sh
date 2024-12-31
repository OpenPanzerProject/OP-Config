# A script to perform the required build steps to generate the OPConfig setup exe file.
# Developed as a unix shell script just because it was easier for me (a bat or powershell script shouldn't be too different).
# I like to use git bash for this stuff on my windows machine just because I am much more familiar with unix scripting.
# Some assumptions are made here.
#
# 1) Qt Assistant of the required version is in the current PATH.
# 2) InnoSetup has been installed and added to the current PATH.
# 3) psvince.dll is a DLL used in the setup exection to check if an instance of OpConfig is running before installing.
# 4) The help files have already been updated/generated.
# 5) The OpConfig.exe has been built and exists in the debug build folder (I had issues getting release to build).
# 6) This will only build the Windows installer including QTAssistant and WinSparkle.

# Create/Replace the required folder structure
rm -rf InstallFiles
mkdir InstallFiles
mkdir InstallFiles/help_files

# Copy the psvince library into the install folder for the setup to use to check running processes
cp InnoExtraFiles/psvince.dll InstallFiles/psvince.dll

# Find the assistant.exe from the current path and copy that to the install
cp $(which assistant.exe) InstallFiles/assistant.exe

# Add the avrdude and teensy folders
cp -R ../avrdude InstallFiles/avrdude
cp -R ../teensyloader InstallFiles/teensyloader

# Copy the main application from the debug/release folder
cp ../../build-*-Debug/debug/OPConfig.exe InstallFiles/OPConfig.exe

# Add the compressed help files (could also regenerate these if needed?)
cp ../help_files/opconfighelp.qch InstallFiles/help_files/opconfighelp.qch
cp ../help_files/opconfighelp.qhc InstallFiles/help_files/opconfighelp.qhc

# Add the winsparkle.dll
cp ../winsparkle.dll InstallFiles/winsparkle.dll

# Now run the windeployqt tool to find and copy the required dependencies for both OPConfig and Assistant
cd InstallFiles
windeployqt assistant.exe
windeployqt OPConfig.exe

# Run the InnoSetup Compiler
cd ..
iscc OPConfig.iss

echo "Add Done.  Check folder for OPConfig_Setup.exe"