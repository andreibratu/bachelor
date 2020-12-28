//
// Created by Andrei Bratu on 20.12.2020.
//

#ifndef LAB8_DSMVALUE_H
#define LAB8_DSMVALUE_H

struct DSMValue {
    enum type_enum {INT = 0, DOUBLE = 1, CHR_ARR = 2} type;

    union {
        int intValue{};
        double dblValue;
        char strValue[30];
    } value;

    DSMValue() {
        this->type = INT;
    }

    explicit DSMValue(int val) {
        this->type = INT;
        this->value.intValue = val;
    }

    explicit DSMValue(double val) {
        this->type = DOUBLE;
        this->value.dblValue = val;
    }

    explicit DSMValue(const char* arr) {
        assert (strlen(arr) < 30);
        this->type = CHR_ARR;
        strcpy(this->value.strValue, arr);
    }
};

#endif //LAB8_DSMVALUE_H
