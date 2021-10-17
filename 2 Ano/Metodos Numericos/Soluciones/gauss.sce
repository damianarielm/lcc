function [x, a] = gausselim(A, b)
    a = [A b];
    [nA, mA] = size(A)

    for k = 1:nA-1
        for i = k+1:nA
            for j = k+1:nA+1
                a(i, j) = a(i, j) - a(k, j) * a(i, k) / a(k, k);
            end;
        end;
    end;

    x = superior(a(:,1:mA), a(:,mA+1))
    a = [triu(a(:,1:mA)), a(:,mA+1)]
endfunction
