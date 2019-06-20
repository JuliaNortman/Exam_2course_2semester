#pragma once

#include <QtTest>

// add necessary includes here

#include "linearhash.h"


class HashTest : public QObject
{
    Q_OBJECT

public:
    HashTest();
    ~HashTest();



private slots:
    void addTest();

    void getValueTest();

    void deleteValueTest();

};

