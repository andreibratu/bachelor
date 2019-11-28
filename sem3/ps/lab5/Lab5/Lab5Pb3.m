clear all
clc
close all

x=[22.4, 21.7, 24.5, 23.4, 21.6, 23.3, 22.4, 21.6, 24.8, 20.0];

y=[17.7, 14.8, 19.6, 19.6,12.1,14.8,15.4, 12.6,14.0, 12.2];

n1=length(x);
n2=length(y);
mx=mean(x);
my=mean(y);
mdif=mx-my;
sxsqr=var(x);
sysqr=var(y);
rapvar=sxsqr/sysqr;

alpha1=0.05;%significance level-first case
alpha2=0.01;%significance level -second case

%a)
sp=sqrt(((n1-1)*sxsqr+(n2-1)*sysqr)/(n1+n2-2));
qa1=icdf('t',1-alpha1/2,n1+n2-2);
qa2=icdf('t',1-alpha2/2,n1+n2-2);
ca=sqrt(1/n1+1/n2);

la1=mdif-qa1*sp*ca;
ra1=mdif+qa1*sp*ca;
la2=mdif-qa2*sp*ca;
ra2=mdif+qa2*sp*ca;

fprintf('a)\n')
fprintf('Confidence interval for difference of two population means, variances equal,(sample diff. means=%f)\n',mdif)
fprintf('Confidence level %.2f: (%f,%f)\n',1-alpha1,la1,ra1)
fprintf('Confidence level %.2f: (%f,%f)\n',1-alpha2,la2,ra2)

%b)
c=(sxsqr/n1)/(sxsqr/n1+sysqr/n2);
n=1/(c^2/(n1-1)+(1-c)^2/(n2-1));
qb1=icdf('t',1-alpha1/2,n);
qb2=icdf('t',1-alpha2/2,n);
cb=sqrt(sxsqr/n1+sysqr/n2);

lb1=mdif-qb1*cb;
rb1=mdif+qb1*cb;
lb2=mdif-qb2*cb;
rb2=mdif+qb2*cb;

fprintf('b)\n')
fprintf('Confidence interval for difference of two population means, variances not equal,(sample diff. means=%f)\n',mdif)
fprintf('Confidence level %.2f: (%f,%f)\n',1-alpha1,lb1,rb1)
fprintf('Confidence level %.2f: (%f,%f)\n',1-alpha2,lb2,rb2)

%c)

qcl1=icdf('f',1-alpha1/2,n1-1,n2-1);
qcr1=icdf('f',alpha1/2,n1-1,n2-1);
qcl2=icdf('f',1-alpha2/2,n1-1,n2-1);
qcr2=icdf('f',alpha2/2,n1-1,n2-1);

lc1=rapvar/qcl1;
rc1=rapvar/qcr1;
lc2=rapvar/qcl2;
rc2=rapvar/qcr2;


fprintf('c)\n')
fprintf('Confidence interval for ratio of variances (sample ratio variances=%f)\n',rapvar)
fprintf('Confidence level %.2f: (%f,%f)\n',1-alpha1,lc1,rc1)
fprintf('Confidence level %.2f: (%f,%f)\n',1-alpha2,lc2,rc2)


