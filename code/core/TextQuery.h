//
// Created by bryan on 2025-11-09.
//

#ifndef TIMELY_TEXTQUERY_H
#define TIMELY_TEXTQUERY_H

#include <string>
#include <optional>
#include "Event.h"
#include "DateRange.h"

using namespace std;

// Header file for searching for events via text
struct TextQuery {
    string text = "";
    optional<Event::Category> category = nullopt;
    optional<DateRange> range = nullopt;
};

#endif //TIMELY_TEXTQUERY_H
