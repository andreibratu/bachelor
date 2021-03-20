  
x = 1:2:115;
y = sqrt(x);

m = length(x);

f = [y'];

X = 115;

for i = 1:m
  for j = 1:i-1
    determinant = det([f(j, j), x(j) - X; f(i, j), x(i) - X]);
    f(i, j+1) = 1 / (x(i) - x(j)) * determinant;
  end
end

f(m, m)