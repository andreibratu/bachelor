pkg load statistics;

m=1; s=2; n=10;

%a

% F(a) = P(x <= a) = P(x < a)

% P(x <= 0)
a1 = cdf('Normal', 0, m, s)
a2 = cdf('t', 0, n)

% P(x >= 0)
a3 = 1 - a1
a4 = 1 - a2

printf('Normal\n')
fprintf('a)P(X<=0)=%f\n', a1)
fprintf('a)P(X>=0)=%f\n', a3)

fprintf('Student\n')
fprintf('a)P(X<=0)=%f\n', a2)
fprintf('a)P(X>=0)=%f\n', a4)

% b
% P(a <= x <= b) = F(b) - F(a)

% P(?1 ? x ? 1)
b1 = cdf('Normal', 1, m, s) - cdf('Normal', -1, m, s)
b2 = cdf('t', 1, n) - cdf('t', -1, n)

% P( x <= -1 or x >= 1) <=> 1 - P ( -1 < x < 1)
b3 = 1 - b1
b4 = 1 - b2

printf('Normal\n')
fprintf('b)P(-1<=X<=1)=%f\n', b1)
fprintf('a)P(x<=-1 or x>=1)=%f\n', b3)

fprintf('Student\n')
fprintf('b)P(-1<=X<=1)=%f\n', b2)
fprintf('a)P(x<=-1 or x>=1)=%f\n', b4)


% c
% The value x? such that P(X < x?) = ?, for ? ? (0, 1) (x? is called the 
% quantile of order ?);
% P(X < Xa) = F(Xa) = a => Xa = ICDF(a)
alpha = 0.6
c1 = icdf('Normal', alpha, m, s)
c2 = icdf('t', alpha, n)

fprintf('Normal, quantil of order %f is %f\n', alpha, c1)
fprintf('Student, quantil of order %f is %f\n', alpha, c2)


% d
% the value x? such that P(X > x?) = ?, for ? ? (0, 1) (x? is the 
% quantile of order 1 ? ?).
beta = 0.3
d1 = icdf('Normal', 1-beta, m, s)
d2 = icdf('t', 1-beta, n)

fprintf('Normal, quantil of order 1-%f is %f\n', beta, d1)
fprintf('Student, quantil of order 1-%f is %f\n', beta, d2)