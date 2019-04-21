#include "MovieRepository.h"
#include "../../exception/IndexException.h"


void MovieRepository::updateName(int idx, const std::string& name) {
  if(0 > idx || idx >= (int)this->objects.size()) throw IndexException();

  this->objects[idx].setName(name);
}


void MovieRepository::updateGenre(int idx, const std::string& genre) {
  if(0 > idx || idx >= (int)this->objects.size()) throw IndexException();

  this->objects[idx].setGenre(genre);
}


void MovieRepository::updateTrailer(int idx, const std::string& trailer) {
  if(0 > idx || idx >= (int)this->objects.size()) throw IndexException();

  this->objects[idx].setTrailer(trailer);
}


void MovieRepository::updateYear(int idx, int year) {
  if(0 > idx || idx >= (int)this->objects.size()) throw IndexException();

  this->objects[idx].setYear(year);
}


void MovieRepository::incrementLikes(int idx) {
  if(0 > idx || idx >= (int)this->objects.size()) throw IndexException();

  this->objects[idx].setLikes(this->objects[idx].getLikes() + 1);
}
