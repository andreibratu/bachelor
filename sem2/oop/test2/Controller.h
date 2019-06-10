//
// Created by andreib on 06.05.2019.
//

#ifndef TEST2_REPOSITORY_H
#define TEST2_REPOSITORY_H


#include "Person.h"

class Controller {
private:
    Person& p;
public:
    Controller(Person& person);

    void add(MedicalAnalysis* a);

    std::vector<MedicalAnalysis*> getAll();

    std::vector<MedicalAnalysis*> getByMonth(int month);

    bool isIll(int month);

    std::vector<MedicalAnalysis*> getDates(const std::string& date1, const std::string& date2);

    void writeUsDownScotty(const std::string& f, const std::string& date1, const std::string& date2);
};


#endif //TEST2_REPOSITORY_H
