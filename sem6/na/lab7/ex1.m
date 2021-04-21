x = 1:7;
f = [13, 15, 20, 14, 15, 13, 10];

A = [sum(x.^2), sum(x); sum(x), length(x)];
B = [sum(x .* f); sum(f)];

X = linsolve(A, B)';
fprintf('phi(x)=%fx + %f\n', X);

polyval(X, 8)

X_alt = polyfit(x, f, 1);
fprintf('phi_alt(x)=%fx + %f\n', X_alt);
polyval(X_alt, 8)

E_min=sum((f-polyval(X_alt, x)).^2)

plot(x, f, 'bo');
hold on
xp = 1:0.01:8;
plot(xp, polyval(X_alt, xp), 'r-');