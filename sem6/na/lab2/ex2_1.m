1;

function result = CP(n, t)
    result = cos(n .* acos(t))
endfunction

x=-1:0.01:1
for n = 1:3
  l = CP(n, x);
  subplot(2, 2, n);
  plot(x, l)
end