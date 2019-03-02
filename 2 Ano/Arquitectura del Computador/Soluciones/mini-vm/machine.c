// gcc machine.c lex.yy.c parser.tab.c

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "parser.tab.h"
#include "machine.h"

// Variables globales
int count; // Lineas de codigo
struct Instruction code[512]; // Arreglo de instrucciones
const char *regname[REGS] = { "\%zero", "\%pc", "\%sp", "\%r0","\%r1","\%r2","\%r3", "\%flags"};
struct Machine machine;
extern FILE *yyin;

// Banderas del depurador
char next = 0;
char breakpoint = 0;

// Devuelve el numero de registro
int reg(const char* r) {
  r++; // Skip %
  if (!strcmp(r,"zero")) return 0;
  if (!strcmp(r,"pc")) return 1;
  if (!strcmp(r,"sp")) return 2;
  if (!strcmp(r,"r0")) return 3;
  if (!strcmp(r,"r1")) return 4;
  if (!strcmp(r,"r2")) return 5;
  if (!strcmp(r,"r3")) return 6;
  if (!strcmp(r,"flags")) return 7;
  printf("Unkown Register %s\n",r);
  abort();
}

// Volcado de registros
void dumpMachine() {
  printf("************************ Machine state at PC=%d **********************\n", machine.reg[PC]);
  for (int i = 0; i < REGS; i++) 
    if (strlen(regname[i])==0) continue; 
    else printf("%d\t%s\t\t\t= \t\t%d \t\t%x\n", i, regname[i],machine.reg[i],machine.reg[i]);
  printf("**********************************************************************\n");
}

// Volcado de memoria
void dumpMemory() {
  printf("***************** Memory state at PC=%d ***************\n", machine.reg[PC]);
  for (int i = 0; i < MEM_SIZE; i++) {
    printf("%d: %d\t", i, machine.memory[i]);
  }
  printf("\n********************************************************\n");
}

int origen(struct Operand o) {
  switch(o.type) {
    case IMM:
      return o.val;
    case REG:
      return machine.reg[o.val];
    case MEM:
      if (o.lab) return machine.memory[machine.reg[o.val]];
      else return machine.memory[o.val];
  }
}

int* destino(struct Operand o) {
  switch(o.type) {
    case REG:
      if (o.val == ZERO) { printf("Error. Intentando modificar el registro zero.\n"); abort(); }
      else { return &(machine.reg[o.val]); }
    case MEM:
      if (ISSET_SEGMENTATION && o.val < count) return NULL;
      else return &(machine.memory[o.val]);
  }
}

// Ejecuta una instruccion
void runIns(struct Instruction i) {
  int* d1 = destino(i.src);
  int* d2 = destino(i.dst);
  int o1 = origen(i.src);
  int o2 = origen(i.dst);

  switch (i.op) {
    case NOP:
      break;
    case MOV: {
      *d2 = o1;
      break;
    }
    case SW:
      machine.memory[o2] = o1;
      break;
    case LW: {
      *d2 = machine.memory[o1];
      break;
    }
    case PUSH:
      machine.reg[SP]--;
      machine.memory[machine.reg[SP]] = o1;
      break;
    case POP: {
      *d1 = machine.memory[machine.reg[SP]];
      machine.reg[SP]++;
      break;
    }
    case CALL:
      machine.reg[SP]--;
      machine.memory[machine.reg[SP]] = machine.reg[PC];
      machine.reg[PC] = o1 - 1;
      break;
    case RET:
      machine.reg[PC] = machine.memory[machine.reg[SP]];
      machine.reg[SP]++;
      break;
    case PRINT:
      printf("%d\n", o1);
      break;
    case READ: {
      scanf("%d", d1);
      break;
    }
    case ADD: {
      *d2 = o1 + o2;
      if (*d2 == 0) SET_ZERO; else UNSET_ZERO;
      break;
    }
    case SUB: {
      *d2 = o1 - o2;
      if (*d2 == 0) SET_ZERO; else UNSET_ZERO;
      break;
    }
    case MUL: {
      *d2 = o1 * o2;
      if (*d2 == 0) SET_ZERO; else UNSET_ZERO;
      break;
    }
    case DIV: {
      *d2 = o1 / o2;
      if (*d2 == 0) SET_ZERO; else UNSET_ZERO;
      break;
    }
    case AND: {
      *d2 = o1 & o2;
      if (*d2 == 0) SET_ZERO; else UNSET_ZERO;
      break;
    }
    case CMP:
      if (o1 == o2) {
        UNSET_LOWER;
        SET_EQUAL;
      } else {
        UNSET_EQUAL;
	if (o1 < o2) SET_LOWER;
      }
      break;
    case JMP:
      machine.reg[PC] = o1 - 1;
      break;
    case JMPE:
      if (ISSET_EQUAL) machine.reg[PC] = o1 - 1;
      break;
    case JMPL:
      if (ISSET_LOWER) machine.reg[PC] = o1 - 1;
      break;
    case DMP:
      dumpMachine();
      dumpMemory();
      break;
    case DBG:
      if (ISSET_DEBUG) UNSET_DEBUG; else SET_DEBUG;
      break;
    case SEG:
      if (ISSET_SEGMENTATION) UNSET_SEGMENTATION; else SET_SEGMENTATION;
      break;
    case HLT:
      machine.reg[PC]--;
      break;
    default:
      printf("Instruction not implemented\n");
      abort();
  }
}

// Reemplaza las etiquetas por valores inmediatos
void processLabels() {
  int i,j,k;
  for (i=0;i<count;i++) { // Recorre el codigo...
    if (code[i].op==LABEL) { // ...en busca de una etiqueta
      for (j=0;j<count;j++) { // Recorre el codigo...
        if (code[j].op == CALL || code[j].op == JMP || code[j].op== JMPE || code[j].op==JMPL) { // ...buscando un salto
          if (code[j].src.lab && strcmp(code[j].src.lab,code[i].src.lab)==0) { // Si el salto corresponde a la etiqueta
            code[j].src.type=IMM;
            code[j].src.val=i; // Agrega el numero de linea
            code[j].src.lab=NULL; // Borra la etiqueta de la instruccion
          }
        }
      }
      // Borra la etiqueta del codigo
      for (j=i;j<count-1;j++) {
        code[j]=code[j+1];
      }
      count--;      
    }
  }
  // Chequea que todas las etiquetas existan
  for (j=0;j<count;j++) {
    if (code[j].op == CALL || code[j].op == JMP || code[j].op== JMPE || code[j].op==JMPL) {
      if (code[j].src.lab) {
        printf("Jump to unkown label %s\n",code[j].src.lab);
        exit(-1);
      }
    }
  }
}

void printOperand(struct Operand s) {
  switch (s.type) {
    case IMM:
      printf("$%d", s.val);
      break;
    case REG:
      printf("%s", regname[s.val]);
      break;
    case MEM:
      if (s.lab) printf("(%s)", regname[s.val]);
      else printf("%d", s.val);
      break;
  } 
}

void printInstr(struct Instruction i) {
  switch (i.op) {
    case NOP:
      printf("NOP");
      break;
    case HLT:
      printf("HLT");
      break;
    case MOV:
      printf("MOV ");
      printOperand(i.src);
      printf(",");
      printOperand(i.dst);
      break;
    case LW:
      printf("LW ");
      printOperand(i.src);
      printf(",");
      printOperand(i.dst);
      break;
    case ADD:
      printf("ADD ");
      printOperand(i.src);
      printf(",");
      printOperand(i.dst);
      break;
    case MUL:
      printf("MUL ");
      printOperand(i.src);
      printf(",");
      printOperand(i.dst);
      break;
    case SUB:
      printf("SUB ");
      printOperand(i.src);
      printf(",");
      printOperand(i.dst);
      break;
    case DIV:
      printf("DIV ");
      printOperand(i.src);
      printf(",");
      printOperand(i.dst);
      break;
    case AND:
      printf("AND ");
      printOperand(i.src);
      printf(",");
      printOperand(i.dst);
      break;
    case JMPL:
      printf("JMPL ");
      printOperand(i.src);
      if (i.src.lab)
        printf("%s",i.src.lab);
      break;
    case JMPE:
      printf("JMPE ");
      printOperand(i.src);
      if (i.src.lab)
        printf("%s",i.src.lab);
      break;
    case JMP:
      printf("JMP ");
      printOperand(i.src);
      if (i.src.lab)
        printf("%s",i.src.lab);
      break;
    case LABEL:
      printf("LABEL %s",i.src.lab);
      break;
    case CMP:
      printf("CMP ");
      printOperand(i.src);
      printf(",");
      printOperand(i.dst);
      break;
    case PRINT:
      printf("PRINT ");
      printOperand(i.src);
      break;
    case READ:
      printf("READ ");
      printOperand(i.src);
      break;
    case PUSH:
      printf("PUSH ");
      printOperand(i.src);
      break;
    case POP:
      printf("POP ");
      printOperand(i.src);
      break;
    case CALL:
      printf("CALL ");
      printOperand(i.src);
      if (i.src.lab)
        printf("%s",i.src.lab);
      break;
    case RET:
      printf("RET ");
      break;
    case DMP:
      printf("DMP ");
    case DBG:
      printf("DBG ");
      break;
    default:
      printf("Instrucction not printed.\n");
  }
}

struct Instruction* getInstruction(int linea) {
    return (struct Instruction*) &(machine.memory[linea*SIZE_INSTRUCTION/sizeof(int)]);
}

void printCode() {
  printf("\n*****Codigo******\n");
  for (int j = 0; j < count; j++)  {
    if (j == machine.reg[PC]) printf(">> ");
    printf("%d: ",j);
    printInstr(*getInstruction(j));
    if (breakpoint && breakpoint == j) printf(" (*)");
    puts("");
  }
  printf("*****************\n");
}

void debug() {
  char comando[100];
  int direccion, valor;
  
  while (1) {
    printf("Ingrese comando (h para ayuda): ");
    scanf("%s", comando);

    if (*comando == 'r') dumpMachine();
    if (*comando == 'm') dumpMemory();
    if (*comando == 'l') printCode();
    if (*comando == 'w') {
      printf("%d: ", machine.reg[PC]);
      printInstr(*getInstruction(machine.reg[PC]));
      puts("");
    }
    if (*comando == 'j') {
      printf("Ingrese una instruccion: ");
      scanf("%d", &valor);
      machine.reg[PC] = valor;
    }
    if (*comando == 'x') {
      printf("Ingrese una direccion de memoria: ");
      scanf("%d", &direccion);
      printf("Valor: %d\n", machine.memory[direccion]);
    }
    if (*comando == 'c') {
      printf("Indique (m)emoria o (r)egistro: ");
      scanf("%s", comando);
      if (*comando == 'm') {
        printf("Ingrese una direccion de memoria: ");
        scanf("%d", &direccion);
        printf("Ingrese el nuevo valor: ");
        scanf("%d", &valor);
	machine.memory[direccion] = valor;
      } else {
        printf("Ingrese un numero de registro: ");
        scanf("%d", &direccion);
        printf("Ingrese el nuevo valor: ");
        scanf("%d", &valor);
	machine.reg[direccion] = valor;
      }
    }
    if (*comando == 'h') {
      printf("******Help******\n");
      printf("(s)tep\n");
      printf("(n)ext\n");
      printf("(j)ump\n");
      printf("(b)reakpoint\n");
      printf("(c)hange\n");
      printf("(r)egisters\n");
      printf("(m)emory\n");
      printf("(l)ist\n");
      printf("(w)here\n");
      printf("e(x)amine\n");
      printf("(q)uit\n");
      printf("****************\n");
    }
    if (*comando == 'b') {
      printf("Ingrese una instruccion: ");
      scanf("%d", &valor);
      breakpoint = valor;
    }
    if (*comando == 's') return;
    if (*comando == 'n') { UNSET_DEBUG; next = 1; return; }
    if (*comando == 'q') { UNSET_DEBUG; return; }
    puts("");
  }
}

void run() {
  // Arquitectura de Von Neumann
  memcpy(&(machine.memory), &code, count*SIZE_INSTRUCTION);

  // Ciclo de ejecucion
  struct Instruction i;
  do {
    i = *getInstruction(machine.reg[PC]);

    // Unidad de depuramiento
    if (ISSET_DEBUG || (breakpoint && machine.reg[PC] == breakpoint) ) { breakpoint = 0; debug(); }
    if (next && i.op == RET) { SET_DEBUG; next = 0; }

    if (ISSET_SEGMENTATION && machine.reg[PC] >= count) {
      printf("Error: Intentando ejecutar codigo en el segmento de pila.\n");
      exit(-1);
    } else {
      runIns(i); // Ejecuta la instruccion
    }
    
    machine.reg[PC]++; // If not a jump, continue with next instruction
  } while (i.op != HLT);
}

// Inicializa la maquina
void init(int argc, char** argv) {
  // Inicializa registros
  machine.reg[PC] = 0; // Start at first instruction
  machine.reg[FLAGS] = 1; // Segmentacion por defecto
  machine.reg[SP] = MEM_SIZE;
  machine.reg[ZERO] = 0;
  machine.reg[R0] = 0;
  machine.reg[R1] = 0;
  machine.reg[R2] = 0;
  machine.reg[R3] = 0;
  
  // Inicializa memoria
  for(int i = 0; i < MEM_SIZE; i++) machine.memory[i] = 0;

  // Argumentos por linea de comando
  if (argc > 2) machine.reg[R0] = atoi(argv[2]);
  if (argc > 3) machine.reg[R1] = atoi(argv[3]);
  if (argc > 4) machine.reg[R2] = atoi(argv[4]);
  if (argc > 5) machine.reg[R3] = atoi(argv[5]);
  for (int i = argc-1; i > 5; i--) {
    machine.reg[SP]--;
    machine.memory[machine.reg[SP]] = atoi(argv[i]);
  }
}

int main(int argc, char** argv) {
  // Manejo de linea de comando
  if (argc < 2) {
    printf("Usage: %s file1.asm\n", argv[0]);
    return -1;
  }

  // Manejo de archivo de entrada
  yyin = fopen(argv[1], "r"); // Lee el archivo
  yyparse(); // Analisis sintactico
  fclose (yyin);  // Cierra el archivo
  processLabels(); // Procesa las etiquetas

  // Bootea la maquina
  init(argc, argv); // Inicializa la maquina
  run(); // Ejecuta el codigo
  return machine.reg[R0]; // Devuelve segun la convencion
}
