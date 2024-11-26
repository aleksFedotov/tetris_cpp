#pragma once 
#include "grid.h"
#include "blocks.cpp"


class Game 
{
    public: 
        Game();
        Block GetRandomBlock();
        std::vector<Block> GetAllBlocks();
        void Draw();
        void HandleInput();
        void MoveBlockLeft();
        void MoveBlockRight();
        void MoveBlockDown();
        Grid grid;
        bool gameOver;
        int score;

    private:
        bool isBlockOutside();
        void RotateBlock();
        void LockBlock();
        bool BlockFits();
        void Reset();
        void UpdateScore(int rowsCompleted, int moveDownPoints);
        std::vector<Block> blocks;
        Block currentBlock;
        Block nextBlock;
        

};