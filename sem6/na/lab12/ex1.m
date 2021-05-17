f = @(x) cos(x) - x;
fd = @(x) -sin(x) - 1;

x = newton(f, fd, pi / 4, 100, 0.0001);
