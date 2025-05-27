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
    AdminAccount originalAccount = targetAccount;

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

        case AdminAccount::ContactNumber: {
            string contactNumber;
            Input::readContactNumber(
                contactNumber
            );
            targetAccount.setContactNumber(
                contactNumber
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

            originalAccount.setAccount(
                targetAccount
            );
        } else
            targetAccount.setAccount(
                originalAccount
            );
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

        if (choice != Lengths::Person::Owner::COUNT_OF_MENU_LINES) {
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
                ClientAccount::displayTotalBalances();
                break;
            }
            default: { break; }
            }
        } else
            return;
    } while (true);
}

void modifyBalancesMenu(
    vector<Balance> &balances
) {
    const short COUNT_OF_BALANCES = static_cast<short>(balances.size());
    do {
        Utils::displayMenu(
            Texts::Person::Admin::MODIFY_BALANCES_MENU_TITLE,
            0,
            {}
        );

        Utils::displayBalances(
            balances
        );

        Utils::displayMessage(
            to_string(
                COUNT_OF_BALANCES + 1
            ) + " - Back to ~{ " + Texts::Person::Admin::MANAGE_BALANCES_MENU_TITLE + " }~"
        );

        short choice;
        Input::readChoice(
            choice,
            1,
            static_cast<short>(COUNT_OF_BALANCES + 1)
        );

        if (choice == COUNT_OF_BALANCES + 1)
            return;
        Balance balance;
        ClientAccount::readBalance(
            balance
        );
        balances[choice - 1] = balance;
    } while (true);
}

void manageBalancesMenu(
    vector<Balance> &balances
) {
    do {
        Utils::displayBalances(
            balances
        );

        Utils::displayMenu(
            Texts::Person::Admin::MANAGE_BALANCES_MENU_TITLE,
            Lengths::Person::Admin::COUNT_OF_MANAGE_BALANCES_MENU,
            Texts::Person::Admin::MANAGE_BALANCES_MENU_LINES
        );

        short choice;
        Input::readChoice(
            choice,
            1,
            Lengths::Person::Admin::COUNT_OF_MANAGE_BALANCES_MENU
        );

        switch (static_cast<ClientAccount::ManageBalancesMenuChoice>(choice - 1)) {
        case ClientAccount::CreateBalance: {
            vector<Balance> createdBalances;
            ClientAccount::readBalances(
                createdBalances
            );

            for (Balance &createdBalance : createdBalances) {
                bool found = false;
                for (Balance &balance : balances)
                    if (createdBalance.getCode() == balance.getCode()) {
                        found = true;
                        break;
                    }
                if (!found)
                    balances.push_back(
                        createdBalance
                    );
            }
            break;
        }

        case ClientAccount::ModifyBalance: {
            modifyBalancesMenu(
                balances
            );
            break;
        }

        case ClientAccount::DeleteBalance: {
            string code;
            Input::readCode(
                code
            );

            bool found = false;
            short index = 0;
            while (index < balances.size()) {
                if (balances[index].getCode() == code) {
                    found = true;
                    break;
                }
                index++;
            }

            if (found)
                balances.erase(
                    balances.begin() + index
                );
            else
                Utils::displayMessage(
                    "Isn't Found."
                );
            break;
        }

        case ClientAccount::BackToModifyMenyChoice: { return; }

        default: { break; }
        }
    } while (true);
}

void modifyMenu(
    ClientAccount targetAccount
) {
    ClientAccount originalAccount = targetAccount;

    do {
        ClientAccount::printAccountInformation(
            targetAccount
        );

        Utils::displayLine(
            Texts::Person::Client::LINE_CHARACTER,
            Lengths::Person::Client::LINE_LENGTH
        );

        Utils::displayMenu(
            Texts::Person::Admin::MODIFY_MENU_TITLE,
            Lengths::Person::Admin::COUNT_OF_MODIFY_MENU,
            Texts::Person::Admin::MODIFY_MENU_LINES
        );

        short choice;
        Input::readChoice(
            choice,
            1,
            Lengths::Person::Admin::COUNT_OF_MODIFY_MENU
        );

        switch (static_cast<ClientAccount::ModifyMenuChoice>(choice - 1)) {
        case ClientAccount::PIN_Code: {
            string pinCode;
            Input::readPIN_Code(
                pinCode
            );
            targetAccount.setPIN_Code(
                pinCode
            );
            break;
        }

        case ClientAccount::FirstName: {
            string firstName;
            Input::readFirstName(
                firstName
            );
            targetAccount.setFirstName(
                firstName
            );
            break;
        }

        case ClientAccount::SecondName: {
            string secondName;
            Input::readSecondName(
                secondName
            );
            targetAccount.setSecondName(
                secondName
            );
            break;
        }

        case ClientAccount::CountryCode: {
            string countryCode;
            Input::readCountryCode(
                countryCode
            );
            targetAccount.setCountryCode(
                countryCode
            );
            break;
        }

        case ClientAccount::ContactNumber: {
            string contactNumber;
            Input::readContactNumber(
                contactNumber
            );
            targetAccount.setContactNumber(
                contactNumber
            );
            break;
        }

        case ClientAccount::Email: {
            string email;
            Input::readEmail(
                email
            );
            targetAccount.setEmail(
                email
            );
            break;
        }

        case ClientAccount::Balances: {
            vector<Balance> balances = targetAccount.getBalances();
            manageBalancesMenu(
                balances
            );
            targetAccount.setBalances(
                balances
            );
            break;
        }

        case ClientAccount::BackToManageClientsMenuFromModifyMenu: { return; }

        default: { break; }
        }

        if (
            Input::confirm()
        ) {
            targetAccount.setLastModifyDate(
                {}
            );

            ClientAccount::modifyAccount(
                targetAccount,
                true
            );

            originalAccount.setAccount(
                targetAccount
            );
        } else
            targetAccount.setAccount(
                originalAccount
            );
    } while (true);
}

void transactionMenu(
    ClientAccount &currentAccount
) {
    ClientAccount originalAccount = currentAccount;
    short choice;
    do {
        Utils::displayBalances(
            currentAccount.getBalances()
        );

        Utils::displayMenu(
            Texts::Person::Admin::TRANSACTION_MENU_TITLE,
            Lengths::Person::Admin::COUNT_OF_TRANSACTION_MENU,
            Texts::Person::Admin::TRANSACTION_MENU
        );

        Input::readChoice(
            choice,
            1,
            Lengths::Person::Admin::COUNT_OF_TRANSACTION_MENU
        );

        bool found = false;
        short index = 0;
        vector<Balance> balances = currentAccount.getBalances();
        Balance targetBalance;

        switch (static_cast<ClientAccount::TransactionMenuChoice>(choice - 1)) {
        case ClientAccount::Deposit: {
            Balance depositedBalance;
            ClientAccount::readBalance(
                depositedBalance
            );

            string code = depositedBalance.getCode();
            depositedBalance.setCode(
                String::toUppercaseText(
                    code
                )
            );

            while (index < currentAccount.getBalances().size()) {
                targetBalance = balances[index];
                if (targetBalance.getCode() == depositedBalance.getCode()) {
                    found = true;
                    break;
                }
                index++;
            }

            if (found)
                balances[index].setCount(
                    targetBalance.getCount() +
                    depositedBalance.getCount()
                );
            else
                balances.push_back(
                    targetBalance
                );
            currentAccount.setBalances(
                balances
            );

            if (
                Input::confirm()
            ) {
                currentAccount.setLastModifyDate(
                    {}
                );

                ClientAccount::modifyAccount(
                    currentAccount,
                    true
                );

                originalAccount.setAccount(
                    currentAccount
                );
            } else
                currentAccount.setAccount(
                    originalAccount
                );

            break;
        }
        case ClientAccount::Withdraw: {
            Balance withdrawnBalance;
            ClientAccount::readBalance(
                withdrawnBalance
            );

            string code = withdrawnBalance.getCode();
            withdrawnBalance.setCode(
                String::toUppercaseText(
                    code
                )
            );

            while (index < currentAccount.getBalances().size()) {
                targetBalance = balances[index];
                if (targetBalance.getCode() == withdrawnBalance.getCode()) {
                    found = true;
                    break;
                }
                index++;
            }

            if (found)
                if (withdrawnBalance.getCount() <= targetBalance.getCount()) {
                    balances[index].setCount(
                        targetBalance.getCount() -
                        withdrawnBalance.getCount()
                    );
                    currentAccount.setBalances(
                        balances
                    );

                    if (
                        Input::confirm()
                    ) {
                        currentAccount.setLastModifyDate(
                            {}
                        );

                        ClientAccount::modifyAccount(
                            currentAccount,
                            true
                        );

                        originalAccount.setAccount(
                            currentAccount
                        );
                    } else
                        currentAccount.setAccount(
                            originalAccount
                        );
                } else
                    cout << "The balance is not sufficient to withdraw the required amount." << endl;

            break;
        }
        case ClientAccount::Transfer: {
            string id;
            Input::readID(
                id
            );

            ClientAccount anotherAccount {
                id
            };

            ClientAccount targetAnotherAccount = ClientAccount::findByID_InFile(
                anotherAccount
            );

            if (
                ClientAccount::isValidAccountByID(
                    anotherAccount,
                    targetAnotherAccount,
                    false,
                    true
                )
            ) {
                Balance withdrawnBalanceFromCurrentAccount;
                ClientAccount::readBalance(
                    withdrawnBalanceFromCurrentAccount
                );

                string code = withdrawnBalanceFromCurrentAccount.getCode();
                withdrawnBalanceFromCurrentAccount.setCode(
                    String::toUppercaseText(
                        code
                    )
                );

                while (index < currentAccount.getBalances().size()) {
                    targetBalance = balances[index];
                    if (targetBalance.getCode() == withdrawnBalanceFromCurrentAccount.getCode()) {
                        found = true;
                        break;
                    }
                    index++;
                }

                if (found)
                    if (withdrawnBalanceFromCurrentAccount.getCount() <= targetBalance.getCount()) {
                        balances[index].setCount(
                            targetBalance.getCount() -
                            withdrawnBalanceFromCurrentAccount.getCount()
                        );
                        currentAccount.setBalances(
                            balances
                        );

                        found = false;
                        index = 0;
                        balances = targetAnotherAccount.getBalances();
                        targetBalance = {};

                        while (index < targetAnotherAccount.getBalances().size()) {
                            targetBalance = balances[index];
                            if (targetBalance.getCode() == withdrawnBalanceFromCurrentAccount.getCode()) {
                                found = true;
                                break;
                            }
                            index++;
                        }

                        if (found) {
                            balances[index].setCount(
                                targetBalance.getCount() +
                                withdrawnBalanceFromCurrentAccount.getCount()
                            );
                            balances.push_back(
                                targetBalance
                            );
                        } else
                            balances.push_back(
                                withdrawnBalanceFromCurrentAccount
                            );

                        targetAnotherAccount.setBalances(
                            balances
                        );

                        if (
                            Input::confirm()
                        ) {
                            currentAccount.setLastModifyDate(
                                {}
                            );

                            ClientAccount::modifyAccount(
                                currentAccount,
                                true
                            );

                            targetAnotherAccount.setLastModifyDate(
                                {}
                            );

                            ClientAccount::modifyAccount(
                                targetAnotherAccount,
                                false
                            );

                            originalAccount.setAccount(
                                currentAccount
                            );
                        } else
                            currentAccount.setAccount(
                                originalAccount
                            );
                    } else
                        cout << "The balance is not sufficient to withdraw the required amount." << endl;
            }
            break;
        }
        case ClientAccount::Conversion: {
            Balance convertedBalance;
            ClientAccount::readBalance(
                convertedBalance
            );

            string code = convertedBalance.getCode();
            convertedBalance.setCode(
                String::toUppercaseText(
                    code
                )
            );

            while (index < currentAccount.getBalances().size()) {
                targetBalance = balances[index];
                if (targetBalance.getCode() == convertedBalance.getCode()) {
                    found = true;
                    break;
                }
                index++;
            }

            if (found)
                if (convertedBalance.getCount() <= targetBalance.getCount()) {
                    balances[index].setCount(
                        targetBalance.getCount() -
                        convertedBalance.getCount()
                    );
                    currentAccount.setBalances(
                        balances
                    );

                    found = false;
                    index = 0;
                    targetBalance = {};
                    Input::readCode(
                        code
                    );
                    String::toUppercaseText(
                        code
                    );

                    while (index < currentAccount.getBalances().size()) {
                        targetBalance = balances[index];
                        if (targetBalance.getCode() == code) {
                            found = true;
                            break;
                        }
                        index++;
                    }

                    if (found)
                        balances[index].setCount(
                            targetBalance.getCount() +
                            convertedBalance.getCount()
                        );
                    else {
                        convertedBalance.setCode(
                            code
                        );
                        balances.push_back(
                            convertedBalance
                        );
                    }

                    currentAccount.setBalances(
                        balances
                    );

                    if (
                        Input::confirm()
                    ) {
                        currentAccount.setLastModifyDate(
                            {}
                        );

                        ClientAccount::modifyAccount(
                            currentAccount,
                            true
                        );

                        originalAccount.setAccount(
                            currentAccount
                        );
                    } else
                        currentAccount.setAccount(
                            originalAccount
                        );
                } else
                    cout << "The balance is not sufficient to withdraw the required amount." << endl;
            break;
        }
        case ClientAccount::BackToManageClientsMenuFromTransactionMenu: { return; }
        default: { break; }
        }
    } while (true);
}

void adminMenu(
    AdminAccount adminAccount
) {
    short choice;
    do {
        AdminAccount::displayAdminMenu(
            adminAccount.getPermissions()
        );

        Input::readChoice(
            choice,
            1,
            Lengths::Person::Admin::COUNT_OF_MENU_LINES
        );

        if (choice != Lengths::Person::Admin::COUNT_OF_MENU_LINES) {
            bool found = false;
            for (const AdminAccount::AdminPermission &PERMISSION : adminAccount.getPermissions())
                if (PERMISSION == static_cast<AdminAccount::AdminPermission>(choice - 1)) {
                    found = true;
                    break;
                }

            if (found) {
                if (choice != Lengths::Person::Admin::COUNT_OF_MENU_LINES)
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
                case AdminAccount::AdminMenuChoice::ModifyClient: {
                    string id;
                    Input::readID(
                        id
                    );

                    ClientAccount currentClientAccount {
                        id
                    };

                    const ClientAccount TARGET_ACCOUNT = ClientAccount::findByID_InFile(
                        currentClientAccount
                    );

                    if (
                        ClientAccount::isValidAccountByID(
                            currentClientAccount,
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
                case AdminAccount::AdminMenuChoice::DeleteClient: {
                    string id;
                    Input::readID(
                        id
                    );

                    ClientAccount currentClientAccount {
                        id
                    };

                    ClientAccount targetAccount = ClientAccount::findByID_InFile(
                        currentClientAccount
                    );

                    if (
                        ClientAccount::isValidAccountByID(
                            currentClientAccount,
                            targetAccount,
                            true,
                            true
                        )
                    ) {
                        if (
                            Input::confirm()
                        )
                            ClientAccount::deleteAccount(
                                targetAccount
                            );
                    }
                    break;
                }
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
                case AdminAccount::AdminMenuChoice::TransactionClient: {
                    string id;
                    Input::readID(
                        id
                    );

                    ClientAccount currentAccount {
                        id
                    };

                    ClientAccount targetAccount = ClientAccount::findByID_InFile(
                        currentAccount
                    );

                    if (
                        ClientAccount::isValidAccountByID(
                            currentAccount,
                            targetAccount,
                            true,
                            true
                        )
                    )
                        transactionMenu(
                            targetAccount
                        );
                    break;
                }
                case AdminAccount::AdminMenuChoice::ClientEventLog: { return; }
                default: { break; }
                }
            } else
                cout << "You don't have permission." << endl;
        } else
            return;
    } while (true);
}

void login(
    const AccountType &ACCOUNT_TYPE,
    short &attempt
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
        ) {
            ownerMenu();
            attempt = 1;
        }
        break;
    }
    case Admin: {
        AdminAccount currentAdminAccount {
            username,
            password
        };
        const AdminAccount TARGET_ADMIN_ACCOUNT = AdminAccount::findByUsernameInFile(
            currentAdminAccount
        );
        if (
            AdminAccount::isValidAccountByUsernameAndPassword(
                currentAdminAccount,
                TARGET_ADMIN_ACCOUNT
            )
        ) {
            adminMenu(
                TARGET_ADMIN_ACCOUNT
            );
            attempt = 1;
        }
        break;
    }
    default: { break; }
    }

    attempt++;
}

void performAccountTypeLoginMenu(
    short attempt = 1
) {
    while (attempt < 4) {
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
                ),
                attempt
            );
    }
}

void startProgram() { performAccountTypeLoginMenu(); }

int main() {
    Utils::activeRandom();
    startProgram();
}