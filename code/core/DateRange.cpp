//
// Created by bryan on 2025-11-08.
//

#include "DateRange.h"
#include <ctime>

using namespace std;

// Constructor
DateRange::DateRange(TimePoint from, TimePoint to)
    : _lowerBound(from), _upperBound(to) {}

DateRange::TimePoint DateRange::getLowerBound() const { return _lowerBound; }
DateRange::TimePoint DateRange::getUpperBound() const { return _upperBound; }

bool DateRange::contains(TimePoint tp) const {
    return (tp >= _lowerBound) && (tp < _upperBound);
}

// Function to see if a range overlaps with another
bool DateRange::overlaps(const DateRange &other) const {
    return (_lowerBound < other._upperBound) && (other._lowerBound < _upperBound);
}

// Helper function to find the date
DateRange::TimePoint DateRange::startOfDay(int year, int month, int day) {
    std::tm tm{};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;

    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;

    // mktime interprets tm as local time and normalizes fields
    std::time_t time = std::mktime(&tm);
    return chrono::system_clock::from_time_t(time);
}

// Function to find a 24 hour range
DateRange DateRange::forDay(int year, int month, int day) {
    TimePoint start = startOfDay(year, month, day);
    TimePoint end = start + chrono::hours(24);
    return DateRange(start, end);
}

// Function to find a range that spans a week.
DateRange DateRange::forWeekContaining(int year, int month, int day) {
    std::tm tm{};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;

    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    std::mktime(&tm);
    int wday = tm.tm_wday;

    DateRange::TimePoint dayStart = startOfDay(year, month, day);

    // Adjusting range boundaries to equal a week's worth of time
    TimePoint weekStart = dayStart - chrono::hours(24) * wday;
    TimePoint weekEnd = weekStart + chrono::hours(24 * 7);

    return DateRange(weekStart, weekEnd);
}





