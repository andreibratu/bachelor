f = @(x) x^3 - x^2 - 1;

x = secant(f, 1, 2, 100, 1e-4);
