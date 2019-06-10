#include <QFile>
#include <QTextStream>
#include "adminmoviemodel.h"
#include "movie.h"
#include "helpers.h"
#include <QTextStream>
#include <QDebug>

AdminMovieModel::AdminMovieModel(QObject *parent): MovieModel(parent)
{
    readCSV(this->movies, "/home/andreib/asg11-12/admin.csv");
}

QVariant AdminMovieModel::data(const QModelIndex &index, int role) const
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

bool AdminMovieModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    QVariant oldValue;
    if (data(index, role) != value) {
        int row = index.row();
        Movie& movie = this->movies[row];
        switch(index.column()) {
        case 0:
            oldValue = QVariant::fromValue(movie.name);
            movie.name = value.toString();
            break;
        case 1:
            oldValue = QVariant::fromValue(movie.genre);
            movie.genre = value.toString();
            break;
        case 2:
            oldValue = QVariant::fromValue(movie.likes);
            movie.likes = value.toInt();
            break;
        case 3:
            oldValue = QVariant::fromValue(movie.year);
            movie.year = value.toInt();
            break;
        case 4:
            oldValue = QVariant::fromValue(movie.trailer);
            movie.trailer = value.toString();
            break;
        }
        emit undoEdit(index, this, oldValue, value);
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags AdminMovieModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    switch(index.column()) {
    case 2:
        return QAbstractTableModel::flags(index);
        break;
    default:
        return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
    }
}

AdminMovieModel::~AdminMovieModel() {
    writeCSV(this->movies, "/home/andreib/asg11-12/admin.csv");
}
