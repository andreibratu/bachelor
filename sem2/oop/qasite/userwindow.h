#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QDialog>
#include <QString>
#include "questionservice.h"
#include "answer.h"
#include "question.h"
#include "store.h"

namespace Ui {
class UserWindow;
}

class UserWindow : public QDialog
{
    Q_OBJECT
public:
    UserWindow(Store* store, QString user, QWidget *parent);
    ~UserWindow();
private:
    Ui::UserWindow *ui;
    QString user;
    QVector<Question> questions;
    Question *currentQuestion;
    void setQuestionTable(QVector<Question> questions);
    void setAnswersTable(QVector<Answer> answers);
    void setAnswerFormComboBox(QVector<Question> questions);
    void setAnswerFormSubmitButton();
public slots:
    void onUpdate(QVector<Question> questions);
    void onVoteUpdate(int val);
signals:
    void update(QVector<Question> questions);
private slots:
    void on_questionTextInput_textEdited(const QString &arg1);
    void on_questionFormSubmitButton_clicked();
    void on_questionsTable_cellActivated(int row, int column);
    void on_questionSelectComboBox_currentIndexChanged(int index);
    void on_answerTextInput_textEdited(const QString &arg1);
    void on_answerFormSubmitButton_clicked();
};

#endif // USERWINDOW_H
