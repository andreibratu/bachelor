function A = repeated_simpson(f, a, b, n)
  h = (b - a) / n;
  x = a:h:b;
  A = h ./ 6 .* ( f(a) + f(b) + 4 .* sum(f((x(2:n + 1) + x(1:n)) ./ 2)) + 2 .* sum(f(x(2:n))));
end