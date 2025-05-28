#pragma once
#include <iostream>
#include <chrono>
#include <vector>
#include <string>

using namespace std;
using namespace chrono;

class Time {
    short seconds,
          minutes,
          hours;
    static inline const string DEFAULT_DELIMITER = ":";
    string delimiter = DEFAULT_DELIMITER;

    static Time getSystemTime() {
        const time_t TIME = time(
            nullptr
        );
        const tm *TIME_NOW = localtime(
            &TIME
        );
        return {
            static_cast<short>(TIME_NOW->tm_sec),
            static_cast<short>(TIME_NOW->tm_min),
            static_cast<short>(TIME_NOW->tm_hour)
        };
    }

    static void splitText(
        string text,
        vector<short> &parts,
        const string &DELIMITER
    ) {
        size_t position;
        while (
            (
                position = text.find(
                    DELIMITER
                )
            ) != string::npos
        ) {
            parts.push_back(
                static_cast<short>(
                    stoi(
                        text.substr(
                            0,
                            position
                        )
                    )
                )
            );
            text.erase(
                0,
                position + DELIMITER.length()
            );
        }
        parts.push_back(
            static_cast<short>(
                stoi(
                    text
                )
            )
        );
    }

    static vector<short> convertTimeTextToTimeParts(
        const string &TIME_TEXT,
        const string &DELIMITER = DEFAULT_DELIMITER
    ) {
        vector<short> timeParts;
        splitText(
            TIME_TEXT,
            timeParts,
            DELIMITER
        );
        return timeParts;
    }

    static Time convertTimePartsToTimeStructure(
        const vector<short> &TIME_PARTS,
        const string &DELIMITER = DEFAULT_DELIMITER
    ) {
        return {
            TIME_PARTS[0],
            TIME_PARTS[1],
            TIME_PARTS[2],
            DELIMITER
        };
    }

    static Time convertTimeTextToTimeStructure(
        const string &TIME_TEXT,
        const string &DELIMITER = DEFAULT_DELIMITER
    ) {
        return convertTimePartsToTimeStructure(
            convertTimeTextToTimeParts(
                TIME_TEXT,
                DELIMITER
            ),
            DELIMITER
        );
    }

public:
    Time() {
        const Time TIME_NOW = getSystemTime();
        seconds = TIME_NOW.seconds;
        minutes = TIME_NOW.minutes;
        hours = TIME_NOW.hours;
        delimiter = DEFAULT_DELIMITER;
    }

    Time(
        const short &SECONDS,
        const short &MINUTES,
        const short &HOURS,
        const string &DELIMITER = DEFAULT_DELIMITER
    ) {
        seconds = SECONDS;
        minutes = MINUTES;
        hours = HOURS;
        delimiter = DELIMITER;
    }

    string getTimeText() {
        return to_string(
                hours
            ) + delimiter
            + to_string(
                minutes
            ) + delimiter
            + to_string(
                seconds
            );
    }
};