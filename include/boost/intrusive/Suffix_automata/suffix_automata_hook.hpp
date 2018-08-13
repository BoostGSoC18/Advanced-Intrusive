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
class make_suffix_automata_base_hook
{
  public:    
  typedef typename pack_options
      <hook_defaults>::type packed_options;
  public:
    /*!
  <ul>
  <li>This generic hook forms core part for every hook. </li>
   <li> For any type of hook the difference lies in the arguments passed, the core hook
    i.e generic hook lies the same.</li>
  </ul>
  */

   typedef generic_hook
   < SuffixAutomataAlgorithms
   , suffix_automata_node_traits<typename packed_options::void_pointer>
   , typename packed_options::tag
   , packed_options::link_mode
   , SuffixAutomataBaseHookId
   > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1, class O2, class O3>
#endif
class suffix_automata_base_hook
   : public make_suffix_automata_base_hook
     #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      <O1, O2, O3>
      #else
      <Options...>
      #endif
    ::type      
{
   public:
   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state.
   //!
   //! <b>Throws</b>: Nothing.
   suffix_automata_base_hook();

   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   suffix_automata_base_hook(const suffix_automata_base_hook& );

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   suffix_automata_base_hook& operator=(const suffix_automata_base_hook& );

   //! <b>Effects</b>: If link_mode is \c normal_link, the destructor does
   //!   nothing (ie. no code is generated). If link_mode is \c safe_link and the
   //!   object is stored in an suffix automata an assertion is raised. If link_mode is
   //!   \c auto_unlink and \c is_linked() is true, the node is unlinked.
   //!
   //! <b>Throws</b>: Nothing.
   ~suffix_automata_base_hook();

   //! <b>Precondition</b>: link_mode must be \c safe_link or \c auto_unlink.
   //!
   //! <b>Returns</b>: true, if the node belongs to a container, false
   //!   otherwise. This function can be used to test whether \c suffix::iterator_to
   //!   will return a valid iterator.
   //!
   //! <b>Complexity</b>: Constant
   bool is_linked() const;
};
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1, class O2, class O3>
#endif

class make_suffix_automata_member_hook
{
   public:
   typedef typename pack_options
      < hook_defaults>::type packed_options;
  /*!
  <ul>
  <li>This generic hook forms core part for every hook. </li>
   <li> For any type of hook the difference lies in the arguments passed, the core hook
    i.e generic hook lies the same.</li>
  </ul>
  */
   typedef generic_hook
   < SuffixAutomataAlgorithms
   , suffix_automata_node_traits<typename packed_options::void_pointer>
   , member_tag
   , packed_options::link_mode
   , NoBaseHookId
   > implementation_defined;
   typedef implementation_defined type;
};
#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class ...Options>
#else
template<class O1, class O2, class O3>
#endif
class suffix_automata_member_hook
   :  public make_suffix_automata_member_hook
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      <O1, O2, O3>
      #else
      <Options...>
      #endif
      ::type
{
    public:
   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state.
   //!
   //! <b>Throws</b>: Nothing.
   suffix_automata_member_hook();

   //! <b>Effects</b>: If link_mode is \c auto_unlink or \c safe_link
   //!   initializes the node to an unlinked state. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing a copy-constructor
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   suffix_automata_member_hook(const suffix_automata_member_hook& );

   //! <b>Effects</b>: Empty function. The argument is ignored.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Rationale</b>: Providing an assignment operator
   //!   makes classes using the hook STL-compliant without forcing the
   //!   user to do some additional work. \c swap can be used to emulate
   //!   move-semantics.
   suffix_automata_member_hook& operator=(const suffix_automata_member_hook& );

   //! <b>Effects</b>: If link_mode is \c normal_link, the destructor does
   //!   nothing (ie. no code is generated). If link_mode is \c safe_link and the
   //!   object is stored in an suffix_automata an assertion is raised. If link_mode is
   //!   \c auto_unlink and \c is_linked() is true, the node is unlinked.
   //!
   //! <b>Throws</b>: Nothing.
   ~suffix_automata_member_hook();

   //! <b>Precondition</b>: link_mode must be \c safe_link or \c auto_unlink.
   //!
   //! <b>Returns</b>: true, if the node belongs to a container, false
   //!   otherwise. This function can be used to test whether \c suffix_automata::iterator_to
   //!   will return a valid iterator.
   //!
   //! <b>Complexity</b>: Constant
   bool is_linked() const;
};
#include <boost/intrusive/detail/config_end.hpp>            
    
    }
}
