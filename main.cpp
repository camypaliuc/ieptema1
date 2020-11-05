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

class Animal : private Uncopyable
{
    public: 
        Animal(const std::string& name, const std::string& owner_name, unsigned int age):
        name(name),
        owner_name(owner_name),
        age(age){};

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
        const std::string& owner_name;
        const unsigned int age;
};

class Dog: public Animal
{
    public:
        Dog (const std::string& name, const std::string& owner_name, unsigned int age) : Animal(name,owner_name, age){};
        void bark()
        {
            std::cout<<"Woof woof!"<<std::endl;
        }
};

class Cat: public Animal
{
    public: 
        Cat (const std::string& name, const std::string& owner_name, unsigned int age) : Animal (name, owner_name,age){};
        void meow()
        {
            std::cout<<"Meow!"<<std::endl;
        }
};

int main()
{
    Dog dog1("Azor", "Camelia", 2);
    dog1.bark();
    dog1.sleep();

    Cat cat1("Thomas", "Deiana", 4);
    cat1.eat();
    cat1.meow();

    //This operations are illegal:
    //Dog d2(d1); // the copy constructor is disallow
    //Cat c2=c1; // the copy assigment operator is disallow

    return 0;
}