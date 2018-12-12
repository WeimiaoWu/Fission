#include <vector>
#include <memory>
#include <iostream>
#include <sstream>
#include "baseboard.h"
#include "piece.h"
#include "math.h"

namespace cs427_527
{
  BaseBoard::BaseBoard(int w, int h):  
  width(w),
  height(h),
  turn(0),
  move_limit(100000),
  totalMoves(0),
  board(h, std::vector<std::shared_ptr<Piece>>(w, nullptr)),
  outprint({"..", "  "})
  {
  }

  BaseBoard::~BaseBoard()
  {
  }


  void BaseBoard::setBoardFace(int i, std::string toprint)
  {
    if (i < int(outprint.size()))
    {
      outprint[i] = toprint;
    }
  }

  int BaseBoard::getWidth() const
  {
    return width;
  }
  int BaseBoard::getHeight() const
  {
    return height;
  }

  int BaseBoard::getCurrentPlayer() const
  {
    return turn;
  }

  bool BaseBoard::inBounds(int r, int c) const
  {
    return r >= 0 && r < height && c >= 0 && c < width;
  }


  std::shared_ptr<Piece> BaseBoard::getPiece(int r, int c)
  {
  if (inBounds(r, c))
      {
  return board[r][c];
      }
    else
      {
  return nullptr;
      }

  }
  std::shared_ptr<Piece> BaseBoard::getPiece(int r, int c) const
  {
  if (inBounds(r, c))
      {
  return board[r][c];
      }
    else
      {
  return nullptr;
      }
  }


  void BaseBoard::turnPiece(int r, int c)
  {
    if(inBounds(r, c) && board[r][c] && getPiece(r, c)!= nullptr)
    {
      int p = getPiece(r, c)->getPlayer();
      p = iabs(1-p);
      getPiece(r, c)->setPlayer(p);

    }

  }


  void BaseBoard::placePiece(int r, int c, std::shared_ptr<Piece> p)
  {
  if (inBounds(r, c))
      {
      board[r][c] = p;
      }
  }

  void BaseBoard::removePiece(int r, int c)
  {
     if (inBounds(r, c))
      {
        board[r][c] = nullptr;
      }
  }

  bool BaseBoard::isFull() const
  {
    bool full = true;
    for (int r = 0; r < height; r++)
        {
        for (int c = 0; c < width; c++)
          {
            if (getPiece(r, c) == nullptr)
              {
                full = false;
              }
          }

      }

    return full;
  }


  

   int BaseBoard::pieceCount(int p) const
   {
    int count = 0;
    for (int r = 0; r < height; r++)
        {
        for (int c = 0; c < width; c++)
          {
            if(getPiece(r, c)!=nullptr){

              if (getPiece(r, c)->getPlayer()==p)
                {
                  count +=1;
                }
            }
          }
      }
   return count;
 }


   bool BaseBoard::isBoarder(int row, int col) const
  {
    return(row == 0 ||row == getHeight()-1|| col == 0 ||col == getWidth()-1);
  }

   std::string BaseBoard::toString() const
  {
    std::ostringstream os;

    for (int r = 0; r < height; r++)
      {
  for (int c = 0; c < width; c++)
    {
      if (getPiece(r, c) == nullptr)
        {

        os << outprint[getBoardColor(r, c)];  
        }
      else
        {
        os << getPiece(r, c)->toString();
        }
     
    }
  os << std::endl;
      }

    return os.str();
  }

  int BaseBoard::findLongestMove() const
  {
    int longest = 0;
    for (int fromR = 0; fromR < height; fromR++)
      {
  for (int fromC = 0; fromC < width; fromC++)
    {
      if (getPiece(fromR, fromC) != nullptr
    && getPiece(fromR, fromC)->getPlayer() == turn)
        {
    longest = imax(longest, findLongestMove(fromR, fromC));
        }
    }
      }
    return longest;
  }

  int BaseBoard::findLongestMove(int fromR, int fromC) const
  {
    int longest = 0;
    for (int toR = 0; toR < height; toR++)
      {
  for (int toC = 0; toC < width; toC++)
    {
      if (distance(fromR, fromC, toR, toC) > longest
    && getPiece(fromR, fromC)->isLegalMove(*this, toR, toC))
        {
    longest = distance(fromR, fromC, toR, toC);
        }
    }
      }
    return longest;
  }

}