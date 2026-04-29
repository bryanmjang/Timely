//
// Created by bryan on 2025-11-07.
//

#pragma once

#include <string>
#include <optional>
#include <chrono>
#include <vector>

using namespace std;

// Event Class
// This is the main object of the calendar. It has several different fields (as listed below).
class Event {
public:
    using TimePoint = chrono::system_clock::time_point;

    // Enum for ease of use and simplicity
    enum class Category {
        School,
        Work,
        Personal,
        Other,
    };

    Event() = default;

    Event(string id,
          string title,
          TimePoint start,
          optional<TimePoint> end = nullopt,
          optional<Category> category = nullopt,
          optional<string> location = nullopt,
          optional<string> notes = nullopt);

    // Getters
    const string& getId() const;
    const string& getTitle() const;
    TimePoint getStart() const;
    optional<TimePoint> getEnd() const;
    optional<Category> getCategory() const;
    const optional<string>& getLocation() const;
    const optional<string>& getNotes() const;

    const vector<int>& getRemindersMinutesBefore() const {return _remindersMinutesBefore; }
    void setRemindersMinutesBefore(vector<int> v) { _remindersMinutesBefore = std::move(v); }

private:
    string _id;
    string _title;
    TimePoint _start;
    optional<TimePoint> _end;
    optional<Category> _category;
    optional<string> _location;
    optional<string> _notes;
    vector<int> _remindersMinutesBefore;
};
