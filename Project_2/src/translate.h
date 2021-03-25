#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <stdint.h>




int translate_inst(FILE* output, const char* name, char** args, size_t num_args, 
    uint32_t addr, SymbolTable* symtbl, SymbolTable* reltbl);

/* Declaring helper functions: */

int write_rtype(uint8_t opcode,  uint8_t funct3, uint8_t funct7, FILE* output, char** args, size_t num_args); /* for add, sub, and, or, sll, srl, sra instructions */


int write_shift_im(uint8_t opcode, uint8_t funct3, uint8_t funct7,FILE* output, char** args, size_t num_args); /* For immediate shift instructions */ 

int write_pc(uint8_t opcode, FILE* output, char** args, size_t num_args);




int write_imm(uint8_t opcode, uint8_t funct3, FILE* output, char** args, size_t num_args); /* for addi and orri instructions */
int read_mem(uint8_t opcode, uint8_t funct3, FILE* output, char** args, size_t num_args);



int write_mem(uint16_t opcode, uint8_t funct3, FILE* output, char** args, size_t num_args); /* for ldurw, ldurb, sturw, and sturb instructions */
                      

int write_branch(uint8_t opcode, uint8_t funct3, FILE* output, char** args, size_t num_args, 
	uint32_t addr, SymbolTable* symtbl);


int write_jal(uint8_t opcode, FILE* output, char** args, size_t num_args, 
	uint32_t addr, SymbolTable* reltbl);                                   /* for b and bl instructions */
	
int write_jalr(uint8_t opcode, uint8_t funct3, FILE* output, char** args, size_t num_args, 
	uint32_t addr, SymbolTable* reltbl);

#endif
