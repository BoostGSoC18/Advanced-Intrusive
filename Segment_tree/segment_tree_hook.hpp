//
// (C) Copyright Olaf Krzikalla 2004-2006.
// (C) Copyright Ion Gaztanaga  2006-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#include "/home/hari/BoostGsoc18/boost_1_65_1/boost/intrusive/detail/node_holder.hpp"
#include "/home/hari/BoostGsoc18/boost_1_65_1/boost/intrusive/detail/generic_hook.hpp"
#include "/home/hari/BoostGsoc18/boost_1_65_1/boost/intrusive/options.hpp"
#include "/home/hari/BoostGsoc18/boost_1_65_1/boost/intrusive/pack_options.hpp"


#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {

      namespace intrusive {

class make_segment_tree_base_hook
{
  public:    
  typedef typename boost::intrusive::pack_options
      <boost::intrusive::hook_defaults>::type packed_options;

   typedef boost::intrusive::generic_hook
   < SegTreeAlgorithms
   , segment_tree_node_traits<typename packed_options::void_pointer>
   , typename packed_options::tag
   , packed_options::link_mode
   , SegTreeBaseHookId
   > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};
class segment_tree_base_hook
   : public make_segment_tree_base_hook::type      
{
   
};

#include <boost/intrusive/detail/config_end.hpp>

            
}
}
