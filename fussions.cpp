#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "fussionboard.h"

using cs427_527::FussionBoard;

int main(int argc, char **argv)
{
  
   if(argc == 3)
  {
    try{
          FussionBoard b(atoi(argv[1]), atoi(argv[2]));
 
  std::cout << b;
  while (!b.gameOver() && std::cin)
    {
      std::cout << "PLAYER " << b.getCurrentPlayer() << std::endl;
      std::string move;
      if (std::getline(std::cin, move))
  {
    std::istringstream in(move);
    int fromR, fromC, toR, toC;
    if (in >> fromR >> fromC >> toR >> toC)
      {
        if (b.isLegalMove(fromR, fromC, toR, toC))
    {
      
      b.makeMove(fromR, fromC, toR, toC);
      std::cout << b;
    }
        else
    {
      std::cout << "illegal move" << std::endl;
    }
      }
    else
      {
        std::cout << "invalid input" << std::endl;
      }
  }
    }
    try{
      b.toHTML();
    }catch(...)
    {
      std::cerr << "unable to generate HTML display" << std::endl;
    }
  if (b.gameOver())
    {
      
      if (b.pieceCount(0) == b.pieceCount(1))
      {
       std::cout << "Draw"  <<  std::endl;
     
      }else
      {
      int win;
      win = (b.pieceCount(0)==1)?0 : 1;
      std::cout << win << " wins" <<  std::endl;
      }

    }



  }
  catch (const std::string& s)
    {
      std::cerr << argv[0] << ": " << s << std::endl;
      return 1;
    }
  catch (...)
  {
    std::cerr << "wrong parameter" <<std::endl;
    return 1;
  }
}else
{
  std::cerr << "wrong number of parameter" <<std::endl;
  return 1;
}
}


