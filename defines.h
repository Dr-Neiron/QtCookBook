#ifndef DEFINES_H
#define DEFINES_H

namespace Defines
{
    enum roles_t
    {
        ADMINISTRATOR_ROLE  = 1,
        USER_ROLE           = 2
    };

    enum filters_t
    {
        ID_FILTER = 0,
        DURATION_FILTER = 4,
        SEASON_FILTER = 5,
        TYPES_FILTER = 6,
        CONTRY_FILTER = 7,
        VEGETARIAN_FILTER = 9
    };

}

#endif // DEFINES_H
