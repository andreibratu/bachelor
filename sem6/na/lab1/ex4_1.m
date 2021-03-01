% IV.1

x=0:0.01:1;

y1=exp(10.*x.*(x-1)).*sin(12.*pi.*x);
y2=3.*exp(5.*x.^2-1).*cos(12.*pi.*x);

plot(x,y1)
hold on
plot(x, y2, 'r')