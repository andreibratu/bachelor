#include "question.h"

Question::Question()
{

}

Question::Question(int id, QString who, QString text)
{
    this->id = id;
    this->who = who;
    this->text = text;
}

QTextStream& operator >> (QTextStream& stream, Question &q)
{
    QString line;
    stream.readLineInto(&line);
    QStringList tokens = line.split(",", QString::SkipEmptyParts);
    q.id = tokens[0].toInt();
    q.text = tokens[1];
    q.who = tokens[2];

    return stream;
}

QTextStream& operator << (QTextStream& stream, const Question &q)
{
    stream << q.id << ',' << q.text << ',' << q.who << '\n';

    return stream;
}
