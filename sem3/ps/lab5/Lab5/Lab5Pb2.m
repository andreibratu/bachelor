
clc
clear all
close all

A=[7 7 4 5 9 9
4 12 8 1 8 7
3 13 2 1 17 7
12 5 6 2 1 13
14 10 2 4 9 11
3 5 12 6 10 7];


x=A(:)';
nx=length(x);
alpha1=0.05;%significance level-first case
alpha2=0.01;%significance level -second case

%a)

sigma=5;
med_s=mean(x); %sample mean
ca=sigma/sqrt(nx);
inta_1=icdf('norm',1-alpha1/2,0,1)*ca;
inta_2=icdf('norm',1-alpha2/2,0,1)*ca;

la1=med_s-inta_1;
ra1=med_s+inta_1;
la2=med_s-inta_2;
ra2=med_s+inta_2;

fprintf('a)\n')
fprintf('Confidence interval for the mean (standard deviation=%f and sample mean=%f)\n',sigma,med_s)
fprintf('Confidence level %.2f: (%f,%f)\n',1-alpha1,la1,ra1)
fprintf('Confidence level %.2f: (%f,%f)\n',1-alpha2,la2,ra2)

%b
sigma_s=std(x);
cb=sigma_s/sqrt(nx);%standard error of the mean
fprintf('b)\n')
intb_1=icdf('t',1-alpha1/2,nx-1)*cb;
intb_2=icdf('t',1-alpha2/2,nx-1)*cb;


lb1=med_s-intb_1;
rb1=med_s+intb_1;
lb2=med_s-intb_2;
rb2=med_s+intb_2;


fprintf('Confidence interval for the mean (sample standard deviation=%f and sample mean=%f)\n',sigma_s,med_s)
fprintf('Confidence level %.2f: (%f,%f)\n',1-alpha1,lb1,rb1)
fprintf('Confidence level %.2f: (%f,%f)\n',1-alpha2,lb2,rb2)


% c)
sigma_sqr = var(x);
cc=(nx-1)*sigma_sqr;

ql1 = icdf('chi2',1-alpha1/2,nx-1);
qr1 = icdf('chi2',alpha1/2,nx-1);
lc1 =cc/ql1; 
rc1 =cc/qr1;

ql2 = icdf('chi2',1-alpha2/2,nx-1);
qr2 = icdf('chi2',alpha2/2,nx-1);
lc2 =cc/ql2; 
rc2 =cc/qr2;




fprintf('c)\n')
fprintf('Confidence interval for the variance (sample variance=%f and sample mean=%f)\n',sigma_sqr,med_s)
fprintf('Confidence level %.2f: (%f,%f)\n',1-alpha1,lc1,rc1)
fprintf('Confidence level %.2f: (%f,%f)\n',1-alpha2,lc2,rc2)


