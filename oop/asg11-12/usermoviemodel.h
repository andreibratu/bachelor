#ifndef USERMOVIEMODEL_H
#define USERMOVIEMODEL_H

#include <QAbstractTableModel>
#include "moviemodel.h"

class UserMovieModel : public MovieModel
{
    Q_OBJECT
public:
    explicit UserMovieModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    ~UserMovieModel() override;
};

#endif
