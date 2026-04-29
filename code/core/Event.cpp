//
// Created by bryan on 2025-11-07.
//

#include "Event.h"

using namespace std;

// Constructor for an Event. Initializing fields.
Event::Event(string id, string title, TimePoint start, optional<TimePoint> end, optional<Category> category, optional<string> location, optional<string> notes)
    : _id(move(id)),
    _title(move(title)),
    _start(move(start)),
    _end(move(end)),
    _category(move(category)),
    _location(move(location)),
    _notes(move(notes)) {}


// Getter methods
const string& Event::getId() const {
    return _id;
}

const string& Event::getTitle() const {
    return _title;
}

Event::TimePoint Event::getStart() const {
    return _start;
}

optional<Event::TimePoint> Event::getEnd() const {
    return _end;
}

optional<Event::Category> Event::getCategory() const {
    return _category;
}

const optional<string>& Event::getLocation() const {
    return _location;
}

const optional<string>& Event::getNotes() const {
    return _notes;
}
