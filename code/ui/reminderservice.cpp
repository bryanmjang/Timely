//
// Created by bryan on 2025-12-15.
//

#include "ReminderService.h"

#include <QDateTime>
#include <QMessageBox>
#include <chrono>

using namespace std;

// Converting chrono time to QDateTime for Qt usage
static QDateTime toQDateTime(const chrono::system_clock::time_point &tp) {
    using namespace std::chrono;

    // convert to milliseconds since epoch
    auto ms = duration_cast<milliseconds>(tp.time_since_epoch()).count();
    return QDateTime::fromMSecsSinceEpoch(ms);
}

// Initialize reminder service
ReminderService::ReminderService(QObject* parent) : QObject(parent) {}

// Set tray icon used for notifications
void ReminderService::setTrayIcon(QSystemTrayIcon *icon) {
    _tray = icon;
}

// Cancel all reminders for an event
void ReminderService::cancelForEvent(const string& eventID) {
    _timers.erase(eventID);
}

// Clear and reschedule reminders for all events
void ReminderService::rescheduleAll(const vector<Event>& events) {
    _timers.clear();
    for (const auto& e : events) {
        scheduleForEvent(e);
    }
}

// Schedule a reminder for a single event
void ReminderService::scheduleForEvent(const Event& e) {
    const string id = e.getId();

    // Remove old timers
    cancelForEvent(id);

    QDateTime start = toQDateTime(e.getStart());
    QDateTime now = QDateTime::currentDateTime();

    // Timer list for this event
    auto& vec = _timers[id];

    // Calculating when reminder should fire
    for (int minsBefore : e.getRemindersMinutesBefore()) {
        QDateTime trigger = start.addSecs(-minsBefore * 60);
        if (trigger <= now) continue;

        qint64 delayMs = now.msecsTo(trigger);
        auto timer = make_unique<QTimer>();
        timer->setSingleShot(true);

        // Firing reminder when timer expires
        Event copy = e;
        connect(timer.get(), &QTimer::timeout, this,
                [this, copy, minsBefore]() {
                    fire(copy, minsBefore);
                });

        // Starting and storing the timer so that it isnt destroyed.
        timer->start(static_cast<int>(delayMs));
        vec.push_back(move(timer));
    }
}

// Show reminder service
void ReminderService::fire(const Event& e, int minsBefore) {

    // Notifying the listeners
    emit reminderFired(e, minsBefore);

    // Building the reminder message
    QString msg;
    if (minsBefore == 1) msg = QString("Event \"%1\" Starts in %2 Minute!").arg(QString::fromStdString(e.getTitle())).arg(minsBefore);
    else msg = QString("Event: %1 Starts in %2 Minutes.").arg(QString:: fromStdString(e.getTitle())).arg(minsBefore);

    if (_tray && _tray->isVisible()) _tray->showMessage("Reminder", msg, QSystemTrayIcon::Information, 8000);
    else QMessageBox::information(nullptr, "Reminder", msg);
}
