#ifndef STORE_H
#define STORE_H

#include <QObject>
#include <QVector>
#include <QString>
#include "answer.h"
#include "question.h"

class Store : public QObject
{
Q_OBJECT
private:
    QVector<Question> questions;
    QVector<QString> users;
public:
    Store(QObject *parent = nullptr);
    QVector<QString> getUsers();
    void init();
public slots:
    void onUpdate(QVector<Question> questions);
signals:
    void update(QVector<Question> questions);
};

#endif // STORE_H
