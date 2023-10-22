#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include "Data.h"
using namespace std;

Data::Data() {};


void Data::readClasses(){
    string f = "../schedule/classes.csv";
    ifstream file(f);
    if (!file.is_open() && !file.good()) {
        std::cerr << "Failed to open file: " << f << std::endl;
    }
    string line, ClassCode, UcCode, Weekday, Type, StartHour, Duration;
    list<pair<UC,Lesson>> aux;
    getline(file, line);

    map<string, int> WeekdayToNum = {
            {"Monday", 1},
            {"Tuesday", 2},
            {"Wednesday", 3},
            {"Thursday", 4},
            {"Friday", 5}
    };

    while (getline(file, line)) {
        istringstream iss(line);
        getline(iss, ClassCode, ',');
        getline(iss, UcCode, ',');
        getline(iss, Weekday, ',');
        getline(iss, StartHour, ',');
        getline(iss, Duration, ',');
        getline(iss, Type, ',');



        int w = WeekdayToNum[Weekday];
        float sh = stof(StartHour);
        float d = stof(Duration);


        pair<UC,Lesson> p (UC(UcCode,ClassCode), Lesson(w, d, sh, Type));
        aux.push_back(p);
    }
    listClasses_ = aux;
    file.close();
}
void Data::readClasses_Per_Uc(){
    string f = "../schedule/classes_per_uc.csv";
    ifstream file(f);
    if (!file.is_open() && !file.good()) {
        std::cerr << "Failed to open file: " << f << std::endl;
    }
    string UcCode,ClassCode,line;
    list<UC> aux;
    list<Lesson> Lesson={};
    getline(file, line);
    while (getline(file, line)) {
        istringstream iss(line);
        getline(iss, ClassCode, ',');
        getline(iss, UcCode, ',');
        aux.push_back(UC(UcCode, ClassCode, Lesson));
    }
    listClasses_Per_Uc_ = aux;
    file.close();
}

void Data::readStudents_Classes(){
    string f = "../schedule/students_classes.csv";
    ifstream file(f);
    if (!file.is_open() && !file.good()) {
        std::cerr << "Failed to open file: " << f << std::endl;
    }
    string StName,StCode, UcCode, ClassCode, line;

    list<pair<Student, UC>> aux;
    getline(file, line);
    while(getline(file, line)) {
        istringstream inn(line);
        getline(inn, StCode, ',');
        getline(inn, StName, ',');
        getline(inn, UcCode, ',');
        getline(inn, ClassCode, ',');

        int stc = stoi(StCode);

        pair<Student,UC> p (Student(stc,StName), UC(UcCode, ClassCode));
        aux.push_back(p);

    }
    listStudents_Classes_ = aux;
    file.close();
}

std::list<std::pair<UC, Lesson>> Data::getListClasses_() {
    return listClasses_;
}

std::list<UC> Data::getListClasses_Per_Uc_() {
    return listClasses_Per_Uc_;
}

std::list<std::pair<Student, UC>> Data::getListStudents_Classes_() {
    return listStudents_Classes_;
}
void Student::Student printClassTableSchedule() const{
    cout << classCode_ + " schedule\n";
    string schedule_ = " ________________________________________________________________________________________\n"
                       "|     Hour    |    Monday    |   Tuesday    |   Wednesday  |   Thursday   |    Friday    |\n"
                       "|________________________________________________________________________________________|\n";

    vector<string> periodOfTime(24 * 5 * 2, "              |");

    for (const UcClass& ucClass_ : listClasses_Per_UC_) {
        if (ucClass_.getClassCode() == classCode_) {
            for (const Lecture& lesson : ucClass_.getLessons()) {
                int weekDayPosition=lesson.getWeekday() -1;

                float duration = lesson.getDuration();
                int lessonStartPosition = 24 * 2 * weekDayPosition + (lecture.getStartHour() - 8.00) * 2;

                periodOfTime[lessonStartPosition] = " " + ucClass_.getUcCode() + "(" + lesson.getType() + ")";

                if (ucClass_.getUcCode().length() + lesson.getType().length() + 2 < 15)
                    periodOfTime[lessonStartPosition] += string(15 - ucClass_.getUcCode().length() - lesson.getType().length(), ' ');

                periodOfTime[lessonStartPosition] += "|";

                periodOfTime[++lessonStartPosition] = "   " + ucClass_.getClassCode() + "    |";

                duration -= 0.5;
                while (duration > 0.5) {
                    duration -= 0.5;
                    periodOfTime[++lectureStartPosition] = "              |";
                    periodOfTime[++lectureStartPosition] = "              |";
                }
                periodOfTime[++lessonStartPosition] = "              |";
            }
        }
    }

    float time = 8.0;
    for (int i = 0; i < 24 * 2; i += 2) {
        if (time < 10 || (time + 0.5 < 10)) cout << "|  ";
        else cout << "| ";

        cout << to_string(static_cast<int>(time)) << ':' << to_string(static_cast<int>((time - static_cast<int>(time)) * 6)) << "0-";

        time += 0.5;

        cout << to_string(static_cast<int>(time)) << ':' << to_string(static_cast(int)(time - static_cast<int>(time)) * 6) << "0";

        if (time < 10 && (time - 0.5 < 10)) cout << ' ';
        cout << " |" << periodOfTime[i] << periodOfTime[48 * 1 + i] << periodOfTime[48 * 2 + i] << periodOfTime[48 * 3 + i] << periodOfTime[48 * 4 + i] << '\n';
        cout << "|_____________|" << periodOfTime[i + 1] << periodOfTime[48 * 1 + i + 1] << periodOfTime[48 * 2 + i + 1] << periodOfTime[48 * 3 + i + 1] << periodOfTime[48 * 4 + i + 1] << '\n';
    }
}
