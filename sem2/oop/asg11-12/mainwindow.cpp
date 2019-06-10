#include <QtCharts>
#include "movie.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "playlistmoviemodel.h"
#include "usermoviemodel.h"
#include <unordered_map>


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

    connect(this, SIGNAL(adminAddMovie(Movie)), this->adminMovieModel, SLOT(addMovie(Movie)));
    connect(this, SIGNAL(adminAddMovie(Movie)), this->userMovieModel, SLOT(addMovie(Movie)));
    connect(this, SIGNAL(adminRemoveMovie(int)), this->adminMovieModel, SLOT(deleteMovie(int)));
    connect(this, SIGNAL(adminRemoveMovie(int)), this->userMovieModel, SLOT(deleteMovie(int)));
    connect(this, SIGNAL(playlistAddMovie(Movie)), this->playlistMovieModel, SLOT(addMovie(Movie)));
    connect(this, SIGNAL(playlistRemoveMovie(int)), this->playlistMovieModel, SLOT(deleteMovie(int)));
//    connect(
//        this->adminMovieModel,
//        SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
//        this->userMovieModel,
//        SLOT(updateData(QModelIndex,QModelIndex,QVector<int>))
//    );
//    connect(
//        this->userMovieModel,
//        SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
//        this->adminMovieModel,
//        SLOT(updateData(QModelIndex,QModelIndex,QVector<int>))
//    );
//    connect(
//        this,
//        SIGNAL(sendToPlaylist(Movie)),
//        this->playlistMovieModel,
//        SLOT(movieAddedToPlaylist(Movie))
//    );

//    connect(
//        this->movieModel,
//        SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
//        this,
//        SLOT(movieModelChartUpdate(QModelIndex, QModelIndex, QVector<int>))
//    );

    this->setup_graph();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete adminMovieModel;
    delete userMovieModel;
    delete playlistMovieModel;
}

void MainWindow::on_addMovieButton_clicked()
{
    emit adminAddMovie(Movie{ui->nameEdit->text(), ui->genreEdit->text(), 0, ui->yearSpinBox->value(), ui->trailerEdit->text()});
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
           emit this->adminRemoveMovie(row.row());
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
            emit playlistAddMovie(Movie{
                columns[0].data(),
                columns[1].data(),
                columns[2].data(),
                columns[3].data(),
                columns[4].data()
            });
           emit adminRemoveMovie(rowIndex);
       }
    }
}

void MainWindow::setup_graph() {
    QPieSeries *series = new QPieSeries();
    std::vector<QPieSlice*> slices;

    QHash<QString, int> genreCount;

    for (auto x : this->adminMovieModel->movies)
    {
        genreCount[x.genre] += 1;
    }

    int i = 0;
    for (auto x = genreCount.begin(); x != genreCount.end(); x++) {
        series->append(x.key(), x.value());
        slices.push_back(series->slices().at(i));
        slices[i]->setLabelVisible();
        i++;
    }

    QChart *chart = new QChart();
    chart->setTheme(chart->ChartThemeBrownSand);
    chart->addSeries(series);
    chart->setTitle("Movie genre percentage");

    QChartView *chart_view = new QChartView(chart);
    chart_view->setRenderHint(QPainter::Antialiasing);
    chart_view->setMinimumWidth(499);

    ui->statsTab->layout()->addWidget(chart_view);
}

void MainWindow::on_sendFromPlaylistButton_clicked()
{
    QItemSelectionModel *selection = this->ui->playlistTableView->selectionModel();
    if(selection->hasSelection()) {
       for(auto r : selection->selectedRows()) {
           int rowIndex = r.row();
           QVector<QModelIndex> columns;
           for(int i = 0; i < 5; i++) {
               columns << this->userMovieModel->index(rowIndex, i);
           }
            // Get all columns from row - locations are indexes
            emit adminAddMovie(Movie{
                columns[0].data(),
                columns[1].data(),
                columns[2].data(),
                columns[3].data(),
                columns[4].data()
            });
           emit playlistRemoveMovie(rowIndex);
       }
    }
}
