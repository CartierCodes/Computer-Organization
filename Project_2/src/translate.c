#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tables.h"
#include "translate_utils.h"
#include "translate.h"

/* Writes instructions during the assembler's first pass to OUTPUT. The case
   for general instructions has already been completed, but you need to write
   code to translate pseudoinstructions. Your pseudoinstruction 
   expansions should not have any side effects.

   NAME is the name of the instruction, ARGS is an array of the arguments, and
   NUM_ARGS specifies the number of items in ARGS.

   Error checking for regular instructions are done in pass two. However, for
   pseudoinstructions, you must make sure that ARGS contains the correct number
   of arguments. You do NOT need to check whether the registers / label are 
   valid, since that will be checked in part two.

   
   Returns the number of instructions written (so 0 if there were any errors).
 */
unsigned write_pass_one(FILE* output, const char* name, char** args, int num_args) {
	/* Future codes for pseudo instructions fisrt pass processing*/
		write_inst_string(output, name, args, num_args);
		return 1;
	
}

/* Writes instructions during the assembler's first pass to OUTPUT. The case
   for general instructions has already been completed, but you need to write
   code to translate the li and blt pseudoinstructions. Your pseudoinstruction 
   expansions should not have any side effects.

   NAME is the name of the instruction, ARGS is an array of the arguments, and
   NUM_ARGS specifies the number of items in ARGS. 

   Writes the instruction in hexadecimal format to OUTPUT during pass #2. 
   
  NAME is the name of the instruction, ARGS is an array of the arguments, and
   NUM_ARGS specifies the number of items in ARGS. 

   The symbol table (SYMTBL) is given for any symbols that need to be resolved
   at this step. If a symbol should be relocated, it should be added to the
   relocation table (RELTBL), and the fields for that symbol should be set to
   all zeros. 

   You must perform error checking on all instructions and make sure that their
   arguments are valid. If an instruction is invalid, you should not write 
   anything to OUTPUT but simply return -1. MARS may be a useful resource for
   this step.

   Note the use of helper functions. Consider writing your own! If the function
   definition comes afterwards, you must declare it first (see translate.h).

   Returns 0 on success and -1 on error. 
 */
int translate_inst(FILE* output, const char* name, char** args, size_t num_args, uint32_t addr,
	SymbolTable* symtbl, SymbolTable* reltbl) {
        
	if (strcmp(name, "add") == 0)        return write_rtype (0x33, 0x00, 0x00, output, args, num_args);
	else if (strcmp(name, "or") == 0)    return write_rtype (0x33, 0x06, 0x00, output, args, num_args);
	else if (strcmp(name, "sub") == 0)   return write_rtype (0x33, 0x00, 0x20, output, args, num_args);
        else if (strcmp(name, "srl") == 0)   return write_rtype (0x33, 0x05, 0x00, output, args, num_args);
        else if (strcmp(name, "sra") == 0)   return write_rtype (0x33, 0x05, 0x20, output, args, num_args);
        else if (strcmp(name, "sll") == 0)   return write_rtype (0x33, 0x01, 0x00, output, args, num_args);

        else if (strcmp(name, "addi") == 0)  return write_imm(0x13, 0x00, output, args, num_args);
        else if (strcmp(name, "andi") == 0)  return write_imm(0x13, 0x07, output, args, num_args);
        else if (strcmp(name, "ori") == 0)   return write_imm(0x13, 0x06, output, args, num_args);

        else if (strcmp(name, "jal") == 0)   return write_jal(0x6F, output, args, num_args, addr, reltbl);
        else if (strcmp(name, "jalr") == 0)  return write_jalr(0x67, 0x00, output, args, num_args, addr, reltbl);

        else if (strcmp(name, "lb") == 0)    return read_mem(0x03, 0x00, output, args, num_args);
        else if (strcmp(name, "lw") == 0)    return read_mem(0x03, 0x02, output, args, num_args);
        else if (strcmp(name, "sb") == 0)    return write_mem(0x23, 0x00, output, args, num_args);
        else if (strcmp(name, "sw") == 0)    return write_mem(0x23, 0x02, output, args, num_args);

        else if (strcmp(name, "beq") == 0)   return write_branch(0x63, 0x00, output, args, num_args, addr, reltbl);
        else if (strcmp(name, "bne") == 0)   return write_branch(0x63, 0x01, output, args, num_args, addr, reltbl);
        else if (strcmp(name, "blt") == 0)   return write_branch(0x63, 0x04, output, args, num_args, addr, reltbl);

        else if (strcmp(name, "srli") == 0)  return write_shift_im(0x13, 0x05, 0x00, output, args, num_args);
        else if (strcmp(name, "srai") == 0)  return write_shift_im(0x13, 0x05, 0x20, output, args, num_args);
        else if (strcmp(name, "slli") == 0)  return write_shift_im(0x13, 0x02, 0x00, output, args, num_args);
	else                                 return -1;
}




/* A helper function for writing most R-type instructions. You should use
   translate_reg() to parse registers and write_inst_hex() to write to 
   OUTPUT. Both are defined in translate_utils.h.

   This function is INCOMPLETE. Complete the implementation below. You will
   find bitwise operations to be the cleanest way to complete this function.
 */
int write_rtype(uint8_t opcode,  uint8_t funct3, uint8_t funct7, FILE* output, char** args, size_t num_args) {
	if (num_args != 3) {
		return -1;
	}
	
	int rd = translate_reg(args[0]);
	int rs1 = translate_reg(args[1]);
	int rs2 = translate_reg(args[2]);

	if (rd == -1 || rs1 == -1 || rs2 == -1) {
		return -1;
	} 

	
	uint32_t instruction = (funct7 << 25) + (rs2 << 20)  + (rs1 << 15) +  (funct3 << 12) +   (rd << 7) + opcode ;
	write_inst_hex(output, instruction);
	return 0;
}

int write_branch(uint8_t opcode, uint8_t funct3, FILE* output, char** args, size_t num_args,
        uint32_t addr, SymbolTable* symtbl) {
        if (num_args != 3) {
                return -1;
        }

        int rs1 = translate_reg(args[0]);
        int rs2 = translate_reg(args[1]);
        char* label = args[2];

        int add = get_addr_for_symbol(symtbl, label);

        uint32_t imm = (add - addr -4);

        uint32_t bits10to5 = (imm >> 5) & 0x3f;
        uint32_t bits12 = (imm >> 12) & 0x1;
        uint32_t bits11 = (imm >> 11) & 0x1;
        uint32_t bits4to1 = (imm >> 1) & 0xF;


        if (add == -1 || rs1 == -1 || rs2 == -1) {
                return -1;
        }

        uint32_t instruction = opcode + (funct3 << 12) + (rs1 << 15) + (rs2 << 20) +  (bits11 << 7) + (bits4to1 << 8) + (bits10to5 << 25) + (bits12 << 31);


        write_inst_hex(output, instruction);
        return 0;
}


int write_jal(uint8_t opcode, FILE* output, char** args, size_t num_args,
        uint32_t addr,    SymbolTable* reltbl ) {
        if (num_args != 2) {
                return -1;
        }

        int rd = translate_reg(args[0]);
        char* label = args[1];
        int64_t add = add_to_table(reltbl, label, addr);
        uint32_t imm = (add - addr-4) ;

        uint32_t bits19to12 = (imm & 0xFF000);
        uint32_t bits10to1 = ((imm & 0x07FF) >> 1) << 21;
        uint32_t bit11 =  ( (imm >> 11) & 0x1) << 20;
        uint32_t bit20 =  ((imm >> 20) & 0x1 ) << 31;
        if (add == -1 || rd == -1) {
                return -1;
        }
        uint32_t instruction = opcode + (rd << 7) + bits19to12 + bits10to1 + bit11 + bit20 ;
        write_inst_hex(output, instruction);
        return 0;
}

int write_jalr(uint8_t opcode, uint8_t funct3, FILE* output, char** args, size_t num_args,
        uint32_t addr, SymbolTable* reltbl)
{
        if (num_args != 3) {
                return -1;
        }


        int rd = translate_reg(args[0]);
        int rs = translate_reg(args[1]);
        char* label = args[2];
        int64_t add = add_to_table(reltbl, label, addr);
        uint32_t imm = (add - addr-4) ;

        if (add == -1 || rd == -1 || rs == -1) {
                return -1;
        }

        uint32_t instruction = opcode +  (rd << 7) + (funct3 << 12) + (rs << 15)  + (imm << 20) ;
        write_inst_hex(output, instruction);
  return 0;
}

/* A helper function for writing shift immediatei nstructions. You should use 
   translate_num() to parse numerical arguments. translate_num() is defined
   in translate_utils.h.

   This function is INCOMPLETE. Complete the implementation below. You will
   find bitwise operations to be the cleanest way to complete this function.
 */

/* ADD your code here: Functions in translate.h that are not yet implemented */

int write_imm(uint8_t opcode, uint8_t funct3, FILE* output, char** args, size_t num_args) {
        if (num_args != 3) return -1;

        long int s;
        int rd = translate_reg(args[0]);
        int rs1 = translate_reg(args[1]);
        int imm = translate_num(&imm, args[2], -32768, 32767);

        if (rd == -1 || rs1 == -1 || imm == -1) return -1;

        uint32_t bits11 = (imm >> 11) & 0x1;
        uint32_t bits10to5 = (imm >> 5) & 0x3f;
        uint32_t bits4to0 = (s & 0xF);

        uint32_t instruction = (bits11 << 31) + (bits10to5 << 25) + (bits4to0 << 20) + (rs1 << 15) + (funct3 << 12) + (rd << 7) + opcode;

}

int read_mem(uint8_t opcode, uint8_t funct3, FILE* output, char** args, size_t num_args) {
        if (num_args != 3) return -1;

        long int s;
        int rd = translate_reg(args[0]);
        int rs1 = translate_reg(args[1]);
        long imm = translate_num(&imm, args[2], -32768, 32767);

        if (rd == -1 || rs1 == -1 || imm == -1) return -1;

        uint32_t bits11 = (imm >> 11) & 0x1;
        uint32_t bits10to5 = (imm >> 5) & 0x3f;
        uint32_t bits4to0 = (s & 0xF);

        uint32_t instruction = (bits11 << 31) + (bits10to5 << 25) + (bits4to0 << 20) + (rs1 << 15) + (funct3 << 12) + (rd << 7) + opcode;
}

int write_mem(uint16_t opcode, uint8_t funct3, FILE* output, char** args, size_t num_args) {
        if (num_args != 3) return -1;

        long int imm;
        int rs1 = translate_reg(args[0]);
        int error = translate_num(&imm, args[1], -32768, 32767);
        int rs2 = translate_reg(args[2]);

        if (error == -1 || rs1 == -1 || rs2 == -1) return -1;

        uint32_t bits10to5 = (imm >> 5) & 0x3f;
        uint32_t bits11 = (imm >> 11) & 0x1;
        uint32_t bits4to0 = (imm & 0xF);
                        
        uint32_t instruction = (bits11 << 31) + (bits10to5 << 25) + (rs2 << 20) + (rs1 << 15) + (funct3 << 12) + (bits4to0 << 7) + opcode;
	write_inst_hex(output, instruction);
        
	return 0;
}

int write_shift_im(uint8_t opcode, uint8_t funct3, uint8_t funct7,FILE* output, char** args, size_t num_args) {
        if (num_args != 3) return -1;

        long int s;
        int rd = translate_reg(args[0]);
        int rs1 = translate_reg(args[1]);
        int imm = translate_num(&s, args[2], 0, 31);


        if (rd == -1 || rs1 == -1 || imm == -1) return -1;

        uint32_t bits4to0 = (s & 0xF);

        uint32_t instruction = (funct7 << 25) + (bits4to0 << 20) + (rs1 << 15) + (funct3 << 12) + (rd << 7) + opcode;
	write_inst_hex(output, instruction);
	return 0;

}