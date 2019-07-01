#include "store.h"
#include "helpers.h"
#include <algorithm>

Store::Store(QObject *parent) : QObject(parent)
{
    QVector<Answer> answers;
    readObjects(answers, "/home/andreib/qasite/answers.csv");
    readObjects(questions, "/home/andreib/qasite/questions.csv");
    for(auto a : answers)
    {
        users.push_back(a.who);
    }
    for(auto q : questions)
    {
        users.push_back(q.who);
        std::copy_if(answers.begin(),
                     answers.end(),
                     std::back_inserter(q.answers),
                     [&q](const Answer &a)
        {
            return a.questionId == q.id;
        }
        );
    }
}

void Store::init()
{
    emit update(questions);
}

void Store::onUpdate(QVector<Question> questions)
{
    this->questions = questions;
    emit update(questions);
}

QVector<QString> Store::getUsers()
{
    return QVector<QString>(users);
}
