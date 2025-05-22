#pragma once

#include <string>

using namespace std;

namespace Texts {
    namespace Login {
        const string LOGIN_CHOICES_MENU_TITLE = "Login Choices Menu";
        const string LOGIN_MENU_TITLE = "Login Menu";

        const string LINES[] = {
            "Owner",
            "Admin"
        };
    }

    namespace Person {
        const string FIRST_NAME = "First Name";
        const string SECOND_NAME = "Second Name";
        const string FULL_NAME = "Full Name";
        const string COUNTRY_CODE = "Country Code";
        const string CONTACT_NUMBER = "Contact Number";
        const string MOBILE_NUMBER = "Mobile Number";
        const string EMAIL = "Email";
        const string JOIN_DATE = "Join Date";
        const string LAST_MODIFY_DATE = "Last Modify Date";

        namespace Owner {
            const string MENU_TITLE = "Manage Admins Menu";

            const string LINES[] = {
                "Create New Admin",
                "Modify Admin",
                "Delete Admin",
                "Find Admin",
                "Admin List",
                "Total Balances",
                "Admin Event Log",
                "Logout"
            };

            const string USERNAME = "Username";
            const string PASSWORD = "Password";
        }

        namespace Admin {
            const string MENU_TITLE = "Manage Clients Menu";

            const string LINES[] = {
                "Create New Client",
                "Modify Client",
                "Delete Client",
                "Find Client",
                "Client List",
                "Transaction",
                "Logout"
            };

            constexpr char LINE_CHARACTER = '-';

            const string USERNAME = Owner::USERNAME;
            const string PASSWORD = Owner::PASSWORD;

            namespace Permissions {
                const string CREATE = "Create";
                const string MODIFY = "Modify";
                const string DELETE = "Delete";
                const string SEARCH = "Search";
                const string SHOW_LIST = "Show List";
                const string TRANSACTION = "Transaction";
            }

            const string LIST_COUNTER_MESSAGE = "Admin Count = ";
        }

        namespace Client {}
    }
}