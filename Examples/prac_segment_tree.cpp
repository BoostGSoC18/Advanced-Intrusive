#include <boost/GSOC18/Advanced-Intrusive/Segment_tree/segment_tree.hpp>
#include<boost/intrusive/intrusive_fwd.hpp>

using namespace boost::intrusive;
class Foo
{
   public:
   segment_tree_member_hook<> hook_;
};


typedef member_hook<Foo, segment_tree_member_hook<>, &Foo::hook_> MemberHookOption;
typedef segment_tree<Foo, MemberHookOption> FooList;

int main()
{
  Foo foo_object;
  FooList segtree(5);
  return 0;
}
