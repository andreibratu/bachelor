function [y, err] = romberg_aitken(a,b,f,n)
  y=zeros(n);
  for k=1:n
      y(k,1)=repeated_trapezium(a, b, f, k);
      close all
  end
  nn=0;
  for k=2:n
      for jj=2:n
          if jj+nn>n
              break
          end
          y(jj+nn,k) = (4^(k-1)*y(jj+nn,k-1)-y(jj-1+nn,k-1))/(4^(k-1)-1);
      end
      nn=nn+1;
  end

if n > 1
    err = y(n, n) - y(n-1, n-1);
else
    err = 1000;
end

y = y(n, n);

end