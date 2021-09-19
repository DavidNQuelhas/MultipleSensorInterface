#--------------------------------------------------------------------------------------------------
# Copyright (C) 2021 David Nuno Quelhas. LGPL License 3.0 (GNU).  
# David Nuno Quelhas; Lisboa, Portugal.  david.quelhas@yahoo.com ,                                  
# https://multiple-sensor-interface.blogspot.com                                                    
#                                                                                                   
# Multi-sensor interface, RTU. Modbus RS485/RS232 Device Driver.                           
#
# This library is free software; you can redistribute it and/or modify it under the terms of the    
# GNU Lesser General Public version 3.0 License as published by the Free Software Foundation.      
# This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;         
# without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.         
# See the GNU Lesser General Public License for more details.                                       
# You should have received a copy of the GNU Lesser General Public License along with this library. 
#--------------------------------------------------------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += widgets serialport
} else {
    include($$QTSERIALPORT_PROJECT_ROOT/src/serialport/qt4support/serialport.prf)
}

TARGET = multiple_sensor_modbus_driver
TEMPLATE = lib

#for generating '.lib' library, for static linking use:  CONFIG += staticlib

HEADERS += \
    multiple_sensor_modbus_driver.h

SOURCES += \
    multiple_sensor_modbus_driver.cpp

#-------------------------------------------------
# Make sure output directory for object file and
# executable is in the correct subdirectory
#-------------------------------------------------
macx {
    DESTDIR = mac
    OBJECTS_DIR = mac
    MOC_DIR = mac
    UI_DIR = mac
    RCC_DIR = mac
}
unix: !macx {
    DESTDIR = linux
    OBJECTS_DIR = linux
    MOC_DIR = linux
    UI_DIR = linux
    RCC_DIR = linux
}
win32 {
    DESTDIR = windows
    OBJECTS_DIR = windows
    MOC_DIR = windows
    UI_DIR = windows
    RCC_DIR = windows
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}