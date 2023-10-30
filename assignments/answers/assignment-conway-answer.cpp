#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

class GameOfLife {
public:
    // constructor
    GameOfLife(unsigned int rows, unsigned int cols) {
        // set width and height of the grid where the game takes place
        width_ = cols;
        height_ = rows;

        // populate the grid with boolean false values
        for (unsigned int i = 0; i < height_; ++i) {
            std::vector<bool> row(width_, false);
            grid_.push_back(row);
        }
        // push the full-false state to grid history
        gridHistory_.push_back(grid_);


    }

    // update cells in the grid; they either remain alive, die, or come back to life depending on how many neighbouring live cells they have
    void update(unsigned int steps) {


        for (unsigned int step = 0; step < steps; ++step) {

            // push the previous grid state to grid history
            gridHistory_.push_back(grid_);

            // initialize the new state of the grid
            std::vector<std::vector<bool>> newGrid = grid_;

            // loop through all cells, calculate how many neighbours they have and update their state (false=dead, true=alive)
            for (int i = 0; i < height_; ++i) {
                for (int j = 0; j < width_; ++j) {
                    // count number of alive neighbours
                    unsigned int aliveNeighbours = checkNeighbours(i, j);

                    // get current state
                    bool currentState = grid_[i][j];
                    if (currentState && (aliveNeighbours == 2 || aliveNeighbours == 3)) {
                        // alive cells with 2 or 3 neighbours remain alive
                    }
                    else if (!currentState && aliveNeighbours == 3)
                        newGrid[i][j] = true; // dead cells with exactly 3 neighbours come back to life
                    else
                        newGrid[i][j] = false; // others die
                }
            }

            // print the grid from the previous step
            std::cout << "Step: " << step << std::endl;
            printCurrentGrid();

            // if no change occurred, print the most recent one and break out of the loop
            if (newGrid == grid_) {
                std::cout << "Stable state achieved at step " << step << ", breaking from loop!" << std::endl;
                gridHistory_.push_back(newGrid);
                printCurrentGrid();
                break;
            }

            // reassign grid_
            grid_ = newGrid;

        }
    }

    // set state of cells in the current grid
    void setState(unsigned int i, unsigned int j, bool state) { grid_[i][j] = state; }

    // print the state of cells in the current grid
    void printCurrentGrid() {
        printGrid(gridHistory_.size() - 1);
    }

    // print the state of cells in any grid in grid history
    void printState(unsigned int s) { printGrid(s); }

private:

    // print the state of cells in the given state in grid history
    void printGrid(unsigned int s) {
        for (int i = 0; i < height_; ++i) {
            for (int j = 0; j < width_; ++j) {
                std::cout << (int)gridHistory_[s][i][j];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    // count how many live neighbours a cell has
    unsigned int checkNeighbours(int i, int j) {
        unsigned int liveNeighbours = 0;

        for (int x = -1; x < 2; ++x) {
            for (int y = -1; y < 2; ++y) {

                if (x == 0 && y == 0)
                    continue;


                if (i + x < 0 || i + x >= height_ || j + y < 0 || j + y >= width_)
                    continue;

                if (grid_[i + x][j + y])
                    ++liveNeighbours;

            }
        }

        return liveNeighbours;

    }

    // grid holding the current state of all cells
    std::vector<std::vector<bool>> grid_;
    // dimensions of the grid
    unsigned int width_ = 16;
    unsigned int height_ = 16;
    // a container holding all states
    std::vector<std::vector<std::vector<bool>>> gridHistory_;
};

int main()
{
    // initialize random seed
    srand(time(NULL));

    // define grid dimensions
    unsigned int rows = 6;
    unsigned int cols = 8;

    // create a new object and set initial state
    GameOfLife gol(rows, cols);
    for (unsigned int i = 0; i < rows; ++i) {
        for (unsigned int j = 0; j < cols; ++j) {
            gol.setState(i, j, (bool)(rand() % 2));
        }
    }

    // update for 100 steps or until no change occurs
    gol.update(100);

}
