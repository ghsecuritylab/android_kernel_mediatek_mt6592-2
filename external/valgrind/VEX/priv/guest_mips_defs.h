

/*
   This file is part of Valgrind, a dynamic binary instrumentation
   framework.

   Copyright (C) 2010-2013 RT-RK
      mips-valgrind@rt-rk.com

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307, USA.

   The GNU General Public License is contained in the file COPYING.
*/


#ifndef __VEX_GUEST_MIPS_DEFS_H
#define __VEX_GUEST_MIPS_DEFS_H

#include "libvex_basictypes.h"
#include "guest_generic_bb_to_IR.h"  


extern DisResult disInstr_MIPS ( IRSB*        irbb,
                                 Bool         (*resteerOkFn) (void *, Addr),
                                 Bool         resteerCisOk,
                                 void*        callback_opaque,
                                 const UChar* guest_code,
                                 Long         delta,
                                 Addr         guest_IP,
                                 VexArch      guest_arch,
                                 const VexArchInfo* archinfo,
                                 const VexAbiInfo*  abiinfo,
                                 VexEndness   host_endness,
                                 Bool         sigill_diag );

extern IRExpr *guest_mips32_spechelper ( const HChar * function_name,
                                         IRExpr ** args,
                                         IRStmt ** precedingStmts,
                                         Int n_precedingStmts );

extern IRExpr *guest_mips64_spechelper ( const HChar * function_name,
                                         IRExpr ** args,
                                         IRStmt ** precedingStmts,
                                         Int n_precedingStmts);

extern
Bool guest_mips32_state_requires_precise_mem_exns ( Int, Int,
                                                    VexRegisterUpdates );

extern
Bool guest_mips64_state_requires_precise_mem_exns ( Int, Int,
                                                    VexRegisterUpdates );

extern VexGuestLayout mips32Guest_layout;
extern VexGuestLayout mips64Guest_layout;

typedef enum {
   CEILWS=0, CEILWD,  CEILLS,  CEILLD,
   FLOORWS,  FLOORWD, FLOORLS, FLOORLD,
   ROUNDWS,  ROUNDWD, ROUNDLS, ROUNDLD,
   TRUNCWS,  TRUNCWD, TRUNCLS, TRUNCLD,
   CVTDS,    CVTDW,   CVTSD,   CVTSW,
   CVTWS,    CVTWD,   CVTDL,   CVTLS,
   CVTLD,    CVTSL,   ADDS,    ADDD,
   SUBS,     SUBD,    DIVS
} flt_op;

extern UInt mips32_dirtyhelper_mfc0 ( UInt rd, UInt sel );

extern ULong mips64_dirtyhelper_dmfc0 ( UInt rd, UInt sel );


#if defined(__mips__) && ((defined(__mips_isa_rev) && __mips_isa_rev >= 2))
extern UInt mips32_dirtyhelper_rdhwr ( UInt rt, UInt rd );
extern ULong mips64_dirtyhelper_rdhwr ( ULong rt, ULong rd );
#endif

extern UInt mips_dirtyhelper_calculate_FCSR_fp32 ( void* guest_state, UInt fs,
                                                   UInt ft, flt_op op );
extern UInt mips_dirtyhelper_calculate_FCSR_fp64 ( void* guest_state, UInt fs,
                                                   UInt ft, flt_op op );


typedef enum {
   MIPSCondEQ = 0,   
   MIPSCondNE = 1,   

   MIPSCondHS = 2,   
   MIPSCondLO = 3,   

   MIPSCondMI = 4,   
   MIPSCondPL = 5,   

   MIPSCondVS = 6,   
   MIPSCondVC = 7,   

   MIPSCondHI = 8,   
   MIPSCondLS = 9,   

   MIPSCondGE = 10,  
   MIPSCondLT = 11,  

   MIPSCondGT = 12,  
   MIPSCondLE = 13,  

   MIPSCondAL = 14,  
   MIPSCondNV = 15   
} MIPSCondcode;

#endif            
