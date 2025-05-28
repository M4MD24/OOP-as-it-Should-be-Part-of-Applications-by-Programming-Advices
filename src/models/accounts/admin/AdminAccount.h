#pragma once

#include <fstream>

#include "../PersonAccount.h"
#include "../../../constants/Delimiters.h"
#include "../../../constants/FilePaths.h"
#include "../../../constants/Lengths.h"
#include "../../../constants/Texts.h"
#include "../../../libraries/Input.h"
#include "../../../libraries/datetime/Date.h"
#include "../../../libraries/datetime/Time.h"
#include "../../../libraries/String.h"
#include "../../../libraries/Utils.h"

using namespace std;

class AdminAccount : public PersonAccount {
public:
    enum AdminPermission {
        Create = 0,
        Modify = 1,
        Delete = 2,
        Search = 3,
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
        ClientTransferLog = 6,
        Logout = 7
    };

    enum ModifyMenuChoice {
        Username = 0,
        Password = 1,
        FirstName = 2,
        SecondName = 3,
        CountryCode = 4,
        ContactNumber = 5,
        Email = 6,
        Permissions = 7,
        BackToManageAdminsMenu = 8
    };

    enum ModifyPermissionsMenuChoice {
        CreatePermission = 0,
        ModifyPermission = 1,
        DeletePermission = 2,
        SearchPermission = 3,
        ShowListPermission = 4,
        TransactionPermission = 5,
        BackToModifyAdminsMenu = 6
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
        if (FIELDS.size() == Lengths::Person::Admin::COUNT_OF_FIELDS) {
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

    static void printAccountBody(
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
            Lengths::Person::Admin::ACCOUNT_LINE_LENGTH
        );
    }

    static void printAccountHeader() {
        Utils::displayLine(
            Texts::Person::Admin::LINE_CHARACTER,
            Lengths::Person::Admin::ACCOUNT_LINE_LENGTH
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
            Lengths::Person::Admin::ACCOUNT_LINE_LENGTH
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
        AdminAccount account
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
    }

    static string convertRecordToSessionText(
        AdminAccount &account
    ) {
        return account.getUsername() + Delimiters::ACCOUNT_FIELDS +
            account.getPassword() + Delimiters::ACCOUNT_FIELDS +
            (Date().getDateText() + ' ' + Time().getTimeText());
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

    void setAccount(
        AdminAccount &adminAccount
    ) {
        username = adminAccount.username;
        password = adminAccount.password;
        setFullName(
            adminAccount.getFullName()
        );
        setMobileNumber(
            adminAccount.getMobileNumber()
        );
        setEmail(
            adminAccount.getEmail()
        );
        permissions = adminAccount.permissions;
        setJoinDate(
            adminAccount.getJoinDate()
        );
        setLastModifyDate(
            adminAccount.getLastModifyDate()
        );
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

    static void createSession(
        AdminAccount &account
    ) {
        const string SESSION_TEXT = convertRecordToSessionText(
            account
        );

        fstream file {
            FilePaths::ADMIN_LOGIN_LOG_FILE_PATH,
            ios::out | ios::app
        };

        if (file.is_open())
            file << SESSION_TEXT << endl;
    }

    static void printLoginLogHeader() {
        Utils::displayLine(
            Texts::Person::Admin::LINE_CHARACTER,
            Lengths::Person::Admin::LOGIN_LOG_LINE_LENGTH
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
            Texts::Person::DATE_TIME,
            Lengths::Person::DATE_TIME
        );

        cout << endl;

        Utils::displayLine(
            Texts::Person::Admin::LINE_CHARACTER,
            Lengths::Person::Admin::LOGIN_LOG_LINE_LENGTH
        );
    }

    static void printLoginLogBody(
        const vector<string> &FIELDS
    ) {
        cout << '|';

        Utils::displayMessage(
            FIELDS[0],
            Lengths::Person::Admin::USERNAME
        );

        Utils::displayMessage(
            FIELDS[1],
            Lengths::Person::Admin::PASSWORD
        );

        Utils::displayMessage(
            FIELDS[2],
            Lengths::Person::DATE_TIME
        );

        cout << endl;

        Utils::displayLine(
            Texts::Person::Admin::LINE_CHARACTER,
            Lengths::Person::Admin::LOGIN_LOG_LINE_LENGTH
        );
    }

    static void showLoginLog() {
        printLoginLogHeader();
        fstream file {
            FilePaths::ADMIN_LOGIN_LOG_FILE_PATH,
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

                vector<string> fields;

                String::splitText(
                    line,
                    fields,
                    Delimiters::ACCOUNT_FIELDS
                );

                if (fields.size() == 3)
                    printLoginLogBody(
                        fields
                    );
            }

            Utils::displayNote(
                Texts::Person::Admin::LOGIN_LOG_COUNTER_MESSAGE + to_string(
                    counter
                )
            );
        }

        file.close();
    }

    static void deleteAccount(
        AdminAccount &targetAccount
    ) {
        const vector<AdminAccount> ACCOUNTS = readAccountsFileToRecords();

        fstream file(
            FilePaths::ADMIN_ACCOUNTS_FILE_PATH,
            ios::out | ios::trunc
        );

        if (file.is_open())
            for (AdminAccount account : ACCOUNTS)
                if (account.getUsername() != targetAccount.getUsername())
                    saveAccountOnFile(
                        account
                    );

        Utils::displayMessage(
            "The admin account has been deleted."
        );

        file.close();
    }

    static void modifyAccount(
        const AdminAccount &TARGET_ACCOUNT
    ) {
        const vector<AdminAccount> ACCOUNTS = readAccountsFileToRecords();

        fstream file {
            FilePaths::ADMIN_ACCOUNTS_FILE_PATH,
            ios::out | ios::trunc
        };

        if (file.is_open())
            for (const AdminAccount &CURRENT_ACCOUNT : ACCOUNTS)
                if (TARGET_ACCOUNT.username != CURRENT_ACCOUNT.username)
                    saveAccountOnFile(
                        CURRENT_ACCOUNT
                    );
                else
                    saveAccountOnFile(
                        TARGET_ACCOUNT
                    );

        Utils::displayMessage(
            "The admin account has been modified."
        );

        file.close();
    }

    static void readPermission(
        vector<AdminPermission> &permissions,
        const AdminPermission &PERMISSION,
        const string &MESSAGE,
        bool &status
    ) {
        if (
            Input::readPermission(
                status,
                MESSAGE
            )
        )
            permissions.push_back(
                PERMISSION
            );
    }

    static void readCreatePermission(
        vector<AdminPermission> &permissions,
        bool &status
    ) {
        readPermission(
            permissions,
            Create,
            Texts::Person::Admin::Permissions::Text::CREATE,
            status
        );
    }

    static void readModifyPermission(
        vector<AdminPermission> &permissions,
        bool &status
    ) {
        readPermission(
            permissions,
            Modify,
            Texts::Person::Admin::Permissions::Text::MODIFY,
            status
        );
    }

    static void readDeletePermission(
        vector<AdminPermission> &permissions,
        bool &status
    ) {
        readPermission(
            permissions,
            Delete,
            Texts::Person::Admin::Permissions::Text::DELETE,
            status
        );
    }

    static void readSearchPermission(
        vector<AdminPermission> &permissions,
        bool &status
    ) {
        readPermission(
            permissions,
            Search,
            Texts::Person::Admin::Permissions::Text::SEARCH,
            status
        );
    }

    static void readShowListPermission(
        vector<AdminPermission> &permissions,
        bool &status
    ) {
        readPermission(
            permissions,
            ShowList,
            Texts::Person::Admin::Permissions::Text::SHOW_LIST,
            status
        );
    }

    static void readTransactionPermission(
        vector<AdminPermission> &permissions,
        bool &status
    ) {
        readPermission(
            permissions,
            Transaction,
            Texts::Person::Admin::Permissions::Text::TRANSACTION,
            status
        );
    }

    static void readPermissions(
        vector<AdminPermission> &permissions
    ) {
        bool status;

        readCreatePermission(
            permissions,
            status
        );

        readModifyPermission(
            permissions,
            status
        );

        readDeletePermission(
            permissions,
            status
        );

        readSearchPermission(
            permissions,
            status
        );

        readShowListPermission(
            permissions,
            status
        );

        readTransactionPermission(
            permissions,
            status
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
                false,
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
            "The admin account has been created."
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
        printAccountHeader();

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

                printAccountBody(
                    account
                );
            }

            Utils::displayNote(
                Texts::Person::Admin::ACCOUNT_COUNTER_MESSAGE + to_string(
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
        printAccountHeader();
        printAccountBody(
            adminAccount
        );
    }

    static bool isValidAccountByUsername(
        AdminAccount currentAccount,
        AdminAccount targetAccount,
        const bool PRINT_TABLE,
        const bool PRINT_NOT_FOUND_MESSAGE
    ) {
        if (currentAccount.getUsername() == targetAccount.getUsername()) {
            if (PRINT_TABLE)
                printAccountTable(
                    targetAccount
                );
            return true;
        }
        if (PRINT_NOT_FOUND_MESSAGE)
            Utils::displayMessage(
                "Isn't Found."
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

    static void displayAdminMenu(
        const vector<AdminPermission> &PERMISSIONS
    ) {
        Utils::displayMenu(
            Texts::Person::Admin::MENU_TITLE,
            {},
            nullptr
        );

        for (short index = 0; index < Lengths::Person::Admin::COUNT_OF_MENU_LINES - 1; ++index) {
            bool found = false;
            for (const AdminPermission &CURRENT_PERMISSION : PERMISSIONS)
                if (CURRENT_PERMISSION == static_cast<AdminPermission>(index)) {
                    found = true;
                    break;
                }
            if (!found)
                cout << "\033[31m";
            cout << (index + 1) << " - " << Texts::Person::Admin::LINES[index] << "\033[0m" << endl;
        }

        cout << Lengths::Person::Admin::COUNT_OF_MENU_LINES << " - " << Texts::Person::Admin::LINES[Lengths::Person::Admin::COUNT_OF_MENU_LINES - 1] << endl;
    }
};