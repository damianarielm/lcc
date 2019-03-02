.text
.globl sum

sum:
	movq %rdx, %rcx # Inicializa el iterador

	for:
		movss (%rdi), %xmm0 # %xmm0 = a[i]
		movss (%rsi), %xmm1 # %xmm1 = b[i]
		addss %xmm1,  %xmm0 # %xmm0 = a[i] + b[i]
		movss %xmm0,  (%rdi)
		addq $4, %rdi
		addq $4, %rsi
	loop for
ret
