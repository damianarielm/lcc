function r = secante(f, xn1, xn, e)
    if abs(xn - xn1) <= e then
        r = xn1
    else
        numerador = xn - xn1
        denominador = f(xn) - f(xn1)
        sig = xn - f(xn) * (numerador / denominador)
        r = secante(f, xn, sig, e)
    end
endfunction

function y = p(x)
    y = (x - 3) * (x + 3)
endfunction

assert_checkalmostequal(secante(p, -4, -2, 0.1), -3, 0.1)
assert_checkalmostequal(secante(p, 2, 4, 0.1), 3, 0.1)
