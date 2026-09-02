#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include <cstdio>
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

    bool findStudent(int scholarNo, Student &st);
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
bool StudentManager::findStudent(int scholarNo, Student &st)
{
    fstream file;
    file.open("Student.txt", ios::in);

    if(!file)
    {
        return false;
    }

    string line;

    while(getline(file, line))
    {
        if(line.find("Student Name") != string::npos)
        {
            int pos = line.find(":");
            st.setName(line.substr(pos + 2));
        }

        getline(file, line);

        if(line.find("Student Roll Number") != string::npos)
        {
            int pos = line.find(":");
            st.setRoll(stoi(line.substr(pos + 2)));
        }

        getline(file, line);

        if(line.find("Student Class") != string::npos)
        {
            int pos = line.find(":");
            st.setClas(stoi(line.substr(pos + 2)));
        }

        getline(file, line);

        if(line.find("Student Scholar Number") != string::npos)
        {
            int pos = line.find(":");

            int SN = stoi(line.substr(pos + 2));

            st.setScholarNo(SN);

            if(SN == scholarNo)
            {
                file.close();
                return true;
            }
        }

        // Skip blank line
        getline(file, line);
    }

    file.close();

    return false;
}
void StudentManager::searchStudent()
{
    int sn;

    cout << " Enter The Scholar Number Of Student :-- ";
    cin >> sn;

    Student st;

    if(findStudent(sn, st))
    {
        cout << endl << " Student Found !" << endl;

        cout << " Student Name :-- "
             << st.getName() << endl;

        cout << " Student Roll Number :-- "
             << st.getRoll() << endl;

        cout << " Student Class :-- "
             << st.getClas() << endl;

        cout << " Student Scholar Number :-- "
             << st.getScholarNo() << endl << endl;
    }
    else
    {
        cout << endl
             << " Student Of Scholar Number "
             << sn
             << " Not Found !"
             << endl << endl;
    }
}
void StudentManager::updateStudent()
{
    int searchScholar;

    cout << " Enter The Scholar Number Of Student :-- ";
    cin >> searchScholar;

    Student st;

    if(!findStudent(searchScholar, st))
    {
        cout << endl
             << " Student Of Scholar Number "
             << searchScholar
             << " Not Found !"
             << endl << endl;

        return;
    }

    cout << endl << " Student Found !" << endl;

    cout << " Current Details :" << endl;

    cout << " Student Name :-- "
         << st.getName() << endl;

    cout << " Student Roll Number :-- "
         << st.getRoll() << endl;

    cout << " Student Class :-- "
         << st.getClas() << endl;

    cout << " Student Scholar Number :-- "
         << st.getScholarNo() << endl;


    int choice;

    cout << endl;
    cout << " What Do You Want To Update ?" << endl;
    cout << " 1 --> Name" << endl;
    cout << " 2 --> Roll Number" << endl;
    cout << " 3 --> Class" << endl;
    cout << " 4 --> All Details" << endl;
    cout << " 5 --> Cancel" << endl;

    cout << " Enter Your Choice :-- ";
    cin >> choice;


    if(choice == 1)
    {
        string name;

        cin.ignore();

        cout << " Enter New Name :-- ";
        getline(cin, name);

        st.setName(name);
    }

    else if(choice == 2)
    {
        int roll;

        cout << " Enter New Roll Number :-- ";
        cin >> roll;

        st.setRoll(roll);
    }

    else if(choice == 3)
    {
        int clas;

        cout << " Enter New Class :-- ";
        cin >> clas;

        st.setClas(clas);
    }

    else if(choice == 4)
    {
        string name;
        int roll, clas;

        cin.ignore();

        cout << " Enter New Name :-- ";
        getline(cin, name);

        cout << " Enter New Roll Number :-- ";
        cin >> roll;

        cout << " Enter New Class :-- ";
        cin >> clas;

        st.setName(name);
        st.setRoll(roll);
        st.setClas(clas);
    }

    else if(choice == 5)
    {
        cout << endl << " Update Cancelled !" << endl << endl;
        return;
    }

    else
    {
        cout << endl << " Invalid Choice !" << endl << endl;
        return;
    }


    // Open original file
    fstream file;
    file.open("Student.txt", ios::in);

    if(!file)
    {
        cout << " File Not Found !" << endl;
        return;
    }


    // Open temporary file
    fstream temp;
    temp.open("Temp.txt", ios::out);

    if(!temp)
    {
        cout << " Unable To Create Temporary File !" << endl;
        file.close();
        return;
    }


    string line;

    while(getline(file, line))
    {
        // Read Name
        string name = line.substr(line.find(":") + 2);

        // Read Roll
        getline(file, line);
        int roll = stoi(line.substr(line.find(":") + 2));

        // Read Class
        getline(file, line);
        int clas = stoi(line.substr(line.find(":") + 2));

        // Read Scholar Number
        getline(file, line);
        int scholarNo = stoi(line.substr(line.find(":") + 2));

        // Skip blank line
        getline(file, line);


        // Check whether this is the student we want
        if(scholarNo == searchScholar)
        {
            temp << "Student Name: " << st.getName() << endl;
            temp << "Student Roll Number: " << st.getRoll() << endl;
            temp << "Student Class: " << st.getClas() << endl;
            temp << "Student Scholar Number: " << st.getScholarNo()
                 << endl << endl;
        }
        else
        {
            // Write unchanged student
            temp << "Student Name: " << name << endl;
            temp << "Student Roll Number: " << roll << endl;
            temp << "Student Class: " << clas << endl;
            temp << "Student Scholar Number: " << scholarNo
                 << endl << endl;
        }
    }


    file.close();
    temp.close();


    // Replace old file with new file
    remove("Student.txt");

    if(rename("Temp.txt", "Student.txt") != 0)
    {
        cout << " Error Renaming Temporary File !" << endl;
        return;
    }


    cout << endl
         << " Student Details Updated Successfully !"
         << endl << endl;
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
                SM.updateStudent();
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