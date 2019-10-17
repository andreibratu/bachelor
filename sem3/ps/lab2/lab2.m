pkg load statistics;

clear all;
close all;

n = 3;
p = 0.5;
k = 0:n;

% a
% pdf is the distribution of having exactly x successes from n trials
P = pdf('bino', k, n, p);
% binopdf(k, n, p)
figure(1)
hold on
plot(k, P, 'b*')

% b
% cdf is equivalent but cumulative
figure(2)
F = cdf('bino', k, n, p);
plot(k, F, 'r*')

%c
% P(x=0)
print(pdf('bino', 0, n, p))
% P(x!=1)
print(1 - pdf('bino', 1, n, p))

%d
% P(x<=2)
print(cdf('bino', 2, n, p))
% P(x<2)
print(cdf('bino', 1, n, p))

%e
% P(x>=1)
print(1-cdf('bino', 0, n, p))
% P(x>1)
print()

%f
% 10 experiments, each flipping coin three times
N = 100000;
A = rand(3, N);
x = sum(A < 0.5);
v(1) = sum(x == 0);
v(2) = sum(x == 1);
v(3) = sum(x == 2);
v(4) = sum(x == 3);

figure(1)
plot(k, v/N, 'ro')