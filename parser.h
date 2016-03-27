#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QVector>
#include <QFile>
#include <QDebug>
#include "contact.h"

class Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = 0);

    QVector<Contact> parseFile(const QString &filename);

signals:

public slots:

private:
    QVector<Contact> contacts;
    Contact currentContact;

    void parseLine(const QByteArray &line);
    QByteArray decode(const QByteArray &input);
};

#endif // PARSER_H
