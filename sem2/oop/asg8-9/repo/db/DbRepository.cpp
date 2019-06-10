//
// Created by andreib on 21.04.2019.
//

#include <sqlite3.h>
#include <zconf.h>
#include <sstream>
#include <cstring>
#include "DbRepository.h"


static int callback(void *arr, int argc, char **argv, char **azColName) {
    auto* p_vector = (std::vector<Movie>*)arr;
    Movie m{};

    m.setName(argv[1]);
    m.setGenre(argv[2]);
    m.setTrailer(argv[3]);
    m.setYear(std::stoi(argv[4]));
    m.setLikes(std::stoi(argv[5]));

    p_vector->push_back(m);
    return 0;
}



DbRepository::DbRepository(const std::string& path) {
    std::stringstream ss;
    ss << "../" << path;
    this->filename = ss.str();
    int error = sqlite3_open(ss.str().c_str(), &this->db);
    if(!error) {
        this->load();
    }
    else {
        throw std::exception();
    }
}


DbRepository::~DbRepository() {
    this->save();
    sqlite3_close(this->db);
}


void DbRepository::load() {
    const char* sql = "SELECT * FROM MOVIES";
    char* error = nullptr;
    sqlite3_exec(this->db, sql, callback, (void*)&this->objects, &error);
}


void DbRepository::save() {
    char* error = nullptr;
    const char* dropTableSql = "DELETE * FROM MOVIES";
    sqlite3_exec(this->db, dropTableSql, nullptr, nullptr, &error);

    for(int idx = 0; idx < this->objects.size(); idx++) {
        std::stringstream ss;
        Movie m = this->objects[idx];
        ss << "INSERT INTO MOVIES VALUES (" << idx << "," << m.getName()
           << "," << m.getGenre() << "," << m.getTrailer() << ","
           << m.getYear() << "," << m.getLikes() << ")";
        char* insertSql = new char [ss.str().size()+1];
        strcpy(insertSql, ss.str().c_str());
        sqlite3_exec(this->db, insertSql, nullptr, nullptr, &error);
    }
}