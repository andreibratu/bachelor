//
// Created by andreib on 21.04.2019.
//

#include <sqlite3.h>
#include <zconf.h>
#include <sstream>
#include "DbMovieRepo.h"


DbMovieRepo::DbMovieRepo(const std::string& path) {
    std::stringstream ss;
    ss << "../" << path;
    int error = sqlite3_open(ss.str().c_str(), &this->db);
    if(!error) {
        std::cout << "Hello there!";
        this->load();
    }
    else {
        throw std::exception();
    }
}


DbMovieRepo::~DbMovieRepo() {
    this->save();
    sqlite3_close(this->db);
}


void DbMovieRepo::load() {
    const char* sql = std::string("SELECT * FROM MOVIE").c_str();
    char* error = nullptr;
    sqlite3_exec(this->db, sql, callback, nullptr, &error);
}


void DbMovieRepo::save() {
    char* error = nullptr;
    const char* dropTableSql = std::string("DELETE * FROM MOVIE").c_str();
    sqlite3_exec(this->db, dropTableSql, empty_callback, nullptr, &error);

    for(int idx = 0; idx < this->objects.size(); idx++) {
        std::stringstream ss;
        Movie m = this->objects[idx];
        ss << "INSERT INTO MOVIE VALUES (" << idx << m.getName() << m.getGenre() << m.getTrailer() << m.getYear() << m.getLikes() << ")";
        const char* insertSql = ss.str().c_str();
        sqlite3_exec(this->db, insertSql, empty_callback, nullptr, &error);
    }
}


int DbMovieRepo::callback(void *data, int argc, char **argv, char **azColName) {
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for(i = 0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}


int DbMovieRepo::empty_callback(void *data, int argc, char **agv, char **azColName) {
    return 0;
}
