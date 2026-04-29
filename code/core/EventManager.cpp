//
// Created by bryan on 2025-11-10.
//

#include "EventManager.h"
#include <cctype>
#include <algorithm>
#include <stdexcept>

using namespace std;

// Function validates incoming event, assigns a unique ID if needed, inserts it into the map, and returns a reference to the stored event
const Event& EventManager::create(const Event& e) {
    if (auto err = Validate::event(e)) {
        throw runtime_error(err -> message);
    }

    // Ensuring Unique ID
    string id = e.getId();
    if (id.empty() || _idMap.count(id)) {
        id = uniqueId();
    }

    // Inserting into map
    Event insert = cloneWithId(e, id);
    _idMap[id] = insert;
    Event& ref = _idMap.at(id);
    indexInsert(ref);

    // Notifying listeners
    notify();
    return ref;
}

// Function to update the event
bool EventManager::update(const Event& e) {
    if (e.getId().empty()) { return false; }
    if (!_idMap.count(e.getId())) { return false; }

    if (auto err = Validate::event(e)) {
        throw runtime_error(err -> message);
    }
    Event& current = _idMap.at(e.getId());
    indexUpdate(current, e);
    current = e;

    notify();
    return true;

}

// Function to remove an event
bool EventManager::remove(const string &id) {
    auto it = _idMap.find(id);
    if (it == _idMap.end()) { return false; }

    indexRemove(id);
    _idMap.erase(it);
    notify();
    return true;
}

// Function to return all events stored
vector<Event> EventManager::all() const {
    vector<Event> result;
    result.reserve(_idMap.size());

    for (auto it = _timeMap.begin(); it != _timeMap.end(); ++it) {
        const string& id = it->second;

        auto found = _idMap.find(id);
        if (found != _idMap.end()) result.push_back(found->second);
    }
    return result;
}

// Function to return all events in a certain range
vector<Event> EventManager::inRange(const DateRange& range) const {
    vector<Event> result;

    auto itL = _timeMap.lower_bound(range.getLowerBound());
    for (auto it = itL; it != _timeMap.end() && it->first < range.getUpperBound(); ++it) {
        const string& id = it->second;
        auto eventID = _idMap.find(id);
        if (eventID != _idMap.end()) {
            result.push_back(eventID->second);
        }
    }
    return result;
}

// Function to return all events on a certain date
vector<Event> EventManager::onDate(int year, int month, int day) const {
    return inRange(DateRange::forDay(year, month, day));
}

// Function to search for an event by title
vector<Event> EventManager::searchByTitle(const TextQuery& text) const {
    vector<Event> base = all();
    vector<Event> result;
    result.reserve(base.size());

    for (const auto& e : base) {
        if (contains(e.getTitle(), text.text)) result.push_back(e);
    }

    return result;
}


// Helper function to get rid of capitals in a string
string EventManager::toLower(string s) {
    for (size_t i = 0; i < s.size(); i++) {
        unsigned char ch = static_cast<unsigned char>(s[i]);
        s[i] = static_cast<char>(tolower(ch));
    }
    return s;
}

// Helper function to see if a string is a subset of a larger string
bool EventManager::contains(const string& hay, const string& needle) {
    if (needle.empty()) { return true; }
    return toLower(hay).find(toLower(needle)) != string::npos;
}

// Helper function to clone an event with a new ID
Event EventManager::cloneWithId(const Event& e, const string& newId) {
    Event out{newId, e.getTitle(), e.getStart(), e.getEnd(), e.getCategory(), e.getLocation(), e.getNotes()};
    out.setRemindersMinutesBefore(e.getRemindersMinutesBefore());
    return out;
}

// Helper function to add events into the time map
void EventManager::indexInsert(const Event &e) {
    auto it = _timeMap.insert(make_pair(e.getStart(), e.getId()));
    _iterateIdMap[e.getId()] = it;
}

// Helper function to remove events from the time map
void EventManager::indexRemove(const Id &id) {
    auto pos = _iterateIdMap.find(id);
    if (pos != _iterateIdMap.end()) {
        _timeMap.erase(pos->second);
        _iterateIdMap.erase(pos);
    }
}

// Helper function to update the time map if the start time of the event is updated.
void EventManager::indexUpdate(const Event &old, const Event &newEvent) {
    if (old.getStart() == newEvent.getStart()) { return ; }

    if (auto pos = _iterateIdMap.find(old.getId()); pos != _iterateIdMap.end()) {
        _timeMap.erase(pos->second);
        _iterateIdMap.erase(pos);
    }
    auto newIt = _timeMap.insert(make_pair(newEvent.getStart(), newEvent.getId()));
    _iterateIdMap[newEvent.getId()] = newIt;
}

// Helper function that calls IdGenerator until it generates a key that is not in use
string EventManager::uniqueId() const {
    while (true) {
        string id = IdGenerator::newId();
        if (_idMap.count(id) == 0) { return id; }
    }
}

// Helpfer function to call all listeners
void EventManager::notify() const {
    for (size_t i = 0; i < _listeners.size(); i++) {
        const Listener& l = _listeners[i];
        if (l) l();
    }
}
