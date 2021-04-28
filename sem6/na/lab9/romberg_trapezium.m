function Q = romberg_trapezium(f, qPrev, k, a, b, eps)
    h = b - a;
    j = 1:1:2^(k - 1);  
    qCurrent = 0.5 * qPrev + h / (2^k) * sum(f(a + (2.*j - 1) / (2^k) * h));

    if (abs(qCurrent - qPrev) > eps)
        Q = romberg_trapezium(f, qCurrent, k + 1, a, b, eps);
    else
        Q = qCurrent;
    end
end