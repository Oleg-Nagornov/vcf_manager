#include "parser.h"

Parser::Parser(QObject *parent) : QObject(parent)
{
}

void Parser::parseLine(const QByteArray &line)
{
    QString src(line);
    QString str(line);
    str = str.trimmed();
    src = src.trimmed();

    QString search = "CHARSET=UTF-8;ENCODING=QUOTED-PRINTABLE:";

    QString parsed;
    if (str.contains(search))
    {
        int start = str.indexOf(search);
        str = str.mid(start + search.length());
        str = str.trimmed();

        parsed = QString::fromUtf8(this->decode(str.toUtf8()));
    } else {
        parsed = str.mid(str.indexOf(":") + 1);
    }
    parsed = parsed.trimmed();

    if (src.startsWith("BEGIN:VCARD"))
    {
        this->currentContact = Contact();
    }
    else if (src.startsWith("END:VCARD"))
    {
        this->contacts.append(this->currentContact);
    }
    else if (src.startsWith("N;"))
    {
        QStringList data = parsed.split(";", QString::SkipEmptyParts);
        if (data.size() >= 2)
        {
            this->currentContact.lastName = data[0];
            this->currentContact.name = data[1];
        }
        if (data.size() >= 3)
        {
            this->currentContact.secondName = data[2];
        }

    }
    else if (src.startsWith("TEL;"))
    {
        Phone phone;
        phone.number = parsed;
        phone.type = Phone::NONE;

        this->currentContact.addPhone(phone);
    }
    else if (src.startsWith("ORG;"))
    {
        this->currentContact.work = parsed;
    }
    else if (src.startsWith("EMAIL"))
    {
        this->currentContact.email = parsed;
    }
}

QVector<Contact> Parser::parseFile(const QString &filename)
{
    QFile *file = new QFile(filename);

    if (!file->open(QFile::ReadOnly))
    {
        return this->contacts;
    }

    while (!file->atEnd())
    {
        QByteArray line = file->readLine();

        this->parseLine(line);
    }

    file->close();
    delete file;

    return this->contacts;
}

QByteArray Parser::decode(const QByteArray &input)
{
    //                              0  1  2  3  4  5  6  7  8  9  :  ;  <  =  >  ?  @  A   B   C   D   E   F
    const unsigned char hexVal[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0, 0, 10, 11, 12, 13, 14, 15};

    QByteArray output;
    output.reserve(input.size());

    int len = input.size();
    for (int i = 0; i < len; ++i)
    {
        if (input[i] == '=' && i + 2 < len)
        {
            unsigned i1 = input[++i] - '0';
            unsigned i2 = input[++i] - '0';
            if (i1 < sizeof(hexVal) / sizeof(hexVal[0]) &&
                    i2 < sizeof(hexVal) / sizeof(hexVal[0]))
            {
                unsigned char c = (hexVal[i1] << 4) + hexVal[i2];
                output.append(c);
            }
        }
        else
        {
            output.append(input[i]);
        }
    }

    return output;
}
