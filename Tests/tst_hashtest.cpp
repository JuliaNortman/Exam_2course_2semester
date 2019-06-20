#include "tst_hashtest.h"

HashTest::HashTest()
{

}

HashTest::~HashTest()
{

}

void HashTest::addTest()
{
    LinearHash<QDateTime, QTime> hash(13, [](const QTime& t)->int
        {return t.hour()*3600+t.minute()*60+t.second();});

    QDateTime d1(QDate(2000,3,1), QTime(5, 48));
    QDateTime d2(QDate(1999,3,1), QTime(6, 54));
    //QDateTime d3(QDate(1998,3,1), QTime(7, 48));

    Data<QDateTime, QTime> data1(d1, d1.time());
    Data<QDateTime, QTime> data2(d2, d2.time());
    //Data<QDateTime, QTime> data3(d3, d3.time());

    hash.addValue(data1);
    QVERIFY(hash.table[2] == 2);
    QVERIFY(hash.dataStore[2].getData() == QDateTime(QDate(2000,3,1), QTime(5, 48)));

    //collision
    hash.addValue(data2);
    QVERIFY(hash.table[3] == 3);
    QVERIFY(hash.dataStore[3].getData() == QDateTime(QDate(1999,3,1), QTime(6, 54)));

    hash.addValue(data1);
    QVERIFY(hash.table[2] == 2);
    QVERIFY(hash.dataStore[2].getData() == QDateTime(QDate(2000,3,1), QTime(5, 48)));
}

void HashTest::getValueTest()
{
    LinearHash<QDateTime, QTime> hash(13, [](const QTime& t)->int
        {return t.hour()*3600+t.minute()*60+t.second();});

    QDateTime d1(QDate(2000,3,1), QTime(5, 48));
    QDateTime d2(QDate(1999,3,1), QTime(6, 54));
    //QDateTime d3(QDate(1998,3,1), QTime(7, 48));

    Data<QDateTime, QTime> data1(d1, d1.time());
    Data<QDateTime, QTime> data2(d2, d2.time());
    //Data<QDateTime, QTime> data3(d3, d3.time());
    hash.dataStore.resize(13);
    hash.table.resize(13);
    hash.dataStore[0].setData(d1);
    hash.dataStore[0].setKey(QTime(5, 48));
    hash.table[0] = 0;
    QVERIFY_EXCEPTION_THROWN(hash.getValue(d1.time()) == d1, char *);
}

void HashTest::deleteValueTest()
{
    LinearHash<QDateTime, QTime> hash(13, [](const QTime& t)->int
        {return t.hour()*3600+t.minute()*60+t.second();});

    QDateTime d1(QDate(2000,3,1), QTime(5, 48));
    QDateTime d2(QDate(1999,3,1), QTime(6, 54));
    //QDateTime d3(QDate(1998,3,1), QTime(7, 48));

    Data<QDateTime, QTime> data1(d1, d1.time());
    Data<QDateTime, QTime> data2(d2, d2.time());
    //Data<QDateTime, QTime> data3(d3, d3.time());

    hash.addValue(data1);
    hash.addValue(data2);
    hash.deleteValue(QTime(5, 48));

    QVERIFY(hash.table[0] == -1);
}

QTEST_APPLESS_MAIN(HashTest)

//#include "tst_hashtest.moc"
