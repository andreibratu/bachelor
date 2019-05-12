#include <QFile>
#include <QTextStream>
#include "moviemodel.h"
#include "movie.h"
#include <QTextStream>
#include <QDebug>

MovieModel::MovieModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    this->loadFromCSV();
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

bool MovieModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    return false;
//    if (value != headerData(section, orientation, role)) {
//        // FIXME: Implement me!
//        emit headerDataChanged(orientation, section, section);
//        return true;
//    }
//    return false;
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

QVariant MovieModel::data(const QModelIndex &index, int role) const
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

bool MovieModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
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

Qt::ItemFlags MovieModel::flags(const QModelIndex &index) const
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


void MovieModel::loadFromCSV() {
    QFile file("/home/andreib/asg11-12/admin.csv");

    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);

        while(!in.atEnd()) {
            // read one line from textstream(separated by "\n")
            QString fileLine = in.readLine();

            // parse the read line into separate pieces(tokens) with "," as the delimiter
            QStringList lineToken = fileLine.split(",", QString::SkipEmptyParts);

            Movie m;
            m.setName(lineToken[0].toStdString());
            m.setGenre(lineToken[1].toStdString());
            m.setTrailer(lineToken[2].toStdString());
            m.setYear(lineToken[3].toInt());
            m.setLikes(lineToken[4].toInt());
            this->movies.push_back(m);
        }
    }

    file.close();
}

void MovieModel::addNewMovie(Movie movie) {
    this->insertRow(this->rowCount());
    this->movies[this->rowCount()-1] = movie;
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

MovieModel::~MovieModel() {
    QFile file("/home/andreib/asg11-12/admin.csv");

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
