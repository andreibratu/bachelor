#ifndef ANSWER_H
#define ANSWER_H

#include <QString>
#include <QTextStream>

class Answer
{
public:
    int id;
    int questionId;
    QString text;
    QString who;
    int votes;
    Answer();
    Answer(int id, int questionId, QString who, QString text, int votes);
    friend QTextStream& operator << (QTextStream& stream, const Answer& a);
    friend QTextStream& operator >> (QTextStream& stream, Answer& a);
};

#endif // ANSWER_H
