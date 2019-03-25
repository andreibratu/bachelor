#include "AdminController.h"
#include <iostream>


AdminController::AdminController(Repository& r) : repository{r} {}


Vector<Movie> AdminController::getAll() {
  return this->repository.getAll();
}


void AdminController::addMovie(std::string n, std::string g, std::string t, int y) {
  Movie m = Movie{n, g, t, y};
  this->repository.addMovie(Movie{n, g, t, y});
}


bool AdminController::deleteMovie(int idx) {
  return this->repository.deleteMovie(idx);
}


bool AdminController::updateName(int idx, std::string name) {
  return this->repository.updateName(idx, name);
}


bool AdminController::updateGenre(int idx, std::string genre) {
  return this->repository.updateGenre(idx, genre);
}


bool AdminController::updateTrailer(int idx, std::string trailer) {
  return this->repository.updateTrailer(idx, trailer);
}


bool AdminController::updateYear(int idx, int year) {
  return this->repository.updateYear(idx, year);
}
