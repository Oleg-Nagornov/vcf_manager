#ifndef CONTACT_H
#define CONTACT_H

#include <QVector>

#include "phone.h"

class Contact
{
public:
    Contact();

    void addPhone(Phone phone);
    QVector<Phone> &getPhones();

    QString getFullName();


    QString name;
    QString lastName;
    QString secondName;

    QString address;
    QString work;
    QString email;
    int id;

private:
    QVector<Phone> phones;


};

#endif // CONTACT_H
