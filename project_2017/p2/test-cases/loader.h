//
// Created by tripack on 2017/6/8.
//

#ifndef PROJ2_LOADER_H
#define PROJ2_LOADER_H

#include <iostream>

std::istream& operator>>(std::istream& stream, list_t& list);
std::ostream& operator<<(std::ostream& stream, const tree_t& tree);
std::istream& operator>>(std::istream& stream, tree_t& tree);
std::ostream& operator<<(std::ostream& stream, const list_t& list);

#endif //PROJ2_LOADER_H
