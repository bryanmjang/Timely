//
// Created by bryan on 2025-11-09.
//

#ifndef TIMELY_IDGENERATOR_H
#define TIMELY_IDGENERATOR_H
#include <random>
#include <string>
#include <sstream>

using namespace std;

// Header file for an ID Generator
// It automatically generates an id upon being called.
struct IdGenerator {

    static string newId() {
        static random_device rd;
        static mt19937_64 gen(rd());
        static uniform_int_distribution<uint64_t> dist;

        uint64_t id = dist(gen);

        stringstream ss;
        ss << hex << id;
        return ss.str();
    }
};

#endif //TIMELY_IDGENERATOR_H
