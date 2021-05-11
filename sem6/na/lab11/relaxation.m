function z = relaxation(A, b, eps_val, omega_val)
  [m, n] = size(A);
  x = A \ b;
  
  x_old = zeros(m, 1);
  x_new = x_old;
  it_c = 0;
  
  while it_c < 100
    
    for i = 1 : m
      s = A(i, i+1:n) * x_old(i+1:n, :);
      s2 = A(i, 1:i-1) * x_new(1:i-1, :);
      
      x_new(i) = 1 / A(i, i) * (b(i) - s - s2)
    endfor
    
    if abs(x_new - x_old) < eps_val
      break
    endif
    
    x_old = x_new;
    it_c += 1;
  endwhile
  
  z = [x_new, it_c];
endfunction  