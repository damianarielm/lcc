.globl shiftleft
shiftleft:
	mov r1, r0 @ Argumento
	sub r1, r1, #1
	mov r3, #2
	mov r0, r3, LSL r1
	bx lr
