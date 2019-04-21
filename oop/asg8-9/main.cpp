#include <db/DbMovieRepo.h>
#include "repo/abstract/AbstractRepository.h"
#include "repo/CSVMovieRepo.h"
#include "controller/AdminController.h"
#include "controller/UserController.h"
#include "ui/AdminUI.h"
#include "ui/UserUI.h"


int main() {
    DbMovieRepo dbr{"movies.csv"};
//    CSVMovieRepo r{"admin.csv"};
//
//    bool option = false;
//    std::cout << "Admin(0) / User(1)? ";
//    std::cin >> option;
//
//    std::cin.ignore();
//
//    if(!option) {
//        AdminController c{r};
//        AdminUI ui{c};
//        ui.input_loop();
//    }
//    else {
//        CSVMovieRepo watchlist{"user.csv"};
//        UserController c{r, watchlist};
//        UserUI ui{c};
//        ui.input_loop();
//    }

    return 0;
}
