#ifndef ADDACTION_H
#define ADDACTION_H

#include <QUndoCommand>
#include "mainwindow.h"
#include <movie.h>
#include "moviemodel.h"

class AdminAddAction : public QUndoCommand
{
private:
    Movie movie;
    MovieModel* model;
    MainWindow* window;
public:
    AdminAddAction(Movie m, MovieModel* model, MainWindow* window);

    void redo() override;

    void undo() override;

    ~AdminAddAction() override;
};

#endif // ADDACTION_H
