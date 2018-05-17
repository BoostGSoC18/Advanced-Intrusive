#include "boost/intrusive/detail/node_holder.hpp"
#include "boost/intrusive/detail/generic_hook.hpp"
#include "boost/intrusive/options.hpp"
#include "boost/intrusive/pack_options.hpp"


#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {

      namespace intrusive {

class make_segment_tree_base_hook
{
  public:    
  typedef typename pack_options
      <hook_defaults>::type packed_options;
  public:
   typedef generic_hook
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
