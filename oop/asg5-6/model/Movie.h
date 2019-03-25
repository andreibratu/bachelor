#ifndef MOVIE_H
#define MOVIE_H
#include <string>

class Movie {
private:
  std::string name;
  std::string genre;
  std::string trailer;
  int year;
  int likes;
public:
  Movie();

  Movie(const Movie& m);

  Movie(std::string n, std::string g, std::string t, int y);

  void setName(std::string name);

  std::string getName() const;

  void setGenre(std::string genre);

  std::string getGenre() const;

  void setTrailer(std::string trailer);

  std::string getTrailer() const;

  void setYear(int year);

  int getYear() const;

  void setLikes(int likes);

  int getLikes();

  bool operator == (const Movie other) const;

  Movie& operator ++ ();

  Movie& operator ++ (int);
};

#endif
