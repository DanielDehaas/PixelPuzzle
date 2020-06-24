#include <string>
#include <iostream>
#include <vector>

#ifndef PIXEL_PUZZLE_LINE_H
#define PIXEL_PUZZLE_LINE_H

class PixelPuzzleLine
{
public:
    PixelPuzzleLine();
    PixelPuzzleLine(int lineLength, bool dir, int rank, std::vector<int> blockSize);

    // accessors
    int getDimension()              const {return this->dimension;};
    bool getDirection()             const {return this->direction;};
    int getOrder()                  const {return this->order;};
    std::vector<int> getSegments()  const {return this->segments;};
    std::vector<std::vector<int> > getSegmentSolutionSpace()    const {return this->segmentSolutionSpace;};
    std::vector<unsigned short int> getLineInProgress()         const {return this->lineInProgress;};

    // mutators
    void setDimension(int lineLength) {dimension = lineLength;};
    void setSegments(std::vector<int> blockSize) {segments = blockSize;};
    //void setSegmentSolutionSpace(std::vector<std::vector<int> > blocks) {segmentSolutionSpace = blocks;};

    
    void printLine();


    std::vector<unsigned short int> inductiveSegmentFill();

private:
    // fields
    int dimension;
    bool direction;
    int order;
    std::vector<int> segments;
    std::vector<std::vector<int> > segmentSolutionSpace;
    std::vector<unsigned short int> lineInProgress;

    // member functions
    std::vector<std::vector< int > > initializeBlockSpace(int lineLength, std::vector<int> blockSize);

    //TODO: write a line validation function (ie. line segments > dimension)

};
#endif