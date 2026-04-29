//
// Created by bryan on 2025-11-11.
//

#include "JsonStorage.h"

#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QString>
#include <QDateTime>
#include <QIODevice>

#include <chrono>
#include <stdexcept>

using namespace std;

// Helper Method to convert time_point to "YYYY-MM-DD HH:MM:SS" string
string JsonStorage::toStringTime(const Event::TimePoint &tp) {
    using namespace std::chrono;
    const auto secs = time_point_cast<seconds>(tp).time_since_epoch().count();
    const QDateTime dt = QDateTime::fromSecsSinceEpoch(static_cast<qint64>(secs));
    return dt.toString("yyyy-MM-dd HH:mm:ss").toStdString();
}

// Helper Method to convert a string to a time_point
Event::TimePoint JsonStorage::toTimePoint(const string &s) {
    QDateTime dt = QDateTime::fromString(QString::fromStdString(s), "yyyy-MM-dd HH:mm:ss");
    if (!dt.isValid()) { throw runtime_error("Invalid date/time format in JSON " + s); }

    dt.setTimeZone(QTimeZone::LocalTime);
    using namespace std::chrono;
    return system_clock::time_point{ seconds{ dt.toSecsSinceEpoch()}};
}


// Function to save all of the events into the Json File
bool JsonStorage::save(const vector<Event>& all) {
    QJsonArray events;

    // Saving the field values for each seperate event. Does this by inserting values into a QJsonObject
    for (size_t i = 0; i < all.size(); i++) {
        const Event& e = all[i];
        QJsonObject obj;
        obj.insert("id", QString::fromStdString(e.getId()));
        obj.insert("title", QString::fromStdString(e.getTitle()));
        obj.insert("start", QString::fromStdString(toStringTime(e.getStart())));

        if (e.getEnd().has_value()) { obj.insert("end", QString::fromStdString(toStringTime(e.getEnd().value()))); }
        else { obj.insert("end", QJsonValue()); }

        if (e.getCategory().has_value()) {obj.insert("category", static_cast<int>(e.getCategory().value()));}
        else { obj.insert("category", QJsonValue()); }

        if (e.getLocation().has_value()) {obj.insert("location", QString::fromStdString(e.getLocation().value()));}
        else { obj.insert("location", QJsonValue()); }

        if (e.getNotes().has_value()) {obj.insert("notes", QString::fromStdString(e.getNotes().value()));}
        else { obj.insert("notes", QJsonValue()); }

        // Saving reminders
        QJsonArray reminders;
        for (int mins : e.getRemindersMinutesBefore()) reminders.append(mins);
        obj.insert("remindersMinutesBefore", reminders);
        events.append(obj);
    }

    // Validating the Json File
    QFile file(QString::fromStdString(_path));
    QFileInfo info(file);
    QDir dir = info.dir();
    if (!dir.exists()) { dir.mkpath("."); }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        throw runtime_error("Unable to open file for writing: " + _path);
    }

    // Writing to the Json file
    QJsonDocument doc(events);
    file.write(doc.toJson());
    file.close();

    return true;
}


// Function to load all events.
vector<Event> JsonStorage::load() {
    vector<Event> result;

    // Reading Json file
    QFile file(QString::fromStdString(_path));
    if (!file.open(QIODevice::ReadOnly)) {
        throw runtime_error("Unable to open file for reading: " + _path);
    }

    const QByteArray data = file.readAll();
    file.close();

    QJsonParseError perr;
    QJsonDocument doc = QJsonDocument::fromJson(data, &perr);
    if (perr.error != QJsonParseError::NoError) {
        throw runtime_error("Error parsing JSON: " + perr.errorString().toStdString());
    }

    if (!doc.isArray()) { throw runtime_error("JSON root must be an array of events."); }

    // Json array of events
    QJsonArray arr = doc.array();
    result.reserve(static_cast<size_t>(arr.size()));

    // Filling the array and going through each event to get its field values
    for (int i = 0; i < arr.size(); i++) {
        if (!arr[i].isObject()) continue;
        QJsonObject currEvent = arr[i].toObject();

        const string id = currEvent.value("id").toString().toStdString();
        const string title = currEvent.value("title").toString().toStdString();
        const Event::TimePoint start = toTimePoint(currEvent.value("start").toString().toStdString());

        optional<Event::TimePoint> end = nullopt;
        if (currEvent.contains("end") && !currEvent.value("end").isNull()) {
            end = toTimePoint(currEvent.value("end").toString().toStdString());
        }

        optional<Event::Category> category = nullopt;
        if (currEvent.contains("category") && !currEvent.value("category").isNull()) {
            category = static_cast<Event::Category>(currEvent.value("category").toInt());
        }

        optional<string> location = nullopt;
        if (currEvent.contains("location") && !currEvent.value("location").isNull()) {
            location = currEvent.value("location").toString().toStdString();
        }

        optional<string> notes = nullopt;
        if (currEvent.contains("notes") && !currEvent.value("notes").isNull()) {
            notes = currEvent.value("notes").toString().toStdString();
        }

        Event e(id, title, start, end, category, location, notes);

        // Reminders
        vector<int> reminders;
        if (currEvent.contains("remindersMinutesBefore") && currEvent.value("reminderMinutesBefore").isArray()) {
            QJsonArray a = currEvent.value("remindersMinutesBefore").toArray();
            reminders.reserve(a.size());
            for (const auto& v : a) reminders.push_back(v.toInt());
        }

        e.setRemindersMinutesBefore(std::move(reminders));

        // Appending the current event to the end of the vector
        result.push_back(std::move(e));

    }
    return result;
}




