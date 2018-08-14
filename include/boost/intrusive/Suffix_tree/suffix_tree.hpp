#include <boost/intrusive/Suffix_tree/suffix_tree_algorithms.hpp>
#include <boost/intrusive/Suffix_tree/suffix_tree_hook.hpp>
#include <boost/intrusive/Suffix_tree/suffix_tree_iterator.hpp>


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

struct default_suffix_tree_hook_applier
{  
    template <class T> 
    struct apply
    { 
        typedef typename T::default_suffix_tree_hook type;  
    };  
};

template<>
struct is_default_hook_tag<default_suffix_tree_hook_applier>
{  static const bool value = true;  };

struct suffix_tree_defaults
{
   typedef default_suffix_tree_hook_applier proto_value_traits;
   static const bool constant_time_size = true;
   typedef std::size_t size_type;
   typedef void header_holder_type;
};
/*!
<ul>
<li>
In this class contains all the methods supported by suffix tree are defined.
</li>
<li>
This is derived in the "suffix tree" class.
</li>
*/
template<typename ValueTraits, class SizeType, bool ConstantTimeSize, typename HeaderHolder>
class suffix_tree_impl
{
    public:
    typedef ValueTraits                                               value_traits;
    typedef typename value_traits::node_traits node_traits;
    typedef typename node_traits::node node;
    typedef typename node::node_ptr node_ptr;
    typedef typename value_traits::pointer pointer;
    typedef typename pointer_traits<pointer>::element_type            value_type;
    typedef typename pointer_traits<pointer>::reference               reference;
    typedef suffix_tree_algorithms<node_traits> algo;
    typedef typename node_traits::const_node_ptr                      const_node_ptr;
    typedef SizeType                                                  size_type;
    typedef suffix_tree_iterator<value_traits, false>                        iterator;
    typedef suffix_tree_iterator<value_traits, true>                         const_iterator;
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
      typedef typename suffix_tree_impl::value_traits value_traits;
      root_plus_size root_plus_size_;
      value_type *root = NULL; 
      value_type *lastNewNode = NULL;
      value_type *activeNode = NULL;  
      int activeEdge = -1,activeLength = 0,remainingSuffixCount = 0,leafEnd = -1;
      int *rootEnd = NULL;
      int *splitEnd = NULL;
      int size = -1;
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
   typedef typename boost::intrusive::value_traits_pointers
      <ValueTraits>::const_value_traits_ptr const_value_traits_ptr;

   const_value_traits_ptr priv_value_traits_ptr() const
   {  return pointer_traits<const_value_traits_ptr>::pointer_to(this->priv_value_traits());  }

value_type *newNode(int start, int *end)
{
    value_type *new_node =(value_type*)malloc(sizeof(value_type));
    node_ptr curr_node=value_traits::to_node_ptr(*new_node);
    int i;
    for (i = 0; i < 256; i++)
          curr_node->children[i] = NULL;
    curr_node->suffix_link = value_traits::to_node_ptr(*data_.root);
    curr_node->start = start;
    curr_node->end = end;
    curr_node->suffix_index = -1;
    return new_node;
}
int edgeLength(value_type *n) 
{
    node_ptr curr=value_traits::to_node_ptr(*n);
    return *(curr->end) - (curr->start) + 1;
}
int walkDown(value_type *currNode)
{
    if (data_.activeLength >= edgeLength(currNode))
    {
        data_.activeEdge += edgeLength(currNode);
        data_.activeLength -= edgeLength(currNode);
        data_.activeNode = currNode;
        return 1;
    }
    return 0;
}
void extendSuffixTree(char *text,int pos,int start)
{
    data_.leafEnd = pos;
    data_.remainingSuffixCount++;
    data_.lastNewNode = NULL;
    while(data_.remainingSuffixCount > 0)
    {
        if (data_.activeLength == 0)
            data_.activeEdge = pos;
        node_ptr next_start=value_traits::to_node_ptr(*data_.activeNode);
        if (next_start->children[text[data_.activeEdge]] == NULL)
        {
            next_start->children[text[data_.activeEdge]] =value_traits::to_node_ptr(*newNode(pos, &data_.leafEnd));
            node_ptr last_nodeptr=value_traits::to_node_ptr(*data_.lastNewNode);
            if (data_.lastNewNode != NULL)
            {
                last_nodeptr->suffix_link = value_traits::to_node_ptr(*data_.activeNode);
                data_.lastNewNode = NULL;
            }
        }
        else
        {
            value_type *next = value_traits::to_value_ptr(data_.activeNode->children[text[data_.activeEdge]]);
            if (walkDown(next))
            {
                continue;
            }
            if (text[next->start + data_.activeLength] == text[pos])
            {
                node_ptr last_nodeptr=value_traits::to_node_ptr(*data_.lastNewNode);    
                if(data_.lastNewNode != NULL && data_.activeNode != data_.root)
                {
                    last_nodeptr->suffix_link = data_.activeNode;
                    data_.lastNewNode = NULL;
                }
                data_.activeLength++;
                break;
            }

            data_.splitEnd = (int*) malloc(sizeof(int));
            *data_.splitEnd = next->start + data_.activeLength - 1;

            value_type *split = newNode(next->start, data_.splitEnd);
            data_.activeNode->children[text[data_.activeEdge]] = value_traits::to_node_ptr(*split);

            split->children[text[pos]] = value_traits::to_node_ptr(*newNode(pos, &data_.leafEnd));
            next->start += data_.activeLength;
            split->children[text[next->start]] = value_traits::to_node_ptr(*next);

            node_ptr last_nodeptr=value_traits::to_node_ptr(*data_.lastNewNode);
            if (data_.lastNewNode != NULL)
            {
                last_nodeptr->suffix_link = split;
            }
            data_.lastNewNode = split;
        }
        data_.remainingSuffixCount--;
        if (data_.activeNode == data_.root && data_.activeLength > 0)
        {
            data_.activeLength--;
            data_.activeEdge = pos - data_.remainingSuffixCount + 1;
        }
        else if (data_.activeNode != data_.root)
        {
            node_ptr next_start=value_traits::to_node_ptr(*data_.activeNode);
            data_.activeNode = value_traits::to_value_ptr(next_start->suffix_link);
        }
    }
}
public:
/*!
<ul>
<li>
This function declares all the variables required by suffix tree and initialises them
</li>
<li>
This function builds the suffix tree for the given inputs.
</li>
</ul>
\param text base string on which suffix tree needs to be built
\param start starting index of base string to be considered
\param end ending index of base string to be considered
\return Nothing
<p> </p>
<b> Complexity: </b> O(N)
*/
suffix_tree_impl(char *text,int start,int end)
{
    data_.size = strlen(text);
    int i;
    data_.rootEnd = (int*) malloc(sizeof(int));
    *data_.rootEnd = - 1;
    data_.root = newNode(-1, data_.rootEnd); 
    data_.activeNode = data_.root;
    for (i=start; i<=end; i++)
        extendSuffixTree(text,i-start,start);
    int labelHeight = 0;
}
/*!
This returns an iterator to the root node of suffix tree.
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
struct make_suffix_tree
{
    public:
   typedef typename pack_options
      < suffix_tree_defaults,
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
    <li>This is the main class which contains all the methods supported by suffix tree.</li>
    <li>This class is derived into "suffix_tree" class by giving appropriate inputs.</li>
   </ul>
   */
   typedef suffix_tree_impl
      <value_traits,
        typename packed_options::size_type,
         packed_options::constant_time_size,
         typename packed_options::header_holder_type
   > implementation_defined;
   /// @endcond
   typedef implementation_defined type;
};

#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED

#if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
template<class T, class O1, class O2, class O3, class O4>
#else
template<class T, class ...Options>
#endif
class suffix_tree 
   : public make_suffix_tree<T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4
      #else
      Options...
      #endif
   >::type
{
    public:
       typedef typename make_suffix_tree
      <T,
      #if !defined(BOOST_INTRUSIVE_VARIADIC_TEMPLATES)
      O1, O2, O3, O4
      #else
      Options...
      #endif
      >::type      Base;

 public:
   typedef typename Base::value_traits          value_traits;
   
    public:
        /*!
        <ul>
        <li> This is the first and main function used while working with any data structure.</li>
        <li>This calls the "suffix_tree_impl" function which does initialisation and declaration of variables.</li>
        </ul>
    */
    suffix_tree(char *text,int start,int end)
        : Base(text,start,end)
    {

    };
};

}
}
#endif 