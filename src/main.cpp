#include <raylib.h>
#include "grid.h"
#include "blocks.cpp"



int main() 
{
   // Colors 
   Color darkBlue = {44,44,127,255};
   InitWindow(300, 600, "Tetris");
   SetTargetFPS(60);
   Grid grid = Grid();
   grid.Print();

   LBLock block = LBLock();
   while(WindowShouldClose() == false) {
      BeginDrawing();
      ClearBackground(darkBlue);
      grid.Draw();
      block.Draw();

      EndDrawing();
   }

   CloseWindow();
}