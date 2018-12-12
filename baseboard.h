#ifndef __BASEBOARD_H__
#define __BASEBOARD_H__

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "piece.h"


namespace cs427_527
{
    class Checker;
    class BaseBoard
    {
    public: 
        /* construct/deconstruct/appearance */
        
        BaseBoard(int w, int h);
        virtual ~BaseBoard();
        void setBoardFace(int i, std::string toprint);

        /* basic board info */        
        int getWidth() const;
        int getHeight() const;
        int getCurrentPlayer() const;
        bool isFull() const;
        virtual int getBoardColor(int row, int col) const = 0;

        /* basic piece movement */        
        bool inBounds(int r, int c) const;
        std::shared_ptr<Piece> getPiece(int row, int col);
        std::shared_ptr<Piece> getPiece(int row, int col) const ;
        void placePiece(int r, int c, std::shared_ptr<Piece> p);
        void removePiece(int r, int c);
        int pieceCount(int p) const;
        bool isBoarder(int toR, int toC) const;
 
        

        /* other virtual methods */      
        virtual bool isLegalMove(int fromR, int fromC, int toR, int toC) const = 0;
        virtual void makeMove(int fromR, int fromC, int toR, int toC) = 0;
        virtual bool gameOver() const = 0;
        virtual std::string toString() const;
        virtual void turnPiece(int r, int c); 
        



    protected:
        int width;
        int height;
        int turn;
        const int move_limit;
        int totalMoves;
        
        std::vector<std::vector<std::shared_ptr<Piece>>> board;
        std::vector<std::string> outprint; 

        virtual int findLongestMove() const;
        virtual int findLongestMove(int fromR, int fromC) const;

    };




}



#endif