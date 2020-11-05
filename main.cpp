#include <iostream>
using namespace std;

class Animal
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
        Dog(const std::string& name, const std::string& owner_name, unsigned int age):Animal(name,owner_name, age){};
        void bark()
        {
            std::cout<<"Woof woof!"<<std::endl;
        }
};

int main()
{
    Dog dog1("Azor", "Camelia", 2);
    dog1.bark();
    dog1.sleep();

    return 0;
}