clc
clear all
close all

N = 10000;

y = rand(1, N);
z = randn(1, N);

figure(1)
hold on

hist(y, 20);
title('RAND')


figure(2)
hist(z, 20);
title('RANDN')

a = 0;
b = 2;
w = a + (b - a) * y;

figure(3)
hold on
hist(w, 20);
title('Shifted RAND')

% NameRND

u = normrnd(0, 2, 1, N);
figure(4);
hold on
hist(u, 20)

v = binornd(3, 0.5, 1, N)
figure(5);
hold on
hist(v, 20);