#ifndef __PIECE_H__
#define __PIECE_H__

#include <string>
#include <memory>
#include <vector>

namespace cs427_527
{
  class BaseBoard;

  class Piece
  {
  public:
    Piece(int p, int r, int c);
    virtual ~Piece();

    int getPlayer() const;
    void setPlayer(int p);
    int getPlayerNumber() const;
    void reverse(); 
    void setColor(int p, std::string color);
    void addPlayer(std::string color);
    virtual std::string toString() const;
    virtual bool isLegalMove(const BaseBoard& board, int toR, int toC) const = 0;
    virtual void makeMove(BaseBoard& board, int toR, int toC) = 0;

  protected:
 


  protected:
    int player;    
    int row;
    int col;
    std::vector<std::string> outprint;
    int nPlayer;

  };
}





#endif
