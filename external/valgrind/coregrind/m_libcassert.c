
 
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

#include "pub_core_basics.h"
#include "pub_core_vki.h"
#include "pub_core_vkiscnums.h"
#include "pub_core_threadstate.h"
#include "pub_core_gdbserver.h"
#include "pub_core_aspacemgr.h"
#include "pub_core_libcbase.h"
#include "pub_core_libcassert.h"
#include "pub_core_libcprint.h"
#include "pub_core_libcproc.h"      
#include "pub_core_machine.h"
#include "pub_core_stacks.h"
#include "pub_core_stacktrace.h"
#include "pub_core_syscall.h"
#include "pub_core_tooliface.h"     
#include "pub_core_options.h"       


#if defined(VGP_x86_linux) || defined(VGP_x86_darwin)
#  define GET_STARTREGS(srP)                              \
      { UInt eip, esp, ebp;                               \
        __asm__ __volatile__(                             \
           "call 0f;"                                     \
           "0: popl %0;"                                  \
           "movl %%esp, %1;"                              \
           "movl %%ebp, %2;"                              \
           : "=r" (eip), "=r" (esp), "=r" (ebp)           \
           :                              \
           : "memory"                                     \
        );                                                \
        (srP)->r_pc = (ULong)eip;                         \
        (srP)->r_sp = (ULong)esp;                         \
        (srP)->misc.X86.r_ebp = ebp;                      \
      }
#elif defined(VGP_amd64_linux) || defined(VGP_amd64_darwin)
#  define GET_STARTREGS(srP)                              \
      { ULong rip, rsp, rbp;                              \
        __asm__ __volatile__(                             \
           "leaq 0(%%rip), %0;"                           \
           "movq %%rsp, %1;"                              \
           "movq %%rbp, %2;"                              \
           : "=r" (rip), "=r" (rsp), "=r" (rbp)           \
           :                              \
           : "memory"                                     \
        );                                                \
        (srP)->r_pc = rip;                                \
        (srP)->r_sp = rsp;                                \
        (srP)->misc.AMD64.r_rbp = rbp;                    \
      }
#elif defined(VGP_ppc32_linux)
#  define GET_STARTREGS(srP)                              \
      { UInt cia, r1, lr;                                 \
        __asm__ __volatile__(                             \
           "mflr 0;"                         \
           "bl m_libcassert_get_ip;"         \
           "m_libcassert_get_ip:\n"                       \
           "mflr %0;"                        \
           "mtlr 0;"                      \
           "mr %1,1;"                        \
           "mr %2,0;"                        \
           : "=r" (cia), "=r" (r1), "=r" (lr)             \
           :                              \
           : "r0"                            \
        );                                                \
        (srP)->r_pc = (ULong)cia;                         \
        (srP)->r_sp = (ULong)r1;                          \
        (srP)->misc.PPC32.r_lr = lr;                      \
      }
#elif defined(VGP_ppc64be_linux) || defined(VGP_ppc64le_linux)
#  define GET_STARTREGS(srP)                              \
      { ULong cia, r1, lr;                                \
        __asm__ __volatile__(                             \
           "mflr 0;"                         \
           "bl .m_libcassert_get_ip;"        \
           ".m_libcassert_get_ip:\n"                      \
           "mflr %0;"                        \
           "mtlr 0;"                      \
           "mr %1,1;"                        \
           "mr %2,0;"                        \
           : "=r" (cia), "=r" (r1), "=r" (lr)             \
           :                              \
           : "r0"                            \
        );                                                \
        (srP)->r_pc = cia;                                \
        (srP)->r_sp = r1;                                 \
        (srP)->misc.PPC64.r_lr = lr;                      \
      }
#elif defined(VGP_arm_linux)
#  define GET_STARTREGS(srP)                              \
      { UInt block[6];                                    \
        __asm__ __volatile__(                             \
           "str r15, [%0, #+0];"                          \
           "str r14, [%0, #+4];"                          \
           "str r13, [%0, #+8];"                          \
           "str r12, [%0, #+12];"                         \
           "str r11, [%0, #+16];"                         \
           "str r7,  [%0, #+20];"                         \
           :                                     \
           :  "r"(&block[0])                      \
           :  "memory"                         \
        );                                                \
        (srP)->r_pc = block[0] - 8;                       \
        (srP)->misc.ARM.r14 = block[1];                   \
        (srP)->r_sp = block[2];                           \
        (srP)->misc.ARM.r12 = block[3];                   \
        (srP)->misc.ARM.r11 = block[4];                   \
        (srP)->misc.ARM.r7  = block[5];                   \
      }
#elif defined(VGP_arm64_linux)
#  define GET_STARTREGS(srP)                              \
      { ULong block[4];                                   \
        __asm__ __volatile__(                             \
           "adr x19, 0;"                                  \
           "str x19, [%0, #+0];"                  \
           "mov x19, sp;"                                 \
           "str x19, [%0, #+8];"                  \
           "str x29, [%0, #+16];"                 \
           "str x30, [%0, #+24];"                 \
           :                                     \
           :  "r"(&block[0])                      \
           :  "memory","x19"                   \
        );                                                \
        (srP)->r_pc = block[0];                           \
        (srP)->r_sp = block[1];                           \
        (srP)->misc.ARM64.x29 = block[2];                 \
        (srP)->misc.ARM64.x30 = block[3];                 \
      }
#elif defined(VGP_s390x_linux)
#  define GET_STARTREGS(srP)                              \
      { ULong ia, sp, fp, lr;                             \
        __asm__ __volatile__(                             \
           "bras %0,0f;"                                  \
           "0: lgr %1,15;"                                \
           "lgr %2,11;"                                   \
           "lgr %3,14;"                                   \
           : "=r" (ia), "=r" (sp),"=r" (fp),"=r" (lr)     \
                                   \
        );                                                \
        (srP)->r_pc = ia;                                 \
        (srP)->r_sp = sp;                                 \
        (srP)->misc.S390X.r_fp = fp;                      \
        (srP)->misc.S390X.r_lr = lr;                      \
      }
#elif defined(VGP_mips32_linux)
#  define GET_STARTREGS(srP)                              \
      { UInt pc, sp, fp, ra, gp;                          \
      asm("move $8, $31;"                    \
          "bal m_libcassert_get_ip;"         \
          "m_libcassert_get_ip:\n"                        \
          "move %0, $31;"                                 \
          "move $31, $8;"                 \
          "move %1, $29;"                                 \
          "move %2, $30;"                                 \
          "move %3, $31;"                                 \
          "move %4, $28;"                                 \
          : "=r" (pc),                                    \
            "=r" (sp),                                    \
            "=r" (fp),                                    \
            "=r" (ra),                                    \
            "=r" (gp)                                     \
          :                               \
          : "$8"  );                         \
        (srP)->r_pc = (ULong)pc - 8;                      \
        (srP)->r_sp = (ULong)sp;                          \
        (srP)->misc.MIPS32.r30 = (ULong)fp;               \
        (srP)->misc.MIPS32.r31 = (ULong)ra;               \
        (srP)->misc.MIPS32.r28 = (ULong)gp;               \
      }
#elif defined(VGP_mips64_linux)
#  define GET_STARTREGS(srP)                              \
      { ULong pc, sp, fp, ra, gp;                          \
      asm("move $8, $31;"                    \
          "bal m_libcassert_get_ip;"         \
          "m_libcassert_get_ip:\n"                        \
          "move %0, $31;"                                 \
          "move $31, $8;"                 \
          "move %1, $29;"                                 \
          "move %2, $30;"                                 \
          "move %3, $31;"                                 \
          "move %4, $28;"                                 \
          : "=r" (pc),                                    \
            "=r" (sp),                                    \
            "=r" (fp),                                    \
            "=r" (ra),                                    \
            "=r" (gp)                                     \
          :                               \
          : "$8"  );                         \
        (srP)->r_pc = (ULong)pc - 8;                      \
        (srP)->r_sp = (ULong)sp;                          \
        (srP)->misc.MIPS64.r30 = (ULong)fp;               \
        (srP)->misc.MIPS64.r31 = (ULong)ra;               \
        (srP)->misc.MIPS64.r28 = (ULong)gp;               \
      }
#elif defined(VGP_tilegx_linux)
#  define GET_STARTREGS(srP)                              \
      { ULong pc, sp, fp, ra;                              \
        __asm__ __volatile__(                             \
          "move r8, lr \n"                                \
          "jal 0f \n"                                     \
          "0:\n"                                          \
          "move %0, lr \n"                                \
          "move lr, r8 \n"            \
          "move %1, sp \n"                                \
          "move %2, r52 \n"                               \
          "move %3, lr \n"                                \
          : "=r" (pc),                                    \
            "=r" (sp),                                    \
            "=r" (fp),                                    \
            "=r" (ra)                                     \
          :                               \
          : "%r8"  );                        \
        (srP)->r_pc = (ULong)pc - 8;                      \
        (srP)->r_sp = (ULong)sp;                          \
        (srP)->misc.TILEGX.r52 = (ULong)fp;               \
        (srP)->misc.TILEGX.r55 = (ULong)ra;               \
      }
#else
#  error Unknown platform
#endif

#define BACKTRACE_DEPTH    100         

__attribute__ ((__noreturn__))
static void exit_wrk( Int status, Bool gdbserver_call_allowed)
{
   static Bool exit_called = False;
   

   if (gdbserver_call_allowed && !exit_called) {
      const ThreadId atid = 1; 
      exit_called = True;
      if (status != 0 && VG_(gdbserver_stop_at) (VgdbStopAt_ValgrindAbExit)) {
         if (VG_(gdbserver_init_done)()) {
            VG_(umsg)("(action at valgrind abnormal exit) vgdb me ... \n");
            VG_(gdbserver) (atid);
         } else {
            VG_(umsg)("(action at valgrind abnormal exit) "
                      "Early valgrind exit : vgdb not yet usable\n");
         }
      }
      if (VG_(gdbserver_init_done)()) {
         
         
         VG_(gdbserver_exit) (atid,
                              status == 0 ? VgSrc_ExitProcess : VgSrc_FatalSig);
      }
   }
   exit_called = True;

   VG_(exit_now) (status);
}

__attribute__ ((__noreturn__))
void VG_(exit_now)( Int status )
{
#if defined(VGO_linux)
   (void)VG_(do_syscall1)(__NR_exit_group, status );
#elif defined(VGO_darwin)
   (void)VG_(do_syscall1)(__NR_exit, status );
#else
#  error Unknown OS
#endif
   
   
   
   __builtin_trap();
   *(volatile Int*)0 = 'x';
}

void VG_(exit)( Int status )
{
   exit_wrk (status, True);
}

void VG_(client_exit)( Int status )
{
   exit_wrk (status, False);
}


static void show_sched_status_wrk ( Bool host_stacktrace,
                                    Bool stack_usage,
                                    Bool exited_threads,
                                    const UnwindStartRegs* startRegsIN)
{
   Int i; 
   if (host_stacktrace) {
      const Bool save_clo_xml = VG_(clo_xml);
      Addr stacktop;
      Addr ips[BACKTRACE_DEPTH];
      Int  n_ips;
      ThreadState *tst 
         = VG_(get_ThreadState)( VG_(lwpid_to_vgtid)( VG_(gettid)() ) );
 
      
      
      
      UnwindStartRegs startRegs;
      VG_(memset)(&startRegs, 0, sizeof(startRegs));
      
      if (startRegsIN == NULL) {
         GET_STARTREGS(&startRegs);
      } else {
         startRegs = *startRegsIN;
      }
 
      stacktop = tst->os_state.valgrind_stack_init_SP;

      n_ips = 
         VG_(get_StackTrace_wrk)(
            0, 
            ips, BACKTRACE_DEPTH, 
            NULL,
            NULL,
            &startRegs, stacktop
         );
      VG_(printf)("\nhost stacktrace:\n"); 
      VG_(clo_xml) = False;
      VG_(pp_StackTrace) (ips, n_ips);
      VG_(clo_xml) = save_clo_xml;
   }

   VG_(printf)("\nsched status:\n"); 
   VG_(printf)("  running_tid=%d\n", VG_(get_running_tid)());
   for (i = 1; i < VG_N_THREADS; i++) {
      VgStack* stack 
         = (VgStack*)VG_(threads)[i].os_state.valgrind_stack_base;
      if (VG_(threads)[i].status == VgTs_Empty
          && (!exited_threads || stack == 0)) continue;
      VG_(printf)("\nThread %d: status = %s (lwpid %d)\n", i, 
                  VG_(name_of_ThreadStatus)(VG_(threads)[i].status),
                  VG_(threads)[i].os_state.lwpid);
      if (VG_(threads)[i].status != VgTs_Empty)
         VG_(get_and_pp_StackTrace)( i, BACKTRACE_DEPTH );
      if (stack_usage && VG_(threads)[i].client_stack_highest_byte != 0 ) {
         Addr start, end;
         
         start = end = 0;
         VG_(stack_limits)(VG_(threads)[i].client_stack_highest_byte,
                           &start, &end);
         if (start != end)
            VG_(printf)("client stack range: [%p %p] client SP: %p\n",
                        (void*)start, (void*)end, (void*)VG_(get_SP)(i));
         else
            VG_(printf)("client stack range: ???????\n");
      }
      if (stack_usage && stack != 0)
          VG_(printf)("valgrind stack top usage: %ld of %ld\n",
                      VG_(clo_valgrind_stacksize)
                        - VG_(am_get_VgStack_unused_szB)
                               (stack, VG_(clo_valgrind_stacksize)),
                      (SizeT) VG_(clo_valgrind_stacksize));
   }
   VG_(printf)("\n");
}

void VG_(show_sched_status) ( Bool host_stacktrace,
                              Bool stack_usage,
                              Bool exited_threads)
{
   show_sched_status_wrk (host_stacktrace,
                          stack_usage,
                          exited_threads,
                          NULL);
}

__attribute__ ((noreturn))
static void report_and_quit ( const HChar* report,
                              const UnwindStartRegs* startRegsIN )
{
   show_sched_status_wrk (True,  
                          False, 
                          False, 
                          startRegsIN);
   VG_(printf)(
      "\n"
      "Note: see also the FAQ in the source distribution.\n"
      "It contains workarounds to several common problems.\n"
      "In particular, if Valgrind aborted or crashed after\n"
      "identifying problems in your program, there's a good chance\n"
      "that fixing those problems will prevent Valgrind aborting or\n"
      "crashing, especially if it happened in m_mallocfree.c.\n"
      "\n"
      "If that doesn't help, please report this bug to: %s\n\n"
      "In the bug report, send all the above text, the valgrind\n"
      "version, and what OS and version you are using.  Thanks.\n\n",
      report);
   VG_(exit)(1);
}

void VG_(assert_fail) ( Bool isCore, const HChar* expr, const HChar* file, 
                        Int line, const HChar* fn, const HChar* format, ... )
{
   va_list vargs, vargs_copy;
   const HChar* component;
   const HChar* bugs_to;
   UInt written;

   static Bool entered = False;
   if (entered) 
      VG_(exit)(2);
   entered = True;

   if (isCore) {
      component = "valgrind";
      bugs_to   = VG_BUGS_TO;
   } else { 
      component = VG_(details).name;
      bugs_to   = VG_(details).bug_reports_to;
   }

   if (VG_(clo_xml))
      VG_(printf_xml)("</valgrindoutput>\n");

   
   if (VG_STREQ(expr, "0")) {
      VG_(printf)("\n%s: %s:%d (%s): the 'impossible' happened.\n",
                  component, file, line, fn );
   } else {
      VG_(printf)("\n%s: %s:%d (%s): Assertion '%s' failed.\n",
                  component, file, line, fn, expr );
   }

   /* Check whether anything will be written */
   HChar buf[5];
   va_start(vargs, format);
   va_copy(vargs_copy, vargs);
   written = VG_(vsnprintf) ( buf, sizeof(buf), format, vargs );
   va_end(vargs);

   if (written > 0) {
      VG_(printf)("%s: ", component);
      VG_(vprintf)(format, vargs_copy);
      VG_(printf)("\n");
   }

   report_and_quit(bugs_to, NULL);
}

__attribute__ ((noreturn))
static void panic ( const HChar* name, const HChar* report, const HChar* str,
                    const UnwindStartRegs* startRegs )
{
   if (VG_(clo_xml))
      VG_(printf_xml)("</valgrindoutput>\n");
   VG_(printf)("\n%s: the 'impossible' happened:\n   %s\n", name, str);
   report_and_quit(report, startRegs);
}

void VG_(core_panic_at) ( const HChar* str, const UnwindStartRegs* startRegs )
{
   panic("valgrind", VG_BUGS_TO, str, startRegs);
}

void VG_(core_panic) ( const HChar* str )
{
   VG_(core_panic_at)(str, NULL);
}

void VG_(tool_panic) ( const HChar* str )
{
   panic(VG_(details).name, VG_(details).bug_reports_to, str, NULL);
}

void VG_(unimplemented) ( const HChar* msg )
{
   if (VG_(clo_xml))
      VG_(printf_xml)("</valgrindoutput>\n");
   VG_(umsg)("\n");
   VG_(umsg)("Valgrind detected that your program requires\n");
   VG_(umsg)("the following unimplemented functionality:\n");
   VG_(umsg)("   %s\n", msg);
   VG_(umsg)("This may be because the functionality is hard to implement,\n");
   VG_(umsg)("or because no reasonable program would behave this way,\n");
   VG_(umsg)("or because nobody has yet needed it.  "
             "In any case, let us know at\n");
   VG_(umsg)("%s and/or try to work around the problem, if you can.\n",
             VG_BUGS_TO);
   VG_(umsg)("\n");
   VG_(umsg)("Valgrind has to exit now.  Sorry.  Bye!\n");
   VG_(umsg)("\n");
   VG_(show_sched_status)(False,  
                          False,  
                          False); 
   VG_(exit)(1);
}

