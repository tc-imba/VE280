#include <sstream>
#include "exceptions.h"

using namespace std;

SquareException::SquareException(const Square &_sq, const string &_m): 
   m(_sq.toString() + " is " + _m + "."){
}

const char * SquareException::what() const noexcept{
   return m.c_str();
}

UsedPieceException::UsedPieceException(const Piece &_p): m(_p.toString() + " is already used."){
}

const char * UsedPieceException::what() const noexcept{
   return m.c_str();
}

InvalidInputException::InvalidInputException(const string &_m): m(_m + " is an invalid input."){
}

const char * InvalidInputException::what() const noexcept{
   return m.c_str();
}
