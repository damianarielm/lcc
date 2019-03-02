.text
.globl solve

solve:
	# Sistema 2x2:
	# (1) ax + by = c
	# (2) dx + ey = f

	# a viene en %xmm0
	# b viene en %xmm1
	# c viene en %xmm2
	# d viene en %xmm3
	# e viene en %xmm4
	# f viene en %xmm5

	# x se guardara en (%rdi)
	# y se guardara en (%rsi)

	# Calculo del determinante
	movss %xmm0, %xmm6 # %xmm6 = a
	mulss %xmm4, %xmm6 # %xmm6 = ae
	movss %xmm1, %xmm7 # %xmm7 = b
	mulss %xmm3, %xmm7 # %xmm7 = bd
	subss %xmm7, %xmm6 # %xmm6 = ae - bd

	# Sistema incompatible/indeterminado
	xorq %rax, %rax
	cvtsi2ssq %rax, %xmm7
	ucomiss %xmm6, %xmm7
	je determinante0

	# Calculo de x por Cramer
	movss %xmm2, %xmm7 # %xmm7 = c
	mulss %xmm4, %xmm7 # %xmm7 = ce
	mulss %xmm1, %xmm5 # %xmm5 = fb
	subss %xmm5, %xmm7 # %xmm7 = ce - fb
	divss %xmm6, %xmm7 # %xmm7 = (ce - fb) / (ae - bd) = x

	# Calculo de y por substitucion en (1)
	mulss %xmm7, %xmm0 # %xmm0 = ax
	subss %xmm0, %xmm2 # %xmm2 = c - ax
	divss %xmm1, %xmm2 # %xmm2 = (c-ax)/b = y

	# Escribe en memoria
	movss %xmm7, (%rdi)
	movss %xmm2, (%rsi)
ret

determinante0:
	movq $-1, %rax
ret

