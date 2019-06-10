#ifndef HELPERS_H
#define HELPERS_H

#include <QVector>
#include <QFile>
#include <QTextStream>
#include "movie.h"

void writeCSV(const QVector<Movie>& movies, QString filename);

void readCSV(QVector<Movie>& movies, QString filename);

#endif // HELPERS_H
