#include <boost/intrusive/Suffix_automata/suffix_automata_algorithms.hpp>
#include <boost/intrusive/Suffix_automata/suffix_automata_hook.hpp>
#include <boost/intrusive/Suffix_automata/suffix_automata_iterator.hpp>


#include<boost/intrusive/any_hook.hpp>
#include <boost/intrusive/detail/get_value_traits.hpp>
#include "boost/intrusive/options.hpp"
#include <boost/intrusive/detail/is_stateful_value_traits.hpp>
#include <boost/intrusive/detail/default_header_holder.hpp>
#include "boost/intrusive/detail/size_holder.hpp"
#include<iostream>
#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/detail/assert.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/link_mode.hpp>
#include <boost/intrusive/detail/reverse_iterator.hpp>
#include <boost/intrusive/detail/uncast.hpp>
#include <boost/intrusive/detail/array_initializer.hpp>
#include <boost/intrusive/detail/exception_disposer.hpp>
#include <boost/intrusive/detail/equal_to_value.hpp>
#include <boost/intrusive/detail/key_nodeptr_comp.hpp>
#include <boost/intrusive/detail/simple_disposers.hpp>
#include <boost/intrusive/detail/algorithm.hpp>

#include <boost/move/utility_core.hpp>
#include <boost/static_assert.hpp>

#include <boost/intrusive/detail/minimal_less_equal_header.hpp>//std::less
#include <cstddef>   //std::size_t, etc.

#include <queue>

namespace boost {
    namespace intrusive {

struct default_suffix_automata_hook_applier
{  
    template <class T> 
    struct apply
    { 
        typedef typename T::default_suffix_automata_hook type;  
    };  
};

template<>
struct is_default_hook_tag<default_suffix_automata_hook_applier>
{  static const bool value = true;  };

struct suffix_automata_defaults
{
   typedef default_suffix_automata_hook_applier proto_value_traits;
   static const bool constant_time_size = true;
   typedef std::size_t size_type;
   typedef void header_holder_type;
};
/*!
<ul>
<li>This class contains all the basic methods supported by suffix automata. </li>
<li> This class is derived in the "suffix_automata" class </li>
</ul>
*/

template<typename ValueTraits, class SizeType, bool ConstantTimeSize, typename HeaderHolder>
class suffix_automata_impl
{
    public:
    typedef ValueTraits                                               value_traits;
    typedef typename value_traits::node_traits node_traits;
    typedef typename node_traits::node node;
    typedef typename node::node_ptr node_ptr;
    typedef typename value_traits::pointer pointer;
    typedef typename pointer_traits<pointer>::element_type            value_type;
    typedef typename pointer_traits<pointer>::reference               reference;
    typedef suffix_automata_algorithms<node_traits> algo;
    typedef typename node_traits::const_node_ptr                      const_node_ptr;
    typedef SizeType                                                  size_type;
    typedef suffix_automata_iterator<value_traits, false>                        iterator;
    typedef suffix_automata_iterator<value_traits, true>                         const_iterator;
    typedef typename detail::get_header_holder_type
      < value_traits, HeaderHolder >::type                           header_holder_type;
///@cond
   static const bool constant_time_size = ConstantTimeSize;
   static const bool stateful_value_traits = detail::is_stateful_value_traits<value_traits>::value;
   static const bool has_container_from_iterator =
        detail::is_same< header_holder_type, detail::default_header_holder< node_traits > >::value;

   /// @endcond

   private:
    typedef detail::size_holder<constant_time_size, size_type>          size_traits;
   
   node_ptr get_root_node()
   { return data_.root_plus_size_.m_header.get_node(); }

   const_node_ptr get_root_node() const
   { return data_.root_plus_size_.m_header.get_node(); }

   struct root_plus_size : public size_traits
   {
      header_holder_type m_header;
   };

   struct data_t : public ValueTraits
   {
      typedef typename suffix_automata_impl::value_traits value_traits;
      root_plus_size root_plus_size_;
      value_type *root = NULL; 
      value_type *last = NULL;
      
   } data_;


   size_traits &priv_size_traits()
   {  return data_.root_plus_size_;  }

   const size_traits &priv_size_traits() const
   {  return data_.root_plus_size_;  }

   const value_traits &priv_value_traits() const
   {
     return data_;  
   }
   value_traits &priv_value_traits()
   {
      return data_;
   }
   typedef typename boost::intrusive::value_traits_pointers<ValueTraits>::const_value_traits_ptr const_value_traits_ptr;

   const_value_traits_ptr priv_value_traits_ptr() const
   {  return pointer_traits<const_value_traits_ptr>::pointer_to(this->priv_value_traits());  }

private:
void extend_automata(char *text,int i)
{
    value_type *curr_node=(value_type*)malloc(sizeof(value_type));
    node_ptr curr_ptr=value_traits::to_node_ptr(*curr_node);
    node_ptr last_ptr=value_traits::to_node_ptr(*data_.last);
    curr_ptr->length=last_ptr->length+1;
    for(int i=0;i<26;i++)
        curr_ptr->children[i]=nullptr;
    node_ptr p;
    for(p=last_ptr;(p!=nullptr && p->children[text[i]-97]==nullptr);p=p->suffix_link)
    {
        p->children[text[i]-97]=curr_ptr;
    }
    if(p==nullptr)
    {
        curr_ptr->suffix_link=value_traits::to_node_ptr(*data_.root);
    }
    else
    {
        node_ptr q=p->children[text[i]-97];
        if(q->length==p->length+1)
        {
            curr_ptr->suffix_link=q;
        }
        else
        {
            value_type *cloned_node=(value_type*)malloc(sizeof(value_type));
            node_ptr cloned_ptr=value_traits::to_node_ptr(*cloned_node);
            cloned_ptr->length=p->length+1;
            cloned_ptr->suffix_link=p->suffix_link;
            for(int i=0;i<26;i++)
                cloned_ptr->children[i]=q->children[i];
            for(;(p!=nullptr &&  p->children[text[i]-97]==q);p=p->suffix_link)
            {
                p->children[text[i]-97]=cloned_node;
            }
            q->suffix_link=cloned_ptr;
            curr_ptr->suffix_link=cloned_ptr;

        }
    }
    data_.last=curr_node;
    
}
public:
/*!
<ul>
<li>
This function declares all the variables required by suffix automata and initialises them
</li>
<li>
This function also builds the suffix automata for the given inputs.
</li>
</ul>
\param text base string on which suffix automata needs to be built
\param start starting index of base string to be considered
\param end ending index of base string to be considered
\return Nothing
<p> </p>
<b> Complexity: </b> O(N)
*/

suffix_automata_impl(char *text)
{
    int len=strlen(text);
    data_.root=(value_type*)malloc(sizeof(value_type));
    node_ptr root_ptr=value_traits::to_node_ptr(*data_.root);
    root_ptr->length=0;
    root_ptr->suffix_link=nullptr;
    data_.last=data_.root;
    for(int i=0;i<len;i++)
    {
        extend_automata(text,i);
    }
}
/*!
This returns an iterator to the root node of suffix automata.
*/
iterator get_root()
{
    node_ptr root_node=value_traits::to_node_ptr(*data_.root);
    return iterator(root_node,this->priv_value_traits_ptr());
}

};


#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED) || defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class ...Options>
#else
template<class T, class O1 = void, class O2 = void, class O3 = void, class O4 = void>
#endif
struct make_suffix_automata
{
   public:
   typedef typename pack_options
      < suffix_automata_defaults,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
         O1, O2, O3, O4
         #else
         Options...
         #endif
         >::type packed_options;

   typedef typename detail::get_value_traits
      <T, typename packed_options::proto_value_traits>::type value_traits;
   /*!
   <ul>
    <li>This is the main class which contains all the methods supported by suffix automata.</li>
    <li>This class is derived into "suffix_automata" class by giving appropriate inputs.</li>
   </ul>
   */
   typedef suffix_automata_impl
      <value_traits,
        typename packed_options::size_type,
         packed_options::constant_time_size,
         typename packed_options::header_holder_type
   > implementation_defined;
   typedef implementation_defined type;
};

#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class O1, class O2, class O3, class O4>
#else
template<class T, class ...Options>
#endif
class suffix_automata
   : public make_suffix_automata<T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4
      #else
      Options...
      #endif
   >::type
{
    public:
       typedef typename make_suffix_automata
      <T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4
      #else
      Options...
      #endif
      >::type      Base;

 public:
   typedef typename Base::value_traits          value_traits;
       /*!
        <ul>
        <li> This is the first and main function used while working with any data structure.</li>
        <li>This calls the "suffix_automata_impl" function which does initialisation and declaration of variables.</li>
        </ul>
    */

    public:
    suffix_automata(char *text)
        : Base(text)
    {

    };
};

}
}
#endif 