.text
.globl sum_sse

# Asumimos que se trata de una cantidad de flotantes multiplo de 4
sum_sse:
	movq %rdx, %rcx # Inicializa el iterador

	for:
		movaps (%rdi), %xmm0 # Carga 4 flotantes en %xmm0 desde (%rdi)
		movaps (%rsi), %xmm1 # Carga 4 flotantes en %xmm1 desde (%rsi)
		addps  %xmm1,  %xmm0 # Suma los 8 flotantes
		movaps %xmm0, (%rdi) # Carga el resultado en la memoria
		addq $16, %rdi
		addq $16, %rsi
		subq $3, %rcx # Drecrementamos de a 4
	loop for
ret
