//
// Created by bratu on 11/14/2020.
//

#include <iostream>
#include "Polynomial.h"


std::ostream &operator<<(std::ostream &os, const Polynomial &dt) {
    std::vector<int> number = dt.coefficients;
    for(int i = number.size() - 1; i >= 0; i--){ // NOLINT(cppcoreguidelines-narrowing-conversions)
        if(i == number.size() - 2 && number[i + 1] == 0){
            if(number[i] > 0){
                os << number[i] << "x^" << std::to_string(i);
            }else{
                os << std::abs(number[i]) << "x^" << std::to_string(i);
            }
        }
        if(number[i] != 0 && i != 0) {
            if(i == number.size() - 1) {
                if (number[i] > 0) {
                    os << number[i] << "x^" << std::to_string(i);
                }
                else {
                    os << "-" << std::abs(number[i]) << "x^" << std::to_string(i);
                }
            }
            else {
                if(number[i] > 0) {
                    os << " + " << number[i] << "x^" << std::to_string(i);
                }
                else {
                    os << " - " << std::abs(number[i]) << "x^" << std::to_string(i);
                }
            }
        }
        else if(i == 0 && number[i] != 0) {
            if (number[i] > 0) {
                os << " + " << number[i];
            }
            else{
                os << " - " << std::abs(number[i]);
            }
        }
    }
    return os;
}

const std::vector<int> &Polynomial::getCoefficients() const {
    return this->coefficients;
}

void Polynomial::setCoefficients(std::vector<int> &newCoefficients) {
    this->coefficients = newCoefficients;
}


