#include <algorithm>
#include <fstream>
#include <sstream>

#include "UserController.h"
#include "IndexException.h"
#include "LikeException.h"


UserController::UserController(
  MovieRepository& r,
  MovieRepository& w): watchlist{w}, repository{r}, current{0} {
}


void UserController::queryByGenre(const std::string& genre) {
  Movie key{"", genre, "", -1};

  std::vector<Movie> all = this->repository.getAll();
  std::vector<Movie> wl = this->watchlist.getAll();
  std::vector<Movie> ans(all.size());

  auto copy_it = std::copy_if(
    all.begin(),
    all.end(),
    ans.begin(),
    [&](const Movie& m){ return
      m == key &&
      (std::find_if(
        wl.begin(),
        wl.end(),
        [&](const Movie& mw) {return m.getName() == mw.getName();}
      ) == wl.end());
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
  if(this->query.empty()) return;

  this->watchlist.add(Movie(this->query[this->current]));
  this->query.erase(this->query.begin() + this->current);
}


Movie UserController::seeDetails() {
  return this->query[this->current];
}


void UserController::removeWatchlist(int idx, int was_liked) {
  std::vector<Movie> all = this->repository.getAll();
  std::vector<Movie> wl = this->watchlist.getAll();

  if(idx < 0 || idx >= (int)wl.size()) throw IndexException();
  if(was_liked < 0 || was_liked > 1) throw LikeException();


  if(was_liked) {
    Movie m = this->watchlist[idx];
    auto search_it = std::find_if(
      all.begin(),
      all.end(),
      [&](const Movie& m_repo) {return m_repo == m;}
    );

    int repo_idx = std::distance(all.begin(), search_it);
    this->repository.incrementLikes(repo_idx);
    for(auto x: this->repository.getAll()) {
        std::cout << x << '\n';
    }
  }

  this->watchlist.remove(idx);
}


std::vector<Movie> UserController::getQuery() {
  return this->query;
}


std::vector<Movie> UserController::getWatchlist() {
  return this->watchlist.getAll();
}
