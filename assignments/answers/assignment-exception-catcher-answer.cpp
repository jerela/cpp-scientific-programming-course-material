#include <iostream>
#include <cmath>
#include <exception>

class UnitVector {
public:
    UnitVector(double x, double y) {
        x_ = x;
        y_ = y;
	    double vectorLength = calculateLength();
		if (abs(vectorLength - 1) > eps) {
            throw std::invalid_argument("Error: vector length is not 1");
        }
    }
private:
    double calculateLength() {
        double length = 0;
        length += sqrt(x_ * x_ + y_ * y_);
        return length;
    }

    double x_ = 1;
    double y_ = 0;

    double eps = 1e-6;
};

int main()
{
    std::cout << "Hello World!\n";
    std::cout << "Creating UnitVector (1,0)" << std::endl;
    UnitVector vec1(1.0, 0.0);
    try {
        std::cout << "Creating UnitVector (2,0)" << std::endl;
        UnitVector vec2(2.0, 0.0);
    }
    catch (const std::exception &e) {
        std::cout << "Caught custom invalid argument error: " << e.what() << std::endl;
    }
}
