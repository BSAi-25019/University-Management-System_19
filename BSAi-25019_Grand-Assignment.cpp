#include <iostream>
#include <fstream>
#include <windows.h>
#include<conio.h>
#include<time.h>

using namespace std;

void gotoRowCol(int r, int c)
{
    COORD scrn;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = c;
    scrn.Y = r;
    SetConsoleCursorPosition(hOutput, scrn);
}
void hideConsoleCursor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}
void color(int k)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
}
void printlines(int r1, int r2, int c1, int c2, double A, char S)
{
    for (double a = 0; a <= 1; a += A)
    {
        int dr = round(r1 * a + (1 - a) * r2);
        int dc = round(c1 * a + (1 - a) * c2);
        gotoRowCol(dr, dc);
        cout << S;
    }
}

struct Course {
    int courseID;
    char courseName[100];
    char instructor[50];
    int credits;
    int capacity;
    int enrolled;
};

struct Student {
    int studentID;
    char studentName[100];
    char department[50];
    int semester;
};

struct Enrollment {
    int studentID;
    int courseID;
    char enrollmentDate[50];
};
int generateID(Student* St, Course* Crs, int ct_crs, int ct_st,int C)
{
    while (true)
    {
        if (C == 1)
        {
            int id;
            bool unique;
            do
            {
                id = 1000 + rand() % 9000;
                unique = true;
                for (int i = 0; i < ct_st; i++)
                {
                    if (St[i].studentID == id)
                    {
                        unique = false;
                        break;
                    }
                }
            } while (!unique);
            cout << "\n Your New #ID -->: " << id;
            return id;
        }
        else if (C == 2)
        {
            int id;
            bool unique;
            do
            {
                id = 101 + rand() % 99;

                unique = true;
                for (int i = 0; i < ct_crs; i++)
                {
                    if (Crs[i].courseID == id)
                    {
                        unique = false;
                        break;
                    }
                }
            } while (!unique);
            cout << "\n Your New #ID -->: " << id;
            return id;
        }
    }
}
//Course Management Functions
void addCourse(Course*& courses, int& ct_crs,Student*St,int& ct_st) 
{
    Course* newCrs = new Course[++ct_crs];
    for (int i = 0; i < ct_crs-1; i++)
    {
        newCrs[i] = courses[i];
    }
    Course Nc;
    cout << "\n\nGenrating Course ID: ";
    Sleep(2000);
    Nc.courseID = generateID(St, courses, ct_crs, ct_st,2);
    cin.ignore();
    char ch;
    int j = 0;
    cout << "\n\nEnter Course Name: ";
    while (cin.get(ch) && ch != '\n')
    {
        Nc.courseName[j++] = ch;
    }
    Nc.courseName[j] = '\0';
    j = 0;
    cout << "\n\nEnter Instructor Name: ";
    while (cin.get(ch) && ch != '\n')
    {
        Nc.instructor[j++] = ch;
    }
    Nc.instructor[j] = '\0';

    cout << "\n\nEnter Credits: ";
    cin >> Nc.credits;
    cout << "\n\nEnter Capacity: ";
    cin >> Nc.capacity;
    Nc.enrolled = 0; 
    cout << "\n\nSuccesfully Added New Course!\n";
    newCrs[ct_crs-1] = Nc;
    delete[] courses;
    courses = newCrs;
    
}
void viewAllCourses(Course* Crs, int ct_crs)
{
    cout << "\n\n\n\n#ID\t"<<"Course Name\t\t"<<"Instructor\t"<<"Credits\t\t"<<"Capacity\t"<<"Enrolled\n\n";
    for (int i = 0; i < ct_crs; i++)
    {
        cout << Crs[i].courseID << "\t" << Crs[i].courseName << "\t\t" << Crs[i].instructor << "\t\t"<< Crs[i].credits << "\t\t" << Crs[i].capacity << "\t\t"<< Crs[i].enrolled << "\n\n";
    }
}
void updateCourse(Course* Crs, int ct_crs)
{
    int id;
    cout << "\n\n\nEnter Course #ID For Updating: ";
    cin >> id;
    int index =-2;
    for (int i = 0; i < ct_crs; i++)
    {
        if (Crs[i].courseID == id)
        {
            index = i;
            break;
        }
    }
    if (index == -2)
    {
        cout << "\n\nCourse not found!\n";
        return;
    }
    cout << "\n\nEnter New Course Name: ";
    cin.ignore();

    char ch;
    int j = 0;
    while (cin.get(ch) && ch != '\n')
    {
        Crs[index].courseName[j++] = ch;
    }
    Crs[index].courseName[j] = '\0';
    j = 0;

    cout << "\n\nEnter New Instructor: ";
    while (cin.get(ch) && ch != '\n')
    {
        Crs[index].instructor[j++] = ch;
    }
    Crs[index].instructor[j] = '\0';
    cout << "\n\nEnter New Credits: ";
    cin >> Crs[index].credits;
    cout << "\n\nEnter New Capacity: ";
    cin >> Crs[index].capacity;

    cout << "\n\nNew Courses Added!\n";
}
void deleteCourse(Course*& Crs, int& ct_crs)
{
    int id;
    cout << "\n\n\nEnter Course ID to delete: ";
    cin >> id;
    int index = -1;
    for (int i = 0; i < ct_crs; i++)
    {
        if (Crs[i].courseID == id)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        cout << "\n\nNo Course Found!\n";
        return;
    }

    Course* newCrs = new Course[--ct_crs];
    int j = 0;
    for (int i = 0; i < ct_crs + 1; i++)
    {
        if (i != index)
        {
            newCrs[j++] = Crs[i];
        }
    }
    delete[] Crs;
    Crs = newCrs;
    cout << "\n\nCourse Deleted !\n";
}
void searchCourse(Course* Crs, int ct_crs)
{
    int id=0;
    cout << "\n\nEnter Course #ID to search: ";
    cin >> id;
    for (int i = 0; i < ct_crs; i++)
    {
        if (Crs[i].courseID == id)
        {
            cout << "\nCourse Found:\n\n";
            cout << "\n\n\n#ID\t" << "NAME\t\t" << "Instructer\t" << "Credits\t\t" << "Capacity\t" << "Enrolled\t\n\n";
            cout << Crs[i].courseID <<"\t";
            cout << Crs[i].courseName << "\t"; 
            cout << Crs[i].instructor << "\t\t";
            cout << Crs[i].credits << "\t\t";
            cout << Crs[i].capacity << "\t\t";
            cout << Crs[i].enrolled << "\n";
            return;
        }
    }
    cout << "\n\nNo Course Found!\n";
}
//Student Management Functions
void addStudent(Course*& courses, int& ct_crs, Student*& St, int& ct_st)
{
    Student* newSt = new Student[ct_st+1];
    for (int i = 0; i < ct_st ; i++)
    {
        newSt[i] = St[i];
    }
    Student NSt;
    cout << "\n\nGenerating Student ID: ";
    Sleep(2000);
    NSt.studentID = generateID(St, courses, ct_crs, ct_st,1);
    cin.ignore();

    char ch;
    int j = 0;
    cout << "\n\nEnter Student Name: ";
    while (cin.get(ch) && ch != '\n')
    {
        NSt.studentName[j++] = ch;
    }
    NSt.studentName[j] = '\0';
    j = 0;
    cout << "\n\nEnter Department: ";
    while (cin.get(ch) && ch != '\n')
    {
        NSt.department[j++] = ch;
    }
    NSt.department[j] = '\0';

    cout << "\n\nEnter Semester: ";
    cin >> NSt.semester;

    newSt[ct_st] = NSt;
    delete[] St;
    St = newSt;
    ct_st++;
    cout << "\n\nNew Student Added!\n";
}
void viewAllStudents(Student* St, int ct_st)
{
    cout << "\n\n#ID\t"<<"Name\t\t\t"<<"Department\t\t"<<"Semester\n\n";
    for (int i = 0; i < ct_st; i++)
    {
        cout << St[i].studentID << "\t"<< St[i].studentName << "\t\t"<< St[i].department << "\t\t"<< St[i].semester << "\n\n";
    }
}
void updateStudent(Student* St, int ct_st)
{
    int id;
    cout << "\n\nEnter Student #ID To Update: ";
    cin >> id;
    int index = -1;
    for (int i = 0; i < ct_st; i++)
    {
        if (St[i].studentID == id)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        cout << "\n\nNo Student Found!\n";
        return;
    }
    cout << "\n\nEnter New Student Name: ";
    cin.ignore();

    char ch;
    int j = 0;
    while (cin.get(ch) && ch != '\n')
    {
        St[index].studentName[j++] = ch;
    }
    St[index].studentName[j] = '\0';
    j = 0;

    cout << "\n\nEnter New Department: ";
    while (cin.get(ch) && ch != '\n')
    {
        St[index].department[j++] = ch;
    }
    St[index].department[j] = '\0';

    cout << "\n\nEnter New Semester: ";
    cin >> St[index].semester;

    cout << "\n\nStudent Record Updated!\n";
}
void deleteStudent(Student*& St, int& ct_st)
{
    int id;
    cout << "\n\nEnter Student #ID to delete: ";
    cin >> id;
    int index = -1;
    for (int i = 0; i < ct_st; i++)
    {
        if (St[i].studentID == id)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        cout << "\n\nNo Student Found!\n";
        return;
    }

    Student* newSt = new Student[--ct_st];
    int j = 0;
    for (int i = 0; i < ct_st + 1; i++)
    {
        if (i != index)
        {
            newSt[j++] = St[i];
        }
    }
    delete[] St;
    St = newSt;

    cout << "\n\nStudent Deleted!\n";
}
void searchStudent(Student* St, int ct_st)
{
    int id;
    cout << "\n\nEnter Student ID to search: ";
    cin >> id;

    for (int i = 0; i < ct_st; i++)
    {
        if (St[i].studentID == id)
        {
            cout << "\nStudent Found:\n\n";
            cout << "#ID\tName\t\t\tDepartment\t\tSemester\n\n";
            cout << St[i].studentID << "\t"<< St[i].studentName << "\t\t" << St[i].department << "\t\t"<< St[i].semester << "\n";
            return;
        }
    }
    cout << "\n\nNo Student Found!\n";
}
//Enrollment Functions
void addEnrollment(Enrollment*& enr, int& ct_enr,Student* St, int ct_st,Course* Crs, int ct_crs)
{
    int Stid, Crsid;
    cout << "\n\nEnter Student ID: ";
    cin >> Stid;
    int Stcheck = 0;
    for (int i = 0; i < ct_st; i++)
    {
        if (St[i].studentID == Stid)
        {
            Stcheck = 1;
            break;
        }
    }
    if (Stcheck==0)
    {
        cout << "\n\nNo Student Found!\n";
        return ;
    }


    cout << "\n\nEnter Course #ID: ";
    cin >> Crsid;
    int Crscheck=0;
    for (int i = 0; i < ct_crs; i++)
    {
        if (Crs[i].courseID == Crsid)
        {
            Crscheck = i;
            if (Crs[i].enrolled >= Crs[i].capacity)
            {
                cout << "\n\nNo Seat Available!\n";
                return;
            }
            break;
        }
    }
    if (Crscheck == -1)
    {
        cout << "\n\nNo Course Found!\n";
        return;
    }

    for (int i = 0; i < ct_enr; i++)
    {
        if (enr[i].studentID == Stid && enr[i].courseID == Crsid)
        {
            cout << "\n\nAlready Enrolled!\n";
            return;
        }
    }
    Enrollment* newEnr = new Enrollment[ct_enr+1];
    
    for (int i = 0; i < ct_enr ; i++)
    {
        newEnr[i] = enr[i];
    }
    newEnr[ct_enr].studentID = Stid;
    newEnr[ct_enr].courseID = Crsid;
    cin.ignore();
    char ch;
    int j = 0;
    cout << "\n\nEnter Enrollment Date (YYYY-MM-DD): ";
    while (cin.get(ch) && ch != '\n')
    {
        newEnr[ct_enr].enrollmentDate[j++] = ch;
    }
    newEnr[ct_enr].enrollmentDate[j] = '\0';
    delete[] enr;
    enr = newEnr;
    ct_enr++;
    Crs[Crscheck].enrolled++;

    cout << "\n\nNew Student Enrolled!\n";
}
void viewStudentEnrollments(Enrollment* enr, int ct_enr, Course* Crs, int ct_crs,Student*St,int ct_St)
{
    int id;
    cout << "\n\nEnter Student #ID: ";
    cin >> id;
    bool found = false;
    for (int i = 0; i < ct_enr; i++)
    {
        if (enr[i].studentID == id)
        {
            for (int s = 0; s < ct_St; s++)
            {
                if (St[s].studentID == id)
                {
                    cout << "\n\nStudent Name--> " << St[s].studentName << "\n\n";
                    break;
                }
            }
            cout << "\n\nCourseID\t" << "Course Name\t\t" << "Course Enrolled Date\n\n";
            for (int j = 0; j < ct_crs; j++)
            {
                if (Crs[j].courseID == enr[i].courseID)
                {
                    found = true;
                    cout << Crs[j].courseID << "\t\t"<< Crs[j].courseName << "\t\t"<<enr[i].enrollmentDate<<"\n\n";
                    
                }
            }
        }
    }
    if (!found)
     cout << "\n\nNo Student Found!\n";
}

void viewCourseEnrollments(Enrollment* enr, int ct_enr, Course* Crs, int ct_crs, Student* St, int ct_st)
{
    char name[100];
    cout << "\n\nEnter Course Name:";
    char ch;
    int j = 0;
    while (cin.get(ch) && ch != '\n')
    {
        
    }
    while (cin.get(ch) && ch != '\n')
    {
        name[j++] = ch;
    }
    
    name[j] = '\0';
   /* cin.getline(name, 100, '.');*/

    bool k = false;
    for (int c = 0; c < ct_crs; c++)
    {
        if (strcmp(Crs[c].courseName, name) == 0)
        {
            cout << "\n\nCourse Instructor--> " << Crs[c].instructor << "\n\n";
            k = true;
        }
    }
    if (!k)
    {
        cout << "\nCourse not found!\n";
    }

}
void dropCourse(Enrollment*& enr, int& ct_enr, Course* Crs, int ct_crs)
{
    int Stid=0, Crsid=0;
    cout << "\n\nEnter Student ID: ";
    cin >> Stid;
    cout << "\n\nEnter Course ID: ";
    cin >> Crsid;

    int index = -1;
    for (int i = 0; i < ct_enr; i++)
    {
        if (enr[i].studentID == Stid && enr[i].courseID == Crsid)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
    {
        cout << "\n\nNo Enrollment Found!\n";
        return;
    }

    for (int i = 0; i < ct_crs; i++)
    {
        if (Crs[i].courseID == Crsid)
        {
            Crs[i].enrolled--;
            break;
        }
    }
    Enrollment* newEnr = new Enrollment[--ct_enr];
    int j = 0;
    for (int i = 0; i < ct_enr + 1; i++)
    {
        if (i != index)
        {
            newEnr[j++] = enr[i];
        }
    }
    delete[] enr;
    enr = newEnr;
    cout << "\n\nCourse Dropped!\n";
}
//File Handling Functions
Course* loadCoursesFromFile(const char* filename, int& ct_crs) 
{
    ifstream rdr(filename);
    if (!rdr) 
    {
        ct_crs = 0;
        return nullptr;
    }
    rdr >> ct_crs;
    rdr.ignore();

    Course* Crs = new Course[ct_crs];
    for (int i = 0; i < ct_crs; i++)
    {
        char ch; 
        int j = 0;
        rdr >> Crs[i].courseID;
        rdr.ignore();
        j = 0;
        while (rdr.peek() != '|')
        {
            rdr.get(ch);
            Crs[i].courseName[j++] = ch;
        }
        Crs[i].courseName[j] = '\0';
        rdr.ignore();
        j = 0;
        while (rdr.peek() != '|')
        {
            rdr.get(ch);
            Crs[i].instructor[j++] = ch;
        }
        Crs[i].instructor[j] = '\0';
        rdr.ignore();

        rdr >> Crs[i].credits; 
        rdr.ignore();
        rdr >> Crs[i].capacity; 
        rdr.ignore();
        rdr >> Crs[i].enrolled;
    }

    return Crs;
}
void saveCoursesToFile(const char* filename, Course* Crs, int ct)
{
    ofstream wtr(filename);
    if (!wtr) {
        cout << "Error opening file for writing!\n";
        return;
    }
    wtr << ct << "\n";
    for (int i = 0; i < ct; i++)
    {
        wtr << Crs[i].courseID << '|';
        wtr << Crs[i].courseName << '|';
        wtr << Crs[i].instructor << '|';
        wtr << Crs[i].credits << '|';
        wtr << Crs[i].capacity << '|';
        wtr << Crs[i].enrolled << "\n";
    }
}
Student* loadStudentsFromFile(const char* filename, int& ct)
{
    ifstream rdr(filename);
    if (!rdr)
    {
        ct = 0;
        return nullptr;
    }
    rdr >> ct;
    rdr.ignore();

    Student* St = new Student[ct];
    for (int i = 0; i < ct; i++)
    {
        char ch;
        int j = 0;
        rdr >> St[i].studentID;
        rdr.ignore();
        j = 0;
        while (rdr.peek() != '|')
        {
            rdr.get(ch);
            St[i].studentName[j++] = ch;
        }
        St[i].studentName[j] = '\0';
        rdr.ignore();
        j = 0;
        while (rdr.peek() != '|')
        {
            rdr.get(ch);
            St[i].department[j++] = ch;
        }
        St[i].department[j] = '\0';
        rdr.ignore();

        rdr >> St[i].semester;
        
    }

    return St;
}
void saveStudentsToFile(const char* filename,Student* St, int ct)
{
    ofstream wtr(filename);
    if (!wtr) {
        cout << "Error opening file for writing!\n";
        return;
    }
    wtr << ct << "\n";
    for (int i = 0; i < ct; i++)
    {
        wtr << St[i].studentID << '|';
        wtr << St[i].studentName << '|';
        wtr << St[i].department << '|';
        wtr << St[i].semester << "\n";
    }

}
Enrollment* loadEnrollmentsFromFile(const char* filename, int& ct) 
{
    ifstream rdr(filename);
    if (!rdr) {
        cout << "File not found!\n";
        ct = 0;
        return nullptr;
    }
    rdr >> ct;  
    rdr.ignore();
    Enrollment* enr = new Enrollment[ct];

    for (int i = 0; i < ct; i++) 
    {
        char ch;
        int j = 0;
        rdr >> enr[i].studentID;
        rdr.ignore(); 

        rdr >> enr[i].courseID;
        rdr.ignore();

        j = 0;
        while (rdr.peek() != '\n' && j < 19)
        { 
            rdr.get(ch);
            enr[i].enrollmentDate[j++] = ch;
        }
        enr[i].enrollmentDate[j] = '\0';
        rdr.ignore();
    }

    return enr;
}
void saveEnrollmentsToFile(const char* filename, Enrollment* enr, int ct)
{
    ofstream wtr(filename);
    if (!wtr) 
    {
        cout << "Error opening file for writing!\n";
        return;
    }
    wtr << ct << "\n";
    for (int i = 0; i < ct; i++) 
    {
        wtr << enr[i].studentID << '|';
        wtr << enr[i].courseID << '|';
        wtr << enr[i].enrollmentDate << "\n";
    }
}
//Utility Functions
void displayMenu() 
{
    cout << "\n\n\n\n1. Course Management" << "\n\n2. Student Management" << "\n\n3. Enrollment Management" << "\n\n4. Exit"<<"\n\nChoice-->";
}
bool validateInput() 
{
    return false;
}
void clearScreen() 
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
//CMS Display
void DisplayCms(int r, int c)
{
  color(6);
  for (int i = 0; i < (r/10)+3; i++)
      for (int j = 0; j < c; j++)
          cout << char(-37);

  gotoRowCol(r -10, 0);
  for (int i = r-10; i < r; i++)
      for (int j = 0; j < c; j++)
          cout << char(-37);

  color(10);
  for (int i = 0; i < 54; i++)
  {
      gotoRowCol((r / 2)-26+i, 0);
      for (int j = 0; j < c-2; j++)
      {
          if (i == 0 || i == 53)
              cout << char(-37);
          else
              cout << " ";
      }
      cout << endl;
      
  }
  color(15);
  gotoRowCol((r / 2) - 24, c / 4);
  cout << "==========================================================";
  gotoRowCol((r / 2) - 22, c / 4);
  cout << "      CMS PORTAL INFORMATION TECHNOLOGY UNIVERSITY";
  gotoRowCol((r / 2) - 20, c / 4);
  cout << "==========================================================";
  color(10);
  printlines((r / 2) - 18, (r / 2) - 18, 0, c-2,0.001,char(-37));
  color(15);
}
bool Psw(int R,int C) 
{
    char* password = new char[10];
    int count = 0;
    char ch;
    cout << "Enter password (max 9 chars): ";
    gotoRowCol(R / 2 - 4, C / 2 - 10);
    while (count < 9 && cin.get(ch) && ch != '\n')
    {
        password[count++] = ch;
    }
    password[count] = '\0';
    const char* correct = "itu123456";
    bool check = true;
    for (int i = 0; i < 9; i++) 
    {
        if (password[i] != correct[i]) 
        {
            check = false;
            break;
        }
    }
    if (password[9] != '\0') 
        check = false;

    delete[] password;
    return check;
}
bool compareStname(Student a, Student b)
{
    for (int i = 0; (a.studentName[i] != '\0' && b.studentName[i] != '\0'); i++)
    {
        if (a.studentName[i] < b.studentName[i])
            return false;

        if (a.studentName[i] > b.studentName[i])
            return true;
    }
    return true;
}
bool compareStID(Student a, Student b)
{
    return a.studentID > b.studentID;
}
bool compareStSem(Student a, Student b)
{
    return a.semester > b.semester;
}
bool compareCrsname(Course a, Course b)
{
    for (int i = 0;( a.courseName[i] != '\0' && b.courseName[i] != '\0'); i++)
    {
        if (a.courseName[i] < b.courseName[i])
            return false;
        if (a.courseName[i] > b.courseName[i])
            return true;
    }

    return true;
}
bool compareCrsID(Course a, Course b)
{
    return a.courseID > b.courseID;
}
bool compareCrs_enr(Course a, Course b)
{
    return a.enrolled > b.enrolled;
}
void sortStudents(Student* arr, int size, bool (*compare)(Student, Student))
{
    for (int i = 0; i < size ; i++)
    {
        for (int j = 0; j + 1 < size; j++)
        {
            if (compare(arr[j], arr[j + 1]))
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
void sortCourses(Course* arr, int size, bool (*compare)(Course, Course))
{
    for (int i = 0; i < size ; i++)
    {
        for (int j = 0; j + 1 < size; j++)
        {
            if (compare(arr[j], arr[j + 1]))
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}


int main() 
{
    int R = 80, C = 118;
    srand(time(0));

    Course* Crs = nullptr;
    int Ct_crs = 0;
    Student* St = nullptr;
    int Ct_st = 0;
    Enrollment* enr = nullptr;
    int Ct_enr = 0;

    gotoRowCol(R / 2 - 8, C / 2 - 10);
    cout << "ADMIN PASSWORD REQUIRED : ";
    gotoRowCol(R / 2 - 6, C / 2 - 10);
    if (Psw(R,C))
    {
        gotoRowCol(R / 2 - 2, C / 2 - 10);
        Sleep(2000);
        cout << "Access Granted !";
    }
    else
    {
        gotoRowCol(R / 2 - 2, C / 2 - 10);
        Sleep(2000);
        cout << "Acces Denied;!";
        Sleep(1000);
        exit(1);
    }
    Sleep(2000);

    Crs = loadCoursesFromFile("courses.txt", Ct_crs);
    St = loadStudentsFromFile("students.txt", Ct_st);
    enr = loadEnrollmentsFromFile("enrollments.txt", Ct_enr);

    int k;
    bool check = true;
    while (check)
    {
        clearScreen();
        DisplayCms(R, C);
        displayMenu();
        cin >> k;
        switch (k)
        {
        case 1:
        {
            clearScreen();
            DisplayCms(R, C);
            int Crs_choice;
            cout << "\n\n--- Course Management ---\n\n";
            cout << "1.Add Course"<< "\n\n2.View All Courses"<< "\n\n3.Update Course"<< "\n\n4.Delete Course"<< "\n\n5.Search Course"<< "\n\n6.Sort Courses"<< "\n\n7.Back\n";
            cout << "\n\nChoice --> ";
            cin >> Crs_choice;
            clearScreen();
            DisplayCms(R, C);
            switch (Crs_choice)
            {
            case 1:
                addCourse(Crs, Ct_crs, St, Ct_st);
                break;
            case 2:
                viewAllCourses(Crs, Ct_crs);
                break;
            case 3:
                updateCourse(Crs, Ct_crs);
                break;
            case 4:
                deleteCourse(Crs, Ct_crs);
                break;
            case 5:
                searchCourse(Crs, Ct_crs);
                break;
            case 6:
            {
                int C;
                cout << "\n\nSort Courses By:\n";
                cout << "\n1.Name\n";
                cout << "\n2.Course ID\n";
                cout << "\n3.Enrolled Count\n";
                cout << "\n\nChoice --> ";
                cin >> C;

                if (C == 1)
                    sortCourses(Crs, Ct_crs, compareCrsname);
                else if (C == 2)
                    sortCourses(Crs, Ct_crs, compareCrsID);
                else if (C == 3)
                    sortCourses(Crs, Ct_crs, compareCrs_enr);
                else
                    cout << "\n\nInvalid Choice!\n";
                cout << "\n\nSorted !\n";
                break;
            }
            case 7:
                break;
            default:
                cout << "\n\nInvalid Choice!\n";
            }
            _getch();
            break;
        }

        case 2:
        {
            clearScreen();
            DisplayCms(R, C);
            int St_choice;
            cout << "\n\n--- Student Management ---\n";
            cout << "\n1.Add Student" << "\n\n2.View All Students" << "\n\n3.Update Student" << "\n\n4.Delete Student" << "\n\n5.Search Student" << "\n\n6.Sort Students" << "\n\n7.Back\n";
            cout << "\nChoice --> ";
            cin >> St_choice;
            clearScreen();
            DisplayCms(R, C);
            switch (St_choice)
            {
            case 1:
                addStudent(Crs, Ct_crs, St, Ct_st);
                break;
            case 2:
                viewAllStudents(St, Ct_st);
                break;
            case 3:
                updateStudent(St, Ct_st);
                break;
            case 4:
                deleteStudent(St, Ct_st);
                break;
            case 5:
                searchStudent(St, Ct_st);
                break;
            case 6:
            {
                int S;
                cout << "\n\nSort Students By:\n";
                cout << "\n1.Name\n";
                cout << "\n2.Student ID\n";
                cout << "\n3.Semester\n";
                cout << "\n\nChoice --> ";
                cin >> S;
                if (S == 1)
                    sortStudents(St, Ct_st, compareStname);
                else if (S == 2)
                    sortStudents(St, Ct_st, compareStID);
                else if (S == 3)
                    sortStudents(St, Ct_st, compareStSem);
                else
                    cout << "\n\nInvalid Choice!\n";
                cout << "\n\nSorted !\n";
                break;
            }
            case 7:
                break;
            default:
                cout << "\n\nInvalid Choice!\n";
            }
            _getch();
            break;
        }

        case 3:
        {
            clearScreen();
            DisplayCms(R, C);
            int enr_choice;
            cout << "\n\n--- Enrollment Management ---\n";
            cout << "\n1.Enroll Student" << "\n\n2.View Student Enrollments" << "\n\n3.View Course Enrollments" << "\n\n4.Drop Course" << "\n\n5.Back\n";
            cout << "\nChoice --> ";
            cin >> enr_choice;
            clearScreen();
            DisplayCms(R, C);
            switch (enr_choice)
            {
            case 1:
                addEnrollment(enr, Ct_enr, St, Ct_st, Crs, Ct_crs);
                break;
            case 2:
                viewStudentEnrollments(enr, Ct_enr, Crs, Ct_crs, St, Ct_st);
                break;
            case 3: 
                viewCourseEnrollments(enr, Ct_enr, Crs, Ct_crs, St, Ct_st);
                break;
            case 4: 
                dropCourse(enr, Ct_enr, Crs, Ct_crs);
                break;
            case 5:
                break;
            default:
                cout << "\n\nInvalid choice!\n";
            }
            _getch();
            break;
        }

        case 4:
        {
            clearScreen();
            DisplayCms(R, C);
            cout << "\n\nExiting CMS...\n";
            saveCoursesToFile("courses.txt", Crs, Ct_crs);
            saveStudentsToFile("students.txt", St, Ct_st);
            saveEnrollmentsToFile("enrollments.txt", enr, Ct_enr);

            delete[] Crs;
            delete[] St;
            delete[] enr;
            check = false;
            break;
        }
        default:
            cout << "\n\nInvalid choice! Please try again.\n";
            _getch();
        }
    }



    return 0;
}
