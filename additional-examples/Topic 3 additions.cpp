/* Another demonstration of runtime polymorphism

*/


#include <iostream>
#include <vector>

class Parent {
public:
    virtual void doThings() {
        std::cout << "- virtual doThings() called from parent" << std::endl;
    }

    void performStuff() {
        std::cout << "- performStuff() called from parent" << std::endl;
    }

};

class Child : public Parent {
public:
    void doThings() override{
        std::cout << "- doThings() called from child" << std::endl;
    }

    void performStuff() {
        std::cout << "- performStuff() called from child" << std::endl;
    }

};


int main()
{
    Child child;
    Parent* pointer = &child;

    std::cout << "CALLING FUNCTIONS FROM OBJECT VALUE (CHILD TYPE OBJECT)" << std::endl;
    child.doThings(); // calls from child (normal behaviour)
    child.performStuff(); // calls from child (normal behaviour)

    std::cout << "CALLING FUNCTIONS FROM OBJECT POINTER (PARENT TYPE POINTER)" << std::endl;
    pointer->doThings(); // calls from child because doThings() is declared virtual in the parent class (even though the pointer is of parent type, it knows which function to call on runtime -> runtime polymorphism)
    pointer->performStuff(); // calls from parent because performStuff() isn't declared virtual in the parent class and the caller is a pointer of parent type, even though the pointed object iself is of child type

    // What use is this? Let's say we need to store several objects, and we don't know which of them will be parent type and which will be child type (might depend on user input during the program)
    // We can create a container of the parent's (pointer) type, because the inheriting child is also considered that type; this container can hold containers for both objects
    std::vector<Parent*> objects;
    // We can test this container by adding two objects to it
    Child someChild;
    Parent someParent;
    objects.push_back(&someChild);
    objects.push_back(&someParent);

    // then we can call the doThings() method from the pointers in the container without explicitly stating which of the methods (Parent's or Child's) should be used; it is decided at run-time
    std::cout << "CALLING FROM POINTERS IN A CONTAINER" << std::endl;
    for (unsigned int i = 0; i < objects.size(); ++i)
        objects[i]->doThings();

    // This is useful also for other classes than Child that inherit Parent (e.g., we can store pointers to several different classes that inherit Parent)

}
