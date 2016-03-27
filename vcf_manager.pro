#-------------------------------------------------
#
# Project created by QtCreator 2016-03-13T00:19:59
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vcf_manager
TEMPLATE = app


SOURCES += main.cpp\
        vcfmanager.cpp \
    dataservice.cpp \
    contact.cpp \
    phone.cpp \
    parser.cpp

HEADERS  += vcfmanager.h \
    dataservice.h \
    contact.h \
    phone.h \
    parser.h

FORMS    += vcfmanager.ui
