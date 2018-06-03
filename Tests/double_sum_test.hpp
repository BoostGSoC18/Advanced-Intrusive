template <typename SegtreeType, typename ValueContainer >
void test_build_double_sum(ValueContainer *input);

template<typename iterator>
struct itr_range{
    public:
    int start,end;
    iterator itr;
};
template <typename SegtreeType, typename ValueContainer >
void test_build_double_sum(ValueContainer *input)
{
    SegtreeType segtree(0,99,100);
    segtree.build(input,0,99,double_sum);
    typedef typename SegtreeType::iterator iterator;
    std::queue<itr_range<iterator>> range_iterator;
    itr_range<iterator> curr_node,curr_left,curr_right;
    curr_node.itr=segtree.get_root();
    curr_node.start=0;
    curr_node.end=99;
    range_iterator.push(curr_node);  
    while(!range_iterator.empty())
    {
        curr_node=range_iterator.front();
        int start=curr_node.start,end=curr_node.end;
        int sum=0;
        for(int i=start;i<=end;i++)
        {
            sum+=input[i].a;
        }
        BOOST_CHECK_EQUAL(sum,curr_node.itr->value.a);
        sum=0;
        for(int i=start;i<=end;i++)
        {
            sum+=input[i].b;
        }
        BOOST_CHECK_EQUAL(sum,curr_node.itr->value.b);
        if(curr_node.start!=curr_node.end)
        {
            iterator temp;
            itr_range<iterator> left,right;
            temp=curr_node.itr;
            temp.get_left_child();
            left.itr=temp;
            temp=curr_node.itr;
            temp.get_right_child();
            right.itr=temp;
            int mid=(start+end)/2;
            left.start=start;
            left.end=mid;
            right.start=mid+1;
            right.end=end;
            range_iterator.push(left);
            range_iterator.push(right);
        }
        range_iterator.pop();
    }
}
