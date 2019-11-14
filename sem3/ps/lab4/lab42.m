clc
clear all
close all

pkg load statistics

s = 10000;
p = 0.35;

% Bernoulli simulation

for i = 1:s
  x(i) = rand < p;
endfor

fr_ber = hist(x, 2) / s


% Binomial simulation

x = zeros(1, s);

n = 3;
for i = 1:s
  u = rand(1, n);
  x(i) = sum(u < p);
endfor

unique(x);

fr_bin = hist(x, n+1)
p_teor = pdf('bino', 0, n, p)


% Geometric simulation

x = zeros(1, n)
for i = 1,n
  while rand >= p
    x(i) = x(i) + 1;
  endwhile
endfor

ux = unique(x);
fr_geo = hist(x, length(ux)) / s;
geo_teor = pdf('geo', ux, p);

[ux', fr_geo', geo_teor']


% Pascal simulation

y = zeros(1, s);
for i = 1:s
  x = zeros(1, n);
  for j = 1:n
    while rand >= p
      x(j) = x(j) + 1;
    endwhile
  endfor
  y(i) = sum(x);
endfor

uy = unique(y);
fr_pascal = hist(y, length(uy)) / s
pasc_teor = pdf('nbin', uy, n, p)

[uy', fr_pascal', pasc_teor']

