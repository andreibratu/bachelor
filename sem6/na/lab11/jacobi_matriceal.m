function [x, i] = jacobi_matriceal(A, b, x0, err, N)
    L = tril(A);
    D = diag(diag(A));
    U = A - L - D;
    x = x0(:);

    for i = 1:N
        x0 = x;
        x = inv(D) * (-(L + U) * x0 + b);

        if norm(x - x0, inf) < err * norm(x, inf)
            return
        end

    end

end
