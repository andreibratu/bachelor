function r = repeated_trapezium(a, b, f, n)
  h = (b-a)/n;
  xi = a:h:b;
  r = h/2*(f(xi(1))+2*sum(f(xi(2:end-1)))+f(xi(end)));
end