#include <utility>

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "AdminController.h"


std::vector<Movie> AdminController::getAll() {
  return this->repository.getAll();
}


void AdminController::addMovie(const std::string& n, const std::string& g, const std::string& t, int y) {
  Movie m{n, g, t, y};
  this->repository.add(m);
}


void AdminController::deleteMovie(int idx) {
  this->repository.remove(idx);
}


void AdminController::updateName(int idx, const std::string& name) {
  this->repository.updateName(idx, name);
}


void AdminController::updateGenre(int idx, const std::string& genre) {
  this->repository.updateGenre(idx, genre);
}


void AdminController::updateTrailer(int idx, const std::string& trailer) {
  this->repository.updateTrailer(idx, trailer);
}


void AdminController::updateYear(int idx, int year) {
  this->repository.updateYear(idx, year);
}

AdminController::AdminController(MovieRepository &r): repository{r} {

}