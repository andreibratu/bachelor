#include <algorithm>
#include <fstream>
#include <sstream>
#include "UserController.h"
#include "../exception/IndexException.h"
#include "../exception/LikeException.h"
#define yeet throw


UserController::UserController(Repository& repo): r{repo} {
  this->current = -1;
  std::fstream fin_movies("./admin.csv", std::ios::in);
  std::string line;
  Movie m;

  while (std::getline(fin_movies, line)) {
    std::stringstream s(line);
    s >> m;
    this->r.addMovie(m);
  }

  fin_movies.close();


  std::fstream fin_watchlist("./user.csv", std::ios::in);
  while (std::getline(fin_watchlist, line)) {
    std::stringstream s(line);
    s >> m;
    this->watchlist.push_back(m);
  }
}


void UserController::queryByGenre(const std::string& genre) {
  Movie key{"", genre, "", -1};

  std::vector<Movie> all = this->r.getAll();
  std::vector<Movie> ans(all.size());

  auto copy_it = std::copy_if(
    all.begin(),
    all.end(),
    ans.begin(),
    [&](const Movie& m){ return
      m == key &&
      (std::find_if(
        this->watchlist.begin(),
        this->watchlist.end(),
        [&](const Movie& mw) {return m.getName() == mw.getName();}
      ) == this->watchlist.end());
    }
  );

  ans.resize(std::distance(ans.begin(), copy_it));

  this->query = ans;
  this->current = 0;
}


void UserController::nextMovie() {
  int allCount = this->query.size();
  this->current = (this->current == allCount-1) ? (0):(this->current+1);
}


void UserController::addToWatchList() {
  if(!this->query.size()) return;

  this->watchlist.push_back(Movie(this->query[this->current]));
  this->query.erase(this->query.begin() + this->current);
}


Movie UserController::seeDetails() {
  return this->query[this->current];
}


void UserController::removeWatchlist(int idx, int was_liked) {
  if(idx < 0 || idx >= (int)this->watchlist.size()) yeet IndexException();
  if(was_liked < 0 || was_liked > 1) yeet LikeException();

  if(was_liked) {
    Movie m = this->watchlist[idx];
    auto search_it = std::find_if(
      this->r.movies.begin(),
      this->r.movies.end(),
      [&](const Movie& m_repo) {return m_repo == m;}
    );
    search_it->setLikes(search_it->getLikes() + 1);
  }

  this->watchlist.erase(this->watchlist.begin() + idx);
}


std::vector<Movie> UserController::getQuery() {
  return this->query;
}


std::vector<Movie> UserController::getWatchlist() {
  return this->watchlist;
}


UserController::~UserController() {
  std::fstream fout("./user.csv", std::ios::out | std::ios::trunc);
  for(auto& x: this->watchlist) {
    fout << x << '\n';
  }

  fout.close();
}
