#ifndef ADMIN_CONTROLLER_H
#define ADMIN_CONTROLLER_H

#include "../repo/Repository.h"


class AdminController {
private:
  Repository& repository;
public:
  AdminController(Repository& r);

  Vector<Movie> getAll();

  void addMovie(const std::string& n, const std::string& g, const std::string& t, int y);

  bool deleteMovie(int idx);

  bool updateName(int idx, const std::string& name);

  bool updateGenre(int idx, const std::string& genre);

  bool updateTrailer(int idx, const std::string& trailer);

  bool updateYear(int idx, int year);
};

#endif
