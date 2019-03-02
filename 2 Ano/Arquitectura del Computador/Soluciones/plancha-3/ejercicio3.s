.text
.global fuerzabruta

# buscarchar(char* %rdi, unsigned %rsi, unsigned %rdx):
# cadena donde buscar, longitud de la cadena, caracter a buscar.
buscarchar:
	# La cadena donde buscar ya viene en %rdi
	movq %rsi, %rcx # Cantidad maxima de iteraciones
	movq %rdx, %rax # Caracter a buscar

	repne scasb
	jnz notfound
	jmp continuar

# compararcadenas(char* %rdi, char* %rsi, unsigned %rdx):
# primer cadena, segunda cadena, longitud de las cadenas.
compararcadenas:
	# La primer cadena ya viene en %rdi
	# La segunda cadena ya viene en %rsi
	movq %rdx, %rcx # Cantidad maxima de iteraciones

	repe cmpsb
	jnz inicio
	jmp epilogo

fuerzabruta:
	# Prologo
	movq %r13, %xmm0
	movq %r14, %xmm1
	movq %r15, %xmm2
	
	# Crea una copia de los argumentos
	movq %rdi, %r8 # Cadena larga
	movq %rsi, %r9 # Cadena corta
	movq %rdx, %r13 # Longitud larga
	movq %rcx, %r14 # Longitud corta
	decq %r14
	movq %rdi, %r15 # Subcadena larga

	inicio:
		# Busca el caracter inicial de la palabra corta
		movq %r15, %rdi # Carga el priemr argumento 
		movq %r13, %rsi # Carga el segundo argumento 
		movq (%r9), %rdx # Carga el tercer argumento
		jmp buscarchar

	continuar:
		movq %rdi, %r15 # Nueva cadena para la proxima busqueda

		# Prepara el retorno por si encuentra la cadena
		movq %rdi, %rax
		subq %r8, %rax
		decq %rax

		# Caso particular, cadena corta de 1 caracter
		cmpq $0, %r14
		je epilogo

		# Compara la cadena desde la posicion actual
		# El primer argumento ya quedo acomodado por buscarchar
		movq %r9, %rsi # Carga el segundo argumento
		incq %rsi # El primer caracter ya fue encontrado
		movq %r14, %rdx # Carga el tercer argumento
		jmp compararcadenas

notfound:
	movq $-1, %rax

epilogo:
	movq %xmm0, %r13
	movq %xmm1, %r14
	movq %xmm2, %r15
ret
