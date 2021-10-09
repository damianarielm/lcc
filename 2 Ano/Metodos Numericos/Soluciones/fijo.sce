function r = fijo(ecuacion, g, xk)
    if ecuacion(xk) then
        r = xk
    else
        r = fijo(ecuacion, g, g(xk))
    end
endfunction
