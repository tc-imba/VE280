#ifndef __DLIST_H__
#define __DLIST_H__

class emptyList {
    // OVERVIEW: an exception class
};

template <class T>
class Dlist {
    // OVERVIEW: contains a double-ended list of Objects

   public:
    // Operational methods

    bool isEmpty() const;
    // EFFECTS: returns true if list is empty, false otherwise

    void insertFront(T *op);
    // MODIFIES this
    // EFFECTS inserts o at the front of the list

    void insertBack(T *op);
    // MODIFIES this
    // EFFECTS inserts o at the back of the list

    T *removeFront();
    // MODIFIES this
    // EFFECTS removes and returns first object from non-empty list
    //         throws an instance of emptyList if empty

    T *removeBack();
    // MODIFIES this
    // EFFECTS removes and returns last object from non-empty list
    //         throws an instance of emptyList if empty

    T *remove(bool (*cmp)(const T*, const T*), T* ref);
    // MODIFIES this
    // REQUIRES there is only one or zero node in the list satisfying cmp(op, ref) == true
    // EFFECTS traverses through the whole list
    //         if `op` in a node satisfies cmp(op, ref) == true,
    //         removes and returns this object from the list
    //         returns NULL pointer if no such node exists

    // Maintenance methods
    Dlist();                           // constructor
    Dlist(const Dlist &l);             // copy constructor
    Dlist &operator=(const Dlist &l);  // assignment operator
    ~Dlist();                          // destructor

   private:
    // A private type
    struct node {
        node *next;
        node *prev;
        T *op;
    };

    node *first;  // The pointer to the first node (NULL if none)
    node *last;   // The pointer to the last node (NULL if none)

    // Utility methods

    void removeAll();
    // EFFECT: called by destructor/operator= to remove and destroy
    //         all list elements

    void copyAll(const Dlist &l);
    // EFFECT: called by copy constructor/operator= to copy elements
    //         from a source instance l to this instance
};

/*
Note: as we have shown in the lecture, for template, we also need
to include the method implementation in the .h file. For this
purpose, we include dlist_impl.h below. Please provide the method
implementation in this file.
*/

#include "dlist_impl.h"

#endif /* __DLIST_H__ */
