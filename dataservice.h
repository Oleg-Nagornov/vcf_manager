#ifndef DATASERVICE_H
#define DATASERVICE_H

#include <QDebug>
#include <QtSql>

#include "contact.h"

class DataService
{
public:
    DataService();

    void save(Contact &contact);
    void remove(Contact &contact);

    QVector<Contact> getContacts();

    QSqlDatabase getDb();
private:
    QSqlDatabase db;
    void savePhones(Contact &contact);
    Contact loadContact(const int &id);
};

#endif // DATASERVICE_H
