#ifndef __FUSSION_H__
#define __FUSSION_H__

#include <string>
#include <memory>
#include <vector>
#include "piece.h"
#include "fussion.h"
// #include "Fussionboard.h"


namespace cs427_527
{
  class FussionBoard;

  class Fussion : public Piece
  {
  public:

    
    Fussion(int p, int r, int c);
    virtual ~Fussion();
    bool isLegalMove(const BaseBoard& board, int toR, int toC) const override ;
    void makeMove(BaseBoard& board, int toR, int toC) override;
    virtual std::shared_ptr<Fussion> light() const;
    virtual bool isLight() const;

  protected:

    // bool isLegalJump(const BaseBoard& board, int toR, int toC) const override;
    // void jump(BaseBoard& board, int toR, int toC) const override;
  
    virtual bool isLegalDirection(int toR, int toC) const;
    virtual bool isLegalDestination(const BaseBoard& board, int fromR, int fromC, int toR, int toC) const ;
    

  
    // virtual bool isLegalDistance(int dist) const;

    // // virtual bool canMoveBackwards() const;


    // bool checkPromote(const BaseBoard& board, int toR, int toC) const override;

   

  };
}

#endif
