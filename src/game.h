#pragma once 
#include "grid.h"
#include "blocks.cpp"
#include <map>


class Game 
{
    public: 
        Game();
        ~Game();
        void Draw();
        void HandleInput();
        void HandleKeyAction(int key);
        void HandleKeyRelease(int key);
        void MoveBlockDown();
        double CalculateFallInterval();
        bool gameOver;
        int score;
        Music music;
        int level;
        int rowCompletedOverall;
        double initialDelay;
        double repeatInterval;
       

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
        std::map<int, bool> keyPressed;
        std::map<int, double> keyTimers;
        

};