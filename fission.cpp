#include <memory>
// #include "checker.h"
#include "baseboard.h"
#include "king.h"
#include "piece.h"
#include "math.h"
#include "fussion.h"

namespace cs427_527
{
 

  Fussion::Fussion(int p, int r, int c)
    : Piece(p, r, c)
  {
    outprint = {"RR","BB"};
    
  }


  Fussion::~Fussion()
  {
  }

  bool Fussion::isLegalMove(const BaseBoard& board, int toR, int toC) const
  {
    // int dist = distance(row, col, toR, toC);

    return (board.inBounds(row, col) && board.inBounds(toR, toC)
        && isLegalDirection(toR, toC)
        && (row !=toR || col !=toC)
        && isLegalDestination(board, row, col, toR, toC));

  }

  std::shared_ptr<Fussion> Fussion::light() const
  {
    return std::make_shared<King>(player, row, col);
  }

  bool Fussion::isLegalDirection(int toR, int toC) const
  {
    // direction legal if (can move backwards or moving forward) and diagonal
    return (iabs(row - toR) == iabs(col - toC) ||((row - toR))==0 ||(col - toC)==0 );
  }

  void Fussion::makeMove(BaseBoard& board, int toR, int toC)
  { 
    if (isLegalMove(board, toR, toC))
    {

        std::shared_ptr<Fussion> self = std::dynamic_pointer_cast<Fussion>(board.getPiece(row, col));
        board.removePiece(row, col);
        row = toR;
        col = toC;
        board.placePiece(toR, toC, self);

    }
  }

  bool Fussion::isLegalDestination(const BaseBoard& board,int fromR, int fromC, int toR, int toC) const
  { 
    // destination must be empty
    int hitR = toR +(fromR<toR) - (fromR > toR);
    int hitC = toC +(fromC<toC) - (fromC > toC);
    return (board.getPiece(hitR, hitC) != nullptr ||(board.isBoarder(toR, toC) && board.getPiece(toR, toC) == nullptr));
  }



  bool Fussion::isLight() const
  {
    return false;
  }

}

