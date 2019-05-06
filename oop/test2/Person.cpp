//
// Created by andreib on 06.05.2019.
//

#include <algorithm>
#include <fstream>
#include "Person.h"

Person::Person(std::string name) {
    this->name = name;
}

void Person::addAnalysis(MedicalAnalysis* a) {
    this->analyses.push_back(a);
}

std::vector<MedicalAnalysis*> Person::getAllAnalyses() {
    return std::vector<MedicalAnalysis*>(this->analyses);
}

std::vector<MedicalAnalysis*> Person::getAnalysesByMonth(int month) {
    std::vector<MedicalAnalysis*> result(this->analyses.size());

    auto condition = [month](MedicalAnalysis* a) {
        int a_month = stoi(a->getDate().substr(5,2));
        return a_month == month;
    };

    auto it = std::copy_if(
        this->analyses.begin(),
        this->analyses.end(),
        result.begin(),
        condition
    );

    result.resize(std::distance(result.begin(), it));
    return result;
}

bool Person::isIll(int month) {
    std::vector<MedicalAnalysis*> as = this->getAnalysesByMonth(month);

    for(auto x: as) {
        if(x->isResultOk()) {
            return false;
        }
    }

    return true;
}

std::vector<MedicalAnalysis*> Person::getAnalysesBetweenDates(const std::string& date1, const std::string& date2) {
    std::vector<MedicalAnalysis*> result(this->analyses.size());

    auto condition = [date1, date2](MedicalAnalysis* a) {
        return date1 <= a->getDate() && a->getDate() <= date2;
    };

    auto it = std::copy_if(
        this->analyses.begin(),
        this->analyses.end(),
        result.begin(),
        condition
    );

    result.resize(std::distance(result.begin(), it));
    return result;
}

void Person::writeToFile(const std::string& filename, const std::string& date1, const std::string& date2) {
    std::fstream out(filename, std::fstream::out | std::fstream::trunc);

    std::vector<MedicalAnalysis*> result = this->getAnalysesBetweenDates(date1, date2);
    for(auto x: result) {
        std::string s = x->toString();
        out << s << '\n';
    }
}

Person::~Person() {
    for(auto x: this->analyses) {
        delete x;
    }
}


