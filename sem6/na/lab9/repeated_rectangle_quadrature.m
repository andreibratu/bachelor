function rez = repeated_rectangle_quadrature(f, a, b, n)
  x = linspace(a, b, n);
  rez = (b - a) / n * sum(f(x(1:n)));
end