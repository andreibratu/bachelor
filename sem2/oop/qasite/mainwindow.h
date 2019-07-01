#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "questionservice.h"
#include "question.h"
#include "answer.h"
#include "store.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Store *store, QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    QVector<Question> questions;
    void setBestQuestionLabel(const QString& text);
    void setBestAnswersTabel(QVector<Answer> Answers);
signals:
    void update(QVector<Question> questions);
public slots:
    void onUpdate(QVector<Question> questions);
private slots:
    void on_searchBox_textEdited(const QString &arg1);
};

#endif // MAINWINDOW_H
