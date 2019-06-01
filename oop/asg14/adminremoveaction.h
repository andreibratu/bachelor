#ifndef ADMINREMOVEACTION_H
#define ADMINREMOVEACTION_H

#include <QUndoCommand>
#include "moviemodel.h"
#include "movie.h"
#include "mainwindow.h"

class AdminRemoveAction : public QUndoCommand
{
private:
    int row;
    MovieModel* model;
    Movie movie;
    MainWindow* window;
public:
    AdminRemoveAction(Movie m, MovieModel* model, MainWindow* window, int row);

    void undo() override;

    void redo() override;

    ~AdminRemoveAction() override;
};

#endif // ADMINREMOVEACTION_H
