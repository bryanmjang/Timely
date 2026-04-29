//
// Created by bryan on 2025-11-11.
//

#ifndef TIMELY_ISTORAGE_H
#define TIMELY_ISTORAGE_H

#include <vector>
#include <string>
#include <stdexcept>
#include <vector>

#include "Event.h"

using namespace std;

class IStorage {
public:
    virtual ~IStorage() = default;

    // Human readable description or path
    virtual string location() const = 0;

    // Function to save all the events, returns true on success
    virtual bool save(const vector<Event>& all) = 0;

    // Load all events from storage
    virtual vector<Event> load() = 0;
};

#endif //TIMELY_ISTORAGE_H