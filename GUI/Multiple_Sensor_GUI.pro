#-------------------------------------------------
#
# Project created by QtCreator 2014-06-21T17:46:24
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Multiple_Sensor_GUI
TEMPLATE = app

QMAKE_LFLAGS += /INCREMENTAL:NO

SOURCES += main.cpp\
        mainwindow.cpp \
    worker.cpp \
    worker_handler.cpp \
    about_dialog.cpp \
    calibrate_sensors_dialog.cpp \
    device_calibrate_sensors_dialog.cpp \
    virtual_calibrate_sensors_dialog.cpp

HEADERS  += mainwindow.h \
    worker.h \
    worker_handler.h \
    multiple_sensor_modbus_driver.h \
    multiple_sensor_usb_driver.h \
    about_dialog.h \
    calibrate_sensors_dialog.h \
    device_calibrate_sensors_dialog.h \
    virtual_calibrate_sensors_dialog.h \
    multiple_sensor_USB/multiple_sensor_usb_driver.h \
    multiple_sensor_modbus/multiple_sensor_modbus_driver.h

FORMS    += mainwindow.ui \
    about_dialog.ui

#-------------------------------------------------
# Add the Signal11's hidapi library that was
# created
#-------------------------------------------------
macx: LIBS += -L$$PWD/HIDAPI/mac -lHIDAPI
win32: LIBS += -L$$PWD/HIDAPI/windows -lHIDAPI
unix: !macx: LIBS += -L$$PWD/HIDAPI/linux -lHIDAPI

#-------------------------------------------------
# Make sure to add the required libraries or
# frameoworks for the hidapi to work depending on
# what OS is being used
#-------------------------------------------------
macx: LIBS += -framework CoreFoundation -framework IOkit
win32: LIBS += -lSetupAPI
unix: !macx: LIBS += -lusb-1.0

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/multiple_sensor_USB/windows -lmultiple_sensor_usb_driver
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/multiple_sensor_USB/windows -lmultiple_sensor_usb_driverd
else:unix: LIBS += -L$$PWD/multiple_sensor_USB/linux -lmultiple_sensor_usb_driver

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/multiple_sensor_USB/windows/multiple_sensor_usb_driver.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/multiple_sensor_USB/windows/multiple_sensor_usb_driverd.lib
else:unix: PRE_TARGETDEPS += $$PWD/multiple_sensor_USB/linux/libmultiple_sensor_usb_driver.a


#LINK WITH SERIAL PORT DRIVER
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/multiple_sensor_modbus/windows -lmultiple_sensor_modbus_driver
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/multiple_sensor_modbus/windows -lmultiple_sensor_modbus_driverd
else:unix: LIBS += -L$$PWD/multiple_sensor_modbus/linux -lmultiple_sensor_modbus_driver

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/multiple_sensor_modbus/windows/multiple_sensor_modbus_driver.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/multiple_sensor_modbus/windows/multiple_sensor_modbus_driverd.lib
else:unix: PRE_TARGETDEPS += $$PWD/multiple_sensor_modbus/linux/libmultiple_sensor_modbus_driver.a

RESOURCES += \
    multiple_sensor_resources.qrc

OTHER_FILES +=
