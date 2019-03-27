#include "Movie.h"


Movie::Movie() {}


Movie::Movie(const Movie& m) {
  this->name = std::string(name);
  this->genre = std::string(genre);
  this->trailer = std::string(trailer);
  this->year = year;
  this->likes = likes;
}


Movie::Movie(std::string n, std::string g, std::string t, int y) {
  this->name = n;
  this->genre = g;
  this->trailer = t;
  this->year = y;
  this->likes = 0;
}


void Movie::setName(std::string n) {
  this->name = n;
}


std::string Movie::getName() const {
  return this->name;
}


void Movie::setGenre(std::string genre) {
  this->genre = genre;
}


std::string Movie::getGenre() const {
  return this->genre;
}


void Movie::setTrailer(std::string trailer) {
  this->trailer = trailer;
}


std::string Movie::getTrailer() const {
  return this->trailer;
}


void Movie::setYear(int year) {
  this->year = year;
}


int Movie::getYear() const {
  return this->year;
}


void Movie::setLikes(int likes) {
  this->likes = likes;
}


int Movie::getLikes() const {
  return this->likes;
}


bool Movie::operator == (const Movie other) const {
  if(this->getGenre().size() == 0 || other.getGenre().size() == 0) return true;

  return this->getGenre() == other.getGenre();
}


Movie& Movie::operator ++ () {
  this->likes++;
  return *this;
}


Movie& Movie::operator ++ (int) {
  ++(*this);
  return *this;
}


std::ostream& operator << (std::ostream& os,  const Movie& m) {
  os << m.getName() << '-' << m.getGenre() << '-' << m.getTrailer() << '-' << m.getYear() << '-' << m.getLikes();

  return os;
}
