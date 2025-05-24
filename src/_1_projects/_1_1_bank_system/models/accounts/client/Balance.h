#pragma once

using namespace std;

class Balance {
    long double count;
    string code;

public:
    Balance(
        const long double &COUNT,
        const string &CODE
    ) {
        count = COUNT;
        code = CODE;
    }

    void setCount(
        const long double &COUNT
    ) {
        count = COUNT;
    }

    long double getCount() {
        return count;
    }

    void setCode(
        const string &CODE
    ) {
        code = CODE;
    }

    string getCode() {
        return code;
    }
};