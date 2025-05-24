#include "constants/Texts.h"
#include "libraries/Options.h"
#include "libraries/Input.h"
#include "libraries/Utils.h"
#include "libraries/Validation.h"
#include "models/accounts/admin/AdminAccount.h"
#include "models/accounts/client/ClientAccount.h"
#include "models/accounts/owner/OwnerAccount.h"

void modifyPermissionsMenu(
    vector<AdminAccount::AdminPermission> &permissions
) {
    do {
        Utils::displayMenu(
            Texts::Person::Owner::MODIFY_PERMISSIONS_MENU_TITLE,
            Lengths::Person::Owner::COUNT_OF_MODIFY_PERMISSIONS_MENU,
            Texts::Person::Owner::MODIFY_PERMISSIONS_MENU_LINES
        );

        short choice;
        Input::readChoice(
            choice,
            1,
            Lengths::Person::Owner::COUNT_OF_MODIFY_PERMISSIONS_MENU
        );

        bool status;
        AdminAccount::AdminPermission permission = {};

        switch (static_cast<AdminAccount::ModifyPermissionsMenuChoice>(choice - 1)) {
        case AdminAccount::CreatePermission: {
            permission = AdminAccount::Create;
            Input::readPermission(
                status,
                Texts::Person::Admin::Permissions::Text::CREATE
            );
            break;
        }

        case AdminAccount::ModifyPermission: {
            permission = AdminAccount::Modify;
            Input::readPermission(
                status,
                Texts::Person::Admin::Permissions::Text::MODIFY
            );
            break;
        }
        case AdminAccount::DeletePermission: {
            permission = AdminAccount::Delete;
            Input::readPermission(
                status,
                Texts::Person::Admin::Permissions::Text::DELETE
            );
            break;
        }
        case AdminAccount::SearchPermission: {
            permission = AdminAccount::Search;
            Input::readPermission(
                status,
                Texts::Person::Admin::Permissions::Text::SEARCH
            );
            break;
        }
        case AdminAccount::ShowListPermission: {
            permission = AdminAccount::ShowList;
            Input::readPermission(
                status,
                Texts::Person::Admin::Permissions::Text::SHOW_LIST
            );
            break;
        }
        case AdminAccount::TransactionPermission: {
            permission = AdminAccount::Transaction;
            Input::readPermission(
                status,
                Texts::Person::Admin::Permissions::Text::TRANSACTION
            );
            break;
        }
        case AdminAccount::BackToModifyAdminsMenu: { return; }
        default: { break; }
        }

        bool permissionFound = false;
        short index = 0;
        while (index < permissions.size()) {
            if (permissions[index] == permission) {
                permissionFound = true;
                break;
            }
            index++;
        }

        if (status == 1 && !permissionFound)
            permissions.push_back(
                permission
            );
        else if (status == 0 && permissionFound)
            permissions.erase(
                permissions.begin() + index
            );
    } while (true);
}

void modifyMenu(
    AdminAccount targetAccount
) {
    do {
        AdminAccount::printAccountTable(
            targetAccount
        );

        Utils::displayMenu(
            Texts::Person::Owner::MODIFY_MENU_TITLE,
            Lengths::Person::Owner::COUNT_OF_MODIFY_MENU,
            Texts::Person::Owner::MODIFY_MENU_LINES
        );

        short choice;
        Input::readChoice(
            choice,
            1,
            Lengths::Person::Owner::COUNT_OF_MODIFY_MENU
        );

        switch (static_cast<AdminAccount::ModifyMenuChoice>(choice - 1)) {
        case AdminAccount::Username: {
            string username;
            bool found = false;
            do {
                Input::readUsername(
                    username
                );

                if (username == targetAccount.getUsername())
                    found = false;
                else
                    found = AdminAccount::isValidAccountByUsername(
                        {
                            username
                        },
                        AdminAccount::findByUsernameInFile(
                            targetAccount
                        ),
                        false,
                        false
                    );
            } while (
                found
            );

            targetAccount.setUsername(
                username
            );
            break;
        }

        case AdminAccount::Password: {
            string password;
            Input::readPassword(
                password
            );
            targetAccount.setPassword(
                password
            );
            break;
        }

        case AdminAccount::FirstName: {
            string firstName;
            Input::readFirstName(
                firstName
            );
            targetAccount.setFirstName(
                firstName
            );
            break;
        }

        case AdminAccount::SecondName: {
            string secondName;
            Input::readSecondName(
                secondName
            );
            targetAccount.setSecondName(
                secondName
            );
            break;
        }

        case AdminAccount::CountryCode: {
            string countryCode;
            Input::readCountryCode(
                countryCode
            );
            targetAccount.setCountryCode(
                countryCode
            );
            break;
        }

        case AdminAccount::Email: {
            string email;
            Input::readEmail(
                email
            );
            targetAccount.setEmail(
                email
            );
            break;
        }

        case AdminAccount::Permissions: {
            vector<AdminAccount::AdminPermission> permissions = targetAccount.getPermissions();
            modifyPermissionsMenu(
                permissions
            );
            targetAccount.setPermissions(
                permissions
            );
            break;
        }

        case AdminAccount::BackToManageAdminsMenu: { return; }

        default: { break; }
        }

        if (
            Input::confirm()
        ) {
            targetAccount.setLastModifyDate(
                {}
            );

            AdminAccount::modifyAccount(
                targetAccount
            );
        }
    } while (true);
}

void ownerMenu() {
    short choice;
    do {
        Utils::displayMenu(
            Texts::Person::Owner::MENU_TITLE,
            Lengths::Person::Owner::COUNT_OF_MENU_LINES,
            Texts::Person::Owner::LINES
        );

        Input::readChoice(
            choice,
            1,
            Lengths::Person::Owner::COUNT_OF_MENU_LINES
        );

        Utils::displayMenu(
            Texts::Person::Owner::LINES[choice - 1],
            0,
            {}
        );

        switch (static_cast<OwnerAccount::OwnerMenuChoice>(choice - 1)) {
        case OwnerAccount::OwnerMenuChoice::CreateNewAdmin: {
            AdminAccount::createAccount();
            break;
        }
        case OwnerAccount::OwnerMenuChoice::ModifyAdmin: {
            string username;
            Input::readUsername(
                username
            );

            AdminAccount currentAdminAccount {
                username
            };

            const AdminAccount TARGET_ACCOUNT = AdminAccount::findByUsernameInFile(
                currentAdminAccount
            );

            if (
                AdminAccount::isValidAccountByUsername(
                    currentAdminAccount,
                    TARGET_ACCOUNT,
                    false,
                    true
                )
            )
                modifyMenu(
                    TARGET_ACCOUNT
                );
            break;
        }
        case OwnerAccount::OwnerMenuChoice::DeleteAdmin: {
            string username;
            Input::readUsername(
                username
            );

            AdminAccount currentAdminAccount {
                username
            };

            AdminAccount targetAccount = AdminAccount::findByUsernameInFile(
                currentAdminAccount
            );

            if (
                AdminAccount::isValidAccountByUsername(
                    currentAdminAccount,
                    targetAccount,
                    true,
                    true
                )
            ) {
                if (
                    Input::confirm()
                )
                    AdminAccount::deleteAccount(
                        targetAccount
                    );
            }
            break;
        }
        case OwnerAccount::OwnerMenuChoice::FindAdmin: {
            string username;
            Input::readUsername(
                username
            );

            AdminAccount currentAccount {
                username
            };

            const AdminAccount TARGET_ACCOUNT = AdminAccount::findByUsernameInFile(
                currentAccount
            );

            AdminAccount::isValidAccountByUsername(
                currentAccount,
                TARGET_ACCOUNT,
                true,
                true
            );
            break;
        }
        case OwnerAccount::OwnerMenuChoice::AdminList: {
            AdminAccount::showList();
            break;
        }
        case OwnerAccount::OwnerMenuChoice::TotalBalances: {
            break;
        }
        case OwnerAccount::OwnerMenuChoice::Logout: { return; }
        default: { break; }
        }
    } while (true);
}

void adminMenu() {
    short choice;
    do {
        Utils::displayMenu(
            Texts::Person::Admin::MENU_TITLE,
            Lengths::Person::Admin::COUNT_OF_MENU_LINES,
            Texts::Person::Admin::LINES
        );

        Input::readChoice(
            choice,
            1,
            Lengths::Person::Admin::COUNT_OF_MENU_LINES
        );

        Utils::displayMenu(
            Texts::Person::Admin::LINES[choice - 1],
            0,
            {}
        );

        switch (static_cast<AdminAccount::AdminMenuChoice>(choice - 1)) {
        case AdminAccount::AdminMenuChoice::CreateNewClient: {
            ClientAccount::createAccount();
            break;
        }
        case AdminAccount::AdminMenuChoice::ModifyClient: { return; }
        case AdminAccount::AdminMenuChoice::DeleteClient: { return; }
        case AdminAccount::AdminMenuChoice::FindClient: {
            string id;
            Input::readID(
                id
            );

            ClientAccount currentAccount {
                id
            };

            const ClientAccount TARGET_ACCOUNT = ClientAccount::findByID_InFile(
                currentAccount
            );

            ClientAccount::isValidAccountByID(
                currentAccount,
                TARGET_ACCOUNT,
                true,
                true
            );
            break;
        }
        case AdminAccount::AdminMenuChoice::ClientList: {
            ClientAccount::showList();
            break;
        }
        case AdminAccount::AdminMenuChoice::TransactionClient: { return; }
        case AdminAccount::AdminMenuChoice::ClientEventLog: { return; }
        case AdminAccount::AdminMenuChoice::Logout: { return; }
        default: { break; }
        }
    } while (true);
}

void login(
    const AccountType &ACCOUNT_TYPE
) {
    Utils::displayMenu(
        Texts::Login::LOGIN_MENU_TITLE,
        0,
        {}
    );

    string username,
           password;
    Input::readUsername(
        username
    );
    Input::readPassword(
        password
    );

    switch (ACCOUNT_TYPE) {
    case Owner: {
        OwnerAccount currentOwnerAccount {
            username,
            password
        };
        if (
            OwnerAccount::isValidAccountByUsernameAndPassword(
                currentOwnerAccount,
                OwnerAccount::findByUsernameAndPasswordInFile(
                    currentOwnerAccount
                )
            )
        )
            ownerMenu();
        break;
    }
    case Admin: {
        AdminAccount currentAdminAccount {
            username,
            password
        };
        if (
            AdminAccount::isValidAccountByUsernameAndPassword(
                currentAdminAccount,
                AdminAccount::findByUsernameInFile(
                    currentAdminAccount
                )
            )
        )
            adminMenu();
        break;
    }
    default: { break; }
    }
}

void performAccountTypeLoginMenu() {
    short choice;

    Utils::displayMenu(
        Texts::Login::LOGIN_CHOICES_MENU_TITLE,
        Lengths::Login::COUNT_OF_MENU_LINES,
        Texts::Login::LINES
    );

    Input::readChoice(
        choice
    );

    if (
        Validation::isBetweenNumbers(
            choice,
            static_cast<short>(1),
            Lengths::Login::COUNT_OF_MENU_LINES
        )
    )
        login(
            static_cast<AccountType>(
                choice - 1
            )
        );
}

void startProgram() {
    while (true)
        performAccountTypeLoginMenu();
}

int main() {
    Utils::activeRandom();
    startProgram();
}