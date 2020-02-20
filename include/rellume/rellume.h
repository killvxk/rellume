/**
 * This file is part of Rellume.
 *
 * (c) 2016-2019, Alexis Engelke <alexis.engelke@googlemail.com>
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

#ifndef RELLUME_RELLUME_H
#define RELLUME_RELLUME_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <fadec.h>
#include <llvm-c/Core.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RELLUME_API __attribute__((visibility("default")))
#define RELLUME_DEPRECATED __attribute__((deprecated))


typedef struct LLConfig LLConfig;

RELLUME_API LLConfig* ll_config_new(void);
RELLUME_API void ll_config_free(LLConfig*);

RELLUME_API void ll_config_set_hhvm(LLConfig*, bool);
RELLUME_API void ll_config_set_sptr_addrspace(LLConfig*, unsigned);
RELLUME_API void ll_config_enable_overflow_intrinsics(LLConfig*, bool);
RELLUME_API void ll_config_enable_fast_math(LLConfig*, bool);
RELLUME_API void ll_config_enable_verify_ir(LLConfig*, bool);
RELLUME_API void ll_config_set_global_base(LLConfig*, uintptr_t, LLVMValueRef);
RELLUME_API void ll_config_set_instr_impl(LLConfig*, FdInstrType, LLVMValueRef);
RELLUME_API void ll_config_set_call_ret_clobber_flags(LLConfig*, bool);
RELLUME_API void ll_config_set_use_native_segment_base(LLConfig*, bool);


typedef struct LLFunc LLFunc;

RELLUME_API LLFunc* ll_func_new(LLVMModuleRef mod, LLConfig*);

RELLUME_API void ll_func_add_inst(LLFunc* fn, uint64_t block_addr, FdInstr* instr);
RELLUME_API LLVMValueRef ll_func_lift(LLFunc* fn);
RELLUME_API void ll_func_dispose(LLFunc*);

typedef size_t(* RellumeMemAccessCb)(size_t, uint8_t*, size_t, void*);
RELLUME_API int ll_func_decode_instr(LLFunc* func, uintptr_t addr,
                                     RellumeMemAccessCb cb, void* user_arg);
RELLUME_API int ll_func_decode_block(LLFunc* func, uintptr_t addr,
                                     RellumeMemAccessCb cb, void* user_arg);
RELLUME_API int ll_func_decode_cfg(LLFunc* func, uintptr_t addr,
                                   RellumeMemAccessCb cb, void* user_arg);

RELLUME_API void ll_func_fast_opt(LLVMValueRef llvm_fn) RELLUME_DEPRECATED;
RELLUME_API LLVMValueRef ll_func_wrap_sysv(LLVMValueRef llvm_fn, LLVMTypeRef ty,
                                           LLVMModuleRef mod,
                                           size_t stack_sz) RELLUME_DEPRECATED;

#ifdef __cplusplus
}
#endif

#endif
