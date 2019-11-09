#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"
#include "pool.h"

class Player{
   // OVERVIEW: A base class for the player interface
protected:
   Board *board;
   Pool *pool;

public:
   Player(Board *board, Pool *pool): board(board), pool(pool){}
   // EFFECTS: create a player with access to "board" and "pool"

   virtual Piece & selectPiece() = 0;
   // REQUIRES: there is an unused piece to select
   // EFFECTS: return an unused piece for the next player to place

   virtual Square & selectSquare(const Piece &p) = 0;
   // REQUIRES: there is an empty square to place the piece "p"
   // EFFECTS: return an empty square to place the piece "p".
};

extern Player *getHumanPlayer(Board *b, Pool *p);
extern Player *getMyopicPlayer(Board *b, Pool *p, unsigned int s);
#endif
