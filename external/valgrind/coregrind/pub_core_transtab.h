

/*
   This file is part of Valgrind, a dynamic binary instrumentation
   framework.

   Copyright (C) 2000-2013 Julian Seward
      jseward@acm.org

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

#ifndef __PUB_CORE_TRANSTAB_H
#define __PUB_CORE_TRANSTAB_H


#include "pub_core_transtab_asm.h"
#include "pub_tool_transtab.h"
#include "libvex.h"                   

typedef
   struct { 
      Addr guest;
      Addr host;
   }
   FastCacheEntry;

extern __attribute__((aligned(16)))
       FastCacheEntry VG_(tt_fast) [VG_TT_FAST_SIZE];

#define TRANSTAB_BOGUS_GUEST_ADDR ((Addr)1)


extern void VG_(init_tt_tc)       ( void );


 
#define MIN_N_SECTORS 2
#define MAX_N_SECTORS 24

#if defined(VGPV_arm_linux_android) \
    || defined(VGPV_x86_linux_android) \
    || defined(VGPV_mips32_linux_android) \
    || defined(VGPV_arm64_linux_android)
# define N_SECTORS_DEFAULT 6
#else
# define N_SECTORS_DEFAULT 16
#endif

extern
void VG_(add_to_transtab)( const VexGuestExtents* vge,
                           Addr             entry,
                           Addr             code,
                           UInt             code_len,
                           Bool             is_self_checking,
                           Int              offs_profInc,
                           UInt             n_guest_instrs );

typedef UShort SECno; 
typedef UShort TTEno; 

#define INV_SNO ((SECno)0xFFFF)
#define INV_TTE ((TTEno)0xFFFF)

extern
void VG_(tt_tc_do_chaining) ( void* from__patch_addr,
                              SECno to_sNo,
                              TTEno to_tteNo,
                              Bool  to_fastEP );

extern Bool VG_(search_transtab) ( Addr*  res_hcode,
                                   SECno* res_sNo,
                                   TTEno* res_tteNo,
                                   Addr          guest_addr, 
                                   Bool          upd_cache );

extern void VG_(discard_translations) ( Addr  start, ULong range,
                                        const HChar* who );

extern void VG_(print_tt_tc_stats) ( void );

extern UInt VG_(get_bbs_translated) ( void );


extern
void VG_(add_to_unredir_transtab)( const VexGuestExtents* vge,
                                   Addr             entry,
                                   Addr             code,
                                   UInt             code_len );
extern 
Bool VG_(search_unredir_transtab) ( Addr*  result,
                                    Addr          guest_addr );


typedef struct _SBProfEntry {
   Addr   addr;
   ULong  score;
} SBProfEntry;

extern ULong VG_(get_SB_profile) ( SBProfEntry tops[], UInt n_tops );

extern Bool  VG_(ok_to_discard_translations);

#endif   

