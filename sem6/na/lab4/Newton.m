function N = Newton(x,f,xx)
  n = length(x)-1;

  % divided differences table
  m = divided_diff_table(x, f);

  % approximation of function f at points in x using Newton interpolation 
  % polynomial with the nodes from vector x
  lx=length(xx);
  p=ones(1,lx);
  s=m(1,2)*ones(1,lx);
  for j=1:lx
    for i=1:n
      p(j) = p(j) * (xx(j) - x(i));
      s(j) = s(j) + p(j) * m(1,i+2);
    endfor
  endfor
  N=s;
 endfunction