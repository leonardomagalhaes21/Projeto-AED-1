#ifndef PROJECT_MENU_H
#define PROJECT_MENU_H
#include <iostream>
#include <string>
#include <iomanip>
#include "Student.h"
#include "UC.h"
#include "Schedule.h"

class Menu {
public:
    Menu();
    void showMenu();
    static void drawTop(int largura);
    static void drawBottom(int largura);
};


#endif //PROJECT_MENU_H