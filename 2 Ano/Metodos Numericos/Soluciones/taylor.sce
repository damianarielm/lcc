function valor = taylor(f, v, n)
    h = 0.01

    for i = 1:n
        numerador = derivar(f, 0 , i, h)
        denominador = factorial(i)
        coeficientes(i) = numerador / denominador
    end
    p = poly(coeficientes, "x", "coeff")
    valor = horner(p, v) + f(0)
endfunction
