#define mantisa(n) (*((unsigned int*) &n) << 9) >> 9
#define exponente(n) ((*((unsigned int*) &n) << 1) >> 24)
#define signo(n) (*((unsigned int*) &n) >> 31)

/*
La norma ilcc2017 utiliza:
	1 bit para el signo,
	16 para la mantisa y
	18 para el exponente
con un sesgo de 30000
y 1 implicito.
*/

typedef struct {
	unsigned int negative:1;
	unsigned int exponent:16;
	unsigned int mantissa:18;
} ilcc;

void ilcc_print(ilcc n);
float ilcc_significante(ilcc n);