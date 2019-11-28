clc
clear all
close all

Xnew=[4.21, 4.03, 3.99, 4.05, 3.89, 3.98, 4.01, 3.92, 4.23, 3.85, 4.20];

n=length(Xnew);
alpha1=0.05;%nivel de semnificatie-primul caz/probabilitate de risc
alpha2=0.01;%nivel de semnificatie-cazul doi/probabilitate de risc

med_s=mean(Xnew); %media esantionului

sigma_sqr=var(Xnew);%abaterea standard a esantionului


cc=(n-1)*sigma_sqr;

ql1 = icdf('chi2',1-alpha1/2,n-1);
qr1 = icdf('chi2',alpha1/2,n-1);
lc1 =cc/ql1; 
rc1 =cc/qr1;

ql2 = icdf('chi2',1-alpha2/2,n-1);
qr2 = icdf('chi2',alpha2/2,n-1);
lc2 =cc/ql2; 
rc2 =cc/qr2;


fprintf('Interval de incredere pentru varianta (varianta esantionului=%f si media esantionului=%f)\n',sigma_sqr,med_s)
fprintf('Probabilitate de incredere %.2f: (%f,%f)\n',1-alpha1,lc1,rc1)
fprintf('Probabilitate de incredere %.2f: (%f,%f)\n',1-alpha2,lc2,rc2)
