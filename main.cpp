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
Student::Student()
{
    roll = 0;
    clas = 0;
    name = "";
}
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
class StudentManager
{
private:
    vector<Student> S;

public:
    void addStudent();
    void displayAllStudents();
    void searchStudent();
    void updateStudent();
    void deleteStudent();
    void countStudents();

    void saveToFile(Student &st);
    void loadFromFile();
};

void StudentManager :: addStudent()
{
    Student st ;
    int clas , roll ;
    string name ;
    cin.ignore();
    cout << endl << endl << " Enter The Name Of Student :-- " ;
    getline(cin,name);
    cout << endl << " Enter The Roll No. Of Student :-- ";
    cin >> roll ;
    cout << endl << " Enter The Class Of Student :-- ";
    cin >> clas ;

    st.setName(name);
    st.setClas(clas);
    st.setRoll(roll);

    S.push_back(st);
    saveToFile(st);
}
void StudentManager::saveToFile(Student &st)
{

    fstream file ;
    file.open("Student.txt",ios::app);
    file << "Student Name: " << st.getName() << endl;
    file << "Student Roll Number: " << st.getRoll() << endl ;
    file << "Student Class: " << st.getClas() << endl << endl ;
    file.close();

}
void StudentManager::displayAllStudents()
{
    fstream file ;
    file.open("Student.txt",ios::in);
    if(!file)
    {
        cout << " File Not Found !! " ;
    }
    cout << endl << endl ;
    string line ;
    while(getline(file,line))
    {
        cout << line << endl ;
    }
    file.close();

}


int main()
{
    StudentManager SM ;
    int ch ;
    cout << " Student Management System !! " << endl ;
    do
    {
        cout << endl << " 1 --> Add Student " ;
        cout << endl << " 2 --> Display All Student " ;
        cout << endl << " 3 --> Search Student " ;
        cout << endl << " 4 --> Update Student " ;
        cout << endl << " 5 --> Delete Student " ;
        cout << endl << " 6 --> Count Student " ;
        cout << endl << " 7 --> Exit " ;
        cout << endl << " What You Want To Do Tell Here In Number (1-7) :-- ";
        cin >> ch ;

        switch(ch)
        {
            case 1:
            {
                SM.addStudent();
                break;
            }

            case 2:
            {
                SM.displayAllStudents();
                break;
            }

            case 3:
            {
                //SM.searchStudent();
                break;
            }

            case 4:
            {
                //SM.updateStudent();
                break;
            }

            case 5:
            {
                //SM.deleteStudent();
                break;
            }

            case 6:
            {
                //SM.countStudents();
                break;
            }

            case 7:
            {
                cout << endl << "Exiting Student Management System..." << endl;
                break;
            }

            default:
            {
                cout << endl << "Invalid Choice! Please enter a number from 1 to 7." << endl;
                break;
            }
        }

    } while (ch != 7);
    
    return 0 ; 
}