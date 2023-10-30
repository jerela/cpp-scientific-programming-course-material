#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "C:/Users/StudentMcStudentson/Downloads/dlib-19.24/dlib/mlp.h"
#include "C:/Users/StudentMcStudentson/Downloads/dlib-19.24/dlib/clustering.h"
#include "C:/Users/StudentMcStudentson/Downloads/dlib-19.24/dlib/matrix.h"


// clusters points with dlib
void clustering() {

    // create an alias of the dlib::matrix with specific dimensions
    typedef dlib::matrix<double, 2, 1> sample_type;

    // declare a matrix for a single data points
    sample_type point;

    // read 2D points from a comma-separated file
    std::fstream fs;
    fs.open("C:/Users/StudentMcStudentson/Downloads/points.txt", std::fstream::in);
    std::vector<sample_type> points;

    if (fs.is_open()) {
        while (!fs.eof()) {
            // get a whole text line until the newline symbol and assign read x and y values to a data point variable, then push it to a container
            char newString[256];
            fs.getline(newString, 256, '\n');

            std::string str = newString;
            if (str.size() < 1)
                continue;

            std::size_t comma = str.find(',');
            point(0) = std::stod(str.substr(0, comma));
            point(1) = std::stod(str.substr(comma + 1));

            points.push_back(point);
        }
    }

    fs.close();

    // print the points to make sure we read them correctly
    for (auto it : points) {
        std::cout << it << std::endl;
    }

    // create a new container for the cluster centers
    std::vector<sample_type> centers;
    centers.resize(2);
    // use dlib's k-means algorithm to find 2 cluster centers
    try {
        dlib::find_clusters_using_kmeans(points, centers);
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }
    // print the found cluster centers
    std::cout << "Centers:" << std::endl;
    for (auto it : centers) {
        std::cout << it << std::endl;
    }

}

// trains an artificial neural network to classify points to two labels using dlib
void classification() {

    typedef dlib::matrix<double, 2, 1> sample_type;
    sample_type point;

    std::fstream fs;

    fs.open("C:/Users/StudentMcStudentson/Downloads/points.txt", std::fstream::in);
    std::vector<sample_type> points;

    if (fs.is_open()) {
        while (!fs.eof()) {
            char newString[256];
            fs.getline(newString, 256, '\n');

            std::string str = newString;
            if (str.size() < 1)
                continue;

            std::size_t comma = str.find(',');
            point(0) = std::stod(str.substr(0, comma));
            point(1) = std::stod(str.substr(comma + 1));


            points.push_back(point);
        }
    }

    // create a mlp network with 2 nodes in the input layer and 1 node in the hidden layer
    dlib::mlp::kernel_1a_c net(2, 1);

    // training loop: train points 1-40 to label 1 and points 51-90 to label 2
    for (int i = 0; i < 40; ++i) {
        point = points[i];
        net.train(point, 1);

        point = points[i + 50];
        net.train(point, 0);
    }

    // test loop: use a simple round to closest integer function as the final classifier function; give the output of the network to it for points 41 to 50 and points 91 to 100
    for (int i = 40; i < 50; ++i) {
        point = points[i];
        std::cout << "Point (" << point(0) << ", " << point(1) << ") is classified to cluster " << round(net(point)) << "." << std::endl;
        point = points[i + 50];
        std::cout << "Point (" << point(0) << ", " << point(1) << ") is classified to cluster " << round(net(point)) << "." << std::endl;
    }

}

int main()
{
    clustering();
    classification();
}