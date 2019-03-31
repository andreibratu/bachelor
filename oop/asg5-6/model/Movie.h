#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include <iostream>

class Movie {
private:
  std::string name;
  std::string genre;
  std::string trailer;
  int year;
  int likes;
public:
  Movie();

  Movie(const std::string& n, const std::string& g, const std::string& t, int y);

  Movie(const Movie& m);

  void setName(std::string name);

  std::string getName() const;

  void setGenre(std::string genre);

  std::string getGenre() const;

  void setTrailer(std::string trailer);

  std::string getTrailer() const;

  void setYear(int year);

  int getYear() const;

  void setLikes(int likes);

  int getLikes() const;

  bool operator == (const Movie other) const;

  Movie& operator ++ ();

  Movie& operator ++ (int);

  friend std::ostream& operator << (std::ostream& os, const Movie& m);
};

#endif
