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
 * TODO: this should be updated with a call to have intersecting cels filled in the perpendicular column/row
 *          currently this logic is only handled in the puzzles update solution space -
 *       This could be done by comparing the lineInProgress before and after running inductiveSegmentFill - 
 *          if there is a difference then the perpendicular line would be updated.
 *       THe wrong way to do this seems to be to compare all rows with all columns after runInductiveFill completes
 * Has each line run inductive fill
 * Loops through row and column spaces and updates the working solution
 */
void PixelPuzzle::runInductiveFill()
{
    for (int i = 0; i < this->dimensions; i++) {
// ------pseudo code for intersecting fill
/*       std::vector<int> tempLIP = this->rowSolutionSpace[i].getLineInProgress;
        if (tempLIP != this->rowSolutionSpace[i].inductiveSegmentFill()) {
                this->updateSolutionSpace(this->rowSolutionSpace[i].getDirection(), 
                                       this->rowSolutionSpace[i].getOrder(), 
                                        this->rowSolutionSpace[i].getLineInProgress());
                for(i = 0; i < this->dimensions; i++) {
                    if (tempLip[i] != this->rowSolutionSpace[i].getLineInProgress()[i]) {
                        update cell in perpendicular line
                    }
                }
        }
*/
        this->rowSolutionSpace[i].inductiveSegmentFill();
        this->updateSolutionSpace(this->rowSolutionSpace[i].getDirection(), 
                                    this->rowSolutionSpace[i].getOrder(), 
                                    this->rowSolutionSpace[i].getLineInProgress());
    }
    for (int i = 0; i < this->dimensions; i++) {
        this->columnSolutionSpace[i].inductiveSegmentFill();
        this->updateSolutionSpace(this->columnSolutionSpace[i].getDirection(), 
                                    this->columnSolutionSpace[i].getOrder(), 
                                    this->columnSolutionSpace[i].getLineInProgress());
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

void PixelPuzzle::printLine() 
{
    for (uint i = 0; i < this->solution.size(); i++) {
        for (uint j = 0; j < this->solution.size(); j++) {
            if (solution[i][j] != -1 ) {
                std::cout << " ";
            }
            std::cout << solution[i][j] << " ";
        }
        std::cout << std::endl;
    }
}