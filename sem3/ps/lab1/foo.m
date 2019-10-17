close all
x1 = -4 : 0.01 : 4;
x2 = 0 : 0.01 : 2*pi;

f1 = abs(x1);
f2 = sin(x2);

hold on
fig1 = plot(x1, f1, [1,0,0])
fig2 = plot(x2, f2, [0,1,0])