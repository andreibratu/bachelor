from math import sqrt

class Complex:
    """Class that describes a complex number."""

    def __init__(self, real, imag):
        self.real = float(real)
        self.imag = float(imag)
        self.modulus = sqrt(self.real**2 + self.imag**2)

    def __add__(self, other):
        return Complex(self.real + other.real, self.imag + other.imag)

    def __sub__(self, other):
        return Complex(self.real - other.real, self.imag - other.imag)

    def __mul__(self, other):
        return Complex(
            self.real*other.real-self.imag*other.imag,
            self.imag*other.real+self.real*other.imag
        )

    def __eq__(self, other):
        return self.real == other.real and self.imag == other.imag

    def __str__(self):
        if self.real == 0 and self.imag == 0:
            return str(0)

        if self.real == 0:
            if self.imag >= 0:
                return '{}i'.format(self.imag)
            else:
                return '-{}i'.format(self.imag)

        if self.imag == 0:
            return str(self.real)

        sign = ''
        if self.imag >= 0:
            sign = '+'
        else:
            sign = '-'

        return '{}{}{}i'.format(self.real, sign, abs(self.imag))

    __repr__ = __str__ # __reprs__ is called to print objects inside lists.
