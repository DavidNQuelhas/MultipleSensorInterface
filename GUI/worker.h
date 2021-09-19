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
 *   FILE: worker.h - Here are classes declaration and functions prototype       *
 *              related to implementing data transfer(upload/download) of        *
 *              calibration data between a PC and Multiple-Sensor Interface.     *
 *              These instruction are executed as a separated thread to avoid    *
 *              locking the program GUI.                                         *
 ********************************************************************************/

#include <QStandardItemModel>

#define N_LCR_CHANNELS 6  //number of available channels for LCR sensors
#define N_ADC_CHANNELS 4  //number of available channels for the ADC (2 ch are voltmeter, 2 ch are sensor based on resistance change)

#define N_CHARS_CALIB_UNITS 31

#define MAX_N_CHARS_ERROR_MSG 300

typedef struct MultipleSensor_serial_driver_struct MultipleSensor_serial_driver;
typedef struct MultipleSensor_USB_driver_struct MultipleSensor_USB_driver;

#ifndef DEVICE_CALIB_HEADER_DATA_STRUCT_H
#define DEVICE_CALIB_HEADER_DATA_STRUCT_H


 /** 'typedef DeviceCalibHeaderData' ;  'struct Device_Calib_Header_Data_struct' - Structure containing all data of table headers for all calibration tables to the Multiple-Sensor Interface.
   *
   * @b Description
   * Structure containing all data of table headers for all calibration tables to the Multiple-Sensor Interface. This includes the calibration units of all device calibration tables, and calibration units of all counter calibration functions. Also all the parameters/constants that define the calibration functions for counter measurements. Also what calibration tables are active, number of valid lines of each calib table, and what is the sensor channel mode and jumper configuration that is valid for each calib table.
   */
typedef struct Device_Calib_Header_Data_struct {
    char device_calib_units_vector[N_LCR_CHANNELS+N_ADC_CHANNELS][N_CHARS_CALIB_UNITS];
    char counters_calib_units_vector[N_LCR_CHANNELS][N_CHARS_CALIB_UNITS];
    float counters_calib_constants_vector[N_LCR_CHANNELS][4];
    unsigned char calib_table_is_active_bool[N_LCR_CHANNELS+N_ADC_CHANNELS];
    unsigned char number_table_lines[N_LCR_CHANNELS+N_ADC_CHANNELS];
    unsigned char calib_channel_mode_bool[N_LCR_CHANNELS+N_ADC_CHANNELS];   //0-calib is for multiple CHs, 1-calib is for single CH
    char jumper_selection_osc_tuning_range[N_LCR_CHANNELS+N_ADC_CHANNELS]; //only used on the LCR channels, this is channels: 0,1,2,3,4,5
} DeviceCalibHeaderData;

#endif // DEVICE_CALIB_HEADER_DATA_STRUCT_H

#ifndef WORKER_H
#define WORKER_H

#ifndef DATASTRUCT_H
#define DATASTRUCT_H

 /** 'typedef Worker_Arguments' ;  'struct Worker_Arguments_Struct'
   *
   * @b Description
   * Structure containing all info and variable references by the worker thread that will upload/download the Multiple-Sensor Interface calibration data.
   */
typedef struct Worker_Arguments_Struct {
    char communication_is_SERIAL_bool;  //indicates if the Multiple-Sensor device is connected by USB(=0) or RS485_serial(=1)
    DeviceCalibHeaderData *device_calib_header_data_ptr; //needed for the upload of header and tables to the device
    QStandardItemModel *model_tables_device_calib_vector[N_LCR_CHANNELS+N_ADC_CHANNELS];   //needed for the upload of header and tables to the device
    char N_channels;    //integer, usually: N_LCR_CHANNELS+N_ADC_CHANNELS (6+4=10)
    int calib_table_max_rows_to_process_on_single_mode; // #define CALIB_TABLE_MAX_ROWS_TO_PROCESS_ON_SINGLE_MODE 90
    char *log_msg_str_ptr;  //any errors during the operation append a notification to error_log
    char flag_transfer_mode_bool;   //indicates if operation is to download the calib tables ('0') or to upload the calib tables ('1')
    MultipleSensor_serial_driver *serial_driver_LCR_sensors_session_ptr;
    MultipleSensor_USB_driver *driver_LCR_sensors_session_ptr;
} Worker_Arguments;


#define THREAD_WORKER_RET_VAL_OK 1  //must be bigger than zero ('>0').
#define THREAD_WORKER_RET_VAL_FAIL -1   //must be smaller or equal than/to zero ('<=0').

 /** 'typedef Data' ;  'struct Data_Struct'
   *
   * @b Description
   * Structure containing the status data returned by the worker thread (with the messages and error counter).
   */
typedef struct Data_Struct {
    int ret_value;
    int error_counter;
    char first_error_message[MAX_N_CHARS_ERROR_MSG+1];
    char last_error_message[MAX_N_CHARS_ERROR_MSG+1];
    char ret_message_str[MAX_N_CHARS_ERROR_MSG+1];
} Data;

#endif // DATASTRUCT_H
 
#include <QObject>
#include <QMutex>
#include <QWaitCondition>
#include <QDebug>



 /** class Worker - Separate thread for transferring (download or upload) calibration tables between the PC and a Multiple-Sensor Interface device, by using USB and RS485/serial drivers of the Multiple-Sensor Interface.
   *
   * @b Description
   * Instructions to be executed on a separate thread, that execute the operations of transferring (download or upload) calibration tables between the PC and a Multiple-Sensor Interface device, implemented by using the functions of the USB and RS485/serial drivers of the Multiple-Sensor Interface.
   */
class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = 0);
    void Process_Return_Value(int return_value_of_operation, char is_operation_on_header_bool, const char *ret_message_str_in_case_of_success, const char *ret_message_str_in_case_of_error, const char *log_msg_str_ptr_in_case_of_error, int *current_value_progress_bar_ptr, Worker_Arguments *item_args_ptr , Data_Struct *ret_data_ptr, int *error_retry_counter_ptr, int *channel_number_ptr, int *row_number_ptr, float RAW_value, float measurement);

signals:
    void max_progress_range_changed_signal(int max_range);
    void progress_value_changed_signal(int value);
    void progress_text_changed_signal(const QString &text);
    void status_text_changed_signal(const QString &text);
    void finished_signal();
    void result_ready_signal(Data ret_data);
 
public slots:
    void Cancel();    
    void Pause();
    void Set_Pause_Condition(QWaitCondition &pause_condition);
    void Start_Work(const QList<Worker_Arguments> &list);
 
private:
    QMutex m_sync;
    QWaitCondition *m_pause_cond;
    volatile bool m_pause;
    volatile bool m_stop;

};
 
#endif // WORKER_H
