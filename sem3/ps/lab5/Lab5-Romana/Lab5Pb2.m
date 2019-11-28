clc
clear all
close all

X=[2.7 2.8 2.9 3.0 3.1 3.2 3.3
    1 2 5 3 5 4 2];



Xnew=Reform_vect(X);

n=length(Xnew);
alpha1=0.02;%nivel de semnificatie-primul caz/probabilitate de risc
alpha2=0.01;%nivel de semnificatie-cazul doi/probabilitate de risc

med_s=mean(Xnew); %media esantionului

sigma_s=std(Xnew);%abaterea standard a esantionului
ca=sigma_s/sqrt(n);

q_1=icdf('t',1-alpha1/2,n-1);
q_2=icdf('t',1-alpha2/2,n-1);

l_1=q_1*ca;
l_2=q_2*ca;

la1=med_s-l_1;
ra1=med_s+l_1;
la2=med_s-l_2;
ra2=med_s+l_2;


fprintf('Interval de incredere pentru medie (abaterea standard a esantionului= %f si media esantionului= %f)\n',sigma_s,med_s)
fprintf('Probabilitate de incredere %.2f: (%f,%f)\n',1-alpha1,la1,ra1)
fprintf('Probabilitate de incredere %.2f: (%f,%f)\n',1-alpha2,la2,ra2)