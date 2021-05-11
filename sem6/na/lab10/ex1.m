A = [10 7 8 7; 7 5 6 5; 8 6 10 9; 7 5 9 10];
B = [32 23 33 31]';

%a
fprintf("a\n"); 
fprintf("the result:\n");  
X = gauss(A,B)
fprintf("k2 = %4.2e, k1 = %4.2e, kinf = %4.2e\n", cond(A,2), cond(A,1), cond(A,inf));

%b
fprintf("\n\n"); 
Bb = [32.1 22.9 33.1 30.9]';
fprintf("B~=:\n");  
Xb = gauss(A,Bb)


input_relative_err = norm(B-Bb)/norm(B)
output_relative_err = norm(X-Xb)/norm(X)
output_relative_err/input_relative_err

%c
fprintf("\n\n"); 
Aa = [10 7 8.1 7.2; 7.08 5.04 6 5; 8 5.98 9.89 9; 6.99 4.99 9 9.98]; 
Xa = gauss(Aa,B)

input_relative_err_A = norm(A-Aa)/norm(A)
output_relative_err_A = norm(X-Xa)/norm(X)
output_relative_err_A/input_relative_err_A