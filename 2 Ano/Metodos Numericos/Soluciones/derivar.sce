function y = derivar(f, v, n, h)
    if n == 0 then
        y = f(v)
    else
        d0 = f
        for i = 1:n
            argumento = "(x)"
            incremento = "(x + " + string(h) + ")"
            nombre = "d" + string(i)
            anterior = "d" + string(i - 1)
            cuerpo = "y = (" + anterior + incremento
            cuerpo = cuerpo + "-" + anterior + argumento
            cuerpo = cuerpo + ") /" + string(h)
            deff("y = " + nombre + "(x)", cuerpo)
        end
        deff("y = dn" + "(x)", cuerpo)
        y = dn(v);
    end
endfunction
