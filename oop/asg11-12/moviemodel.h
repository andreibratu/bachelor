#ifndef MOVIEMODEL_H
#define MOVIEMODEL_H

#include <QAbstractTableModel>
#include "movie.h"

class MovieModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit MovieModel(QObject *parent = nullptr);

    MovieModel(QObject *parent = nullptr, QString read_from_filename = "", QString write_to_filename = "");

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const = 0;

    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) = 0;

    virtual Qt::ItemFlags flags(const QModelIndex& index) const = 0;

    virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    virtual ~MovieModel();

private:
    QString read_from_filename;

    QString write_to_filename;

    void readCSV();

    void writeCSV();

protected:
    std::vector<Movie> movies;

public slots:
    void addMovie(Movie);

    void deleteMovie(int);

    void updateData(QModelIndex, QModelIndex, QVector<int>);
};

#endif // MOVIEMODEL_H
