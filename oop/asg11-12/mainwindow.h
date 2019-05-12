#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <moviemodel.h>
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

signals:
    void newMovie(Movie);

private:
    Ui::MainWindow *ui;
    MovieModel* movieModel;
};

#endif // MAINWINDOW_H
