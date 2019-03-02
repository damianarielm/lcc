.text

.globl setjmp2
.globl longjmp2

setjmp2:
	# En %rdi viene la direccion donde guardar la informacion

	# Guarda los registros callee saved en el buffer
	# AMD64 ABI Draft 0.99.7, Pagina 21
	movq %rbx, 8(%rdi)
	movq %r12, 16(%rdi)
	movq %r13, 24(%rdi)
	movq %r14, 32(%rdi)
	movq %r15, 40(%rdi)
	movq %rbp, 48(%rdi)

	movq %rsp, 56(%rdi)
	addq $8, 56(%rdi) # Guarda la pila sin la r.a.

	movq (%rsp), %rax # No puedo tener dos accesos a memoria en la misma instruccion
	movq %rax, 64(%rdi) # Guarda la r.a. para longjmp2

	xorq %rax, %rax # Retorna 0
ret

longjmp2:
	# En %rdi viene la direccion de la informacion a restaurar

	# Restaura los registros del buffer
	movq 8(%rdi), %rbx
	movq 16(%rdi), %r12
	movq 24(%rdi), %r13
	movq 32(%rdi), %r14
	movq 40(%rdi), %r15
	movq 48(%rdi), %rbp
	movq 56(%rdi), %rsp
	movq 64(%rdi), %rdi # Direccion donde saltara longjmp2

	movq %rsi, %rax # Modifica el retorno de setjmp2
jmp *%rdi
