#ifndef HELPERS_H
#define HELPERS_H

#include <QTextStream>
#include <QVector>
#include <QString>
#include <QFile>

template <class T>
void readObjects(QVector<T> &objects, QString filename)
{
    QFile file(filename);

    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            T object;
            in >> object;
            objects.push_back(object);
        }
    }
}

template <class T>
void writeObjects(const QVector<T> &objects, QString filename)
{
    QFile file(filename);

    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);

        for(auto o : objects) out << o;
    }
}

#endif // HELPERS_H
