#include <bits/stdc++.h>
struct Student {
    std::string name;
    std::string admno;
    int pmark, cmark, mmark, emark, csmark, attend;
    double agg;
};

void create_rec() {
    std::ifstream f1("Student.dat", std::ios::binary);
    std::vector<std::string> lst;
    Student temp;

    while (f1.read(reinterpret_cast<char*>(&temp), sizeof(Student))) {
        lst.push_back(temp.admno);
    }
    f1.close();

    std::ofstream f2("Student.dat", std::ios::binary | std::ios::app);
    
    while (true) {
        Student d;
        std::cout << "Enter Name: ";
        std::cin >> d.name;
        std::cout << "Enter Admission number: ";
        std::cin >> d.admno;

        if (std::find(lst.begin(), lst.end(), d.admno) == lst.end()) {
            lst.push_back(d.admno);
        } else {
            std::cout << "Record with this admission number already exists!" << std::endl;
            break;
        }

        std::cout << "Enter Marks out of 100 in Physics: ";
        std::cin >> d.pmark;
        std::cout << "Enter Marks out of 100 in Chemistry: ";
        std::cin >> d.cmark;
        std::cout << "Enter Marks out of 100 in Maths: ";
        std::cin >> d.mmark;
        std::cout << "Enter Marks out of 100 in English: ";
        std::cin >> d.emark;
        std::cout << "Enter Marks out of 100 in Computer science: ";
        std::cin >> d.csmark;
        std::cout << "Enter the no. of days attended school: ";
        std::cin >> d.attend;

        d.agg = (d.pmark + d.cmark + d.mmark + d.emark + d.csmark) / 5.0;

        f2.write(reinterpret_cast<char*>(&d), sizeof(Student));
        std::cout << "Student record successfully created!" << std::endl;

        std::string ask;
        std::cout << "Do you want to input more records? (Y/N): ";
        std::cin >> ask;
        if (ask != "Y" && ask != "y") {
            break;
        }
    }
    f2.close();
}

void delete_rec() {
    std::string rec;
    std::cout << "Enter the admission number of the student whose record is to be deleted: ";
    std::cin >> rec;

    bool f = false;
    std::ifstream f2("Student.dat", std::ios::binary);
    std::ofstream f3("Student2.dat", std::ios::binary);
    Student temp;

    while (f2.read(reinterpret_cast<char*>(&temp), sizeof(Student))) {
        if (temp.admno == rec) {
            f = true;
        } else {
            f3.write(reinterpret_cast<char*>(&temp), sizeof(Student));
        }
    }
    f2.close();
    f3.close();

    std::ifstream f4("Student2.dat", std::ios::binary);
    std::ofstream f5("Student.dat", std::ios::binary);

    while (f4.read(reinterpret_cast<char*>(&temp), sizeof(Student))) {
        f5.write(reinterpret_cast<char*>(&temp), sizeof(Student));
    }
    f4.close();
    f5.close();

    if (!f) {
        std::cout << "Student record not found!" << std::endl;
    } else {
        std::cout << "Student record successfully deleted." << std::endl;
    }
}
void modify_rec() {
    std::string adm;
    std::cout << "Enter admission number of student whose details are to be changed: ";
    std::cin >> adm;

    std::fstream f2("Student.dat", std::ios::in | std::ios::out | std::ios::binary);
    Student i;
    bool f = false;

    while (f2.read(reinterpret_cast<char*>(&i), sizeof(Student))) {
        if (i.admno == adm) {
            f = true;
            std::streampos pntr = f2.tellg() - static_cast<std::streampos>(sizeof(Student));

            std::cout << "Enter updated Name: ";
            std::cin >> i.name;
            std::cout << "Enter new Marks in Physics: ";
            std::cin >> i.pmark;
            std::cout << "Enter new Marks in Chemistry: ";
            std::cin >> i.cmark;
            std::cout << "Enter new Marks in Maths: ";
            std::cin >> i.mmark;
            std::cout << "Enter new Marks in English: ";
            std::cin >> i.emark;
            std::cout << "Enter new Marks in Computer science: ";
            std::cin >> i.csmark;
            std::cout << "Enter the updated no. of days attended school: ";
            std::cin >> i.attend;

            i.agg = (i.pmark + i.cmark + i.mmark + i.emark + i.csmark) / 5.0;

            f2.seekp(pntr);
            f2.write(reinterpret_cast<char*>(&i), sizeof(Student));
            break;
        }
    }

    f2.close();

    if (!f) {
        std::cout << "Student record not found!" << std::endl;
    } else {
        std::cout << "Student record successfully modified!" << std::endl;
    }
}
void search() {
    std::string sd;
    std::cout << "Enter the admission no of student to get details : ";
    std::cin >> sd;

    std::ifstream f1("Student.dat", std::ios::binary);
    Student i;
    bool f = false;

    while (f1.read(reinterpret_cast<char*>(&i), sizeof(Student))) {
        if (i.admno == sd) {
            f = true;
            std::cout << "\nSTUDENT REPORT" << std::endl;
            std::cout << "Admission NO. : " << i.admno << std::endl;
            std::cout << "NAME : " << i.name << std::endl;
            std::cout << "Attendance : " << i.attend << std::endl;
            std::cout << "MARKS IN FOLLOWING SUBJECTS : " << std::endl;
            std::cout << "PHYSICS   : " << i.pmark << std::endl;
            std::cout << "CHEMISTRY : " << i.cmark << std::endl;
            std::cout << "MATHS     : " << i.mmark << std::endl;
            std::cout << "ENGLISH   : " << i.emark << std::endl;
            std::cout << "COMPUTER  : " << i.csmark << std::endl;
            std::cout << "Aggregate percentage : " << i.agg << "%" << std::endl;
            break;
        }
    }

    f1.close();
    if (!f) {
        std::cout << "No such record found!" << std::endl;
    }
}
void display() {
    std::ifstream f1("student.dat", std::ios::binary);
    std::vector<double> l;
    int c = 0;
    Student i;

    std::cout << "AGGREGATE PERCENTAGE OF STUDENTS: " << std::endl;
    while (f1.read(reinterpret_cast<char*>(&i), sizeof(Student))) {
        std::cout << i.admno << " " << i.name << " scored " << i.agg << "%" << std::endl;
        c++;
        l.push_back(i.agg);
    }

    f1.close();

    if (c > 0) {
        double avg = std::accumulate(l.begin(), l.end(), 0.0) / c;
        std::cout << "Class average is " << avg << "%" << std::endl;
    }
    std::cout << "DATA DISPLAYED!" << std::endl;
}
void fail() {
    std::ifstream f1("student.dat", std::ios::binary);
    Student i;
    int c = 0;

    std::cout << "FOLLOWING STUDENTS HAVE FAILED: " << std::endl;
    while (f1.read(reinterpret_cast<char*>(&i), sizeof(Student))) {
        if (i.agg <= 33) {
            std::cout << i.admno << " " << i.name << " has failed" << std::endl;
            c++;
        }
    }
    f1.close();

    if (c == 0) {
        std::cout << "No one failed." << std::endl;
    } else {
        std::cout << "Total students failed : " << c << std::endl;
    }
}

void merit() {
    std::cout << "First 3 rank holders are:" << std::endl;
    std::ifstream f("Student.dat", std::ios::binary);
    std::vector<double> l;
    Student i;

    while (f.read(reinterpret_cast<char*>(&i), sizeof(Student))) {
        l.push_back(i.agg);
    }
    f.close();

    std::sort(l.begin(), l.end(), std::greater<double>());
    l.erase(std::unique(l.begin(), l.end()), l.end());

    std::vector<std::string> l1, l2, l3;
    std::ifstream f1("Student.dat", std::ios::binary);

    while (f1.read(reinterpret_cast<char*>(&i), sizeof(Student))) {
        std::string det = i.admno + " " + i.name;
        if (i.agg == l[0]) {
            l1.push_back(det);
        }
        if (l.size() > 1 && i.agg == l[1]) {
            l2.push_back(det);
        }
        if (l.size() > 2 && i.agg == l[2]) {
            l3.push_back(det);
        }
    }
    f1.close();

    std::cout << "Student(s) holding rank 1:" << std::endl;
    for (const auto& s : l1) {
        std::cout << s << std::endl;
    }
    std::cout << "Student(s) holding rank 2:" << std::endl;
    for (const auto& s : l2) {
        std::cout << s << std::endl;
    }
    std::cout << "Student(s) holding rank 3:" << std::endl;
    for (const auto& s : l3) {
        std::cout << s << std::endl;
    }
    std::cout << "Congratulations to all the students!" << std::endl;
}
void print_line(int length = 70) {
    std::cout << std::string(length, '=') << std::endl;
}
void intro() {
    print_line();
    std::cout << "SCHOOL DATA MANAGEMENT SYSTEM" << std::endl;
    std::cout << "REPORT DATA OF STUDENTS OF CLASS 12 FOR 1ST TERM: SESSION 2023-24" << std::endl;
    print_line();
    std::cout << std::endl;
}

void main_menu() {
    std::cout << "\nMAIN MENU" << std::endl;
    std::cout << "1. REPORT MENU" << std::endl;
    std::cout << "2. ADMIN MENU" << std::endl;
    std::cout << "3. EXIT" << std::endl;
}

void report_menu() {
    std::cout << "\nREPORT MENU" << std::endl;
    std::cout << "1. CLASS RESULT" << std::endl;
    std::cout << "2. LIST OF STUDENTS WITH MERIT" << std::endl;
    std::cout << "3. LIST OF STUDENTS WHO FAILED" << std::endl;
    std::cout << "4. BACK TO MAIN MENU" << std::endl;
}

void admin_menu() {
    std::cout << "\nADMIN MENU" << std::endl;
    std::cout << "1. CREATE STUDENT RECORD" << std::endl;
    std::cout << "2. SEARCH STUDENT RECORD" << std::endl;
    std::cout << "3. MODIFY STUDENT RECORD" << std::endl;
    std::cout << "4. DELETE STUDENT RECORD" << std::endl;
    std::cout << "5. BACK TO MAIN MENU" << std::endl;
}
int get_int_input() {
    int choice;
    while (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number: ";
    }
    return choice;
}

void main2() {
    intro();
    while (true) {
        main_menu();
        std::cout << "ENTER CHOICE 1-3 : ";
        int choice = get_int_input();
        std::cout << std::endl;

        if (choice == 1) {
            while (true) {
                report_menu();
                std::cout << "Enter choice 1-4 : ";
                int rchoice = get_int_input();
                std::cout << std::endl;

                switch (rchoice) {
                    case 1: display(); break;
                    case 2: merit(); break;
                    case 3: fail(); break;
                    case 4: goto end_report_menu;
                    default: std::cout << "INVALID INPUT!!!" << std::endl;
                }
                std::cout << std::endl;
            }
            end_report_menu:;
        }
        else if (choice == 2) {
            while (true) {
                admin_menu();
                std::cout << "Enter choice 1-5 : ";
                int rchoice = get_int_input();
                std::cout << std::endl;

                switch (rchoice) {
                    case 1: create_rec(); break;
                    case 2: search(); break;
                    case 3: modify_rec(); break;
                    case 4: delete_rec(); break;
                    case 5: goto end_admin_menu;
                    default: std::cout << "INVALID INPUT!!!" << std::endl;
                }
                std::cout << std::endl;
            }
            end_admin_menu:;
        }
        else if (choice == 3) {
            std::cout << "THANKS FOR USING STUDENT DATABASE MANAGEMENT SYSTEM" << std::endl;
            break;
        }
        else {
            std::cout << "INVALID INPUT!!!" << std::endl;
            std::cout << std::endl;
        }
    }
    
}

int main() {
    // COMPUTER SCIENCE PROJECT
    std::ofstream f("Student.dat", std::ios::app | std::ios::binary);
    if (!f) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }
    f.close();

    if (!f) {
        std::cerr << "Error closing file!" << std::endl;
        return 1;
    }

    std::cout << "File 'Student.dat' opened and closed successfully." << std::endl;
    main2();
    return 0;
}
