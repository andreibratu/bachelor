#include "answer.h"

Answer::Answer()
{

}

Answer::Answer(int id, int questionId, QString who, QString text, int votes)
{
    this->id = id;
    this->questionId = questionId;
    this->text = text;
    this->votes = votes;
    this->who = who;
}

QTextStream& operator << (QTextStream& stream, const Answer &a)
{
    stream << a.id << ',' << a.questionId << ',' << a.text << ',' << a.who << ',' << a.votes << '\n';

    return stream;
}

QTextStream& operator >> (QTextStream& stream, Answer &a)
{
    QString line;
    stream.readLineInto(&line);
    QStringList tokens = line.split(",", QString::SkipEmptyParts);
    a.id = tokens[0].toInt();
    a.questionId = tokens[1].toInt();
    a.text = tokens[2];
    a.who = tokens[3];
    a.votes = tokens[4].toInt();

    return stream;
}
