//
// Created by andreib on 06.05.2019.
//

#ifndef TEST2_PERSON_H
#define TEST2_PERSON_H


#include <string>
#include <vector>
#include "MedicalAnalysis.h"

class Person {
private:
    std::string name;
    std::vector<MedicalAnalysis*> analyses;
public:
    Person(std::string name);

    void addAnalysis(MedicalAnalysis* a);

    std::vector<MedicalAnalysis*> getAllAnalyses();

    std::vector<MedicalAnalysis*> getAnalysesByMonth(int month);

    bool isIll(int month);

    std::vector<MedicalAnalysis*> getAnalysesBetweenDates(const std::string& date1, const std::string& date2);

    void writeToFile(const std::string& filename, const std::string& date1, const std::string& date2);

    ~Person();
};


#endif //TEST2_PERSON_H
