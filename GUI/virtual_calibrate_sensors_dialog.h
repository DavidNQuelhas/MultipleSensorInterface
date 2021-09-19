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
 *   FILE: virtual_calibrate_sensors_dialog.h - Here is                          *
 *                    'Virtual_Calibrate_Sensors_Dialog' class declaration and   *
 *                    function prototypes, used for view/edit of Multiple-Sensor *
 *                    virtual calibration tables of the various sensor channels. *
 ********************************************************************************/

#ifndef VIRTUAL_CALIBRATE_SENSORS_DIALOG_H
#define VIRTUAL_CALIBRATE_SENSORS_DIALOG_H

#include "calibrate_sensors_dialog.h"


/** class Virtual_Calibrate_Sensors_Dialog - Class of the dialog window used for configuring the virtual calibrations, that are used by the Multiple-Sensor software (PC) to calculate sensor measurements.
   *
   * @b Description
   * Class of the dialog window used for configuring the virtual calibrations. The virtual calibrations are only available to use on the PC, not on the sensors board. The virtual calibration are just like the device calibrations, they translate a RAW value of the sensor (frequency, voltage, or number of counts/cycles) to a sensor measurement or counter measurement.
   * These are a 2 column table(for LCR channels and ADC channels) that translates a RAW value of the sensor (frequency, voltage) to a sensor measurement , and 4 float constants used on a function(counters of LCR/frequency channels) that translates a RAW_counter_value of the sensor (number of counts/cycles) to a counter measurement.
   */
class Virtual_Calibrate_Sensors_Dialog : public Calibrate_Sensors_Dialog
{
    Q_OBJECT

    //inherits from class Calibrate_Sensors_Dialog
public:

    /**
      * explicit Virtual_Calibrate_Sensors_Dialog(int *previous_ch_number_for_saved_virtual_calib_dialog_ptr,char (*virtual_calib_units_vector_ptr)[N_CHARS_CALIB_UNITS], QStandardItemModel **model_tables_virtual_calib_vector_ptr, counters_calib *counters_virtual_calib_ptr, unsigned char *virtual_calib_channel_mode_bool_vector_ptr, char *virtual_calib_jumper_selection_osc_tuning_range_vector_ptr)
      *
      * The constructor of the class used for configuring the virtual calibration tables of measurements on LCR/frequency/ADC sensor channels , and configuring the constants of virtual calibration function of counter measurements on frequency sensor channels. 'virtual calibration' means the measurements are calculated on the computer program by applying the 'virtual calibration' on the received data.
      * @param[in,out] *previous_ch_number_for_saved_calib_dialog_ptr Pointer to variable that stores the selected channel number that was previously selected by the user on 'Calibrate_Sensors_Dialog'.
      * @param[in,out] (*calib_units_vector_ptr)[N_CHARS_CALIB_UNITS] Pointer to array(vector) where are stored the calibration units for all the sensor channels (each entry of this array is a pointer to a C string).
      * @param[in,out] **model_tables_calib_vector_ptr Pointer to array(vector) where are stored the calibration tables for all the sensor channels
      * @param[in,out] *counters_calib_ptr Pointer to structure ('counters_calib') where are stored the constants of the calibration function used to calculate the counter measurements
      * @param[in,out] *virtual_calib_channel_mode_bool_vector_ptr Pointer to array(vector) where are stored the channel mode of the virtual calibrations for all the sensor channels
      * @param[in,out] *virtual_calib_jumper_selection_osc_tuning_range_vector_ptr Pointer to array(vector) where are stored the jumper configuration of the virtual calibrations for all the sensor channels
        */
    explicit Virtual_Calibrate_Sensors_Dialog(int *previous_ch_number_for_saved_virtual_calib_dialog_ptr,char (*virtual_calib_units_vector_ptr)[N_CHARS_CALIB_UNITS], QStandardItemModel **model_tables_virtual_calib_vector_ptr, counters_calib *counters_virtual_calib_ptr, unsigned char *virtual_calib_channel_mode_bool_vector_ptr, char *virtual_calib_jumper_selection_osc_tuning_range_vector_ptr);
    ~Virtual_Calibrate_Sensors_Dialog();

private:
   unsigned char *m_virtual_calib_channel_mode_bool_vector_ptr;
   char *m_virtual_calib_jumper_selection_osc_tuning_range_vector_ptr;

public slots:

   /**
     * void Save_Virtual_Sensors_Calibrations()
     *
     * @brief Saves calibration data of currently selected sensor channel from 'Virtual_Calibrate_Sensors_Dialog' dialog to the correspondent program variables.
     *
     * @details This function calls the 'Save_Sensors_Calibrations()' from parent class, and also saves other information of the virtual calibration table, namely: the channel mode (saved to 'virtual_calib_channel_mode_bool_vector[]') and jumper configuration (saved to 'virtual_calib_jumper_selection_osc_tuning_range_vector[]').
     */
    void Save_Virtual_Sensors_Calibrations();

    /**
      * void Update_Virtual_Calibrate_Sensors_Dialog()
      *
      * @brief Reads sensor calibration data stored on the program variables, and sets/updates items visible on dialog 'Virtual_Calibrate_Sensors_Dialog'.
      *
      * @details This function calls the 'Update_Sensors_Calibrations()' from parent class, and also updates other information of the currenlty visible virtual calibration table, namely: the channel mode (read from 'virtual_calib_channel_mode_bool_vector[]') and jumper configuration (read from 'virtual_calib_jumper_selection_osc_tuning_range_vector[]').
      */
    void Update_Virtual_Calibrate_Sensors_Dialog();
};

#endif // VIRTUAL_CALIBRATE_SENSORS_DIALOG_H
