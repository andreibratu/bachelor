#include <utility>

//
// Created by andreib on 22.04.2019.
//

#include <sstream>
#include <fstream>
#include "AdminHtmlController.h"

void AdminHtmlController::show() {
    std::stringstream ss;
    ss << "<html>" << "<head> Movie </head>" << "<body> <table border=1>";
    for(const auto& x: this->getAll()) {
        ss << "<tr>";
        ss << "<td>" << x.getName() << "</td>";
        ss << "<td>" << x.getGenre() << "</td>";
        ss << "<td><a>" << x.getTrailer() << "</a></td>";
        ss << "<td>" << x.getYear() << "</td>";
        ss << "<td>" << x.getLikes() << "</td>";
        ss << "</tr>";
    }
    ss << "</table> </body> </html>";

    std::fstream out("../movie.html", std::ios::out | std::ios::trunc);
    out << ss.str();
    out.close();
    system("chrome ../movie.html");
}


AdminHtmlController::AdminHtmlController(MovieRepository &r) : AdminController(r) {

}
