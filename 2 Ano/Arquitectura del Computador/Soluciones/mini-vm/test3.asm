datos:
	read %r0
	mov %r0, %r1
	cmp %r0, $0
	jmpe end
	ford:
		read %r2
		push %r2
	loop ford
	mov %r1, %r0
	call suma
	end:
	print %r0
	hlt
suma:
	pop %r3
	mov $0, %r1
	fors:
		pop %r2
		add %r2, %r1
	loop fors
	mov %r1, %r0
	push %r3
ret
