#pragma once

#include <iostream>

#include "Utils.h"
#include "Validation.h"
#include "../constants/Lengths.h"
#include "../constants/Texts.h"
#include "../models/accounts/PersonAccount.h"

using namespace std;

class Input {
public:
    static void readNumber(
        short &value
    ) {
        cin >> value;
    }

    static void readNumber(
        int &value
    ) {
        cin >> value;
    }

    static void readNumber(
        float &value
    ) {
        cin >> value;
    }

    static void readNumber(
        double &value
    ) {
        cin >> value;
    }

    static void readNumber(
        long double &value
    ) {
        cin >> value;
    }

    static void readNumber(
        size_t &value
    ) {
        cin >> value;
    }

    static void readCharacter(
        char &value
    ) {
        cin >> value;
    }

    static void readWord(
        string &value
    ) {
        cin >> value;
    }

    static void readText(
        string &value
    ) {
        if (cin.peek() == '\n')
            cin.ignore();

        getline(
            cin,
            value
        );
    }

    static void readBoolean(
        bool &value
    ) {
        cin >> value;
    }

    static void readNumber(
        short &value,
        const string &MESSAGE
    ) {
        Utils::displayMessage(
            MESSAGE
        );

        readNumber(
            value
        );
    }

    static void readNumber(
        int &value,
        const string &MESSAGE
    ) {
        Utils::displayMessage(
            MESSAGE
        );

        readNumber(
            value
        );
    }

    static void readNumber(
        float &value,
        const string &MESSAGE
    ) {
        Utils::displayMessage(
            MESSAGE
        );

        readNumber(
            value
        );
    }

    static void readNumber(
        double &value,
        const string &MESSAGE
    ) {
        Utils::displayMessage(
            MESSAGE
        );

        readNumber(
            value
        );
    }

    static void readNumber(
        long double &value,
        const string &MESSAGE
    ) {
        Utils::displayMessage(
            MESSAGE
        );

        readNumber(
            value
        );
    }

    static void readNumber(
        size_t &value,
        const string &MESSAGE
    ) {
        Utils::displayMessage(
            MESSAGE
        );

        readNumber(
            value
        );
    }

    static void readCharacter(
        char &value,
        const string &MESSAGE
    ) {
        Utils::displayMessage(
            MESSAGE
        );

        readCharacter(
            value
        );
    }

    static void readWord(
        string &value,
        const string &MESSAGE
    ) {
        Utils::displayMessage(
            MESSAGE
        );

        readWord(
            value
        );
    }

    static void readText(
        string &value,
        const string &MESSAGE
    ) {
        Utils::displayMessage(
            MESSAGE
        );

        readText(
            value
        );
    }

    static void readBoolean(
        bool &value,
        const string &MESSAGE
    ) {
        Utils::displayMessage(
            MESSAGE + " (0 = no, 1 = yes)"
        );

        readBoolean(
            value
        );
    }

    static void readChoice(
        short &choice
    ) {
        do
            readNumber(
                choice,
                "Choose number:"
            );
        while (
            !Validation::isNumber()
        );
    }

    static void readChoice(
        short &choice,
        const short &FROM,
        const short &TO
    ) {
        do
            readChoice(
                choice
            );
        while (
            !Validation::isBetweenNumbers(
                choice,
                FROM,
                TO
            )
        );
    }

    static void readUsername(
        string &username
    ) {
        do
            readText(
                username,
                "Enter Username:"
            );
        while (
            !(
                username.length() >= Limits::Username::MINIMUM &&
                username.length() <= Limits::Username::MAXIMUM
            )
        );
    }

    static void readPassword(
        string &password
    ) {
        do
            readText(
                password,
                "Enter Password:"
            );
        while (
            !(
                password.length() >= Limits::Password::MINIMUM &&
                password.length() <= Limits::Password::MAXIMUM
            )
        );
    }

    static void readFirstName(
        string &firstName
    ) {
        do
            readText(
                firstName,
                "Enter First Name:"
            );
        while (
            !(
                firstName.length() >= Limits::FullName::FirstName::MINIMUM &&
                firstName.length() <= Limits::FullName::FirstName::MAXIMUM
            )
        );
    }

    static void readSecondName(
        string &secondName
    ) {
        do
            readText(
                secondName,
                "Enter Second Name:"
            );
        while (
            !(
                secondName.length() >= Limits::FullName::SecondName::MINIMUM &&
                secondName.length() <= Limits::FullName::SecondName::MAXIMUM
            )
        );
    }

    static void readFullName(
        PersonAccount::FullName &fullName
    ) {
        readFirstName(
            fullName.firstName
        );
        readSecondName(
            fullName.secondName
        );
    }

    static void readCountryCode(
        string &countryCode
    ) {
        do
            readText(
                countryCode,
                "Enter Country Code:"
            );
        while (
            !(
                countryCode.find(
                    '+'
                ) != string::npos &&
                countryCode.length() >= Limits::MobileNumber::CountryCode::MINIMUM &&
                countryCode.length() <= Limits::MobileNumber::CountryCode::MAXIMUM
            )
        );
    }

    static void readContactNumber(
        string &contactNumber
    ) {
        do
            readText(
                contactNumber,
                "Enter Contact Number:"
            );
        while (
            !(
                Validation::areTextNumbers(
                    contactNumber
                ) &&
                contactNumber.length() >= Limits::MobileNumber::ContactNumber::MINIMUM &&
                contactNumber.length() <= Limits::MobileNumber::ContactNumber::MAXIMUM
            )
        );
    }

    static void readMobileNumber(
        PersonAccount::MobileNumber &mobileNumber
    ) {
        readCountryCode(
            mobileNumber.countryCode
        );

        readContactNumber(
            mobileNumber.contactNumber
        );
    }

    static void readEmail(
        string &email
    ) {
        do
            readText(
                email,
                "Enter Email:"
            );
        while (
            !(
                Validation::isEmail(
                    email
                ) &&
                email.length() >= Limits::Email::MINIMUM &&
                email.length() <= Limits::Email::MAXIMUM
            )
        );
    }

    static bool readPermission(
        bool &status,
        const string &MESSAGE
    ) {
        do
            readBoolean(
                status,
                MESSAGE
            );
        while (
            !(
                Validation::isNumber() &&
                (
                    status == 0 ||
                    status == 1
                )
            )
        );
        return status;
    }

    static void readPIN_Code(
        string &pinCode
    ) {
        do
            readText(
                pinCode,
                "Enter PIN Code:"
            );
        while (
            pinCode.length() != Lengths::Person::Client::PIN_CODE ||
            !Validation::areTextNumbers(
                pinCode
            )
        );
    }

    static bool confirm() {
        bool status;
        readBoolean(
            status,
            Texts::CONFIRM_MESSAGE
        );
        return status;
    }

    static void readCount(
        long double &count
    ) {
        do {
            readNumber(
                count,
                "Enter Balance Count:"
            );
        } while (
            !(
                Validation::isNumber() &&
                Validation::isPositive(
                    count
                )
            )
        );
    }

    static void readCode(
        string &code
    ) {
        do {
            readText(
                code,
                "Enter Balance Code:"
            );
        } while (
            code.length() != Lengths::Person::Client::BALANCE_CODE ||
            !Validation::areTextCharacters(
                code
            )
        );
    }

    static void readID(
        string &id
    ) {
        short delimiterCount;
        do {
            readText(
                id,
                "Enter ID:"
            );
            delimiterCount = 0;
            for (
                short index = 0;
                delimiterCount < 3 && index < Lengths::Person::Client::ID;
                index++
            )
                if (id[index] == Texts::Person::Client::ID_DELIMITER)
                    delimiterCount++;
        } while (
            id.length() != Lengths::Person::Client::ID ||
            delimiterCount != 3
        );
    }
};