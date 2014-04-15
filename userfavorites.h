#ifndef USERFAVORITES_H
#define USERFAVORITES_H

#include <QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>

class UserFavorites : public QObject
{
    Q_OBJECT
public:
    explicit UserFavorites(QObject *parent = 0);
    void init(QString initString);
    QString asString();
    QString asSqlSet();
    bool inFavorites(int id);

signals:
    
public slots:
    void add(int id);
    void remove(int id);

private:
    QStringList favorites;
    
};

#endif // USERFAVORITES_H
