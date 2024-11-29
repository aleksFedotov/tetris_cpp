#include "game.h"
#include <random>
#include <algorithm>
#include <iostream>




Game::Game() 
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
    InitAudioDevice();
    music = LoadMusicStream("Sounds/music.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("Sounds/rotate.mp3");
    completeSound = LoadSound("Sounds/clear.mp3");
    rowCompletedOverall = 0;
    maxFallInterval = 0.8;
    minFallInterval = 0.1;
    totalLevels = 29;
    level = 0;
    initialDelay = 0.3;
    repeatInterval = 0.06;
    gameOver = false;
}

Game::~Game() 
{   
    UnloadMusicStream(music);
    UnloadSound(rotateSound);
    UnloadSound(completeSound);
    CloseAudioDevice();
}

Block Game::GetRandomBlock() 
{
    if(blocks.empty()) 
    {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks() 
{
    return {IBlock(),JBlock(), LBlock(), OBlock(), SBlock(), TBlock(),ZBlock()};
}

void Game::Draw() 
{
    grid.Draw();
    currentBlock.Draw(11,11);
    switch (nextBlock.id)
    {
    case 3:
        nextBlock.Draw(255,415);
        break;
    case 4:
        nextBlock.Draw(255,405);
        break;
    
    default:
        nextBlock.Draw(270,395);
        break;
    }
   
}

// void Game::HandleInput()
// {
//    int keyPressed = GetKeyPressed();
//    if(gameOver && keyPressed != 0) 
//    {
//         gameOver = false;
//         Reset();
//    }
//    switch (keyPressed)
//    {
//         case KEY_LEFT:
//             MoveBlockLeft();    
//             break;
//         case KEY_RIGHT:
//             MoveBlockRight();
//             break;
//         case KEY_DOWN:
//             MoveBlockDown();
//             UpdateScore(0,1);
//             break;
//         case KEY_UP:
//             RotateBlock();
//             break;
        
//         default:
//             break;
//    } 
// }
void Game::HandleInput()
{
    for (auto& [key, pressed] : keyPressed) 
        {    
            if (IsKeyUp(key)) 
            {
               
                keyPressed[key] = false;
                HandleKeyRelease(key);
            } 
            else if (pressed && IsKeyDown(key) && key !=KEY_UP) 
            {
                
                double currentTime = GetTime();
                double elapsedTime = currentTime - keyTimers[key];

                if (elapsedTime >= repeatInterval) 
                {
                    HandleKeyAction(key); 
                    keyTimers[key] = currentTime; 
                }
            }
        }

     
        int key = GetKeyPressed();
        if (key != 0) 
        {
            
            keyPressed[key] = true; 
            keyTimers[key] = GetTime(); 
            HandleKeyAction(key); 
        }
}

void Game::HandleKeyAction(int key)
{
    switch (key) 
    {
        case KEY_LEFT:
            MoveBlockLeft();
            break;
        case KEY_RIGHT:
            MoveBlockRight();
            break;
        case KEY_DOWN:
            MoveBlockDown();
            UpdateScore(0, 1); 
            break;
        case KEY_UP:
            RotateBlock();
            break;
        default:
            break;
    }
}

void Game::HandleKeyRelease(int key)
{
    keyPressed[key] = false;
}

void Game::MoveBlockLeft() 
{   
    if(!gameOver)
    {
        currentBlock.Move(0,-1);
        if(isBlockOutside() || !BlockFits()) 
        {
            currentBlock.Move(0,1);
        }
    }
}

void Game::MoveBlockRight() 
{
    if(!gameOver) 
    {
        currentBlock.Move(0,1);
        if(isBlockOutside() || !BlockFits()) 
        {
            currentBlock.Move(0,-1);
        }

    }
}

void Game::MoveBlockDown() 
{   
    if(!gameOver) 
    {
        currentBlock.Move(1,0);
        if(isBlockOutside() || !BlockFits()) 
        {
            currentBlock.Move(-1,0);
            LockBlock();
        }
    }

}

double Game::CalculateFallInterval()
{
    return std::max(minFallInterval, maxFallInterval *  pow(minFallInterval/maxFallInterval,level/totalLevels));
}

bool Game::isBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for(Position item : tiles) 
    {
        if(grid.IsCellOutside(item.row, item.col)) 
        {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock()
{   
    if(!gameOver) 
    {
        currentBlock.Rotate();

        if(isBlockOutside() || !BlockFits()) 
        {
            currentBlock.UndoRotate();
        }
        else 
        {
            PlaySound(rotateSound);
        }
    }

}

void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition();

    for(Position item : tiles ) 
    {
        grid.grid[item.row][item.col] = currentBlock.id;  
    }
    currentBlock = nextBlock;
    if(!BlockFits())
    {
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCompleted = grid.ClearFullRows();
    if(rowsCompleted > 0) 
    {
        PlaySound(completeSound);
        UpdateScore(rowsCompleted,0);
    }
}

bool Game::BlockFits()
{   
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for(Position item : tiles) 
    {
        if(!grid.IsCellEmpty(item.row, item.col)) {
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
    level = 0;
    rowCompletedOverall = 0;
}

void Game::UpdateScore(int rowsCompleted, int moveDownPoints)
{   
    int basePoints = 0;
    switch (rowsCompleted)
    {
    case 1:
        basePoints += 40;
        break;
    case 2:
        basePoints += 100;
        break;
    case 3:
        basePoints += 300;
        break;
    case 4:
        basePoints += 1200; // bonus for tetris
        break;
    default:
        break;
    }

    score += basePoints * (level +1);
    score += moveDownPoints;

    rowCompletedOverall += rowsCompleted;

    if(rowCompletedOverall >= (level+1) * 10) 
    {
        level++;
    }

    // if(level == 30) {
    //     gameOver = true;
    // }

}
