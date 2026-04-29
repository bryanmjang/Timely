//
// Created by bryan on 2025-11-10.
//

#ifndef TIMELY_EVENTMANAGER_H
#define TIMELY_EVENTMANAGER_H

#include <unordered_map>
#include <unordered_set>
#include <map>
#include <functional>
#include <optional>
#include <string>

#include "Event.h"
#include "DateRange.h"
#include "IdGenerator.h"
#include "TextQuery.h"
#include "Validate.h"

using namespace std;

// EventManager Class
// This is the class that handles all the events. Events are stored in 2 ways: Unordered map (mapped by id) and Multimap (mapped in chronological order).
// We use 2 maps to optimize speed. Sometimes users will search by title, id, or category, other times they will search by date/time.
// We use a multimap because multiple events could happen at the same time.
// Class is responsible for notifying observers (UI) when data changes.
class EventManager {
public:
    using Id = string;
    using TimePoint = Event::TimePoint;
    using Listener = function<void()>;

    // CRUD operations
    const Event& create(const Event& e);
    bool update(const Event& e);
    bool remove(const string& id);

    // Query functions
    vector<Event> all() const;
    vector<Event> inRange(const DateRange& range) const;
    vector<Event> onDate(int year, int month, int day) const;
    vector<Event> searchByTitle(const TextQuery& text) const;

    // Observer
    void subscribe(Listener l) { _listeners.push_back(std::move(l)); }
private:
    // Primary store for events (mapped by ID)
    unordered_map<Id, Event> _idMap;

    // Secondary store for events (mapped by Time)
    multimap<TimePoint, Id> _timeMap;

    // Iterator to go through the maps
    unordered_map<Id, multimap<TimePoint, Id>::iterator> _iterateIdMap;

    // List of functions to call when data changes
    vector<Listener> _listeners;

    // Helper functions
    static string toLower(string s);
    static bool contains(const string& hay, const string& needle);
    static Event cloneWithId(const Event& e, const string& newId);

    void indexInsert(const Event& e);
    void indexRemove(const Id& id);
    void indexUpdate(const Event& before, const Event& after);

    string uniqueId() const;
    void notify() const;
};


#endif //TIMELY_EVENTMANAGER_H
