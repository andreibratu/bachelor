t = [0 10 20 30 40 60 80 100];
p = [0.0061 0.0123 0.0234 0.0424 0.0738 0.1992 0.4736 1.0133];

real_v = bary_lagn(t, p, 45)

printf('Degree 2\n');
X_2 = polyfit(t, p, 2);
Y_2 = polyval(X_2, t);
E_2 = (real_v - polyval(X_2, 45)) .^ 2

printf('Degree 5\n');
X_5 = polyfit(t, p, 5);
Y_5 = polyval(X_5, t);
E_5 = (real_v - polyval(X_5, 45)) .^ 2

hold on
scatter(t, p, 'g', 'filled')
plot(t, Y_2, 'r-')
plot(t, Y_5, 'b-')
title('5th degree approximates the distribution best', 'fontsize', 16)
legend('Data points', '2nd degree fitting', '5th degree fitting')
