inicializacion:
	read %r0
	push %r0
	mov $31, %r0
programa:
	mov %r0, %r3
	call shiftleft
	and (%sp), %r0
	cmp $0, %r0
	jmpe end
	add $1, %r2
	end:
	mov %r3, %r0
	loop programa
	mov $1, %r0
	and (%sp), %r0
	add %r0, %r2
	print %r2
	hlt
shiftleft:
	mov $1, %r1
	for:
		mul $2, %r1
	loop for
	mov %r1, %r0
ret
