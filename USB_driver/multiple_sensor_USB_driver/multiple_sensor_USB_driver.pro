#--------------------------------------------------------------------------------------------------
# Copyright (C) 2021 David Nuno Quelhas. LGPL License 3.0 (GNU).  
# David Nuno Quelhas; Lisboa, Portugal.  david.quelhas@yahoo.com ,                                  
# https://multiple-sensor-interface.blogspot.com                                                    
#                                                                                                   
# Multi-sensor interface, low-cost RTU. Modbus RS485/RS232 Device Driver.                           
#
# This library is free software; you can redistribute it and/or modify it under the terms of the    
# GNU Lesser General Public version 3.0 License as published by the Free Software Foundation.      
# This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;         
# without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.         
# See the GNU Lesser General Public License for more details.                                       
# You should have received a copy of the GNU Lesser General Public License along with this library. 
#--------------------------------------------------------------------------------------------------

QT       += core

QT       -= gui

TARGET = multiple_sensor_USB_driver
TEMPLATE = lib

#for generating '.lib' library, for static linking use:  CONFIG += staticlib

SOURCES += \
    multiple_sensor_usb_driver.c

HEADERS  += \
    multiple_sensor_usb_driver.h

FORMS    +=


#-------------------------------------------------
# Add the Signal11's hidapi library that was
# created
#-------------------------------------------------
macx: LIBS += -L../HIDAPI/mac -lHIDAPI
win32: LIBS += -L../HIDAPI/windows -lHIDAPI
unix: !macx: LIBS += -L../HIDAPI/linux -lHIDAPI

#-------------------------------------------------
# Make sure to add the required libraries or
# frameoworks for the hidapi to work depending on
# what OS is being used
#-------------------------------------------------
macx: LIBS += -framework CoreFoundation -framework IOkit
win32: LIBS += -lSetupAPI
unix: !macx: LIBS += -lusb-1.0

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

