/*********************************************************************************
 *   Multiple Sensor Interface - Connect to device, measure sensors,             *
 *   read and write configurations and calibration tables                        *
 *                                                                               *
 *   Copyright (C) 2021 by David Nuno Quelhas; Lisboa, Portugal;                 *
 *    david.quelhas@yahoo.com ,  https://multiple-sensor-interface.blogspot.com  *
 *    In accordance with 7-b) and 7-c) of GNU-GPLv3, this license requires       *
 *     to preserve/include prior copyright notices with author names, and also   *
 *     add new additional copyright notices, specifically on start/top of source *
 *     code files and on 'About'(or similar) dialog/windows at 'user interfaces',*
 *     on the software and on any 'modified version' or 'derivative work'.       *
 *                                                                               *
 *   This program is free software; you can redistribute it and/or modify it     *
 *   under the terms of the GNU General Public License version 3 as published by *
 *   the Free Software Foundation.                                               *
 *                                                                               *
 *   This program is distributed in the hope that it will be useful, but         *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY  *
 *   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License    *
 *   for more details.                                                           *
 *                                                                               *
 *   You should have received a copy of the GNU General Public License along     *
 *   with this program; if not, write to the                                     *
 *   Free Software Foundation, Inc.,                                             *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.                   *
 *  --------------------                                                         *
 *   FILE: mainwindow.h - Here are the prototypes of the classes and functions   *
 *                  that implement the GUI software of Multiple-Sensor Interface.*
 ********************************************************************************/

//  Here are listed the prototypes of the classes and functions, and also the return codes of the functions.

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QTimer>
#include <QObject>
#include <QSpinBox>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>
#include <QGroupBox>
#include <QCheckBox>
#include <QRadioButton>

#include <QTableView>
#include <QStandardItemModel>

#include <QFile>
#include <QFileDialog>

#include <QProgressBar>

#include "multiple_sensor_USB/multiple_sensor_usb_driver.h"
#include "multiple_sensor_modbus/multiple_sensor_modbus_driver.h"

#include "device_calibrate_sensors_dialog.h"
#include "virtual_calibrate_sensors_dialog.h"

#include "worker_handler.h"

#define VERSION_MULTIPLE_SENSOR_GUI "1.00"       //a string with the version of the Multiple-Sensor Interface GUI, using the format: X.xx , where 'X' is major version (1 or more characters), 'xx' is subversion (2 characters)

#define N_CALIB_CONSTANS 4

#define NL_ASCII 0x0A

//const short LINES_CALIB_TABLE_const = (short) ( (1024.0 *  EEPROM_I2C_SIZE_KBITS ) / ( 64.0*(N_LCR_CHANNELS+N_ADC_CHANNELS) ) );	//each line has 8 bytes (4 bytes the RAW_value, 4 bytes the measurement) , for 512Kbit EEPROM this is 819 lines for each calib table
#define CALIB_UNITS_SIZE_STR 20
#define CALIB_TABLE_MAX_ROWS_TO_PROCESS_ON_MULTI_MODE 12		//when working in multiple sensor mode the device must process 10 channels instead of 1 when in single channel, number of lines of calib table limited by the speed the PIC microprocessor on the device
#define CALIB_TABLE_MAX_ROWS_TO_PROCESS_ON_SINGLE_MODE 32		//number of lines of calib table limited by the speed the PIC microprocessor on the device

//#define MAX_SIZE_VIRTUAL_CALIB_TABLE 200000
#define MAX_SIZE_OF_CHARACTERS_PER_CALIB_TABLE 200000


//Convert_Char_To_Bool(char value) - converts a char variable ( representing a logic value as 0 or 1) to a boolean value
bool Convert_Char_To_Bool(char value);

//Convert_Bool_To_Char(bool value) - converts a bool variable to a char value ( representing a logic value as 0 or 1)
char Convert_Bool_To_Char(bool value);


class MainWindow;


/** class Config_Sensor_Channels_Dialog - Class of the dialog window used for configuring the trigger condition of each sensor channel used for generating its virtual digital variable
   *
   * @b Description
   * Config_Sensor_Channels_Dialog, the class for the dialog used for configuring the trigger/limit value of the RAW or measurement on a sensor channel that will set his corresponding value as true(1) or false(0) used as a digital input associated with each corresponding sensor channel.
   */
class Config_Sensor_Channels_Dialog : public QDialog
{
    Q_OBJECT

public:

    /**
      * explicit Config_Sensor_Channels_Dialog(MultipleSensor_USB_driver *session, MultipleSensor_serial_driver *session_serial, int *m_previous_ch_number_for_saved_config_dialog_ptr, char communication_is_SERIAL_bool)
      *
      * @brief Constructor of base class used on dialog windows for configuring the sensor channels.
      *
      * @param[in] *session Variable with information of a currently used/available USB session on the main window of the Multiple-Sensor Interface.
      * @param[in] *session_serial Variable with information of a currently used/available serial/RS485 session on the main window of the Multiple-Sensor Interface.
      * @param[in,out] *m_previous_ch_number_for_saved_config_dialog_ptr pointer to variable that stores the channel number that was previously selected by the user on 'Config sensor channels dialog'.
      * @param[in] communication_is_SERIAL_bool Is as boolean used to signal if currently the program is communicating with the Multiple-Sensor device through the USB driver(=0) of through the serial/RS485 driver(=1).
      */
    explicit Config_Sensor_Channels_Dialog(MultipleSensor_USB_driver *session, MultipleSensor_serial_driver *session_serial, int *m_previous_ch_number_for_saved_config_dialog_ptr, char communication_is_SERIAL_bool);
    ~Config_Sensor_Channels_Dialog();

    QWidget *config_output_sensors_widget;

private:
    QGridLayout *config_output_sensors_dialog_layout;
    QLabel *select_channel_number_label;
    QSpinBox *select_channel_number_spinBox;
    QWidget *select_channel_widget;
    QGridLayout *select_channel_widget_layout;

    QString default_style_sheet;

    QLabel *select_comparison_activate_sensor_for_outputs_label;
    QComboBox *select_comparison_activate_sensor_for_outputs_comboBox;

    QLabel *trigger_value_label;
    QDoubleSpinBox *trigger_value_doubleSpinBox ;

    QWidget *button_widget;
    QGridLayout *button_widget_layout;
    QPushButton *OK_button;
    QPushButton *cancel_button;

    QLabel *status_label;

    QGridLayout *config_output_sensors_widget_layout;

    MultipleSensor_USB_driver *m_USB_driver_LCR_sensors_session;
    MultipleSensor_serial_driver *m_serial_driver_LCR_sensors_session;
    int *m_previous_ch_number_for_saved_config_dialog_ptr;
    char m_communication_is_SERIAL_bool;

private slots:

    void Cancel_Dialog();


    /**
      * void Config_Sensor_Channels_Dialog::Send_Config_Sensor_Channels()
      *
      * @brief Send to the Multiple-Sensor device the configurations on 'Config Sensor Channels Dialog' inserted/edited by the user.
      *
      * @details This function will send the configurations on 'Config Sensor Channels Dialog' inserted/edited by the user (for selected channel number), to the Multiple-Sensor device,  for this the function will call 'Save_Sensor_Configs(...)'(by USB) or 'Save_Sensor_Configs_Modbus_LCR(...)'(by serial).
      */
    void Send_Config_Sensor_Channels();

    /**
      * void Config_Sensor_Channels_Dialog::Update_Config_Sensor_Channels_Dialog()
      *
      * @brief Update the 'Config Sensor Channels Dialog' with the sensor channel configurations read from the Multiple-Sensor device.
      *
      * @details This function will update the fields 'Comparison used...', 'Trigger value' of the 'Config Sensor Channels' dialog window so they display the current configurations of the Multiple-Sensor device; for this the function will call 'Read_Sensor_Configs(...)'(by USB) or 'Read_Sensor_Configs_Modbus_LCR(...)'(by serial) to read the configurations from the device.
      * This function should be connected to the signal 'valueChanged(int)' of the spinBox 'select_channel_number_spinBox', so every time the user changes the selected channel number on the dialog window, the dialog fields are updated to display the configurations of the currently selected sensor channel.
      */
    void Update_Config_Sensor_Channels_Dialog();

    void Set_Status_Label_Valid();
    void Set_Status_Label_Invalid();
    void Set_Status_Label_Error();

};


 /** class Config_Outputs_Dialog - Class of the dialog window used for configuring the outputs of the sensors board (OUT0, OUT1, OUT2).
   *
   * @b Description
   * Config_Outputs_Dialog is the class for the dialog used for configuring the outputs of the sensors board (OUT0, OUT1, OUT2)
   * Each output is defined by a boolean expression ( using the logical operators '+', '.', '/', and considering priorities of sub-expressions inside brackets '(',')' ), where the digital inputs are the variables : 'M?', 'R?', 'C?', 'K?' . the '?' should be a character between '0' and '9' indicating what is the sensor channel number.
   * 'M?' variables are digital inputs made by using the sensor measurement, 'C?' variables are digital inputs made by using the RAW value of sensor [in Hz or V], 'C' variables are digital inputs made by using the RAW counter value, 'K' variables are digital inputs made by using the counter measurement .
   */
class Config_Outputs_Dialog : public QDialog
{
    Q_OBJECT

public:

    /**
      * explicit Config_Outputs_Dialog::Config_Outputs_Dialog(MultipleSensor_USB_driver *session, MultipleSensor_serial_driver *session_serial, int *previous_output_number_for_saved_config_dialog_ptr, char communication_is_SERIAL_bool)
      *
      * @brief Constructor of the class used on the dialog windows used to configure the digital outputs of Multiple-Sensor Interface device.
      *
      * @param[in] *session Variable with information of a currently used/available USB session on the main window of the Multiple-Sensor Interface.
      * @param[in] *session_serial Variable with information of a currently used/available serial/RS485 session on the main window of the Multiple-Sensor Interface.
      * @param[in,out] *previous_output_number_for_saved_config_dialog_ptr Pointer to variable that stores the output number that was previously selected by the user on 'Config Outputs Dialog'.
      * @param[in] communication_is_SERIAL_bool Is as boolean used to signal if currently the program is communicating with the Multiple-Sensor device through the USB driver(=0) of through the serial/RS485 driver(=1).
      */
    explicit Config_Outputs_Dialog(MultipleSensor_USB_driver *session, MultipleSensor_serial_driver *session_serial, int *previous_output_number_for_saved_config_dialog_ptr, char communication_is_SERIAL_bool);
    ~Config_Outputs_Dialog();

    QWidget *config_outputs_widget;

private:
    QGridLayout *config_outputs_dialog_layout;

    QLabel *select_output_active_level_label_vector[N_DIGITAL_OUT];
    QLineEdit *select_output_active_level_bool_func_vector[N_DIGITAL_OUT];

    QWidget *button_widget;
    QGridLayout *button_widget_layout;
    QPushButton *OK_button;
    QPushButton *cancel_button;

    QLabel *status_label;

    QGridLayout *config_outputs_widget_layout;

    MultipleSensor_USB_driver *m_USB_driver_LCR_sensors_session;
    MultipleSensor_serial_driver *m_serial_driver_LCR_sensors_session;
    int *m_previous_output_number_for_saved_config_dialog_ptr;
    char m_communication_is_SERIAL_bool;

private slots:

    void Cancel_Dialog();

    /**
      * void Config_Outputs_Dialog::Send_Config_Outputs()
      *
      * @brief Send to the Multiple-Sensor device the configurations on 'Config Outputs Dialog' inserted/edited by the user.
      *
      * @details This function will send the configurations on 'Config Outputs Dialog' inserted/edited by the user (for selected channel number) to the Multiple-Sensor device, for this the function will call 'WriteOutputConfig(...)'(by USB) or 'WriteOutputConfig_Modbus_LCR(...)'(by serial).
      */
    void Send_Config_Outputs();

    /**
      * void Config_Outputs_Dialog::Update_Config_Outputs_Dialog()
      *
      * @brief Update the 'Config Outputs Dialog' with the boolean output functions read from the Multiple-Sensor device.
      *
      * @details This function will update the dialog fields named 'Boolean function for output for N?', so they display the current/updated configurations read from Multiple-Sensor device; for this the function will call 'ReadOutputConfig(...)'(by USB) or 'ReadOutputConfig_Modbus_LCR(...)'(by serial) to read configurations from the device.
      * This function should be called after creating the dialog 'Config Outputs Dialog', so the displayed output boolean functions viewed on the dialog window match what was read from Multiple-Sensor device.
      */
    void Update_Config_Outputs_Dialog();


    void Set_Status_Label_Valid();
    void Set_Status_Label_Invalid();
    void Set_Status_Label_Error();
};



 /** class Config_BoardID_Dialog - Dialog window for the configuration of the boardID of a connected Multiple-Sensor device.
   *
   * @b Description
   * Class of the dialog window used for reading and writing the boardID of a Multiple-Sensor Interface device.
   */
class Config_BoardID_Dialog : public QDialog
{
    Q_OBJECT

public:
    /**
      * explicit Config_BoardID_Dialog(MultipleSensor_USB_driver *session, MultipleSensor_serial_driver *session_serial, int *previous_output_number_for_saved_config_dialog_ptr, char communication_is_SERIAL_bool)
      *
      * @brief The constructor of the class of the dialog used for configuring the boardID of a connected Multiple-Sensor device.
      *
      * @param[in] *session Variable with information of a currently used/available USB session on the main window of the Multiple-Sensor Interface.
      * @param[in] *session_serial Variable with information of a currently used/available serial/RS485 session on the main window of the Multiple-Sensor Interface.
      * @param[in] communication_is_SERIAL_bool Is as boolean used to signal if currently the program is communicating with the Multiple-Sensor device through the USB driver(=0) of through the serial/RS485 driver(=1).
      */
    explicit Config_BoardID_Dialog(MultipleSensor_USB_driver *session, MultipleSensor_serial_driver *session_serial, char communication_is_SERIAL_bool);
    ~Config_BoardID_Dialog();

    QWidget *config_boardID_widget;

private:
    QGridLayout *config_boardID_dialog_layout;

    QSpinBox *boardID_spinbox;

    QWidget *button_widget;
    QGridLayout *button_widget_layout;
    QPushButton *set_boardID_button;
    QPushButton *read_boardID_button;
    QPushButton *close_dialog_button;

    QLabel *status_label;
    QLabel *boardID_name_label;
    QGridLayout *config_boardID_widget_layout;

    MultipleSensor_USB_driver *m_USB_driver_LCR_sensors_session;
    MultipleSensor_serial_driver *m_serial_driver_LCR_sensors_session;
    char m_communication_is_SERIAL_bool;

private slots:


    /**
      * void Send_New_BoardID()
      *
      * @brief Save on the Multiple-Sensor device the new board_ID of that specific device/unit.
      *
      * @details This function will save/send a new board_ID number (between 0 and 255, 255 used for broadcast) on a target Multiple-Sensor device.
      * To be able to set/save a new board_ID on a Multiple-Sensor device connected by RS485/serial, you must know the current board_ID of the device and use it on the program to send the message of new board_ID to that device, or alternatively use on the program the '255'(broadcast) board_ID and ensure only one Multiple-Sensor device is connected on the RS485/serial cable.
      */
    void Send_New_BoardID();

    /**
      * void Read_BoardID()
      *
      * @brief Read from a Multiple-Sensor device the board_ID of that specific device/unit
      *
      * @details This function will read the board_ID number (between 0 and 255, 255 used for broadcast) from a target Multiple-Sensor device.
      * To be able to read a board_ID from a Multiple-Sensor device connected by RS485/serial, you must know the current board_ID of the device and use it on the program to send the message of read board_ID to that device, or alternatively use on the program the '255'(broadcast) board_ID and ensure only one Multiple-Sensor device is connected on the RS485/serial cable.
      */
    void Read_BoardID();

    void Close_Dialog();
    void Set_Status_Label_Error();
    void Set_Status_Label_OK();
};



 /** class Transfer_Calib_Table_Dialog - Dialog window for showing the progress of upload/download of calibration data between PC and Multiple-Sensor device.
   *
   * @b Description
   * Class of the dialog window used for showing to the user the progress of the transfer (download or upload) between a PC and a Multiple-Sensor device, of calibration tables (including the table headers) and also the calibration parameters for the counter calibration functions.
   */
class Transfer_Calib_Table_Dialog : public QDialog
{
    Q_OBJECT

public:
    /**
      * explicit Transfer_Calib_Table_Dialog(QWidget *parent, Worker_Arguments *worker_args_ptr, char flag_transfer_mode_bool)
      *
      * @brief The constructor of the class of the dialog used for showing the progress of upload/download of calibration data between PC and Multiple-Sensor device.
      *
      * @param[in] *parent - The main widget/window where this dialog belongs (relevant for deleting instance of this class when no longer required).
      * @param[in] *worker_args_ptr - A variable of type 'Worker_Arguments' (structure) with all the required data(info and references (of variables) required for setting up an instance of 'Worker_Handler' for then executing the upload/download between PC and device
      * @param[in] flag_transfer_mode_bool - A boolean variable (of type 'char', '0' - false, '1' - true) used to request what direction is the data transfer, this is:  '0' indicates download (PC reads the calib tables/data from the device), '1' indicates upload (PC sends new calib tables/data to the device).
      */
    explicit Transfer_Calib_Table_Dialog(QWidget *parent, Worker_Arguments *worker_args_ptr, char flag_transfer_mode_bool);
    ~Transfer_Calib_Table_Dialog();

    Data ret_data_worker;

public slots:

    /**
      * void Start_Transfer_Calib_Table()
      *
      * @brief After user clicks the button (upload or download) it starts the worker thread that does the upload or download
      *
      * @details The 'Start_Transfer_Calib_Table' is the function called after the user clicks the button (upload or download),  and it will start the worker thread that does the upload or download of calibration data between PC and device.
      */
    void Start_Transfer_Calib_Table();

    /**
      * void Data_Ready(const Data data)
      *
      * @brief Function to save status data/info returned by the worker thread (with the messages and error counter), to be called just after the worker thread finishes the upload/download.
      *
      * @details The 'Data_Ready' function is set to be called immediately after the worker thread finishes the upload or download of calibration data between PC and device, to save status data/info returned by the worker thread (with the messages and error counter).
      */
    void Data_Ready(const Data data);

    /**
      * void Call_On_Process_Finished()
      * @brief Function to update this dialog window with info/status about the completion and success(and any errors) of the upload/download.
      *
      * @details The 'Call_On_Process_Finished' function updates this dialog window with info/status about the completion and success(and any errors) of the upload/download of calibration tables/data between the PC and the device.
      */
    void Call_On_Process_Finished();


private:
    Worker_Handler *worker;

    /**
      * void Data_Copy(Data *data_dest, Data const &data_src)
      *
      * @brief Copy the content of a variable of the type 'Data'.
      *
      * @details Copy the content of variable of the type 'Data' ('Data' is used passing info/data between the worker thread and the MainWindow about the status and/or errors of the upload/download process).
      */
    void Data_Copy(Data *data_dest, Data const &data_src);

    Worker_Arguments *m_worker_args_ptr;
    char m_flag_transfer_mode_bool;
    int m_max_N_steps_progress_bar;
    int m_current_progress_bar;


    QDialog *progress_dialog;
    QGridLayout *progress_dialog_layout;

    QWidget *title_widget;
    QGridLayout *title_widget_layout;

    QWidget *status_widget;
    QGridLayout *status_widget_layout;
    QLabel *title_label;
    QProgressBar *progress_bar;
    QLabel *process_label;
    QLabel *status_label;

    QWidget *button_widget;
    QGridLayout *button_widget_layout;

    QPushButton *pause_button;
    QPushButton *stop_button;
    QPushButton *start_button;

    QPushButton *close_button;

};



namespace Ui {
class MainWindow;
}


/** class MainWindow - main window of the Multiple-Sensor Interface GUI application.
   *
   * @b Description
   * Class of the main window of the Multiple-Sensor Interface GUI(Graphical User Interface) application.
   */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //variables used with the measurement of the sensors with the device calibration
    QStandardItemModel *model_tables_device_calib_vector[N_LCR_CHANNELS+N_ADC_CHANNELS];
    //QModelIndex model_tables_index;
    float device_calib_sensors_measurement_vector[N_LCR_CHANNELS+N_ADC_CHANNELS];
    DeviceCalibHeaderData device_calib_header_data;
    DeviceCalibHeaderData downloaded_device_calib_header_data;

    //variables used with the measurement of the LCR sensors with the virtual calibration
    float virtual_calib_LCR_sensors_measurement_vector[N_LCR_CHANNELS];
    QStandardItemModel *model_tables_virtual_calib_vector[N_LCR_CHANNELS+N_ADC_CHANNELS];
    //QModelIndex model_tables_index;    
    char virtual_calib_units_vector[N_LCR_CHANNELS+N_ADC_CHANNELS][N_CHARS_CALIB_UNITS];
    unsigned char virtual_calib_channel_mode_bool_vector[N_LCR_CHANNELS+N_ADC_CHANNELS];
    char virtual_calib_jumper_selection_osc_tuning_range_vector[N_LCR_CHANNELS+N_ADC_CHANNELS];

    //variables used with the measurement of the ADC sensors with the virtual calibration
    float virtual_calib_ADC_sensors_measurement_vector[N_ADC_CHANNELS];

    //variable used to store the calibration of the counters device calibration
    counters_calib counters_device_calib;

    //variable used to store the calibration of the counters virtual calibration
    counters_calib counters_virtual_calib;

    //'INTERVAL_MSEC_TIMER_READ_SENSOR' - time interval in milliseconds (ms) between reading from the Multiple-Sensor device the sensor channel values / measurements. Recommended INTERVAL_MSEC_TIMER_READ_SENSOR >= 500 so the device has time to process the various read commands in case of 'multi' channel mode
    static const int INTERVAL_MSEC_TIMER_READ_SENSOR=500;  // 500 ms

private:
    Ui::MainWindow *ui;
    QGridLayout *Sensors_Values_groupBox_layout;
    QLabel *sensors_names_display_vector[N_LCR_CHANNELS+N_ADC_CHANNELS+2];
    QLabel *sensors_values_display_vector[N_LCR_CHANNELS+N_ADC_CHANNELS+2]; //array with the sensor values to be shown (RAW or measurement)

    QLabel *space_label;
    QLabel *long_space_label;

    QGridLayout *virtual_calib_Sensors_Values_groupBox_layout;
    QGridLayout *counters_virtual_calib_Sensors_Values_groupBox_layout;
    QLabel *virtual_calib_sensors_names_display_vector[N_LCR_CHANNELS+N_ADC_CHANNELS+2];
    QLabel *virtual_calib_sensors_values_display_vector[N_LCR_CHANNELS+N_ADC_CHANNELS+2];    //array with the sensor measurement values to be shown, obtained using the virtual calibration tables
    QLabel *counters_virtual_calib_sensors_names_display_vector[N_LCR_CHANNELS+1];
    QLabel *counters_virtual_calib_sensors_values_display_vector[N_LCR_CHANNELS+1];     //array with the sensor counter measurement values to be shown, obtained using the virtual calibration constants/function

    QGridLayout *Outputs_Values_groupBox_layout;
    QLabel *outputs_names_display_vector[N_DIGITAL_OUT];
    QLabel *outputs_values_display_vector[N_DIGITAL_OUT];

    //variables used for the display graphic view of the sensors
    QGridLayout *sensors_graphic_view_groupBox_layout;
    QLabel *sensors_graphic_view_names_display_vector[N_LCR_CHANNELS+N_ADC_CHANNELS];
    QDoubleSpinBox *sensors_graphic_view_select_min_vector[N_LCR_CHANNELS+N_ADC_CHANNELS];
    QDoubleSpinBox *sensors_graphic_view_select_max_vector[N_LCR_CHANNELS+N_ADC_CHANNELS];
    QProgressBar *sensors_progress_bar_vector[N_LCR_CHANNELS+N_ADC_CHANNELS];

    QTimer *timer_read_sensors;

    // ----- Declarations for the Toolbar of the Multiple Sensor Interface application -----
    QAction *calibrate_device_sensors_action;
    QAction *config_sensors_action;
    QAction *config_outputs_action;
    QAction *virtual_calibrate_sensors_action;
    QAction *config_boardID_action;
    // ------------------------------------------------------------------------

    Config_Sensor_Channels_Dialog *config_sensors_dialog_obj;
    Config_Outputs_Dialog *config_outputs_dialog_obj;
    Calibrate_Sensors_Dialog *calibrate_device_sensors_dialog_obj;
    Calibrate_Sensors_Dialog *virtual_calibrate_sensors_dialog_obj;
    Config_BoardID_Dialog *config_boardID_dialog_obj;


    MultipleSensor_USB_driver m_USB_driver_LCR_sensors_session;
    MultipleSensor_serial_driver m_serial_driver_LCR_sensors_session;

    int previous_ch_number_for_saved_calib_dialog;
    int previous_ch_number_for_saved_config_dialog;
    int previous_output_number_for_saved_config_dialog;
    int previous_ch_number_for_saved_device_calib_dialog;
    int previous_ch_number_for_saved_virtual_calib_dialog;

    QFont *font_display_sensors;

    int select_CH_mode_comboBox_previous_value;
    int select_CH_spinBox_previous_value;

    int frequency_sensors_vector[N_LCR_CHANNELS];

    float measurements_sensor_vector[N_LCR_CHANNELS+N_ADC_CHANNELS];
    long int counters_sensors_vector[N_LCR_CHANNELS];
    float counters_sensors_measurements_vector[N_LCR_CHANNELS];

    float LCR_sensors_values_vector[N_LCR_CHANNELS], ADC_sensors_values_vector[N_ADC_CHANNELS];

    QString error_log;

private slots:

    /**
      * void Connect_LCR_Board()
      *
      * @brief Connect this program to the Multiple-Sensor Interface (by USB or by RS485/serial).
      *
      * @details Connect this program to the Multiple-Sensor Interface by USB or by RS485/serial, it opens a connection through a Multiple-Sensor Interface driver library ('MultipleSensor_USB_driver.lib' or 'MultipleSensor_serial_driver.lib').
      * Also updates the items on the main window to display the current connection status to the Multiple-Sensor device.
      */
    void Connect_LCR_Board();

    /**
      * void Update_Sensors_Display()
      *
      * @brief Update the current visible values/measurements for all active/requested sensor channels of the Multiple-Sensor Interface.
      *
      * @details Update the current visible values or measurements of the sensor channels, depending what option is selected 'RAW Values' or 'Measured Values', for all active/requested (defined by 'multi' or 'single' channel mode) sensor channels of the Multiple-Sensor Interface.
      */
    void Update_Sensors_Display();

    /**
      * void Update_Virtual_Calibration_Measurements_Display()
      *
      * @brief Update the current visible Virtual Measurements for the sensor channels of the Multiple-Sensor Interface.
      *
      * @details Update the visible 'virtual' measurements of the sensor channels, the virtual measurements are the measurements for the current/last received values from Multiple-Sensor device, calculated by the PC Multiple-Sensor GUI app using a calibration table that is stored on PC along with the app.
      */
    void Update_Virtual_Calibration_Measurements_Display();

    /**
      * void Update_Counters_Virtual_Calibration_Measurements_Display()
      *
      * @brief Update the current visible Virtual Counter Measurements for the sensor channels of the Multiple-Sensor Interface.
      *
      * @details Update the visible 'virtual' counter measurements of the sensor channels, the virtual counter measurements are the measurements for the current/last received counter values from Multiple-Sensor device, calculated by the PC Multiple-Sensor GUI app using a counter calib function (Measured_total = C3*(COUNTER^3) + C2*(COUNTER^2) + C1*COUNTER) + C0) with 4 parameters/constants used as the calibration for the counter measurements, that is stored on PC along with the app.
      */
    void Update_Counters_Virtual_Calibration_Measurements_Display();


    /**
      * void Call_Update_Sensors_Display()
      *
      * @brief First check currently selected user option of 'multi' or single' channel mode, then call 'Update_Sensors_Display()'.
      *
      * @details The function will first check if currently selected user option of 'multi' or single' channel mode is different of the last read configuration from Multiple-Sensor device, in case is different that read now the channel mode configurations from Multiple-Sensor device and update accordingly the GUI items about 'multi' or 'single' channel mode.
      * Then finally call the function 'Update_Sensors_Display()'.
      */
    void Call_Update_Sensors_Display();



    /**
      * void Change_Sensors_Read_Mode()
      *
      * @brief Checks if the user selected 'Continuous Read' checkBox, and configures accordingly the 'timer_read_sensors' timer.
      *
      * @details Checks the checkBox 'Continuous Read', if the user selected continuous read then it activates the 'timer_read_sensors' timer for reading sensor channel values/measurements every time interval 'INTERVAL_MSEC_TIMER_READ_SENSOR'.
      */
    void Change_Sensors_Read_Mode();


    /**
      * void Disable_Virtual_Calib_Measurements() - Disables Virtual Calibration, typically called automatically when the user enables the selected the 'Measured Values' option for the 'Read Type'.
      *
      * Disables the checkBox 'enable_virtual_calib_checkBox' thus disabling the Virtual Calibration, typically called automatically when the user enables the selected the 'Measured Values' option for the 'Read Type', since Virtual Calibration is only possible to do when the application is reading 'RAW Values' from the device.
      */
    void Disable_Virtual_Calib_Measurements();

    /**
        * void EnableRAWValues() - Enables 'RAW Values' option for the 'Read Type', typically called automatically when the user enables the 'Virtual Calibration' tab.
        *
        * Disables the 'measured_radioButton' and enables the 'RAW_radioButton', typically called automatically when the user enables the 'Virtual Calibration' tab, since Virtual Calibration requires reading 'RAW Values' from the device.
        */
    void EnableRAWValues();

    /**
        * void Create_Calibrate_Device_Sensors_Dialog() - Creates/Display a new 'Device_Calibrate_Sensors_Dialog' dialog window, fills the calibration table on the dialog
        *
        * Creates/Display a new 'Device_Calibrate_Sensors_Dialog' dialog window, fills the calibration table shown on the dialog with data from the corresponding 'QStandardItemModel' entry on 'model_tables_device_calib_vector'. Typically called after clicking on related button of the main window toolbar.
        */
    void Create_Calibrate_Device_Sensors_Dialog();

    /**
        * void Create_Config_Sensors_Dialog() - Creates/Display the 'Config_Sensor_Channels_Dialog' dialog window
        *
        * Creates/Display the 'Config_Sensor_Channels_Dialog' dialog window, typically called after clicking on related button of the main window toolbar. That dialog window is used for configuring the trigger condition of each sensor channel used for generating its virtual digital variable.
        */
    void Create_Config_Sensors_Dialog();

    /**
        * void Create_Config_Outputs_Dialog() - Creates/Display the 'Config_Outputs_Dialog' dialog window
        *
        * Creates/Display the 'Config_Outputs_Dialog' dialog window, typically called after clicking on related button of the main window toolbar. That dialog window is used for configuring the bool(logical) function used for defining the output 'OUT' digital signal of the Multiple Sensor Interface device.
        */
    void Create_Config_Outputs_Dialog();


    /**
        * void Create_Virtual_Calibrate_Sensors_Dialog() - Creates/Display a new 'Virtual_Calibrate_Sensors_Dialog' dialog window, fills the calibration table on the dialog
        *
        * Creates/Display a new 'Virtual_Calibrate_Sensors_Dialog' dialog window, fills the calibration table shown on the dialog with data from the corresponding 'QStandardItemModel' entry on 'model_tables_virtual_calib_vector'. Typically called after clicking on related button of the main window toolbar.
        */
    void Create_Virtual_Calibrate_Sensors_Dialog();

    /**
        * void Create_Config_BoardID_Dialog() - Creates/Display a new 'Config_BoardID_Dialog' dialog window,
        *
        * Creates/Display a new 'Config_BoardID_Dialog' dialog window, typically called after clicking on related button of the main window toolbar. That dialog window is used for configuring the board_ID of the device.
        */
    void Create_Config_BoardID_Dialog();

    /**
        * void ModeMultipleCH_Changed() - When the user selects 'multi' sensor channel mode it disables the 'select_CH_mode_comboBox' comboBox
        *
        * When the user selects 'multi' sensor channel mode it disables the 'select_CH_mode_comboBox' comboBox, that only should work for selecting a sensor channel on 'single' sensor channel mode.
        */
    void ModeMultipleCH_Changed();

    /**
        * void SaveModeMultipleCH() - Saves on the Multiple-Sensor device the 'multi' or 'single' sensor channel mode configuration selected by the user.
        *
        * Saves on the Multiple-Sensor device the 'multi' or 'single' sensor channel mode configuration selected by the user. Called when the user click the 'Save' button of the 'Select multiple CH or single CH' groupBox.
        */
    void SaveModeMultipleCH();

    /**
        * void Reset_Counters() - Resets the sensor counters of the Multiple Sensor Interface device.
        *
        * Resets the sensor counters of the Multiple Sensor Interface device. Typically called after clicking on the button 'Reset Counters Now'.
        */
    void Reset_Counters();

    /**
        * void SetConnectioStatusLabel_OK() - Sets/Displays the 'Connection  Status' groupBox of the application, to 'OK' state (with green color).
        *
        * Sets/Displays the 'Connection  Status' groupBox of the application, to 'OK' state (with green color).
        */
    void SetConnectioStatusLabel_OK();

    /**
        * void SetConnectioStatusLabel_ERROR() - Sets/Displays the 'Connection  Status' groupBox of the application, to 'ERROR' state (with red color).
        *
        * Sets/Displays the 'Connection  Status' groupBox of the application, to 'ERROR' state (with red color).
        */
    void SetConnectioStatusLabel_ERROR();

    /**
        * void Update_Sensors_Graphic_View() - Calculates and updates/display the bar views of sensor channels.
        *
        * Using the 'RAW values' of the sensor channels and also the 'min_value', 'max_value' selected by the user, if calculates the value and updates/display the bar views of sensor channels.
        */
    void Update_Sensors_Graphic_View();

    /**
        * void Check_Max_Graph_View(int CH_number) - Updates the minimum allowed value of 'max_value' is bigger than the current value of 'min_value' of the bar views of sensor channels.
        *
        * Updates the minimum allowed value of 'max_value' is bigger than the current value of 'min_value' of the bar views of sensor channels.
        */
    void Check_Max_Graph_View(int CH_number);

    /**
        * void Check_Min_Graph_View(int CH_number) - Updates the maximum allowed value of 'min_value' is smaller than the current value of 'max_value' of the bar views of sensor channels.
        *
        * Updates the maximum allowed value of 'min_value' is smaller than the current value of 'max_value' of the bar views of sensor channels.
        */
    void Check_Min_Graph_View(int CH_number);

    /**
      * void About()
      *
      * @brief Shows the 'About' dialog window with information about the project and the software licenses.
      */
    void About();

    /**
      * void Show_Error_Log()
      *
      * @brief Shows the 'ERROR LOG' dialog window with information about errors when sending/receiving data between PC and Multiple-Sensor device.
      */
    void Show_Error_Log();

    /**
      * void Show_User_Guide()
      *
      * @brief Opens the 'html' user guide on the web browser.
      */
    void Show_User_Guide();

    /**
      * void Import_Device_Calibrations()
      *
      * @brief Imports/Reads the device calibrations of Multiple-Sensor Interface from a text file(name and path) selected by the user, and saves its content on all 'QStandardItemModel' entries of 'model_tables_device_calib_vector'.
      */
    void Import_Device_Calibrations();

    /**
      * void Export_Device_Calibrations()
      *
      * @brief Exports/Saves the device calibrations of Multiple-Sensor Interface on all 'QStandardItemModel' entries of 'model_tables_device_calib_vector' to a text file(name and path) selected by the user.
      */
    void Export_Device_Calibrations();

    /**
      * void Import_Virtual_Calibrations()
      *
      * @brief Imports/Reads the virtual calibrations of Multiple-Sensor Interface from a text file(name and path) selected by the user, and saves its content on all 'QStandardItemModel' entries of 'model_tables_device_calib_vector'.
      */
    void Import_Virtual_Calibrations();

    /**
      * void Export_Virtual_Calibrations()
      *
      * @brief Exports/Saves the virtual calibrations of Multiple-Sensor Interface on all 'QStandardItemModel' entries of 'model_tables_virtual_calib_vector' to a text file(name and path) selected by the user.
      */
    void Export_Virtual_Calibrations();

    /**
      * void Upload_Device_Calib_Table()
      *
      * @brief Uploads/Saves to a Multiple-Sensor device the calibration tables, parameters, headers, from all 'QStandardItemModel' entries of 'model_tables_device_calib_vector'.
      */
    void Upload_Device_Calib_Table();

    /**
      * void Download_Device_Calib_Table()
      *
      * @brief Downloads/Reads from a Multiple-Sensor device the calibration tables, parameters, headers, to all 'QStandardItemModel' entries of 'model_tables_device_calib_vector'.
      */
    void Download_Device_Calib_Table();

};


#endif // MAINWINDOW_H
