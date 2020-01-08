# OPConfig 		Configuration program for the Open Panzer TCB (Tank Control Board)
# Source: 		openpanzer.org
# Authors:    		Luke Middleton
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#
#-------------------------------------------------------
# Project created by Luke Middleton 2015-06-27T12:43:02
#-------------------------------------------------------

QT       += core gui serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OPConfig
TEMPLATE = app

RC_FILE = resources.rc

#This is how we link in an external dll, in this case WinSparkle.
# $$_PRO_FILE_PWD_ returns the path to the directory containing the project file in use
# http://doc.qt.io/qt-5/qmake-variable-reference.html
# L is the library path and l is the library
LIBS += -L$$_PRO_FILE_PWD_/ -lWinSparkle

SOURCES += main.cpp\
        mainwindow.cpp \
    assistant.cpp \
    helpbutton.cpp \
    combo_drivetype.cpp \
    combo_baudrates.cpp \
    combo_channelorder.cpp \
    combo_specialfunction.cpp \
    combo_sounddevices.cpp \
    tablemodel_functiontriggers.cpp \
    getopqmaps.cpp \
    combo_triggersource.cpp \
    combo_analogdigital.cpp \
    combo_auxchannelpositions.cpp \
    combo_drivepreset.cpp \
    combo_irprotocol.cpp \
    combo_repairprotocol.cpp \
    combo_damageprofile.cpp \
    framecontent.cpp \
    combo_mgprotocol.cpp \
    combo_irteams.cpp \
    openpanzercomm.cpp \
    downloader.cpp \
    mainwindow_tab_motors.cpp \
    mainwindow_tab_functions.cpp \
    mainwindow_tab_lightsio.cpp \
    mainwindow_tab_driving.cpp \
    mainwindow_tab_sounds.cpp \
    mainwindow_tab_battle.cpp \
    mainwindow_tab_misc.cpp \
    mainwindow_tab_firmware.cpp \
    mainwindow_varcontrols.cpp \
    mainwindow_vararray.cpp \
    mainwindow_device_rw.cpp \
    mainwindow_file_rw.cpp \
    mainwindow_tab_radio.cpp \
    singleapplication.cpp \
    combo_recoilservopreset.cpp \
    combo_devices.cpp \
    combo_smokertype.cpp

HEADERS  += mainwindow.h \
    arduino_compat.h \
    op_eeprom_varinfo.h \
    op_defines.h \
    assistant.h \
    helpbutton.h \
    op_devicedata_struct.h \
    combo_drivetype.h \
    combo_baudrates.h \
    combo_channelorder.h \
    combo_specialfunction.h \
    combo_sounddevices.h \
    tablemodel_functiontriggers.h \
    getopqmaps.h \
    combo_triggersource.h \
    combo_analogdigital.h \
    combo_auxchannelpositions.h \
    combo_drivepreset.h \
    combo_irprotocol.h \
    combo_repairprotocol.h \
    combo_damageprofile.h \
    framecontent.h \
    combo_mgprotocol.h \
    combo_irteams.h \
    openpanzercomm.h \
    downloader.h \
    version.h \
    winsparkle.h \
    winsparkle-version.h \
    resources.rc \
    singleapplication.h \
    combo_recoilservopreset.h \
    combo_devices.h \
    combo_smokertype.h

FORMS    += mainwindow.ui

RESOURCES += \
    opc_resources.qrc

DISTFILES +=

CONFIG += c++11     #Needed this or it wouldn't compile under mingw

# Added this for the SingleApplication class
DEFINES += QAPPLICATION_CLASS=QApplication # or whatever app class you want
