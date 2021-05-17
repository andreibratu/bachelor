function [x, cnt] = gauss_seidel_iterative(A, b, x0, err, N)
    n = size(b);
    cnt = 0;
    x = x0;

    while cnt < N
        cnt = cnt + 1;

        for i = 1:n
            s = 0;

            for j = 1:n

                if (j > i)
                    s = s + A(i, j) * x0(j);
                end

                if (j < i)
                    s = s + A(i, j) * x(j);
                end

            end

            x(i) = (b(i) - s) / (A(i, i));
        end

        if norm(x - x0) < err
            return
        end

        x0 = x;
    end

    fprintf('Insufficient iteration steps')
end
