#include "adminaddaction.h"

AdminAddAction::AdminAddAction(Movie m, MovieModel* model, MainWindow* window)
{
    this->window = window;
    this->movie = m;
    this->model = model;
}

void AdminAddAction::redo()
{
    emit window->adminAddMovie(movie);
}

void AdminAddAction::undo()
{
    emit window->adminRemoveMovie(model->rowCount()-1);
}

AdminAddAction::~AdminAddAction() = default;
