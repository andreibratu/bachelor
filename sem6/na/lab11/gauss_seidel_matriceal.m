function [xx, i] = gauss_seidel_matriceal(A, b, x0, err, N)
    x = x0(:);
    L = tril(A);
    D = diag(diag(A));
    U = A - L - D;

    for i = 1:N
        x0 = x;
        x = inv((D + L)) * (-U * x0 + b);

        if norm(x - x0, inf) < err * norm(x, inf)
            xx = x;
            return
        end

    end

end
