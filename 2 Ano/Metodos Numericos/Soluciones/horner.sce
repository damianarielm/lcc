function bi = aux(p, x0, i)
    n = degree(p)
    if i == n then
        bi = coeff(p, n)
    else
        ai = coeff(p, i)
        bi = ai + x0 * aux(p, x0, i + 1)
    end
endfunction

function b0 = calcular(p, x0)
    b0 = aux(p, x0, 0)
endfunction

p = poly([3 2 1], "x", "coeff");
assert_checkequal(calcular(p, 4), horner(p, 4));
