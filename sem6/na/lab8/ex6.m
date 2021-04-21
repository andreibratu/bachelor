val = erf(0.5); 
e = exp(1);

a = 0; b = 0.5;
f = @(x) e .^ (-x .^2);

% n=4
n1 = 4;
approx1 = 2/sqrt(pi)*simpson(f, a, b, n1)
error1 = abs(approx1 - val)

% n=10
n2 = 10;
approx2 = 2/sqrt(pi)*simpson(f, a, b, n2)
error2 = abs(approx2 - val)