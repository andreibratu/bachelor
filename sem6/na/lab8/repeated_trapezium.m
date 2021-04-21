function res = repeated_trapezium(a, b, f, n)
  h = (b-a)/n;
  i = a:h:b; % x_k values
  res = h / 2 * (f( i(1)) + 2 * sum(f(i(2:end - 1))) + f(i(end)));
end