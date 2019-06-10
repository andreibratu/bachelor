#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QUndoStack>
#include <QMainWindow>
#include <adminmoviemodel.h>
#include <usermoviemodel.h>
#include <movie.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    friend class MovieModel;
    Q_OBJECT

public:
    QUndoStack adminUndoStack{};
    QUndoStack userUndoStack{};

    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void on_addMovieButton_clicked();

    void on_deleteMovieButton_clicked();

    void on_sendToPlaylistButton_clicked();

    void on_sendFromPlaylistButton_clicked();

    void on_undoButton_clicked();

    void on_redoButton_clicked();

    void on_userUndoButton_clicked();

    void on_userRedoButton_clicked();

public slots:
    void undoEditHandle(QModelIndex index, MovieModel* model, QVariant oldValue, QVariant newValue);

signals:
    void adminAddMovie(Movie);

    void adminRemoveMovie(int);

    void playlistAddMovie(Movie);

    void playlistRemoveMovie(int);

private:
    Ui::MainWindow *ui;

    MovieModel *adminMovieModel;

    MovieModel *userMovieModel;

    MovieModel* playlistMovieModel;

    void setup_graph();
};

#endif // MAINWINDOW_H
