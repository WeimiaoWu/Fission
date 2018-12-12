#ifndef __FUSSIONBOARD_H__
#define __FUSSIONBOARD_H__

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "baseboard.h"


namespace cs427_527
{
    class FussionBoard : public BaseBoard
    {
    public:
        FussionBoard(int w, int h);
        int getBoardColor(int row, int col) const override;
    //     virtual FussionBoard();
        bool isLegalMove(int fromR, int fromC, int toR, int toC) const override;
        void makeMove(int fromR, int fromC, int toR, int toC) override;
        bool gameOver() const override;
        bool isEmptyPath(int fromR, int fromC, int toR, int toC) const;
        bool isBoarder(int row, int col) const;

        void toHTML();

    };
    std::ostream& operator<<(std::ostream& os, const FussionBoard& board);



}


#endif