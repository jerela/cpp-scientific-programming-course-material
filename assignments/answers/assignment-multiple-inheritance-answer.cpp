/* ASSIGNMENT:
Specify the correct keywords and access specifiers for the classes MobileParticle, Attractor, Repulsor, InteractiveParticle, and DynamicSystem.
Attractor and Repulsor should inherit from MobileParticle. InterActiveParticle should inherit from Attractor and Repulsor. All this should work without the diamond problem (no ambiguity in inheritance).
You don't need to change anything but the inheritance properties of the classes (so no need to write new lines of code, change values, or add new data members).
After you have specified the correct inheritance, the code should compile and print for the final values of the two particles:
x=-35.4034, y=21.8401
x=90.4034, y=-17.8401
Then answer the following questions.
1. Name the class (one of the five named above) that represents composition with custom classes: DynamicSystem
2. Name the class (one of the five named above) that uses multiple inheritance: InteractiveParticle
*/

#include <iostream>
#include <vector>
#include <cmath> // this was needed for some compilers

// a particle that has position, velocity, and acceleration in 2D space
class MobileParticle {
public:
    MobileParticle() {
        std::cout << "MobileParticle constructed" << std::endl;
    };

    // functions to set x and y position and velocity
    void setX(double x) { px_ = x; }
    void setY(double y) { py_ = y; }
    void setVX(double vx) { vx_ = vx; }
    void setVY(double vy) { vy_ = vy; }

    // print the (x,y) position of the particle
    void printPosition() {
        std::cout << "x=" << px_ << ", y=" << py_ << std::endl;
    }

    // update velocity and position according to acceleration and velocity
    void propagate(double delta) {
        vx_ += ax_ * delta;
        vy_ += ay_ * delta;
        px_ += vx_ * delta;
        py_ += vy_ * delta;
    }

    // get x and y position
    double getX() { return px_; }
    double getY() { return py_; }

    // change the acceleration of the particle, as if forces were affecting it
    void accelerate(double ax, double ay) {
        ax_ += ax;
        ay_ += ay;
    }

    // get the scalar distance from the calling particle to the argument particle
    double getDistance(MobileParticle particle) {
        double xd = particle.getX() - this->getX();
        double yd = particle.getY() - this->getY();
        return sqrt(pow(xd, 2) + pow(yd, 2));
    }

protected:
    // get the normalized direction vector from the calling particle to the argument particle
    std::vector<double> getDirection(MobileParticle particle) {
        double xd = particle.getX() - this->getX();
        double yd = particle.getY() - this->getY();

        // now we have a vector between the particles, but we must normalize it so that its length is 1
        double distance = getDistance(particle);
        xd /= distance;
        yd /= distance;

        std::vector<double> dir;
        dir.push_back(xd);
        dir.push_back(yd);
        return dir;
    }

private:
    // 2D position
    double px_ = 0;
    double py_ = 0;
    // 2D velocity
    double vx_ = 0;
    double vy_ = 0;
    // 2D acceleration
    double ax_ = 0;
    double ay_ = 0;
};



// an object that can attract other particles
class Attractor : virtual public MobileParticle {
public:
    Attractor() {
        std::cout << "Attractor constructed" << std::endl;
    };

    // apply an attractive "force" to another particle
    void attract(MobileParticle& particle, double delta) {
        std::vector<double> dir = getDirection(particle);
        double distance = getDistance(particle);
        double distanceDecay = (1.0 / pow(1.0 + distance, 2));
        double attraction = -delta * attractionMagnitude_ * distanceDecay;
        particle.accelerate(attraction * dir[0], attraction * dir[1]);
    }

private:
    double attractionMagnitude_ = 21.0;
};



// an object that can repulse other particles
class Repulsor : virtual public MobileParticle {
public:
    Repulsor() {
        std::cout << "Repulsor constructed" << std::endl;
    };

    // apply a repulsive "force" to another particle
    void repulse(MobileParticle& particle, double delta) {
        std::vector<double> dir = getDirection(particle);
        double distance = getDistance(particle);
        double distanceDecay = (1.0 / pow(1.0 + distance, 3));
        double repulsion = delta * repulsionMagnitude_ * distanceDecay;
        particle.accelerate(repulsion * dir[0], repulsion * dir[1]);
    }
private:
    double repulsionMagnitude_ = 7.10;
};

// a particle that is an attractor, a repulsor and a mobile particle
class InteractiveParticle : public Attractor, public Repulsor {
public:
    InteractiveParticle(double x, double y, double vx, double vy) {
        std::cout << "InteractiveParticle constructed" << std::endl;
        setX(x);
        setY(y);
        setVX(vx);
        setVY(vy);
    };
};



// a system of multiple bodies
class DynamicSystem {
public:
    DynamicSystem() {};

    // add a particle to the system
    void addParticle(double x, double y, double vx, double vy) {
        InteractiveParticle particle(x, y, vx, vy);
        particles_.push_back(particle);
    }

    // apply the two-way forces between all particles
    void integrate_particles(double delta) {
        for (unsigned int i = 0; i < particles_.size(); ++i) {
            for (unsigned int j = 0; j < particles_.size(); ++j) {

                // we don't want a particle to apply a force on itself
                if (i == j)
                    continue;

                if (i == 0) // otherwise, we can print the distance between the particles
                    std::cout << "distance between particles: " << particles_[i].getDistance(particles_[j]) << std::endl;

                // apply both repulsive and attractive forces between particles
                particles_[i].repulse(particles_[j], delta);
                particles_[i].attract(particles_[j], delta);
            }
        }

        // now that the forces have been applied, we let them affect the motion of the particles
        for (auto it = particles_.begin(); it < particles_.end(); ++it) {
            it->propagate(delta);
        }

    }

    // print the x and y coordinates of a particle by index
    void printPosition(int i) {
        particles_[i].printPosition();
    }

private:
    std::vector<InteractiveParticle> particles_;
};



int main()
{
    // create a new system and add 2 particles to it
    DynamicSystem system;
    system.addParticle(10, 1, -5.0, 0.0);
    system.addParticle(20, 3, 5.5, 0.0);

    // let our time step be 0.05 arbitrary units
    double dt = 0.05;
    // iterate for 1000 epochs
    for (unsigned int i = 0; i < 1000; ++i) {
        std::cout << "EPOCH " << i << std::endl;
        system.integrate_particles(dt);
        // print positions of the two particles
        system.printPosition(0);
        system.printPosition(1);

    }

    std::cout << "Final positions:" << std::endl;
    system.printPosition(0);
    system.printPosition(1);
}
