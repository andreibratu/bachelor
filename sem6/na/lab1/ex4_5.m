x = 0:1:50;
f = (mod(x, 2) == 0).* (x/2) + (mod(x,2) == 1).* (x*3 + 1);

scatter(x, f, 'filled')