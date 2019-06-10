//
// Created by andreib on 06.05.2019.
//

#ifndef TEST2_UI_H
#define TEST2_UI_H


#include "Controller.h"

class UI {
private:
    Controller& controller;
public:
    explicit UI(Controller& c);

    void addNew();

    void showAll();

    void isIll();

    void saveFile();

    void loop();
};


#endif //TEST2_UI_H
