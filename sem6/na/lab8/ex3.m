r = 110; p = 75;
a = 0; b = 2*pi;

f = @(x) sqrt(1-(p/r)^2*sin(x));

n1 = 2
int_trapez1 = repeated_trapezium(a,b,f,n1);
h1 = 60*r/(r*r - p*p) * int_trapez1

n2 = 3
int_trapez2 = repeated_trapezium(a,b,f,n2);
h2 = 60*r/(r*r - p*p) * int_trapez2