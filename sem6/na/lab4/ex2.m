 %a) 
x = [1 2 3 4 5];
f = [22 23 25 30 28];
xx= [2.5];
s = Newton(x,f,xx);

display(s);

%b) plot(x,f(x)) and plot Newton interpolation polynomial
plot(x,f,'r')
hold on
g = [0:0.1:6];
plot(g,Newton(x,f,g),'b')


