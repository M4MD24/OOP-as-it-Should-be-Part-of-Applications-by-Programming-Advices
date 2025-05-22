#pragma once

#include <string>

using namespace std;

class Balance {
    string name;
    string code;
    long double count;

public:
    Balance(
        const string &NAME,
        const string &CODE,
        const long double COUNT
    ) {
        name = NAME;
        code = CODE;
        count = COUNT;
    }

    void setName(
        const string &NAME
    ) {
        name = NAME;
    }

    string getName() {
        return name;
    }

    void setCode(
        const string &CODE
    ) {
        code = CODE;
    }

    string getCode() {
        return code;
    }

    void setCount(
        const long double &COUNT
    ) {
        count = COUNT;
    }

    long double getCount() {
        return count;
    }
};