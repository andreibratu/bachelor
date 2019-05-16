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

    ~PlaylistMovieModel() = default;

public slots:
    void movieAddedToPlaylist(Movie);

    void movieRemovedFromPlaylist(Movie);
};

#endif // PLAYLISTMOVIEMODEL_H
