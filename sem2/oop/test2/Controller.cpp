//
// Created by andreib on 06.05.2019.
//

#include <iostream>
#include "Controller.h"

void Controller::add(MedicalAnalysis* a) {
    this->p.addAnalysis(a);
}

std::vector<MedicalAnalysis*> Controller::getAll() {
    return std::vector<MedicalAnalysis*>(this->p.getAllAnalyses());
}

std::vector<MedicalAnalysis*> Controller::getByMonth(int month) {
    return std::vector<MedicalAnalysis*>(this->p.getAnalysesByMonth(month));
}

bool Controller::isIll(int month) {
    return this->p.isIll(month);
}

std::vector<MedicalAnalysis*> Controller::getDates(const std::string& date1, const std::string& date2) {
    return std::vector<MedicalAnalysis*>(this->p.getAnalysesBetweenDates(date1, date2));
}

void Controller::writeUsDownScotty(const std::string &f, const std::string& date1, const std::string& date2) {
    this->p.writeToFile(f, date1, date2);
}

Controller::Controller(Person &person): p{person} {}




