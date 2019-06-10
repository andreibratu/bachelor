//
// Created by andreib on 06.05.2019.
//

#ifndef TEST2_BMI_H
#define TEST2_BMI_H

#include "MedicalAnalysis.h"

class BMI: public MedicalAnalysis {
private:
    double value;
public:
    BMI(std::string date, double value);

    bool isResultOk() override;

    std::string toString() override;

    ~BMI() override = default;
};


#endif //TEST2_BMI_H
