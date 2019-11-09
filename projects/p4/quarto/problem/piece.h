#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <sstream>
#include "quarto.h"

class Piece{
   // represents a piece of the game
   Height h;
   Color c;
   Shape s;
   Top t;
   bool used; // indicates if it has already been placed on the board

public:
   Piece(Height h=SHORT, Color c=BEIGE, Shape s=CIRCLE, Top t=HOLLOW);
   // EFFECTS: create an unused piece with attributes (h, c, s, t)

   bool compareHeight(const Piece &p) const;
   // EFFECTS: return true if "this" has the same height as "p"
   //          return false otherwise

   bool compareColor(const Piece &p) const;
   // EFFECTS: return true if "this" has the same color as "p"
   //          return false otherwise

   bool compareShape(const Piece &p) const;
   // EFFECTS: return true if "this" has the same shape as "p"
   //          return false otherwise

   bool compareTop(const Piece &p) const;
   // EFFECTS: return true if "this" has the same top as "p"
   //          return false otherwise

   bool isUsed() const;
   // EFFECTS: return true if "this" has been placed on the board
   //          return false otherwise

   void setUsed(bool u);
   // MODIFIES: "used"
   // EFFECTS: set "used" to "u"

   std::string toString() const;
   // EFFECTS: return a 4-char string representing "this"
   // see file "quarto.h" for the encoding of each attribute
   // e.g., "SEQO" encodes a piece that is short, sepia, square, and solid
};

#endif
