function S = simpson(f, a, b)
  S = (b - a) ./ 6 .* (f(a) + 4 .* f((a + b) / 2) + f(b));
end