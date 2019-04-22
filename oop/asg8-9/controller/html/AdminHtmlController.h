//
// Created by andreib on 22.04.2019.
//

#ifndef ASG8_9_ADMINHTMLCONTROLLER_H
#define ASG8_9_ADMINHTMLCONTROLLER_H
#include "base/AdminController.h"



class AdminHtmlController: public AdminController {
public:
    void show() override;

    explicit AdminHtmlController(MovieRepository& r);
};


#endif //ASG8_9_ADMINHTMLCONTROLLER_H
