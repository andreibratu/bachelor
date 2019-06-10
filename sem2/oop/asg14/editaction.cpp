#include "editaction.h"

EditAction::EditAction(QModelIndex index, MovieModel* model, QVariant oldValue, QVariant newValue)
{
    this->index = index;
    this->model = model;
    this->oldValue = oldValue;
    this->newValue = newValue;
}

void EditAction::undo()
{
    this->applyValue(oldValue);
}

void EditAction::redo()
{
    this->applyValue(newValue);
}

void EditAction::applyValue(QVariant value)
{
    int row = index.row();
    int column = index.column();
    Movie& m = model->movies[row];
    switch (column) {
    case 0:
        m.name = value.toString();
        break;
    case 1:
        m.genre = value.toString();
        break;
    case 2:
        m.likes = value.toInt();
        break;
    case 3:
        m.year = value.toInt();
        break;
    case 4:
        m.trailer = value.toString();
        break;
    }
    emit model->dataChanged(index, index, QVector<int>() << Qt::EditRole);
}

EditAction::~EditAction() = default;
