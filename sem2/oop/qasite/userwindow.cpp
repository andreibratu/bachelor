#include <QTableWidgetItem>
#include <QSpinBox>
#include "userwindow.h"
#include "ui_userwindow.h"
#include "assert.h"

UserWindow::UserWindow(Store *store, QString user, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserWindow)
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
    this->user = user;
    ui->setupUi(this);
    this->setWindowTitle(user);

    ui->questionFormSubmitButton->setEnabled(false);
    ui->answerFormSubmitButton->setEnabled(false);

    ui->questionsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->questionsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->questionsTable->setColumnCount(2);

    ui->answersTable->setColumnCount(3);
}

UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::setQuestionTable(QVector<Question> questions)
{
    QuestionService::sortByNumberAnswers(questions);
    ui->questionsTable->setRowCount(questions.size());
    int r = 0;
    for(auto question : questions)
    {
        QTableWidgetItem *text = new QTableWidgetItem(question.text);
        QTableWidgetItem *who = new QTableWidgetItem(question.who);
        ui->questionsTable->setItem(r, 0, text);
        ui->questionsTable->setItem(r, 1, who);
        r += 1;
    }
}

void UserWindow::onUpdate(QVector<Question> questions)
{
    this->questions = questions;
    setQuestionTable(questions);
    setAnswerFormComboBox(questions);
}

void UserWindow::setAnswerFormComboBox(QVector<Question> questions)
{
    ui->questionSelectComboBox->addItem("Select..");
    for(auto question : questions)
    {
        ui->questionSelectComboBox->addItem(question.text);
    }
    ui->questionSelectComboBox->setCurrentIndex(0);
}

void UserWindow::on_questionTextInput_textEdited(const QString &arg1)
{
    ui->questionFormSubmitButton->setEnabled(arg1 != "");
}

void UserWindow::on_questionFormSubmitButton_clicked()
{
    Question q{questions.size(), user, ui->questionTextInput->text()};
    ui->questionTextInput->clear();
    questions.push_back(q);
    emit this->update(questions);
}

void UserWindow::on_questionsTable_cellActivated(int row, int column)
{
    currentQuestion = &questions[row];
    setAnswersTable(questions[row].answers);
}

void UserWindow::setAnswersTable(QVector<Answer> answers)
{
    ui->answersTable->setRowCount(answers.size());
    int r = 0;
    for(auto answer : answers)
    {
        QTableWidgetItem *text = new QTableWidgetItem(answer.text);
        QTableWidgetItem *who = new QTableWidgetItem(answer.who);
        QSpinBox *votes = new QSpinBox(ui->answersTable);
        votes->setValue(answer.votes);
        connect(votes,
                SIGNAL(valueChanged(int)),
                this,
                SLOT(onVoteUpdate(int))
        );

        if(answer.who == user)
        {
            text->setBackgroundColor(Qt::yellow);
            who->setBackgroundColor(Qt::yellow);
            votes->setStyleSheet("QComboBox { background-color: yellow; }"); // frumos asa
        }

        ui->answersTable->setItem(r, 0, text);
        ui->answersTable->setItem(r, 1, who);
        ui->answersTable->setCellWidget(r, 2, new QSpinBox(ui->answersTable));
    }
}

void UserWindow::setAnswerFormSubmitButton()
{
    ui->answerFormSubmitButton->setEnabled(
        ui->questionSelectComboBox->currentIndex() != 0 &&
        ui->answerTextInput->text() != ""
    );
}

void UserWindow::on_questionSelectComboBox_currentIndexChanged(int index)
{
    setAnswerFormSubmitButton();
}

void UserWindow::on_answerTextInput_textEdited(const QString &arg1)
{
    setAnswerFormSubmitButton();
}

void UserWindow::on_answerFormSubmitButton_clicked()
{
    QString text = ui->answerTextInput->text();
    int index = ui->questionSelectComboBox->currentIndex();
}

void UserWindow::onVoteUpdate(int val)
{
    QWidget* spinBox = qobject_cast<QWidget*>(sender());
    for(int r = 0; r < ui->answersTable->rowCount(); r++)
    {
        // Identify the sending spinbox
        if(ui->answersTable->cellWidget(r, 2) == spinBox)
        {
            currentQuestion->answers[r].votes = val;
            emit update(questions);
            break;
        }
    }
    assert(0);
}
