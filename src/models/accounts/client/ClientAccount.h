#pragma once

#include <fstream>

#include "Balance.h"
#include "../PersonAccount.h"
#include "../../../constants/Delimiters.h"
#include "../../../constants/FilePaths.h"
#include "../../../libraries/String.h"
#include "../../../libraries/Utils.h"
#include "../../../libraries/date/Date.h"

using namespace std;

class ClientAccount : protected PersonAccount {
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
                    balanceFields[0],
                    balanceFields[1],
                    stold(
                        balanceFields[2]
                    ),
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
        if (FIELDS.size() == 9) {
            clientAccount.setPIN_Code(
                FIELDS[0]
            );
            clientAccount.setFullName(
                {
                    FIELDS[1],
                    FIELDS[2]
                }
            );
            clientAccount.setMobileNumber(
                {
                    FIELDS[3],
                    FIELDS[4]
                }
            );
            clientAccount.setEmail(
                FIELDS[5]
            );
            clientAccount.setBalances(
                readBalancesFields(
                    FIELDS[6]
                )
            );
            clientAccount.setJoinDate(
                {
                    FIELDS[7]
                }
            );
            clientAccount.setLastModifyDate(
                {
                    FIELDS[8]
                }
            );
        }
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
        id = Utils::generateKey();
        pinCode = PIN_CODE;
        balances = BALANCES;
    }

    string getID() {
        return id;
    }

    void setPIN_Code(
        const string &PIN_CODE
    ) {
        pinCode = PIN_CODE;
    }

    void setBalances(
        const vector<Balance> &BALANCES
    ) {
        balances = BALANCES;
    }

    vector<Balance> getBalances() {
        return balances;
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
};