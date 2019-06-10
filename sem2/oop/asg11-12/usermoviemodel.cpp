#include <QFile>
#include <QTextStream>
#include <QTextStream>
#include <QDebug>
#include "usermoviemodel.h"
#include "movie.h"
#include "helpers.h"

UserMovieModel::UserMovieModel(QObject *parent) : MovieModel(parent)
{
    readCSV(this->movies, "/home/andreib/asg11-12/admin.csv");
}

QVariant UserMovieModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    int column = index.column();
    const Movie& m = this->movies[row];

    switch(role) {
    case Qt::DisplayRole:
        switch (column) {
        case 0:
            return m.name;
            break;
        case 1:
            return m.genre;
            break;
        case 2:
            return m.likes;
            break;
        case 3:
            return m.year;
            break;
        case 4:
            return m.trailer;
            break;
        }
        break;
    case Qt::TextAlignmentRole:
        return Qt::AlignCenter + Qt::AlignHCenter;
        break;
    default:
        break;
    }

    return QVariant();
}

bool UserMovieModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (data(index, role) != value) {
        int row = index.row();
        Movie& movie = this->movies[row];
        switch(index.column()) {
        case 0:
            movie.name = value.toString();
            break;
        case 1:
            movie.genre = value.toString();
            break;
        case 2:
            movie.likes = value.toInt();
            break;
        case 3:
            movie.year = value.toInt();
            break;
        case 4:
            movie.trailer = value.toString();
            break;
        }
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags UserMovieModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractTableModel::flags(index);
}

UserMovieModel::~UserMovieModel() = default;
