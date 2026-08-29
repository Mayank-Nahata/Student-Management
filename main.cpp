#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

class Student
{
private:
    int roll, clas;
    string name;

public:
    Student();

    // Getters
    int getRoll();
    int getClas();
    string getName();

    // Setters
    void setRoll(int roll);
    void setName(string name);
    void setClas(int clas);
};
// ================= GETTERS =================

int Student::getRoll()
{
    return roll;
}

int Student::getClas()
{
    return clas;
}

string Student::getName()
{
    return name;
}


// ================= SETTERS =================

void Student::setRoll(int roll)
{
    this->roll = roll;
}

void Student::setName(string name)
{
    this->name = name;
}

void Student::setClas(int clas)
{
    this->clas = clas;
}