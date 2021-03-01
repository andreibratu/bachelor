n=input('Give value for n: ');
g = 1;
for i = 1:1:n
   g = 1/(1 + g); 
end

display(g)