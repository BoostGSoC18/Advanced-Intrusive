#include<boost/GSOC18/Advanced-Intrusive/Segment_tree/segment_tree.hpp>

using namespace boost::intrusive;

struct single_node : public segment_tree_base_hook
{
  int a;
};
int main()
{
  struct single_node first;
  std::cout << first.position;
  segment_tree<single_node> last(3);
  last.setting_position(first);

  return 0;
}