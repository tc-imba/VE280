//
// Created by liu on 27/7/2020.
//

#ifndef VE280_DLIST_IMPL_H
#define VE280_DLIST_IMPL_H

#include "dlist.h"

template<class T>
bool Dlist<T>::isEmpty() const {
    return first == nullptr;
}

template<class T>
void Dlist<T>::insert(T *op, bool front) {
    auto newNode = std::make_unique<node>();
    newNode->op = std::unique_ptr<T>(op);
    if (isEmpty()) {
        first = last = newNode->prev = newNode.get();
        newNode->next = std::move(newNode);
    } else {
        first->prev = newNode.get();
        newNode->prev = last;
        newNode->next = std::move(last->next);
        last->next = std::move(newNode);
        if (front) {
            first = first->prev;
        } else {
            last = last->next.get();
        }
    }
}

template<class T>
void Dlist<T>::insertFront(T *op) {
    insert(op, true);
}

template<class T>
void Dlist<T>::insertBack(T *op) {
    insert(op, false);
}

template<class T>
T *Dlist<T>::remove(std::unique_ptr<node> victim) {
    if (first->prev == first) {
        first = last = nullptr;
    } else {
        victim->next->prev = victim->prev;
        victim->prev->next = std::move(victim->next);
    }
    return victim->op.release();
}

template<class T>
T *Dlist<T>::removeFront() {
    if (isEmpty()) {
        throw emptyList();
    }
    auto newFirst = first->next.get();
    auto op = remove(std::move(last->next));
    if (first) first = newFirst;
    return op;
}

template<class T>
T *Dlist<T>::removeBack() {
    if (isEmpty()) {
        throw emptyList();
    }
    last = last->prev;
    return remove(std::move(last->next));
}

template<class T>
T *Dlist<T>::remove(bool (*cmp)(const T *, const T *), T *ref) {
    if (isEmpty()) {
        return nullptr;
    }
    if (cmp(first->op.get(), ref)) {
        return removeFront();
    }
    if (cmp(last->op.get(), ref)) {
        return removeBack();
    }
    auto temp = last->prev;
    while (temp != first) {
        if (cmp(temp->op.get(), ref)) {
            return remove(std::move(temp->prev->next));
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
        // reset the owner of the first node
        auto temp = std::move(last->next);
        // clear nodes reversely one by one to prevent stack overflow
        while (first->next) {
            last = last->prev;
            last->next = nullptr;
        }
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
