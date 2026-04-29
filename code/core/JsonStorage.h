//
// Created by bryan on 2025-11-11.
//

#ifndef TIMELY_QTJSONSTORAGE_H
#define TIMELY_QTJSONSTORAGE_H

#include <string>
#include <vector>
#include <optional>

#include "IStorage.h"
#include "Event.h"

using namespace std;

// File for JsonStorage. Uses built-in Qt Json library
class JsonStorage : public IStorage {
public:
    explicit JsonStorage(string path) : _path(move(path)) {}

    string location() const override { return _path; }

    bool save(const vector<Event>& all) override;

    vector<Event> load() override;

private:
    string _path;

    // Helpers convert between std::chrono time_point and a simple local-time string.
    static string toStringTime(const Event::TimePoint& tp);
    static Event::TimePoint toTimePoint(const string& s);
};

#endif //TIMELY_QTJSONSTORAGE_H
