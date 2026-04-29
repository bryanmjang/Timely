//
// Created by bryan on 2025-12-15.
//

#ifndef TIMELY_REMINDERSERVICE_H
#define TIMELY_REMINDERSERVICE_H

#include <QObject>
#include <QTimer>
#include <QSystemTrayIcon>

#include <unordered_map>
#include <vector>
#include <memory>
#include <string>

#include "Event.h"

using namespace std;

// ReminderService Class
// This class is responsible for scheduling and firing event reminders using Qt Timers.
// It emits signals when reminders occur.
class ReminderService : public QObject {
    Q_OBJECT

public:

    // Constructor
    explicit ReminderService(QObject *parent = nullptr);

    // Function to set tray icon used for notifications
    void setTrayIcon(QSystemTrayIcon* icon);

    // Function to schedule all reminders for a given event
    void scheduleForEvent(const Event& e);

    // Function to cancel all reminders for an event
    void cancelForEvent(const string& eventID);

    // Function to clear and reschedule reminders for all events
    void rescheduleAll(const vector<Event>& events);

signals:

    // Emits when a reminder goes off
    void reminderFired(const Event& e, int minsBefore);

private:
    QSystemTrayIcon* _tray = nullptr;

    unordered_map<string, vector<unique_ptr<QTimer>>> _timers;

    // Function to show notification and emit signal
    void fire(const Event& e, int minutesBefore);
};

#endif //TIMELY_REMINDERSERVICE_H
