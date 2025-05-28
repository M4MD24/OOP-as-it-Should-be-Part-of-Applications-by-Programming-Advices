#pragma once

#include "Date.h"

using namespace std;

class Period {
    Date startDate,
         endDate;

public:
    Period(
        const Date &START_PERIOD,
        const Date &END_PERIOD
    ): startDate(
           START_PERIOD
       ),
       endDate(
           END_PERIOD
       ) {}

    void setStartDate(
        Date startDate
    ) {
        Date::setDate(
            this->startDate,
            startDate
        );
    }

    Date getStartDate() {
        return startDate;
    }

    void setEndDate(
        Date endDate
    ) {
        Date::setDate(
            this->endDate,
            endDate
        );
    }

    Date getEndDate() {
        return endDate;
    }

    static bool areOverlap(
        const Period &FIRST_DATE,
        const Period &SECOND_DATE
    ) {
        return !(
            Date::isBefore(
                SECOND_DATE.endDate,
                FIRST_DATE.startDate
            ) ||
            Date::isAfter(
                SECOND_DATE.startDate,
                FIRST_DATE.endDate
            )
        );
    }

    bool areOverlap(
        const Period &SECOND_DATE
    ) {
        return areOverlap(
            *this,
            SECOND_DATE
        );
    }

    static bool isDateInPeriod(
        const Period &PERIOD,
        const Date &DATE
    ) {
        return !(
            Date::isBefore(
                DATE,
                PERIOD.startDate
            ) ||
            Date::isAfter(
                DATE,
                PERIOD.startDate
            )
        );
    }

    bool isDateInPeriod(
        const Date &DATE
    ) {
        return isDateInPeriod(
            *this,
            DATE
        );
    }

    static short countOverlapDays(
        const Period &FIRST_PERIOD,
        const Period &SECOND_PERIOD
    ) {
        const Date OVERLAP_START = Date::isAfter(
                                       FIRST_PERIOD.startDate,
                                       SECOND_PERIOD.startDate
                                   )
                                       ? FIRST_PERIOD.startDate
                                       : SECOND_PERIOD.startDate,
                   OVERLAP_END = Date::isBefore(
                                     FIRST_PERIOD.endDate,
                                     SECOND_PERIOD.endDate
                                 )
                                     ? FIRST_PERIOD.endDate
                                     : SECOND_PERIOD.endDate;

        if (
            Date::isAfter(
                OVERLAP_START,
                OVERLAP_END
            )
        )
            return 0;

        return Date::countDaysBetweenDates(
            OVERLAP_START,
            OVERLAP_END
        );
    }

    short countOverlapDays(
        const Period &SECOND_PERIOD
    ) {
        return countOverlapDays(
            *this,
            SECOND_PERIOD
        );
    }
};