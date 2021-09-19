/******************************************************************************************************
**                                                                                                    *
**  Copyright (C) 2021 David Nuno Quelhas. LGPL License 3.0 (GNU).                                    *
**  David Nuno Quelhas; Lisboa, Portugal.  david.quelhas@yahoo.com ,                                  *
**  https://multiple-sensor-interface.blogspot.com                                                    *
**                                                                                                    *
**  Multi-sensor interface, RTU. Modbus USB Device Driver.                                            *
**                                                                                                    *
**  This is the header file for the USB Driver of the Multiple-Sensor Interface, also                 *
**                               referenced/mentioned here by the name 'LCR sensors' .                *
**                                                                                                    *
**  This library is free software; you can redistribute it and/or modify it under the terms of the    *
**  GNU Lesser General Public version 3.0 License as published by the Free Software Foundation.       *
**  This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;         *
**  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.         *
**  See the GNU Lesser General Public License for more details.                                       *
**  You should have received a copy of the GNU Lesser General Public License along with this library. *
**  --------------------                                                                              *
**   FILE: multiple_sensor_usb_driver.h - Here are the structs and prototypes of functions of the     *
**                          USB Device Driver of Multiple-Sensor Interface. The USB driver has the    *
**                          same design/coding as the Modbus RS485/serial driver.                     *
******************************************************************************************************/


#ifndef HIDAPI_H__
#define HIDAPI_H__

#include <wchar.h>

#ifdef _WIN32
      #define HID_API_EXPORT __declspec(dllexport)
      #define HID_API_CALL
#else
      #define HID_API_EXPORT /**< API export macro */
      #define HID_API_CALL /**< API call macro */
#endif

#define HID_API_EXPORT_CALL HID_API_EXPORT HID_API_CALL /**< API export and call macro*/

typedef struct hid_device_ hid_device; /**< opaque hidapi structure */

HID_API_EXPORT hid_device * HID_API_CALL hid_open(unsigned short vendor_id, unsigned short product_id, wchar_t *serial_number);
int HID_API_EXPORT HID_API_CALL hid_read_timeout(hid_device *dev, unsigned char *data, size_t length, int milliseconds);
int  HID_API_EXPORT HID_API_CALL hid_write(hid_device *device, const unsigned char *data, size_t length);
void HID_API_EXPORT HID_API_CALL hid_close(hid_device *device);

#endif

//#include <wchar.h>

#ifdef _WIN32
      #define MultipleSensor_USB_driver_EXPORT __declspec(dllexport)
      #define MultipleSensor_USB_driver_CALL
#else
      #define MultipleSensor_USB_driver_EXPORT /**< API export macro */
      #define MultipleSensor_USB_driver_CALL /**< API call macro */
#endif

#define MultipleSensor_USB_driver_EXPORT_CALL MultipleSensor_USB_driver_EXPORT MultipleSensor_USB_driver_CALL /**< API export and call macro*/


#ifdef __cplusplus
extern "C" {
#endif

#ifndef MULTIPLE_SENSOR_USB_DRIVER_H
#define MULTIPLE_SENSOR_USB_DRIVER_H

#define MAX_SIZE_SERIAL_SEND_BUFFER 65  //USB BUFFER SIZE MUST 65 bytes
#define MAX_SIZE_SERIAL_RECEIVE_BUFFER 65   //USB BUFFER SIZE MUST 65 bytes

// #define MY_DEVICE_ID  "Vid_04d8&Pid_003F"
#define MY_DEVICE_VID  0x04d8
#define MY_DEVICE_PID  0x003F

#define GS_ASCII 29  //"group separator" character ASCII code
#define US_ASCII 31  //"unit separator" character ASCII code
#define N_LCR_CHANNELS 6  //number of available channels for LCR sensors
#define N_ADC_CHANNELS 4  //number of available channels for the ADC (2 ch are voltmeter, 2 ch are sensor based on resistance change)
#define N_DIGITAL_OUT 3	//number of available digital outputs

#define CALIB_UNITS_SIZE_STR 20 // number of characters available to save the units of each sensor calibration table

#define EEPROM_I2C_SIZE_KBITS 512	//512Kbits <=> 64Kbytes, 24LC512 or 24FC512
//#define SIZE_CALIB_TABLE_BYTES ( EEPROM_I2C_SIZE_KBITS / ( 8*(N_LCR_CHANNELS+N_ADC_CHANNELS) ) );
#define TABLE_HEADER_SIZE_BYTES 64  //size in bytes of the header of each calibration table, where is saved the units of calibration, the mode: multi channel or single channel, etc...
const short SIZE_CALIB_TABLE_BYTES_const = (short) ( (1024.0 *  EEPROM_I2C_SIZE_KBITS ) / ( 8.0*(N_LCR_CHANNELS+N_ADC_CHANNELS) ) );

// ----- USB Driver of LCR sensors, commands return codes -----
#define SENSOR_CALIB_SUCCESS 1003
#define USB_CONNECTED 1002
#define USB_COMMAND_OK 1001
#define USB_COMMAND_ERROR -1002
#define USB_CONNECTION_ERROR -1003
#define SENSOR_CALIB_FAILED -1004
#define SENSOR_READ_FAIL_DUE_MISSING_CALIB -1005
#define USB_REPLY_WITH_INVALID_DATA -1012

#define OK 1
#define ERROR_BOOL_FUNC_MISSING_STRING_TERMINATOR -2004
#define ERROR_BOOL_FUNC_INVALID_VARIABLE -2005
#define ERROR_BOOL_FUNC_PARENTHESIS_PAIRS_MISMATCH -2006
#define ERROR_BOOL_FUNC_MISSING_OPERATOR -2007
#define ERROR_BOOL_FUNC_OPERATION_MISSING_1ST_VARIABLE -2008
#define ERROR_BOOL_FUNC_OPERATION_MISSING_2ND_VARIABLE -2009
#define ERROR_BOOL_FUNC_INVALID_CHARACTER -2010
#define ERROR_BOOL_FUNC_PARENTHESES_NOT_MATCHING -2011
#define ERROR_BOOL_FUNC_EMPTY_PARENTHESES -2012


#define TRUE_BOOL 1
#define FALSE_BOOL 0

#define CALIB_UNITS_SIZE_STR 20
#define CALIB_TABLE_MAX_ROWS_TO_PROCESS_ON_MULTI_MODE 12		//maximum size/lines used from a calibration table of sensor measurements when device is in multiple channel mode, this restriction is to ensure the measurements process doesn't overload the processing by the PIC18F2550
#define CALIB_TABLE_MAX_ROWS_TO_PROCESS_ON_SINGLE_MODE 32		//maximum size/lines used from a calibration table of sensor measurements when device is in single channel mode, this restriction is to ensure the measurements process doesn't overload the processing by the PIC18F2550
#define INF_4byte_float 2000000000.0    //larger number to be considered for the measurement values (4 byte float)

#define COUNTER_CALIB_ROW_NUMBER 240	//row number where are saved the calibration constants for the counter calibration

#define BOOL_FUNC_N_BYTES 54	// bool_func_N_bytes/2=(integer), MUST BE DIVISIBLE BY 2	//max. 50 characters for the boolean functions of the outputs, 2 character for ( ), 1 character for '\0', and 1 extra character
#define BOOL_FUNC_MAX_LENGTH 50	//the actual maximum length/size for bool func is '50', because must have/add '(' at start and ')' at end for ensuring bool function / expression is evaluated correctly, plus '\0' at the end

/** 'typedef MultipleSensor_USB_driver' ;  'struct MultipleSensor_USB_driver_struct' - Structure containing all variables required to interact with the Multiple-Sensor Interface by USB
   *
   * @b Description
   * Structure containing all variables required to interact with the Multiple-Sensor Interface by USB
   */
typedef struct MultipleSensor_USB_driver_struct{
    int isConnected;    //True=1, False=0
    hid_device *device;
    unsigned char board_ID;  // number (0 - 254) that identifies the board that should respond to the message

    int error_code_recent;    //when an error occurs, the error code is saved on recent_error_code
    int error_at_CH_number_or_position; //the channel number or the array position were the error occured
}MultipleSensor_USB_driver;

// static const MultipleSensor_USB_driver session_not_connected = { FALSE_BOOL, NULL, "" };



/**   **************************************************************************************
**  void print_ERROR_MSG_USB_MultipleSensor(int error_code)
**   @brief Prints the error message correspondent to the error code that was returned by the USB driver of Multiple-Sensor
**
**   @param[in] error_code - int - The 'error code'/'return value' an integer number from the list "Driver of LCR sensors, list of commands return codes"
**
**   @returns void
********************************************************************************************   */
MultipleSensor_USB_driver_EXPORT_CALL void print_ERROR_MSG_USB_MultipleSensor(int error_code);



/**   **************************************************************************************
** int OpenDevice_USB_MultipleSensor(MultipleSensor_USB_driver *session)
**   @brief Open the USB connection to the Multiple-Sensor device.
**
**   @param[in,out] *session - MultipleSensor_USB_driver - pointer to structure of infos about this session of multi-sensor device USB driver
**
**   @returns void
********************************************************************************************   */
MultipleSensor_USB_driver_EXPORT_CALL int OpenDevice_USB_MultipleSensor(MultipleSensor_USB_driver *session);



/**   **************************************************************************************
**  int SaveSensorConfigs_USB_MultipleSensor(MultipleSensor_USB_driver *session, int configs_for_channel_number, char make_compare_w_calibrated_sensor_value, char compare_is_greater_than, char sensor_prescaler, char sensor_used_for_OUT[3], float sensor_trigger_value)
**   @brief  Configures the trigger states that activates the digital outputs of the device
**
**   @param[in,out]  *session - MultipleSensor_USB_driver - pointer to structure of infos about this session of multi-sensor device USB driver.
**   @param[in]  configs_for_channel_number  -  int  -  Number of the channel to be configured ;
**   @param[in]  make_compare_w_calibrated_sensor_value  -  char  -  NOT IMPLEMENTED/USED (Multiple-Sensor Interface no longer uses this parameter).  boolean value (0 or 1), 0 RAW sensor measurement is used , 1 calibrated measurement is used; for the trigger of the sensor channel ;
**   @param[in]  compare_is_greater_than  -  char  -  boolean value (0 or 1),  0 is used for the minor than compare, 1 is used for the greater than compare.
**   @param[in]  sensor_prescaler  -  char  -  NOT IMPLEMENTED/USED (the firmware is set to 4)
**   @param[in]  sensor_used_for_OUT[3]  -  char [3]  -  NOT IMPLEMENTED/USED  -  boolean values that indicate which outputs are activated by this sensor channel  (ex: {0,1,0} means this channel only activates output N.1, {1,1,0} means this channel activates output N.0 and N.1
**   @param[in]  sensor_trigger_value  -  float  -  is the reference value used on the comparison that determines if this sensor channel is triggered
**
**   @returns  (int) command return code
********************************************************************************************   */
MultipleSensor_USB_driver_EXPORT_CALL int SaveSensorConfigs_USB_MultipleSensor(MultipleSensor_USB_driver *session, int configs_for_channel_number, char make_compare_w_calibrated_sensor_value, char compare_is_greater_than, char sensor_prescaler, char sensor_used_for_OUT[3], float sensor_trigger_value);



/**   **************************************************************************************
** int ReadFrequencyMeasurement_USB_MultipleSensor(MultipleSensor_USB_driver *session, int *integer_CH_vector)
**   @brief    Read the frequency of the all the sensor channels in Hertz, save them as a integer vector.
**
**   @param[in,out]  *session - MultipleSensor_USB_driver - pointer to structure of infos about this session of multi-sensor device USB driver.
**   @param[out]  *integer_CH_vector  -  int  -  pointer to (int) vector were will be saved the frequency in Hertz of each sensor channel signal (integer values)
**
**   @returns  (int) command return code
********************************************************************************************   */
MultipleSensor_USB_driver_EXPORT_CALL int ReadFrequencyMeasurement_USB_MultipleSensor(MultipleSensor_USB_driver *session, long int *integer_CH_vector);



/**   **************************************************************************************
**  int ReadADCValue_USB_MultipleSensor(MultipleSensor_USB_driver *session, float *ADC_values_vector_ptr)
**   @brief   Read the ADC values in Volt (V) for all the ADC channels (ADC-Analogue to digital converter).
**
**   @param[in,out]  *session - MultipleSensor_USB_driver - pointer to structure of infos about this session of multi-sensor device USB driver.
**   @param[out]  *ADC_values_vector_ptr  -  float  -  pointer to (float) vector were will be saved the values read from the ADC
**
**   @returns  (int) command return code
********************************************************************************************   */
MultipleSensor_USB_driver_EXPORT_CALL int ReadADCValue_USB_MultipleSensor(MultipleSensor_USB_driver *session, float *ADC_values_vector_ptr);



/**   **************************************************************************************
**  int ReadLineCalibTable_USB_MultipleSensor(MultipleSensor_USB_driver *session, int channel_number, int line_number, float *RAW_value_ptr, float *measurement_ptr)
**   @brief  function to download/read from the device a line (indicated by line_number) of the calibration table of the selected channel (by channel_number).
**
**   @param[in,out]  *session - MultipleSensor_USB_driver - pointer to structure of infos about this session of multi-sensor device USB driver.
**   @param[in]  channel_number  -  int  -  number of the channel to be read data from its calibration table
**   @param[in]  line_number  -  int  - number of the line to be read from the calibration table
**   @param[out]  *RAW_value_ptr  -  float  -  pointer to the variable where should be saved the read RAW_value
**   @param[out]  *measurement_ptr  -  float  -  pointer to the variable where should be saved the read measurement(of calibration table)
**
**   @returns  (int) command return code
********************************************************************************************   */
MultipleSensor_USB_driver_EXPORT_CALL int ReadLineCalibTable_USB_MultipleSensor(MultipleSensor_USB_driver *session, int channel_number, int line_number, float *RAW_value_ptr, float *measurement_ptr);



/**   **************************************************************************************
**  int WriteLineCalibTable_USB_MultipleSensor(MultipleSensor_USB_driver *session, int channel_number, int line_number, float RAW_value, float measurement)
**   @brief  function to upload/write to the device a line (indicated by line_number) of the calibration table of the selected channel (by channel_number).
**
**   @param[in,out]  *session - MultipleSensor_USB_driver - pointer to structure of infos about this session of multi-sensor device USB driver.
**   @param[in]  channel_number  -  int  -  number of the channel to be written data to its calibration table
**   @param[in]  line_number  -  int  -  number of the line to be written to the calibration table on the device
**   @param[out]  RAW_value  -  float  -  argument were is passed the RAW_value to be written to the device
**   @param[out]  measurement  -  float  -  argument were is passed the measurement to be written to the device
**
**   @returns  (int) command return code
********************************************************************************************   */
MultipleSensor_USB_driver_EXPORT_CALL int WriteLineCalibTable_USB_MultipleSensor(MultipleSensor_USB_driver *session, int channel_number, int line_number, float RAW_value, float measurement);



/**   **************************************************************************************
**  int ReadHeaderCalibTable_USB_MultipleSensor(MultipleSensor_USB_driver *session, int channel_number, unsigned char *calib_table_is_active_bool_ptr, unsigned char *number_table_lines_ptr, unsigned char *calibration_mode_multi_or_single_ch_ptr, char *jumper_selection_osc_tunning_range_ptr, char *units_str_ptr, char *counter_calib_units_str_ptr)
**   @brief  Reads/downloads the header of the calibration table for the selected channel number on the device.

**   @param[in,out]  *session - MultipleSensor_USB_driver - pointer to structure of infos about this session of multi-sensor device USB driver.
**   @param[in] channel_number  -  int  - number of the channel that is to be read its calibration table
**   @param[out] *calib_table_is_active_bool_ptr  -  unsigned char  -  pointer to variable where will be saved if the calib table is being used by the device to calculate measurements for the respective sensor channel
**   @param[out] *number_table_lines_ptr  -  unsigned char  -  pointer to variable where will be saved the number of valid lines of the calibration table
**   @param[out] *calibration_mode_multi_or_single_ch_ptr  -  unsigned char  -  pointer to variable where will be saved the mode of operation of the device when the calibration table was obtained ('1' - single channel mode , '0' - multiple channel mode)
**   @param[out] *jumper_selection_osc_tunning_range_ptr  -  char  -  pointer to variable where will be saved the letter (character A or B) indicating the jumper selection of oscilator tunning range , this parameter is the jumper position of a LCR channel selected by the user on the multiple sensor interface , it can be A or B ( A, B coded in ASCII)
**   @param[out] *units_str_ptr  -  char  -  string (char *) where will be saved the units of the calibration table
**   @param[out] *counter_calib_units_str_ptr  -  char  -  string (char *) where will be saved the units of the counter calibration*
**
**   @returns  (int) command return code
********************************************************************************************   */
MultipleSensor_USB_driver_EXPORT_CALL int ReadHeaderCalibTable_USB_MultipleSensor(MultipleSensor_USB_driver *session, int channel_number, unsigned char *calib_table_is_active_bool_ptr, unsigned char *number_table_lines_ptr, unsigned char *calibration_mode_multi_or_single_ch_ptr, char *jumper_selection_osc_tunning_range_ptr, char *units_str_ptr, char *counter_calib_units_str_ptr);



/**   **************************************************************************************
**  int WriteHeaderCalibTable_USB_MultipleSensor(MultipleSensor_USB_driver *session, int channel_number, unsigned char calib_table_is_active_bool, unsigned char number_table_lines, unsigned char calibration_mode_multi_or_single_ch, char jumper_selection_osc_tunning_range, char *units_str, char *counter_calib_units_str);
**   @brief  Writes/uploads the header of the calibration table for the selected channel number on the device.
**
**   @param[in,out]  *session - MultipleSensor_USB_driver - pointer to structure of infos about this session of multi-sensor device USB driver.
**   @param[in] channel_number  -  int  -   number of the channel that is to be written its calibration table
**   @param[in] calib_table_is_active_bool  -  unsigned char  -  indicates if the calib table is being used by the device to calculate measurements for the respective sensor channel, ('0' false, '1' true)
**   @param[in] number_table_lines  -  unsigned char  -  number (0 - 32) of valid lines of the calibration table
**   @param[in] calibration_mode_multi_or_single_ch  -  unsigned char  - mode of operation of the device when the calibration table was obtained ('1' - single channel mode , '0' - multiple channel mode)
**   @param[in] jumper_selection_osc_tunning_range  -  char  -  letter (character 'A', 'B', '+', '-') indicating the jumper selection of oscillator tuning range , this parameter is the jumpers position of a LCR channel selected by the user on the multiple sensor interface , it can be '+', '-' 'A' or 'B' ( +, -, A, B coded in ASCII)
**                                                                 ('A' - only placed/closed the jumper A; 'B' - only placed/closed the jumper B; '+' - placed/closed the jumpers A and B; '-' - removed/open the jumpers A and B)
**   @param[in] *units_str  -  char  -  string (char *) with the units of the calibration table
**   @param[in] *counter_calib_units_str  -  char  -  string (char *) with the units of the counter calibration
**
**   @returns (int) command return code
********************************************************************************************   */
MultipleSensor_USB_driver_EXPORT_CALL int WriteHeaderCalibTable_USB_MultipleSensor(MultipleSensor_USB_driver *session, int channel_number, unsigned char calib_table_is_active_bool, unsigned char number_table_lines, unsigned char calibration_mode_multi_or_single_ch, char jumper_selection_osc_tunning_range, char *units_str, char *counter_calib_units_str);





/**   **************************************************************************************
**  int Read_Sensor_Configs_USB_MultipleSensor(MultipleSensor_USB_driver *session, int configs_for_channel_number, char *make_compare_w_calibrated_sensor_value_ptr, char *compare_is_greater_than_ptr, char *sensor_prescaler_ptr, char *sensor_used_for_OUT_ptr, float *sensor_trigger_value_ptr)
**   @brief Read the various configurations of the sensor channel selected on configs_for_channel_number.
**               Please pass on the arguments the pointers to the variables were the read configuration will be saved
**
**   @param[in,out]  *session - MultipleSensor_USB_driver - pointer to structure of infos about this session of multi-sensor device USB driver.
**   @param[in]  configs_for_channel_number  -  int  -  Number of the channel to obtain its configuration.
**   @param[out]  *make_compare_w_calibrated_sensor_value_ptr  -  char  -  NOT IMPLEMENTED/USED (Multiple-Sensor Interface no longer uses this parameter). Pointer to the variable where will be saved a boolean value (0 or 1), 0 RAW sensor measurement is used , 1 calibrated measurement is used, for the trigger of the sensor channel
**   @param[out]  *compare_is_greater_than_ptr  -  char  -  pointer to the variable where will be saved a boolean value (0 or 1),  0 is used for the minor than compare, 1 is used for the greater than compare.
**   @param[out]  *sensor_prescaler_ptr  -  char  -  NOT IMPLEMENTED - (the firmware is set to 4)
**   @param[out]  *sensor_used_for_OUT_ptr  -  char [3]  -  NOT IMPLEMENTED/USED -  pointer to the variable where will be saved a boolean value that indicate which outputs are activated by this sensor channel
**   @param[out]  *sensor_trigger_value_ptr  -  float  -  pointer to the variable where will be saved the reference value used on the comparison that determines if this sensor channel is triggered
**
**   @returns (int) command return code
********************************************************************************************   */
MultipleSensor_USB_driver_EXPORT_CALL int ReadSensorConfigs_USB_MultipleSensor(MultipleSensor_USB_driver *session, int configs_for_channel_number, char *make_compare_w_calibrated_sensor_value_ptr, char *compare_is_greater_than_ptr, char *sensor_prescaler_ptr, char *sensor_used_for_OUT_ptr, float *sensor_trigger_value_ptr);






/**   **************************************************************************************
**  int WriteOutputConfig_USB_MultipleSensor(MultipleSensor_USB_driver *session, unsigned char output_number, char *out_bool_func_str)
**   @brief  Writes the boolean equation of the selected digital output to the device, before writing to the device it checks the validity of the boolean function inserted by the user,
**            in case the boolean function has an error returns the correspondent error code and inside the session struct sets "error_at_CH_number_or_position" to the value of the position were the error occured.
**
**   @param[in,out]  *session - MultipleSensor_USB_driver - pointer to structure of infos about this session of multi-sensor device USB driver.
**   @param[in]  output_number  -  unsigned char  -  output number (0,1,2) that will use the saved boolean equation
**   @param[in]  *out_bool_func_str  -  char  -  string (char *) with the boolean equation to be saved on the device for the selected 'output_number' (max length 50 characters (bytes))
**
**   @returns (int) command return code
********************************************************************************************   */
MultipleSensor_USB_driver_EXPORT_CALL int WriteOutputConfig_USB_MultipleSensor(MultipleSensor_USB_driver *session, unsigned char output_number, char *out_bool_func_str);




/**   **************************************************************************************
**  int ReadOutputConfig_USB_MultipleSensor(MultipleSensor_USB_driver *session, unsigned char output_number, char *out_bool_func_str)
**   @brief  Reads the boolean equation of the selected digital output.
**
**   @param[in,out]  *session - MultipleSensor_USB_driver - pointer to structure of infos about this session of multi-sensor device USB driver.
**   @param[in]  output_number  -  unsigned char  -  output number (0,1,2) where to be read the boolean equation
**   @param[out]  *out_bool_func_str  -  char [3]  -  string (char *) were will be saved the read boolean equation
**
**   @returns (int) command return code
********************************************************************************************   */
MultipleSensor_USB_driver_EXPORT_CALL int ReadOutputConfig_USB_MultipleSensor(MultipleSensor_USB_driver *session, unsigned char output_number, char *out_bool_func_str);



/**   **************************************************************************************
**  int ReadOutputs_USB_MultipleSensor(MultipleSensor_USB_driver *session, unsigned char *outputs_vector)
**   @brief  Read the outputs of the multi-sensors device, INACTIVE=0x00, ACTIVE=0x01.
**
**   @param[in,out]  *session - MultipleSensor_USB_driver - pointer to structure of infos about this session of multi-sensor device USB driver.
**   @param[out]  *outputs_vector  -  unsigned char [3]  -  pointer to the vector where will be save the values of the digital outputs of the multi-sensors device , boolean values ('0', '1') type char
**
**   @returns (int) command return code
********************************************************************************************   */
MultipleSensor_USB_driver_EXPORT_CALL int ReadOutputs_USB_MultipleSensor(MultipleSensor_USB_driver *session, unsigned char *outputs_vector);



/**   **************************************************************************************
**  int SaveModeCHConfig_USB_MultipleSensor(MultipleSensor_USB_driver *session, unsigned char mode_is_single_channel_bool, int selected_channel_number)
**   @brief  Save the selected L,C,R sensors channel mode on the multi-sensors device, if in single-channel mode the update frequency of the sensor measurement is faster because only one channel is monitored
**                   in multi-channel mode the device monitors the 6 channels using time-multiplexing.
**
**   @param[in,out]  *session - MultipleSensor_USB_driver - pointer to structure of infos about this session of multi-sensor device USB driver.
**   @param[in]  mode_is_single_channel_bool  -  unsigned char  -  boolean value that indicates the mode of operation, 0 ("zero") indicates board is in multi-channel mode, 1 ("one") indicates board is in single-channel mode,
**   @param[in]  selected_channel_number  -  int  -  the number of the sensor channel that should be read/measured in case the single channel mode is selected, in multi-channel mode this argument isn't used
**
**   @returns (int) command return code
********************************************************************************************   */
MultipleSensor_USB_driver_EXPORT_CALL int SaveModeCHConfig_USB_MultipleSensor(MultipleSensor_USB_driver *session, unsigned char mode_is_single_channel_bool, int selected_channel_number);




/**   **************************************************************************************
**  int ReadModeCHConfig_USB_MultipleSensor(MultipleSensor_USB_driver *session, unsigned char *mode_is_single_channel_bool_ptr, int *selected_channel_number_ptr)
**   @brief  Read the selected L,C,R sensor channel mode on the multi-sensors device.
**
**   @param[in,out]  *session - MultipleSensor_USB_driver - pointer to structure of infos about this session of multi-sensor device USB driver.
**   @param[out]  *mode_is_single_channel_bool_ptr  -  unsigned char  -  pointer to variable were will be saved the boolean value that indicates the mode of operation, 0 ("zero") indicates board is in multi-channel mode, 1 ("one") indicates board is in single-channel mode ,
**   @param[out]  *selected_channel_number_ptr  -  int  -  pointer to variable were will be saved the number of the sensor channel that should be read/measured in case the single channel mode is selected
**
**   @returns (int) command return code
********************************************************************************************   */
MultipleSensor_USB_driver_EXPORT_CALL int ReadModeCHConfig_USB_MultipleSensor(MultipleSensor_USB_driver *session, unsigned char *mode_is_single_channel_bool_ptr, int *selected_channel_number_ptr);



/**   **************************************************************************************
**  int ReadSensorCounters_USB_MultipleSensor(MultipleSensor_USB_driver *session, long int *integer_CH_vector)
**   @brief  Reads/downloads the counter values (units: cycles) of each sensor channel signal, save them on a (long int) vector.
**
**   @param[in,out]  *session - MultipleSensor_USB_driver - pointer to structure of infos about this session of multi-sensor device USB driver.
**   @param[out]  *integer_CH_vector  - long int  -  pointer to the (long int) vector were will be saved the counter values (units: cycles) of each sensor channel signal (integer values)
**
**   @returns (int) command return code
********************************************************************************************   */
MultipleSensor_USB_driver_EXPORT_CALL int ReadSensorCounters_USB_MultipleSensor(MultipleSensor_USB_driver *session, long int *integer_CH_vector);



/**   **************************************************************************************
**  int ResetSensorCounters_USB_MultipleSensor(MultipleSensor_USB_driver *session)
**   @brief   resets the counter values (units: cycles) of each sensor channel signal. resets <=> set to zero.
**
**   @param[in,out]  *session - MultipleSensor_USB_driver - pointer to structure of infos about this session of multi-sensor device USB driver.
**
**   @returns (int) command return code
********************************************************************************************   */
MultipleSensor_USB_driver_EXPORT_CALL int ResetSensorCounters_USB_MultipleSensor(MultipleSensor_USB_driver *session);



/**   **************************************************************************************
**  int SetBoardIDCode_USB_MultipleSensor(MultipleSensor_USB_driver *session, unsigned char new_board_ID)
**   @brief  Set the Multiple-Sensor Board_ID, relevant for the Modbus RS485/Serial interface.
**
**   @param[in,out]  *session - MultipleSensor_USB_driver - pointer to structure of infos about this session of multi-sensor device USB driver.
**   @param[in]  new_board_ID  -  unsigned char  -  number (0 - 254) of the new 'board_ID' to be saved on the Multiple-Sensor Interface device
**
**   @returns (int) command return code
********************************************************************************************   */
MultipleSensor_USB_driver_EXPORT_CALL int SetBoardIDCode_USB_MultipleSensor(MultipleSensor_USB_driver *session, unsigned char new_board_ID);



/**   **************************************************************************************
**  int GetBoardIDCode_USB_MultipleSensor(MultipleSensor_USB_driver *session, unsigned char *board_ID_ptr)
**   @brief  Get the Multiple-Sensor Board_ID, relevant for the Modbus RS485/Serial interface.
**
**   @param[in,out]  *session - MultipleSensor_USB_driver - pointer to structure of infos about this session of multi-sensor device USB driver.
**   @param[out]  *board_ID_ptr  -  unsigned char  -  pointer to variable where to save the 'board_ID' (0 - 254) read from the Multiple-Sensor Interface device.
**
**   @returns (int) command return code
********************************************************************************************   */
MultipleSensor_USB_driver_EXPORT_CALL int GetBoardIDCode_USB_MultipleSensor(MultipleSensor_USB_driver *session, unsigned char *board_ID_ptr);



/**   **************************************************************************************
**  int ReadMeasurements_USB_MultipleSensor(MultipleSensor_USB_driver *session, float *measurements_vector_ptr)
**   @brief  Read the measurements for the LCR+ADC channels in the units defined on the calibration table . (ADC-Analogue to Digital Converter).
**
**   @param[in,out]  *session - MultipleSensor_USB_driver - pointer to structure of infos about this session of multi-sensor device USB driver.
**   @param[out]  *measurements_values_vector_ptr - float - pointer to the (float) vector were will be saved the values read of the calibrated measurements from the LCR+ADC channels
**
**   @returns (int) command return code
********************************************************************************************   */
MultipleSensor_USB_driver_EXPORT_CALL int ReadMeasurements_USB_MultipleSensor(MultipleSensor_USB_driver *session, float *measurements_vector_ptr);




/**   **************************************************************************************
**  int ReadCountersCalib_USB_MultipleSensor(MultipleSensor_USB_driver *session, int channel_number, float *C0_ptr, float *C1_ptr, float *C2_ptr, float *C3_ptr)
**   @brief Reads the counter calibration constants for the selected channel number on the device the calibration for the counters is:  counter_measurement = C3*(counter_RAW_value^3) + C2*(counter_RAW_value^2) + C1*counter_RAW_value + C0
**
**   @param[in,out]  *session - MultipleSensor_USB_driver - pointer to structure of infos about this session of multi-sensor device USB driver.
**   @param[in] channel_number - number of the channel that is to be read its counter calibration constants/parameters
**   @param[out] *C0_ptr  -  float  -  pointer to where will be saved the constant of the offset
**   @param[out] *C1_ptr  -  float  -  pointer to where will be saved the constant of the counter_RAW_value
**   @param[out] *C2_ptr  -  float  -  pointer to where will be saved the constant of the counter_RAW_value^2
**   @param[out] *C3_ptr  -  float  -  pointer to where will be saved the constant of the counter_RAW_value^3
**
**   @returns (int) command return code
********************************************************************************************   */
MultipleSensor_USB_driver_EXPORT_CALL int ReadCountersCalib_USB_MultipleSensor(MultipleSensor_USB_driver *session, int channel_number, float *C0_ptr, float *C1_ptr, float *C2_ptr, float *C3_ptr);



/**   **************************************************************************************
**  int WriteCountersCalib_USB_MultipleSensor(MultipleSensor_USB_driver *session, int channel_number, float C0, float C1, float C2, float C3)
**   @brief  Writes the counter calibration constants for the selected channel number on the device, the calibration for the counters is:  counter_measurement = C3*(counter_RAW_value^3) + C2*(counter_RAW_value^2) + C1*counter_RAW_value + C0
**
**   @param[in,out]  *session - MultipleSensor_USB_driver - pointer to structure of infos about this session of multi-sensor device USB driver.
**   @param[in] channel_number  -  int  -  number of the channel that is to be written its counter calibration constants/parameters
**   @param[in] C0  -  float  -  constant of the offset
**   @param[in] C1  -  float  -  constant of the counter_RAW_value
**   @param[in] C2  -  float  -  constant of the counter_RAW_value^2
**   @param[in] C3  -  float  -  constant of the counter_RAW_value^3
**
**   @returns (int) command return code
********************************************************************************************   */
MultipleSensor_USB_driver_EXPORT_CALL int WriteCountersCalib_USB_MultipleSensor(MultipleSensor_USB_driver *session, int channel_number, float C0, float C1, float C2, float C3);



/**   **************************************************************************************
**  int ReadCountersMeasurements_USB_MultipleSensor(MultipleSensor_USB_driver *session, float *counters_measurements_values_vector_ptr)
**   @brief  Read the measurements for the counters of the LCR channels in the units defined on the counters calibration .
**
**   @param[in,out]  *session - MultipleSensor_USB_driver - pointer to structure of infos about this session of multi-sensor device USB driver.
**   @param[out]  *counters_measurements_values_vector_ptr - float - pointer to the (float) vector were will be saved the values read of the calibrated counters measurements from the LCR channels
**
**   @returns (int) command return code
********************************************************************************************   */
MultipleSensor_USB_driver_EXPORT_CALL int ReadCountersMeasurements_USB_MultipleSensor(MultipleSensor_USB_driver *session, float *counters_measurements_values_vector_ptr);



/**   **************************************************************************************
**  void CloseDevice_USB_MultipleSensor(MultipleSensor_USB_driver *session);
**
**   @brief  Close the USB connection to the Multiple-Sensor device.
**
**   @param[in,out]  *session - MultipleSensor_USB_driver - pointer to structure of infos about this session of multi-sensor device USB driver.
**
**   @returns (int) command return code
********************************************************************************************   */
MultipleSensor_USB_driver_EXPORT_CALL void CloseDevice_USB_MultipleSensor(MultipleSensor_USB_driver *session);


#endif // MULTIPLE_SENSOR_USB_DRIVER_H

#ifdef __cplusplus
}
#endif
