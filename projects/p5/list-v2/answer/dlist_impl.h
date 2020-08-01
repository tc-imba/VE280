//
// Created by liu on 16-7-19.
//

#ifndef VE280_DLIST_IMPL_H
#define VE280_DLIST_IMPL_H

#include "dlist.h"

template<class T>
bool Dlist<T>::isEmpty() const {
    return first == nullptr;
}

template<class T>
void Dlist<T>::insertFront(T *op) {
    auto newNode = new node;
    newNode->op = op;
    if (isEmpty()) {
        first = last = newNode->prev = newNode->next = newNode;
    } else {
        newNode->prev = last;
        newNode->next = first;
        first = first->prev = last->next = newNode;
    }
}

template<class T>
void Dlist<T>::insertBack(T *op) {
    auto newNode = new node;
    newNode->op = op;
    if (isEmpty()) {
        first = last = newNode->prev = newNode->next = newNode;
    } else {
        newNode->prev = last;
        newNode->next = first;
        last = first->prev = last->next = newNode;
    }
}

template<class T>
T *Dlist<T>::removeFront() {
    if (isEmpty()) {
        throw emptyList();
    }
    auto victim = first;
    auto op = victim->op;
    if (victim == victim->next) {
        first = last = nullptr;
    } else {
        first = victim->prev->next = victim->next;
        victim->next->prev = victim->prev;
    }
    delete victim;
    return op;
}

template<class T>
T *Dlist<T>::removeBack() {
    if (isEmpty()) {
        throw emptyList();
    }
    auto victim = last;
    auto op = victim->op;
    if (victim == victim->next) {
        first = last = nullptr;
    } else {
        victim->prev->next = victim->next;
        last = victim->next->prev = victim->prev;
    }
    delete victim;
    return op;
}

template<class T>
T * Dlist<T>::remove(bool (*cmp)(const T *, const T *), T *ref) {
    if (isEmpty()) {
        return nullptr;
    }
    if (cmp(first->op, ref)) {
        return removeFront();
    }
    if (cmp(last->op, ref)) {
        return removeBack();
    }
    auto temp = last->prev;
    while (temp != first) {
        if (cmp(temp->op, ref)) {
            auto op = temp->op;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
            return op;
        }
        temp = temp->prev;
    }
    return nullptr;
}

template<class T>
Dlist<T>::Dlist() {
    first = last = nullptr;
}

template<class T>
Dlist<T>::Dlist(const Dlist &l) {
    first = last = nullptr;
    copyAll(l);
}

template<class T>
Dlist<T> &Dlist<T>::operator=(const Dlist &l) {
    removeAll();
    copyAll(l);
    return *this;
}

template<class T>
Dlist<T>::~Dlist() {
    removeAll();
}

template<class T>
void Dlist<T>::removeAll() {
    if (!isEmpty()) {
        auto temp = first;
        while (temp != last) {
            temp = temp->next;
            delete temp->prev->op;
            delete temp->prev;
        }
        delete temp->op;
        delete temp;
    }
    first = last = nullptr;
}

template<class T>
void Dlist<T>::copyAll(const Dlist &l) {
    if (!l.isEmpty()) {
        auto temp = l.last;
        while (temp != l.first) {
            insertFront(new T(*temp->op));
            temp = temp->prev;
        }
        insertFront(new T(*temp->op));
    }
}

#endif //VE280_DLIST_IMPL_H
