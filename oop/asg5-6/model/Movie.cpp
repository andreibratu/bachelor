#include "Movie.h"
#include <algorithm>
#include <assert.h>

Movie::Movie() {}


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
  // Search by genre use case

  if(other.getYear() == -1) {
    if(other.getGenre().size() == 0) return true;

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


Movie& Movie::operator ++ (int) {
  ++(*this);
  return *this;
}


std::ostream& operator << (std::ostream& os,  const Movie& m) {

  os << m.getName() << " | " << m.getGenre() << " | " << m.getTrailer() << " | " << m.getYear() << " | " << m.getLikes();

  return os;
}
