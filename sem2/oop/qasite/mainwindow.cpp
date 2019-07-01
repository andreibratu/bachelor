#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Store *store, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    connect(store,
            SIGNAL(update(QVector<Question>)),
            this,
            SLOT(onUpdate(QVector<Question>))
            );
    connect(this,
            SIGNAL(update(QVector<Question>)),
            store,
            SLOT(onUpdate(QVector<Question>))
            );
    ui->setupUi(this);
    this->setWindowTitle("Search");
    ui->bestAnswersTable->setColumnCount(3);
    ui->bestAnswersTable->setRowCount(3);
}

void MainWindow::onUpdate(QVector<Question> questions)
{
    this->questions = questions;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_searchBox_textEdited(const QString &arg1)
{
    if(arg1 == "")
    {
        setBestQuestionLabel("");
        setBestAnswersTabel({});
        return;
    }
    Question q = QuestionService::filterByQuery(questions, arg1);
    setBestQuestionLabel(q.text);
    setBestAnswersTabel(q.answers);
}

void MainWindow::setBestQuestionLabel(const QString &text)
{
    ui->bestQuestionLabel->setText(text);
}

void MainWindow::setBestAnswersTabel(QVector<Answer> answers)
{
    for(int i = 0; i < std::min(answers.size(), 3); i++)
    {
        Answer a = answers[i];
        QTableWidgetItem *text = new QTableWidgetItem(a.text);
        QTableWidgetItem *who = new QTableWidgetItem(a.who);
        QTableWidgetItem *votes = new QTableWidgetItem(a.votes);
        ui->bestAnswersTable->setItem(i, 0, text);
        ui->bestAnswersTable->setItem(i, 1, who);
        ui->bestAnswersTable->setItem(i, 2, votes);
    }
}
