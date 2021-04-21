a=1.4; b=2;
c=1; d=1.5;

f = @(x,y) log(x + 2 * y);

%trapezium formula for double integrals
res = trapezium_double(a,b,c,d,f)