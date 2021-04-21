a = 0; b = pi;
f = @(x) 1 ./ (4+sin(20 .*x));
n1 = 10; n2 = 30;

res1 = simpson(f, a, b, n1)
res2 = simpson(f, a, b, n2)