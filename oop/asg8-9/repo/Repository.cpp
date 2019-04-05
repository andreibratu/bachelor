#include "Repository.h"


Repository::Repository() {}


std::vector<Movie> Repository::getAll() {
  return std::vector<Movie>(this->movies);
}


void Repository::addMovie(const Movie& m) {
  this->movies.push_back(m);
}


bool Repository::deleteMovie(int idx) {
  if(idx >= (int)this->movies.size()) return false;

  this->movies.erase(this->movies.begin()+idx);
  return true;
}


bool Repository::updateName(int idx, const std::string& name) {
  if(idx >= (int)this->movies.size()) return false;

  this->movies[idx].setName(name);
  return true;
}


bool Repository::updateGenre(int idx, const std::string& genre) {
  if(idx >= (int)this->movies.size()) return false;

  this->movies[idx].setGenre(genre);
  return true;
}


bool Repository::updateTrailer(int idx, const std::string& trailer) {
  if(idx >= (int)this->movies.size()) return false;

  this->movies[idx].setTrailer(trailer);
  return true;
}


bool Repository::updateYear(int idx, int year) {
  if(idx >= (int)this->movies.size()) return false;

  this->movies[idx].setYear(year);
  return true;
}


bool Repository::incrementLikes(int idx) {
  if(idx >= (int)this->movies.size()) return false;

  this->movies[idx].setLikes(this->movies[idx].getLikes() + 1);
  return true;
}


Movie Repository::operator [] (int idx) const {
  return this->movies[idx];
}
