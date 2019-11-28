clc
clear all
close all

X=[22.7 22.8 22.9 23.0 23.1 23.2 23.3 23.4
    1 3 7 4 6 7 5 2];
sigma=sqrt(0.35);

Xnew=Reform_vect(X);

n=length(Xnew);
alpha1=0.05;%nivel de semnificatie-primul caz/probabilitate de risc
alpha2=0.01;%nivel de semnificatie-cazul doi/probabilitate de risc

med_s=mean(Xnew); %media esantionului

ca=sigma/sqrt(n);
q_1=icdf('norm',1-alpha1/2,0,1);%cuantila de ordin alpha-primul caz
q_2=icdf('norm',1-alpha2/2,0,1);%cuantila de ordin alpha-cazul doi

l_1=q_1*ca;
l_2=q_2*ca;

la1=med_s-l_1;
ra1=med_s+l_1;
la2=med_s-l_2;
ra2=med_s+l_2;


fprintf('Interval de incredere pentru medie (deviatia standard= %f si media esantionului= %f)\n',sigma,med_s)
fprintf('Probabilitate de incredere %.2f: (%f,%f)\n',1-alpha1,la1,ra1)
fprintf('Probabilitate de incredere %.2f: (%f,%f)\n',1-alpha2,la2,ra2)
