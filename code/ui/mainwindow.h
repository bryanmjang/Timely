//
// Created by bryan on 2025-11-07.
//
#pragma once

#include <QMainWindow>
#include <QStandardItemModel>
#include <QDate>
#include <memory>
#include <vector>
#include <QSystemTrayIcon>

#include "reminderservice.h"
#include "EventManager.h"
#include "Event.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// MainWindow Class
// This class controls the main user interface, so things like the calendar view, the event table, toolbar actions, and communicating with EventManager
class MainWindow : public QMainWindow {
    Q_OBJECT
public:

    // Constructor - Takes a reference to the EventManager so that the UI can create, edit and delete events
    explicit MainWindow(EventManager& manager, QWidget* parent = nullptr);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent* event) override;

private:
    Ui::MainWindow* _ui;
    EventManager& _manager;
    QStandardItemModel* _model{nullptr};
    QSystemTrayIcon* _tray{nullptr};
    ReminderService _reminders;

    // Refreshed the tbale when the selected date changes
    void refreshForDate(const QDate& d);

    // Function to find an event through its ID
    std::optional<Event> findById(const std::string& id) const;

    // helpers to go between chrono and QDateTime
    static QString tpToQString(Event::TimePoint tp, const char* fmt = "HH:mm");
    static Event::TimePoint qdtToTimePoint(const QDateTime& dt);
    void populateEventsTable(const std::vector<Event>& events, const QString& statusMsg = "");

private slots:

    // Slots are called when toolbar buttons or calendar changes
    void onNew();
    void onEdit();
    void onDelete();
    void onToday();
    void onCalendarDateChanged();
    void onEventClicked(const QModelIndex& index);
    void onSearch();
};
