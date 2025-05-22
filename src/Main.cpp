#include "constants/Texts.h"
#include "libraries/Options.h"
#include "libraries/Input.h"
#include "libraries/Utils.h"
#include "libraries/Validation.h"
#include "models/accounts/admin/AdminAccount.h"
#include "models/accounts/owner/OwnerAccount.h"

[[noreturn]] void ownerMenu() {
    short choice;
    do {
        Utils::displayMenu(
            Texts::Person::Owner::MENU_TITLE,
            Lengths::Person::Owner::COUNT_OF_LINES,
            Texts::Person::Owner::LINES
        );

        Input::readChoice(
            choice,
            1,
            Lengths::Person::Owner::COUNT_OF_LINES
        );

        switch (static_cast<OwnerAccount::OwnerMenuChoice>(choice - 1)) {
        case OwnerAccount::OwnerMenuChoice::CreateNewAdmin: {
            AdminAccount::createAccount();
            break;
        }
        case OwnerAccount::OwnerMenuChoice::ModifyAdmin: {
            break;
        }
        case OwnerAccount::OwnerMenuChoice::DeleteAdmin: {
            break;
        }
        case OwnerAccount::OwnerMenuChoice::FindAdmin: {
            Utils::displayMenu(
                Texts::Person::Owner::LINES[choice - 1],
                0,
                {}
            );

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

            AdminAccount::isValidAccountByUsername(
                currentAdminAccount,
                TARGET_ACCOUNT,
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
        case OwnerAccount::OwnerMenuChoice::AdminEventLog: {
            break;
        }
        case OwnerAccount::OwnerMenuChoice::Logout: { return; }
        default: { break; }
        }
    } while (true);
}

[[noreturn]] void adminMenu() {
    short choice;
    do {
        Utils::displayMenu(
            Texts::Person::Admin::MENU_TITLE,
            Lengths::Person::Admin::COUNT_OF_LINES,
            Texts::Person::Admin::LINES
        );

        Input::readChoice(
            choice,
            1,
            Lengths::Person::Admin::COUNT_OF_LINES
        );

        /*switch (static_cast<AdminAccount::AdminMenuChoice>(choice- 1)) {
        default: { break; }*/
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
        Lengths::Login::COUNT_OF_LINES,
        Texts::Login::LINES
    );

    Input::readChoice(
        choice
    );

    if (
        Validation::isBetweenNumbers(
            choice,
            static_cast<short>(1),
            Lengths::Login::COUNT_OF_LINES
        )
    )
        login(
            static_cast<AccountType>(
                choice - 1
            )
        );
}

[[noreturn]] void startProgram() {
    while (true)
        performAccountTypeLoginMenu();
}

int main() {
    Utils::activeRandom();
    startProgram();
}