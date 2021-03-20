x = linspace(0, 6, 13);
f = @(x) exp(sin(x));
fx = f(x);

%plot interpolation points
plot(x,f(x),'*')
hold on;

%plot the function f
plot(x,fx,'r')
hold on;

%plot the Newton interpolation
x2 = linspace(0, 6, 100);
rez = Newton(x, fx, x2);
plot(x2, rez, 'b')