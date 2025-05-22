#pragma once

using namespace std;

namespace Limits {
    namespace Username {
        constexpr short MINIMUM = 4;
        constexpr short MAXIMUM = 20;
    }

    namespace Password {
        constexpr short MINIMUM = 4;
        constexpr short MAXIMUM = 20;
    }

    namespace FullName {
        namespace FirstName {
            constexpr short MINIMUM = 1;
            constexpr short MAXIMUM = 20;
        }

        namespace SecondName {
            constexpr short MINIMUM = 1;
            constexpr short MAXIMUM = 20;
        }

        constexpr short MAXIMUM = FirstName::MAXIMUM + 1 + SecondName::MAXIMUM;
    }

    namespace MobileNumber {
        namespace CountryCode {
            constexpr short MINIMUM = 2;
            constexpr short MAXIMUM = 5;
        }

        namespace ContactNumber {
            constexpr short MINIMUM = 6;
            constexpr short MAXIMUM = 14;
        }

        constexpr short MAXIMUM = CountryCode::MAXIMUM + ContactNumber::MAXIMUM;
    }

    namespace Email {
        constexpr short MINIMUM = 5;
        constexpr short MAXIMUM = 30;
    }
}