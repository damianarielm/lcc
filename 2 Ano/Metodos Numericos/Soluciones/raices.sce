function r = raices(polinomio)
    a = coeff(p, 2)
    b = coeff(p, 1)
    c = coeff(p, 0)
    delta = b^2 - 4*a*c

    if b < 0 then
        x1 = (2*c) / (-b + sqrt(delta))
        x2 = (-b + sqrt(delta)) / (2*a)
    else
        x1 = (-b - sqrt(delta)) / (2*a)
        x2 = (2*c) / (-b - sqrt(delta))
    end

    r = [x1; x2]
endfunction

function r = resolvente(p)
    a = coeff(p, 2)
    b = coeff(p, 1)
    c = coeff(p, 0)
    delta = b^2 - 4*a*c
    x1 = (-b - sqrt(delta)) / 2*a
    x2 = (-b + sqrt(delta)) / 2*a
    r = [x1; x2]
endfunction

epsilon = 0.0001;
a = epsilon;
b = 1 / epsilon;
c = -epsilon;

p = poly([c b a], "x", "coeff");
assert_checkequal(raices(p), roots(p));

error1 = abs(raices(p)(1) - resolvente(p)(1))
error2 = abs(raices(p)(1) - resolvente(p)(1))
