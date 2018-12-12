#include <memory>
// #include "checker.h"
// #include "checkerboard.h"
#include "baseboard.h"
#include "piece.h"
#include "math.h"

namespace cs427_527
{
  Piece::Piece(int p, int r, int c):
      player(p),
      row(r),
      col(c),
      outprint({"bb", "rr"}),
      nPlayer(2)
  {
    
  }

  Piece::~Piece()
  {

  }

  int Piece::getPlayer() const
  {
    return player;
  }

  void Piece::setPlayer(int p)
  {
    if (p < nPlayer)
    {
      player = p;

    }else
    {
      throw std::string("Error: undefined player");
    }
  }

  void Piece::reverse() /* Reversi kind of behavior */
  
  {
    player = (player + 1) % nPlayer;
  }

  void Piece::setColor(int p, std::string color)
  {
    if (p < (int)(outprint.size()))
    {
      outprint[p] = color;
    }
  }

  int Piece::getPlayerNumber() const
  {
    return nPlayer;
  }

  void Piece::addPlayer(std::string color)
  {
    nPlayer +=1;
    outprint.push_back(color);
  }

  std::string Piece::toString() const
  {

    return outprint[player];
  
  }

  // bool Piece::isLegalDestination(const BaseBoard& board, int toR, int toC) const
  // { 
  //   // destination must be empty
  //   return board.getPiece(toR, toC) == nullptr;
  // }


}