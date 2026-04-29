//
// Created by bryan on 2025-11-11.
//
#pragma once

#include <QDialog>
#include <QDate>
#include <QDateTime>
#include <optional>
#include <string>
#include <vector>

#include "Event.h"  // for Event::Category and TimePoint

namespace Ui { class EventDialog; }

// EventDialog class
// This class is responsible for creating and editing events, validating user input and returning user choices back to MainWindow
class EventDialog : public QDialog {
    Q_OBJECT
public:

    // Constuctor
    explicit EventDialog(QWidget* parent = nullptr);
    ~EventDialog();

    // Function to prefill the date (Used when creating a new event)
    void prefillDate(const QDate& d);

    // Function to populate all fields based on an existing event
    void setEvent(const Event& e);

    // getter methods
    std::string title() const;
    QDateTime startDateTime() const;
    bool hasEnd() const;
    QDateTime endDateTime() const; // valid only if hasEnd()
    std::optional<Event::Category> category() const;
    std::optional<std::string> location() const;
    std::optional<std::string> notes() const;
    std::vector<int> remindersMinutesBefore() const;

private:
    Ui::EventDialog* _ui;

    //Helper to populate the dropdown menus
    void populateCategoryCombo();
    void populateReminderCombo();
    // Mapping helpers between ComboBox index and Category
    static int categoryToIndex(std::optional<Event::Category> cat);
    static std::optional<Event::Category> indexToCategory(int idx);

private slots:
    void onHasEndToggled(bool checked);
    void onAccept();
};
