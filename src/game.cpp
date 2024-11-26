#include "game.h"
#include <random>




Game::Game() 
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
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
    currentBlock.Draw();
}

void Game::HandleInput()
{
   int keyPressed = GetKeyPressed();
   if(gameOver && keyPressed != 0) 
   {
        gameOver = false;
        Reset();
   }
   switch (keyPressed)
   {
        case KEY_LEFT:
            MoveBlockLeft();
            break;
        case KEY_RIGHT:
            MoveBlockRight();
            break;
        case KEY_DOWN:
            MoveBlockDown();
            UpdateScore(0,1);
            break;
        case KEY_UP:
            RotateBlock();
            break;
        
        default:
            break;
   } 
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
    currentBlock.Rotate();

    if(isBlockOutside() || !BlockFits()) 
    {
        currentBlock.UndoRotate();
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
    UpdateScore(rowsCompleted,0);
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
}

void Game::UpdateScore(int rowsCompleted, int moveDownPoints)
{   
    switch (rowsCompleted)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    default:
        break;
    }

    score += moveDownPoints;
}
