#include <QtCharts>
#include "movie.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "usermoviemodel.h"
#include "playlistmoviemodel.h"

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->adminMovieModel = new AdminMovieModel();
    this->userMovieModel = new UserMovieModel();
    this->playlistMovieModel = new PlaylistMovieModel();

    ui->setupUi(this);

    ui->adminTableView->setModel(this->adminMovieModel);
    ui->adminTableView->resizeColumnsToContents();

    ui->userTableView->setModel(this->userMovieModel);
    ui->userTableView->resizeColumnsToContents();

    ui->playlistTableView->setModel(this->playlistMovieModel);
    ui->playlistTableView->resizeColumnsToContents();

    connect(this, SIGNAL(newMovie(Movie)), this->adminMovieModel, SLOT(addMovie(Movie)));
    connect(this, SIGNAL(newMovie(Movie)), this->userMovieModel, SLOT(addMovie(Movie)));
    connect(this, SIGNAL(movieWasDeleted(int)), this->adminMovieModel, SLOT(deleteMovie(int)));
    connect(this, SIGNAL(movieWasDeleted(int)), this->userMovieModel, SLOT(deleteMovie(int)));
    connect(
        this->adminMovieModel,
        SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
        this->userMovieModel,
        SLOT(updateData(QModelIndex,QModelIndex,QVector<int>))
    );
//    connect(
//        this->userMovieModel,
//        SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
//        this->adminMovieModel,
//        SLOT(updateData(QModelIndex,QModelIndex,QVector<int>))
//    );
    connect(
        this,
        SIGNAL(sendToPlaylist(Movie)),
        this->playlistMovieModel,
        SLOT(movieAddedToPlaylist(Movie))
    );

//    connect(
//        this->movieModel,
//        SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
//        this,
//        SLOT(movieModelChartUpdate(QModelIndex, QModelIndex, QVector<int>))
//    );

//    QBarSet *set0 = new QBarSet("Jane");
//    QBarSet *set1 = new QBarSet("John");
//    QBarSet *set2 = new QBarSet("Axel");
//    QBarSet *set3 = new QBarSet("Mary");
//    QBarSet *set4 = new QBarSet("Samantha");

//    *set0 << 1 << 2 << 3 << 4 << 5 << 6;
//    *set1 << 5 << 0 << 0 << 4 << 0 << 7;
//    *set2 << 3 << 5 << 8 << 13 << 8 << 5;
//    *set3 << 5 << 6 << 7 << 3 << 4 << 5;
//    *set4 << 9 << 7 << 5 << 3 << 1 << 2;

//    QBarSeries *series = new QBarSeries();
//    series->append(set0);
//    series->append(set1);
//    series->append(set2);
//    series->append(set3);
//    series->append(set4);


//    QChart *chart = new QChart();
//    chart->addSeries(series);
//    chart->setTitle("Simple barchart example");
//    chart->setAnimationOptions(QChart::SeriesAnimations);

//    QStringList categories;
//    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
//    QBarCategoryAxis *axisX = new QBarCategoryAxis();
//    axisX->append(categories);
//    chart->addAxis(axisX, Qt::AlignBottom);
//    series->attachAxis(axisX);

//    QValueAxis *axisY = new QValueAxis();
//    axisY->setRange(0,15);
//    chart->addAxis(axisY, Qt::AlignLeft);
//    series->attachAxis(axisY);

//    chart->legend()->setVisible(true);
//    chart->legend()->setAlignment(Qt::AlignBottom);

//    QChartView *chartView = new QChartView(chart);
//    chartView->setRenderHint(QPainter::Antialiasing);

//    ui->statsTab->layout()->addWidget(chartView);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete adminMovieModel;
}

void MainWindow::on_addMovieButton_clicked()
{
    emit newMovie(Movie{ui->nameEdit->text(), ui->genreEdit->text(), 0, ui->yearSpinBox->value(), ui->trailerEdit->text()});
    ui->nameEdit->clear();
    ui->genreEdit->clear();
    ui->yearSpinBox->clear();
    ui->trailerEdit->clear();
}

void MainWindow::on_deleteMovieButton_clicked()
{
    QItemSelectionModel *selection = this->ui->adminTableView->selectionModel();
    if(selection->hasSelection()) {
       for(auto row : selection->selectedRows()) {
           emit this->movieWasDeleted(row.row());
       }
    }
}

void MainWindow::on_sendToPlaylistButton_clicked()
{
    QItemSelectionModel *selection = this->ui->userTableView->selectionModel();
    if(selection->hasSelection()) {
       for(auto r : selection->selectedRows()) {
           int rowIndex = r.row();
           QVector<QModelIndex> columns;
           for(int i = 0; i < 5; i++) {
               columns << this->userMovieModel->index(rowIndex, i);
           }
            // Get all columns from row - locations are indexes
            emit sendToPlaylist(Movie{
                columns[0].data(),
                columns[1].data(),
                columns[2].data(),
                columns[3].data(),
                columns[4].data()
            });
       }
    }
}
