#include <string>
#include <iostream>
#include <vector>
#include "PixelPuzzle.hpp"
#include "PixelPuzzleLine.hpp"

/*
    variables
*/
std::string intro = "The Picture Cross Puzzle Solver";
std::string details = "This program solves puzzles from the Android app Picture Cross.";
bool test = true;
std::string test_text = "******** Test Mode ********";
int TEST_DIMENSIONS = 8;
std::string instructions = "Enter new for a new puzzle or demo to see a demonstration";
std::string user_input = "";
std::string new_puzzle = "The puzzle board is square grid. Each column and row has one or more digits. Each digit represents a sequence of filled cells. The puzzle is solved when each row and column has the same number of cells filled as indicated by the digit.";
std::string enter_dimensions = "Enter the dimensions of the puzzle (8, 10, 12, or 15.): ";
std::string enter_columns = "Enter the digits for each column. Seperate digits with a comma and seperate columns with a semicolon :";
std::string enter_rows = "Enter the digits for each row. Seperate digits with a comma and seperate columns with a semicolon :";
std::string solving = "Solving puzzle...";

int main() {
    bool running = true;
    
    while(running) {
        // 3 stages: 
        //      puzzle setup: intro text- input to setup puzzle or test mode
        //      solving puzzle: calls puzsolver class to 
        //      puzzle solved: display solved puzzle and time to solve. prompt for another run or quit
        std::cout << intro << std::endl;
        if (test) {
            std::cout << test_text << std::endl;
            std::cout << "Testing line class .   .   .   " << std::endl;
            std::vector<int> TEST_VEC = std::vector<int>{9, 4};
            //std::vector<std::vector<int> > TEST_VEC2D = std::vector<std::vector<int> >{ {3} };
            //std::vector<std::vector<int> > TEST_VEC2D;

            PixelPuzzleLine testLineDefault  = PixelPuzzleLine();
            testLineDefault.printLine();
            std::cout << std::endl;

            PixelPuzzleLine testLine  = PixelPuzzleLine(TEST_DIMENSIONS, true, 3, TEST_VEC);
            testLine.printLine();
            std::cout << std::endl;


            std::cout << "Testing puzzle class .   .   .   " << std::endl;
            std::cout << "Solving puzzle of " << TEST_DIMENSIONS << " x " << TEST_DIMENSIONS << " dimensions..." <<  std::endl;
            PixelPuzzle testPuz = PixelPuzzle();

            testPuz.runInductiveFill();
            testPuz.printLine();
        }

        running = false;
    }

    std::cout << "goodbye" << std::endl;

    int dim = 15;
    std::cout << dim /2 << std::endl;
    return 0;
}


