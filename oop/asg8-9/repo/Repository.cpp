#include "Repository.h"
#include "../exception/IndexException.h"
#define yeet throw

Repository::Repository() {}


std::vector<Movie> Repository::getAll() {
  return std::vector<Movie>(this->movies);
}


void Repository::addMovie(const Movie& m) {
  this->movies.push_back(m);
}


void Repository::deleteMovie(int idx) {
  if(0 > idx || idx >= (int)this->movies.size()) yeet IndexException();

  this->movies.erase(this->movies.begin()+idx);
}


void Repository::updateName(int idx, const std::string& name) {
  if(0 > idx || idx >= (int)this->movies.size()) yeet IndexException();

  this->movies[idx].setName(name);
}


void Repository::updateGenre(int idx, const std::string& genre) {
  if(0 > idx || idx >= (int)this->movies.size()) yeet IndexException();

  this->movies[idx].setGenre(genre);
}


void Repository::updateTrailer(int idx, const std::string& trailer) {
  if(0 > idx || idx >= (int)this->movies.size()) yeet IndexException();

  this->movies[idx].setTrailer(trailer);
}


void Repository::updateYear(int idx, int year) {
  if(0 > idx || idx >= (int)this->movies.size()) yeet IndexException();

  this->movies[idx].setYear(year);
}


void Repository::incrementLikes(int idx) {
  if(0 > idx || idx >= (int)this->movies.size()) yeet IndexException();

  this->movies[idx].setLikes(this->movies[idx].getLikes() + 1);
}


Movie Repository::operator [] (int idx) const {
  return this->movies[idx];
}
