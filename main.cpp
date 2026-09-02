#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

class Student
{
private:
    int roll, clas,scholarNo;
    string name;

public:
    Student();

    // Getters
    int getRoll();
    int getClas();
    string getName();
    int getScholarNo();

    // Setters
    void setRoll(int roll);
    void setName(string name);
    void setClas(int clas);
    void setScholarNo(int scholarNo);
};
// ================= GETTERS =================
Student::Student()
{
    roll = 0;
    clas = 0;
    name = "";
    scholarNo = 0; 
}
int Student::getScholarNo()
{
    return scholarNo ;
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

void Student::setScholarNo(int scholarNo)
{
    this->scholarNo = scholarNo ;
}
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
    int getNextScholarNo();
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
    st.setScholarNo(getNextScholarNo());

    S.push_back(st);
    saveToFile(st);
}
void StudentManager::saveToFile(Student &st)
{

    fstream file ;
    file.open("Student.txt",ios::app);
    file << "Student Name: " << st.getName() << endl;
    file << "Student Roll Number: " << st.getRoll() << endl ;
    file << "Student Class: " << st.getClas() << endl  ;
    file << "Student Scholar Number: " << st.getScholarNo() << endl << endl ;
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
int StudentManager::getNextScholarNo()
{
    fstream file;
    file.open("Student.txt", ios::in);

    if(!file)
    {
        return 1001;
    }

    if(file.peek() == EOF)
    {
        return 1001;
    }

    // Go to the end of the file
    file.seekg(0, ios::end);

    long long pos = file.tellg();
    char ch;

    // Skip all newline characters at the end
    do
    {
        pos--;
        file.seekg(pos);
        file.get(ch);

    } while(pos > 0 && (ch == '\n' || ch == '\r'));

    // Move backward until we find the beginning
    // of the last line
    while(pos > 0)
    {
        pos--;

        file.seekg(pos);
        file.get(ch);

        if(ch == '\n' || ch == '\r')
        {
            pos++;
            break;
        }
    }

    // Go to beginning of Scholar Number line
    file.seekg(pos);

    string line;
    getline(file, line);

    // Extract Scholar Number
    int p = line.find(":");

    if(p == string::npos)
    {
        cout << "Scholar Number line not found!";
        file.close();
        return 1001;
    }

    string scholar = line.substr(p + 2);

    int scholarNo = stoi(scholar);

    file.close();

    return scholarNo + 1;
}
void StudentManager::searchStudent()
{
    fstream file;
    string line;
    int sn;

    bool f = false;

    cout << " Enter The Scholar Number Of Student :-- ";
    cin >> sn;

    file.open("Student.txt", ios::in);

    if(!file)
    {
        cout << " File Not Found ! " << endl;
        return;
    }

    if(file.peek() == EOF)
    {
        cout << " The File Does Not Contain Any Student Detail's " << endl;
        return;
    }

    int pos;
    int clas, roll;
    string name;

    while(getline(file, line))
    {
        if(line.find("Name") != string::npos)
        {
            pos = line.find(":");
            name = line.substr(pos + 2);
        }

        if(line.find("Roll") != string::npos)
        {
            pos = line.find(":");
            roll = stoi(line.substr(pos + 2));
        }

        if(line.find("Class") != string::npos)
        {
            pos = line.find(":");
            clas = stoi(line.substr(pos + 2));
        }

        if(line.find("Scholar Number") != string::npos)
        {
            pos = line.find(":");

            int SN = stoi(line.substr(pos + 2));

            if(SN == sn)
            {
                f = true;

                cout << endl << " Student Found !" << endl;
                cout << " Student Name :-- " << name << endl;
                cout << " Student Roll Number :-- " << roll << endl;
                cout << " Student Class :-- " << clas << endl;
                cout << " Student Scholar Number :-- " << SN << endl << endl;

                break;
            }
        }
    }
    if(!f)
    {
        cout << endl
             << " Student Of Scholar Number "
             << sn
             << " Not Found !"
             << endl << endl;
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
                SM.searchStudent();
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