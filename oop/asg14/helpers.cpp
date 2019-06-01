#include "helpers.h"

void writeCSV(const QVector<Movie> &movies, QString filename) {
    QFile file(filename);

    if(file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);

        for(auto m : movies) {
            out << m.name << ','
                << m.genre << ','
                << m.trailer << ','
                << m.year << ','
                << m.likes << ','
                << endl;
        }
        file.close();
    }
}

void readCSV(QVector<Movie> &movies, QString filename) {
    QFile file(filename);

    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while(!in.atEnd()) {
            // read one line from textstream(separated by "\n")
            QString fileLine = in.readLine();
            // parse the read line into separate pieces(tokens) with "," as the delimiter
            QStringList lineToken = fileLine.split(",", QString::SkipEmptyParts);
            movies.push_back(Movie{
                lineToken[0],
                lineToken[1],
                lineToken[2],
                lineToken[3].toInt(),
                lineToken[4].toInt(),
            });
        }
        file.close();
    }
}
