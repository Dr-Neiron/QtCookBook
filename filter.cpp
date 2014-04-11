#include "filter.h"

Filter::Filter()
{
    filterMap[ID_FILTER] = "";
    filterMap[SEASON_FILTER] = "";
    filterMap[TYPES_FILTER] = "";
    filterMap[CONTRY_FILTER] = "";
    filterMap[DURATION_FILTER] = "";
    filterMap[VEGETARIAN_FILTER] = "";
}

QString Filter::currentFilter()
{
    QString result = "1";
    if (!filterMap[ID_FILTER].isEmpty())
        result += " AND bluda.id IN " + filterMap[ID_FILTER];
    if (!filterMap[SEASON_FILTER].isEmpty())
        result += " AND bluda.season = " + filterMap[SEASON_FILTER];
    if (!filterMap[TYPES_FILTER].isEmpty())
        result += " AND bluda.type = " + filterMap[TYPES_FILTER];
    if (!filterMap[CONTRY_FILTER].isEmpty())
        result += " AND bluda.contry = " + filterMap[CONTRY_FILTER];
    if (!filterMap[DURATION_FILTER].isEmpty())
        result += " AND bluda.duration <= " + filterMap[DURATION_FILTER];
    if (!filterMap[VEGETARIAN_FILTER].isEmpty())
        result += " AND bluda.is_vegetarian = " + filterMap[VEGETARIAN_FILTER];
    return result;
}

void Filter::applyNew(filters_t filter, QString filteredValue)
{
    filterMap[filter] = filteredValue;
}

void Filter::resetFilter(filters_t filter)
{
    filterMap[filter] = "";
}
