template <typename SegtreeType, typename ValueContainer >
void test_build_double_sum(ValueContainer *input);

template <typename SegtreeType, typename ValueContainer >
void test_update_double_sum(ValueContainer *input);

template <typename SegtreeType, typename ValueContainer >
void test_query_double_sum(ValueContainer *input);


template<typename iterator>
struct itr_range{
    public:
    int start,end;
    iterator itr;
};
template <typename SegtreeType, typename ValueContainer >
void test_build_double_sum(ValueContainer *input)
{
    SegtreeType segtree(input,0,199);
    segtree.build(double_sum);
    typedef typename SegtreeType::iterator iterator;
    std::queue<itr_range<iterator>> range_iterator;
    itr_range<iterator> curr_node,curr_left,curr_right;
    curr_node.itr=segtree.get_root();
    curr_node.start=0;
    curr_node.end=199;
    range_iterator.push(curr_node);  
    while(!range_iterator.empty())
    {
        curr_node=range_iterator.front();
        int start=curr_node.start,end=curr_node.end;
        int sum=0;
        for(int i=start;i<=end;i++)
        {
            sum+=input[i].value.a;
        }
        BOOST_CHECK_EQUAL(sum,curr_node.itr->value.a);
        sum=0;
        for(int i=start;i<=end;i++)
        {
            sum+=input[i].value.b;
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
template <typename SegtreeType, typename ValueContainer >
void test_update_double_sum(ValueContainer *input)
{
    SegtreeType segtree(input,0,199);
    segtree.build(double_sum);
    input[0].value.a=0;
    segtree.update(double_sum,0);
    typedef typename SegtreeType::iterator iterator;
    std::queue<itr_range<iterator>> range_iterator;
    itr_range<iterator> curr_node,curr_left,curr_right;
    curr_node.itr=segtree.get_root();
    curr_node.start=0;
    curr_node.end=199;
    range_iterator.push(curr_node);  
    int flag=1;
    while(!range_iterator.empty())
    {
        iterator temp_left,temp_right;
        curr_node=range_iterator.front();
        int start=curr_node.start,end=curr_node.end;
        int sum=0;
        for(int i=start;i<=end;i++)
        {
            sum+=input[i].value.a;
        }
        BOOST_CHECK_EQUAL(sum,curr_node.itr->value.a);
        sum=0;
        for(int i=start;i<=end;i++)
        {
            sum+=input[i].value.b;
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
template <typename SegtreeType, typename ValueContainer >
void test_query_double_sum(ValueContainer *input)
{
    SegtreeType segtree(input,0,199);
    segtree.build(double_sum);
    for(int i=0;i<=199;i++)
    {
        for(int m=i;m<=199;m++)
        {
            type_used temp=segtree.query(double_sum,i,m);
            int sum=0;
            for(int k=i;k<=m;k++)
            {
                sum+=input[k].value.a;
            }
            BOOST_CHECK_EQUAL(sum,temp.a);
            sum=0;
            for(int k=i;k<=m;k++)
            {
                sum+=input[k].value.b;
            }
            BOOST_CHECK_EQUAL(sum,temp.b);
        }
    }
}
