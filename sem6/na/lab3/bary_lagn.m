function L = bary_lagn(x, y, x_hat)
  m = length(x);
  P = zeros(1,m);
  N = length(x_hat);
  L = zeros(1,N);
  for j = 1:N
    s1 = 0;
    s2 = 0;
    for i = 1:m
      P(i) = ai_test(i,x);
      s1 = s1 + P(i)*y(i)/(x_hat(j)-x(i));
      s2 = s2 + P(i)/(x_hat(j)-x(i));
    endfor
  L(j) = s1/s2;
  endfor
endfunction