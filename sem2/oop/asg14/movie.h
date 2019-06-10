#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <iostream>
#include <QString>
#include <QVariant>

class Movie {
public:
    QString name;
    QString genre;
    QString trailer;
    int year;
    int likes;

    Movie();

    Movie(QString n , QString g, QString t, int y, int l);

    Movie(QVariant n , QVariant g, QVariant t, QVariant l, QVariant y);

    Movie(const Movie& m);

    Movie& operator = (const Movie&);

    bool operator == (const Movie& other) const;

    friend std::ostream& operator << (std::ostream& os, const Movie& m);

    friend std::istream& operator >> (std::istream& is, Movie& m);
};

#endif // MOVIE_H
