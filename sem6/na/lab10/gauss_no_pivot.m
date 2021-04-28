function res = gauss_no_pivot(A, b)
  n = size(A, 1)
  x = zeros(n, 1)
  for k = 1: (n-1)
    for i = (k+1):n
      A[i, k] = A[i, k] / A[k, k]
      for j = (k+1):n
        A[i, j] -= A[i, k] * A[k, j]
      endfor
    endfor
  endfor
  
  for k = 1: (n-1)
    for i = (k+1):n
      b[i] -= A[i, k] * b[k]
    endfor
  endfor
  
  for i = n:-1:1
    s = b[i]
    for j = (i+1):n
      s -= A[i, j] * x[j]
    endfor
    x[i] = s / A[i, i]
  endfor
endfunction
