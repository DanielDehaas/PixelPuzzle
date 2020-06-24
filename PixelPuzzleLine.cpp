#include "PixelPuzzleLine.hpp"
/**
 * Default constructor initializes a zero line or empty line.
 */
PixelPuzzleLine::PixelPuzzleLine()
{
    const int defaultSize = 8;
    bool defaultDirection = false; // 0 is column 1 is row
    int defaultOrder = 0;
    std::vector<int> zeroBlock = {0};
    //std::vector<std::vector<int> > zeroBlockSpace { {0,0,0,0,0,0,0,0} };
    //PixelPuzzleLine(defaultSize, defaultDirection, defaultOrder, zeroBlock, zeroBlockSpace);
    this->dimension = defaultSize;
    this->direction = defaultDirection;
    this->order     = defaultOrder;
    this->segments  = zeroBlock;
    this->segmentSolutionSpace = initializeBlockSpace(defaultSize, zeroBlock);
    this->lineInProgress = std::vector<unsigned short int>(defaultSize, 2);
}

/**
 * Parameterized constructor builds a line given parameterized input.
 */
PixelPuzzleLine::PixelPuzzleLine(int lineLength, bool dir, int rank, std::vector<int> blockSize)
{
    //this->SetLine(lineLength, dir, rank, blockSize, blockSpace);
    this->dimension = lineLength;
    this->direction = dir;
    this->order     = rank;
    this->segments  = blockSize;
    this->segmentSolutionSpace = initializeBlockSpace(lineLength, blockSize);
    this->lineInProgress = std::vector<unsigned short int>(lineLength, 2);
}

/**
 * Helper function for constructor. Uses simple logic to create a naive solution space for each segment (digit.)
 * The solution space is a vector of int vectors. Each inner vector contains the potential indices where the segment
 * could exist in a solution.
 * The function works through each segment for that line determining the left and right bounds.
 * @param:int lineLength is the length of the line and the dimensions of the puzzle.
 * @param:vector blockSize is each segment, given as its length, which exist in the line.
 * @return:2d vector which is set as PixelPuzzleLine.segmentSolutionSpace
 */
std::vector<std::vector< int > > PixelPuzzleLine::initializeBlockSpace(int lineLength, std::vector<int> blockSize)
{

     std::vector<std::vector<int> > blockSpace;
    // working left to right assign indices where segment could possibly exist
    if (blockSize[0] == 0) {
        blockSpace.push_back(std::vector<int> ());
        for (int i = 0; i < lineLength; i++) {
            blockSpace[0].push_back(0);
        }
    } else {
        // set variables
        uint blocks = blockSize.size();
        uint blocksum = 0;
        for (uint i = 0; i < blocks; i++) {
            blocksum += blockSize[i];
        }
        uint buffer = blocks - 1;
        uint leftBound = 0;
        uint rightBound;
        for (uint i = 0; i < blocks; i++) {
            blockSpace.push_back(std::vector<int> () );
            //set lb and rb
            rightBound = lineLength + leftBound + blockSize[i] -blocksum - buffer;
            //std::cout << "[" << leftBound << ":" << rightBound << "]" << std::endl;
            for (uint j = leftBound; j < rightBound; j++) {
                blockSpace[i].push_back(j);
            }
            leftBound += blockSize[i] + 1;
        }
    }

    return blockSpace;
}

/**
 * //TODO: change return to changed flag bool type
 * Inductively fills cels which have to be filled.
 * This is done by
 * 
 */
std::vector<unsigned short int> PixelPuzzleLine::inductiveSegmentFill()
{
    // int dimension;
    // std::vector<int> segments;                              //
    // std::vector<std::vector<int> > segmentSolutionSpace;    //
    // std::vector<unsigned short int> lineInProgress;         //
//    bool changes = false;
    for(uint i = 0; i < this->segments.size(); i++) {
        std::cout << i << ": ";
        if (this->segments[i] > (int)(this->segmentSolutionSpace[i].size() / 2) ) {
//            changes = true;
            int endBuffer = this->dimension - this->segments[i];
            int leftBound = this->segmentSolutionSpace[i][0] + endBuffer;
            int rightBound = this->segmentSolutionSpace[i].back() - endBuffer;
            std::cout << endBuffer << " eb, " << leftBound << " lb, " << rightBound << " rb" << std::endl;
            for (int cel = leftBound; cel <= rightBound; cel++) {
                this->lineInProgress[cel] = 1;
            }
        }
    }
    std::cout << "l.i.p.: ";
    for (uint i = 0; i < this->lineInProgress.size(); i++) {
        std::cout << this->lineInProgress[i] << " ";
    }
    std::cout << " fin" << std::endl;
    return this->lineInProgress;
    
}

/**
 * TODO: break this into smaller pieces
 * Function to print all the information about the line - mostly for development
 */
void PixelPuzzleLine::printLine()
{
    std::string singleOrPlural;
    if (this->segments.size() == 1 && this->segments[0] != 0) {
        singleOrPlural = "segment";
    } else {
        singleOrPlural = "segments";
    }
    std::cout << "Line length: " << this->dimension << std::endl;
    std::cout << "Line is " << ((this->direction) ? "column" : "row") << " number "<< this->order << " of " << this->dimension << std::endl;
    //std::cout << "Line has " << ((this->segments[0] == 0) ? 0 : this->segments.size()) << " " << singleOrPlural << std::endl;
    if (this->segments[0] !=0 ) {
        std::cout << "Line has " << this->segments.size() << " " << singleOrPlural << std::endl;
        std::cout << "of size: ";
        if (this->segments.size() == 1) {
            std::cout << segments[0] << std::endl;
        } else if (this->segments.size() == 2) {
            std::cout << segments[0] << " and " << segments[1] << std::endl;
        } else {
            uint iter = 0;
            while (iter < segments.size() - 1) {
                std::cout << segments[iter++] << ", ";
            }
            std::cout << "and " << segments[iter] << std::endl;
        }
    } else {
        std::cout << "Line has 0 segments" << std::endl;
    }
    std::cout << "Current line is: ";
    for (uint i = 0; i < this->lineInProgress.size(); i++) {
        std::cout << lineInProgress[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Line solution space: " << std::endl;
    for (uint i = 0; i < this->segmentSolutionSpace.size(); i++) {
        std::cout << this->segments[i] << ": ";
        for (uint j = 0; j < this->segmentSolutionSpace[i].size(); j++) {
            std::cout<< this->segmentSolutionSpace[i][j]<< " ";
        }
        std::cout << std::endl;
    }

    // std::cout << "testing vector.back(): " << std::endl;
    // for (uint i = 0; i < this->segmentSolutionSpace.size(); i++) {
    //     std::cout << this->segments[i] << ": ";
    //     std::cout << this->segmentSolutionSpace[i].back() << ", ";
    //     std::cout << std::endl;
    // }
}