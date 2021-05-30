f = @(e) e - 0.8 * sin(e) - (2 * pi) / 10;
fd = @(e) 1 - 0.8 * cos(e);

x = newton(f, fd, 1, 6, 1e-20);
