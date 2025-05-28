#pragma once
#include "Limits.h"

using namespace std;

namespace Lengths {
    namespace Login {
        constexpr short COUNT_OF_MENU_LINES = 2;
    }

    namespace Person {
        constexpr short FIRST_NAME = 20;
        constexpr short SECOND_NAME = 20;
        constexpr short FULL_NAME = FIRST_NAME + 1 + SECOND_NAME;
        constexpr short COUNTRY_CODE = 6;
        constexpr short CONTACT_NUMBER = 14;
        constexpr short MOBILE_NUMBER = COUNTRY_CODE + CONTACT_NUMBER;
        constexpr short EMAIL = 30;
        constexpr short JOIN_DATE = 9;
        constexpr short LAST_MODIFY_DATE = 16;

        constexpr short DATE_TIME = 19;

        namespace Owner {
            constexpr short COUNT_OF_MENU_LINES = 8;

            constexpr short USERNAME = Limits::Username::MAXIMUM;
            constexpr short PASSWORD = Limits::Password::MAXIMUM;

            constexpr short COUNT_OF_FIELDS = 9;

            constexpr short COUNT_OF_MODIFY_MENU = 9;

            constexpr short COUNT_OF_MODIFY_PERMISSIONS_MENU = 8;
        }

        namespace Admin {
            constexpr short COUNT_OF_MENU_LINES = 8;

            constexpr short ACCOUNT_LINE_LENGTH = 232;
            constexpr short LOGIN_LOG_LINE_LENGTH = 63;

            constexpr short USERNAME = Limits::Username::MAXIMUM;
            constexpr short PASSWORD = Limits::Password::MAXIMUM;

            constexpr short COUNT_OF_PERMISSIONS = 7;

            namespace Permissions {
                constexpr short CREATE = 6;
                constexpr short MODIFY = 6;
                constexpr short DELETE = 6;
                constexpr short SEARCH = 6;
                constexpr short SHOW_LIST = 9;
                constexpr short TRANSACTION = 11;
                constexpr short SHOW_TRANSFER_LOG = 17;
            }

            constexpr short COUNT_OF_FIELDS = 10;

            constexpr short COUNT_OF_MODIFY_MENU = 8;

            constexpr short COUNT_OF_MANAGE_BALANCES_MENU = 4;

            constexpr short COUNT_OF_TRANSACTION_MENU = 5;
        }

        namespace Client {
            constexpr short LINE_LENGTH = 40;
            constexpr short ID = 19;
            constexpr short PIN_CODE = 4;
            constexpr short BALANCE_COUNT = 20;
            constexpr short BALANCE_CODE = 3;
            constexpr short BALANCE = 24;
            constexpr short COUNT_OF_FIELDS = 10;
            constexpr short TRANSFER_LOG_LINE_LENGTH = 86;
        }
    }
}