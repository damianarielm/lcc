#define REGS 8
#define MEM_SIZE (1024)
#define SIZE_INSTRUCTION sizeof(struct Instruction)

// Posicion de cada bandera
#define SEGMENTATION_BIT_FLAGS 0
#define DEBUG_BIT_FLAGS 1
#define ZERO_BIT_FLAGS 2
#define EQUAL_BIT_FLAGS 3
#define LOWER_BIT_FLAGS 4

#define ISSET_BIT(X) (machine.reg[FLAGS] & (1<<(X)))

#define ISSET_DEBUG ISSET_BIT(DEBUG_BIT_FLAGS)
#define ISSET_SEGMENTATION ISSET_BIT(SEGMENTATION_BIT_FLAGS)
#define ISSET_ZERO ISSET_BIT(ZERO_BIT_FLAGS)
#define ISSET_EQUAL ISSET_BIT(EQUAL_BIT_FLAGS)
#define ISSET_LOWER ISSET_BIT(LOWER_BIT_FLAGS)

#define SET_DEBUG machine.reg[FLAGS] = (machine.reg[FLAGS] | (1<<(DEBUG_BIT_FLAGS)))
#define SET_SEGMENTATION machine.reg[FLAGS] = (machine.reg[FLAGS] | (1<<(SEGMENTATION_BIT_FLAGS)))
#define SET_ZERO machine.reg[FLAGS] = (machine.reg[FLAGS] | (1<<(ZERO_BIT_FLAGS)))
#define SET_EQUAL machine.reg[FLAGS] = (machine.reg[FLAGS] | (1<<(EQUAL_BIT_FLAGS)))
#define SET_LOWER machine.reg[FLAGS] = (machine.reg[FLAGS] | (1<<(LOWER_BIT_FLAGS)))

#define UNSET_DEBUG machine.reg[FLAGS] = (machine.reg[FLAGS] & ~(1<<(DEBUG_BIT_FLAGS)))
#define UNSET_SEGMENTATION machine.reg[FLAGS] = (machine.reg[FLAGS] & ~(1<<(SEGMENTATION_BIT_FLAGS)))
#define UNSET_ZERO machine.reg[FLAGS] = (machine.reg[FLAGS] & ~(1<<(ZERO_BIT_FLAGS)))
#define UNSET_EQUAL machine.reg[FLAGS] = (machine.reg[FLAGS] & ~(1<<(EQUAL_BIT_FLAGS)))
#define UNSET_LOWER machine.reg[FLAGS] = (machine.reg[FLAGS] & ~(1<<(LOWER_BIT_FLAGS)))

typedef enum { ZERO,
            PC,
            SP,
            R0,
            R1,
            R2,
            R3,
            FLAGS
} Registers ;

typedef enum { IMM, REG, MEM, LABELOP } OperandType ;

struct Operand {
  const char *lab;
  OperandType type; 
  int val;
} ;

typedef enum {
  NOP,
  MOV,
  AND,
  LW,
  SW,
  PUSH,
  POP,
  CALL,
  RET,
  PRINT,
  READ,
  ADD,
  SUB,
  MUL,
  DIV,
  CMP,
  JMP,
  JMPE,
  JMPL,
  HLT, 
  LABEL,
  DMP,
  DBG,
  SEG
} Opcode;

struct Instruction {
  Opcode op;
  struct Operand src; 
  struct Operand dst;
} ;

struct Machine {
  int reg[REGS];
  int memory[MEM_SIZE];
} ;

extern int count;
extern struct Instruction code[512];

int reg(const char*);
