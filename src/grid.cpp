#include "grid.h"
#include <iostream>
#include <raylib.h>

// Grid class represents the game grid
Grid::Grid() {
  // Initialize grid dimensions and cell size
  numRows = 20;
  numCols = 10;
  cellSize = 30;

  // Initialize the grid cells to empty
  Initialize();

  // Get the color palette for cells
  colors = GetCellColors();
}

// Initializes the grid cells to empty
void Grid::Initialize() {
  for (int row = 0; row < numRows; row++) {
    for (int col = 0; col < numCols; col++) {
      grid[row][col] = 0; // 0 represents an empty cell
    }
  }
}

// Prints the grid to the console for debugging
void Grid::Print() {
  for (int row = 0; row < numRows; row++) {
    for (int col = 0; col < numCols; col++) {
      std::cout << grid[row][col] << " ";
    }
    std::cout << std::endl;
  }
}

// Draws the grid on the screen
void Grid::Draw() {
  for (int row = 0; row < numRows; row++) {
    for (int col = 0; col < numCols; col++) {
      // Get the color for the cell based on its value
      int cellColor = grid[row][col];
      // Draw the cell as a rectangle with the specified color
      DrawRectangle(col * cellSize + 11, row * cellSize + 11, cellSize - 1, cellSize - 1, colors[cellColor]);
    }
  }
}

// Checks if a cell is outside the grid boundaries
bool Grid::IsCellOutside(int row, int col) {
  // If the row and column are within the grid bounds, it's not outside
  if (row >= 0 && row < numRows && col >= 0 && col < numCols) {
    return false;
  }

  return true;
}

// Checks if a cell is empty (has a value of 0)
bool Grid::IsCellEmpty(int row, int col) {
  if (grid[row][col] == 0) {
    return true;
  }
  return false;
}

// Clears completed rows and moves rows down
int Grid::ClearFullRows() {
  int completedRows = 0;
  for (int row = numRows - 1; row >= 0; row--) {
    // If the row is full, clear it and increment the completed rows count
    if (IsRowCompleted(row)) {
      ClearRow(row);
      completedRows++;
    }
    // If there are completed rows above, move rows down to fill the gaps
    else if (completedRows > 0) {
      MoveRowDown(row, completedRows);
    }
  }

  return completedRows;
}

// Checks if a row is full (all cells have non-zero values)
bool Grid::IsRowCompleted(int row) {
  for (int col = 0; col < numCols; col++) {
    if (grid[row][col] == 0) {
      return false;
    }
  }
  return true;
}

// Clears all cells in a row
void Grid::ClearRow(int row) {
  for (int col = 0; col < numCols; col++) {
    grid[row][col] = 0;
  }
}

// Moves a row down by a specified number of rows
void Grid::MoveRowDown(int row, int numRows) {
  for (int col = 0; col < numCols; col++) {
    grid[row + numRows][col] = grid[row][col];
    grid[row][col] = 0;
  }
}