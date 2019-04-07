#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "AdminController.h"


AdminController::AdminController(Repository& r) : repository{r} {
  std::fstream fin("./admin.csv", std::ios::in);
  std::string line;
  Movie m;

  while (std::getline(fin, line)) {
    std::stringstream s(line);
    s >> m;
    this->repository.addMovie(m);
  }

  fin.close();
}


std::vector<Movie> AdminController::getAll() {
  return this->repository.getAll();
}


void AdminController::addMovie(const std::string& n, const std::string& g, const std::string& t, int y) {
  Movie m{n, g, t, y};
  this->repository.addMovie(m);
}


bool AdminController::deleteMovie(int idx) {
  return this->repository.deleteMovie(idx);
}


bool AdminController::updateName(int idx, const std::string& name) {
  return this->repository.updateName(idx, name);
}


bool AdminController::updateGenre(int idx, const std::string& genre) {
  return this->repository.updateGenre(idx, genre);
}


bool AdminController::updateTrailer(int idx, const std::string& trailer) {
  return this->repository.updateTrailer(idx, trailer);
}


bool AdminController::updateYear(int idx, int year) {
  return this->repository.updateYear(idx, year);
}


AdminController::~AdminController() {
  std::fstream fout("./admin.csv", std::ios::out | std::ios::trunc);
  for(auto& x: this->repository.getAll()) {
    fout << x << '\n';
  }

  fout.close();
}
