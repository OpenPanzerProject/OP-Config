![Open Panzer](http://www.openpanzer.org/images/github/openpanzeropconfig.png)
# Introduction
  * [Open Panzer](http://www.openpanzer.org) is a community project to develop open source products for the RC tank market. 
  * The TCB (tank control board) is a highly capable circuit board designed specifically for RC model tanks, but also suitable for halftracks, cars, or even battleships. The hardware is based on an ATmega 2560 processor and the code consists of an Arduino sketch as well as various C++ libraries. It has its own firmware repository, [see here](https://github.com/OpenPanzerProject/TCB)
  * OP Config is a desktop application used to configure the many options on the TCB and to simplify flashing new firmware to the TCB. The repository you are in now contains the source code for the OP Config application. It was written in C++ using the open source application development software called ["Qt"](http://www.qt.io/developers/).

## Resources
  * For more information on the Open Panzer project, see the [OpenPanzer Wiki](http://wiki.openpanzer.org).
  * To discuss the project, feel free to join the [Open Panzer Community](http://openpanzer.org/forum/index.php?action=forum).
  * To download a compiled version of OP Config for installation in Windows, see the [Open Panzer Downloads page](http://www.openpanzer.org/downloads). 

## General Users
If you are not a developer, you probably don't need to worry about anything on this site. Instead, go to the [Open Panzer Downloads page](http://www.openpanzer.org/downloads) and get your own installable version of OP Config. 

## Developers
OP Config from versions 0.94.00 were developed using Qt Creator 15.0.0 using Qt version 6.8.1. Code is written in C++. Executables (available on the [Open Panzer Downloads page](http://www.openpanzer.org/downloads) were compiled for Windows using the MinGW 13.1.0 64-bit compiler. 

OP Config versions prior to 0.94.00 were developed with Qt Creator 3.4.1 using Qt version 5.4.2. Compiler was MinGW 4.9.1 32-bit. Prior version executables are available from the same Downloads link above. 

Qt is well-known for being cross-platform compatible so it should be possible to compile a version for use on other operating systems such as Mac OS X, but it only exists here in a Windows variant at present. If you want to compile this source for another operating system feel free, and please let us know! 

For those curious, we are using [Inno Setup 5.5.8](http://www.jrsoftware.org/isinfo.php) to create the Windows installer package. Qt has the Qt Installer Framework but we found it rather limiting. For the auto-update feature we are using [WinSparkle](https://github.com/vslavik/winsparkle). This would have to be changed for a non-Windows version, but it is based on the well-known Mac project called [Sparkle](https://sparkle-project.org/) so that should not be too difficult. There are no other external dependencies aside from various libraries bundled with Qt. 

A deployment folder has been added which includes a number of extra artifacts and a script to build the Windows installer.  This is a unix shell script at the moment just because it was easier but could be converted to Windows batch/powershell.  The script assumes that the code and help files have already been deployed and that both Qt Assistant and InnoSetup are installed and in the PATH.  The script will gather all of the required files into a new folder and run the InnoSetup compiler to build the installer exe file.

## License
Source files for OP Config are free software: you can redistribute them and/or modify them under the terms of the GNU General Public License version 3 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 

For more specific details see [http://www.gnu.org/licenses](http://www.gnu.org/licenses), the [Quick Guide to GPLv3.](http://www.gnu.org/licenses/quick-guide-gplv3.html) and the [copying.txt](https://github.com/OpenPanzerProject/OP-Config/blob/master/COPYING.txt) file in the codebase.

The GNU operating system which is under the same license has an informative [FAQ here](http://www.gnu.org/licenses/gpl-faq.html).
