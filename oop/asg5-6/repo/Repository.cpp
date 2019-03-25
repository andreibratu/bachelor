#include "Repository.h"


Repository::Repository(Vector<Movie>& m) : movies{m} {}


Vector<Movie> Repository::getAll() const {
  return Vector<Movie>(this->movies);
}


void Repository::addMovie(Movie m) {
  this->movies.push_back(m);
}


bool Repository::deleteMovie(int idx) {
  try {
    this->movies.remove(idx);
    return true;
  }
  catch(std::exception()) {
    return false;
  }
}


bool Repository::updateName(int idx, std::string name) {
  try {
    this->movies[idx].setName(name);
    return true;
  }
  catch(std::exception e) {
    return false;
  }
}


bool Repository::updateGenre(int idx, std::string genre) {
  try {
    this->movies[idx].setGenre(genre);
    return true;
  }
  catch(std::exception e) {
    return false;
  }
}


bool Repository::updateTrailer(int idx, std::string trailer) {
  try {
    this->movies[idx].setTrailer(trailer);
    return true;
  }
  catch(std::exception()) {
    return false;
  }
}


bool Repository::updateYear(int idx, int year) {
  try {
    this->movies[idx].setYear(year);
    return true;
  }
  catch(std::exception()) {
    return false;
  }
}


bool Repository::incrementLikes(int idx) {
  try {
    this->movies[idx]++;
    return true;
  }
  catch(std::exception()) {
    return false;
  }
}


Movie& Repository::operator [] (int idx) const {
  return this->movies[idx];
}
