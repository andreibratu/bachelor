f = @(x) 100 ./ (x.^2) .* sin(10 ./ x);

x = linspace(1,3,100);
y = f(x);

eps = 10^(-4);
a = 1;
b = 3;

% plot the graph
plot(x, y);

% compute with adaptive quadrature
fprintf('Adaptive quadrature for Simpson formula: %.6f\n', adaptiveQuadrature(f, a, b, eps));

% compute with repeated simpson
fprintf('Repeated Simpson for %d: %.6f\n', 50, repeated_simpson(f, a, b, 50));
fprintf('Repeated Simpson for %d: %.6f\n', 100, repeated_simpson(f, a, b, 100));
