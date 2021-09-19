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
 *   FILE: about_dialog.h - Here the prototypes of classes and functions related *
 *                   to the dialog for displaying 'About'/'License' information. *
 ********************************************************************************/

#ifndef ABOUT_DIALOG_H
#define ABOUT_DIALOG_H

#include  <QDialog>

#include "ui_About_Dialog.h"

/** class About_Dialog_Impl
  *
  * @b Description
  * Class of the dialog window that displays/shows the software and hardware licenses and also general information about the Multiple Sensor Interface.
  */
class About_Dialog_Impl : public QDialog, private Ui::About_Dialog
{
    Q_OBJECT

    void Init_Text(QTextBrowser* text_display_box_ptr, const char* text_file_path_and_name);

public:
    About_Dialog_Impl(QWidget* parent_widget = 0, QString app_version = "");
    ~About_Dialog_Impl();

protected slots:
    //connected to 'm_ok_button' of 'about_dialog.ui' on signal 'clicked()', by the Qt Auto-Connect (Syntax: "void on_<object name>_<signal name>(<signal parameters>);")
    void on_m_ok_button_clicked() {accept();}
};

#endif	// ABOUT_DIALOG_H

