#pragma once

#include <string>

using namespace std;

namespace FilePaths {
    const string OWNER_ACCOUNTS_FILE_PATH = "src/_1_projects/_1_1_bank_system/database/accounts/OwnerAccounts.txt";
    const string ADMIN_ACCOUNTS_FILE_PATH = "src/_1_projects/_1_1_bank_system/database/accounts/AdminAccounts.txt";
    const string CLIENT_ACCOUNTS_FILE_PATH = "src/_1_projects/_1_1_bank_system/database/accounts/ClientAccounts.txt";

    const string ADMIN_LOGIN_LOG_FILE_PATH = "src/_1_projects/_1_1_bank_system/database/logs/AdminLoginLog.txt";
    const string CLIENT_TRANSFER_LOG_FILE_PATH = "src/_1_projects/_1_1_bank_system/database/logs/ClientTransferLog.txt";
}