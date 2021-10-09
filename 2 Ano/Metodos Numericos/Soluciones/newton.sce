function r = newton(f, xn, n)
    if n == 0 then
        r = xn
    else
        j = numderivative(f, xn)^-1
        xn1 = xn - j * f(xn)
        r = newton(f, xn1, n - 1)
    end
endfunction
