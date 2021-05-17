A = [3 1 1; -2 4 0; -1 2 -6];
b = [12 2 -5]';

x0 = zeros(size(b));
maxIter = 100;
xe = A \ b;
omega = 1.1;
err = 1e-5;

[x_jacobi, iter_jacobi] = jacobi_matriceal(A, b, x0, err, maxIter);
[x_gauss, iter_gauss] = gauss_seidel_matriceal(A, b, x0, err, maxIter);
[x_relax, iter_relax] = relaxation_matriceal(A, b, omega, x0, err, maxIter);

fprintf('norm(x_jacobi - xe)/norm(xe) = %d, with %d iterations\n', norm(x_jacobi - xe) / norm(xe), iter_jacobi);
fprintf('norm(x_gauss - xe)/norm(xe) = %d, with %d iterations\n', norm(x_gauss - xe) / norm(xe), iter_gauss);
fprintf('norm(x_relax - xe)/norm(xe) = %d, with %d iterations\n', norm(x_relax - xe) / norm(xe), iter_relax);
