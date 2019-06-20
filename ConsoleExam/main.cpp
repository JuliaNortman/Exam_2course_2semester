#include <QCoreApplication>

#include "singlelinkedlist.h"
#include "linearhash.h"
#include <QDateTime>

#include <iostream>

using namespace std;

int func(const QTime &t)
{
    return t.hour()*3600+t.minute()*60+t.second();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout << "*********************HASH**************************" << endl;

    QDateTime d1(QDate(2000,3,1), QTime(5, 48));
    QDateTime d2(QDate(1999,3,1), QTime(6, 48));
    QDateTime d3(QDate(1998,3,1), QTime(7, 48));
    QDateTime d4(QDate(1997,3,1), QTime(8, 48));
    QDateTime d5(QDate(1996,3,1), QTime(9, 48));
    QDateTime d6(QDate(1995,3,1), QTime(10, 48));
    QDateTime d7(QDate(1994,3,1), QTime(11, 48));
    QDateTime d8(QDate(1993,3,1), QTime(12, 48));
    QDateTime d9(QDate(1992,3,1), QTime(13, 48));
    QDateTime d10(QDate(1991,3,1), QTime(14, 48));

    QVector<QDateTime> vect;
    vect.push_back(d1);
    vect.push_back(d2);
    vect.push_back(d3);
    vect.push_back(d4);
    vect.push_back(d5);
    vect.push_back(d6);
    vect.push_back(d7);
    vect.push_back(d8);
    vect.push_back(d9);
    vect.push_back(d10);

    //SingleLinkedList<QDateTime, QTime> list;
    LinearHash<QDateTime, QTime> hash(13, func);


    for(int i = 0; i < 10; ++i)
    {
        Data<QDateTime, QTime> d(vect[i], vect[i].time());
        hash.addValue(d);
    }
    try
    {
        cout << "Get value: " << hash.getValue(d1.time()).date().year() << endl;
    }
    catch(...)
    {
        cout << "No such a data" << endl;
    }

    hash.changeValue(d5.time(), d4);
    hash.deleteValue(d5.time());
    QVector<QDateTime> keys = hash.getAllValues();
    for(int i = 0; i < keys.size(); ++i)
    {
        cout << "Key" << keys[i].date().year() << endl;
    }


    cout << "************************LIST**********************" << endl;

    SingleLinkedList<QDateTime, QTime> list;


    for(int i = 0; i < 10; ++i)
    {
        Data<QDateTime, QTime> d(vect[i], vect[i].time());
        list.addValue(d);
    }
    try
    {
        cout << "Get value: " << list.getValue(d1.time()).date().year() << endl;
    }
    catch(...)
    {
        cout << "No such a data" << endl;
    }

    list.changeValue(d5.time(), d4);
    list.deleteValue(d5.time());
    keys = list.getAllValues();
    for(int i = 0; i < keys.size(); ++i)
    {
        cout << "Key" << keys[i].date().year() << endl;
    }
    system("pause");
    return a.exec();
}
