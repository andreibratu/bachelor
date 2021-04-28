f = @(x) 2./(1 + x.^2);
a = 0;
b  = 1;
eps = 10^(-4);

% Trapezium
q0_t = (1 / 2) * (f(a) + f(b));
fprintf('Romberg - trapezium: %.6f\n', romberg_trapezium(f, q0_t, 1, a, b, eps));

% Aitken
n = 1;
[romberg_a, err] = romberg_aitken(a, b, f, n);

while abs(err) > eps
  n = n + 1;
  [romberg_a, err] = romberg_aitken(a, b, f, n);
end
fprintf('Romberg - aitken: %.6f\n', romberg_a);