#include</home/hari/BoostGsoc18/boost_1_65_1/boost/GSOC18/Advanced-Intrusive/Segment_tree/segment_tree.hpp>

using namespace boost::intrusive;

struct node : public segment_tree_base_hook<>
{
    int a;
};
int main()
{
    segment_tree<struct node> first(4);
    

    return 0;
}