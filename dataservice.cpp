#include "dataservice.h"

DataService::DataService()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.db3");
    if (!db.open())
    {
        qDebug() << "could not open db";
    }
}

void DataService::save(Contact &contact)
{
    QSqlQuery query;

    if (contact.id > 0)
    {
        query.prepare("UPDATE contact SET lastname = ?, name = ?, secondname = ?, work = ?, address = ?, email = ? WHERE id = ?");

        query.bindValue(0, contact.lastName);
        query.bindValue(1, contact.name);
        query.bindValue(2, contact.secondName);
        query.bindValue(3, contact.work);
        query.bindValue(4, contact.address);
        query.bindValue(5, contact.email);
        query.bindValue(6, contact.id);

        if (!query.exec())
        {
            qDebug() << query.lastError();
        }

        this->savePhones(contact);
    }
    else
    {
        query.prepare("INSERT INTO contacts (`lastname`, `name`, `secondname`, `work`, `address`, `email`) VALUES (?, ?, ?, ?, ?, ?);");

        query.bindValue(0, contact.lastName);
        query.bindValue(1, contact.name);
        query.bindValue(2, contact.secondName);
        query.bindValue(3, contact.work);
        query.bindValue(4, contact.address);
        query.bindValue(5, contact.email);

        if (!query.exec())
        {
            qDebug() << query.lastError();
        }

        contact.id = query.lastInsertId().toInt();

        this->savePhones(contact);
    }
}

void DataService::remove(Contact &contact)
{
    if (contact.id <= 0)
    {
        return;
    }

    QSqlQuery queryContact;
    queryContact.prepare("DELETE FROM contacts WHERE id = ?");

    queryContact.bindValue(0, contact.id);
    if (!queryContact.exec())
    {
        qDebug() << queryContact.lastError();
    }

    QSqlQuery queryPhones;
    queryPhones.prepare("DELETE FROM phones WHERE contact_id = ?");

    queryPhones.bindValue(0, contact.id);
    if (!queryPhones.exec())
    {
        qDebug() << queryPhones.lastError();
    }
}

QVector<Contact> DataService::getContacts()
{
    QVector<Contact> result;

    QSqlQuery query;

    query.prepare("SELECT id FROM contacts");

    query.exec();
    while (query.next())
    {
        result.append(this->loadContact(query.value(0).toInt()));
    }

    return result;
}

QSqlDatabase DataService::getDb()
{
    return this->db;
}

void DataService::savePhones(Contact &contact)
{
    for (int i = 0; i < contact.getPhones().length(); i++) {
        Phone phone = contact.getPhones().at(i);

        QSqlQuery query;

        if (phone.id > 0)
        {
            query.prepare("UPDATE phones SET number = ?, type = ? WHERE id = ?");

            query.bindValue(0, phone.number);
            query.bindValue(1, Phone::getPhoneTypeStr(phone.type));
            query.bindValue(2, phone.id);

            if (!query.exec())
            {
                qDebug() << query.lastError();
            }
        }
        else
        {
            query.prepare("INSERT INTO phones(contact_id, number, type) "
                          "VALUES (?, ?, ?);");
            query.bindValue(0, contact.id);
            query.bindValue(1, phone.number);
            query.bindValue(2, Phone::getPhoneTypeStr(phone.type));


            if (!query.exec())
            {
                qDebug() << query.lastError();
            }

            phone.id = query.lastInsertId().toInt();

            contact.getPhones()[i] = phone;
        }
    }
}

Contact DataService::loadContact(const int &id)
{
    Contact contact;

    QSqlQuery queryContact;

    queryContact.prepare("SELECT * FROM contacts WHERE id = ?");
    queryContact.bindValue(0, id);

    if (!queryContact.exec())
    {
        qDebug() << queryContact.lastError();
    }
    else if (queryContact.next())
    {
        contact.id = id;
        contact.lastName = queryContact.value(1).toString();
        contact.name = queryContact.value(2).toString();
        contact.secondName = queryContact.value(3).toString();
        contact.work = queryContact.value(4).toString();
        contact.address = queryContact.value(5).toString();
        contact.email = queryContact.value(6).toString();
    }

    QSqlQuery queryPhones;
    queryPhones.prepare("SELECT * FROM phones WHERE contact_id = ?");
    queryPhones.bindValue(0, id);

    if (!queryPhones.exec())
    {
        qDebug() << queryPhones.lastError();
        return contact;
    }
    while (queryPhones.next())
    {
        Phone phone;
        phone.id = queryPhones.value(0).toInt();
        phone.number = queryPhones.value(2).toString();
        phone.type = Phone::getPhoneType(queryPhones.value(3).toString());

        contact.addPhone(phone);
    }

    return contact;
}
