function ret = bisection(f, a, b, err)

    for n = 0:100

        if abs(a - b) < err
            break
        end

        c = (a + b) ./ 2;

        if f(a) * f(c) <= 0
            b = c;
        else
            a = c;
        end

    end

    ret = a;
end
