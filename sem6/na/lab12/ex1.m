f = @(x) cos(x);
fd = @(x) -sin(x);

x = newton(f, fd, pi / 4, 100, 0.0001);