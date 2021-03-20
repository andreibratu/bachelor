1;

function result = wow (t)
  result = (1 + cos(pi .* t)) ./ (1 + t);
endfunction

x0 = 0:0.1:10;
y0 = wow(x0);

x1 = linspace(0, 10, 1000);
y1 = wow(x1);

x_l = linspace(0, 10, 21);
y_l = bary_lagn(x1, y1, x_l);

subplot (2, 1, 1)
plot(x0, y0)

subplot (2, 1, 2)
plot(x_l, y_l)