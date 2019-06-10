#ifndef ADMINMOVIEMODEL_H
#define ADMINMOVIEMODEL_H

#include <QUndoCommand>
#include "moviemodel.h"
#include "movie.h"

class AdminMovieModel: public MovieModel
{
    Q_OBJECT
public:
    explicit AdminMovieModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const;

    ~AdminMovieModel() override;
};

#endif
