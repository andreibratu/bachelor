clc
clear all
close all

% var(x), std(x), std(x, 0), std(x, 1), cov(X, Y)
% Check normalise by n and normalise by (n-1)

X=[20 21 22 23 24 25 26 27
   2 1 3 6 5 9 2 2];

Y=[75 76 77 78 79 80 81 82
  3 2 2 5 8 8 1 1];

Xnew=Reform_vect(X)
Ynew=Reform_vect(Y);

% a)
fprintf('The means of X and Y: %f and % f \n',mean(Xnew),mean(Ynew))
%b)
fprintf('The variances of X and Y: %f and %f\n',var(Xnew,1),var(Ynew,1))
%c)
fprintf('Covariance matrix\n')
C=cov(Xnew,Ynew,1)
fprintf('The covariance: %f\n',C(1,2))
%d)
fprintf('Correlation coefficients matrix\n')
R=corrcoef(Xnew,Ynew)
fprintf('The correlation coefficient: %f\n',R(1,2))

figure(1)
hold on
box on
plot(Xnew,Ynew,'r*')
xlabel('X')
ylabel('Y')
