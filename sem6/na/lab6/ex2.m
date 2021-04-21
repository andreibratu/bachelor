%2
[x,fx] = ginput(5)
t = 0:0.01:1;
s = spline(x, fx, t);
plot(x, fx, 'o')
hold on
plot(t, s, 'r')