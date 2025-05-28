#pragma once

#include "../../libraries/datetime/Date.h"

using namespace std;

class PersonAccount {
public:
    enum AccountType {
        Owner = 0,
        Admin = 1,
        Client = 2
    };

    struct MobileNumber {
        string countryCode;
        string contactNumber;
    };

    struct FullName {
        string firstName;
        string secondName;
    };

private:
    FullName fullName;
    MobileNumber mobileNumber;
    string email;
    Date joinDate;
    Date lastModifyDate;

public:
    PersonAccount(
        const FullName &FULL_NAME,
        const MobileNumber &MOBILE_NUMBER,
        const string &EMAIL,
        const Date &JOIN_DATE,
        const Date &LAST_MODIFY_DATE
    ) {
        fullName = FULL_NAME;
        mobileNumber = MOBILE_NUMBER;
        email = EMAIL;
        joinDate.setDate(
            JOIN_DATE
        );
        lastModifyDate.setDate(
            LAST_MODIFY_DATE
        );
    }

    void setFirstName(
        const string &FIRST_NAME
    ) {
        fullName.firstName = FIRST_NAME;
    }

    string getFirstName() {
        return fullName.firstName;
    }

    void setSecondName(
        const string &SECOND_NAME
    ) {
        fullName.secondName = SECOND_NAME;
    }

    string getSecondName() {
        return fullName.secondName;
    }

    void setFullName(
        const FullName &FIRST_NAME
    ) {
        fullName = FIRST_NAME;
    }

    FullName getFullName() {
        return fullName;
    }

    string getFullNameText() {
        return fullName.firstName + ' ' + fullName.secondName;
    }

    void setCountryCode(
        const string &COUNTRY_CODE
    ) {
        mobileNumber.countryCode = COUNTRY_CODE;
    }

    string getCountryCode() {
        return mobileNumber.countryCode;
    }

    void setContactNumber(
        const string &CONTACT_NUMBER
    ) {
        mobileNumber.contactNumber = CONTACT_NUMBER;
    }

    string getContactNumber() {
        return mobileNumber.contactNumber;
    }

    void setMobileNumber(
        const MobileNumber &MOBILE_NUMBER
    ) {
        mobileNumber = MOBILE_NUMBER;
    }

    MobileNumber getMobileNumber() {
        return mobileNumber;
    }

    string getMobileNumberText() {
        return mobileNumber.countryCode + mobileNumber.contactNumber;
    }

    void setEmail(
        const string &EMAIL
    ) {
        email = EMAIL;
    }

    string getEmail() {
        return email;
    }

    void setJoinDate(
        const Date &JOIN_DATE
    ) {
        joinDate.setDate(
            JOIN_DATE
        );
    }

    Date getJoinDate() {
        return joinDate;
    }

    void setLastModifyDate(
        const Date &LAST_MODIFY_DATE
    ) {
        lastModifyDate.setDate(
            LAST_MODIFY_DATE
        );
    }

    Date getLastModifyDate() {
        return lastModifyDate;
    }
};