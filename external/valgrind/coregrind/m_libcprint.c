
 
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
#include "pub_core_debuglog.h"
#include "pub_core_gdbserver.h"  
#include "pub_core_libcbase.h"
#include "pub_core_libcassert.h"
#include "pub_core_libcfile.h"   
#include "pub_core_libcprint.h"
#include "pub_core_libcproc.h"   
#include "pub_core_mallocfree.h" 
#include "pub_core_options.h"
#include "pub_core_clreq.h"      



OutputSink VG_(log_output_sink) = {  2, False }; 
OutputSink VG_(xml_output_sink) = { -1, False }; 
 
static
void send_bytes_to_logging_sink ( OutputSink* sink, const HChar* msg, Int nbytes )
{
   if (sink->is_socket) {
      Int rc = VG_(write_socket)( sink->fd, msg, nbytes );
      if (rc == -1) {
         
         sink->is_socket = False;
         sink->fd = 2;
         VG_(write)( sink->fd, msg, nbytes );
      }
   } else {
      if (sink->fd >= 0)
         VG_(write)( sink->fd, msg, nbytes );
      else if (sink->fd == -2 && nbytes > 0)
         VG_(gdb_printf)("%s", msg);
   }
}




typedef 
   struct {
      HChar       buf[512];
      Int         buf_used;
      OutputSink* sink;
   } 
   printf_buf_t;

static void add_to__printf_buf ( HChar c, void *p )
{
   printf_buf_t *b = (printf_buf_t *)p;
   
   if (b->buf_used > sizeof(b->buf) - 2 ) {
      send_bytes_to_logging_sink( b->sink, b->buf, b->buf_used );
      b->buf_used = 0;
   }
   b->buf[b->buf_used++] = c;
   b->buf[b->buf_used]   = 0;
   vg_assert(b->buf_used < sizeof(b->buf));
}

static UInt vprintf_to_buf ( printf_buf_t* b,
                             const HChar *format, va_list vargs )
{
   UInt ret = 0;
   if (b->sink->fd >= 0 || b->sink->fd == -2) {
      ret = VG_(debugLog_vprintf) 
               ( add_to__printf_buf, b, format, vargs );
   }
   return ret;
}

static UInt vprintf_WRK ( OutputSink* sink,
                          const HChar *format, va_list vargs )
{
   printf_buf_t myprintf_buf
      = { "", 0, sink };
   UInt ret
      = vprintf_to_buf(&myprintf_buf, format, vargs);
   
   if (myprintf_buf.buf_used > 0) {
      send_bytes_to_logging_sink( myprintf_buf.sink,
                                  myprintf_buf.buf,
                                  myprintf_buf.buf_used );
   }
   return ret;
}

UInt VG_(vprintf) ( const HChar *format, va_list vargs )
{
   return vprintf_WRK( &VG_(log_output_sink), format, vargs );
}

UInt VG_(printf) ( const HChar *format, ... )
{
   UInt ret;
   va_list vargs;
   va_start(vargs, format);
   ret = VG_(vprintf)(format, vargs);
   va_end(vargs);
   return ret;
}

UInt VG_(vprintf_xml) ( const HChar *format, va_list vargs )
{
   return vprintf_WRK( &VG_(xml_output_sink), format, vargs );
}

UInt VG_(printf_xml) ( const HChar *format, ... )
{
   UInt ret;
   va_list vargs;
   va_start(vargs, format);
   ret = VG_(vprintf_xml)(format, vargs);
   va_end(vargs);
   return ret;
}

static UInt emit_WRK ( const HChar* format, va_list vargs )
{
   if (VG_(clo_xml)) {
      return VG_(vprintf_xml)(format, vargs);
   } else if (VG_(log_output_sink).fd == -2) {
      return VG_(vprintf) (format, vargs);
   } else {
      return VG_(vmessage)(Vg_UserMsg, format, vargs);
   }
}
UInt VG_(emit) ( const HChar* format, ... )
{
   UInt ret;
   va_list vargs;
   va_start(vargs, format);
   ret = emit_WRK(format, vargs);
   va_end(vargs);
   return ret;
}



static void add_to__sprintf_buf ( HChar c, void *p )
{
   HChar** b = p;
   *(*b)++ = c;
}

UInt VG_(vsprintf) ( HChar* buf, const HChar *format, va_list vargs )
{
   Int ret;
   HChar* sprintf_ptr = buf;

   ret = VG_(debugLog_vprintf) 
            ( add_to__sprintf_buf, &sprintf_ptr, format, vargs );
   add_to__sprintf_buf('\0', &sprintf_ptr);

   vg_assert(VG_(strlen)(buf) == ret);

   return ret;
}

UInt VG_(sprintf) ( HChar* buf, const HChar *format, ... )
{
   UInt ret;
   va_list vargs;
   va_start(vargs,format);
   ret = VG_(vsprintf)(buf, format, vargs);
   va_end(vargs);
   return ret;
}



/* The return value of VG_(snprintf) and VG_(vsnprintf) differs from
   what is defined in C99. Let S be the size of the buffer as given in
   the 2nd argument.
   Return value R:
     R < S:  The output string was successfully written to the buffer.
             It is null-terminated and R == strlen( output string )
     R == S: The supplied buffer was too small to hold the output string.
             The first S-1 characters of the output string were written
             to the buffer followed by the terminating null character.
*/

typedef 
   struct {
      HChar* buf;
      Int    buf_size;
      Int    buf_used;
   } 
   snprintf_buf_t;

static void add_to__snprintf_buf ( HChar c, void* p )
{
   snprintf_buf_t* b = p;
   if (b->buf_size > 0 && b->buf_used < b->buf_size) {
      b->buf[b->buf_used++] = c;
      if (b->buf_used < b->buf_size)
         b->buf[b->buf_used] = 0;
      else
         b->buf[b->buf_size-1] = 0; 
   } 
}

UInt VG_(vsnprintf) ( HChar* buf, Int size, const HChar *format, va_list vargs )
{
   snprintf_buf_t b;
   b.buf      = buf;
   b.buf_size = size < 0 ? 0 : size;
   b.buf_used = 0;
   if (b.buf_size > 0)
      b.buf[0] = 0; 
   (void) VG_(debugLog_vprintf) 
             ( add_to__snprintf_buf, &b, format, vargs );

   return b.buf_used;
}

UInt VG_(snprintf) ( HChar* buf, Int size, const HChar *format, ... )
{
   UInt ret;
   va_list vargs;
   va_start(vargs,format);
   ret = VG_(vsnprintf)(buf, size, format, vargs);
   va_end(vargs);
   return ret;
}



void VG_(vcbprintf)( void(*char_sink)(HChar, void* opaque),
                     void* opaque,
                     const HChar* format, va_list vargs )
{
   (void) VG_(debugLog_vprintf)
             ( char_sink, opaque, format, vargs );
}




#define VGFILE_BUFSIZE  8192

struct _VgFile {
   HChar buf[VGFILE_BUFSIZE];
   UInt  num_chars;   
   Int   fd;          
};


static void add_to__vgfile ( HChar c, void *p )
{
   VgFile *fp = p;

   fp->buf[fp->num_chars++] = c;

   if (fp->num_chars == VGFILE_BUFSIZE) {
      VG_(write)(fp->fd, fp->buf, fp->num_chars);
      fp->num_chars = 0;
   }
}

VgFile *VG_(fopen)(const HChar *name, Int flags, Int mode)
{
   SysRes res = VG_(open)(name, flags, mode);

   if (sr_isError(res))
      return NULL;

   VgFile *fp = VG_(malloc)("fopen", sizeof(VgFile));

   fp->fd = sr_Res(res);
   fp->num_chars = 0;

   return fp;
}


UInt VG_(vfprintf) ( VgFile *fp, const HChar *format, va_list vargs )
{
   return VG_(debugLog_vprintf)(add_to__vgfile, fp, format, vargs);
}

UInt VG_(fprintf) ( VgFile *fp, const HChar *format, ... )
{
   UInt ret;
   va_list vargs;
   va_start(vargs,format);
   ret = VG_(vfprintf)(fp, format, vargs);
   va_end(vargs);
   return ret;
}

void VG_(fclose)( VgFile *fp )
{
   
   if (fp->num_chars)
      VG_(write)(fp->fd, fp->buf, fp->num_chars);

   VG_(free)(fp);
}




void VG_(elapsed_wallclock_time) ( HChar* buf, SizeT bufsize )
{
   UInt t, ms, s, mins, hours, days;

   vg_assert(bufsize > 20);

   t  = VG_(read_millisecond_timer)(); 

   ms = t % 1000;
   t /= 1000; 

   s = t % 60;
   t /= 60; 

   mins = t % 60;
   t /= 60; 

   hours = t % 24;
   t /= 24; 

   days = t;

   VG_(sprintf)(buf, "%02u:%02u:%02u:%02u.%03u ", days, hours, mins, s, ms);
}



typedef 
   struct {
      HChar buf[512+128];
      Int   buf_used;
      Bool  atLeft; 
      
      VgMsgKind kind;
      
      OutputSink* sink;
   } 
   vmessage_buf_t;

static vmessage_buf_t vmessage_buf
   = { "", 0, True, Vg_UserMsg, &VG_(log_output_sink) };


static void add_to__vmessage_buf ( HChar c, void *p )
{
   HChar tmp[64];
   vmessage_buf_t* b = (vmessage_buf_t*)p;

   vg_assert(b->buf_used >= 0 && b->buf_used < sizeof(b->buf)-128);

   if (UNLIKELY(b->atLeft)) {
      
      HChar ch;
      Int   i, depth;

      
      
      
      
      
      depth = RUNNING_ON_VALGRIND;
      if (depth > 0 
          && !SimHintiS(SimHint_no_inner_prefix, VG_(clo_sim_hints))) {
         if (depth > 10)
            depth = 10; 
         for (i = 0; i < depth; i++) {
            b->buf[b->buf_used++] = '>';
         }
      }

      if (Vg_FailMsg == b->kind) {
         
         b->buf[b->buf_used++] = 'v';
         b->buf[b->buf_used++] = 'a';
         b->buf[b->buf_used++] = 'l';
         b->buf[b->buf_used++] = 'g';
         b->buf[b->buf_used++] = 'r';
         b->buf[b->buf_used++] = 'i';
         b->buf[b->buf_used++] = 'n';
         b->buf[b->buf_used++] = 'd';
         b->buf[b->buf_used++] = ':';
         b->buf[b->buf_used++] = ' ';
      } else {
         switch (b->kind) {
            case Vg_UserMsg:       ch = '='; break;
            case Vg_DebugMsg:      ch = '-'; break;
            case Vg_ClientMsg:     ch = '*'; break;
            default:               ch = '?'; break;
         }

         b->buf[b->buf_used++] = ch;
         b->buf[b->buf_used++] = ch;

         if (VG_(clo_time_stamp)) {
            VG_(elapsed_wallclock_time)(tmp, sizeof tmp);
            for (i = 0; tmp[i]; i++)
               b->buf[b->buf_used++] = tmp[i];
         }

         VG_(sprintf)(tmp, "%d", VG_(getpid)());
         tmp[sizeof(tmp)-1] = 0;
         for (i = 0; tmp[i]; i++)
            b->buf[b->buf_used++] = tmp[i];

         b->buf[b->buf_used++] = ch;
         b->buf[b->buf_used++] = ch;
         b->buf[b->buf_used++] = ' ';
      }

      vg_assert(b->buf_used < sizeof(b->buf)-32);
   }

   b->buf[b->buf_used++] = c;
   b->buf[b->buf_used]   = 0;
   
   if (b->buf_used >= sizeof(b->buf) - 128) {
      send_bytes_to_logging_sink( b->sink, b->buf, b->buf_used );
      b->buf_used = 0;
   }

   b->atLeft = c == '\n';
}


UInt VG_(vmessage) ( VgMsgKind kind, const HChar* format, va_list vargs )
{
   UInt ret;

   vmessage_buf_t* b = &vmessage_buf; 

   b->kind = kind;

   ret = VG_(debugLog_vprintf) ( add_to__vmessage_buf,
                                 b, format, vargs );


   if (b->atLeft && b->buf_used > 0) {
      send_bytes_to_logging_sink( b->sink, b->buf, b->buf_used );
      b->buf_used = 0;
   }

   return ret;
}

UInt VG_(message) ( VgMsgKind kind, const HChar* format, ... )
{
   UInt count;
   va_list vargs;
   va_start(vargs,format);
   count = VG_(vmessage) ( kind, format, vargs );
   va_end(vargs);
   return count;
}

static void revert_to_stderr ( void )
{
   VG_(log_output_sink).fd = 2; 
   VG_(log_output_sink).is_socket = False;
}


UInt VG_(fmsg) ( const HChar* format, ... )
{
   UInt count;
   va_list vargs;
   va_start(vargs,format);
   count = VG_(vmessage) ( Vg_FailMsg, format, vargs );
   va_end(vargs);
   return count;
}

void VG_(fmsg_bad_option) ( const HChar* opt, const HChar* format, ... )
{
   va_list vargs;
   va_start(vargs,format);
   revert_to_stderr();
   VG_(message) (Vg_FailMsg, "Bad option: %s\n", opt);
   VG_(vmessage)(Vg_FailMsg, format, vargs );
   VG_(message) (Vg_FailMsg, "Use --help for more information or consult the user manual.\n");
   va_end(vargs);
   VG_(exit)(1);
}

void VG_(fmsg_unknown_option) ( const HChar* opt)
{
   revert_to_stderr();
   VG_(message) (Vg_FailMsg, "Unknown option: %s\n", opt);
   VG_(message) (Vg_FailMsg, "Use --help for more information or consult the user manual.\n");
   VG_(exit)(1);
}

UInt VG_(umsg) ( const HChar* format, ... )
{
   UInt count;
   va_list vargs;
   va_start(vargs,format);
   count = VG_(vmessage) ( Vg_UserMsg, format, vargs );
   va_end(vargs);
   return count;
}

UInt VG_(dmsg) ( const HChar* format, ... )
{
   UInt count;
   va_list vargs;
   va_start(vargs,format);
   count = VG_(vmessage) ( Vg_DebugMsg, format, vargs );
   va_end(vargs);
   return count;
}

void VG_(message_flush) ( void )
{
   vmessage_buf_t* b = &vmessage_buf;
   send_bytes_to_logging_sink( b->sink, b->buf, b->buf_used );
   b->buf_used = 0;
}

__attribute__((noreturn))
void VG_(err_missing_prog) ( void  )
{
   revert_to_stderr();
   VG_(fmsg)("no program specified\n");
   VG_(fmsg)("Use --help for more information.\n");
   VG_(exit)(1);
}

__attribute__((noreturn))
void VG_(err_config_error) ( const HChar* format, ... )
{
   va_list vargs;
   va_start(vargs,format);
   revert_to_stderr();
   VG_(message) (Vg_FailMsg, "Startup or configuration error:\n   ");
   VG_(vmessage)(Vg_FailMsg, format, vargs );
   VG_(message) (Vg_FailMsg, "Unable to start up properly.  Giving up.\n");
   va_end(vargs);
   VG_(exit)(1);
}


#if defined(VGO_linux)
const HChar *VG_(sr_as_string) ( SysRes sr )
{
   static HChar buf[7+1+2+16+1+1];   

   if (sr_isError(sr))
      VG_(sprintf)(buf, "Failure(0x%lx)", sr_Err(sr));
   else
      VG_(sprintf)(buf, "Success(0x%lx)", sr_Res(sr));
   return buf;
}

#elif defined(VGO_darwin)

const HChar *VG_(sr_as_string) ( SysRes sr )
{
   static HChar buf[7+1+2+16+1+2+16+1+1];   

   if (sr_isError(sr))
      VG_(sprintf)(buf, "Failure(0x%lx)", sr_Err(sr));
   else
      VG_(sprintf)(buf, "Success(0x%lx:0x%lx)", sr_ResHI(sr), sr_Res(sr));
   return buf;
}

#else

#error unknown OS

#endif

