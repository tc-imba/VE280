#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "square.h"
#include "exceptions.h"

class Board{
   // OVERVIEW: a Quarto 4x4 board
   Square grid[N][N];

public:
   Board();
   // EFFECTS: create a 4x4 board of empty squares

   Square &getSquare(Vaxis v, Haxis h);
   // EFFECTS: return a reference to the square at position (v, h)

   Square &getEmptySquare(Vaxis v, Haxis h);
   // EFFECTS: return a reference to the square at position (v, h)
   //          throw SquareException if the square is not empty

   Square &getEmptySquare(const std::string &s);
   // EFFECTS: return a reference to the square at a position encoded in "s" (e.g., B2)
   //          throw SquareException if the square is not empty

   void place(Piece &p, Square &sq);
   // MODIFIES: "p" and "sq"
   // EFFECTS: place piece "p" on square "sq"

   bool isWinning(const Piece &p, const Square &sq);
   // REQUIRES: if "p" is used, then it is already placed on "sq".
   //           Otherwise, "sq" is empty.
   // EFFECTS: return true if piece "p" on square "sq" yields a
   // winning position (i.e., 4 pieces with at least one common 
   // attribute, which are aligned horizontally, vertically, or 
   // diagonally
   // REMARK: "p" may or may not have been placed on "sq"
   // (Please think about why), which may be empty.

   std::string toString() const;
   // EFFECTS: return a string that represents the board
   // e.g., at the beginning of the game, the returned string
   //       prints as follows:
   //     1    2    3    4
   //   +----+----+----+----+
   // a |    |    |    |    |
   //   |    |    |    |    |
   //   +----+----+----+----+
   // b |    |    |    |    |
   //   |    |    |    |    |
   //   +----+----+----+----+
   // c |    |    |    |    |
   //   |    |    |    |    |
   //   +----+----+----+----+
   // d |    |    |    |    |
   //   |    |    |    |    |
   //   +----+----+----+----+
   //       after placing, SBCH on A1 and TBQO on C2, we get:
   //     1    2    3    4
   //   +----+----+----+----+
   // a | SB |    |    |    |
   //   | CH |    |    |    |
   //   +----+----+----+----+
   // b |    |    |    |    |
   //   |    |    |    |    |
   //   +----+----+----+----+
   // c |    | TB |    |    |
   //   |    | QO |    |    |
   //   +----+----+----+----+
   // d |    |    |    |    |
   //   |    |    |    |    |
   //   +----+----+----+----+
};

#endif
