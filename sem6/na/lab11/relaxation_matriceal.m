function [xx, i] = relaxation_matriceal(A, b, omega, x0, err, N)
    L = tril(A);
    D = diag(diag(A));
    U = A - L - D;
    x = x0(:);

    for i = 1:N
        x0 = x;
        x = inv((D + omega * L)) * (((1 - omega) * D - omega * U) * x0 + omega * b);

        if norm(x - x0, inf) < err * norm(x, inf)
            xx = x;
            return
        end

    end

end
