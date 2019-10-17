x = -3 : 0.01 : 3;
m = 0;
s = 1;

f = 1/sqrt(2*pi*s) * exp( -(x-m) .^ 2 / (2*s));
figure(1);
hold on
plot(x, f, 'color', 'k', 'LineWidth', 3, 'LineStyle', ':')

m1 = -1;
m2 = 1;
f1 = 1/sqrt(2*pi*s) * exp( -(x-m1) .^ 2 / (2*s));
f2 = 1/sqrt(2*pi*s) * exp( -(x-m2) .^ 2 / (2*s));

figure(2);
hold on
title('Gauss');
xlabel('x');
ylabel('f(x)');
plot(x, f, 'color', 'b')
plot(x, f1, 'color', 'r')
plot(x, f2, 'color', 'g')
legend('m=0', 'm=-1', 'm=1');

% this is a comment

close all

s1 = 2;
F = 1/sqrt(2*pi*s) * exp( -(x-m) .^ 2 / (2*s1));

figure(3);
hold on
title('Gauss');
xlabel('x');
ylabel('f(x)');
plot(x, f, 'r')
plot(x, F, 'k')

% m value decides the center of the bell
% s controls the width of the bell proportionally -> more belong to average