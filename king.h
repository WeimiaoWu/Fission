#ifndef __KING_H__
#define __KING_H__

#include <string>

#include "fussion.h"

namespace cs427_527
{
  class CheckerBoard;
  
  class King : public Fussion
  {
  public:
    /**
     * Creates a king owned by the given player at the given position.
     *
     * @param p 0 or 1
     * @param r a nonnegative integer
     * @param c a nonnegative integer
     */
    King(int p, int r, int c);

    /**
     * Destroys this king.
     */
    ~King();

    /**
     * Returns a printable representation of this checker.
     *
     * @return a printable representation of this checker
     */
    std::string toString() const override;
    bool isLight() const override;

  protected:
  

  };
}
#endif
