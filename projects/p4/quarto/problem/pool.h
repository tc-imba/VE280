#ifndef POOL_H
#define POOL_H

#include "piece.h"
#include "exceptions.h"

class Pool{
   // OVERVIEW: a pool of Quarto pieces
   Piece pieces[NP];

   Piece & getUnusedPiece(int index);
   // EFFECTS: return the reference to a piece given its index
   //          throw UsedPieceException if the piece is placed on the board

public:
   Pool();
   // EFFECTS: creates a pool of the 16 unused Quarto pieces
   // "unused" means "not placed on the board"

   Piece & getUnusedPiece(Height h, Color c, Shape s, Top t);
   // EFFECTS: return the reference to a piece "p" given its attributes
   //          throw UsedPieceException if "p" is placed on the board

   Piece & getUnusedPiece(const std::string &in);
   // EFFECTS: return the reference to a piece "p" given its encoding
   //          throw UsedPieceException if "p" is placed on the board
   // see file "quarto.h/cpp" for the encoding of each attribute
   // e.g., "SEQO" encodes a piece that is short, sepia, square, and solid

   std::string toString() const;
   // EFFECTS: returns a string that lists all the unused pieces
   // preceded by string "Available:\n" if the list is not empty
   //          returns the empty string otherwise
   // e.g., when the game starts, the returned string would print as follows:
   // Available:
   // SB SB SB SB SE SE SE SE TB TB TB TB TE TE TE TE 
   // CH CO QH QO CH CO QH QO CH CO QH QO CH CO QH QO
   //
   // Note that all the 4-character strings have been split over two
   // lines (i.e., SBCH is the first piece, SBCO is the second...)
};

#endif
