#include "contact.h"

Contact::Contact()
{
    this->id = 0;
}

void Contact::addPhone(Phone phone)
{
    for (int i = 0; i < this->phones.length(); i++)
    {
        if (phone == this->phones.at(i)) {
            return;
        }
    }

    this->phones.append(phone);

}

QVector<Phone> &Contact::getPhones()
{
    return this->phones;
}

QString Contact::getFullName()
{
    return this->lastName  + (this->lastName.length() > 0 ? " " : "") + this->name + (this->name.length() > 0 ? " " : "") + this->secondName;
}
