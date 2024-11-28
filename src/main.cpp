#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>
#include <string>

double lastUpdateTime = 0;

bool EventTriggered(double interval) 
{
   double currentTime = GetTime();
   if(currentTime - lastUpdateTime >= interval) 
   {
      lastUpdateTime = currentTime;
      return true;
   }

   return false;
}

int main() 
{

   
   InitWindow(500, 620, "Tetris");
   SetTargetFPS(60);

   Font font = LoadFontEx("Font/monogram.ttf", 60, 0,0);

   Game game = Game();

   while(WindowShouldClose() == false) {
      UpdateMusicStream(game.music);
      game.HandleInput();
      double fallInterval = game.CalculateFllInterval();
      if(EventTriggered(fallInterval)) 
      {
         game.MoveBlockDown();
      }
      BeginDrawing();
      ClearBackground(darkBlue);
      if(game.gameOver) {
         DrawTextEx(font, "Game Over", {320,450}, 38, 2, WHITE);
      }
      

      // Score
      DrawTextEx(font, "SCORE", {365,15}, 38, 2, WHITE);
       // Reactangle for score
      DrawRectangleRounded({320,55,170,60}, 0.3, 6, lightBlue);
      char scoreText[10];
      sprintf(scoreText, "%d", game.score);
      Vector2 textSize = MeasureTextEx(font, scoreText, 38,2);
      DrawTextEx(font, scoreText, {320 + (170 - textSize.x)/2,65}, 38, 2, WHITE);

      // Level
      DrawTextEx(font, "LEVEL", {365,120}, 38, 2, WHITE);
      // Reactangle for level
      DrawRectangleRounded({320,165,170,60}, 0.3, 6, lightBlue);
      char levelText[2];
      sprintf(levelText, "%d", game.level);
      DrawTextEx(font, levelText, {320 + (170 - textSize.x)/2,175}, 38, 2, WHITE);
      
      // Lines
      DrawTextEx(font, "LINES", {365,230}, 38, 2, WHITE);
      // Reactangle for level
      DrawRectangleRounded({320,275,170,60}, 0.3, 6, lightBlue);
      char linesText[3];
      sprintf(linesText, "%d", game.rowCompletedOverall);
      DrawTextEx(font, linesText, {320 + (170 - textSize.x)/2,285}, 38, 2, WHITE);


      // Next
      DrawTextEx(font, "NEXT", {370,340}, 38, 2, WHITE);
      // Reactangle for next
      DrawRectangleRounded({320,380,170,100}, 0.3, 6, lightBlue);
      
      
      game.Draw();
      EndDrawing();
   }

   CloseWindow();
}