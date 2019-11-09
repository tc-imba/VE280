#ifndef SQUARE_H
#define SQUARE_H

#include "piece.h"
#include "exceptions.h"

class Square{
   // OVERVIEW: a square of Quarto 4x4 board
   Vaxis v;
   Haxis h;
   const Piece *p;

public:
   Square(Vaxis v=A, Haxis h=H1);
   // EFFECTS: create an empty square at position (v, h)

   Vaxis getV() const;
   // EFFECTS: return the vertical coordinate of the square

   void setV(Vaxis v);
   // MODIFIES: "this"
   // EFFECTS: update the vertical coordinate of the square

   Haxis getH() const;
   // EFFECTS: return the horizontal coordinate of the square

   void setH(Haxis h);
   // MODIFIES: "this"
   // EFFECTS: update the horizontal coordinate of the square

   const Piece &getPiece() const;
   // EFFECTS: return a const reference to the piece placed on the square
   //          throw SquareException if the square is empty

   void setPiece(const Piece *p);
   // MODIFIES: "this"
   // EFFECTS: place "p" on the square

   bool isEmpty() const;
   // EFFECTS: return true if the square is empty, and false otherwise

   bool isOnFirstDiagonal() const;
   // EFFECTS: return true if the square is on the first diagonal 
   // of the board (which goes from top-left to bottom-right)
   //          return false otherwise

   bool isOnSecondDiagonal() const;
   // EFFECTS: return true if the square is on the second diagonal 
   // of the board (which goes from top-right to bottom-left)
   //          return false otherwise

   std::string toString() const;
   // EFFECTS: return a string the encodes the position of the square
   // e.g., A1 for the first square on the top-left, 
   //       and B1 for the square beneath it
};

#endif
