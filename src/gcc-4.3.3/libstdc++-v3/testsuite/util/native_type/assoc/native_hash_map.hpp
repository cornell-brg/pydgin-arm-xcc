// -*- C++ -*-

// Copyright (C) 2005, 2006, 2007 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the terms
// of the GNU General Public License as published by the Free Software
// Foundation; either version 2, or (at your option) any later
// version.

// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this library; see the file COPYING.  If not, write to
// the Free Software Foundation, 59 Temple Place - Suite 330, Boston,
// MA 02111-1307, USA.

// As a special exception, you may use this file as part of a free
// software library without restriction.  Specifically, if other files
// instantiate templates or use macros or inline functions from this
// file, or you compile this file and link it with other files to
// produce an executable, this file does not by itself cause the
// resulting executable to be covered by the GNU General Public
// License.  This exception does not however invalidate any other
// reasons why the executable file might be covered by the GNU General
// Public License.

// Copyright (C) 2004 Ami Tavory and Vladimir Dreizin, IBM-HRL.

// Permission to use, copy, modify, sell, and distribute this software
// is hereby granted without fee, provided that the above copyright
// notice appears in all copies, and that both that copyright notice
// and this permission notice appear in supporting documentation. None
// of the above authors, nor IBM Haifa Research Laboratories, make any
// representation about the suitability of this software for any
// purpose. It is provided "as is" without express or implied
// warranty.

/**
 * @file native_hash_map.hpp
 * Contains an adapter to TR1 unordered containers.
 */

#ifndef PB_DS_NATIVE_HASH_MAP_HPP
#define PB_DS_NATIVE_HASH_MAP_HPP

#include <string>
#include <ext/pb_ds/detail/type_utils.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <native_type/assoc/native_hash_tag.hpp>
#include <io/xml.hpp>
#include <tr1/unordered_map>

namespace __gnu_pbds
{
  namespace test
  {
#define PB_DS_BASE_C_DEC \
    std::tr1::__unordered_map<Key, Data, Hash_Fn, Eq_Fn, \
    typename Allocator::template rebind<std::pair<const Key, Data> >::other, Cache_Hash>

    template<typename Key,
	     typename Data,
	     size_t Init_Size = 8,
	     typename Hash_Fn = typename __gnu_pbds::detail::default_hash_fn<Key>::type,
	     typename Eq_Fn = std::equal_to<Key>,
	     typename Less_Fn = std::less<Key>,
	     typename Allocator = std::allocator<char>, bool Cache_Hash = false
	     >
    class native_hash_map : public PB_DS_BASE_C_DEC
    {
    private:
      typedef PB_DS_BASE_C_DEC base_type;

    public:
      typedef native_hash_tag container_category;

    public:
      native_hash_map() : base_type(Init_Size) { }

      template<typename It>
      native_hash_map(It f, It l) : base_type(f, l) { }

      static std::string
      name()
      {
        return std::string("n_hash_map_") 
               + (Cache_Hash ? std::string("cah") : std::string("ncah"));
      }

      static std::string
      desc()
      {
        const std::string cache_hash_desc =
	make_xml_tag("cache_hash_code",
		     "value",
		    (Cache_Hash ? std::string("true") : std::string("false")));

        return make_xml_tag("type", "value", "std_tr1_unordered_map", 
			    cache_hash_desc);
      }
    };

#undef PB_DS_BASE_C_DEC

  } // namespace test
} // namespace __gnu_pbds

#endif 

