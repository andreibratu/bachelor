//
// Created by andreib on 21.04.2019.
//

#ifndef ASG8_9_DBMOVIEREPO_H
#define ASG8_9_DBMOVIEREPO_H


#include <Movie.h>
#include <sqlite3.h>
#include "../abstract/PersistentRepository.h"


class DbMovieRepo: virtual protected PersistentRepository<Movie>{
private:
    sqlite3* db;

    void load() override;

    void save() override;

    static int callback(void* data, int argc, char** argv, char** azColName);

    static int empty_callback(void* data, int argc, char** agv, char** azColName);
public:

    explicit DbMovieRepo(const std::string& path);

    ~DbMovieRepo();
};


#endif //ASG8_9_DBMOVIEREPO_H
