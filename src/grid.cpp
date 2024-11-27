#include "grid.h"
#include <iostream>
#include <raylib.h>

Grid::Grid() {
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    Initialize();
    colors = GetCellColors();

}


void Grid::Initialize() {
    for(int row = 0; row < numRows; row++ ){
        for ( int col = 0; col < numCols; col++) {
            grid[row][col] = 0;

        }
    }
}

void Grid::Print() {
    for( int row = 0; row < numRows; row++){
        for(int col = 0; col < numCols; col++) {
            std::cout << grid[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::Draw() {
    for( int row = 0; row < numRows; row++){
        for(int col = 0; col < numCols; col++) {
           int cellColor = grid[row][col];
           DrawRectangle(col*cellSize+11, row*cellSize+11, cellSize-1, cellSize-1, colors[cellColor]);
           
        }
        
    }
}

bool Grid::IsCellOutside(int row, int col)
{   
    if(row >= 0 && row < numRows && col >=0 && col < numCols) {
        return false;

    }

    return true;
}

bool Grid::IsCellEmpty(int row, int col)
{
    if(grid[row][col] == 0) {
        return true;
    }
    return false;
}

int Grid::ClearFullRows()
{   
    int completedRows = 0;
    for(int row = numRows -1; row >= 0; row--) {
        if(IsRowCompleted(row)) 
        {
            ClearRow(row);
            completedRows++;
        }
        else if(completedRows > 0) 
        {
            MoveRowDown(row, completedRows);
        }
    }

    return completedRows;
}

bool Grid::IsRowCompleted(int row)
{   
    for(int col =0; col < numCols; col++)
    {
        if(grid[row][col] == 0) 
        {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row)
{
    for(int col = 0; col < numCols; col++) 
    {
        grid[row][col] = 0;    
    }
}

void Grid::MoveRowDown(int row, int numRows)
{
    for( int col = 0; col < numCols; col++)
    {
        grid[row+numRows][col] = grid[row][col];
         grid[row][col] = 0;
    }
}
