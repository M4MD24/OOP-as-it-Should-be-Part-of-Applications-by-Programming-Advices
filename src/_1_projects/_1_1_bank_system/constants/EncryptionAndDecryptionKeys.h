#pragma once

#include <string>

using namespace std;

namespace EncryptionAndDecryptionKeys {
    namespace Accounts {
        constexpr short OWNER_ACCOUNTS = 1;
        constexpr short ADMIN_ACCOUNTS = 2;
        constexpr short CLIENT_ACCOUNTS = 3;
    }

    namespace Logs {
        constexpr short ADMIN_LOGIN_LOG = 4;
        constexpr short CLIENT_TRANSFER_LOG = 5;
    }
}