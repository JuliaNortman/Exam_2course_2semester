#ifndef BASE_H
#define BASE_H

#include <QVector>
#include <QDateTime>

class DateTime
{
public:
    DateTime() = default;

    DateTime(const QDateTime& input)
        :dateTime(input){}
private:
    QDateTime dateTime;
};

/**
 * @brief The Data class stores the pair data-key
 */
template <class T, class K>
class Data
{
public:
    Data() = default;

    Data(const T& d, const K& k)
        :data(d), key(k){}
    T getData() const {return data;}
    K getKey() const {return  key;}
    void setData(const T& data){this->data = data;}
private:
    T data;
    K key;
};

template <class T, class K>
class Base
{
public:
    Base() = default;

    virtual T getValue(const K& key) = 0;

    virtual void changeValue(const K& key, const T& data) = 0;

    virtual void addValue(const Data<T, K>& data) = 0;

    virtual void deleteValue(const K& key) = 0;

    virtual QVector<T> getAllValues() = 0;

    virtual QVector<K> getAllKeys() = 0;

    virtual QVector<Data<T,K>> getAllPairs() = 0;
};

#endif // BASE_H
