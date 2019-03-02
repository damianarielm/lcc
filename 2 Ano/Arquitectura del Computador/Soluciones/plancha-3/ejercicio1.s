# gcc ejercicio1.s -no-pie

.data
	fmt: .asciz "%ld\n"
	fmh: .asciz "%#x\n"
	i: .quad 0xdeadbeef

.text
.global main

main:
	movq $fmt, %rdi # el primer argumento es el formato
	movq $1234, %rsi # el valor a imprimir
	xorq %rax, %rax # cantidad de valores de punto flotante
	call printf

	# "El valor de rsp"
	movq $fmt, %rdi # el primer argumento es el formato
	movq %rsp, %rsi# el valor a imprimir
	xorq %rax, %rax # cantidad de valores de punto flotante
	call printf

	# "La direccion de la cadena de formato"
	movq $fmt, %rdi # el primer argumento es el formato
	movq $fmt, %rsi # el valor a imprimir
	xorq %rax, %rax # cantidad de valores de punto flotante
	call printf

	# "La direccion de la cadena de formato en hexadecimal"
	movq $fmh, %rdi # el primer argumento es el formato
	movq $fmt, %rsi # el valor a imprimir
	xorq %rax, %rax # cantidad de valores de punto flotante
	call printf

	# "El quad en el tope de la pila"
	movq $fmt, %rdi # el primer argumento es el formato
	movq (%rsp), %rsi # el valor a imprimir
	xorq %rax, %rax # cantidad de valores de punto flotante
	call printf

	# "El quad ubicado en la direccion rsp+8"
	movq $fmt, %rdi # el primer argumento es el formato
	movq 8(%rsp), %rsi # el valor a imprimir
	xorq %rax, %rax # cantidad de valores de punto flotante
	call printf

	# "El valor de i"
	movq $fmt, %rdi # el primer argumento es el formato
	movq i, %rsi # el valor a imprimir
	xorq %rax, %rax # cantidad de valores de punto flotante
	call printf

	# "La direccion de i"
	movq $fmt, %rdi # el primer argumento es el formato
	movq $i, %rsi # el valor a imprimir
	xorq %rax, %rax # cantidad de valores de punto flotante
	call printf
ret
