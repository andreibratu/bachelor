//
// Created by andreib on 21.04.2019.
//

#ifndef ASG8_9_DB_MOV_REPO_H
#define ASG8_9_DB_MOV_REPO_H

#include "db/DbRepository.h"
#include <movie/MovieRepository.h>

class DbMovieRepo: public DbRepository, public MovieRepository {
public:
    explicit DbMovieRepo(const std::string& filename): DbRepository(filename) {}
};

#endif //ASG8_9_DBREPOSITORY_H
