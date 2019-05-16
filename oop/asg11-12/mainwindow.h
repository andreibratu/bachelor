#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <adminmoviemodel.h>
#include <usermoviemodel.h>
#include <movie.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addMovieButton_clicked();

    void on_deleteMovieButton_clicked();

    void on_sendToPlaylistButton_clicked();

signals:
    void newMovie(Movie);

    void sendToPlaylist(Movie);

    void sendFromPlaylist(Movie);

    void movieWasDeleted(int);

private:
    Ui::MainWindow *ui;
    MovieModel* adminMovieModel;
    MovieModel* userMovieModel;
    MovieModel* playlistMovieModel;
};

#endif // MAINWINDOW_H
