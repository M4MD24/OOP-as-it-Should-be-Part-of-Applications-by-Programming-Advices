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

            const string MODIFY_MENU_TITLE = "Modify Admin Menu";

            const string MODIFY_MENU_LINES[] = {
                "Username",
                "Password",
                "First Name",
                "Second Name",
                "Country Code",
                "Contact Number",
                "Email",
                "Permissions",
                "Back to ~{Manage Admins Menu}~"
            };

            const string MODIFY_PERMISSIONS_MENU_TITLE = "Modify Permissions Menu";

            const string MODIFY_PERMISSIONS_MENU_LINES[] = {
                "Create",
                "Modify",
                "Delete",
                "Search",
                "Show List",
                "Transaction",
                "Back to ~{Modify Admin Menu}~"
            };
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

                namespace Text {
                    const string CREATE = "Can " + Permissions::CREATE;
                    const string MODIFY = "Can " + Permissions::MODIFY;
                    const string DELETE = "Can " + Permissions::DELETE;
                    const string SEARCH = "Can " + Permissions::SEARCH;
                    const string SHOW_LIST = "Can " + Permissions::SHOW_LIST;
                    const string TRANSACTION = "Can " + Permissions::TRANSACTION;
                }
            }

            const string LIST_COUNTER_MESSAGE = "Admin Count = ";

            const string MODIFY_MENU_TITLE = "Modify Client Menu";
            const string MODIFY_MENU_LINES[] = {
                "PIN Code",
                "First Name",
                "Second Name",
                "Country Code",
                "Contact Number",
                "Email",
                "Balances",
                "Back to ~{ " + MENU_TITLE + " }~"
            };

            const string MANAGE_BALANCES_MENU_TITLE = "Manage Balances Menu";

            const string MANAGE_BALANCES_MENU_LINES[] = {
                "Create Balance",
                "Modify Balance",
                "Delete Balance",
                "Back to ~{ " + LINES[1] + " }~"
            };

            const string MODIFY_BALANCES_MENU_TITLE = "Modify Balances Menu";

            const string TRANSACTION_MENU_TITLE = "Transaction Menu";

            const string TRANSACTION_MENU[] = {
                "Deposit",
                "Withdraw",
                "Transfer",
                "Conversion",
                "Back to ~{ " + MENU_TITLE + " }~"
            };
        }

        namespace Client {
            const string LIST_COUNTER_MESSAGE = "Client Count = ";
            constexpr char LINE_CHARACTER = '#';
            constexpr char ID_DELIMITER = '-';
        }
    }

    const string CONFIRM_MESSAGE = "Are you sure?";
}