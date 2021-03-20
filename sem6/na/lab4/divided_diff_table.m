function result = divided_diff_table (x, f)
    [~, n] = size(x);
    table = zeros(n, n+1);
    
    table(:, 1) = x';
    table(:, 2) = f';
    
    for column = 3 : n+1
        order = column - 2;
        for row = 1 : n
            if row <= n - order
                table(row, column) = ...
                    (table(row + 1, column - 1) - table(row, column - 1)) ...
                    / ( x(1, row + order) - x(1, row) );
            else
                table(row, column) = 0;
            end
        end
    end
    result = table;
endfunction