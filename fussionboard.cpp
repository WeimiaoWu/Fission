#include <vector>
#include <memory>
#include <iostream>
#include <sstream>
#include <fstream>
#include "baseboard.h"
#include "piece.h"
// #include "checker.h"
#include "fussionboard.h"
#include "fussion.h"
// #include "fussion.h"


#include "math.h"

namespace cs427_527
{

FussionBoard::FussionBoard(int w, int h):BaseBoard(w, h)
{
    if((w < 4 )||(w < h) ||(h<4) || (h % 2 !=0) || (w % 2 !=0))
    {
        throw(std::string("Invalid width and hight, use default 8 X 8"));
        w = 8;
        h = 8;
    }

    for (int r = 1; r < h -1; r++)
    {
        for (int c = 1; c < w -1; c++)
        {
          if( (w + h) % 4 ==0){
            board[r][c] = std::make_shared<Fussion>( ((r + c) %2) , r, c);
          }else
            {
              board[r][c] = std::make_shared<Fussion>( ((r + c + 1) %2) , r, c);
            }


        }
    }
    
    for (int c = 1; c < w -1; c++)
    {
        for (int r = 0; r < h / 2 - c; r ++ )
        {
            removePiece(r, c);
            removePiece(r, w - c - 1);
        }

        for (int r = h/2 + c; r < h; r ++)
        {
            removePiece(r, c);
            removePiece(r, w - c - 1);
        }
    }


    if (h >= 6)
        {
            for (int r = h/2 -2; r < h/2 +2; r ++)

            {
                // std::cout << r << std::endl;
                if (getPiece(r, 2)&&getPiece(r, w-3) )
                {
                    board[r][2] = std::dynamic_pointer_cast<Fussion>(getPiece(r, 2))->light();
                    board[r][w-3] = std::dynamic_pointer_cast<Fussion>(getPiece(r, w-3))->light();
                }
            }
        }

}



  int FussionBoard::getBoardColor(int r, int c) const
  {
   if (r % 2 == c % 2)
      {
      return 0;
      }
    else
      {
       return 1;
      }
  }


   bool  FussionBoard::isLegalMove(int fromR, int fromC, int toR, int toC) const
   {
     if (!inBounds(fromR, fromC) || !inBounds(toR, toC))
      {
        return false;
      }else
      {
        std::shared_ptr<const Fussion> moving = std::dynamic_pointer_cast<Fussion>(getPiece(fromR, fromC));
        return (
        moving != nullptr
        &&isEmptyPath(fromR, fromC, toR, toC)
        && moving->getPlayer() == turn
        && moving->isLegalMove(*this, toR, toC));
      }


   }



   void  FussionBoard::makeMove(int fromR, int fromC, int toR, int toC)
   {

    if (isLegalMove(fromR, fromC, toR, toC))
      {
        
        int hitR = toR +(fromR<toR) - (fromR > toR);
        int hitC = toC +(fromC<toC) - (fromC > toC);


        if(getPiece(hitR, hitC) == nullptr)
        {
        std::shared_ptr<Fussion> moving = std::dynamic_pointer_cast<Fussion>(getPiece(fromR, fromC));
        moving->makeMove(*this, toR, toC);
        }else
        { 

          // removePiece(hitR, hitC);

          if(!std::dynamic_pointer_cast<Fussion>(getPiece(hitR, hitC))->isLight())
          {

          for (int i = toR-1; i <= toR + 1; i ++)
          {
            for(int j = toC -1; j <= toC + 1; j++)
            {
              if(getPiece(i, j)!=nullptr)
              {
                removePiece(i, j);
              }
            }
          }
        }
         removePiece(hitR, hitC);
         removePiece(fromR, fromC);
        }
        turn = (turn + 1) % 2;
      }
    }

  bool FussionBoard::gameOver() const
  { 
    return(pieceCount(0) ==1 || pieceCount(1) ==1 || (pieceCount(0) == 0&&pieceCount(1) == 0));

  }


  bool FussionBoard::isEmptyPath(int fromR, int fromC, int toR, int toC) const
  {
    bool empty = true;
    if(fromR ==toR)
    {
      for (int j = fromC+1; j <= toC; j++)
      {
        if(getPiece(fromR, j))
          {empty = false;}
      }
    }else if(fromC ==toC)
    {
      for (int i = fromR+1; i<= toR; i++)
      {
        if(getPiece(i, fromC))
          {empty = false;}
      }
    }else
    {
      for (int i = fromR +1; i<= toR; i ++)
        for (int j = fromC +1; j <= toC; j++)
        {
          if(getPiece(i, j))
          {
            empty = false;
          }
        }
    }
    return empty;
  }


  void FussionBoard::toHTML()
  {
    std::ofstream ofs;
    ofs.open("fission_output.html");
    ofs << "<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"UTF-8\">\n";
    ofs << "<title>Fission</title>\n</head>\n<body>\n<canvas id=\"board\" width=\"";
    ofs << 20*getWidth();
    ofs <<"\" height=\"";
    ofs << 20*getHeight();
    ofs <<"\"></canvas>\n";
    ofs << "<script>\nvar canvas = document.getElementById('board');\nvar g = canvas.getContext('2d');\n";

    //draw the board
    for (int r = 0; r < height; r++)
    {
      for (int c = 0; c < width; c++)
      {
        std::string boardcol = (getBoardColor(r,c) ==0)? "#FFFFFF":"#808080";
          ofs << "g.fillStyle = '"<<boardcol << "';\n";
          ofs << "g.fillRect(" << c*20 <<", " << r*20 << ", "<<"20, 20);\n";
        }
      }

    for (int r = 0; r < height; r++)
    {
      for (int c = 0; c < width; c++)
      {
        if (getPiece(r, c) != nullptr)
        {
          ofs << "g.beginPath();\n";
          if(std::dynamic_pointer_cast<Fussion>(getPiece(r, c)))
          {
            int size = (std::dynamic_pointer_cast<Fussion>(getPiece(r, c))->isLight())?5:8;
            std::string player = (getPiece(r, c)->getPlayer()==0)? "#FF0000" : "#0000FF";
            ofs << "g.arc(" << 20*c +10 << ", " << 20*r +10 << ", " << size << ", 0, 2*Math.PI);\n";
            ofs << "g.fillStyle = '" << player << "';\n";
            ofs << "g.fill();\n";
          }           
        }
        }
      }

    ofs << "</script>\n</body>\n</html>" << std::endl;
    ofs.close();
  }



  std::ostream& operator<<(std::ostream& os, const FussionBoard &board)
  {
    return os << board.toString();
  }


}
