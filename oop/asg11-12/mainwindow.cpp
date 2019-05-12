#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->movieModel = new MovieModel();
    ui->setupUi(this);
    ui->tableView->setModel(this->movieModel);
    ui->tableView->resizeColumnsToContents();

    connect(
        this,
        SIGNAL(newMovie(Movie)),
        this->movieModel,
        SLOT(addNewMovie(Movie))
    );
}

MainWindow::~MainWindow()
{
    delete ui;
    delete movieModel;
}

void MainWindow::on_addMovieButton_clicked()
{
    emit newMovie(Movie{
                      ui->nameEdit->text().toStdString(),
                      ui->genreEdit->text().toStdString(),
                      ui->trailerEdit->text().toStdString(),
                      ui->yearSpinBox->value()
                    });
}
