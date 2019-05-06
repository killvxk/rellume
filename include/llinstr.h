/**
 * This file is part of Rellume.
 *
 * (c) 2019, Alexis Engelke <alexis.engelke@googlemail.com>
 *
 * Rellume is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License (LGPL)
 * as published by the Free Software Foundation, either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * Rellume is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Rellume.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * \file
 **/

#ifndef LL_INSTR_H
#define LL_INSTR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum LLInstrType {
    LL_INS_None = 0,
    LL_INS_Invalid = 1,
#define DEF_IT(opc,...) LL_INS_ ## opc,
#include <opcodes.inc>
#undef DEF_IT
    LL_INS_Max
};


enum {
    LL_RT_None = 0,
    LL_RT_GP8Leg,
    LL_RT_GP8,
    LL_RT_GP16,
    LL_RT_GP32,
    LL_RT_GP64,
    LL_RT_IP,
    LL_RT_X87,
    LL_RT_MMX,
    LL_RT_XMM,
    LL_RT_YMM,
    LL_RT_ZMM,
    LL_RT_SEG,
    LL_RT_Max
};

// Names for register indexes. Warning: indexes for different types overlap!
enum {
    LL_RI_None = 100, // assume no register type has more than 100 regs

    // for LL_RT_GP8Leg (1st 8 from x86, but can address 16 regs in 64bit mode)
    LL_RI_A = 0, LL_RI_C, LL_RI_D, LL_RI_B, LL_RI_SP, LL_RI_BP, LL_RI_SI, LL_RI_DI,
    LL_RI_AH = 4, LL_RI_CH, LL_RI_DH, LL_RI_BH,

    LL_RI_ES = 0, LL_RI_CS, LL_RI_SS, LL_RI_DS, LL_RI_FS, LL_RI_GS,

    LL_RI_GPMax = 16,
    LL_RI_XMMMax = 16,

};

typedef enum LLInstrType LLInstrType;

typedef struct { uint16_t rt; uint16_t ri; } LLReg;

enum {
    LL_OP_NONE = 0,
    LL_OP_REG,
    LL_OP_IMM,
    LL_OP_MEM,
};

struct LLInstrOp {
    uint64_t val;
    int type;
    LLReg reg;
    LLReg ireg;
    int scale;
    int seg;
    int size;
};

typedef struct LLInstrOp LLInstrOp;

struct LLInstr {
    LLInstrType type;
    int operand_count;
    int operand_size;
    int address_size;
    LLInstrOp dst;
    LLInstrOp src;
    LLInstrOp src2;

    uintptr_t addr;
    int len;
};

typedef struct LLInstr LLInstr;

#ifdef __cplusplus
}
#endif

#endif
