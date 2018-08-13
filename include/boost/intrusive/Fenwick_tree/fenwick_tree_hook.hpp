#include "boost/intrusive/detail/node_holder.hpp"
#include "boost/intrusive/detail/generic_hook.hpp"
#include "boost/intrusive/options.hpp"
#include "boost/intrusive/pack_options.hpp"


#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {

      namespace intrusive {

#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1 = void, class O2 = void, class O3 = void>
#endif
class make_fenwick_tree_base_hook
{
  public:    
  typedef typename pack_options
      <hook_defaults>::type packed_options;
  public:
   typedef generic_hook
   < FenTreeAlgorithms
   , fenwick_tree_node_traits<typename packed_options::void_pointer>
   , typename packed_options::tag
   , packed_options::link_mode
   , FenTreeBaseHookId
   > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1, class O2, class O3>
#endif
class fenwick_tree_base_hook
   : public make_fenwick_tree_base_hook
     #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      <O1, O2, O3>
      #else
      <Options...>
      #endif
    ::type      
{
   
};
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1, class O2, class O3>
#endif

class make_fenwick_tree_member_hook
{
   public:
   /// @cond
   typedef typename pack_options
      < hook_defaults>::type packed_options;

   typedef generic_hook
   < FenTreeAlgorithms
   , fenwick_tree_node_traits<typename packed_options::void_pointer>
   , member_tag
   , packed_options::link_mode
   , NoBaseHookId
   > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1, class O2, class O3>
#endif
class fenwick_tree_member_hook
   :  public make_fenwick_tree_member_hook
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      <O1, O2, O3>
      #else
      <Options...>
      #endif
      ::type
{

};
#include <boost/intrusive/detail/config_end.hpp>            
    
    }
}
