#include <boost/GSOC18/Advanced-Intrusive/New_segment_tree/segment_tree.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include "test/itestvalue.hpp"
#include "test/bptr_value.hpp"
#include "test/smart_ptr.hpp"
#include "test/common_functors.hpp"
#include <vector>
#include <boost/detail/lightweight_test.hpp>
#include "test/test_macros.hpp"
#include "test/test_container.hpp"
#include <typeinfo>
#include "double_sum_data_type.hpp"
#include <queue>

#define BOOST_TEST_DYN_LINK     
#define BOOST_TEST_MODULE example
#include <boost/test/included/unit_test.hpp>

#include "double_sum_test.hpp"


using namespace boost::intrusive;

template<class VoidPointer>
struct hooks
{
   typedef segment_tree_base_hook<void_pointer<VoidPointer> >                base_hook_type;
   typedef segment_tree_base_hook< link_mode<auto_unlink>
                         , void_pointer<VoidPointer>, tag<void> >    auto_base_hook_type;
   typedef segment_tree_member_hook<void_pointer<VoidPointer>, tag<void> >   member_hook_type;
   typedef segment_tree_member_hook< link_mode<auto_unlink>
                           , void_pointer<VoidPointer> >             auto_member_hook_type;
   typedef nonhook_node_member< segment_tree_node_traits< VoidPointer >,
segment_tree_algorithms > nonhook_node_member_type;
};

template < typename SegtreeType, typename ValueContainer >
struct test_segment_tree
{
   typedef SegtreeType segment_tree_type;
   typedef typename segment_tree_type::value_traits value_traits;
   typedef typename value_traits::value_type value_type;
   typedef typename value_traits::node_traits node_traits;
   typedef  segment_tree_algorithms<node_traits> node_algorithms;

   static void test_all(ValueContainer*input);
   static void test_build(ValueContainer* input);
   static void test_query(ValueContainer* input);
   static void test_update(ValueContainer* input);
};

template <typename SegtreeType, typename ValueContainer >
void test_segment_tree<SegtreeType , ValueContainer>::test_all(ValueContainer *input)
{
    test_build(input);
    
}
template <typename SegtreeType, typename ValueContainer >
void test_segment_tree<SegtreeType , ValueContainer>::test_build(ValueContainer *input)
{
    test_build_double_sum<SegtreeType,ValueContainer>(input);
}

template < typename ValueTraits, bool ConstantTimeSize, bool Default_Holder, typename ValueContainer >
struct make_and_test_segment_tree
   : test_segment_tree< segment_tree< typename ValueTraits::value_type,
                      value_traits< ValueTraits >,
                      size_type< std::size_t >,
                      constant_time_size< ConstantTimeSize >
                    >,
                ValueContainer
              >
{};

template < typename ValueTraits, bool ConstantTimeSize, typename ValueContainer >
struct make_and_test_segment_tree< ValueTraits, ConstantTimeSize, false, ValueContainer >
   : test_segment_tree< segment_tree< typename ValueTraits::value_type,
                      value_traits< ValueTraits >,
                      size_type< std::size_t >,
                      constant_time_size< ConstantTimeSize >,
                      header_holder_type< heap_node_holder< typename ValueTraits::pointer > >
                    >,
                ValueContainer
              >
{};

template < class VoidPointer, bool ConstantTimeSize, bool Default_Holder >
class test_main_template
{
   public:
   int operator()()
   {
      typedef typename hooks<VoidPointer>::base_hook_type base_hook_type;
      typedef MyClass<base_hook_type,hooks<VoidPointer>> value_type;
      type_used input[105];
      for(int i=0;i<100;i++)
      {
          input[i].a=1;
          input[i].b=1;
      }
      make_and_test_segment_tree < typename detail::get_base_value_traits <
                              value_type,
                              typename hooks<VoidPointer>::base_hook_type
                           >::type,
                           ConstantTimeSize,
                           Default_Holder,
                           type_used
                         >::test_all(input);
      make_and_test_segment_tree < typename detail::get_member_value_traits <
                              member_hook< value_type, typename hooks<VoidPointer>::member_hook_type, &value_type::node_>
                           >::type,
                           ConstantTimeSize,
                           Default_Holder,
                            type_used
                        >::test_all(input);
      make_and_test_segment_tree< nonhook_node_member_value_traits <
                             value_type,
                             typename hooks<VoidPointer>::nonhook_node_member_type,
                             &value_type::nhn_member_,
                             safe_link
                          >,
                          ConstantTimeSize,
                          Default_Holder,
                            type_used
                        >::test_all(input);

      return 0;
   }
};

template < class VoidPointer, bool Default_Holder >
class test_main_template< VoidPointer, false, Default_Holder >
{
   public:
   int operator()()
   {
     typedef typename hooks<VoidPointer>::auto_base_hook_type auto_base_hook_type;
     typedef MyClass<auto_base_hook_type,hooks<VoidPointer>> value_type;
      type_used input[105];
      for(int i=0;i<100;i++)
      {
          input[i].a=1;
          input[i].b=1;
      }
      make_and_test_segment_tree < typename detail::get_base_value_traits <
                              value_type,
                              typename hooks<VoidPointer>::auto_base_hook_type
                           >::type,
                           false,
                           Default_Holder,
                           type_used 
                         >::test_all(input);
      make_and_test_segment_tree < typename detail::get_member_value_traits <
                              member_hook< value_type, typename hooks<VoidPointer>::auto_member_hook_type, &value_type::auto_node_>
                            >::type,
                            false,
                         Default_Holder,
                         type_used
                       >::test_all(input);

      return 0;
   }
};
BOOST_AUTO_TEST_CASE( Segment_tree_testing )
{
    test_main_template<void*, false, true>()();
    test_main_template<void*, true, true>()();
}