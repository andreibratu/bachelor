funct = @(x) sin(2 .* x);
deriv = @(x) 2 .* cos(2 .* x);

x = linspace(-5, 5, 15);

y = funct(x); dy = deriv(x);

x_hat = [-5:0.1:5]; [y_hat] = HermitePol(x, y, dy, x_hat);


x_plot = [-5:0.1:5];
y_plot = funct(x_plot);

figure(1); hold on;

plot(x_hat, y_hat);
plot(x_plot, y_plot);