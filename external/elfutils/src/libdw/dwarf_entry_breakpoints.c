/* Find entry breakpoint locations for a function.
   Copyright (C) 2005-2009 Red Hat, Inc.
   This file is part of elfutils.

   This file is free software; you can redistribute it and/or modify
   it under the terms of either

     * the GNU Lesser General Public License as published by the Free
       Software Foundation; either version 3 of the License, or (at
       your option) any later version

   or

     * the GNU General Public License as published by the Free
       Software Foundation; either version 2 of the License, or (at
       your option) any later version

   or both in parallel, as here.

   elfutils is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received copies of the GNU General Public License and
   the GNU Lesser General Public License along with this program.  If
   not, see <http://www.gnu.org/licenses/>.  */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif
#include "libdwP.h"
#include <dwarf.h>
#include <stdlib.h>


int
dwarf_entry_breakpoints (die, bkpts)
     Dwarf_Die *die;
     Dwarf_Addr **bkpts;
{
  int nbkpts = 0;
  *bkpts = NULL;

  
  inline int add_bkpt (Dwarf_Addr pc)
    {
      Dwarf_Addr *newlist = realloc (*bkpts, ++nbkpts * sizeof newlist[0]);
      if (newlist == NULL)
	{
	  free (*bkpts);
	  *bkpts = NULL;
	  __libdw_seterrno (DWARF_E_NOMEM);
	  return -1;
	}
      newlist[nbkpts - 1] = pc;
      *bkpts = newlist;
      return nbkpts;
    }

  
  inline int entrypc_bkpt (void)
    {
      Dwarf_Addr pc;
      return INTUSE(dwarf_entrypc) (die, &pc) < 0 ? -1 : add_bkpt (pc);
    }

  
  Dwarf_Die cudie = CUDIE (die->cu);
  Dwarf_Lines *lines;
  size_t nlines;
  if (INTUSE(dwarf_getsrclines) (&cudie, &lines, &nlines) < 0)
    {
      int error = INTUSE (dwarf_errno) ();
      if (error == 0)		
	return entrypc_bkpt ();
      __libdw_seterrno (error);
      return -1;
    }

  inline int search_range (Dwarf_Addr low, Dwarf_Addr high,
			   bool dwarf, bool adhoc)
    {
      size_t l = 0, u = nlines;
      while (l < u)
	{
	  size_t idx = (l + u) / 2;
	  if (lines->info[idx].addr < low)
	    l = idx + 1;
	  else if (lines->info[idx].addr > low)
	    u = idx;
	  else if (lines->info[idx].end_sequence)
	    l = idx + 1;
	  else
	    {
	      l = idx;
	      break;
	    }
	}
      if (l < u)
	{
	  if (dwarf)
	    for (size_t i = l; i < u && lines->info[i].addr < high; ++i)
	      if (lines->info[i].prologue_end
		  && add_bkpt (lines->info[i].addr) < 0)
		return -1;
	  if (adhoc && nbkpts == 0)
	    while (++l < nlines && lines->info[l].addr < high)
	      if (!lines->info[l].end_sequence)
		return add_bkpt (lines->info[l].addr);
	  return nbkpts;
	}
      __libdw_seterrno (DWARF_E_INVALID_DWARF);
      return -1;
    }

  

  Dwarf_Addr base;
  Dwarf_Addr begin;
  Dwarf_Addr end;
  ptrdiff_t offset = INTUSE(dwarf_ranges) (die, 0, &base, &begin, &end);
  if (offset < 0)
    return -1;

  
  if (offset == 1)
    return search_range (begin, end, true, true) ?: entrypc_bkpt ();

  Dwarf_Addr lowpc = (Dwarf_Addr) -1l;
  Dwarf_Addr highpc = (Dwarf_Addr) -1l;
  while (offset > 0)
    {
      
      if (search_range (begin, end, true, false) < 0)
	return -1;

      if (begin < lowpc)
	{
	  lowpc = begin;
	  highpc = end;
	}

      offset = INTUSE(dwarf_ranges) (die, offset, &base, &begin, &end);
    }

  return (nbkpts
	  ?: (lowpc == (Dwarf_Addr) -1l ? 0
	      : search_range (lowpc, highpc, false, true))
	  ?: entrypc_bkpt ());
}