#pragma once

#include <fstream>

#include "Balance.h"
#include "../PersonAccount.h"
#include "../../../constants/Delimiters.h"
#include "../../../constants/FilePaths.h"
#include "../../../constants/Lengths.h"
#include "../../../libraries/String.h"
#include "../../../libraries/Utils.h"
#include "../../../libraries/Input.h"
#include "../../../libraries/datetime/Date.h"

using namespace std;

class ClientAccount : public PersonAccount {
public:
    enum ModifyMenuChoice {
        PIN_Code = 0,
        FirstName = 1,
        SecondName = 2,
        CountryCode = 3,
        ContactNumber = 4,
        Email = 5,
        Balances = 6,
        BackToManageClientsMenuFromModifyMenu = 7
    };

    enum ManageBalancesMenuChoice {
        CreateBalance = 0,
        ModifyBalance = 1,
        DeleteBalance = 2,
        BackToModifyMenyChoice = 3,
    };

    enum TransactionMenuChoice {
        Deposit = 0,
        Withdraw = 1,
        Transfer = 2,
        Conversion = 3,
        BackToManageClientsMenuFromTransactionMenu = 4
    };

private:
    string id;
    string pinCode;
    vector<Balance> balances;

    static void readBalanceFields(
        vector<Balance> &balances,
        const vector<string> &BALANCES_FIELDS
    ) {
        for (const string &BALANCE_FIELDS : BALANCES_FIELDS) {
            vector<string> balanceFields;
            String::splitText(
                BALANCE_FIELDS,
                balanceFields,
                Delimiters::BALANCE_FIELDS
            );

            balances.push_back(
                {
                    stold(
                        balanceFields[0]
                    ),
                    balanceFields[1]
                }
            );
        }
    }

    static vector<Balance> readBalancesFields(
        const string &BALANCES_TEXT
    ) {
        vector<Balance> balances;

        vector<string> balancesFields;
        String::splitText(
            BALANCES_TEXT,
            balancesFields,
            Delimiters::BALANCES_FIELDS
        );

        readBalanceFields(
            balances,
            balancesFields
        );
        return balances;
    }

    static void readAccountFields(
        ClientAccount &clientAccount,
        const vector<string> &FIELDS
    ) {
        if (FIELDS.size() == Lengths::Person::Client::COUNT_OF_FIELDS) {
            clientAccount.setID(
                FIELDS[0]
            );

            clientAccount.setPIN_Code(
                FIELDS[1]
            );
            clientAccount.setFullName(
                {
                    FIELDS[2],
                    FIELDS[3]
                }
            );
            clientAccount.setMobileNumber(
                {
                    FIELDS[4],
                    FIELDS[5]
                }
            );
            clientAccount.setEmail(
                FIELDS[6]
            );
            clientAccount.setBalances(
                readBalancesFields(
                    FIELDS[7]
                )
            );
            clientAccount.setJoinDate(
                {
                    FIELDS[8]
                }
            );
            clientAccount.setLastModifyDate(
                {
                    FIELDS[9]
                }
            );
        }
    }

    static string convertBalancesToText(
        const vector<Balance> &BALANCES
    ) {
        string balancesText;
        for (size_t index = 0; index < BALANCES.size(); ++index) {
            Balance balance = BALANCES[index];
            balancesText += to_string(
                balance.getCount()
            ) + Delimiters::BALANCE_FIELDS + balance.getCode();
            if (index != BALANCES.size() - 1)
                balancesText += Delimiters::BALANCES_FIELDS;
        }
        return balancesText;
    }

    static string convertRecordToText(
        ClientAccount &account
    ) {
        return account.getID() + Delimiters::ACCOUNT_FIELDS +
            account.getPIN_Code() + Delimiters::ACCOUNT_FIELDS +
            account.getFirstName() + Delimiters::ACCOUNT_FIELDS +
            account.getSecondName() + Delimiters::ACCOUNT_FIELDS +
            account.getCountryCode() + Delimiters::ACCOUNT_FIELDS +
            account.getContactNumber() + Delimiters::ACCOUNT_FIELDS +
            account.getEmail() + Delimiters::ACCOUNT_FIELDS +
            convertBalancesToText(
                account.balances
            ) + Delimiters::ACCOUNT_FIELDS +
            account.getJoinDate().getDateText() + Delimiters::ACCOUNT_FIELDS +
            account.getLastModifyDate().getDateText();
    }

    static void saveAccountOnFile(
        ClientAccount account
    ) {
        const string RECORD_TEXT = convertRecordToText(
            account
        );

        fstream file {
            FilePaths::CLIENT_ACCOUNTS_FILE_PATH,
            ios::out | ios::app
        };

        if (file.is_open())
            file << RECORD_TEXT << endl;
    }

    ClientAccount(): PersonAccount(
        {},
        {},
        {},
        {},
        {}
    ) {}

public:
    ClientAccount(
        const string &ID
    ): PersonAccount(
        {},
        {},
        {},
        {},
        {}
    ) {
        id = ID;
    }

    ClientAccount(
        const string &ID,
        const string &PIN_CODE
    ): PersonAccount(
        {},
        {},
        {},
        {},
        {}
    ) {
        id = ID;
        pinCode = PIN_CODE;
    }

    ClientAccount(
        const string &ID,
        const string &PIN_CODE,
        const FullName &FULL_NAME,
        const MobileNumber &MOBILE_NUMBER,
        const string &EMAIL,
        const vector<Balance> &BALANCES,
        const Date &JOIN_DATE,
        const Date &LAST_MODIFY_DATE
    ): PersonAccount(
        FULL_NAME,
        MOBILE_NUMBER,
        EMAIL,
        JOIN_DATE,
        LAST_MODIFY_DATE
    ) {
        id = ID;
        pinCode = PIN_CODE;
        balances = BALANCES;
    }

    void setAccount(
        ClientAccount &clientAccount
    ) {
        id = clientAccount.id;
        pinCode = clientAccount.pinCode;
        setFullName(
            clientAccount.getFullName()
        );
        setMobileNumber(
            clientAccount.getMobileNumber()
        );
        setEmail(
            clientAccount.getEmail()
        );
        balances = clientAccount.balances;
        setJoinDate(
            clientAccount.getJoinDate()
        );
        setLastModifyDate(
            clientAccount.getLastModifyDate()
        );
    }

    void setID() {
        id = Utils::generateKey();
    }

    void setID(
        const string &ID
    ) {
        id = ID;
    }

    string getID() {
        return id;
    }

    void setPIN_Code(
        const string &PIN_CODE
    ) {
        pinCode = PIN_CODE;
    }

    string getPIN_Code() {
        return pinCode;
    }

    void setBalances(
        const vector<Balance> &BALANCES
    ) {
        balances = BALANCES;
    }

    vector<Balance> getBalances() {
        return balances;
    }

    static void displayTotalBalances() {
        vector<Balance> totalBalances;
        for (ClientAccount &clientAccount : readAccountsFileToRecords()) {
            for (Balance &clientBalance : clientAccount.getBalances()) {
                bool found = false;
                for (Balance &targetBalance : totalBalances) {
                    if (clientBalance.getCode() == targetBalance.getCode()) {
                        found = true;
                        targetBalance.setCount(
                            targetBalance.getCount() +
                            clientBalance.getCount()
                        );
                        break;
                    }
                }
                if (!found)
                    totalBalances.push_back(
                        clientBalance
                    );
            }
        }

        for (Balance &totalBalance : totalBalances)
            cout << totalBalance.getCount() << ' ' << totalBalance.getCode() << endl;
    }

    static void deleteAccount(
        ClientAccount &targetAccount
    ) {
        const vector<ClientAccount> ACCOUNTS = readAccountsFileToRecords();

        fstream file(
            FilePaths::CLIENT_ACCOUNTS_FILE_PATH,
            ios::out | ios::trunc
        );

        if (file.is_open())
            for (ClientAccount account : ACCOUNTS)
                if (account.getID() != targetAccount.getID())
                    saveAccountOnFile(
                        account
                    );

        Utils::displayMessage(
            "The client account has been deleted."
        );

        file.close();
    }

    static void modifyAccount(
        const ClientAccount &TARGET_ACCOUNT,
        const bool &PRINT_COMPLETION_STATUS
    ) {
        const vector<ClientAccount> ACCOUNTS = readAccountsFileToRecords();

        fstream file {
            FilePaths::CLIENT_ACCOUNTS_FILE_PATH,
            ios::out | ios::trunc
        };

        if (file.is_open())
            for (const ClientAccount &CURRENT_ACCOUNT : ACCOUNTS)
                if (TARGET_ACCOUNT.id != CURRENT_ACCOUNT.id)
                    saveAccountOnFile(
                        CURRENT_ACCOUNT
                    );
                else
                    saveAccountOnFile(
                        TARGET_ACCOUNT
                    );

        if (PRINT_COMPLETION_STATUS)
            Utils::displayMessage(
                "The client account has been modified."
            );

        file.close();
    }

    static void printAccountInformation(
        ClientAccount &account
    ) {
        Utils::displayLine(
            Texts::Person::Client::LINE_CHARACTER,
            Lengths::Person::Client::LINE_LENGTH
        );
        Utils::displayMenu(
            "ID: " + account.getID(),
            {},
            nullptr
        );
        cout << "PIN Code: " << account.getPIN_Code() << endl;
        cout << "Full Name: " << account.getFullNameText() << endl;
        cout << "Mobile Number: " << account.getMobileNumberText() << endl;
        cout << "Email: " << account.getEmail() << endl;
        cout << "Balance:" << endl;
        for (Balance &balance : account.getBalances())
            cout << balance.getCount() << ' ' << balance.getCode() << endl;
        cout << "Join Date: " << account.getJoinDate().getDateText() << endl;
        cout << "Lasy Modify Date: " << account.getLastModifyDate().getDateText() << endl;
    }

    static bool isValidAccountByID(
        ClientAccount currentAccount,
        ClientAccount targetAccount,
        const bool &PRINT_INFORMATION,
        const bool &PRINT_NOT_FOUND_MESSAGE
    ) {
        if (currentAccount.getID() == targetAccount.getID()) {
            if (PRINT_INFORMATION) {
                printAccountInformation(
                    targetAccount
                );
                Utils::displayLine(
                    Texts::Person::Client::LINE_CHARACTER,
                    Lengths::Person::Client::LINE_LENGTH
                );
            }
            return true;
        }
        if (PRINT_NOT_FOUND_MESSAGE)
            Utils::displayMessage(
                "Isn't Found."
            );
        return false;
    }

    static ClientAccount findByID_InFile(
        ClientAccount &targetClientAccount
    ) {
        for (ClientAccount &currentClientAccount : readAccountsFileToRecords()) {
            if (currentClientAccount.getID() == targetClientAccount.getID())
                return currentClientAccount;
        }
        return {};
    }

    static void readBalance(
        Balance &balance
    ) {
        long double count;
        Input::readCount(
            count
        );

        string code;
        Input::readCode(
            code
        );

        balance = {
            count,
            code
        };
    }

    static void readBalances(
        vector<Balance> &balances
    ) {
        bool status = true;
        do {
            Balance balance;
            readBalance(
                balance
            );

            if (Input::confirm())
                balances.push_back(
                    balance
                );

            Input::readBoolean(
                status,
                "Do you want read more balances?"
            );
        } while (status);
    }

    static void createAccount() {
        ClientAccount currentAccount;

        currentAccount.setID();

        string pinCode;
        Input::readPIN_Code(
            pinCode
        );
        currentAccount.setPIN_Code(
            pinCode
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

        vector<Balance> balances;
        readBalances(
            balances
        );
        currentAccount.setBalances(
            balances
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
            "The client account has been created."
        );
    }

    static vector<ClientAccount> readAccountsFileToRecords() {
        vector<ClientAccount> accounts;

        fstream file {
            FilePaths::CLIENT_ACCOUNTS_FILE_PATH,
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
                ClientAccount account;
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
        fstream file {
            FilePaths::CLIENT_ACCOUNTS_FILE_PATH,
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

                ClientAccount account;
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

                printAccountInformation(
                    account
                );
            }

            if (counter)
                Utils::displayLine(
                    Texts::Person::Client::LINE_CHARACTER,
                    Lengths::Person::Client::LINE_LENGTH
                );

            Utils::displayNote(
                Texts::Person::Client::LIST_COUNTER_MESSAGE + to_string(
                    counter
                )
            );
        }

        file.close();
    }
};