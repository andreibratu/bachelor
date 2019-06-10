//
// Created by andreib on 06.05.2019.
//

#ifndef TEST2_MEDICALANALYSIS_H
#define TEST2_MEDICALANALYSIS_H


#include <string>

class MedicalAnalysis {
protected:
    MedicalAnalysis() = default;
public:
    std::string date;

    virtual bool isResultOk() = 0;

    virtual std::string toString() = 0;

    std::string getDate() const;

    virtual ~MedicalAnalysis() = default;
};


#endif //TEST2_MEDICALANALYSIS_H
