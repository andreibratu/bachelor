f = @(x) (x - 2)^2 - log(x);

e = 0.0001;
N = 100;
a = 1;
b = 2;

false_position(f, a, b, e)
bisection(f, a, b, e)
