#include "UserController.h"


UserController::UserController(Repository& repo): r{repo} {
  this->current = -1;
}


Vector<Movie> UserController::queryByGenre(const std::string& genre) {
  std::cout << genre << '\n';
  Movie key{"", genre, "", -1};
  Vector<Movie> ans{};

  Vector<Movie> all = this->r.getAll();

  std::cout << all.size() << '\n';

  for(int i = 0; i < all.size(); i++) {
    if(all[i] == key) {
      ans.push_back(all[i]);
    }
  }

  std::cout << this->query.size() << '\n';
  this->query = ans;
  this->current = 0;

  return ans;
}


void UserController::nextMovie() {
  if(this->current == -1) throw std::exception();
  int allCount = this->query.size();
  this->current = (this->current == allCount-1) ? (0):(this->current+1);
}


void UserController::addToWatchList() {
  this->watchlist.push_back(this->query[this->current]);
  this->nextMovie();
}


Movie UserController::seeDetails() {
  return this->query[this->current];
}


void UserController::removeWatchlist(int idx, int was_liked) {
  if(idx < 0 || idx >= this->watchlist.size() || was_liked < 0 || was_liked > 1) {
    throw std::exception();
  }

  Movie m = this->watchlist[idx];
  for(int i = 0; i < this->r.movies.size() && was_liked; i++) {
    if(this->r.movies[i] == m) {
      int likes = this->r.movies[i].getLikes() + 1;
      this->r.movies[i].setLikes(likes);
      break;
    }
  }

  this->watchlist.remove(idx);
}


Vector<Movie> UserController::getWatchlist() {
  return this->watchlist;
}
