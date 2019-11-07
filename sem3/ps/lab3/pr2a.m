% Normal approximation of the binomial distribution: For moderate values of
% p (0.05 ? p ? 0.95) and large values of n (n ? ?),
% Bino(n, p) ? Norm

clc
clear all
close all

n = 30;
p = 0.65;
k = 0 : n;

y = pdf('bino', k, n, p)
figure(1)
hold on
bar(k, y)

m = n*p;
siq = sqrt(n*p*(1-p));
x = (m - 3 * sig) : 0.01 : (m + 3 * sig);
z = pdf('Normal', x, m, sig);

plot(x, z, 'color', 'r', 'LineWidth', 2);