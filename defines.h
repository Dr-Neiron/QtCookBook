#ifndef DEFINES_H
#define DEFINES_H

#include <QString>
#include <QPixmap>

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

    typedef struct
    {
        int     id;
        QString name;
        QString consist;
        QString description;
        QPixmap pixmap;
        bool    isVegetarian;
    } dish_t;

    enum dish_table_colomns_t
    {
        DISH_TABLE_COLOMN_ID            = 0,
        DISH_TABLE_COLOMN_NAME          = 1,
        DISH_TABLE_COLOMN_CONSIST       = 2,
        DISH_TABLE_COLOMN_DISCRIPTION   = 3,
        DISH_TABLE_COLOMN_DURATION      = 4,
        DISH_TABLE_COLOMN_SEASON        = 5,
        DISH_TABLE_COLOMN_TYPE          = 6,
        DISH_TABLE_COLOMN_CONTRY        = 7,
        DISH_TABLE_COLOMN_PHOTO         = 8,
        DISH_TABLE_COLOMN_VEGETARIAN    = 9
    };

}

#endif // DEFINES_H
