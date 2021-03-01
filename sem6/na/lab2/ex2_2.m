1;

function result = CP2(n, x)
  if n == 0
    result = 1
  elseif n == 1
    result = x
  else
    result = 2 .* x .* CP2(n-1, x) - CP2(n-2, x)
  endif
endfunction

n = input('Input n: ')

# Quick hack to determine subplots layout. We want sqrt x sqrt
sqrt = 1
while sqrt * sqrt < n
  sqrt += 1
endwhile  

x=-1:0.1:1
for nn = 1:n
  l = CP2(nn, x);
  subplot(sqrt, sqrt, nn);
  plot(x, l)
end      