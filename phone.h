#ifndef PHONE_H
#define PHONE_H

#include <QString>

class Phone
{
public:

    enum Type {WORK, HOME, MOBILE, NONE};

    Phone();

    bool operator ==(const Phone &arg);

    Type type;
    QString number;
    int id;

    static Type getPhoneType(const QString &type);
    static QString getPhoneTypeStr(const Type &type);

private:
    QString reverse(const QString &str);
};

#endif // PHONE_H
