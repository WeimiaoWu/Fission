#include <algorithm>
#include <cctype>
#include <iostream>

#include "king.h"
#include "fussion.h"

namespace cs427_527
{
  King::King(int p, int r, int c)
    : Fussion(p, r, c)
  {
  }

  King::~King()
  {
  }

  bool King::isLight() const
  {
    // kings can move backwards
    return true;
  }

  // bool King::checkPromote(const BaseBoard& board, int toR, int toC) const
  // {
  //   // kings are never promoted
  //   return false;
  // }

  std::string King::toString() const
  {

    // convert base class's result to upper case
    std::string result = Piece::toString();
    
    std::transform(result.begin(), result.end(), result.begin(), tolower);
    return result;
  }
}

