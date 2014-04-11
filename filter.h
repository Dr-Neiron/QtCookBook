#ifndef FILTER_H
#define FILTER_H
#include <QtCore/QString>
#include <QMap>
#include "defines.h"

using namespace Defines;

class Filter
{
public:
    Filter();
    QString currentFilter();
    void applyNew(filters_t filter, QString filteredValue);
    void resetFilter(filters_t filter);

private:
    QMap<filters_t, QString> filterMap;
};

#endif // FILTER_H
