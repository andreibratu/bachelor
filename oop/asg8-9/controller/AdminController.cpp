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


void AdminController::deleteMovie(int idx) {
  this->repository.deleteMovie(idx);
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


AdminController::~AdminController() {
  std::fstream fout("./admin.csv", std::ios::out | std::ios::trunc);
  for(auto& x: this->repository.getAll()) {
    fout << x << '\n';
  }

  fout.close();
}
