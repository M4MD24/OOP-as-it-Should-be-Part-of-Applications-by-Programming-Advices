#pragma once

#include <cfloat>
#include <iostream>
#include <limits>

using namespace std;

class Validation {
public:
    static bool isNumber() {
        if (
            const bool VALID = !cin.fail();
            !VALID
        ) {
            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );
            return false;
        }
        return true;
    }

    static bool isNumber(
        const short &NUMBER
    ) {
        return NUMBER >= SHRT_MIN && NUMBER <= SHRT_MAX;
    }

    static bool isNumber(
        const int &NUMBER
    ) {
        return NUMBER >= INT_MIN && NUMBER <= INT_MAX;
    }

    static bool isNumber(
        const float &NUMBER
    ) {
        return NUMBER >= FLT_MIN && NUMBER <= FLT_MAX;
    }

    static bool isNumber(
        const double &NUMBER
    ) {
        return NUMBER >= DBL_MIN && NUMBER <= DBL_MAX;
    }

    static bool isNumber(
        const long double &NUMBER
    ) {
        return NUMBER >= LDBL_MIN && NUMBER <= LDBL_MAX;
    }

    static bool isPositive(
        const short &NUMBER
    ) {
        return NUMBER > 0;
    }

    static bool isPositive(
        const int &NUMBER
    ) {
        return NUMBER > 0;
    }

    static bool isPositive(
        const float &NUMBER
    ) {
        return NUMBER > 0;
    }

    static bool isPositive(
        const double &NUMBER
    ) {
        return NUMBER > 0;
    }

    static bool isPositive(
        const long double &NUMBER
    ) {
        return NUMBER > 0;
    }

    static bool isBetweenNumbers(
        const short &NUMBER,
        const short &FROM,
        const short &TO
    ) {
        return NUMBER >= FROM && NUMBER <= TO;
    }

    static bool isBetweenNumbers(
        const int &NUMBER,
        const int &FROM,
        const int &TO
    ) {
        return NUMBER >= FROM && NUMBER <= TO;
    }

    static bool isBetweenNumbers(
        const float &NUMBER,
        const float &FROM,
        const float &TO
    ) {
        return NUMBER >= FROM && NUMBER <= TO;
    }

    static bool isBetweenNumbers(
        const double &NUMBER,
        const double &FROM,
        const double &TO
    ) {
        return NUMBER >= FROM && NUMBER <= TO;
    }

    static bool isBetweenNumbers(
        const long double &NUMBER,
        const long double &FROM,
        const long double &TO
    ) {
        return NUMBER >= FROM && NUMBER <= TO;
    }

    static bool areTextNumbers(
        const string &TEXT
    ) {
        for (const char &CHARACTER : TEXT)
            if (
                !isdigit(
                    CHARACTER
                )
            )
                return false;
        return true;
    }

    static bool isEmail(
        const string &EMAIL
    ) {
        const int AT_POSITION = EMAIL.find(
            '@'
        );

        const int DOT_POSITION = EMAIL.find(
            '.',
            AT_POSITION + 1
        );

        if (
            AT_POSITION <= 0 ||
            AT_POSITION != EMAIL.rfind(
                '@'
            ) ||
            AT_POSITION == EMAIL.length() - 1
        )
            return false;

        if (
            DOT_POSITION == string::npos ||
            DOT_POSITION == EMAIL.length() - 1
        )
            return false;

        return true;
    }
};