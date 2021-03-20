1;

function result = calc_diff_table (n, a1, h)
  
  f = @(x) sqrt(5*x.^2+1);
  
  z = zeros(n,1);
  z(1) = a1;
  for i=2:n
    z(i) = z(i-1) + h;
  endfor
  
  f_of_z = f(z);
  z = [z f_of_z];
  
  for i=1:n-1
    z2 = zeros(n,1);
    for j=1:n-i
      z2(j) = z(j+1, end) - z(j, end);
    endfor
    z = [z z2];
  endfor
  
  result = z
endfunction
  
 calc_diff_table(7, 1, 0.25)
  
  