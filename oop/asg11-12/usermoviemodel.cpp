#include <QFile>
#include <QTextStream>
#include <QTextStream>
#include <QDebug>
#include "usermoviemodel.h"
#include "movie.h"

UserMovieModel::UserMovieModel(QObject *parent)
    : MovieModel(parent, "/home/andreib/asg11-12/admin.csv", "")
{
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
            return QString::fromStdString(m.getName());
            break;
        case 1:
            return QString::fromStdString(m.getGenre());
            break;
        case 2:
            return QString::number(m.getLikes());
            break;
        case 3:
            return QString::number(m.getYear());
            break;
        case 4:
            return QString::fromStdString(m.getTrailer());
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
            movie.setName(value.toString().toStdString());
            break;
        case 1:
            movie.setGenre(value.toString().toStdString());
            break;
        case 2:
            movie.setLikes(value.toInt());
            break;
        case 3:
            movie.setYear(value.toInt());
            break;
        case 4:
            movie.setTrailer(value.toString().toStdString());
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
