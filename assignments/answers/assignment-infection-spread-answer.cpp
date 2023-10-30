#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

class ColonialOrganism {
public:
    ColonialOrganism() {};
    ColonialOrganism(double initialInfection) {
        infection_ = initialInfection;
    }
    void progress() {
        if (infection_ > 0.0) {
            infection_ += infection_ * 0.1 + 0.01;
            limitInfection();
        }
    }
    void spread(double amount) {
        infection_ += amount;
        limitInfection();
    }

    void setInfection(double amount) {
        infection_ = amount;
    }

    double getInfection() {
        return infection_;
    }

    double getTransmissionRate() {
        return transmissionRate_;
    }

private:

    void limitInfection() {
        if (infection_ > 1.0)
            infection_ = 1.0;
    }

    double infection_ = 0.0;
    double transmissionRate_ = 0.01;

};

class Colony {
public:
    // constructor
    Colony(unsigned int height, unsigned int width) {
        // set width and height of the grid
        width_ = width;
        height_ = height;

        std::vector<std::vector<ColonialOrganism>> cols;

        // populate the grid
        for (unsigned int i = 0; i < height; ++i) {
            std::vector<ColonialOrganism> row;
            for (unsigned int j = 0; j < width; ++j) {
                row.emplace_back(ColonialOrganism(0.0));

            }
            cols.push_back(row);
        }
        grid_ = cols;

    }


    void propagate() {

        // initialize the new state of the grid
        std::vector<std::vector<ColonialOrganism>> newGrid = grid_;

        // loop through all cells
        for (int i = 0; i < height_; ++i) {
            for (int j = 0; j < width_; ++j) {
                //std::cout << i << ", " << j << std::endl;
                spread(i, j, newGrid);
            }
        }

        for (int i = 0; i < height_; ++i) {
            for (int j = 0; j < width_; ++j) {
                newGrid[i][j].progress();
            }
        }


        grid_ = newGrid;

    }

    // set infection of a cell in the current grid
    void setInfection(unsigned int i, unsigned int j, double infection) { grid_[i][j].setInfection(infection); }

    // print the current infection in a grid by mapping the double value to integers 0-9 and X
    void printGrid() {
        for (int i = 0; i < height_; ++i) {
            for (int j = 0; j < width_; ++j) {
                double infection = grid_[i][j].getInfection();
                char infectionSeverity = '0';
                if (infection == 0.0) {
                    infectionSeverity = '0';
                }
                else if (infection < 0.1) {
                    infectionSeverity = '1';
                }
                else if (infection < 0.2) {
                    infectionSeverity = '2';
                }
                else if (infection < 0.3) {
                    infectionSeverity = '3';
                }
                else if (infection < 0.4) {
                    infectionSeverity = '4';
                }
                else if (infection < 0.5) {
                    infectionSeverity = '5';
                }
                else if (infection < 0.6) {
                    infectionSeverity = '6';
                }
                else if (infection < 0.7) {
                    infectionSeverity = '7';
                }
                else if (infection < 0.8) {
                    infectionSeverity = '8';
                }
                else if (infection < 0.9) {
                    infectionSeverity = '9';
                }
                else {
                    infectionSeverity = 'X';
                }
                std::cout << infectionSeverity;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

private:


    void spread(int i, int j, std::vector<std::vector<ColonialOrganism>>& newGrid) {

        double amount = grid_[i][j].getInfection() * grid_[i][j].getTransmissionRate();

        for (int x = -1; x < 2; ++x) {
            for (int y = -1; y < 2; ++y) {

                if (x == 0 && y == 0)
                    continue;

                if (i + x < 0 || i + x > height_ - 1 || j + y < 0 || j + y > width_ - 1)
                    continue;

                newGrid[i + x][j + y].spread(amount);
            }
        }

    }

    // grid holding the current state of all cells
    std::vector<std::vector<ColonialOrganism>> grid_;
    // dimensions of the grid
    unsigned int width_ = 128;
    unsigned int height_ = 128;
};


int main()
{
    // 128x128 can be specified, but for demonstration a smaller grid is easier
    Colony colony(16, 32);

    colony.setInfection(3, 3, 0.001);
    colony.printGrid();

    for (unsigned int i = 0; i < 50; ++i) {
        colony.propagate();
        colony.printGrid();
    }

}