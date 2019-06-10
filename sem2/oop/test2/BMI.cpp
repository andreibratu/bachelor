#include <utility>

//
// Created by andreib on 06.05.2019.
//

#include <sstream>
#include "BMI.h"


bool BMI::isResultOk() {
    return 18.5 <= this->value && this->value <= 25;
}

std::string BMI::toString() {
    std::stringstream ss;
    ss << "BMI" << ' ' << this->date << ' ' << this->value;
    return ss.str();
}

BMI::BMI(std::string date, double value) {
    this->date = date;
    this->value = value;
}
