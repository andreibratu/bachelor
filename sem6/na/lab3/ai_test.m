function z = ai_test(i,x)
  m = length(x);
  p = 1;
for j = 1:m
  if i~=j
    p = p*(x(i)-x(j));
  endif
z = 1/p;
end
endfunction