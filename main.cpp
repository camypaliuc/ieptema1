#include <iostream>
using namespace std;

class Uncopyable {
protected: // allow construction and destruction
    Uncopyable() {} 
    ~Uncopyable() {} 
private:
    // prevent copying
    Uncopyable(const Uncopyable&); 
    Uncopyable& operator=(const Uncopyable&);
};

class Person 
{
    public: 
        Person(const std::string& name, unsigned int age):
        name(name),
        age(age){};
 
    private:
        const std::string& name;
        const unsigned int age;
};

class Animal
{
    public: 
        Animal(const std::string& name, Person *owner, unsigned int age):
        name(name),
        owner(owner),
        age(age){};
    Animal& operator=(const Animal&);
    void eat()
    {
        std::cout<<"I am eating!"<<std::endl;
    }
    void sleep()
    {
        std::cout<<"I am sleeping!"<<std::endl;
    }
    protected:
        const std::string& name;
        const unsigned int age;
        Person *owner;
};
Animal& Animal::operator=(const Animal& rhs)
{
    Person *pOrig = owner; // remember original pb
    owner = new Person(*rhs.owner); // point pb to a copy of rhs’s owner
    delete pOrig; // delete the original pb
    return *this;
}

class Dog: public Animal
{
    public:
        Dog (const std::string& name, Person *owner, unsigned int age) : Animal(name, owner, age){};

        void bark()
        {
            std::cout<<"Woof woof!"<<std::endl;
        }
};

class Cat: public Animal
{
    public: 
        Cat (const std::string& name, Person *owner, unsigned int age) : Animal (name, owner,age){};
        void meow()
        {
            std::cout<<"Meow!"<<std::endl;
        }
};

int main()
{

    Person deiana("Deiana", 22);
    Person camelia("Camelia", 22);

    Dog dog1("Azor", &camelia, 2);
    dog1.bark();
    dog1.sleep();

    Cat cat1("Thomas", &deiana, 4);
    cat1.eat();
    cat1.meow();

    return 0;
}
