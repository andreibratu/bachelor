#include "movie.h"

#include <utility>
#include <algorithm>
#include <cassert>


Movie::Movie(const std::string& n, const std::string& g, const std::string& t, int y) {
  name = std::string(n);
  genre = std::string(g);
  trailer = std::string(t);
  year = y;
  likes = 0;
}


Movie::Movie(const Movie& m) {
  name = std::string(m.getName());
  genre = std::string(m.getGenre());
  trailer = std::string(m.getTrailer());
  year = m.getYear();
  likes = m.getLikes();
}


Movie& Movie::operator = (const Movie& m) {
  name = std::string(m.getName());
  genre = std::string(m.getGenre());
  trailer = std::string(m.getTrailer());
  year = m.getYear();
  likes = m.getLikes();

  return *this;
}


void Movie::setName(std::string n) {
  this->name = std::move(n);
}


std::string Movie::getName() const {
  return this->name;
}


void Movie::setGenre(std::string g) {
  this->genre = std::move(g);
}


std::string Movie::getGenre() const {
  return this->genre;
}


void Movie::setTrailer(std::string t) {
  this->trailer = std::move(t);
}


std::string Movie::getTrailer() const {
  return this->trailer;
}


void Movie::setYear(int y) {
  this->year = y;
}


int Movie::getYear() const {
  return this->year;
}


void Movie::setLikes(int l) {
  this->likes = l;
}


int Movie::getLikes() const {
  return this->likes;
}


bool Movie::operator == (const Movie& other) const {
  // Search by genre use case

  if(other.getYear() == -1) {
    if(other.getGenre().empty()) return true;

    std::string copy1 = std::string(this->getGenre());
    std::string copy2 = std::string(other.getGenre());

    std::transform(copy1.begin(), copy1.end(), copy1.begin(), ::tolower);
    std::transform(copy2.begin(), copy2.end(), copy2.begin(), ::tolower);

    return copy1 == copy2;
  }

  // General case equality between objects
  else {
    return this->getName() == other.getName() &&
    this->getYear() == other.getYear() &&
    this->getGenre() == other.getGenre();
  }
}


Movie& Movie::operator ++ () {
  this->likes++;
  return *this;
}


const Movie Movie::operator ++ (int) {
  ++(*this);
  return *this;
}


std::ostream& operator << (std::ostream& os, const Movie& m) {

  os << m.getName() << ',' << m.getGenre() << ',' << m.getTrailer() << ',' << m.getYear() << ',' << m.getLikes();

  return os;
}


std::istream& operator >> (std::istream& is, Movie& m) {
  std::string x;

  getline(is, x, ',');
  m.setName(x);

  getline(is, x, ',');
  m.setGenre(x);

  getline(is, x, ',');
  m.setTrailer(x);

  getline(is, x, ',');
  m.setYear(std::stoi(x));

  getline(is, x, ',');
  m.setLikes(std::stoi(x));

  return is;
}


Movie::Movie() {
    this->likes = 0;
    this->year = 0;
}
