clear all
clc
close all
alpha=0.35;

%Normal Distribution
mu=0;
sig=1;


x=mu-3*sig-0.1:0.01:mu+3*sig+0.1;
y=pdf('norm',x,mu,sig);
z=cdf('norm',x,mu,sig);
zalpha=icdf('norm',alpha,mu,sig);
fzalpha=pdf('norm',zalpha,mu,sig);
Fzalpha=cdf('norm',zalpha,mu,sig);

figure(1)
hold on
box on
axis([min(x)-0.05 max(x)+0.05 min(z)-0.05 max(z)+0.05])
line([min(x)-0.05, max(x)+0.05],[0,0],'Color','k','LineWidth',1.5)
line([min(x), max(x)],[alpha,alpha],'Color','b','LineWidth',1.5)
line([zalpha, zalpha],[0,Fzalpha],'Color','b','LineWidth',1.5,'LineStyle',':')
plot(x,z,'Color','r','LineWidth',2)
text(zalpha+0.02,0.025,'$z_{\alpha}$','Interpreter','Latex','FontSize',15)
text(zalpha-0.35,alpha+0.025,'$\alpha$','Interpreter','Latex','FontSize',15)
title(['CDF: $\alpha=$',num2str(alpha),'  $z_{\alpha}=$',num2str(zalpha)],'Interpreter','Latex','Fontsize',12)
xlabel(['Quantile of order ', num2str(alpha)])
ylabel(['Normal Distribution $\mu=$',num2str(mu),' $\sigma=$',num2str(sig)],'Interpreter','Latex','Fontsize',12)

figure(2)
hold on
box on
axis([min(x)-0.005 max(x)+0.005 min(y)-0.005 max(y)+0.005])
line([min(x)-0.05, max(x)+0.05],[0,0],'Color','k','LineWidth',1.5)
plot(x,y,'Color','r','LineWidth',2)
line([zalpha, zalpha],[0,fzalpha],'Color','k','LineWidth',2.5,'LineStyle',':')
title(['PDF: $\alpha=$',num2str(alpha),'  $z_{\alpha}=$',num2str(zalpha)],'Interpreter','Latex','Fontsize',12)
text(zalpha+0.02,0.0065,'$z_{\alpha}$','Interpreter','Latex','FontSize',15)
vectzalpha=min(x):0.01:zalpha;
fvect=pdf('norm',vectzalpha,mu,sig);
fill([min(x),vectzalpha,zalpha],[0,fvect,0],'b')
xlabel(['Quantile of order ', num2str(alpha)])
ylabel(['Normal Distribution $\mu=$',num2str(mu),' $\sigma=$',num2str(sig)],'Interpreter','Latex','Fontsize',12)

%Student Distribution
n=8;
x=mu-3*sig-0.1:0.01:mu+3*sig+0.1;
y=pdf('t',x,n);
z=cdf('t',x,n);
zalpha=icdf('t',alpha,n);
fzalpha=pdf('t',zalpha,n);
Fzalpha=cdf('t',zalpha,n);

figure(3)
hold on
box on
axis([min(x)-0.05 max(x)+0.05 min(z)-0.05 max(z)+0.05])
line([min(x)-0.05, max(x)+0.05],[0,0],'Color','k','LineWidth',1.5)
line([min(x), max(x)],[alpha,alpha],'Color','b','LineWidth',1.5)
line([zalpha, zalpha],[0,Fzalpha],'Color','b','LineWidth',1.5,'LineStyle',':')
plot(x,z,'Color','r','LineWidth',2)
text(zalpha+0.02,0.025,'$z_{\alpha}$','Interpreter','Latex','FontSize',15)
text(zalpha-0.35,alpha+0.025,'$\alpha$','Interpreter','Latex','FontSize',15)
title(['CDF: $\alpha=$',num2str(alpha),'  $z_{\alpha}=$',num2str(zalpha)],'Interpreter','Latex','Fontsize',12)
xlabel(['Quantile of order ', num2str(alpha)])
ylabel(['Student Distribution n=',num2str(n)],'Fontsize',12)

figure(4)
hold on
box on
axis([min(x)-0.005 max(x)+0.005 min(y)-0.005 max(y)+0.005])
line([min(x)-0.05, max(x)+0.05],[0,0],'Color','k','LineWidth',1.5)
plot(x,y,'Color','r','LineWidth',2)
line([zalpha, zalpha],[0,fzalpha],'Color','k','LineWidth',2.5,'LineStyle',':')
title(['PDF: $\alpha=$',num2str(alpha),'  $z_{\alpha}=$',num2str(zalpha)],'Interpreter','Latex','Fontsize',12)
text(zalpha+0.032,0.0075,'$z_{\alpha}$','Interpreter','Latex','FontSize',15)
vectzalpha=min(x):0.01:zalpha;
fvect=pdf('t',vectzalpha,n);
fill([min(x),vectzalpha,zalpha],[0,fvect,0],'b')
xlabel(['Quantile of order ', num2str(alpha)])
ylabel(['Student Distribution n=',num2str(n)])





