#pragma once
#include <vector>
#include <map>
#include "colors.h"
#include "position.h"

class Block 
{
    public:
        Block();
        int id;
        void Draw(int offsetx, int offsetY);
        void Move(int row, int col);
        void Rotate();
        void UndoRotate();
        std::vector<Position> GetCellPosition();
        std::map<int, std::vector<Position>> cells;

    private:
        int cellSize;
        int rotationState;
        std::vector<Color> colors;
        int rowOffset;
        int colOffset;
};