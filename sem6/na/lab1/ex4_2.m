t=0:0.01:10*pi;

a=input('Give value for a: ');
b=input('Give value for b: ');

x=(a+b)*cos(t)-b*cos((a/b+1)*t);
y=(a+b)*sin(t)-b*sin((a/b+1)*t);

plot(x,y)