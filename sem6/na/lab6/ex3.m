x = 0: pi/4 : 2 * pi;
f = @(x) cos(x);
i = 0:0.1:6;

hold on
plot(i,f(i));
plot(i,interp1(x,f(x),i));
legend('function','spline');
