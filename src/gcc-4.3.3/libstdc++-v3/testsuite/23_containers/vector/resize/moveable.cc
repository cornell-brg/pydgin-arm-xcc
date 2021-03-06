// { dg-options "-std=gnu++0x" }

// Copyright (C) 2005, 2006, 2007 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING.  If not, write to the Free
// Software Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
// USA.

// As a special exception, you may use this file as part of a free software
// library without restriction.  Specifically, if other files instantiate
// templates or use macros or inline functions from this file, or you compile
// this file and link it with other files to produce an executable, this
// file does not by itself cause the resulting executable to be covered by
// the GNU General Public License.  This exception does not however
// invalidate any other reasons why the executable file might be covered by
// the GNU General Public License.

#include <vector>
#include <testsuite_hooks.h>
#include <testsuite_rvalref.h>

using namespace __gnu_test;

// According to n1771, there should be two resizes, with and without
// parameter. We only have one at present, whose second parameter defaults
// to a default-constructed object.
// Also, the values are one higher than might be expected because internally
// resize calls fill, which copies its input value in case it is already in
// the vector when the vector isn't moved.
void
test01()
{
  bool test __attribute__((unused)) = true;

  std::vector<copycounter> a;
  copycounter::copycount = 0;
  a.resize(10);
  a.resize(98);
  a.resize(99);
  a.resize(100);
#ifndef _GLIBCXX_DEBUG
  VERIFY( copycounter::copycount == 100 + 4 );
#else
  VERIFY( copycounter::copycount == 100 + 4 + 4 );
#endif
  a.resize(99);
  a.resize(0);
#ifndef _GLIBCXX_DEBUG
  VERIFY( copycounter::copycount == 100 + 4 );
#else
  VERIFY( copycounter::copycount == 100 + 4 + 6 );
#endif
  a.resize(100);
#ifndef _GLIBCXX_DEBUG  
  VERIFY( copycounter::copycount == 200 + 5 );
#else
  VERIFY( copycounter::copycount == 200 + 5 + 7 );
#endif
  a.clear();
#ifndef _GLIBCXX_DEBUG
  VERIFY( copycounter::copycount == 200 + 5 );
#else
  VERIFY( copycounter::copycount == 200 + 5 + 7 );
#endif
}


int main()
{
  test01();
  return 0;
}
