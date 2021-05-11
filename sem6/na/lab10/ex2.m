min = 10;
max = 15;

n = [min:max];

warning('off');

for i = 1: length(n)
    H = hilb(n(i));
    
    k2 = cond(H,2);
    k1 = cond(H,1);
    kinf = cond(H,inf);
    
    display(k2);
    display(k1);
    display(kinf);
    
    # fprintf("k2 = %4.2e, k1 = %4.2e, kinf = %4.2e\n", k2, k1, kinf);
end