#include "adminremoveaction.h"

AdminRemoveAction::AdminRemoveAction(Movie m, MovieModel* model, MainWindow* window, int row)
{
    this->window = window;
    this->movie = m;
    this->model = model;
    this->row = row;
}

void AdminRemoveAction::undo()
{
    emit window->adminAddMovie(movie);
}

void AdminRemoveAction::redo()
{
    emit window->adminRemoveMovie(model->rowCount()-1);
    model->removeRow(row);
}

AdminRemoveAction::~AdminRemoveAction() = default;
