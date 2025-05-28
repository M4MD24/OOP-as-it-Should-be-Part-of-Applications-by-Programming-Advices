#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Date {
    enum DateCompare {
        Before = -1,
        Equal = 0,
        After = 1
    };

    short day = 0;
    short month = 0;
    short year = 0;
    static inline const string DEFAULT_DELIMITER = "-";
    string delimiter = DEFAULT_DELIMITER;

    const string DAYS[7] = {
        "Saturday",
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday"
    };

    const string MONTHS[12] = {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };

    static Date getSystemDate() {
        const time_t TIME = time(
            nullptr
        );
        const tm *TIME_NOW = localtime(
            &TIME
        );
        return {
            static_cast<short>(TIME_NOW->tm_mday),
            static_cast<short>(TIME_NOW->tm_mon + 1),
            static_cast<short>(TIME_NOW->tm_year + 1900)
        };
    }

    static void swapDates(
        Date &firstDate,
        Date &secondDate
    ) {
        const Date TEMPORARY_DATE = firstDate;
        firstDate.setDate(
            secondDate
        );
        secondDate.setDate(
            TEMPORARY_DATE
        );
    }

    static bool isLastDayInWeek(
        const short &DAY_OF_WEEK
    ) { return DAY_OF_WEEK == 6; }

    static bool isWeekend(
        const short &DAY_OF_WEEK
    ) {
        return isLastDayInWeek(
            DAY_OF_WEEK
        );
    }

    static bool isBusinessDay(
        const short &DAY_OF_WEEK
    ) {
        return !isWeekend(
            DAY_OF_WEEK
        );
    }

    static bool isPositiveNumber(
        const short &NUMBER
    ) { return NUMBER > 0; }

    static void splitText(
        string text,
        vector<short> &parts,
        const string &DELIMITER
    ) {
        size_t position;
        while (
            (
                position = text.find(
                    DELIMITER
                )
            ) != string::npos
        ) {
            parts.push_back(
                static_cast<short>(
                    stoi(
                        text.substr(
                            0,
                            position
                        )
                    )
                )
            );
            text.erase(
                0,
                position + DELIMITER.length()
            );
        }
        parts.push_back(
            static_cast<short>(
                stoi(
                    text
                )
            )
        );
    }

    static vector<short> convertDateTextToDateParts(
        const string &DATE_TEXT,
        const string &DELIMITER = DEFAULT_DELIMITER
    ) {
        vector<short> dateParts;
        splitText(
            DATE_TEXT,
            dateParts,
            DELIMITER
        );
        return dateParts;
    }

    static Date convertDatePartsToDateStructure(
        const vector<short> &DATE_PARTS,
        const string &DELIMITER = DEFAULT_DELIMITER
    ) {
        return {
            DATE_PARTS[0],
            DATE_PARTS[1],
            DATE_PARTS[2],
            DELIMITER
        };
    }

    static Date convertDateTextToDateStructure(
        const string &DATE_TEXT,
        const string &DELIMITER = DEFAULT_DELIMITER
    ) {
        return convertDatePartsToDateStructure(
            convertDateTextToDateParts(
                DATE_TEXT,
                DELIMITER
            ),
            DELIMITER
        );
    }

public:
    Date() {
        const Date DATE_NOW = getSystemDate();
        day = DATE_NOW.day;
        month = DATE_NOW.month;
        year = DATE_NOW.year;
        delimiter = DEFAULT_DELIMITER;
    }

    static void setDate(
        Date &from,
        Date to
    ) {
        from.setDay(
            to.getDay()
        );
        from.setMonth(
            to.getMonth()
        );
        from.setYear(
            to.getYear()
        );
        from.setDelimiter(
            to.getDelimiter()
        );
    }

    void setDate(
        Date to
    ) {
        setDate(
            *this,
            to
        );
    }

    Date(
        const string &DATE_TEXT,
        const string &DELIMITER = DEFAULT_DELIMITER
    ) {
        setDate(
            *this,
            convertDateTextToDateStructure(
                DATE_TEXT,
                DELIMITER
            )
        );
    }

    Date(
        const short &DAY,
        const short &MONTH,
        const short &YEAR,
        const string &SEPARATOR = DEFAULT_DELIMITER
    ) {
        day = DAY;
        month = MONTH;
        year = YEAR;
        delimiter = SEPARATOR;
    }

    void setDay(
        const short &DAY
    ) {
        day = DAY;
    }

    short getDay() {
        return day;
    }

    void setMonth(
        const short &MONTH
    ) {
        month = MONTH;
    }

    short getMonth() {
        return month;
    }

    void setYear(
        const short &YEAR
    ) {
        year = YEAR;
    }

    short getYear() {
        return year;
    }

    void setDelimiter(
        const string &DELIMITER = DEFAULT_DELIMITER
    ) {
        delimiter = DELIMITER;
    }

    string getDelimiter() {
        return delimiter;
    }

    static bool isLeapYear(
        const short &YEAR
    ) {
        return YEAR % 4 == 0 &&
        (
            YEAR % 100 != 0 ||
            YEAR % 400 == 0
        );
    }

    bool isLeapYear() {
        return isLeapYear(
            year
        );
    }

    static short monthDays(
        const short &MONTH,
        const short &YEAR
    ) {
        if (MONTH == 2)
            return isLeapYear(
                       YEAR
                   )
                       ? 29
                       : 28;

        switch (MONTH) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
        default:
            return 30;
        }
    }

    short monthDays() {
        return monthDays(
            month,
            year
        );
    }

    static short dayOfWeek(
        const short &DAY,
        short month,
        short year
    ) {
        if (month < 3) {
            month += 12;
            year -= 1;
        }

        const short YEAR_PART = static_cast<short>(year % 100);
        const short CENTURY = static_cast<short>(year / 100);
        const short ZELLER_RESULT = static_cast<short>(
            (
                DAY + 13 *
                (month + 1) / 5 +
                YEAR_PART + YEAR_PART / 4 +
                CENTURY / 4 + 5 *
                CENTURY
            ) %
            7
        );

        return ZELLER_RESULT;
    }

    short dayOfWeek() {
        return dayOfWeek(
            day,
            month,
            year
        );
    }

    static string dayOfWeekName(
        const short &DAY,
        const short &MONTH,
        const short &YEAR
    ) {
        return Date().DAYS[
            dayOfWeek(
                DAY,
                MONTH,
                YEAR
            )
        ];
    }

    string dayOfWeekName() {
        return dayOfWeekName(
            day,
            month,
            year
        );
    }

    static string monthName(
        const short &MONTH
    ) {
        return Date().MONTHS[
            MONTH - 1
        ];
    }

    string monthName() {
        return monthName(
            month
        );
    }

    static string dayName(
        const short &DAY
    ) {
        return Date().DAYS[
            DAY - 1
        ];
    }

    static short totalDaysFromStartYearToTargetDate(
        const short &DAY,
        const short &MONTH,
        const short &YEAR
    ) {
        short totalDays = 0;
        for (short month = 1; month < MONTH; ++month)
            totalDays = static_cast<short>(
                totalDays +
                monthDays(
                    month,
                    YEAR
                )
            );
        return static_cast<short>(totalDays + DAY);
    }

    short totalDaysFromStartYearToTargetDate() {
        return totalDaysFromStartYearToTargetDate(
            day,
            month,
            year
        );
    }

    static bool isBefore(
        const Date &FIRST_DATE,
        const Date &SECOND_DATE
    ) {
        if (FIRST_DATE.year != SECOND_DATE.year)
            return FIRST_DATE.year < SECOND_DATE.year;
        if (FIRST_DATE.month != SECOND_DATE.month)
            return FIRST_DATE.month < SECOND_DATE.month;
        return FIRST_DATE.day < SECOND_DATE.day;
    }

    bool isBefore(
        const Date &SECOND_DATE
    ) {
        return isBefore(
            *this,
            SECOND_DATE
        );
    }

    static bool areDatesEqual(
        const Date &FIRST_DATE,
        const Date &SECOND_DATE
    ) {
        return FIRST_DATE.year == SECOND_DATE.year &&
            FIRST_DATE.month == SECOND_DATE.month &&
            FIRST_DATE.day == SECOND_DATE.day;
    }

    bool areDatesEqual(
        const Date &SECOND_DATE
    ) {
        return areDatesEqual(
            *this,
            SECOND_DATE
        );
    }

    static bool isAfter(
        const Date &FIRST_DATE,
        const Date &SECOND_DATE
    ) {
        if (FIRST_DATE.year != SECOND_DATE.year)
            return FIRST_DATE.year > SECOND_DATE.year;
        if (FIRST_DATE.month != SECOND_DATE.month)
            return FIRST_DATE.month > SECOND_DATE.month;
        return FIRST_DATE.day > SECOND_DATE.day;
    }

    bool isAfter(
        const Date &SECOND_DATE
    ) {
        return isAfter(
            *this,
            SECOND_DATE
        );
    }

    static DateCompare compareDates(
        const Date &FIRST_DATE,
        const Date &SECOND_DATE
    ) {
        if (
            areDatesEqual(
                FIRST_DATE,
                SECOND_DATE
            )
        )
            return Equal;
        if (
            isAfter(
                FIRST_DATE,
                SECOND_DATE
            )
        )
            return After;
        return Before;
    }

    DateCompare compareDates(
        const Date &SECOND_DATE
    ) {
        return compareDates(
            *this,
            SECOND_DATE
        );
    }

    static string dateComparisonText(
        const Date &FIRST_DATE,
        const Date &SECOND_DATE
    ) {
        string result = "First Date is ";
        switch (
            compareDates(
                FIRST_DATE,
                SECOND_DATE
            )
        ) {
        case 0:
            result += "Equal to";
            break;
        case 1:
            result += "Bigger Than";
            break;
        default:
            result += "Less Than";
        }
        return result + " Second Date";
    }

    string dateComparisonText(
        const Date &SECOND_DATE
    ) {
        return dateComparisonText(
            *this,
            SECOND_DATE
        );
    }

    static bool isLastMonthInYear(
        const short &MONTH
    ) {
        return MONTH == 12;
    }

    bool isLastMonthInYear() {
        return isLastMonthInYear(
            month
        );
    }

    static bool isLastDayInMonth(
        const short &DAY,
        const short &MONTH,
        const short &YEAR
    ) {
        return DAY == monthDays(
            MONTH,
            YEAR
        );
    }

    bool isLastDayInMonth() {
        return isLastDayInMonth(
            day,
            month,
            year
        );
    }

    static void nextDay(
        Date &date
    ) {
        if (
            ++date.day > monthDays(
                date.month,
                date.year
            )
        ) {
            date.day = 1;
            if (++date.month > 12) {
                date.month = 1;
                ++date.year;
            }
        }
    }

    void nextDay() {
        nextDay(
            *this
        );
    }

    static void nextDays(
        Date &date,
        short days
    ) {
        while (days--)
            nextDay(
                date
            );
    }

    void nextDays(
        const short &DAYS
    ) {
        nextDays(
            *this,
            DAYS
        );
    }

    static short daysDifferenceInDates(
        Date firstDate,
        Date secondDate,
        const bool &INCLUDE_END_DAY = false
    ) {
        short daysDifference = 0;

        if (
            compareDates(
                firstDate,
                secondDate
            ) == 1
        ) {
            swapDates(
                firstDate,
                secondDate
            );
        }

        while (
            !compareDates(
                firstDate,
                secondDate
            ) == 0
        ) {
            daysDifference++;
            nextDay(
                firstDate
            );
        }

        return static_cast<short>(
            INCLUDE_END_DAY
                ? daysDifference + 1
                : daysDifference
        );
    }

    short daysDifferenceInDates(
        const Date &SECOND_DATE,
        const bool &INCLUDE_END_DAY = false
    ) {
        return daysDifferenceInDates(
            *this,
            SECOND_DATE,
            INCLUDE_END_DAY
        );
    }

    static void nextWeek(
        Date &date
    ) {
        nextDays(
            date,
            7
        );
    }

    void nextWeek() {
        nextWeek(
            *this
        );
    }

    static void nextWeeks(
        Date &date,
        short weeks
    ) {
        while (weeks--)
            nextWeek(
                date
            );
    }

    void nextWeeks(
        const short &weeks
    ) {
        nextWeeks(
            *this,
            weeks
        );
    }

    static void nextMonth(
        Date &date
    ) {
        if (++date.month > 12) {
            date.month = 1;
            date.year++;
        }

        if (
            const short MONTH_DAYS = monthDays(
                date.month,
                date.year
            );
            date.day > MONTH_DAYS
        )
            date.day = MONTH_DAYS;
    }

    void nextMonth() {
        nextMonth(
            *this
        );
    }

    static void nextMonths(
        Date &date,
        short &months
    ) {
        while (months--)
            nextMonth(
                date
            );
    }

    void nextMonths(
        short months
    ) {
        nextMonths(
            *this,
            months
        );
    }

    static void nextYear(
        Date &date
    ) {
        if (
            isLeapYear(
                date.year++
            ) && (
                date.month > 2 ||
                (
                    date.month == 2 &&
                    date.day == 29
                )
            )
        )
            nextDay(
                date
            );
    }

    void nextYear() {
        nextYear(
            *this
        );
    }

    static void nextYears(
        Date &date,
        short years
    ) {
        while (years--)
            nextYear(
                date
            );
    }

    void nextYears(
        const short &YEARS
    ) {
        nextYears(
            *this,
            YEARS
        );
    }

    static void nextDecade(
        Date &date
    ) {
        nextYears(
            date,
            10
        );
    }

    void nextDecade() {
        nextDecade(
            *this
        );
    }

    static void nextDecades(
        Date &date,
        short decades
    ) {
        while (decades--)
            nextDecade(
                date
            );
    }

    void nextDecades(
        const short &DECADES
    ) {
        nextDecades(
            *this,
            DECADES
        );
    }

    static void nextCentury(
        Date &date
    ) {
        nextDecades(
            date,
            10
        );
    }

    void nextCentury() {
        nextCentury(
            *this
        );
    }

    static void nextCenturies(
        Date &date,
        short centuries
    ) {
        while (centuries--)
            nextCentury(
                date
            );
    }

    void nextCenturies(
        const short &CENTURIES
    ) {
        nextCenturies(
            *this,
            CENTURIES
        );
    }

    static void nextMillennium(
        Date &date
    ) {
        nextCenturies(
            date,
            10
        );
    }

    void nextMillennium() {
        nextMillennium(
            *this
        );
    }

    static void nextMillenniums(
        Date &date,
        short millenniums
    ) {
        while (millenniums--)
            nextMillennium(
                date
            );
    }

    void nextMillenniums(
        const short &MILLENNIUMS
    ) {
        nextMillenniums(
            *this,
            MILLENNIUMS
        );
    }

    static void previousDay(
        Date &date
    ) {
        if (--date.day == 0) {
            if (--date.month == 0) {
                date.month = 12;
                --date.year;
            }
            date.day = monthDays(
                date.month,
                date.year
            );
        }
    }

    void previousDay() {
        previousDay(
            *this
        );
    }

    static void previousDays(
        Date &date,
        short days
    ) {
        while (days--)
            previousDay(
                date
            );
    }

    void previousDays(
        const short &DAYS
    ) {
        previousDays(
            *this,
            DAYS
        );
    }

    static void previousWeek(
        Date &date
    ) {
        previousDays(
            date,
            7
        );
    }

    void previousWeek() {
        previousWeek(
            *this
        );
    }

    static void previousWeeks(
        Date &date,
        short weeks
    ) {
        while (weeks--)
            previousWeek(
                date
            );
    }

    void previousWeeks(
        const short &WEEKS
    ) {
        previousWeeks(
            *this,
            WEEKS
        );
    }

    static void previousMonth(
        Date &date
    ) {
        if (--date.month < 1) {
            date.month = 12;
            date.year--;
        }

        if (
            const short MONTH_DAYS = monthDays(
                date.month,
                date.year
            );
            date.day > MONTH_DAYS
        )
            date.day = MONTH_DAYS;
    }

    void previousMonth() {
        previousMonth(
            *this
        );
    }

    static void previousMonths(
        Date &date,
        short months
    ) {
        while (months--)
            previousMonth(
                date
            );
    }

    void previousMonths(
        const short &MONTHS
    ) {
        previousMonths(
            *this,
            MONTHS
        );
    }

    static void previousYear(
        Date &date
    ) {
        if (
            isLeapYear(
                date.year--
            ) && (
                date.month > 2 ||
                (
                    date.month == 2 &&
                    date.day == 29
                )
            )
        )
            previousDay(
                date
            );
    }

    void previousYear() {
        previousYear(
            *this
        );
    }

    static void previousYears(
        Date &date,
        short years
    ) {
        while (years--)
            previousYear(
                date
            );
    }

    void previousYears(
        const short &YEARS
    ) {
        previousYears(
            *this,
            YEARS
        );
    }

    static void previousDecade(
        Date &date
    ) {
        previousYears(
            date,
            10
        );
    }

    void previousDecade() {
        previousDecade(
            *this
        );
    }

    static void previousDecades(
        Date &date,
        short decades
    ) {
        while (decades--)
            previousDecade(
                date
            );
    }

    void previousDecades(
        const short &DECADES
    ) {
        previousDecades(
            *this,
            DECADES
        );
    }

    static void previousCentury(
        Date &date
    ) {
        previousDecades(
            date,
            10
        );
    }

    void previousCentury() {
        previousCentury(
            *this
        );
    }

    static void previousCenturies(
        Date &date,
        short centuries
    ) {
        while (centuries--)
            previousCentury(
                date
            );
    }

    void previousCenturies(
        const short &CENTURIES
    ) {
        previousCenturies(
            *this,
            CENTURIES
        );
    }

    static void previousMillennium(
        Date &date
    ) {
        previousCenturies(
            date,
            10
        );
    }

    void previousMillennium() {
        previousMillennium(
            *this
        );
    }

    static void previousMillenniums(
        Date &date,
        short millenniums
    ) {
        while (millenniums--)
            previousMillennium(
                date
            );
    }

    void previousMillenniums(
        const short &MILLENNIUMS
    ) {
        previousMillenniums(
            *this,
            MILLENNIUMS
        );
    }

    bool isLastDayInWeek() {
        return isLastDayInWeek(
            dayOfWeek()
        );
    }

    bool isWeekend() { return isLastDayInWeek(); }

    bool isBusinessDay() {
        return !isWeekend();
    }

    static short daysUntilEndOfWeek(
        const Date &DATE
    ) {
        constexpr short REMAINDER_DAYS = 6;
        const short DAYS_UNTIL_END_OF_WEEK = static_cast<short>(
            REMAINDER_DAYS -
            dayOfWeek(
                DATE.day,
                DATE.month,
                DATE.year
            )
        );
        return DAYS_UNTIL_END_OF_WEEK != 0
                   ? DAYS_UNTIL_END_OF_WEEK
                   : REMAINDER_DAYS;
    }

    short daysUntilEndOfWeek() {
        return daysUntilEndOfWeek(
            *this
        );
    }

    static short daysUntilEndOfMonth(
        const Date &DATE
    ) {
        return static_cast<short>(
            monthDays(
                DATE.month,
                DATE.year
            ) - DATE.day
        );
    }

    short daysUntilEndOfMonth() {
        return daysUntilEndOfMonth(
            *this
        );
    }

    static short daysUntilEndOfYear(
        const Date &DATE
    ) {
        const short REMAINDER = isLeapYear(
                                    DATE.year
                                )
                                    ? 366
                                    : 365;
        short daysBeforeTargetDate = DATE.day;
        for (short month = 1; month < DATE.month; ++month)
            daysBeforeTargetDate = static_cast<short>(
                daysBeforeTargetDate +
                monthDays(
                    month,
                    DATE.year
                )
            );

        return static_cast<short>(REMAINDER - daysBeforeTargetDate);
    }

    short daysUntilEndOfYear() {
        return daysUntilEndOfYear(
            *this
        );
    }

    static short vacationDays(
        Date firstDate,
        Date secondDate
    ) {
        short counter = 0;
        if (
            isAfter(
                firstDate,
                secondDate
            )
        )
            swapDates(
                firstDate,
                secondDate
            );
        while (
            isBefore(
                firstDate,
                secondDate
            ) || areDatesEqual(
                firstDate,
                secondDate
            )
        ) {
            counter = static_cast<short>(
                counter +
                isWeekend(
                    dayOfWeek(
                        firstDate.day,
                        firstDate.month,
                        firstDate.year
                    )
                )
            );
            nextDay(
                firstDate
            );
        }
        return counter;
    }

    short vacationDays(
        const Date &SECOND_DATE
    ) {
        return vacationDays(
            *this,
            SECOND_DATE
        );
    }

    static Date dateAfterVacationDays(
        Date date,
        short vacationDays
    ) {
        while (vacationDays) {
            if (
                isWeekend(
                    dayOfWeek(
                        date.day,
                        date.month,
                        date.year
                    )
                )
            )
                vacationDays--;
            nextDay(
                date
            );
        }
        return date;
    }

    Date dateAfterVacationDays(
        const short &VACATION_DAYS
    ) {
        return dateAfterVacationDays(
            *this,
            VACATION_DAYS
        );
    }

    static short countDaysBetweenDates(
        Date startDate,
        Date endDate
    ) {
        short counter = 0;
        if (
            isAfter(
                startDate,
                endDate
            )
        )
            swapDates(
                startDate,
                endDate
            );
        while (
            isBefore(
                startDate,
                endDate
            ) || areDatesEqual(
                startDate,
                endDate
            )
        ) {
            counter++;
            nextDay(
                startDate
            );
        }
        return counter;
    }

    short countDaysBetweenDates(
        const Date &END_DATE
    ) {
        return countDaysBetweenDates(
            *this,
            END_DATE
        );
    }

    static bool dateIsValid(
        const Date &DATE
    ) {
        return isPositiveNumber(
                DATE.year
            ) &&
            isPositiveNumber(
                DATE.month
            ) &&
            DATE.month <= 12 &&
            isPositiveNumber(
                DATE.day &&
                DATE.day <= monthDays(
                    DATE.month,
                    DATE.year
                )
            );
    }

    void format_yyyy(
        const short &YEAR,
        string &result,
        size_t &position
    ) {
        while (
            (
                position = result.find(
                    "yyyy"
                )
            ) != string::npos
        )
            result.replace(
                position,
                4,
                to_string(
                    YEAR
                )
            );
    }

    void format_yy(
        const short &YEAR,
        string &result,
        size_t &position
    ) {
        while (
            (
                position = result.find(
                    "yy"
                )
            ) != string::npos
        )
            result.replace(
                position,
                2,
                to_string(
                    YEAR % 100
                )
                .insert(
                    0,
                    2 - to_string(
                        YEAR % 100
                    ).length(),
                    '0'
                )
            );
    }

    void format_mm(
        const short &MONTH,
        string &result,
        size_t &position
    ) {
        while (
            (
                position = result.find(
                    "mm"
                )
            ) != string::npos
        )
            result.replace(
                position,
                2,
                to_string(
                    MONTH
                )
                .insert(
                    0,
                    2 - to_string(
                        MONTH
                    ).length(),
                    '0'
                )
            );
    }

    void format_m(
        const short &MONTH,
        string &result,
        size_t &position
    ) {
        while (
            (
                position = result.find(
                    'm'
                )
            ) != string::npos
        )
            result.replace(
                position,
                1,
                to_string(
                    MONTH
                )
            );
    }

    void format_dd(
        const short &DAY,
        string &result,
        size_t &position
    ) {
        while (
            (
                position = result.find(
                    "dd"
                )
            ) != string::npos
        )
            result.replace(
                position,
                2,
                to_string(
                    DAY
                )
                .insert(
                    0,
                    2 - to_string(
                        DAY
                    ).length(),
                    '0'
                )
            );
    }

    void format_d(
        const short &DAY,
        string &result,
        size_t &position
    ) {
        while (
            (
                position = result.find(
                    'd'
                )
            ) != string::npos
        )
            result.replace(
                position,
                1,
                to_string(
                    DAY
                )
            );
    }

    void formatYear(
        const short &DATE,
        string &result,
        size_t &position
    ) {
        format_yyyy(
            DATE,
            result,
            position
        );

        format_yy(
            DATE,
            result,
            position
        );
    }

    void formatMonth(
        const short &MONTH,
        string &result,
        size_t &position
    ) {
        format_mm(
            MONTH,
            result,
            position
        );

        format_m(
            MONTH,
            result,
            position
        );
    }

    void formatDay(
        const short &DAY,
        string &result,
        size_t &position
    ) {
        format_dd(
            DAY,
            result,
            position
        );

        format_d(
            DAY,
            result,
            position
        );
    }

    string formatDate(
        const Date &DATE,
        const string &FORMAT
    ) {
        string result = FORMAT;

        size_t position;

        formatDay(
            DATE.day,
            result,
            position
        );

        formatMonth(
            DATE.month,
            result,
            position
        );

        formatYear(
            DATE.year,
            result,
            position
        );

        return result;
    }

    string getDateText() {
        return to_string(
                day
            ) + delimiter
            + to_string(
                month
            ) + delimiter
            + to_string(
                year
            );
    }

    void print() {
        cout << getDateText() << endl;
    }

    static void showMonthCalendar(
        const short &MONTH,
        const short &YEAR
    ) {
        short dayOfWeekIndex = dayOfWeek(
            1,
            MONTH,
            YEAR
        );
        const short MONTH_DAYS = monthDays(
            MONTH,
            YEAR
        );

        printf(
            "_______________________________%9s_______________________________\n",
            monthName(
                MONTH
            ).c_str()
        );

        for (short day = 1; day <= 7; ++day) {
            printf(
                "%10s",
                dayName(
                    day
                ).c_str()
            );
        }

        cout << endl;

        for (short index = 0; index < dayOfWeekIndex; index++)
            printf(
                "%10c",
                ' '
            );

        for (short day = 1; day <= MONTH_DAYS; day++) {
            printf(
                "%10d",
                day
            );
            if (++dayOfWeekIndex == 7) {
                dayOfWeekIndex = 0;
                printf(
                    "\n"
                );
            }
        }

        printf(
            "\n_______________________________________________________________________\n"
        );
    }

    void showMonthCalendar() {
        showMonthCalendar(
            month,
            year
        );
    }

    static void showYearCalendar(
        const short &YEAR
    ) {
        printf(
            "----------------------------------%4d---------------------------------\n",
            YEAR
        );

        for (short month = 1; month <= 12; ++month)
            showMonthCalendar(
                month,
                YEAR
            );
    }

    void showYearCalendar() {
        showYearCalendar(
            year
        );
    }

    static void printDateByDays(
        short days,
        short startYear,
        const string &SEPARATOR = DEFAULT_DELIMITER
    ) {
        while (days >= 365) {
            days -= isLeapYear(
                        startYear
                    )
                        ? 366
                        : 365;
            startYear++;
        }

        short month = 1;

        while (
            days >= monthDays(
                month,
                startYear
            )
        ) {
            days = static_cast<short>(
                days - monthDays(
                    month,
                    startYear
                )
            );
            month++;
        }

        Date(
            days,
            month,
            startYear,
            SEPARATOR
        ).print();
    }
};