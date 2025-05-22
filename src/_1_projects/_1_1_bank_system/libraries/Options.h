#pragma once

enum AccountType {
    Owner = 0,
    Admin = 1,
    Client = 2
};

enum Mode {
    Login,
    Find,
    Create,
    Modify,
    Delete
};