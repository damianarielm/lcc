function d = determinante(A)
    n = size(A, 1)
    [x a] = gausselim(A, zeros(n, 1))
    d = prod(diag(a))
endfunction
