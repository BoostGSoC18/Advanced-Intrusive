#include</home/hari/BoostGsoc18/boost_1_65_1/boost/GSOC18/Advanced-Intrusive/Segment_tree/segment_tree.hpp>

using namespace boost::intrusive;

struct node : public segment_tree_base_hook
{
    int a;
};
int main()
{
//    segment_tree<struct node> first(4);
  //  std::cout << first.ptr[0].position;
  struct node first;
  std::cout << first.position;
    return 0;
}