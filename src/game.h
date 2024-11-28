#pragma once 
#include "grid.h"
#include "blocks.cpp"


class Game 
{
    public: 
        Game();
        ~Game();
        void Draw();
        void HandleInput();
        void MoveBlockDown();
        double CalculateFllInterval();
        bool gameOver;
        int score;
        Music music;
        int level;
        int rowCompletedOverall;

    private:
        Grid grid;
        Block GetRandomBlock();
        std::vector<Block> GetAllBlocks();
        void MoveBlockLeft();
        void MoveBlockRight();
        bool isBlockOutside();
        void RotateBlock();
        void LockBlock();
        bool BlockFits();
        void Reset();
        void UpdateScore(int rowsCompleted, int moveDownPoints);
        std::vector<Block> blocks;
        Block currentBlock;
        Block nextBlock;
        Sound rotateSound;
        Sound completeSound;
        double maxFallInterval;
        double minFallInterval;
        int totalLevels;
        

};