#ifndef QUESTION_H
#define QUESTION_H

#include <QString>
#include <QVector>
#include <QTextStream>
#include "answer.h"

class Question
{
public:
    int id;
    QString who;
    QString text;
    QVector<Answer> answers;
    Question();
    Question(int id, QString who, QString text);
    friend QTextStream& operator >> (QTextStream& stream, Question &q);
    friend QTextStream& operator << (QTextStream& stream, const Question &q);
};

#endif // QUESTION_H
