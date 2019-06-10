//
// Created by andreib on 22.04.2019.
//

#ifndef ASG8_9_ADMINCSVCONTROLLER_H
#define ASG8_9_ADMINCSVCONTROLLER_H


#include <base/AdminController.h>

class AdminCSVController: public AdminController {
public:
    explicit AdminCSVController(MovieRepository& r);

    void show() override;
};


#endif //ASG8_9_ADMINCSVCONTROLLER_H
