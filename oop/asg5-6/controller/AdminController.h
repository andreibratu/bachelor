#ifndef ADMIN_CONTROLLER_H
#define ADMIN_CONTROLLER_H

#include "../repo/Repository.h"


class AdminController {
private:
  Repository& repository;
public:
  AdminController(Repository& r);

  Vector<Movie> getAll();

  void addMovie(std::string n, std::string g, std::string t, int y);

  bool deleteMovie(int idx);

  bool updateName(int idx, std::string name);

  bool updateGenre(int idx, std::string genre);

  bool updateTrailer(int idx, std::string trailer);

  bool updateYear(int idx, int year);
};

#endif
