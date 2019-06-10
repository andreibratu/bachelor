#include <utility>

//
// Created by andreib on 06.05.2019.
//

#include <sstream>
#include "BP.h"

bool BP::isResultOk() {
    return 90 <= this->systolicValue && this->systolicValue <= 119 &&
            60 <= this->distolicValue && this->distolicValue <= 79;
}

std::string BP::toString() {
    std::stringstream ss;
    ss << "BP" << ' ' << this->date << ' ' << this->systolicValue << ' ' << this->distolicValue;
    return ss.str();
}

BP::BP(std::string date, int systolicValue, int dystolicValue) {
    this->date = date;
    this->systolicValue = systolicValue;
    this->distolicValue = dystolicValue;
}