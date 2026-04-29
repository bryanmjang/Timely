//
// Created by bryan on 2025-11-08.
//

#ifndef TIMELY_VALIDATE_H
#define TIMELY_VALIDATE_H

#include <string>
#include <optional>
#include <algorithm>
#include <cctype>

#include "Event.h"

using namespace std;

// Header file used for validating events.
struct ValidationError {
    string message;
};


struct Validate {

    // Validating event field entries.
    static optional<ValidationError> event(const Event& event) {
        if (!nonEmpty(event.getTitle())) {
            return ValidationError{"Title must not be empty."};
        }

        // Making sure event doesn't end before it starts
        if (!chronological(event)) {
            return ValidationError{"If both times are set, End Time must be later than Start Time."};
        }
        return nullopt;
    }

    // Helper function to check chronological order
    static bool chronological(const Event& event) {
        if (!event.getEnd()) return true;
        return event.getStart() <= *event.getEnd();
    }

    // Helper functions to see if Title is not empty
    static string trimCopy(string s) {
        auto notspace = [](unsigned char ch){ return !std::isspace(ch); };
        auto b = std::find_if(s.begin(), s.end(), notspace);
        auto e = std::find_if(s.rbegin(), s.rend(), notspace).base();
        if (b >= e) return {};
        return string(b, e);
    }

    static bool nonEmpty(const string& s) {
        return !trimCopy(s).empty();
    }


};


#endif //TIMELY_VALIDATE_H
