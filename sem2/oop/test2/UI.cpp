//
// Created by andreib on 06.05.2019.
//

#include <iostream>
#include "UI.h"
#include "BMI.h"
#include "BP.h"

UI::UI(Controller &c): controller{c} {}

void UI::addNew() {
    int flag;
    std::string date;
    MedicalAnalysis* analysis;

    std::cout << "BMI (0) / BP (1) ? ";

    std::cin>>flag;
    std::cin.ignore();

    if(flag == 0) {
        double val;

        std::cout << "Date: ";
        std::cin >> date;
        std::cout << '\n';

        std::cout << "Value: ";
        std::cin >> val;
        std::cout << '\n';

        analysis = new BMI(date, val);
        this->controller.add(analysis);
    } else {
        int sys;
        int dis;

        std::cout << "Date: ";
        std::cin >> date;
        std::cout << '\n';
        std::cin.ignore();

        std::cout << "Systolic: ";
        std::cin >> sys;
        std::cout << '\n';
        std::cin.ignore();

        std::cout << "Diastolic: ";
        std::cin >> dis;
        std::cout << '\n';
        std::cin.ignore();

        analysis = new BP(date, sys, dis);
        this->controller.add(analysis);
    }
}

void UI::showAll() {
    std::vector<MedicalAnalysis*> as = this->controller.getAll();

    for(auto x: as) {
        std::string s = x->toString();
        std::cout << s << '\n';
    }
}

void UI::isIll() {
    int month;
    std::cin >> month;
    bool result = this->controller.isIll(month);

    if(result) {
        std::cout << "You're ill\n";
    } else {
        std::cout << "You're alright fam\n";
    }
}

void UI::saveFile() {
    std::string f;
    std::string date1;
    std::string date2;
    this->controller.writeUsDownScotty(f, date1, date2);
}


void UI::loop() {
    int option;
    bool flag = true;
    while(flag) {
        std::cout << "1. Add\n2. Show all\n3. Is ill\n4. Save\n5. Exit\n";
        std::cin >> option;
        switch (option) {
            case 1:
                this->addNew();
                break;
            case 2:
                this->showAll();
                break;
            case 3:
                this->isIll();
                break;
            case 4:
                this->saveFile();
                break;
            case 5:
                flag = false;
                break;
            default:;
        }
    }
}




