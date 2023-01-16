#include <iostream>
#include <functional>
using namespace std;

class InhabitantBase
{
public:
    virtual void showPass() = 0;
};

template<typename Listener> class InhabitantCallback : public InhabitantBase
{
private:
    Listener* _object;
    void	(Listener::* _member)();
public:
    InhabitantCallback(Listener* object, void (Listener::* member)())
    {
        this->_object = object;
        this->_member = member;
    }
    virtual void showPass()
    {
        (this->_object->*this->_member)();
    }
};

class Inhabitant
{
private:
    InhabitantBase* _inhabitant;
public:
    Inhabitant()
    {
    }
    ~Inhabitant()
    {
    }

    template<typename Listener> void Connect(Listener* object, void (Listener::* member)())
    {
        this->_inhabitant = new InhabitantCallback<Listener>(object, member);
    }
    void operator()()
    {
        this->_inhabitant->showPass();
    }
};

// абстрактный класс
class Building
{
public:
    // поля класса
    string name;
    int age;

    // конструктор абстрактного класса
    Building(string n, int a)
    {
        name = n; age = a;
    }

    // виртуальные функции
    virtual double getSquare() = 0;
    string getApartments() {
        return "your apartments on the second floor";
    };
    virtual bool isOpened() = 0;

    // метод с реализацией
    void welcomeVisitors() {
        cout << "welcome to this house" << endl;
    };

};

// класс наследник
class Skyscaper: Building
{
private:
    string number;
public:
    // Вызов конструктора базового класса
    Skyscaper(string name, int age): Building(name, age)
    {
        cout << "and this is also building, but with concrete name - " << name << "and age - " << age << endl;
    }
    ~Skyscaper() {}

    // делегат
    Inhabitant inhabitant;

    void showPass() {
        inhabitant();
    }

    // переопределение числовых полей
    double getSquare() override
    {
        return 3000 * 200;
    }

    // переопределение функции с динамикой
    bool isOpened() override {
        if (age < 60) {
            return 1;
        }
    }

    // перегрузка
    // конструктор, принимающий в качестве аргумента строку, содержащую число
    void getApartments(string number)
    {
        this->number = number;
        cout << "Apartment's name: " << number << endl;
    }
    // конструктор, принимает число типа double
    double getApartments(double number)
    {
        cout << "Apartment's number: " << number << endl;
        return number;
    }

    // вывод полей класса
    void showTheParams() {
        cout << "Building year: " << age << endl;
        cout << "Building name: " << name << endl;
    }

    void welcome() {
        this->Building::welcomeVisitors();
    }
};

class Villa
{
public:
    Villa(Skyscaper* skyscaper)
    {
        skyscaper->inhabitant.Connect<Villa>(this, &Villa::MyInhabitantCallback);
    }

    void MyInhabitantCallback()
    {
        std::cout << "Hello from inhabitant! This is my pass: 0000" << std::endl;
    }
};

// класс, закрытый для наследования
class Rent final
{
public:
    void getRent() {
        cout << "this is rent class that can't be inherited" << endl;
    };
};

int main(void){

    Skyscaper skyscaper("3r4", 12);

    // вывод метода с реализацией
    skyscaper.welcome();

    // вывод полей класса
    skyscaper.showTheParams();

    // перегрузка
    // будет вызван первый конструктор
    skyscaper.getApartments("Red Hot Chili Peppers");
    // будет вызван второй конструктор
    skyscaper.getApartments(123456);

    // переопределение
    int result;
    result = skyscaper.getSquare();
    cout <<"square of building: " << result << endl;

    bool isOpened;
    isOpened = skyscaper.isOpened();
    cout << "state of building: ";
    if (isOpened = 1) {
        cout << "opened" << endl;
    }
    else {
        cout << "closed" << endl;
    }

    Rent rent;
    rent.getRent();

    // тест делегатов
    Villa villa(&skyscaper);
    villa.MyInhabitantCallback();

    return 0;
}

