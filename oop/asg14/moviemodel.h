#ifndef MOVIEMODEL_H
#define MOVIEMODEL_H

#include <QAbstractTableModel>
#include "movie.h"

class MovieModel : public QAbstractTableModel
{
    friend class MainWindow;
    friend class EditAction;
    Q_OBJECT
public:
    explicit MovieModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const = 0;

    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) = 0;

    virtual Qt::ItemFlags flags(const QModelIndex& index) const = 0;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    virtual ~MovieModel();
protected:
    QVector<Movie> movies;

signals:
    void undoEdit(QModelIndex index, MovieModel* model, QVariant oldValue, QVariant newValue);

public slots:
    void addMovie(Movie);

    void deleteMovie(int);
};

#endif // MOVIEMODEL_H
