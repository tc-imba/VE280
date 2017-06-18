//
// Created by liu on 17-6-8.
//

#pragma once
using namespace std;

#include <gtest/gtest.h>
#include <vector>
#include <list>

#include "recursive.h"
#include "p2.h"

list_t listEmpty, listOne, listTwo, listMore, listLong;

static list_t list_make(const list<int> &l, list<int>::const_iterator it)
{
    if (it == l.end()) return list_make();
    return list_make(*it, list_make(l, ++it));
}

static list_t list_make(const list<int> &l)
{
    return list_make(l, l.cbegin());
}

static void init_lists_simple()
{
    listEmpty = list_make();
    listOne = list_make(std::list<int>{1});
    listTwo = list_make(std::list<int>{3, 2});
    listMore = list_make(std::list<int>{1, 3, 5, 7, 9});
    listLong = list_make(std::list<int>{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9});
}

TEST(List, Size)
{
    init_lists_simple();
    EXPECT_EQ(0, size(listEmpty));
    EXPECT_EQ(1, size(listOne));
    EXPECT_EQ(2, size(listTwo));
    EXPECT_EQ(5, size(listMore));
    EXPECT_EQ(13, size(listLong));
}

TEST(List, MemberOf)
{

}