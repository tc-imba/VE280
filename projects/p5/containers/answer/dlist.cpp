//
// Created by liu on 16-7-19.
//
#pragma once

#include "dlist.h"
#include <cstdlib>

template<class T>
bool Dlist<T>::isEmpty()
{
    return this->first == NULL;
}

template<class T>
void Dlist<T>::insertFront(T *op)
{
    auto newNode = new node;
    newNode->op = op;
    if (this->isEmpty())
    {
        newNode->prev = newNode->next = newNode;
    }
    else
    {
        newNode->prev = this->last;
        newNode->next = this->first;
    }
    this->first = newNode;
}

template<class T>
void Dlist<T>::insertBack(T *op)
{
    auto newNode = new node;
    newNode->op = op;
    if (this->isEmpty())
    {
        newNode->prev = newNode->next = newNode;
    }
    else
    {
        newNode->prev = this->last;
        newNode->next = this->first;
    }
    this->last = newNode;
}

template<class T>
T *Dlist<T>::removeFront()
{
    if (this->isEmpty())
    {
        throw emptyList();
    }
    auto oldNode = this->first;
    auto op = oldNode->op;
    if (oldNode == oldNode->next)
    {
        this->first = this->last = NULL;
    }
    else
    {
        this->first = oldNode->prev->next = oldNode->next;
        oldNode->next->prev = oldNode->prev;
    }
    delete oldNode;
    return op;
}

template<class T>
T *Dlist<T>::removeBack()
{
    if (this->isEmpty())
    {
        throw emptyList();
    }
    auto oldNode = this->last;
    auto op = oldNode->op;
    if (oldNode == oldNode->next)
    {
        this->first = this->last = NULL;
    }
    else
    {
        oldNode->prev->next = oldNode->next;
        this->last = oldNode->next->prev = oldNode->prev;
    }
    delete oldNode;
    return op;
}

template<class T>
Dlist<T>::Dlist()
{
    this->first = this->last = NULL;
}

template<class T>
Dlist<T>::Dlist(const Dlist &l)
{
    this->removeAll();
    this->copyAll(l);
}

template<class T>
Dlist<T> &Dlist<T>::operator=(const Dlist &l)
{
    this->removeAll();
    this->copyAll(l);
    return *this;
}

template<class T>
Dlist<T>::~Dlist()
{
    this->removeAll();
}

template<class T>
void Dlist<T>::removeAll()
{
    if (!this->isEmpty())
    {
        auto temp = this->first;
        while (temp != temp->next)
        {
            temp = temp->next;
            delete temp->prev->op;
            delete temp->prev;
        }
        delete temp->op;
        delete temp;
    }
    this->first = this->last = NULL;
}

template<class T>
void Dlist<T>::copyAll(const Dlist &l)
{
    if (l.last != NULL)
    {
        auto temp = l.last;
        while (temp != temp->prev)
        {
            this->insertFront(new T(*temp->op));
            temp = temp->prev;
        }
        this->insertFront(temp->op);
    }
}
