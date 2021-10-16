function x = superior(A, b)
    n = size(A, 1)
    x = zeros(n, 1)

    x(n) = b(n) / A(n, n)
    for i = n-1:-1:1
        x(i) = (b(i) - A(i, i+1:n) * x(i+1:n)) / A(i, i)
    end
endfunction

function x = inferior(A, b)
    x = flipdim(superior(A', flipdim(b, 1)), 1)
endfunction

assert_checkequal(superior([1, 1; 0, 1], [2; 3]), [-1; 3])
assert_checkequal(inferior([1, 0; 1, 1], [3; 2]), [3; -1])
