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
 *   FILE: calibrate_sensors_dialog.h - Here is the 'Calibrate_Sensors_Dialog'   *
 *    class declaration and function prototypes, that is the base class for      *
 *    'Device_Calibrate_Sensors_Dialog' and 'Virtual_Calibrate_Sensors_Dialog'.  *
 ********************************************************************************/

#ifndef CALIBRATE_SENSORS_DIALOG_H
#define CALIBRATE_SENSORS_DIALOG_H

#include <QDialog>
#include <QTableView>
#include <QStandardItemModel>
#include <QGroupBox>
#include <QComboBox>
#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>
#include <QLineEdit>

#include "multiple_sensor_USB/multiple_sensor_usb_driver.h"
#include "multiple_sensor_modbus/multiple_sensor_modbus_driver.h"


#define N_CHARS_CALIB_UNITS 31


#ifdef WIN32
    #ifndef NAN
        static const unsigned long __nan[2] = {0xffffffff, 0x7fffffff};
        #define NAN (*(const float *) __nan)
    #endif
#endif


/** 'typedef counters_calib' ;  'struct counters_calib_struct'
   * @brief Structure containing arrays with calibration constants and calibration units for the counter measurements, for all sensor channels
   *
   * @details Structure containing float arrays used for saving the calibration constants of the counter measurements for all LCR/frequency sensor channels; and also an array with strings for saving the calibration units of counter measurements for all sensor channels.
   */
typedef struct counters_calib_struct {
    char calib_channel_mode_bool;   //0-calib is for multiple CHs, 1-calib is for single CH
    float counters_calib_C3_vector[N_LCR_CHANNELS+N_ADC_CHANNELS];
    float counters_calib_C2_vector[N_LCR_CHANNELS+N_ADC_CHANNELS];
    float counters_calib_C1_vector[N_LCR_CHANNELS+N_ADC_CHANNELS];
    float counters_calib_C0_vector[N_LCR_CHANNELS+N_ADC_CHANNELS];
    char counters_calib_units[N_LCR_CHANNELS+N_ADC_CHANNELS][N_CHARS_CALIB_UNITS];
} counters_calib;


/** class Calibrate_Sensors_Dialog - Class of the dialog window used for configuring the calibration tables of measurements on LCR/frequency/ADC sensor channels , and configuring the constants of calibration function of counter measurements on frequency sensor channels.
   *
   * @b Description
   * Calibrate_Sensors_Dialog is the base class for the dialog used for configuring the LCR or ADC sensors calibration (applied over the RAW data)
   * Classes that will inherit this class are 'Device_Calibrate_Sensors_Dialog' (used for configuring the device calibrations) and 'Virtual_Calibrate_Sensors_Dialog' (used for configuring the virtual calibrations that are only available to use on the PC, not on the sensors board) .
   */
class Calibrate_Sensors_Dialog : public QDialog
{
    Q_OBJECT

public:
    /**
      * explicit Calibrate_Sensors_Dialog(int *previous_ch_number_for_saved_calib_dialog_ptr,char (*calib_units_vector_ptr)[N_CHARS_CALIB_UNITS], QStandardItemModel **model_tables_calib_vector_ptr, counters_calib *counters_calib_ptr)
      *
      * @brief The constructor of the base class used for configuring the calibration tables of measurements on LCR/frequency/ADC sensor channels , and configuring the constants of calibration function of counter measurements on frequency sensor channels.
      *
      * @param[in,out] *previous_ch_number_for_saved_calib_dialog_ptr Pointer to variable that stores the selected channel number that was previously selected by the user on 'Calibrate_Sensors_Dialog'.
      * @param[in,out] (*calib_units_vector_ptr)[N_CHARS_CALIB_UNITS] Pointer to array(vector) where are stored the calibration units for all the sensor channels (each entry of this array is a pointer to a C string).
      * @param[in,out] **model_tables_calib_vector_ptr Pointer to array(vector) where are stored the calibration tables for all the sensor channels
      * @param[in,out] *counters_calib_ptr Pointer to structure ('counters_calib') where are stored the constants of the calibration function used to calculate the counter measurements
      */
    explicit Calibrate_Sensors_Dialog(int *previous_ch_number_for_saved_calib_dialog_ptr,char (*calib_units_vector_ptr)[N_CHARS_CALIB_UNITS], QStandardItemModel **model_tables_calib_vector_ptr, counters_calib *counters_calib_ptr);
    ~Calibrate_Sensors_Dialog();

    /**
      * int Calib_Table_Row_Count()
      *
      * @brief Returns the number of rows of the calibration table currently shown/presented on the 'Calibrate_Sensors_Dialog' dialog window.
      *
      * @returns (int) The number of rows of the calibration table currently shown/presented on the 'Calibrate_Sensors_Dialog' dialog window.
      */
    int Calib_Table_Row_Count();


    /**
     * static float Read_Measurement_From_Calib_Table(QStandardItemModel **model_tables_calib_vector, int sensor_number, float RAW_value)
     *
     * @brief Reads (calculates) a measurement from the selected calibration table in a similar way to the Multiple-Sensor device; this is it will read from the calibration table the two points closest tot he selected RAW_value, then it will calculate a line ( measurement = a*RAW_value + b) passing on those 2 points, it will calculate measurement from the mentioned equation for the selected RAW_value.
     *
     * @param[in] model_tables_calib_vector Pointer to array(vector) where are stored the calibration tables for all the sensor channels.
     * @param[in] sensor_number The sensor channel number that is to be read(calculated) from the calibration table.
     * @param[in] RAW_value The RAW_value of sensor channel that is to be read (calculated) from the calibration table.
     *
     * @return Returns the read (calculated) measurement for the given RAW_value from the selected calibration table (sensor channel).
     */
    static float Read_Measurement_From_Calib_Table(QStandardItemModel **model_tables_calib_vector, int sensor_number, float RAW_value);


    /**
      * QStandardItemModel *Calibrate_Sensors_Dialog::Create_Copy_Model_Table(QStandardItemModel *src_model_table)
      *
      * @brief Make a copy of the of one QStandardItemModel to another QStandardItemModel (used to save/display a calibration table).
      *
      * @details This function copies one QStandardItemModel table to another table, usually to copy a calibration table from the array on '*model_tables_calib_vector_ptr' to the calibration table currently displayed on the dialog 'Calibrate_Sensors_Dialog'.
      * The various calibration tables are saved on the array on '*model_tables_calib_vector_ptr'. Only one calibration table is currently shown on the 'Calibrate_Sensors_Dialog' dialog (that is saved on variable 'current_model_table_calib'). The currently shown calibration table is on a separated variable because is being edited by the user, thus whenever the dialog is opened or 'Select Channel' spinBox is changed, it is copied the from the array on '*model_tables_calib_vector_ptr' to 'current_model_table_calib' (that is the table currently show/visible on the dialog window).
      * Whenever the user clicks the 'OK' button, it means it finished editing the table contents of the currently selected sensor channel, and then the program uses again Create_Copy_Model_Table(...) to copy the data currently shown/visible on 'current_model_table_calib' (with calibration table data inserted/edited by the user) back to the correspondent table on the array on '*model_tables_calib_vector_ptr'.
      *
      * @param[in] *src_model_table Pointer to the table (of type 'QStandardItemModel') that will have its contents copied.
      *
      * @returns QStandardItemModel* Memory address of the new table created and filled (copied) with same content as on the table referenced by '*src_model_table'.
      */
    QStandardItemModel *Create_Copy_Model_Table(QStandardItemModel *src_model_table);

    QWidget *calibrate_sensors_widget;
    QSpinBox *select_channel_number_spinBox;

    QWidget *top_select_widget;
    QGridLayout *top_select_widget_layout;

    QGroupBox *calib_channel_mode_groupBox;
    QGridLayout *calib_channel_mode_groupBox_layout;
    QLabel *calib_channel_mode_label;
    QComboBox *calib_channel_mode_comboBox;
    QLabel *calib_channel_jumper_selection_osc_tuning_range_label;
    QComboBox *calib_channel_jumper_selection_osc_tuning_range_comboBox;

    QLabel *info_label_for_current_sensor_channel;

    QWidget *button_widget;
    QGridLayout *button_widget_layout;
    QPushButton *OK_button;
    QPushButton *cancel_button;
    QPushButton *zero_calibration_button;

    QGroupBox *calib_table_groupBox;
    QGridLayout *calib_table_groupBox_layout;
    QPushButton *add_new_row_calib_button;
    QPushButton *remove_row_calib_button;
    QPushButton *adapt_table_calib_button;

    QGroupBox *calib_counters_groupBox;
    QGridLayout *calib_counters_groupBox_layout;

private:
    QGridLayout *calibrate_sensors_dialog_layout;
    QLabel *select_channel_number_label;
    QWidget *select_channel_widget;
    QGridLayout *select_channel_widget_layout;
    QWidget *select_units_using_calibration_widget;
    QGridLayout *select_units_using_calibration_widget_layout;
    QLabel *select_units_using_calibration_label;
    QLineEdit *select_units_using_calibration_box;
    QStandardItemModel *current_model_table_calib;

    QTableView *table_view_calib;
    QStandardItemModel **model_tables_calib_vector_ptr;    // 'QStandardItemModel **model_tables_calib_vector_ptr' - pointer to the array that contains the currently used calibration tables of all sensor channels of the Multiple-Sensor Interface GUI software

    QItemSelectionModel *selectionM;
    QModelIndexList selectionL;


    QWidget *calib_counters_widget;
    QGridLayout *calib_counters_widget_layout;
    QDoubleSpinBox *C3_counter_calib;
    QDoubleSpinBox *C2_counter_calib;
    QDoubleSpinBox *C1_counter_calib;
    QDoubleSpinBox *C0_counter_calib;

    QWidget *units_measurement_total_widget;
    QGridLayout *units_measurement_total_widget_layout;
    QLineEdit *units_measurement_total_lineEdit;

    QTabWidget *calib_tabWidget;

    QWidget *table_button_widget;
    QGridLayout *table_button_widget_layout;

    QGroupBox *zero_calibration_groupBox;
    QGridLayout *zero_calibration_groupBox_layout;

    QGridLayout *calibrate_sensors_widget_layout;

    int *m_previous_ch_number_for_saved_calib_dialog_ptr;
    char (*m_calib_units_vector_ptr)[N_CHARS_CALIB_UNITS];
    counters_calib *m_counters_calib_ptr;

    char m_headers_list[2][100];

    //variables used on the zero offset for calibration
   QDialog *calib_zero_dialog;
   QRadioButton *select_automatic_calib_zero_offset;
   QRadioButton *select_manual_calib_zero_offset;
   QDoubleSpinBox *raw_value_to_correct_offset_spinBox;
   QDoubleSpinBox *measurement_to_correct_offset_spinBox;

public slots:
    void Call_Create_Copy_Model_Table(int N_channels);

    /**
      * void Set_Calib_Headers(char *header_name_col0, char *header_name_col1)
      *
      * @brief Set/save the column names of the table header to be used/displayed on the calibration table currently shown/presented on the 'Calibrate_Sensors_Dialog' dialog window.
      *
      * @param[in] header_name_col0 Name of the 1st column of the calibration table (Example: 'Freq(Hz)' or 'Voltage(V)').
      * @param[in] header_name_col1 Name of the 2nd column of the calibration table (Example: 'Measurement').
      */
    void Set_Calib_Headers(char *header_name_col0, char *header_name_col1);

    /**
      * void Calibrate_Sensors_Dialog::Save_Sensors_Calibrations()
      *
      * @brief Saves calibration data of currently selected sensor channel from 'Calibrate_Sensors_Dialog' dialog to the correspondent program variables.
      *
      * @details This function saves all the calibration data of currently selected sensor channel visible on the dialog 'Calibrate_Sensors_Dialog', on the correspondent program variables (model_tables_calib_vector_ptr; calib_units_vector_pt; counters_calib_ptr).
      * Whenever the user clicks the 'OK' button, it means it finished editing the table contents of the currently selected sensor channel, and then the program uses again Create_Copy_Model_Table(...) to copy the data currently shown/visible on 'current_model_table_calib' (with calibration table data inserted/edited by the user) back to the correspondent table on the array on '*model_tables_calib_vector_ptr'.
      * The program also saves the calibration measurement units on the correspondent position on 'calib_units_vector_ptr', and also saves the counter calibration constants and counter calibration measurement units on correspondent position on 'counters_calib_ptr'; 'correspondent position' refers to the vector entry/position determined by the currently selected sensor channel.
      */
    void Save_Sensors_Calibrations();

    void Cancel_Dialog();

    /**
      * void Calibrate_Sensors_Dialog::Update_Calibrate_Sensors_Dialog()
      *
      * @brief Reads sensor calibration data stored on the program variables, and sets/updates items visible on dialog 'Calibrate_Sensors_Dialog'.
      *
      * @details This function reads the sensor calibration data stored on the program variables (model_tables_calib_vector_ptr; calib_units_vector_pt; counters_calib_ptr), and sets/updates the items visible on dialog 'Calibrate_Sensors_Dialog' with the calibration data of currently selected sensor channel.
      * Whenever the user clicks/changes the 'Select Channel #' spinBox, this function should be called to set/update the items visible on dialog 'Calibrate_Sensors_Dialog' with sensor calibration data of the currently selected sensor channel.
      */
    void Update_Calibrate_Sensors_Dialog();


    /**
      * void Set_Rows_Color(int start_row, int end_row, QColor color)
      *
      * @brief Set the color of the rows between (and including) the row numbered 'start_row' and row numbered 'end_row', of the calibration table currently shown/presented on the 'Calibrate_Sensors_Dialog' dialog window.
      *
      * @param[in] start_row The number of the first row to be colored.
      * @param[in] end_row The number of the last row to be colored.
      * @param[in] color The new color to be applied on the selected rows (color as defined on Qt library 'QColor').
      */
    void Set_Rows_Color(int start_row, int end_row, QColor color);

    /**
      * void Add_New_Row()
      *
      * @brief Add a new row at the end of the calibration table currently shown/presented on the 'Calibrate_Sensors_Dialog' dialog window.
      *
      */
    void Add_New_Row();

private slots:

    /**
      * void Calibrate_Sensors_Dialog::Calibrate_Zero_Offset()
      *
      * @brief Creates the dialog window for the 'Calibrate Zero Offset' adjustment; f2(x)=f1(x)+offset, where the offset is calculated by a point(RAW_value, measurement).
      *
      * @details PART1 - Creates the dialog window for the 'Calibrate Zero Offset' adjustment.  'Calibrate Zero Offset' adjustment: Will move all the points on a calibration table by adding an offset value to the calibration function('table'), so this is f2(x)=f1(x)+offset where the offset is calculated by a point(RAW_value, measurement) provided by the user that is desired to be perfectly matched by the calibration function('table').
      */
    void Calibrate_Zero_Offset();

    /**
      * void Calibrate_Sensors_Dialog::Calibrate_Zero_Offset_part2()
      *
      * @brief Executes the 'Calibrate Zero Offset' adjustment; f2(x)=f1(x)+offset, where the offset is calculated by a point(RAW_value, measurement).
      *
      * @details PART2 - Executes the 'Calibrate Zero Offset' adjustment.  'Calibrate Zero Offset' adjustment: Will move all the points on a calibration table by adding an offset value to the calibration function('table'), so this is f2(x)=f1(x)+offset where the offset is calculated by a point(RAW_value, measurement) provided by the user that is desired to be perfectly matched by the calibration function('table').
      */
    void Calibrate_Zero_Offset_part2();

    void Remove_Selected_Row();

    /**
        * void Calibrate_Sensors_Dialog::Adapt_Calib_Table() - Calculate 2 extra calibration samples (at start and end of the calibration table), in order to extend the calibration table to cover all the possible values of the input RAW_value.
        *
        * Calculate 2 extra calibration samples (at start and end of the calibration table), in order to extend the calibration table to cover all the possible values of the input RAW_value.
        * For this the slope of the last 2 points(RAW_value, measurement) at the top and at the bottom of the calibration table is calculated, and so the 2 calculated slopes(at start and end of table) are used to calculate an additional point on each side of the table (one for representing a very small measurement and other for very big measurement), so extending the coverage of the calibration table on each side by extending it with a straight-line with same slope as the previous line segment defined by the last 2 points (at the top or the bottom of the calibration table).
        */
    void Adapt_Calib_Table();

};

#endif // CALIBRATE_SENSORS_DIALOG_H
