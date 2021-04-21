%a)
X = [0 pi/2 pi 3.*pi/2 2.*pi];
x = 0:0.001:2*pi;
f = @(x) sin(x);
fx = f(x);

spline(X, f(X), pi/4)
spline(X, [1 f(X) 1], pi/4)

plot(x,fx,'r')
hold on

%b)
s = spline (X, f(X), x);
cs = spline (X, [1 f(X) 1], x);

plot(x, s, 'b')
plot(x, cs, 'g')
plot(X, f(X), 'o')
