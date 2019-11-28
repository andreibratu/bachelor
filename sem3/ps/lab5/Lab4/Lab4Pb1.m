clear all
clc
close all

N=10000;

y=rand(1,N);

figure(1)
hold on
hist(y,20)
title('RAND')

z=randn(1,N);

figure(2)
hold on
hist(z,20)
title('RANDN')

a=0;b=2;
w=a+(b-a)*y;

figure(3)
hold on
hist(w,20)
title(['RAND [',num2str(a),',',num2str(b),']'])

med=0; sig=2;
u=normrnd(med,sig,1,N);

figure(4)
hold on
hist(u,20)
title(['RANDN  $\mu$=',num2str(med),'\quad$\sigma$=',num2str(sig)],'Interpreter','Latex')

