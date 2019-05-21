#include "movie.h"

Movie::Movie(QString n , QString g,  QString t, int y, int l) {
    name = n;
    genre = g;
    trailer = t;
    likes = l;
    year = y;
}

Movie::Movie(QVariant n, QVariant g, QVariant t, QVariant y, QVariant l) {
    name = n.toString();
    genre = g.toString();
    trailer = t.toString();
    likes = l.toInt();
    year = y.toInt();
}

Movie::Movie(const Movie& m) {
  name = m.name;
  genre = m.genre;
  trailer = m.trailer;
  year = m.year;
  likes = m.likes;
}

Movie& Movie::operator = (const Movie& m) {
  name = m.name;
  genre = m.genre;
  trailer = m.trailer;
  year = m.year;
  likes = m.likes;

  return *this;
}

Movie::Movie() {
    this->likes = 0;
    this->year = 0;
}
