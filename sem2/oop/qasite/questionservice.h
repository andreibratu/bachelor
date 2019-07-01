#ifndef QUESTIONSERVICE_H
#define QUESTIONSERVICE_H

#include <QVector>
#include "question.h"

class QuestionService
{
public:
    static void sortByNumberAnswers(QVector<Question>& questions);
    static Question filterByQuery(const QVector<Question> &questions, const QString &text);
private:
    QuestionService();
};

#endif // QUESTIONSERVICE_H
