x = [1 2];
f = [0 0.6931];
deriv = [1 0.5];
X = 1.5;

res = HermitePol(x,f,deriv,X);
display(res)

val = log(1.5);
err = abs(val-res);
display(err)
