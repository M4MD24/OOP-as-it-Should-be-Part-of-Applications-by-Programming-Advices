#pragma once
#include "Limits.h"

using namespace std;

namespace Lengths {
    namespace Login {
        constexpr short COUNT_OF_LINES = 2;
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

        namespace Owner {
            constexpr short COUNT_OF_LINES = 8;

            constexpr short USERNAME = Limits::Username::MAXIMUM;
            constexpr short PASSWORD = Limits::Password::MAXIMUM;
        }

        namespace Admin {
            constexpr short COUNT_OF_LINES = 7;

            constexpr short LINE_LENGTH = 214;

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
            }
        }

        namespace Client {}
    }
}