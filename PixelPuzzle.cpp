#include "PixelPuzzle.hpp"

PixelPuzzle::PixelPuzzle()
{
    //PixelPuzzleLine(int lineLength, bool dir, int rank, std::vector<int> blockSize);
    /**
    *int dimensions;
    *std::vector<PixelPuzzleLine> columnSolutionSpace;
    *std::vector<PixelPuzzleLine> rowSolutionSpace;
    *std::vector<bool> solution;
    *std::vector<bool> exes;
    */
    int TEST_DIMENSIONS = 8;
    // std::vector<std::string> TEST_COlUMNS = {"5", "3", "3", "4", "4", "3", "3", "5"};
    std::vector<std::vector<int> > TEST_COlUMNS = {{5}, {3}, {3}, {4}, {4}, {3}, {3}, {5}};
    // std::vector<std::string> TEST_ROWS = {"2", "4", "6", "8", "2, 2", "1, 1", "1, 1", "1, 1"};
    std::vector<std::vector<int> > TEST_ROWS = {{2}, {4}, {6}, {8}, {2, 2}, {1, 1}, {1, 1}, {1, 1}};
    this->dimensions = TEST_DIMENSIONS;
    for (uint i = 0; i < TEST_COlUMNS.size(); i++) {
        this->columnSolutionSpace.push_back(PixelPuzzleLine(TEST_DIMENSIONS, false, i, TEST_COlUMNS[i]));
    }
    for (uint i = 0; i < TEST_ROWS.size(); i++) {
        this->rowSolutionSpace.push_back(PixelPuzzleLine(TEST_DIMENSIONS, true, i, TEST_ROWS[i]));
    }
//    this->exes = std::vector<int>( (this->dimensions * this->dimensions), 2);
    this->solution = std::vector<std::vector<int> >(TEST_DIMENSIONS, std::vector<int>(TEST_DIMENSIONS, -1));
    // std::cout << "constructor" << std::endl;
    // for (uint i = 0; i < this->solution.size(); i++) {
    //     for (uint j = 0; j < this->solution[i].size(); j++) {
    //         std::cout << this->solution[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

}

PixelPuzzle::PixelPuzzle(int puzzleDimensions, std::vector<std::vector<int>> columns, std::vector<std::vector<int>> rows)
{
    this->dimensions = puzzleDimensions;
    for (uint i = 0; i < columns.size(); i++) {
        this->columnSolutionSpace.push_back(PixelPuzzleLine(puzzleDimensions, false, (int)i, columns[i]));
    }
    for (uint i = 0; i < rows.size(); i++) {
        this->rowSolutionSpace.push_back(PixelPuzzleLine(puzzleDimensions, true, (int)i, rows[i]));
    }
    //this->exes = std::vector<int>( (this->dimensions * this->dimensions), 2);
    this->solution = std::vector<std::vector<int> >(this->dimensions, std::vector<int>(this->dimensions, -1));
}

void PixelPuzzle::updateSolutionSpace(bool direction, int order, std::vector<int>)
{
    if (direction) {
    // row loop
    //int rowAddition = this->dimensions * order;
    
    } else {
    // column loop

    }



}

void PixelPuzzle::runInductiveFill()
{
    for (int i = 0; i < this->dimensions; i++) {
        this->columnSolutionSpace[i].inductiveSegmentFill();
        //this->printLine(this->columnSolutionSpace[i].getLineInProgress());
    }
}

void PixelPuzzle::printLine(std::vector<unsigned short int> line) 
{
    for(uint i = 0; i < line.size(); i++) {
        std::cout << line[i] << " ";
    }
    std::cout << std::endl;
}