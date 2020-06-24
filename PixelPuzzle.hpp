#include <string>
#include <iostream>
#include <vector>
#include "PixelPuzzleLine.hpp"

#ifndef PIXEL_PUZZLE_H
#define PIXEL_PUZZLE_H

class PixelPuzzle
{
public:
    PixelPuzzle();
    PixelPuzzle(int puzzleDimensions, std::vector<std::vector<int>> columns, std::vector<std::vector<int>> rows);


    //TODO: rewrite setters/getters
    // accessors
    int getDimensions()            const {return dimensions;};
    std::vector<PixelPuzzleLine> getColumnSolutionSpace() const   {return columnSolutionSpace;};
    std::vector<PixelPuzzleLine> getRowSolutionSpace() const      {return rowSolutionSpace;};
    //std::vector<bool> getSolution()   const {return solution;};
    //std::vector<bool> getExes()       const {return exes;};

    // mutators
    void setDimensions (int puzzleDimensions) {dimensions = puzzleDimensions;};
    void setColumnSolutionSpace (std::vector<PixelPuzzleLine> columns) {columnSolutionSpace = columns;};
    void setRowSolutionSpace (std::vector<PixelPuzzleLine> rows) {rowSolutionSpace = rows;};

    void runInductiveFill();
    void printLine(std::vector<unsigned short int>);
private:
    int dimensions;
    std::vector<PixelPuzzleLine> columnSolutionSpace;
    std::vector<PixelPuzzleLine> rowSolutionSpace;
    std::vector<bool> solution;
    std::vector<int> exes;

    // member functions
    void updateSolutionSpace(bool direction, int order, std::vector<int>);

    //solvers
    

    

};

#endif