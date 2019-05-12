#ifndef MOVIEMODEL_H
#define MOVIEMODEL_H

#include <QAbstractTableModel>
#include "movie.h"

class MovieModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit MovieModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    bool insertRows(int row, int count, const QModelIndex &parent) override;

    ~MovieModel();
private:
    std::vector<Movie> movies;
    QString filename;
    void loadFromCSV();

public slots:
    void addNewMovie(Movie);
};

#endif // MOVIEMODEL_H
