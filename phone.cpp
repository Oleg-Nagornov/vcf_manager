#include "phone.h"

Phone::Phone()
{
    this->id = 0;
    this->type = Phone::NONE;
}

bool Phone::operator ==(const Phone &arg)
{
    QString firstNumber = this->reverse(this->number);
    QString secondNumber = this->reverse(arg.number);

    int minLength = firstNumber.length() < secondNumber.length() ? firstNumber.length() : secondNumber.length();

    for (int i = 0; i < minLength; i++)
    {
        if (firstNumber.at(i) != secondNumber.at(i))
        {
            if (i > 5)
            {
                return true;
            }

            return false;
        }
    }

    return true;
}

Phone::Type Phone::getPhoneType(const QString &type)
{
    if (type == "work") {
        return Phone::WORK;
    } else if (type == "home") {
        return Phone::HOME;
    } else if (type == "mobile") {
        return Phone::MOBILE;
    } else {
        return Phone::NONE;
    }
}

QString Phone::getPhoneTypeStr(const Phone::Type &type)
{
    if (type == Phone::WORK) {
        return "work";
    } else if (type == Phone::HOME) {
        return "home";
    } else if (type == Phone::MOBILE) {
        return "mobile";
    } else {
        return "none";
    }
}



QString Phone::reverse(const QString &str)
{
    QString result;

    for (int i = str.length() - 1; i >= 0; i--)
    {
        result.append(str.at(i));
    }

    return result;
}
