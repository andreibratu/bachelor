//
// Created by andreib on 06.05.2019.
//

#ifndef TEST2_BP_H
#define TEST2_BP_H


#include "MedicalAnalysis.h"

class BP: public MedicalAnalysis {
private:
    int systolicValue;
    int distolicValue;
public:
    BP(std::string date, int systolicValue, int dystolicValue);

    bool isResultOk() override ;

    std::string toString() override;

    ~BP() override = default;
};


#endif //TEST2_BP_H
