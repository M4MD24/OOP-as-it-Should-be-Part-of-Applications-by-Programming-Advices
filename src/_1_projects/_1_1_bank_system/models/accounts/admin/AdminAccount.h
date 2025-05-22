#pragma once

#include <fstream>

#include "../PersonAccount.h"
#include "../../../constants/Delimiters.h"
#include "../../../constants/FilePaths.h"
#include "../../../constants/Lengths.h"
#include "../../../constants/Texts.h"
#include "../../../libraries/Input.h"
#include "../../../libraries/date/Date.h"
#include "../../../libraries/String.h"
#include "../../../libraries/Utils.h"

using namespace std;

class AdminAccount : protected PersonAccount {
public:
    enum AdminPermission {
        Create = 0,
        Modify = 1,
        Delete = 2,
        Find = 3,
        ShowList = 4,
        Transaction = 5
    };

    enum AdminMenuChoice {
        CreateNewClient = 0,
        ModifyClient = 1,
        DeleteClient = 2,
        FindClient = 3,
        ClientList = 4,
        TransactionClient = 5,
        Logout = 6
    };

private:
    string username;
    string password;
    vector<AdminPermission> permissions;

    static vector<AdminPermission> readPermissionsFields(
        const string &PERMISSIONS_TEXT
    ) {
        vector<AdminPermission> permissions;

        vector<string> permissionValues;
        String::splitText(
            PERMISSIONS_TEXT,
            permissionValues,
            Delimiters::PERMISSIONS
        );

        for (const string &PERMISSION : permissionValues) {
            if (
                !PERMISSION.empty()
            )
                permissions.push_back(
                    static_cast<AdminPermission>(
                        stoi(
                            PERMISSION
                        )
                    )
                );
        }

        return permissions;
    }

    static void readAccountFields(
        AdminAccount &adminAccount,
        const vector<string> &FIELDS
    ) {
        if (FIELDS.size() == 10) {
            adminAccount.setUsername(
                FIELDS[0]
            );
            adminAccount.setPassword(
                FIELDS[1]
            );
            adminAccount.setFullName(
                {
                    FIELDS[2],
                    FIELDS[3]
                }
            );
            adminAccount.setMobileNumber(
                {
                    FIELDS[4],
                    FIELDS[5]
                }
            );
            adminAccount.setEmail(
                FIELDS[6]
            );
            adminAccount.setPermissions(
                readPermissionsFields(
                    FIELDS[7]
                )
            );
            adminAccount.setJoinDate(
                {
                    FIELDS[8]
                }
            );
            adminAccount.setLastModifyDate(
                {
                    FIELDS[9]
                }
            );
        }
    }

    static void printBody(
        AdminAccount &adminAccount
    ) {
        cout << '|';

        Utils::displayMessage(
            adminAccount.username,
            Lengths::Person::Admin::USERNAME
        );

        Utils::displayMessage(
            adminAccount.password,
            Lengths::Person::Admin::PASSWORD
        );

        Utils::displayMessage(
            adminAccount.getFullNameText(),
            Lengths::Person::FULL_NAME
        );

        Utils::displayMessage(
            adminAccount.getMobileNumberText(),
            Lengths::Person::MOBILE_NUMBER
        );

        Utils::displayMessage(
            adminAccount.getEmail(),
            Lengths::Person::EMAIL
        );

        bool permissions[Lengths::Person::Admin::COUNT_OF_PERMISSIONS] = {
            false
        };
        for (const AdminPermission &ADMIN_PERMISSION : adminAccount.permissions)
            permissions[static_cast<short>(ADMIN_PERMISSION)] = true;
        if (adminAccount.permissions.empty())
            Utils::displayMessage(
                false,
                Lengths::Person::Admin::Permissions::CREATE
            );
        else
            Utils::displayMessage(
                permissions[0],
                Lengths::Person::Admin::Permissions::CREATE
            );
        Utils::displayMessage(
            permissions[1],
            Lengths::Person::Admin::Permissions::MODIFY
        );
        Utils::displayMessage(
            permissions[2],
            Lengths::Person::Admin::Permissions::DELETE
        );
        Utils::displayMessage(
            permissions[3],
            Lengths::Person::Admin::Permissions::SEARCH
        );
        Utils::displayMessage(
            permissions[4],
            Lengths::Person::Admin::Permissions::SHOW_LIST
        );
        Utils::displayMessage(
            permissions[5],
            Lengths::Person::Admin::Permissions::TRANSACTION
        );

        Utils::displayMessage(
            adminAccount.getJoinDate().getDateText(),
            Lengths::Person::JOIN_DATE
        );

        Utils::displayMessage(
            adminAccount.getLastModifyDate().getDateText(),
            Lengths::Person::LAST_MODIFY_DATE
        );

        cout << endl;

        Utils::displayLine(
            Texts::Person::Admin::LINE_CHARACTER,
            Lengths::Person::Admin::LINE_LENGTH
        );
    }

    static void printHeader() {
        Utils::displayLine(
            Texts::Person::Admin::LINE_CHARACTER,
            Lengths::Person::Admin::LINE_LENGTH
        );

        cout << '|';

        Utils::displayMessage(
            Texts::Person::Admin::USERNAME,
            Lengths::Person::Admin::USERNAME
        );

        Utils::displayMessage(
            Texts::Person::Admin::PASSWORD,
            Lengths::Person::Admin::PASSWORD
        );

        Utils::displayMessage(
            Texts::Person::FULL_NAME,
            Lengths::Person::FULL_NAME
        );

        Utils::displayMessage(
            Texts::Person::MOBILE_NUMBER,
            Lengths::Person::MOBILE_NUMBER
        );

        Utils::displayMessage(
            Texts::Person::EMAIL,
            Lengths::Person::EMAIL
        );

        Utils::displayMessage(
            Texts::Person::Admin::Permissions::CREATE,
            Lengths::Person::Admin::Permissions::CREATE
        );
        Utils::displayMessage(
            Texts::Person::Admin::Permissions::MODIFY,
            Lengths::Person::Admin::Permissions::MODIFY
        );
        Utils::displayMessage(
            Texts::Person::Admin::Permissions::DELETE,
            Lengths::Person::Admin::Permissions::DELETE
        );
        Utils::displayMessage(
            Texts::Person::Admin::Permissions::SEARCH,
            Lengths::Person::Admin::Permissions::SEARCH
        );
        Utils::displayMessage(
            Texts::Person::Admin::Permissions::SHOW_LIST,
            Lengths::Person::Admin::Permissions::SHOW_LIST
        );
        Utils::displayMessage(
            Texts::Person::Admin::Permissions::TRANSACTION,
            Lengths::Person::Admin::Permissions::TRANSACTION
        );

        Utils::displayMessage(
            Texts::Person::JOIN_DATE,
            Lengths::Person::JOIN_DATE
        );

        Utils::displayMessage(
            Texts::Person::LAST_MODIFY_DATE,
            Lengths::Person::LAST_MODIFY_DATE
        );

        cout << endl;

        Utils::displayLine(
            Texts::Person::Admin::LINE_CHARACTER,
            Lengths::Person::Admin::LINE_LENGTH
        );
    }

    static string convertPermissionsToText(
        const vector<AdminPermission> &PERMISSIONS
    ) {
        string permissionsText;
        for (size_t index = 0; index < PERMISSIONS.size(); ++index) {
            permissionsText += to_string(
                static_cast<short>(PERMISSIONS[index])
            );
            if (index != PERMISSIONS.size() - 1)
                permissionsText += Delimiters::PERMISSIONS;
        }
        return permissionsText;
    }

    static string convertRecordToText(
        AdminAccount &account
    ) {
        return account.getUsername() + Delimiters::ACCOUNT_FIELDS +
            account.getPassword() + Delimiters::ACCOUNT_FIELDS +
            account.getFirstName() + Delimiters::ACCOUNT_FIELDS +
            account.getSecondName() + Delimiters::ACCOUNT_FIELDS +
            account.getCountryCode() + Delimiters::ACCOUNT_FIELDS +
            account.getContactNumber() + Delimiters::ACCOUNT_FIELDS +
            account.getEmail() + Delimiters::ACCOUNT_FIELDS +
            convertPermissionsToText(
                account.permissions
            ) + Delimiters::ACCOUNT_FIELDS +
            account.getJoinDate().getDateText() + Delimiters::ACCOUNT_FIELDS +
            account.getLastModifyDate().getDateText();
    }

    static void saveAccountOnFile(
        AdminAccount &account
    ) {
        const string RECORD_TEXT = convertRecordToText(
            account
        );

        fstream file {
            FilePaths::ADMIN_ACCOUNTS_FILE_PATH,
            ios::out | ios::app
        };

        if (file.is_open())
            file << RECORD_TEXT << endl;

        file.close();
    }

    AdminAccount(): PersonAccount(
        {},
        {},
        {},
        {},
        {}
    ) {}

public:
    AdminAccount(
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

    AdminAccount(
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

    AdminAccount(
        const string &USERNAME,
        const string &PASSWORD,
        const FullName &FULL_NAME,
        const MobileNumber &MOBILE_NUMBER,
        const string &EMAIL,
        const vector<AdminPermission> &PERMISSIONS,
        const Date &JOIN_DATE,
        const Date &LAST_MODIFY_DATE
    ) : PersonAccount(
        FULL_NAME,
        MOBILE_NUMBER,
        EMAIL,
        JOIN_DATE,
        LAST_MODIFY_DATE
    ) {
        username = USERNAME;
        password = PASSWORD;
        permissions = PERMISSIONS;
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

    void setPermissions(
        const vector<AdminPermission> &PERMISSIONS
    ) {
        permissions = PERMISSIONS;
    }

    vector<AdminPermission> getPermissions() {
        return permissions;
    }

    static void readPermissions(
        vector<AdminPermission> &permissions
    ) {
        bool status;

        if (
            Input::readPermission(
                status,
                "Can Create?"
            )
        )
            permissions.push_back(
                Create
            );

        if (
            Input::readPermission(
                status,
                "Can Modify?"
            )
        )
            permissions.push_back(
                Modify
            );

        if (
            Input::readPermission(
                status,
                "Can Delete?"
            )
        )
            permissions.push_back(
                Delete
            );

        if (
            Input::readPermission(
                status,
                "Can Find?"
            )
        )
            permissions.push_back(
                Find
            );

        if (
            Input::readPermission(
                status,
                "Can Show List?"
            )
        )
            permissions.push_back(
                ShowList
            );

        if (
            Input::readPermission(
                status,
                "Can Transaction?"
            )
        )
            permissions.push_back(
                Transaction
            );
    }

    static void createAccount() {
        AdminAccount currentAccount;

        string username;
        do {
            Input::readUsername(
                username
            );
            currentAccount.setUsername(
                username
            );
        } while (
            isValidAccountByUsername(
                currentAccount,
                findByUsernameInFile(
                    currentAccount
                ),
                false
            )
        );

        string password;
        Input::readPassword(
            password
        );
        currentAccount.setPassword(
            password
        );

        FullName fullName;
        Input::readFullName(
            fullName
        );
        currentAccount.setFullName(
            fullName
        );

        MobileNumber mobileNumber;
        Input::readMobileNumber(
            mobileNumber
        );
        currentAccount.setMobileNumber(
            mobileNumber
        );

        string email;
        Input::readEmail(
            email
        );
        currentAccount.setEmail(
            email
        );

        vector<AdminPermission> permissions;
        readPermissions(
            permissions
        );
        currentAccount.setPermissions(
            permissions
        );

        currentAccount.setJoinDate(
            {}
        );

        currentAccount.setLastModifyDate(
            {}
        );

        saveAccountOnFile(
            currentAccount
        );

        Utils::displayMessage(
            "A new administrator has been added."
        );
    }

    static vector<AdminAccount> readAccountsFileToRecords() {
        vector<AdminAccount> accounts;

        fstream file {
            FilePaths::ADMIN_ACCOUNTS_FILE_PATH,
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
                AdminAccount account;
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

    static void showList() {
        printHeader();

        fstream file {
            FilePaths::ADMIN_ACCOUNTS_FILE_PATH,
            ios::in
        };

        if (file.is_open()) {
            string line;
            size_t counter = 0;
            while (
                getline(
                    file,
                    line
                )
            ) {
                counter++;

                AdminAccount account;
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

                printBody(
                    account
                );
            }

            Utils::displayNote(
                Texts::Person::Admin::LIST_COUNTER_MESSAGE + to_string(
                    counter
                )
            );
        }

        file.close();
    }

    static AdminAccount findByUsernameInFile(
        AdminAccount &targetAdminAccount
    ) {
        for (AdminAccount &currentAdminAccount : readAccountsFileToRecords())
            if (targetAdminAccount.getUsername() == currentAdminAccount.getUsername())
                return currentAdminAccount;
        return {};
    }

    static AdminAccount findByUsernameAndPasswordInFile(
        AdminAccount &targetAdminAccount
    ) {
        for (AdminAccount &currentAdminAccount : readAccountsFileToRecords())
            if (targetAdminAccount.getUsername() == currentAdminAccount.getUsername()) {
                if (targetAdminAccount.getPassword() == currentAdminAccount.getPassword())
                    return currentAdminAccount;
                return targetAdminAccount.getUsername();
            }
        return {};
    }

    static void printAccountTable(
        AdminAccount &adminAccount
    ) {
        printHeader();
        printBody(
            adminAccount
        );
    }

    static bool isValidAccountByUsername(
        AdminAccount &currentAccount,
        AdminAccount targetAccount,
        const bool PRINT_TABLE = true
    ) {
        if (currentAccount.getUsername() == targetAccount.getUsername()) {
            if (PRINT_TABLE)
                printAccountTable(
                    targetAccount
                );
            return true;
        }
        if (PRINT_TABLE)
            Utils::displayMessage(
                "Isn't Found!"
            );
        return false;
    }

    static bool isValidAccountByUsernameAndPassword(
        AdminAccount &currentAccount,
        AdminAccount targetAccount
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