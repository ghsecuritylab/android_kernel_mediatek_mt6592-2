/* Functions to handle creation of Linux archives.
   Copyright (C) 2007-2012 Red Hat, Inc.
   This file is part of elfutils.
   Written by Ulrich Drepper <drepper@redhat.com>, 2007.

   This file is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   elfutils is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <assert.h>
#include <error.h>
#include <gelf.h>
#include <libintl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <system.h>

#include "arlib.h"


struct arlib_symtab symtab;


void
arlib_init (void)
{
#define obstack_chunk_alloc xmalloc
#define obstack_chunk_free free
  obstack_init (&symtab.symsoffob);
  obstack_init (&symtab.symsnameob);
  obstack_init (&symtab.longnamesob);

  struct ar_hdr ar_hdr;
  memcpy (ar_hdr.ar_name, "/               ", sizeof (ar_hdr.ar_name));
  /* Using snprintf here has a problem: the call always wants to add a
     NUL byte.  We could use a trick whereby we specify the target
     buffer size longer than it is and this would not actually fail,
     since all the fields are consecutive and we fill them in
     sequence (i.e., the NUL byte gets overwritten).  But
     _FORTIFY_SOURCE=2 would not let us play these games.  Therefore
     we play it safe.  */
  char tmpbuf[sizeof (ar_hdr.ar_date) + 1];
  int s = snprintf (tmpbuf, sizeof (tmpbuf), "%-*lld",
		    (int) sizeof (ar_hdr.ar_date),
                    (arlib_deterministic_output ? 0
                     : (long long int) time (NULL)));
  memcpy (ar_hdr.ar_date, tmpbuf, s);
  assert ((sizeof (struct ar_hdr)  % sizeof (uint32_t)) == 0);

  memcpy (ar_hdr.ar_uid, "0       ", sizeof (ar_hdr.ar_uid));
  memcpy (ar_hdr.ar_gid, "0       ", sizeof (ar_hdr.ar_gid));
  memcpy (ar_hdr.ar_mode, "0       ", sizeof (ar_hdr.ar_mode));
  memcpy (ar_hdr.ar_fmag, ARFMAG, sizeof (ar_hdr.ar_fmag));

  
  obstack_grow (&symtab.symsoffob, &ar_hdr, sizeof (ar_hdr));

  assert (sizeof (uint32_t) == sizeof (int));
  obstack_int_grow (&symtab.symsoffob, 0);

  memcpy (ar_hdr.ar_name, "//              ", sizeof (ar_hdr.ar_name));
  memcpy (ar_hdr.ar_date, "            ", sizeof (ar_hdr.ar_date));
  memcpy (ar_hdr.ar_uid, "            ", sizeof (ar_hdr.ar_uid));
  memcpy (ar_hdr.ar_gid, "            ", sizeof (ar_hdr.ar_gid));
  memcpy (ar_hdr.ar_mode, "            ", sizeof (ar_hdr.ar_mode));
  
  obstack_grow (&symtab.longnamesob, &ar_hdr, sizeof (ar_hdr));

  
  symtab.symsofflen = 0;
  symtab.symsoff = NULL;
  symtab.symsnamelen = 0;
  symtab.symsname = NULL;
}


void
arlib_finalize (void)
{
  char tmpbuf[sizeof (((struct ar_hdr *) NULL)->ar_size) + 1];

  symtab.longnameslen = obstack_object_size (&symtab.longnamesob);
  if (symtab.longnameslen != sizeof (struct ar_hdr))
    {
      if ((symtab.longnameslen & 1) != 0)
	{
	  
	  obstack_grow (&symtab.longnamesob, "\n", 1);
	  ++symtab.longnameslen;
	}

      symtab.longnames = obstack_finish (&symtab.longnamesob);

      int s = snprintf (tmpbuf, sizeof (tmpbuf), "%-*zu",
			(int) sizeof (((struct ar_hdr *) NULL)->ar_size),
			symtab.longnameslen - sizeof (struct ar_hdr));
      memcpy (&((struct ar_hdr *) symtab.longnames)->ar_size, tmpbuf, s);
    }

  symtab.symsofflen = obstack_object_size (&symtab.symsoffob);
  assert (symtab.symsofflen % sizeof (uint32_t) == 0);
  if (symtab.symsofflen != 0)
    {
      symtab.symsoff = (uint32_t *) obstack_finish (&symtab.symsoffob);

      
      symtab.symsoff[AR_HDR_WORDS] = le_bswap_32 ((symtab.symsofflen
						    - sizeof (struct ar_hdr))
						   / sizeof (uint32_t) - 1);
    }

  symtab.symsnamelen = obstack_object_size (&symtab.symsnameob);
  if ((symtab.symsnamelen & 1) != 0)
    {
      
      obstack_grow (&symtab.symsnameob, "", 1);
      ++symtab.symsnamelen;
    }
  symtab.symsname = obstack_finish (&symtab.symsnameob);

  
  off_t disp = 0;
  if (symtab.symsnamelen > 0)
    disp = symtab.symsofflen + symtab.symsnamelen;
  if (symtab.longnameslen > sizeof (struct ar_hdr))
    disp += symtab.longnameslen;

  if (disp != 0 && symtab.symsoff != NULL)
    {
      uint32_t nsyms = le_bswap_32 (symtab.symsoff[AR_HDR_WORDS]);

      for (uint32_t cnt = 1; cnt <= nsyms; ++cnt)
	{
	  uint32_t val = le_bswap_32 (symtab.symsoff[AR_HDR_WORDS + cnt]);
	  val += disp;
	  symtab.symsoff[AR_HDR_WORDS + cnt] = le_bswap_32 (val);
	}
    }

  
  memcpy (&((struct ar_hdr *) symtab.symsoff)->ar_size, tmpbuf,
	  snprintf (tmpbuf, sizeof (tmpbuf), "%-*zu",
		    (int) sizeof (((struct ar_hdr *) NULL)->ar_size),
		    symtab.symsofflen + symtab.symsnamelen
		    - sizeof (struct ar_hdr)));
}


void
arlib_fini (void)
{
  obstack_free (&symtab.symsoffob, NULL);
  obstack_free (&symtab.symsnameob, NULL);
  obstack_free (&symtab.longnamesob, NULL);
}


void
arlib_add_symref (const char *symname, off_t symoff)
{
  
  assert (sizeof (uint32_t) == sizeof (int));
  obstack_int_grow (&symtab.symsoffob, (int) le_bswap_32 (symoff));

  size_t symname_len = strlen (symname) + 1;
  obstack_grow (&symtab.symsnameob, symname, symname_len);
}


void
arlib_add_symbols (Elf *elf, const char *arfname, const char *membername,
		   off_t off)
{
  if (sizeof (off) > sizeof (uint32_t) && off > ~((uint32_t) 0))
    
    error (EXIT_FAILURE, 0, gettext ("the archive '%s' is too large"),
	   arfname);

  if (elf_kind (elf) != ELF_K_ELF)
    return;

  GElf_Ehdr ehdr_mem;
  GElf_Ehdr *ehdr = gelf_getehdr (elf, &ehdr_mem);
  if (ehdr == NULL)
    error (EXIT_FAILURE, 0, gettext ("cannot read ELF header of %s(%s): %s"),
	   arfname, membername, elf_errmsg (-1));

  GElf_Word symtype;
  if (ehdr->e_type == ET_REL)
    symtype = SHT_SYMTAB;
  else if (ehdr->e_type == ET_EXEC || ehdr->e_type == ET_DYN)
    symtype = SHT_DYNSYM;
  else
    
    return;

  
  Elf_Scn *scn = NULL;
  while ((scn = elf_nextscn (elf, scn)) != NULL)
    {
      
      GElf_Shdr shdr_mem;
      GElf_Shdr *shdr = gelf_getshdr (scn, &shdr_mem);
      if (shdr == NULL)
	continue;

      if (shdr->sh_type != symtype)
	continue;

      Elf_Data *data = elf_getdata (scn, NULL);
      if (data == NULL)
	continue;

      int nsyms = shdr->sh_size / shdr->sh_entsize;
      for (int ndx = shdr->sh_info; ndx < nsyms; ++ndx)
	{
	  GElf_Sym sym_mem;
	  GElf_Sym *sym = gelf_getsym (data, ndx, &sym_mem);
	  if (sym == NULL)
	    continue;

	  
	  if (sym->st_shndx == SHN_UNDEF)
	    continue;

	  
	  const char *symname = elf_strptr (elf, shdr->sh_link, sym->st_name);
	  if (symname != NULL)
	    arlib_add_symref (symname, off);
	}

      
      if (ehdr->e_type != ET_REL)
	break;
    }
}
