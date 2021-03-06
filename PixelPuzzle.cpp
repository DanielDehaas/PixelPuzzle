#include "PixelPuzzle.hpp"

/**
 * Default constructor builds a "test" puzzle (mailbox from Worlds Biggest Puzzle map)
 */
PixelPuzzle::PixelPuzzle()
{
    int TEST_DIMENSIONS = 8;
    std::vector<std::vector<int> > TEST_COlUMNS = {{5}, {3}, {3}, {4}, {4}, {3}, {3}, {5}};
    std::vector<std::vector<int> > TEST_ROWS = {{2}, {4}, {6}, {8}, {2, 2}, {1, 1}, {1, 1}, {1, 1}};
    this->dimensions = TEST_DIMENSIONS;
    for (uint i = 0; i < TEST_ROWS.size(); i++) {
        this->rowSolutionSpace.push_back(PixelPuzzleLine(TEST_DIMENSIONS, false, i, TEST_ROWS[i]));
    }
        for (uint i = 0; i < TEST_COlUMNS.size(); i++) {
        this->columnSolutionSpace.push_back(PixelPuzzleLine(TEST_DIMENSIONS, true, i, TEST_COlUMNS[i]));
    }
    this->solution = std::vector<std::vector<int> >(TEST_DIMENSIONS, std::vector<int>(TEST_DIMENSIONS, -1));
    // std::cout << "constructor" << std::endl;
    // for (uint i = 0; i < this->solution.size(); i++) {
    //     for (uint j = 0; j < this->solution[i].size(); j++) {
    //         std::cout << this->solution[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

}

/**
 * Parameterized constructor is meant to take a puzzle specs from the user and display a solved depiction
 */
PixelPuzzle::PixelPuzzle(int puzzleDimensions, std::vector<std::vector<int>> columns, std::vector<std::vector<int>> rows)
{
    this->dimensions = puzzleDimensions;
    for (uint i = 0; i < rows.size(); i++) {
        this->rowSolutionSpace.push_back(PixelPuzzleLine(puzzleDimensions, false, (int)i, rows[i]));
    }
    for (uint i = 0; i < columns.size(); i++) {
        this->columnSolutionSpace.push_back(PixelPuzzleLine(puzzleDimensions, true, (int)i, columns[i]));
    }
    this->solution = std::vector<std::vector<int> >(this->dimensions, std::vector<int>(this->dimensions, -1));
}

/**
 * Has each line run inductive fill
 * Loops through row and column spaces and updates the working solution for the puzzle 
 * Also calls the line's updateLineInProgress function to update the cel for the perpendicular line
 */
void PixelPuzzle::runInductiveFill()
{
    for (uint row = 0; row < this->rowSolutionSpace.size(); row++) {
        std::vector<int> tempLIP = this->rowSolutionSpace[row].getLineInProgress();
        printVector(tempLIP);
        std::cout << std::endl;
        printVector(this->rowSolutionSpace[row].getLineInProgress());
        std::cout << std::endl;
        if (tempLIP != this->rowSolutionSpace[row].inductiveSegmentFill()) {
            this->updateSolutionSpace(this->rowSolutionSpace[row].getDirection(), 
                                    this->rowSolutionSpace[row].getOrder(), 
                                    this->rowSolutionSpace[row].getLineInProgress());
            
            for(int rowCel = 0; rowCel < this->dimensions; rowCel++) {
                if (tempLIP[rowCel] != this->rowSolutionSpace[row].getLineInProgress()[rowCel]) {
                    // std::cout << "row " << row << std::endl;
                    // printVector(tempLIP);
                    // std::cout << std::endl;
                    // printVector(this->rowSolutionSpace[rowCel].getLineInProgress());
                    // std::cout << std::endl;
                    // std::cout << rowCel << "|" << this->rowSolutionSpace[row].getOrder() << std::endl;
                    this->columnSolutionSpace[rowCel].setLineInProgressCel(this->rowSolutionSpace[row].getOrder());
                }
            }
        }
    }

    for (uint column = 0; column < this->columnSolutionSpace.size(); column++) {
        std::vector<int> tempLIP(this->columnSolutionSpace[column].getLineInProgress());
        if (tempLIP != this->columnSolutionSpace[column].inductiveSegmentFill()) {
            this->updateSolutionSpace(this->columnSolutionSpace[column].getDirection(), 
                                    this->columnSolutionSpace[column].getOrder(), 
                                    this->columnSolutionSpace[column].getLineInProgress());
            for(int columnCel = 0; columnCel < this->dimensions; columnCel++) {
                if (tempLIP[columnCel] != this->columnSolutionSpace[column].getLineInProgress()[columnCel]) {
                    // std::cout << "column " << column << std::endl;
                    // printVector(tempLIP);
                    // std::cout << std::endl;
                    // printVector(this->columnSolutionSpace[columnCel].getLineInProgress());
                    // std::cout << std::endl;
                    // std::cout << columnCel << "|" << this->columnSolutionSpace[column].getOrder() << std::endl;
                    this->rowSolutionSpace[columnCel].setLineInProgressCel(this->columnSolutionSpace[column].getOrder());
                }
            }
        }
    }
}

void PixelPuzzle::updateSolutionSpace(bool direction, int order, std::vector<int> line)
{
    if (direction) {
    // column loop
        for (uint i = 0; i < line.size(); i++) {
            if (this->solution[i][order] == -1) {
                this->solution[i][order] = line[i];
            }
        }
    } else {
    // row loop
        for (uint i = 0; i < line.size(); i++) {
            if (this->solution[order][i] == -1) {
                this->solution[order][i] = line[i];
            }
        }
    }
}

void PixelPuzzle::printLines() 
{
    std::cout << "Printing Puzzle Solution Space" << std::endl;
    for (uint i = 0; i < this->solution.size(); i++) {
        for (uint j = 0; j < this->solution.size(); j++) {
            if (solution[i][j] != -1 ) {
                std::cout << " ";
            }
            std::cout << solution[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // std::cout << "\nPrinting Puzzle Solution Space using line class" << std::endl;
    // for (uint i = 0; i < this->rowSolutionSpace.size(); i++) {
    //     std::vector<int> liner = this->rowSolutionSpace[i].getLineInProgress();
    //     for (uint j = 0; j < liner.size(); j++) {
    //         if (liner[j] != -1) {
    //             std::cout << " ";
    //         }
    //         std::cout << liner[j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << "\nPrinting Puzzle Solution Space using line class" << std::endl;
    // for (uint i = 0; i < this->columnSolutionSpace.size(); i++) {
    //     std::vector<int> liner = this->columnSolutionSpace[i].getLineInProgress();
    //     for (uint j = 0; j < liner.size(); j++) {
    //         if (liner[j] != -1) {
    //             std::cout << " ";
    //         }
    //         std::cout << liner[j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
}

void PixelPuzzle::printVector(std::vector<int> liner) {
        for (uint j = 0; j < liner.size(); j++) {
            if (liner[j] != -1) {
                std::cout << " ";
            }
            std::cout << liner[j] << " ";
        }
}