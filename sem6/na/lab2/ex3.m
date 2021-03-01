1;

pkg load symbolic;

function result = foobar (q)
  result = exp(q)
endfunction


function result = TP(n, t, t0, f)
  sum = 0;
  syms x;
  df = f(x);
  for k = 0:n
    sum += (((t - t0) .^ k) / factorial(k)) .* df(t0);
    df = diff(df, x);
  endfor
  result = sum;
endfunction


w = -1:0.1:3;
w0 = 0;
for n=1:6
  result = TP(n, w, w0, @foobar)
  subplot(3, 3, n)
  plot(w0, result)
endfor  
