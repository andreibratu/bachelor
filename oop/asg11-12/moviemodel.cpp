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

MovieModel::MovieModel(QObject *parent, QString read_from_filename, QString write_to_filename)
    : QAbstractTableModel(parent)
{
    this->read_from_filename = read_from_filename;
    this->write_to_filename = write_to_filename;
    this->readCSV();
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
        this->beginInsertRows(parent, row, count);
        for(int i = 0; i < count; i++) {
            this->movies.push_back(Movie{});
        }
    }
    else {
        this->beginInsertRows(parent, row, count);
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

void MovieModel::readCSV() {
    if(this->read_from_filename != "") {
        QFile file(this->read_from_filename);

        if (file.open(QIODevice::ReadOnly)) {
            QTextStream in(&file);
            while(!in.atEnd()) {
                // read one line from textstream(separated by "\n")
                QString fileLine = in.readLine();
                // parse the read line into separate pieces(tokens) with "," as the delimiter
                QStringList lineToken = fileLine.split(",", QString::SkipEmptyParts);
                this->movies.push_back(Movie{
                    lineToken[0],
                    lineToken[1],
                    lineToken[3].toInt(),
                    lineToken[4].toInt(),
                    lineToken[2],
                });
            }
        }
        file.close();
    }
}

void MovieModel::writeCSV() {
    if(this->write_to_filename != "") {
        QFile file(this->write_to_filename);

        if (file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);

            for (auto m: this->movies) {
                out << QString::fromStdString(m.getName()) << ','
                    << QString::fromStdString(m.getGenre()) << ','
                    << QString::fromStdString(m.getTrailer()) << ','
                    << m.getYear() << ','
                    << m.getLikes() << ','
                    << endl;
            }
        }

        file.close();
    }
}

// DTOR
MovieModel::~MovieModel() {
    this->writeCSV();
}

// SIGNALS
void MovieModel::addMovie(Movie movie) {
    this->insertRow(this->rowCount());
    this->movies[this->rowCount()-1] = movie;
}

void MovieModel::deleteMovie(int row) {
    this->removeRow(row);
}

void MovieModel::updateData(QModelIndex topLeft, QModelIndex bottomRight, QVector<int> roles) {
    for(auto index : QItemSelectionRange(topLeft, bottomRight).indexes()) {
        this->setData(index, index.data(), roles[0]);
    }
}
