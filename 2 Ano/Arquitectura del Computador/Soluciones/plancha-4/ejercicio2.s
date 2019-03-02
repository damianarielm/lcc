.globl campesino_ruso
campesino_ruso:
    mov r2, r1 @ Segundo argumento en r2
    mov r1, r0 @ Primer argumento en r1
    mov r0, #0 @ Argumento de retorno
    push {lr}

inicio:
    cmp r2, #1
    addls r0, r0, r1 @ return res + i
    popls {pc}
    
    andS r3, r2, #1 @ if j & 1

    @ then
    addne r0, r0, r1 @ res += i
    subne r2, r2, #1 @ j -= 1

    @ else
    lsleq r1, #1 @ i *= 2
    asreq r2, #1 @ j /= 2

    b inicio @ loop
