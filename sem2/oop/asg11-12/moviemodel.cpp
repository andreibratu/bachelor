#include <QFile>
#include <QTextStream>
#include <QTextStream>
#include <QDebug>
#include <QItemSelectionRange>
#include "moviemodel.h"

// CTORS
MovieModel::MovieModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int MovieModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return this->movies.size();
}

int MovieModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // Movie entity has five properties
    return 5;
}

bool MovieModel::insertRows(int row, int count, const QModelIndex &parent) {
    if(row < 0 || row > this->rowCount()) return false;

    if(row == this->rowCount()) {
        this->beginInsertRows(parent, row, row+count-1);
        for(int i = 0; i < count; i++) {
            this->movies.push_back(Movie{});
        }
        this->endInsertRows();
    }
    else {
        this->beginInsertRows(parent, row, row+count-1);
        for(int i = 0; i < count; i++) {
            this->movies.insert(this->movies.begin()+row+count, Movie{});
        }
        this->endInsertRows();
    }

    return true;
}

QVariant MovieModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        switch(orientation) {
        case Qt::Orientation::Vertical:
            return QString::number(section);
        case Qt::Orientation::Horizontal:
            switch(section) {
            case 0:
                return QString("Name");
            case 1:
                return QString("Genre");
            case 2:
                return QString("Likes");
            case 3:
                return QString("Year");
            case 4:
                return QString("Trailer");
            }
        }
        break;
    default:
        break;
    }

    return QVariant();
}

bool MovieModel::removeRows(int row, int count, const QModelIndex &parent) {
    if(row < 0 || row >= this->rowCount()) return false;

    this->beginRemoveRows(parent, row, row+count-1);
    for(int i = 0; i < count; i++) {
        this->movies.erase(this->movies.begin()+row);
    }
    this->endRemoveRows();

    return true;
}

MovieModel::~MovieModel() = default;

// SIGNALS
void MovieModel::addMovie(Movie movie) {
    this->insertRow(this->rowCount());
    this->movies[this->rowCount()-1] = movie;
}

void MovieModel::deleteMovie(int row) {
    this->removeRow(row);
}
