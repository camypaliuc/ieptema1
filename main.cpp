#include <iostream>
#include <tr1/memory>
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

class Food
{
    public:         
    virtual std::string getName() = 0;
};
class Bone: public Food
{
    public:
    std::string getName()
    {
        return "bone";
    }
};
class Milk: public Food
{
    public:
    std::string getName()
    {
        return "milk";
    }
};
//factory method
Food* createFood(int choice)
{
    if (choice == 1)
        return new Bone();
    else
    {
        return new Milk();
    }    
}

class Animal
{
    public: 
        Animal(const std::string& name, Person *owner, unsigned int age):
        name(name),
        owner(owner),
        age(age){};
    Animal& operator=(const Animal&);
    virtual void feed() {};
    void sleep()
    {
        std::cout<<name<<":I am sleeping!"<<std::endl;
    }
    const std::string& getName()
    {
        return name;
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
        Dog (const std::string& name, Person *owner, unsigned int age, std::string color ): 
        Animal(name, owner, age),
        color(color){};
        Dog& operator=(const Dog&);
        Dog(const Dog& rhs):
            Animal(rhs), //invoke baseclass body constructor
            color(rhs.color){};
        void bark()
        {
            std::cout<<name<<":Woof woof!"<<std::endl;
        }
        void feed()
        {
            std::tr1::shared_ptr<Food> food (createFood(1)); // creates obj instance of Bone
            std::cout<<name<<":I am eating a "<<food->getName()<<"! ";
            std::cout<<"I finished eating!"<<std::endl<<std::endl;
        }
    private:
        std::string color;
};

Dog& Dog::operator=(const Dog& rhs)
{
    Animal::operator=(rhs); //assign base class parts
    color=rhs.color;
    return *this;
}
class Cat: public Animal
{
    public: 
        Cat (const std::string& name, Person *owner, unsigned int age) : Animal (name, owner,age){};
        void meow()
        {
            std::cout<<name<<":Meow!"<<std::endl;
        }
        void feed()
        {
            std::tr1::shared_ptr<Food> food (createFood(2));// creates obj instance of Milk
            std::cout<<name<<":I am eating a "<<food->getName()<<"! ";
            std::cout<<"I finished eating!"<<std::endl<<std::endl;
        }
};
class Vaccinate: private Uncopyable{
    public:
    explicit Vaccinate(Animal *pet)
    :petPtr(pet)
    { lockForVaccine(petPtr);} //aquire  resource
    ~Vaccinate(){unlock(petPtr);} //release resource
    private:
    void lockForVaccine(Animal *pet)
    {
        std::cout<<pet->getName()<<" locked in a cage for vaccine!"<<std::endl;
    }
    void unlock(Animal *pet)
    {
    std::cout<<pet->getName()<< " vaccinated and unlocked!"<<std::endl;
    }
    Animal *petPtr;
};

int main()
{

    Person deiana("Deiana", 22);
    Person camelia("Camelia", 22);

    Dog dog1("Azor", &camelia, 2, "black");
    dog1.bark();
    dog1.sleep();
    dog1.feed();
    Vaccinate v1 (&dog1);

    Cat cat1("Thomas", &deiana, 4);
    cat1.meow();
    cat1.feed();
    Vaccinate v2 (&cat1);
    return 0;
}