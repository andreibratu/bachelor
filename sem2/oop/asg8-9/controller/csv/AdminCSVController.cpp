#include <utility>

//
// Created by andreib on 22.04.2019.
//

#include <sstream>
#include "AdminCSVController.h"


void AdminCSVController::show() {
    std::stringstream ss;
    ss << "chrome " << "../admin.csv";
    system(ss.str().c_str());
    system("clear");
}

AdminCSVController::AdminCSVController(MovieRepository &r): AdminController(r) {

}
