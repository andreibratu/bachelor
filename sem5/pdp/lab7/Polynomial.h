//
// Created by bratu on 11/14/2020.
//

#ifndef LAB7_POLYNOMIAL_H
#define LAB7_POLYNOMIAL_H
#include <vector>
#include <string>
#include <algorithm>
#include <ostream>

class Polynomial {
private:
    std::vector<int> coefficients;
    static std::vector<int> vectorToPolygon(std::vector<int>& poly){
        std::reverse(poly.begin(), poly.end());
        return poly;
    }

public:
    Polynomial() = default;

    explicit Polynomial(std::vector<int>& numericVector): coefficients{vectorToPolygon(numericVector)} {}

    friend std::ostream& operator<<(std::ostream& os, const Polynomial& dt);

    [[nodiscard]] const std::vector<int>& getCoefficients() const;

    void setCoefficients(std::vector<int>& newCoefficients);
};

#endif //LAB7_POLYNOMIAL_H
