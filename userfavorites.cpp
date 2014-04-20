#include "userfavorites.h"
#include <QDebug>

UserFavorites::UserFavorites(QObject *parent) :
    QObject(parent)
{
}

void UserFavorites::init(QString initString)
{
    if (!initString.isEmpty())
        favorites = initString.split(",");
}

QString UserFavorites::asString()
{
    if (favorites.isEmpty())
        return QString("");
    return favorites.join(",");
}

QString UserFavorites::asSqlSet()
{
    QString result;

    result.append("(");
    result.append(favorites.join(","));
    result.append(")");
    return result;
}

bool UserFavorites::inFavorites(int id)
{
    QString fav = QString::number(id);
    if (favorites.contains(fav))
        return true;
    return false;
}

void UserFavorites::add(int id)
{
    QString fav = QString::number(id);
    if ((!favorites.contains(fav)) && (fav != 0))
        favorites.append(fav);
}

void UserFavorites::remove(int id)
{
    QString fav = QString::number(id);
    favorites.removeOne(fav);
}
