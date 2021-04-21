hold on

axis([0, 5, 0, 5])

[x, y] = ginput(10);

scatter(x, y, 'b')

X = polyfit(x, y, 2)
x_t = 0:0.05:5;
y_t = polyval(X, x_t);

plot(x_t, y_t, 'r-')

scatter(x, polyval(X, x), 'g', 'filled')
title('Best 2 degree fitting', 'fontsize', 16)

legend('User Input', 'Degree 2 fitting', 'Degree 2 predictions')

