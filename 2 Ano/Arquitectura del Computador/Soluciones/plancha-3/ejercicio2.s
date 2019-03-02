# gcc ejercicio2.s

.text
.global main

main:
	movq $127, %rax # Numero de prueba
	movq $64, %rcx # Inicializa el iterador
	movq $0, %rdx # Inicializa el contador

	for:
		ror %rax # Rota el registro
		adc $0, %rdx # Cuenta el carry
	loop for

	movq %rdx, %rax # Prepara el retorno
ret
