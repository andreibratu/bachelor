#include <db/DbRepository.h>
#include <DbMovieRepo.h>
#include <csv/AdminCSVController.h>
#include "controller/html/AdminHtmlController.h"
#include "repo/abstract/AbstractRepository.h"
#include "repo/CSVMovieRepo.h"
#include "base/AdminController.h"
#include "base/UserController.h"
#include "ui/AdminUI.h"
#include "ui/UserUI.h"


int main() {
    AdminController* c;
    MovieRepository* admin_repo;
    bool option = false;
    bool persistanceOption = false;
    bool controllerOption = false;

    std::cout << "CSV(0) / Html(1)? ";
    std::cin >> controllerOption;

    std::cout << "CSV(0) / Database(1)? ";
    std::cin >> persistanceOption;

    if(!persistanceOption) {
        admin_repo = new CSVMovieRepo{"admin.csv"};
    } else {
        admin_repo = new DbMovieRepo{"admin.db"};
    }

    std::cout << "Admin(0) / User(1)? ";
    std::cin >> option;

    std::cin.ignore();

    if(!controllerOption) {
        c = new AdminCSVController{*admin_repo};
    } else {
        c = new AdminHtmlController{*admin_repo};
    }

    if(!option) {
        AdminUI ui{*c};
        ui.input_loop();
    }
    else {
        MovieRepository* watchlist;
        if(!persistanceOption) {
             watchlist = new CSVMovieRepo{"user.csv"};
        } else {
            watchlist = new DbMovieRepo{"movies.db"};
        }

        UserController user{*admin_repo, *watchlist};
        UserUI ui{user};
        ui.input_loop();

//        delete watchlist;
    }

//    delete admin_repo;
    return 0;
}
