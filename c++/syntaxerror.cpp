#include <bits/stdc++.h>
struct Student {
    std::string name;
    std::string admno;
    int pmark, cmark, mmark, emark, csmark;
    int attend;
    float agg;
};

void create_rec() {
    std::vector<std::string> admno_list;
    Student student;
    std::map<std::string, Student> d;

    std::ifstream fin("Student.dat", std::ios::binary);
    if (fin.is_open()) {
        while (fin.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
            admno_list.push_back(student.admno);
        }
        fin.close();
    }

    std::ofstream fout("Student.dat", std::ios::binary | std::ios::app);
    
    while (true) {
        std::cout << "Enter Name: ";
        std::cin >> student.name;

        std::cout << "Enter Admission number: ";
        std::cin >> student.admno;

        if (std::find(admno_list.begin(), admno_list.end(), student.admno) != admno_list.end()) {
            std::cout << "Record with this admission number already exists!" << std::endl;
            break;
        }

        admno_list.push_back(student.admno);

        std::cout << "Enter Marks out of 100 in Physics: ";
        std::cin >> student.pmark;
        std::cout << "Enter Marks out of 100 in Chemistry: ";
        std::cin >> student.cmark;
        std::cout << "Enter Marks out of 100 in Maths: ";
        std::cin >> student.mmark;
        std::cout << "Enter Marks out of 100 in English: ";
        std::cin >> student.emark;
        std::cout << "Enter Marks out of 100 in Computer science: ";
        std::cin >> student.csmark;
        std::cout << "Enter the no. of days attended school: ";
        std::cin >> student.attend;

        student.agg = (student.pmark + student.cmark + student.mmark + student.emark + student.csmark) / 5.0f;

        fout.write(reinterpret_cast<char*>(&student), sizeof(Student));
        std::cout << "Student record successfully created!" << std::endl;

        std::string ask;
        std::cout << "Do you want to input more records? (Y/N): ";
        std::cin >> ask;
        if (ask != "Y" && ask != "y") {
            break;
        }
    }

    fout.close();
}

void delete_rec() {
    std::string rec;
    std::cout << "Enter the admission number of the student whose record is to be deleted: ";
    std::cin >> rec;

    bool found = false;
    Student student;

    std::ifstream fin("Student.dat", std::ios::binary);
    std::ofstream fout("Student2.dat", std::ios::binary);

    while (fin.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        if (student.admno != rec) {
            fout.write(reinterpret_cast<char*>(&student), sizeof(Student));
        } else {
            found = true;
        }
    }

    fin.close();
    fout.close();

    std::remove("Student.dat");
    std::rename("Student2.dat", "Student.dat");

    if (found) {
        std::cout << "Student record successfully deleted." << std::endl;
    } else {
        std::cout << "Student record not found!" << std::endl;
    }
}

void search() {
    std::string sd;
    std::cout << "Enter the admission no of student to get details : ";
    std::cin >> sd;

    std::ifstream fin("Student.dat", std::ios::binary);
    Student student;
    bool found = false;

    while (fin.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        if (student.admno == sd) {
            found = true;
            std::cout << "\nSTUDENT REPORT" << std::endl;
            std::cout << "Admission NO. : " << student.admno << std::endl;
            std::cout << "NAME : " << student.name << std::endl;
            std::cout << "Attendance : " << student.attend << std::endl;
            std::cout << "MARKS IN FOLLOWING SUBJECTS : " << std::endl;
            std::cout << "PHYSICS   : " << student.pmark << std::endl;
            std::cout << "CHEMISTRY : " << student.cmark << std::endl;
            std::cout << "MATHS     : " << student.mmark << std::endl;
            std::cout << "ENGLISH   : " << student.emark << std::endl;
            std::cout << "COMPUTER  : " << student.csmark << std::endl;
            std::cout << "Aggregate percentage : " << student.agg << "%" << std::endl;
            break;
        }
    }

    fin.close();
    if (!found) {
        std::cout << "No such record found!" << std::endl;
    }
}

void intro() {
    std::cout << std::string(70, '=') << std::endl;
    std::cout << "SCHOOL DATA MANAGEMENT SYSTEM" << std::endl;
    std::cout << "REPORT DATA OF STUDENTS OF CLASS 12 FOR 1ST TERM: SESSION 2023-24" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
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
    std::cout << "4. LIST OF STUDENTS WITH SHORT ATTENDANCE" << std::endl;
    std::cout << "5. BACK TO MAIN MENU" << std::endl;
}

void admin_menu() {
    std::cout << "\nADMIN MENU" << std::endl;
    std::cout << "1. CREATE STUDENT RECORD" << std::endl;
    std::cout << "2. SEARCH STUDENT RECORD" << std::endl;
    std::cout << "3. MODIFY STUDENT RECORD" << std::endl;
    std::cout << "4. DELETE STUDENT RECORD" << std::endl;
    std::cout << "5. BACK TO MAIN MENU" << std::endl;
}

int main() {
    intro();
    while (true) {
        main_menu();
        int choice;
        std::cout << "ENTER CHOICE 1-3 : ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << std::endl;

        if (choice == 1) {
            while (true) {
                report_menu();
                int rchoice;
                std::cout << "Enter choice 1-5 : ";
                std::cin >> rchoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << std::endl;

                switch (rchoice) {
                    case 1:
                        display();
                        break;
                    case 2:
                        merit();
                        break;
                    case 3:
                        fail();
                        break;
                    case 4:
                        sattend();
                        break;
                    case 5:
                        goto end_report_menu;
                    default:
                        std::cout << "INVALID INPUT!!!" << std::endl;
                }
                std::cout << std::endl;
            }
            end_report_menu:;
        }
        else if (choice == 2) {
            while (true) {
                admin_menu();
                int rchoice;
                std::cout << "Enter choice 1-5 : ";
                std::cin >> rchoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << std::endl;

                switch (rchoice) {
                    case 1:
                        create_rec();
                        break;
                    case 2:
                        search();
                        break;
                    case 3:
                        modify_rec();
                        break;
                    case 4:
                        delete_rec();
                        break;
                    case 5:
                        goto end_admin_menu;
                    default:
                        std::cout << "INVALID INPUT!!!" << std::endl;
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
        }
        std::cout << std::endl;
    }
}

