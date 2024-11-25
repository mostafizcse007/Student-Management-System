#include <bits/stdc++.h>
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
using namespace std;
class Student
{
public:
    string stID, stName, stBlood, stEmail, stGender, stAddress, stGrade;
    string stPassHash;
    int subNo;
    double totalAvg;
    vector<double> subMarks;
    vector<string> subNames;
    Student *next;

    Student(const string &id, const string &name, const string &passHash, const string &blood,
            const string &email, const string &gender, const string &address, int number,
            bool readFromFile = true)
    {
        stID = id;
        stName = name;
        stPassHash = passHash;
        stBlood = blood;
        stEmail = email;
        stGender = gender;
        stAddress = address;
        subNo = number;
        next = nullptr;
        if (subNo > 0)
        {
            if (readFromFile)
            {
                try
                {
                    calculateAvgFromFile("input.txt");
                    calculateGrade();
                }
                catch (const exception &e)
                {
                    cerr << "Error: " << e.what() << endl;
                }
            }
        }
        else
        {
            cerr << "Error: Number of subjects must be greater than 0." << endl;
        }
    }
    void calculateAvgFromFile(const string &inputFilePath)
    {
        ifstream inputFile(inputFilePath);
        if (!inputFile.is_open() || inputFile.peek() == ifstream::traits_type::eof())
        {
            cout << "Please enter the subject names and marks." << endl;

            subMarks.clear();
            subNames.clear();
            double sum = 0;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            for (int i = 0; i < subNo; i++)
            {
                string subName;
                double mark;

                cout << "Enter subject name for subject " << i + 1 << ": ";
                getline(cin, subName);

                cout << "Enter marks for " << subName << ": ";
                while (!(cin >> mark) || mark < 0 || mark > 100)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid marks. Enter a number between 0 and 100: ";
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                subNames.push_back(subName);
                subMarks.push_back(mark);
                sum += mark;
            }

            totalAvg = sum / subNo;
            return;
        }

        subMarks.clear();
        subNames.clear();
        double sum = 0;
        int subjectCount = 0;

        while (true)
        {
            string subName;
            double mark;

            if (!getline(inputFile, subName))
                break;

            if (!(inputFile >> mark))
            {
                cerr << "Error: Failed to read marks for " << subName << ". Ensure file format is correct." << endl;
                return;
            }
            inputFile.ignore(numeric_limits<streamsize>::max(), '\n');

            if (mark < 0 || mark > 100)
            {
                cerr << "Error: Invalid marks for " << subName << ". Marks should be between 0 and 100." << endl;
                return;
            }

            subNames.push_back(subName);
            subMarks.push_back(mark);
            sum += mark;
            subjectCount++;
        }

        if (subjectCount == 0)
        {
            cerr << "Error: No valid data found in the file." << endl;
            return;
        }

        totalAvg = sum / subjectCount;
    }

    void calculateGrade()
    {
        if (totalAvg >= 80)
            stGrade = "A+";
        else if (totalAvg >= 75)
            stGrade = "A";
        else if (totalAvg >= 70)
            stGrade = "A-";
        else if (totalAvg >= 65)
            stGrade = "B+";
        else if (totalAvg >= 60)
            stGrade = "B";
        else if (totalAvg >= 55)
            stGrade = "B-";
        else if (totalAvg >= 50)
            stGrade = "C+";
        else if (totalAvg >= 45)
            stGrade = "C";
        else if (totalAvg >= 40)
            stGrade = "D";
        else
            stGrade = "F";
    }
    void viewPerformanceAnalysis() const
    {
        cout << CYAN << "\n===================================\n";
        cout << "       Performance Analysis       \n";
        cout << "===================================\n"
             << RESET;
        double highestMark = *max_element(subMarks.begin(), subMarks.end());
        double lowestMark = *min_element(subMarks.begin(), subMarks.end());
        double averageMark = accumulate(subMarks.begin(), subMarks.end(), 0.0) / subMarks.size();

        cout << "Highest Mark: " << highestMark << " in ";
        for (int i = 0; i < subMarks.size(); ++i)
        {
            if (subMarks[i] == highestMark)
            {
                cout << subNames[i] << " ";
            }
        }
        cout << endl;

        cout << "Lowest Mark: " << lowestMark << " in ";
        for (int i = 0; i < subMarks.size(); ++i)
        {
            if (subMarks[i] == lowestMark)
            {
                cout << subNames[i] << " ";
            }
        }
        cout << endl;

        cout << "Average Mark: " << averageMark << endl;

        cout << "Grade Distribution:" << endl;
        int gradeCounts[10] = {0};
        for (double mark : subMarks)
        {
            if (mark >= 80)
                gradeCounts[0]++;
            else if (mark >= 75)
                gradeCounts[1]++;
            else if (mark >= 70)
                gradeCounts[2]++;
            else if (mark >= 65)
                gradeCounts[3]++;
            else if (mark >= 60)
                gradeCounts[3]++;
            else if (mark >= 55)
                gradeCounts[3]++;
            else if (mark >= 50)
                gradeCounts[3]++;
            else if (mark >= 45)
                gradeCounts[3]++;
            else if (mark >= 40)
                gradeCounts[3]++;
            else
                gradeCounts[4]++;
        }
        cout << "A+: " << gradeCounts[0] << endl;
        cout << "A : " << gradeCounts[1] << endl;
        cout << "A-: " << gradeCounts[2] << endl;
        cout << "B+: " << gradeCounts[3] << endl;
        cout << "B: " << gradeCounts[4] << endl;
        cout << "B-: " << gradeCounts[5] << endl;
        cout << "C+: " << gradeCounts[6] << endl;
        cout << "C : " << gradeCounts[7] << endl;
        cout << "D : " << gradeCounts[8] << endl;
        cout << "F : " << gradeCounts[9] << endl;

        cout << CYAN << "===================================\n\n"
             << RESET;
    }

    void PrintStudent() const
    {
        cout << CYAN << "\n===================================\n";
        cout << "          Student Details          \n";
        cout << "===================================\n"
             << RESET;
        cout << setw(25) << left << "Student ID:" << stID << "\n";
        cout << setw(25) << left << "Student Name:" << stName << "\n";
        cout << setw(25) << left << "Blood Group:" << stBlood << "\n";
        cout << setw(25) << left << "Email Address:" << stEmail << "\n";
        cout << setw(25) << left << "Gender:" << stGender << "\n";
        cout << setw(25) << left << "House Address:" << stAddress << "\n";
        cout << setw(25) << left << "Number of Courses:" << subNo << "\n";
        cout << BLUE << "Subjects and Marks:\n"
             << RESET;
        for (int i = 0; i < subNames.size(); ++i)
        {
            cout << "- " << subNames[i] << ": " << subMarks[i] << endl;
        }
        cout << setw(25) << left << "Total Average:" << totalAvg << "\n";
        cout << setw(25) << left << "Grade:" << stGrade << "\n";
        cout << CYAN << "===================================\n\n"
             << RESET;
    }

    string toCSV() const
    {
        ostringstream ss;
        ss << stID << "," << stName << "," << stPassHash << "," << stBlood << ","
           << stEmail << "," << stGender << "," << stAddress << "," << subNo << ","
           << totalAvg << "," << stGrade;
        for (int i = 0; i < subNo; ++i)
        {
            ss << "," << subNames[i] << ":" << subMarks[i];
        }
        return ss.str();
    }

    static Student fromCSV(const string &line)
    {
        istringstream ss(line);
        string id, name, passHash, blood, email, gender, address, grade;
        int number;
        double avg;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, passHash, ',');
        getline(ss, blood, ',');
        getline(ss, email, ',');
        getline(ss, gender, ',');
        getline(ss, address, ',');
        ss >> number;
        ss.ignore();
        ss >> avg;
        ss.ignore();
        getline(ss, grade, ',');
        Student student(id, name, passHash, blood, email, gender, address, number, false);
        student.totalAvg = avg;
        student.stGrade = grade;

        string subNameMark;
        while (getline(ss, subNameMark, ','))
        {
            size_t pos = subNameMark.find(':');
            if (pos != string::npos)
            {
                string subName = subNameMark.substr(0, pos);
                double mark = stod(subNameMark.substr(pos + 1));
                student.subNames.push_back(subName);
                student.subMarks.push_back(mark);
            }
        }
        return student;
    }
    void saveToCSV() const
    {
        ofstream file("students.csv", ios::app);
        if (!file.is_open())
        {
            cerr << "Error opening file for writing." << endl;
            return;
        }
        file << toCSV() << endl;
        file.close();
    }
    void modifyInfo()
    {
        int choice;
        while (true)
        {
            cout << CYAN << "\n-----------------------------------\n";
            cout << "       Modify Student Info         \n";
            cout << "-----------------------------------\n"
                 << RESET;
            cout << "1. Modify Name\n";
            cout << "2. Modify Blood Group\n";
            cout << "3. Modify Email Address\n";
            cout << "4. Modify Gender\n";
            cout << "5. Modify Address\n";
            cout << "6. Modify Number of Courses\n";
            cout << "7. Modify Subjects and Marks\n";
            cout << "8. Exit Modification Menu\n";
            cout << YELLOW << "Enter your choice: " << RESET;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice)
            {
            case 1:
                cout << "Enter new student name: ";
                getline(cin, stName);
                cout << GREEN << "Name updated successfully." << RESET << endl;
                break;
            case 2:
                cout << "Enter new blood group: ";
                getline(cin, stBlood);
                cout << GREEN << "Blood group updated successfully." << RESET << endl;
                break;
            case 3:
                cout << "Enter new email address: ";
                getline(cin, stEmail);
                cout << GREEN << "Email address updated successfully." << RESET << endl;
                break;
            case 4:
                cout << "Enter new gender: ";
                getline(cin, stGender);
                cout << GREEN << "Gender updated successfully." << RESET << endl;
                break;
            case 5:
                cout << "Enter new address: ";
                getline(cin, stAddress);
                cout << GREEN << "Address updated successfully." << RESET << endl;
                break;
            case 6:
                cout << "Enter new number of courses: ";
                cin >> subNo;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                calculateAvgFromFile("input.txt");
                calculateGrade();
                cout << GREEN << "Number of courses updated successfully." << RESET << endl;
                break;
            case 7:
                cout << "Re-enter subjects and marks:\n";
                calculateAvgFromFile("input.txt");
                calculateGrade();
                cout << GREEN << "Subjects and marks updated successfully." << RESET << endl;
                break;
            case 8:
                cout << "Exiting modification menu." << endl;
                return;
            default:
                cout << RED << "Invalid choice. Please try again." << RESET << endl;
            }
            saveToCSV();
            cout << GREEN << "Changes saved successfully." << RESET << endl;
        }
    }
};

class Management
{
public:
    Student *head;
    const string fileName = "students.csv";
    const string deletedFile = "deleted_students.txt";

    Management() : head(nullptr) {}

    ~Management()
    {
        clearMemory();
    }

    Student *findID(const string &id) const
    {
        Student *temp = head;
        while (temp)
        {
            if (temp->stID == id)
                return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    Student *findEmail(const string &email) const
    {
        Student *temp = head;
        while (temp)
        {
            if (temp->stEmail == email)
                return temp;
            temp = temp->next;
        }
        return nullptr;
    }
    Student *findPass(const string &pass) const
    {
        Student *temp = head;
        while (temp)
        {
            if (temp->stPassHash == pass)
                return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    vector<Student *> convertListToVector() const
    {
        vector<Student *> studentVector;
        Student *temp = head;
        while (temp)
        {
            studentVector.push_back(temp);
            temp = temp->next;
        }
        return studentVector;
    }

    void sortStudentsByAverage()
    {
        vector<Student *> studentVector = convertListToVector();

        sort(studentVector.begin(), studentVector.end(), [](Student *a, Student *b)
             { return a->totalAvg < b->totalAvg; });

        head = nullptr;
        for (auto student : studentVector)
        {
            student->next = head;
            head = student;
        }
        cout << "Students sorted by their average marks successfully." << endl;
        saveToCSV();
        cout << GREEN << "Changes saved successfully." << RESET << endl;
    }
    void addStudent(const string &id, const string &name, const string &passHash,
                    const string &blood, const string &email, const string &gender,
                    const string &address, int number)
    {
        if (findID(id) != nullptr)
        {
            cout << RED << "Student with ID: " << id << " already exists." << RESET << endl;
            return;
        }
        if (findEmail(email) != nullptr)
        {
            cout << "Student with Email: " << email << " already present in our system." << endl;
            return;
        }
        Student *newStudent = new Student(id, name, passHash, blood, email, gender, address, number);
        newStudent->next = head;
        head = newStudent;
        cout << GREEN << "Student information added successfully." << RESET << endl;
        saveToCSV();
        cout << GREEN << "Changes saved successfully." << RESET << endl;
    }
    void removeStudent(const string &id)
    {
        if (!head)
        {
            cout << "The student list is empty. No student to remove." << endl;
            return;
        }
        Student *temp = findID(id);
        if (temp == nullptr)
        {
            cout << "Student with ID: " << id << " is not found in our system." << endl;
            return;
        }
        if (head->stID == id)
        {
            Student *toDelete = head;
            head = head->next;
            saveDeletedStudent(toDelete);
            delete toDelete;
            cout << "Student with ID: " << id << " deleted successfully from our system." << endl;
            saveToCSV();
            cout << GREEN << "Changes saved automatically." << RESET << endl;
            return;
        }
        Student *curr = head->next;
        Student *prev = head;
        while (curr && curr->stID != id)
        {
            prev = curr;
            curr = curr->next;
        }
        if (curr)
        {
            prev->next = curr->next;
            saveDeletedStudent(curr);
            delete curr;
            cout << "Student with ID: " << id << " deleted successfully from our system." << endl;
            saveToCSV();
            cout << GREEN << "Changes saved successfully." << RESET << endl;
        }
    }
    void modifyStudentInfo(const string &id)
    {
        Student *temp = findID(id);
        if (temp == nullptr)
        {
            cout << RED << "Student with ID: " << id << " not found in our system." << RESET << endl;
            return;
        }
        temp->modifyInfo();
        cout << GREEN << "Student information modified successfully." << RESET << endl;
    }

    void restoreDeletedStudentByID(const string &id)
    {
        ifstream file(deletedFile);
        if (!file.is_open())
        {
            cout << "No deleted students to restore." << endl;
            return;
        }

        vector<string> lines;
        string line;
        bool found = false;

        while (getline(file, line))
        {
            Student student = Student::fromCSV(line);
            if (student.stID == id)
            {
                Student *newStudent = new Student(student.stID, student.stName, student.stPassHash,
                                                  student.stBlood, student.stEmail, student.stGender,
                                                  student.stAddress, student.subNo, false);
                newStudent->subNames = student.subNames;
                newStudent->subMarks = student.subMarks;
                newStudent->totalAvg = student.totalAvg;
                newStudent->stGrade = student.stGrade;
                newStudent->next = head;
                head = newStudent;
                found = true;
                cout << "Student with ID: " << id << " restored successfully." << endl;
            }
            else
                lines.push_back(line);
        }
        file.close();

        if (!found)
        {
            cout << "Student with ID: " << id << " not found in deleted students." << endl;
        }
        else
        {
            ofstream outFile(deletedFile);
            if (outFile.is_open())
            {
                for (const string &l : lines)
                {
                    outFile << l << endl;
                }
                outFile.close();
            }
            else
            {
                cerr << "Error updating deleted students file." << endl;
            }
            saveToCSV();
            cout << GREEN << "Changes saved successfully." << RESET << endl;
        }
    }
    int totalStudent() const
    {
        Student *temp = head;
        int cnt = 0;
        while (temp)
        {
            cnt++;
            temp = temp->next;
        }
        return cnt;
    }
    void changePassword(const string &id, const string &oldPassHash, const string &newPassHash)
    {
        Student *temp = findID(id);
        if (temp == nullptr)
        {
            cout << "Student with ID: " << id << " not found in our system." << endl;
            return;
        }
        if (oldPassHash == newPassHash)
        {
            cout << "Your current password matches previous password." << endl;
            cout << "Come again next time with something unique in mind." << endl;
            return;
        }
        if (oldPassHash == temp->stPassHash)
        {
            if (!isValidPassword(newPassHash))
            {
                cout << "New password does not meet security requirements." << endl;
                return;
            }
            temp->stPassHash = newPassHash;
            cout << "Password changed successfully." << endl;
        }
        else
        {
            cout << "Password doesn't match." << endl;
        }
    }
    bool isValidPassword(const string &password) const
    {
        if (password.length() < 8)
            return false;
        bool hasUpper = false, hasLower = false, hasDigit = false;
        for (char c : password)
        {
            if (isupper(c))
                hasUpper = true;
            if (islower(c))
                hasLower = true;
            if (isdigit(c))
                hasDigit = true;
        }
        return hasUpper && hasLower && hasDigit;
    }
    void searchByGender(const std::string &gender) const
    {
        Student *temp = head;
        bool found = false;

        while (temp)
        {
            if (temp->stGender == gender)
            {
                found = true;
                temp->PrintStudent();
                cout << "------------------------" << endl;
            }
            temp = temp->next;
        }

        if (!found)
        {
            std::cout << "No student with the gender '" << gender << "' found in the system." << std::endl;
        }
    }
    void loadFromCSV()
    {
        ifstream file(fileName);
        if (!file.is_open())
        {
            cerr << "Error opening file for reading." << endl;
            return;
        }

        string line;
        while (getline(file, line))
        {
            Student student = Student::fromCSV(line);
            Student *newStudent = new Student(student.stID, student.stName, student.stPassHash,
                                              student.stBlood, student.stEmail, student.stGender,
                                              student.stAddress, student.subNo, false);
            newStudent->subNames = student.subNames;
            newStudent->subMarks = student.subMarks;
            newStudent->totalAvg = student.totalAvg;
            newStudent->stGrade = student.stGrade;
            newStudent->next = head;
            head = newStudent;
        }
        file.close();
    }
    void saveDeletedStudent(Student *student) const
    {
        ofstream file(deletedFile, ios::app);
        if (!file.is_open())
        {
            cerr << "Error opening file to save deleted students." << endl;
            return;
        }
        file << student->toCSV() << endl;
        file.close();
    }
    void showAllDeletedStudents() const
    {
        ifstream file(deletedFile);
        if (!file.is_open())
        {
            cout << "No deleted students to show." << endl;
            return;
        }

        string line;
        bool found = false;

        while (getline(file, line))
        {
            if (!line.empty())
            {
                Student student = Student::fromCSV(line);
                student.PrintStudent();
                found = true;
                cout << "------------------------" << endl;
            }
        }
        file.close();

        if (!found)
        {
            cout << "No deleted students found in the system." << endl;
        }
    }
    void modifyStudent(const string &id, const string &newid, const string &name, const string &blood, const string &email, const string &gender, const string &address, int number)
    {
        Student *temp = findID(id);
        if (temp == nullptr)
        {
            cout << "Student with ID: " << id << " is not found in our system." << endl;
            return;
        }
        temp->stID = newid;
        temp->stName = name;
        temp->stBlood = blood;
        temp->stEmail = email;
        temp->stGender = gender;
        temp->stAddress = address;
        temp->subNo = number;
        temp->calculateAvgFromFile("input.txt");
        temp->calculateGrade();
        cout << "All information modified successfully." << endl;
    }
    void searchByID(const string &id) const
    {
        Student *temp = findID(id);
        if (temp == nullptr)
        {
            cout << "Student with ID: " << id << " not found in our system." << endl;
            return;
        }
        temp->PrintStudent();
    }
    void searchByName(const string &name) const
    {
        Student *temp = head;
        bool found = false;

        while (temp)
        {
            if (temp->stName == name)
            {
                found = true;
                temp->PrintStudent();
                cout << "------------------------" << endl;
            }
            temp = temp->next;
        }
        if (!found)
        {
            cout << "No student with the name '" << name << "' found in the system." << endl;
        }
    }
    void searchByEmail(const string &email) const
    {
        Student *temp = findEmail(email);
        if (temp == nullptr)
        {
            cout << "Student with Email: " << email << " not found in our system." << endl;
            return;
        }
        temp->PrintStudent();
    }

    void searchByRange(double low, double high) const
    {
        Student *temp = head;
        bool found = false;

        while (temp)
        {
            if (temp->totalAvg >= low && temp->totalAvg <= high)
            {
                found = true;
                temp->PrintStudent();
                cout << "------------------------" << endl;
            }
            temp = temp->next;
        }

        if (!found)
        {
            cout << "No student found in the marks range between '" << low << " and " << high << "' found in the system." << endl;
        }
    }
    int countDeletedStudents() const
    {
        ifstream file(deletedFile);
        if (!file.is_open())
        {
            return 0;
        }
        int count = 0;
        string line;
        while (getline(file, line))
        {
            if (!line.empty())
                ++count;
        }
        file.close();
        return count;
    }
    void clearMemory()
    {
        while (head)
        {
            Student *temp = head;
            head = head->next;
            delete temp;
        }
    }
    void saveToCSV() const
    {
        ofstream file(fileName, ios::trunc);
        if (!file.is_open())
        {
            cerr << "Error opening file for writing." << endl;
            return;
        }
        Student *curr = head;
        while (curr)
        {
            file << curr->toCSV() << endl;
            curr = curr->next;
        }
        file.close();
    }
};
class Control
{
    Management user;
    string adminUsername = "admin";
    string adminPassHash = "admin123";
    void clearScreen()
    {
        cout << "\033[2J\033[1;1H";
    }
    void pauseScreen()
    {
        cout << GREEN << "Press Enter to continue..." << RESET << endl;
        cin.get();
    }
    void printMainMenu()
    {
        cout << CYAN << "===================================\n";
        cout << "         Student Management        \n";
        cout << "===================================\n"
             << RESET;
        cout << BLUE << "1. Admin Login\n";
        cout << "2. Student Login\n";
        cout << "3. Exit\n"
             << RESET;
        cout << YELLOW << "Enter your choice: " << RESET;
    }
    void printAdminMenu()
    {
        cout << CYAN << "===================================\n";
        cout << "            Admin Menu             \n";
        cout << "===================================\n"
             << RESET;
        cout << BLUE << "1. Add Account\n";
        cout << "2. Remove Account\n";
        cout << "3. Show All Student Accounts\n";
        cout << "4. Modify Account\n";
        cout << "5. Search Account by Different Criteria\n";
        cout << "6. Save Student Data\n";
        cout << "7. Restore Deleted Students\n";
        cout << "8. Sort Students by Their Grade\n";
        cout << "9. Total Active and Inactive Students\n";
        cout << "10. Show All Deleted Accounts\n";
        cout << "11. Log Out\n"
             << RESET;
        cout << YELLOW << "Enter your choice: " << RESET;
    }
    void printUserMenu()
    {
        cout << CYAN << "===================================\n";
        cout << "             User Menu             \n";
        cout << "===================================\n"
             << RESET;
        cout << BLUE << "1. View Details\n";
        cout << "2. Update Information\n";
        cout << "3. Change Password\n";
        cout << "4. View Performance Analysis\n";
        cout << "5. Log Out\n"
             << RESET;
        cout << YELLOW << "Enter your choice: " << RESET;
    }

public:
    Control()
    {
        user.loadFromCSV();
    }

    void adminMenu()
    {
        string stID, stName, stPass, stBlood, stEmail, stGender, stAddress;
        int subNo;
        while (true)
        {
            clearScreen();
            printAdminMenu();
            int choice;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch (choice)
            {
            case 1:
                cout << "Enter student ID: ";
                getline(cin, stID);
                cout << "Enter student name: ";
                getline(cin, stName);
                cout << "Enter a strong password: ";
                getline(cin, stPass);
                cout << "Enter student's blood group: ";
                getline(cin, stBlood);
                cout << "Enter student's email address: ";
                getline(cin, stEmail);
                cout << "Enter student's gender: ";
                getline(cin, stGender);
                cout << "Enter student's address: ";
                getline(cin, stAddress);
                cout << "Number of subject to be enrolled: ";
                cin >> subNo;
                user.addStudent(stID, stName, stPass, stBlood, stEmail, stGender, stAddress, subNo);
                break;
            case 2:
                if (user.totalStudent() == 0)
                {
                    cout << "No student in our system." << endl;
                    break;
                }
                cout << "Enter student ID to remove: ";
                getline(cin, stID);
                user.removeStudent(stID);
                break;
            case 3:
                if (user.totalStudent() == 0)
                {
                    cout << "No student in our system." << endl;
                    break;
                }
                {
                    vector<Student *> students = user.convertListToVector();
                    for (Student *student : students)
                    {
                        student->PrintStudent();
                        cout << "------------------------" << endl;
                    }
                }
                break;
            case 4:
                cout << "Enter student ID to modify: ";
                getline(cin, stID);
                user.modifyStudentInfo(stID);
                break;
            case 5:
                int searchChoice;
                cout << "Search by: 1. ID 2. Name 3. Email 4. Average Range 5.Gender" << endl;
                cout << "Enter your choice: ";
                cin >> searchChoice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                switch (searchChoice)
                {
                case 1:
                    cout << "Enter student ID: ";
                    getline(cin, stID);
                    user.searchByID(stID);
                    break;
                case 2:
                    cout << "Enter student name: ";
                    getline(cin, stName);
                    user.searchByName(stName);
                    break;
                case 3:
                    cout << "Enter student email: ";
                    getline(cin, stEmail);
                    user.searchByEmail(stEmail);
                    break;
                case 4:
                    double low, high;
                    cout << "Enter low range: ";
                    cin >> low;
                    cout << "Enter high range: ";
                    cin >> high;
                    user.searchByRange(low, high);
                    break;
                case 5:
                    cout << "Enter gender: ";
                    user.searchByGender(stGender);
                    break;
                default:
                    cout << "Invalid choice." << endl;
                }
                break;
            case 6:
                user.saveToCSV();
                cout << "Information updated successfully." << endl;
                break;
            case 7:
            {
                cout << "Enter student ID to restore: ";
                string restoreID;
                getline(cin, restoreID);
                user.restoreDeletedStudentByID(restoreID);
                break;
            }
            case 8:
                cout << "Warning: If multiple students have same grade then we sort them based on their average marks" << endl;
                user.sortStudentsByAverage();
                break;
            case 9:
            {
                int activeCount = user.totalStudent();
                int deletedCount = user.countDeletedStudents();
                cout << "Total active students: " << activeCount << endl;
                cout << "Total inactive students: " << deletedCount << endl;
                break;
            }
            case 10:
                user.showAllDeletedStudents();
                break;
            case 11:
                cout << "Logging out..." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
            pauseScreen();
        }
    }

    void userMenu(const string &studentID)
    {
        Student *student = user.findID(studentID);
        if (!student)
        {
            cout << RED << "Student not found." << RESET << endl;
            pauseScreen();
            return;
        }

        string newPass;
        while (true)
        {
            clearScreen();
            printUserMenu();
            int choice;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch (choice)
            {
            case 1:
                student->PrintStudent();
                break;
            case 2:
                student->modifyInfo();
                break;
            case 3:
                cout << "Enter your old password: ";
                getline(cin, student->stPassHash);
                cout << "Enter a new password: ";
                getline(cin, newPass);
                user.changePassword(student->stID, student->stPassHash, newPass);
                break;
            case 4:
                student->viewPerformanceAnalysis();
                break;
            case 5:
                cout << "Logging out..." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
            pauseScreen();
        }
    }
    void login()
    {

        string userAdmin, passAdmin, stuId, stuPass;

        while (true)
        {
            clearScreen();
            printMainMenu();
            int choice;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            try
            {
                switch (choice)
                {
                case 1:
                    cout << "Enter admin username: ";
                    getline(cin, userAdmin);
                    cout << "Enter admin password: ";
                    getline(cin, passAdmin);
                    if (userAdmin == adminUsername && passAdmin == adminPassHash)
                    {
                        adminMenu();
                    }
                    else
                    {
                        cout << "Invalid information." << endl;
                    }
                    break;

                case 2:
                    cout << "Enter student ID: ";
                    getline(cin, stuId);
                    cout << "Enter student password: ";
                    getline(cin, stuPass);
                    {
                        Student *student = user.findID(stuId);
                        if (student && student->stPassHash == stuPass)
                        {
                            cout << "Student login successful!" << endl;
                            userMenu(stuId);
                        }
                        else
                        {
                            cout << "Invalid student ID or password." << endl;
                        }
                    }
                    break;

                case 3:
                    cout << "Exiting system. Goodbye!" << endl;
                    return;

                default:
                    cout << "Invalid choice." << endl;
                }
            }
            catch (const exception &e)
            {
                cerr << "An error occurred: " << e.what() << endl;
            }
            pauseScreen();
        }
    }
};

int main()
{
    Control control;
    control.login();
    return 0;
}