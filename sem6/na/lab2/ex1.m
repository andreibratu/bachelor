1;

function result = LP( n, x )
  if (n == 0)
      result = 1;
  elseif (n == 1)
    result = x;
  else
    result = (2*n+1)/(n+1)*x.*LP(n-1, x)-n/(n+1).*LP(n-2, x);
  endif
endfunction


x=0:0.01:1
for n = 1:4
  l = LP(n, x);
  subplot(2, 2, n);
  plot(x, l)
end  