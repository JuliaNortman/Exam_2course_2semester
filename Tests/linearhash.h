#pragma once

#include "base.h"
#include "tst_hashtest.h"
#include <QVector>
#include <iostream>

#include <QDateTime>
#include <QDate>
#include <QTime>

using namespace std;

class HashTest;

template<class T, class K>
class LinearHash :public Base<T, K>
{
public:

    friend class HashTest;

    //LinearHash() = default;
    LinearHash(int size, int (*pFunc)(const K& key)) :m(size), keyToInt(pFunc)
    {
        table.resize(m);
        dataStore.resize(m);
        for(int i = 0; i < m; ++i)
        {
            table[i] = -1;
        }
    }

    void addValue(const Data<T, K>& data) override;

    T getValue(const K& key) override;

    void changeValue(const K& key, const T& data) override;

    void deleteValue(const K& key) override;

    QVector<T> getAllValues() override;

    QVector<K> getAllKeys() override;

    QVector<Data<T,K>> getAllPairs() override;



    /*void print()
    {
        cout << "All values: ";
        for(int i = 0; i < m; ++i)
        {
            if(table[i] >= 0)
            {
                cout << dataStore[i].getKey().hour() << endl;
            }
        }
    }*/
private:

    const int m = 15;
    QVector<Data<T,K>> dataStore;
    QVector<int> table;

    int (*keyToInt)(const K& key);

    int h(int k)
    {
        return k%(m-2);
    }

    int hash(int k, int i)
    {
        return (h(k)+i)%m;
    }

    int search(const K& key)
    {
        int k = keyToInt(key);
        for(int i = 0; i < m; ++i)
        {
            int cell = hash(k, i);
            if(table[cell] == -1)
            {
                return -1;
            }
            if(dataStore[cell].getKey() == key)
            {
                return cell;
            }
        }
        return -1;
    }
};

template <class T, class K>
void LinearHash<T,K>::addValue(const Data<T, K>& data)
{
    int key = keyToInt(data.getKey());
    for(int i = 0; i < m; ++i)
    {
        int cell = hash(key, i);
        if(table[cell] == -1)
        {
            dataStore[cell] = data;
            table[cell] = cell;
            return;
        }
    }
}

template <class T, class K>
T LinearHash<T,K>::getValue(const K& key)
{
    int cell = search(key);
    if(cell == -1)
    {
        throw("No such data");
    }
    return dataStore[cell].getData();
}

template <class T, class K>
void LinearHash<T,K>::changeValue(const K& key, const T& data)
{
    int cell = search(key);
    if(cell == -1)
    {
        return;
    }
    dataStore[cell].setData(data);
}

template <class T, class K>
void LinearHash<T,K>::deleteValue(const K& key)
{
    int cell = search(key);
    if(cell == -1)
    {
        return;
    }
    table[cell] = -1;
}

template <class T, class K>
QVector<T> LinearHash<T,K>::getAllValues()
{
    QVector<T> result;
    for(int i = 0; i < m; ++i)
    {
        if(table[i] >= 0)
        {
            result.push_back(dataStore[i].getData());
        }
    }
    return result;
}

template<class T, class K>
QVector<K> LinearHash<T,K>::getAllKeys()
{
    QVector<K> result;
    for(int i = 0; i < m; ++i)
    {
        if(table[i] >= 0)
        {
            result.push_back(dataStore[i].getKey());
        }
    }
    return result;
}

template<class T, class K>
QVector<Data<T,K>> LinearHash<T,K>::getAllPairs()
{
    QVector<Data<T,K>> result;
    for(int i = 0; i < m; ++i)
    {
        if(table[i]>=0)
        {
            Data<T,K> d(dataStore[i].getData(), dataStore[i].getKey());
            result.push_back(d);
        }
    }
    return result;
}

