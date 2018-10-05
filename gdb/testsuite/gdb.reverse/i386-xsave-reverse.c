/* This testcase is part of GDB, the GNU debugger.

   Copyright 2018 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* Architecture tests for intel i386 platform.  */

#include <cpuid.h>
#include <stdint.h>
#include <string.h>

uint32_t
get_xsave_buffer_size (void)
{
  uint32_t size, eax, ecx, edx;
  __get_cpuid_count (0xd, 0, &eax, &size, &ecx, &edx);

  return size;
}

void
xsave_test (void)
{
  uint32_t xsave_buf_sze = get_xsave_buffer_size ();
  char buf[xsave_buf_sze] __attribute__ ((aligned (64)));
  memset (buf, 0, xsave_buf_sze);

  asm ("xsave %0" : "=m"(buf) : "a"(~0L), "d"(~0L));
} /* end xsave_test */

void
xsave_no_sse_test (void)
{
  uint32_t xsave_buf_sze = get_xsave_buffer_size ();
  char buf[xsave_buf_sze] __attribute__ ((aligned (64)));
  memset (buf, 0, xsave_buf_sze);

  asm ("xsave %0" : "=m"(buf) : "a"((1 << 1) ^ ~0L), "d"(~0L));
} /* end xsave_no_sse_test */

void xsavec_test (void) {
  uint32_t xsave_buf_sze = get_xsave_buffer_size ();
  char buf[xsave_buf_sze] __attribute__ ((aligned (64)));
  memset (buf, 0, xsave_buf_sze);

  asm ("xsavec %0":"=m"(buf) : "a"(~0L), "d"(~0L));
} /* end xsavec_test */

int
main ()
{
  xsave_test ();
  xsave_no_sse_test ();
  xsavec_test ();
  return 0;	/* end of main */
}
