#include <stdlib.h>
#include <setjmp.h>

#define TPILA 4096
#define NPILAS 10

static void hace_stack(jmp_buf buf, void (*pf)(), unsigned prof, char *dummy) {
	if( dummy - (char *) &prof >= prof) {
		if (setjmp(buf)!=0) {
			pf(); abort();
		}
	} else hace_stack(buf, pf, prof, dummy);
}

void stack(jmp_buf buf, void (*pf)()) {
	static int ctas = NPILAS;
	char dummy;
	hace_stack(buf, pf, TPILA *ctas, &dummy);
	ctas--;
}
