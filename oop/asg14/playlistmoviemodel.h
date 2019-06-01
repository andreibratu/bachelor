#ifndef PLAYLISTMOVIEMODEL_H
#define PLAYLISTMOVIEMODEL_H

#include "moviemodel.h"

class PlaylistMovieModel : public MovieModel
{
    Q_OBJECT

public:
    explicit PlaylistMovieModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    ~PlaylistMovieModel() override;
};

#endif // PLAYLISTMOVIEMODEL_H
