1;

function result = TP(n, t, t0)
  sum = 0;
  for k = 0:n
    sum += (((t - t0) .^ k) ./ factorial(k)) .* exp(t0);
  endfor
  result = sum;
endfunction


w = -1:0.1:3;
w0 = 0;
for n=1:6
  result = TP(n, w, w0)
  subplot(3, 3, n)
  plot(w0, result)
endfor  
