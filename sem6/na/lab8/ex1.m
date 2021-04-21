a=0; b=1;
f = @(x) 2./(1+x.^2);

int = integral(f,a,b) 

%a)
int_trapez = (b-a)/2*(f(a)+f(b)) 

%c)
int_simpsons = (b-a)/6*(f(a)+4*f((b-a)/2) + f(b))

 
%b)
%the function
fplot(f,[a,b]);
hold on
%the trapezium with the vertices (0; 0);(0; f(0));(1; f(1)) and (1; 0):
fill([0,0,1,1],[0,f(0),f(1),0],'g');

