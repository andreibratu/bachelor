n = 6;
line = [3, -1, zeros(1, n - 2)];

A = toeplitz(line);
b = [2 1 1 1 1 2]';

x0 = zeros(size(b));
N = 150;
xe = A \ b;
omega = 1.1;
err = 1e-3;

[x_jacobi, iter_jacobi] = jacobi_iterative(A, b, x0, err, N);
[x_gauss, iter_gauss] = gauss_seidel_iterative(A, b, x0, err, N);
[x_relax, iter_relax] = relaxation_iterative(A, b, omega, x0, err, N);

fprintf('norm(x_jacobi - xe)/norm(xe) = %d, with %d iterations\n', norm(x_jacobi - xe) / norm(xe), iter_jacobi);
fprintf('norm(x_gauss - xe)/norm(xe) = %d, with %d iterations\n', norm(x_gauss - xe) / norm(xe), iter_gauss);
fprintf('norm(x_relax - xe)/norm(xe) = %d, with %d iterations\n', norm(x_relax - xe) / norm(xe), iter_relax);

disp(x_jacobi)
disp(x_gauss)
disp(x_relax)
