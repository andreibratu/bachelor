#ifndef ADMINEDITACTION_H
#define ADMINEDITACTION_H

#include <QModelIndex>
#include <QUndoCommand>
#include <QVariant>
#include "moviemodel.h"

class EditAction : public QUndoCommand
{
private:
    QModelIndex index;
    MovieModel* model;
    QVariant oldValue;
    QVariant newValue;
    void applyValue(QVariant value);
public:
    EditAction(QModelIndex index, MovieModel* model, QVariant oldValue, QVariant newValue);

    void undo() override;

    void redo() override;

    ~EditAction() override;
};

#endif // ADMINEDITACTION_H
