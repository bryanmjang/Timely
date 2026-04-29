//
// Created by bryan on 2025-11-08.
//

#pragma once

#include <chrono>

using namespace std;

// DateRange Class
// Used to find a range of time -> [from, to)
// Useful for when user wants to search for an event on a certain week or time range.
class DateRange {
public:
    using TimePoint = chrono::time_point<chrono::system_clock>;

    DateRange(TimePoint from, TimePoint to);

    // Getters
    TimePoint getLowerBound() const;
    TimePoint getUpperBound() const;

    bool contains(TimePoint tp) const;
    bool overlaps(const DateRange& other) const;

    static DateRange forDay(int year, int month, int day);
    static DateRange forWeekContaining(int year, int month, int day);

private:
    TimePoint _lowerBound;
    TimePoint _upperBound;

    static TimePoint startOfDay(int year, int month, int day);
};
