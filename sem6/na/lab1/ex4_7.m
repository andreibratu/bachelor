[X,Y] = meshgrid(-2:0.1:2, -4:0.1:4);
Z = exp((-(X-1/2).^2-(Y-1/2).^2));
mesh(X,Y,Z);