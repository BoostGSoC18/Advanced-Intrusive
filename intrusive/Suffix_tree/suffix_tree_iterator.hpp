#include <boost/intrusive/detail/iiterator.hpp>
namespace boost{

    namespace intrusive{
        
template<class ValueTraits, bool IsConst>
class suffix_tree_iterator
{
    typedef iiterator
      <ValueTraits, IsConst, std::bidirectional_iterator_tag> types_t;

   static const bool stateful_value_traits =                types_t::stateful_value_traits;

   typedef ValueTraits                                      value_traits;
   typedef typename types_t::node_traits                    node_traits;

   typedef typename types_t::node                           node;
   typedef typename types_t::node_ptr                       node_ptr;
   typedef typename types_t::const_value_traits_ptr         const_value_traits_ptr;

   public:
   typedef typename types_t::iterator_type::difference_type    difference_type;
   typedef typename types_t::iterator_type::value_type         value_type;
   typedef typename types_t::iterator_type::pointer            pointer;
   typedef typename types_t::iterator_type::reference          reference;
   typedef typename types_t::iterator_type::iterator_category  iterator_category;

   BOOST_INTRUSIVE_FORCEINLINE suffix_tree_iterator()
   {}

   BOOST_INTRUSIVE_FORCEINLINE explicit suffix_tree_iterator(const node_ptr & nodeptr, const const_value_traits_ptr &traits_ptr)
      : members_(nodeptr, traits_ptr)
   {}
   
   BOOST_INTRUSIVE_FORCEINLINE const node_ptr &pointed_node() const
   {   
       return members_.nodeptr_; 
   }
   public:

    BOOST_INTRUSIVE_FORCEINLINE pointer operator->() const
   {   return this->operator_arrow(detail::bool_<stateful_value_traits>()); }

    BOOST_INTRUSIVE_FORCEINLINE suffix_tree_iterator get_child(char child)
   {
      members_.nodeptr_=members_.nodeptr_->children[child];
   }

    private:
    BOOST_INTRUSIVE_FORCEINLINE pointer operator_arrow(detail::false_) const
   { return ValueTraits::to_value_ptr(members_.nodeptr_); }

   BOOST_INTRUSIVE_FORCEINLINE pointer operator_arrow(detail::true_) const
   { return this->get_value_traits()->to_value_ptr(members_.nodeptr_); }


   iiterator_members<node_ptr, const_value_traits_ptr, stateful_value_traits> members_;



};

    }
}