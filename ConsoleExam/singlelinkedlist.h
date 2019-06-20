#ifndef SINGLELINKEDLIST_H
#define SINGLELINKEDLIST_H

#include "base.h"

#include <iostream>

using namespace std;

template <class T, class K>
struct Node
{
    Node(const Data<T,K> &d)
        :data(d){}
    Node* next = nullptr;
    Data<T, K> data;
};

template <class T, class K>
class SingleLinkedList :public Base<T, K>
{
public:
    SingleLinkedList() = default;

    void addValue(const Data<T, K>& data) override;

    T getValue(const K& key) override;

    void changeValue(const K& key, const T& data) override;

    void deleteValue(const K& key) override;

    QVector<T> getAllValues() override;

    QVector<K> getAllKeys() override;

    QVector<Data<T,K>> getAllPairs() override;
private:


    Node<T, K> *begin = nullptr;
    Node<T, K> *tail = nullptr;


    Node<T, K>* search(const K& key);
    Node<T, K>* searchPrev(const K& key);
};


template <class T, class K>
void SingleLinkedList<T, K>::addValue(const Data<T, K>& data)
{
    if(search(data.getKey()))
    {
        return;
    }
    //cout << "Begin add" << endl;

    //cout << "Key " << data.getKey() << endl;
    Node<T, K> *p = new Node<T, K>(data);
    p->next = begin;
    begin = p;

    //cout << "End add" << endl;
}

template <class T, class K>
Node<T, K>* SingleLinkedList<T, K>::search(const K& key)
{
    Node<T, K> *p = begin;

    while(p)
    {
        if(p->data.getKey() == key)
        {
            return  p;
        }
        p = p->next;
    }

    return nullptr;
}


template <class T, class K>
Node<T, K>* SingleLinkedList<T, K>::searchPrev(const K& key)
{
    if(!begin || begin->data.getKey() == key)
    {
        return nullptr;
    }

    Node<T, K> *prev = begin;

    while(prev->next)
    {
        if(prev->next->data.getKey() == key)
        {
            return  prev;
        }
        prev = prev->next;
    }

    return nullptr;
}

template <class T, class K>
T SingleLinkedList<T, K>::getValue(const K& key)
{
    Node<T, K> *p = search(key);

    if(!p)
    {
        throw("No such data");
    }
    return p->data.getData();
}

template <class T, class K>
void SingleLinkedList<T, K>::changeValue(const K& key, const T& data)
{
    Node<T, K> *p = search(key);

    if(!p) return;

    p->data.setData(data);
}


template <class T, class K>
void SingleLinkedList<T, K>::deleteValue(const K& key)
{
    Node<T, K> *p = search(key);
    if(!p || !begin) return;
    Node<T, K> *prev = searchPrev(key);

    if(!prev)
    {
        Node<T, K> *t = begin->next;
        begin = t;
        return;
    }

    prev->next = p->next;
    p->next = nullptr;
}

template <class T, class K>
QVector<T> SingleLinkedList<T, K>::getAllValues()
{
    QVector<T> result;
    Node<T, K> *p = begin;
    while(p)
    {
        result.push_back(p->data.getData());
        p = p->next;
    }
    return  result;
}

template <class T, class K>
QVector<K> SingleLinkedList<T, K>::getAllKeys()
{
    QVector<K> result;
    Node<T, K> *p = begin;
    while(p)
    {
        result.push_back(p->data.getKey());
        p = p->next;
    }
    return  result;
}

template <class T, class K>
QVector<Data<T,K>> SingleLinkedList<T, K>::getAllPairs()
{
    QVector<Data<T,K>> result;
    Node<T, K> *p = begin;
    while(p)
    {
        result.push_back(p->data);
        p = p->next;
    }
    return  result;
}


#endif // SINGLELINKEDLIST_H
