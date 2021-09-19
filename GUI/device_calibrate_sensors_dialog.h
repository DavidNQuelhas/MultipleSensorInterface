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
 *   FILE: device_calibrate_sensors_dialog.h - Here is                           *
 *     'Device_Calibrate_Sensors_Dialog' class declaration and function          *
 *     prototypes, used for view/edit of Multiple-Sensor device calibration      *
 *     tables of the various sensor channels.                                    *
 ********************************************************************************/

#ifndef DEVICE_CALIBRATE_SENSORS_DIALOG_H
#define DEVICE_CALIBRATE_SENSORS_DIALOG_H

#include <QCheckBox>

#include "calibrate_sensors_dialog.h"
#include "worker_handler.h"


/** class Device_Calibrate_Sensors_Dialog - Class of the dialog window used for configuring the device calibrations, that are used by Multiple-Sensor device to calculate measurements.
   *
   * @b Description
   * Class of the dialog window used for configuring the device calibrations. The device calibrations are saved on an EEPROM memory on the Multiple-Sensor Interface device, and are used by the device to calculate the sensor measurements.
   * These are a 2 column table(for LCR channels and ADC channels) that translates a RAW value of the sensor (frequency, voltage) to a sensor measurement , and 4 float constants used on a function(counters of LCR/frequency channels) that translates a RAW_counter_value of the sensor (number of counts/cycles) to a counter measurement.
   */
class Device_Calibrate_Sensors_Dialog : public Calibrate_Sensors_Dialog
{
     Q_OBJECT

    //inherits from class Calibrate_Sensors_Dialog
public:
    /**
      * explicit Device_Calibrate_Sensors_Dialog(int *previous_ch_number_for_saved_device_calib_dialog_ptr, DeviceCalibHeaderData *device_calib_header_ptr, QStandardItemModel **model_tables_sensors_calib_vector_ptr, counters_calib *counters_calib_ptr)
      *
      * The constructor of the class used for configuring the device calibration tables of measurements on LCR/frequency/ADC sensor channels , and configuring the constants of the device calibration function of counter measurements on frequency sensor channels.
      * @param[in,out] *previous_ch_number_for_saved_device_calib_dialog_ptr Pointer to variable that stores the selected channel number that was previously selected by the user on 'Calibrate_Sensors_Dialog'.
      * @param[in,out] *device_calib_header_ptr Pointer to structure containing all data of table headers for all calibration tables.
      * @param[in,out] **model_tables_calib_vector_ptr Pointer to array(vector) where are stored the calibration tables for all the sensor channels
      * @param[in,out] *counters_calib_ptr Pointer to structure ('counters_calib') where are stored the constants of the calibration function used to calculate the counter measurements
      */
    explicit Device_Calibrate_Sensors_Dialog(int *previous_ch_number_for_saved_device_calib_dialog_ptr, DeviceCalibHeaderData *device_calib_header_ptr, QStandardItemModel **model_tables_sensors_calib_vector_ptr, counters_calib *counters_calib_ptr);
    ~Device_Calibrate_Sensors_Dialog();

private:
    char (*m_sensors_calib_units_vector_ptr)[N_CHARS_CALIB_UNITS];


    QWidget *number_valid_table_lines_widget;
    QGridLayout *number_valid_table_lines_widget_layout;
    QLabel *number_valid_table_lines_label;
    QSpinBox *number_valid_table_lines_box;

    QWidget *calib_table_is_active_widget;
    QGridLayout *calib_table_is_active_widget_layout;
    QLabel *calib_table_is_active_label;
    QCheckBox *calib_table_is_active_checkbox;

    DeviceCalibHeaderData *device_calib_header_ptr;

public slots:

    /**
      * void Save_Device_Sensors_Calibrations()
      *
      * @brief Saves calibration data of currently selected sensor channel from 'Device_Calibrate_Sensors_Dialog' dialog to the correspondent program variables.
      *
      * @details This function calls the 'Save_Sensors_Calibrations()' from parent class, and also saves other information of the device calibration table (content of 'DeviceCalibHeaderData' structure), namely: the channel mode (saved to 'calib_channel_mode_bool[]'), jumper configuration (saved to 'jumper_selection_osc_tuning_range[]'), active table state (saved to 'calib_table_is_active_bool[]'), number of valid table lines (saved to 'number_table_lines[]') .
      */
    void Save_Device_Sensors_Calibrations();


    /**
      * void Update_Device_Calibrate_Sensors_Dialog()
      *
      * @brief Reads sensor calibration data stored on the program variables, and sets/updates items visible on dialog 'Device_Calibrate_Sensors_Dialog'.
      *
      * @details This function calls the 'Update_Sensors_Calibrations()' from parent class, and also updates other information of the currenlty visible device calibration table (content of 'DeviceCalibHeaderData' structure), namely: the channel mode (read from 'calib_channel_mode_bool[]'), jumper configuration (read from 'jumper_selection_osc_tuning_range[]'), active table state (read from 'calib_table_is_active_bool[]'), number of valid table lines (read from 'number_table_lines[]').
      */
    void Update_Device_Calibrate_Sensors_Dialog();


    void Increase_Number_Valid_Lines();
    void Device_Calib_Add_New_Row();
    void Calib_Channel_Mode_Changed();
    void Number_Valid_Table_Lines_Changed();

};

#endif // DEVICE_CALIBRATE_SENSORS_DIALOG_H
