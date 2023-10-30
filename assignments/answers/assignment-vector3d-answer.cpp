

#include <iostream>
#include <string>

class Vector3D {
public:

    Vector3D(double a, double b, double c) {
        x = a;
        y = b;
        z = c;
    }

    Vector3D() {};

    // get length of vector
    double getLength() {
        return sqrt(x * x + y * y + z * z);
    }

    // if ostream needs access to private variables, use the "friend" declaration to give its << operator access
    //friend std::ostream& operator<<(std::ostream& os, const Vector3D& obj);
    
    // overload subscript operator
    double operator[](unsigned int i) {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        }
    }

    // overload +
    Vector3D operator+(Vector3D const& obj) {
        Vector3D result;
        result.x = x + obj.x;
        result.y = y + obj.y;
        result.z = z + obj.z;
        return result;
    }

    // overload -
    Vector3D operator-(Vector3D const& obj) {
        Vector3D result;
        result.x = x - obj.x;
        result.y = y - obj.y;
        result.z = z - obj.z;
        return result;
    }

    // dot product
    double operator*(Vector3D const& obj) {
        return x * obj.x + y * obj.y + z * obj.z;
    }

    // elements
    double x = 0;
    double y = 0;
    double z = 0;
};

// overload << operator
std::ostream& operator<<(std::ostream& os, const Vector3D& vec)
{
    os << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
    return os;
}


int main()
{
    Vector3D zero;
    Vector3D vec(2.5, 3, -5.5);
    Vector3D anotherVec(50.2, 5, 0);

    std::cout << "zero vector: " << zero << std::endl;
    std::cout << "a vector: " << vec << std::endl;
    std::cout << "another vector: " << anotherVec << std::endl;

    std::cout << "length of zero vector: " << zero.getLength() << std::endl;
    std::cout << "length of a vector: " << vec.getLength() << std::endl;
    std::cout << "length of another vector: " << anotherVec.getLength() << std::endl;

    std::cout << "zero vector minus a vector: " << zero-vec << std::endl;
    std::cout << "a vector plus another vector: " << vec+anotherVec << std::endl;
    std::cout << "dot product of a vector and another vector: " << vec*anotherVec << std::endl;

    std::cout << "final element of a vector: " << vec[2] << std::endl;


}
