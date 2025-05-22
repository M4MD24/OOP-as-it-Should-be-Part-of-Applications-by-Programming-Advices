#pragma once

#include <fstream>

#include "../PersonAccount.h"
#include "../../../constants/Delimiters.h"
#include "../../../libraries/date/Date.h"
#include "../../../libraries/String.h"
#include "../../../constants/FilePaths.h"
#include "../../../libraries/Utils.h"

using namespace std;

class OwnerAccount : protected PersonAccount {
public:
    enum OwnerMenuChoice {
        CreateNewAdmin = 0,
        ModifyAdmin = 1,
        DeleteAdmin = 2,
        FindAdmin = 3,
        AdminList = 4,
        TotalBalances = 5,
        AdminEventLog = 6,
        Logout = 7
    };

private:
    string username;
    string password;

    static void readAccountFields(
        OwnerAccount &ownerAccount,
        const vector<string> &FIELDS
    ) {
        if (FIELDS.size() == 9) {
            ownerAccount.setUsername(
                FIELDS[0]
            );
            ownerAccount.setPassword(
                FIELDS[1]
            );
            ownerAccount.setFullName(
                {
                    FIELDS[2],
                    FIELDS[3]
                }
            );
            ownerAccount.setMobileNumber(
                {
                    FIELDS[4],
                    FIELDS[5]
                }
            );
            ownerAccount.setEmail(
                FIELDS[6]
            );
            ownerAccount.setJoinDate(
                {
                    FIELDS[7]
                }
            );
            ownerAccount.setLastModifyDate(
                {
                    FIELDS[8]
                }
            );
        }
    }

    OwnerAccount(): PersonAccount(
        {},
        {},
        {},
        {},
        {}
    ) {}

    OwnerAccount(
        const string &USERNAME
    ): PersonAccount(
        {},
        {},
        {},
        {},
        {}
    ) {
        username = USERNAME;
    }

public:
    OwnerAccount(
        const string &USERNAME,
        const string &PASSWORD
    ): PersonAccount(
        {},
        {},
        {},
        {},
        {}
    ) {
        username = USERNAME;
        password = PASSWORD;
    }

    OwnerAccount(
        const string &USERNAME,
        const string &PASSWORD,
        const FullName &FULL_NAME,
        const MobileNumber &MOBILE_NUMBER,
        const string &EMAIL,
        const Date &JOIN_DATE,
        const Date &LAST_MODIFY_DATE
    ): PersonAccount(
        FULL_NAME,
        MOBILE_NUMBER,
        EMAIL,
        JOIN_DATE,
        LAST_MODIFY_DATE
    ) {
        username = USERNAME;
        password = PASSWORD;
    }

    void setUsername(
        const string &USERNAME
    ) {
        username = USERNAME;
    }

    string getUsername() {
        return username;
    }

    void setPassword(
        const string &PASSWORD
    ) {
        password = PASSWORD;
    }

    string getPassword() {
        return password;
    }

    static vector<OwnerAccount> readAccountsFileToRecords() {
        vector<OwnerAccount> accounts;

        fstream file {
            FilePaths::OWNER_ACCOUNTS_FILE_PATH,
            ios::in
        };

        if (file.is_open()) {
            string line;
            while (
                getline(
                    file,
                    line
                )
            ) {
                OwnerAccount account;
                vector<string> fields;

                String::splitText(
                    line,
                    fields,
                    Delimiters::ACCOUNT_FIELDS
                );

                readAccountFields(
                    account,
                    fields
                );
                accounts.push_back(
                    account
                );
            }
        }

        file.close();

        return accounts;
    }

    static OwnerAccount findByUsernameAndPasswordInFile(
        OwnerAccount &targetOwnerAccount
    ) {
        for (OwnerAccount &currentOwnerAccount : readAccountsFileToRecords())
            if (targetOwnerAccount.getUsername() == currentOwnerAccount.getUsername()) {
                if (targetOwnerAccount.getPassword() == currentOwnerAccount.getPassword())
                    return currentOwnerAccount;
                return targetOwnerAccount.getUsername();
            }
        return {};
    }

    static bool isValidAccountByUsernameAndPassword(
        OwnerAccount &currentAccount,
        OwnerAccount targetAccount
    ) {
        if (currentAccount.getUsername() == targetAccount.getUsername()) {
            if (currentAccount.getPassword() == targetAccount.getPassword())
                return true;
            Utils::displayMessage(
                "Invalid Password"
            );
            return false;
        }
        Utils::displayMessage(
            "Invalid Username"
        );
        return false;
    }
};