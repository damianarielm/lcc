function r = biseccion(f, a, b, e)
    c = (a + b) / 2
    if b - c <= e then
        r = c
    else
        if f(b)*f(c) <= 0 then
            r = biseccion(f, c, b, e)
        else
            r = biseccion(f, a, c, e)
        end
    end
endfunction

function y = p(x)
    y = (x - 3) * (x + 3)
endfunction

assert_checkalmostequal(biseccion(p, -4, -2, 0.1), -3, 0.1)
assert_checkalmostequal(biseccion(p, 2, 4, 0.1), 3, 0.1)
