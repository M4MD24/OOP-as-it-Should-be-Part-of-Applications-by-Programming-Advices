#pragma once

#include <iostream>

using namespace std;

class Input {
public:
    static short readNumber(
        short &value
    ) {
        cin >> value;
        return value;
    }

    static int readNumber(
        int &value
    ) {
        cin >> value;
        return value;
    }

    static float readNumber(
        float &value
    ) {
        cin >> value;
        return value;
    }

    static double readNumber(
        double &value
    ) {
        cin >> value;
        return value;
    }

    static long double readNumber(
        long double &value
    ) {
        cin >> value;
        return value;
    }

    static size_t readNumber(
        size_t &value
    ) {
        cin >> value;
        return value;
    }

    static char readCharacter(
        char &value
    ) {
        cin >> value;
        return value;
    }

    static string readWord(
        string &value
    ) {
        cin >> value;
        return value;
    }

    static string readText(
        string &value
    ) {
        getline(
            cin,
            value
        );
        return value;
    }

    static bool readBoolean(
        bool &value
    ) {
        cin >> value;
        return value;
    }
};