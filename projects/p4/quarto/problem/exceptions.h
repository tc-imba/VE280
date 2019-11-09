#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>
#include "pool.h"
#include "square.h"

class Square; // Just to tell the compiler that this class exists

class SquareException: public std::exception{
   const std::string m;

public:
   SquareException(const Square &_sq, const std::string &_m);
   virtual const char * what() const noexcept;
};

class UsedPieceException: public std::exception{
   const std::string m;

public:
   UsedPieceException(const Piece &_p);
   virtual const char * what() const noexcept;
};

class InvalidInputException: public std::exception{
   const std::string m;

public:
   InvalidInputException(const std::string &_s);
   virtual const char * what() const noexcept;
};
#endif
