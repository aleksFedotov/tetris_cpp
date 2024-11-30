#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>
#include <string>

// Global variable to track the time of the last update.
double lastUpdateTime = 0;

// Function to determine if an event should be triggered based on the interval.
bool EventTriggered(double interval) 
{
   double currentTime = GetTime();  // Get the current time.
   if(currentTime - lastUpdateTime >= interval)  // Check if the interval has passed.
   {
      lastUpdateTime = currentTime;  // Update the last update time.
      return true;  // Event triggered.
   }
   return false;  // Event not triggered.
}

int main() 
{
   // Initialize the game window.
   InitWindow(500, 820, "Tetris");
   SetTargetFPS(60);  // Set the frame rate to 60 FPS.

   // Load the custom font for the game UI.
   Font font = LoadFontEx("Font/monogram.ttf", 60, 0, 0);

   // Initialize the game.
   Game game = Game();

   // Main game loop.
   while(WindowShouldClose() == false) // Run until the window is closed.
   {
      UpdateMusicStream(game.music);  // Update the background music stream.

      game.HandleInput();  // Handle user input.

      double fallInterval = game.CalculateFallInterval();  // Calculate the block fall interval.
      if(EventTriggered(fallInterval))  // Check if it's time for the block to fall.
      {
         game.MoveBlockDown();  // Move the block down.
      }

      // Begin drawing the frame.
      BeginDrawing();
      ClearBackground(darkBlue);  // Clear the background with a dark blue color.

      // Display "Game Over" message if the game is over.
      if(game.gameOver) {
         DrawTextEx(font, "Game Over", {320, 525}, 38, 2, WHITE);
      }
      
      // Display "Pause" message if the game is paused.
      if(game.paused) {
         DrawTextEx(font, "Pause", {360, 525}, 38, 2, WHITE);
      }

      // Draw the score section.
      DrawTextEx(font, "SCORE", {365, 15}, 38, 2, WHITE);
      DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);  // Background rectangle for score.
      char scoreText[10];
      sprintf(scoreText, "%d", game.score);  // Convert the score to a string.
      Vector2 scoreTextSize = MeasureTextEx(font, scoreText, 38, 2);
      DrawTextEx(font, scoreText, {320 + (170 - scoreTextSize.x) / 2, 65}, 38, 2, WHITE);

      // Draw the level section.
      DrawTextEx(font, "LEVEL", {365, 120}, 38, 2, WHITE);
      DrawRectangleRounded({320, 165, 170, 60}, 0.3, 6, lightBlue);  // Background rectangle for level.
      char levelText[2];
      sprintf(levelText, "%d", game.level);  // Convert the level to a string.
      Vector2 levelTextSize = MeasureTextEx(font, levelText, 38, 2);
      DrawTextEx(font, levelText, {320 + (170 - levelTextSize.x) / 2, 175}, 38, 2, WHITE);

      // Draw the lines cleared section.
      DrawTextEx(font, "LINES", {365, 230}, 38, 2, WHITE);
      DrawRectangleRounded({320, 275, 170, 60}, 0.3, 6, lightBlue);  // Background rectangle for lines.
      char linesText[3];
      sprintf(linesText, "%d", game.rowCompletedOverall);  // Convert the total lines cleared to a string.
      Vector2 linesTextSize = MeasureTextEx(font, linesText, 38, 2);
      DrawTextEx(font, linesText, {320 + (170 - linesTextSize.x) / 2, 285}, 38, 2, WHITE);

      // Draw the next block section.
      DrawTextEx(font, "NEXT", {370, 340}, 38, 2, WHITE);
      DrawRectangleRounded({320, 380, 170, 100}, 0.3, 6, lightBlue);  // Background rectangle for next block.

      // Draw the controls section.
      DrawTextEx(font, "CONTROLS", {150, 630}, 38, 2, WHITE);
      DrawTextEx(font, "LEFT/RIGHT ARROW - MOVE LEFT/RIGHT", {20, 690}, 24, 2, WHITE);
      DrawTextEx(font, "UP ARROW - ROTATE CLOCKWISE", {20, 720}, 24, 2, WHITE);
      DrawTextEx(font, "DOWN ARROW - DOWN BLOCK", {20, 750}, 24, 2, WHITE);
      DrawTextEx(font, "P - PAUSE GAME", {20, 780}, 24, 2, WHITE);

      // Draw the game grid and current block.
      game.Draw();

      EndDrawing();  // End drawing the frame.
   }

   // Close the game window and clean up resources.
   CloseWindow();
}