#include "game.h"
#include <random>
#include <algorithm>
#include <iostream>

// Constructor for the Game class, initializes game settings and resources.
Game::Game() 
{
    grid = Grid();  // Initialize the game grid.
    blocks = GetAllBlocks();  // Retrieve all block types.
    currentBlock = GetRandomBlock();  // Get the first random block.
    nextBlock = GetRandomBlock();  // Get the next random block.
    score = 0;  // Initialize the score to 0.
    
    // Initialize the audio device and load sounds.
    InitAudioDevice();
    music = LoadMusicStream("Sounds/music.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("Sounds/rotate.mp3");
    completeSound = LoadSound("Sounds/clear.mp3");
    
    // Initialize gameplay settings.
    rowCompletedOverall = 0;
    maxFallInterval = 0.8;  // Initial fall speed.
    minFallInterval = 0.1;  // Minimum fall speed.
    totalLevels = 29;  // Total levels before max level.
    level = 0;  // Initial level.
    initialDelay = 0.3;  // Delay for input.
    repeatInterval = 0.06;  // Interval for repeated input.
    gameOver = false;  // Game is not over at start.
}

// Destructor for the Game class, cleans up resources.
Game::~Game() 
{   
    UnloadMusicStream(music);  // Unload background music.
    UnloadSound(rotateSound);  // Unload rotation sound effect.
    UnloadSound(completeSound);  // Unload row-clear sound effect.
    CloseAudioDevice();  // Close the audio device.
}

// Generates a random block from the available set.
Block Game::GetRandomBlock() 
{
    // If no blocks remain in the list, refill it.
    if(blocks.empty()) 
    {
        blocks = GetAllBlocks();
    }
    // Choose a random block and remove it from the list.
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

// Returns all possible block types as a vector.
std::vector<Block> Game::GetAllBlocks() 
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

// Draws the game elements on the screen.
void Game::Draw() 
{
    grid.Draw();  // Draw the game grid.
    currentBlock.Draw(11, 11);  // Draw the current block in play.
    
    // Position the preview of the next block based on its shape.
    switch (nextBlock.id)
    {
    case 3:
        nextBlock.Draw(255, 415);
        break;
    case 4:
        nextBlock.Draw(255, 405);
        break;
    default:
        nextBlock.Draw(270, 395);
        break;
    }
}

// Handles player input during the game.
void Game::HandleInput()
{
    // Handle repeated key presses for smooth movement.
    for (auto& [key, pressed] : keyPressed) 
    {    
        if (IsKeyUp(key)) 
        {
            // Mark key as released.
            keyPressed[key] = false;
            HandleKeyRelease(key);
        } 
        else if (pressed && IsKeyDown(key) && key != KEY_UP) 
        {
            // Check if enough time has passed for a repeated action.
            double currentTime = GetTime();
            double elapsedTime = currentTime - keyTimers[key];
            if (elapsedTime >= repeatInterval) 
            {
                HandleKeyAction(key);  // Perform the action.
                keyTimers[key] = currentTime;  // Reset the timer.
            }
        }
    }

    // Handle single key presses.
    int key = GetKeyPressed();
    if (key != 0) 
    {
        if(key == KEY_P) 
        {
            Pause();  // Pause the game if "P" is pressed.
        }
        else 
        {
            // Register the key press and perform the action.
            keyPressed[key] = true; 
            keyTimers[key] = GetTime(); 
            HandleKeyAction(key); 
        }
    }
}

// Executes actions based on the key pressed.
void Game::HandleKeyAction(int key)
{
    switch (key) 
    {
        case KEY_LEFT:
            MoveBlockLeft();  // Move block left.
            break;
        case KEY_RIGHT:
            MoveBlockRight();  // Move block right.
            break;
        case KEY_DOWN:
            MoveBlockDown();  // Soft drop block.
            UpdateScore(0, 1);  // Update score for soft drop.
            break;
        case KEY_UP:
            RotateBlock();  // Rotate block.
            break;
        default:
            break;
    }
}

// Handles key release events.
void Game::HandleKeyRelease(int key)
{
    keyPressed[key] = false;  // Mark key as released.
}

// Moves the current block left.
void Game::MoveBlockLeft() 
{   
    if(!gameOver)
    {
        currentBlock.Move(0, -1);  // Move block left.
        // Undo the move if it causes a collision.
        if(isBlockOutside() || !BlockFits()) 
        {
            currentBlock.Move(0, 1);
        }
    }
}

// Moves the current block right.
void Game::MoveBlockRight() 
{
    if(!gameOver) 
    {
        currentBlock.Move(0, 1);  // Move block right.
        // Undo the move if it causes a collision.
        if(isBlockOutside() || !BlockFits()) 
        {
            currentBlock.Move(0, -1);
        }
    }
}

// Moves the current block down.
void Game::MoveBlockDown() 
{   
    if(!gameOver && !paused) 
    {
        currentBlock.Move(1, 0);  // Move block down.
        // Lock the block if it cannot move further.
        if(isBlockOutside() || !BlockFits()) 
        {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

// Calculates the fall interval based on the current level.
double Game::CalculateFallInterval()
{
    return std::max(minFallInterval, maxFallInterval *  pow(minFallInterval/maxFallInterval, level / totalLevels));
}

// Checks if the block is outside the grid.
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

// Rotates the current block.
void Game::RotateBlock()
{   
    if(!gameOver) 
    {
        currentBlock.Rotate();  // Rotate the block.
        // Undo rotation if it causes a collision.
        if(isBlockOutside() || !BlockFits()) 
        {
            currentBlock.UndoRotate();
        }
        else 
        {
            PlaySound(rotateSound);  // Play rotation sound if successful.
        }
    }
}

// Locks the current block in place on the grid.
void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition();

    // Place the block on the grid.
    for(Position item : tiles) 
    {
        grid.grid[item.row][item.col] = currentBlock.id;  
    }
    currentBlock = nextBlock;  // Replace with the next block.
    if(!BlockFits())
    {
        gameOver = true;  // End the game if the new block doesn't fit.
    }
    nextBlock = GetRandomBlock();  // Get a new block.
    
    // Clear completed rows and play sound.
    int rowsCompleted = grid.ClearFullRows();
    if(rowsCompleted > 0) 
    {
        PlaySound(completeSound);
        UpdateScore(rowsCompleted, 0);  // Update score for rows cleared.
    }
}

// Checks if the current block fits in the grid.
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

// Resets the game to the initial state.
void Game::Reset()
{
    grid.Initialize();  // Clear the grid.
    blocks = GetAllBlocks();  // Refill the block list.
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;  // Reset score.
    level = 0;  // Reset level.
    rowCompletedOverall = 0;  // Reset completed rows.
}

// Updates the score and handles level progression.
void Game::UpdateScore(int rowsCompleted, int moveDownPoints)
{   
    int basePoints = 0;
    // Calculate score based on rows completed.
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
        basePoints += 1200;  // Bonus for clearing 4 rows.
        break;
    default:
        break;
    }

    // Update the total score and rows completed.
    score += basePoints * (level + 1);
    score += moveDownPoints;
    rowCompletedOverall += rowsCompleted;

    // Level up after every 10 rows.
    if(rowCompletedOverall >= (level + 1) * 10) 
    {
        level++;
    }

    // End the game if the max level is reached.
    if(level == 30) {
        gameOver = true;
    }
}

// Pauses or unpauses the game.
void Game::Pause()
{
    paused = !paused;  // Toggle the paused state.
}
