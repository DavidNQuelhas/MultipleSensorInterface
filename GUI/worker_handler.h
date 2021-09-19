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
 *   FILE: worker_handler.h - Here is the 'Worker_Handler' class declaration and   *
 *             function prototypes, used to allow the main process(MainWindow)   *
 *             to interact with the 'Worker' thread   (for example: getting % of *
 *             progress status; or canceling current data transfer).             *
 ********************************************************************************/

#ifndef WORKER_HANDLER_H
#define WORKER_HANDLER_H
 
#include <QObject>
#include <QThread>
#include <QWaitCondition>
 
#include "worker.h"


 /** class Worker_Handler - Class to create/launch a separate thread of class 'Worker' (for transferring calibration tables between the PC and a Multiple-Sensor Interface device).
   *
   * @b Description Class with the methods/instructions to create/launch a separate thread that will run the instructions on the class 'Worker' (for transferring calibration tables between the PC and a Multiple-Sensor Interface device), thus avoiding any blocking of the main window (UI - User Interface).
   */
class Worker_Handler : public QObject
{
    Q_OBJECT
public:
    explicit Worker_Handler(QObject *parent = 0);
	~Worker_Handler();
 
signals:
 
    void max_progress_range_changed_signal(int max_range);
    void progress_value_changed_signal(int value);
    void progress_text_changed_signal(const QString &text);
    void status_text_changed_signal(const QString &text);
    void finished_signal(); 
    void result_ready_signal(const Data ret_data);
 
    //internal signals, this is 'emit <signal name>' only to be called on the source code of this class
    void internal__pause_signal();
    void internal__cancel_signal();
    void internal__start_work_signal(const QList<Worker_Arguments> &list);
 
public slots:
    void Cancel_Thread();
    void Toggle_Paused_Thread();
 
    void Start_Work_Thread(const QList<Worker_Arguments> &list);
 
public:
    bool Is_Paused();
    bool Is_Running();
 
protected slots:
    void Call_On_Finish();
 
private:
 
    QWaitCondition m_pause_cond;
    bool m_pause;
    bool m_is_running;
 
    Worker *worker;
    QThread *worker_thread;    
};
 
#endif // WORKER_HANDLER_H
