template <typename FenwicktreeType, typename ValueContainer >
void test_build_sum(ValueContainer *input);

template <typename FenwicktreeType, typename ValueContainer >
void test_update_sum(ValueContainer *input);

template <typename FenwicktreeType, typename ValueContainer >
void test_query_sum(ValueContainer *input);

template<typename iterator>
struct itr_range{
    public:
    int index;
    iterator itr;
};
template <typename FenwicktreeType, typename ValueContainer >
void test_build_sum(ValueContainer *input)
{
    FenwicktreeType fenwicktree(input,0,5);
    fenwicktree.build(sum);
    int max_index=6;
    typedef typename FenwicktreeType::iterator iterator;
    std::queue<itr_range<iterator>> nodes_all;
    itr_range<iterator> curr_node;
    curr_node.itr=fenwicktree.get_root();
    curr_node.index=0;
    nodes_all.push(curr_node);
    while(!nodes_all.empty())
    {
        curr_node=nodes_all.front();
        int index=curr_node.index;
        int temp=1,child_par=1;
        int a=index&temp,b=index|temp;
        while((index&temp)!=temp && (index|temp)<=max_index)
        {
            itr_range<iterator> child_node;
            child_node.index=index|temp;
            child_node.itr=curr_node.itr;
            child_node.itr.get_child(child_par);
            nodes_all.push(child_node);
            child_par++;    
            temp*=2;
        }
        if(curr_node.index!=0)
        {
            int sum=0;
            int parent=(curr_node.index)-(curr_node.index & (-1*curr_node.index));
            for(int i=parent;i<curr_node.index;i++)
            {
                sum+=input[i].value.a;
            }
            int x=sum,y=curr_node.itr->value.a;
            BOOST_CHECK_EQUAL(sum,curr_node.itr->value.a);
        }
        nodes_all.pop();
    } 
}
template <typename FenwicktreeType, typename ValueContainer >
void test_update_sum(ValueContainer *input)
{
    FenwicktreeType fenwicktree(input,0,199);
    fenwicktree.build(sum);
    int max_index=200;
    ValueContainer val;
    val.value.a=1;
    input[2].value.a=2;
    fenwicktree.update(sum,2,val);
    typedef typename FenwicktreeType::iterator iterator;
    std::queue<itr_range<iterator>> nodes_all;
    itr_range<iterator> curr_node;
    curr_node.itr=fenwicktree.get_root();
    curr_node.index=0;
    nodes_all.push(curr_node);
    while(!nodes_all.empty())
    {
        curr_node=nodes_all.front();
        int index=curr_node.index;
        int temp=1,child_par=1;
        int a=index&temp,b=index|temp;
        while((index&temp)!=temp && (index|temp)<=max_index)
        {
            itr_range<iterator> child_node;
            child_node.index=index|temp;
            child_node.itr=curr_node.itr;
            child_node.itr.get_child(child_par);
            nodes_all.push(child_node);
            child_par++;    
            temp*=2;
        }
        if(curr_node.index!=0)
        {
            int sum=0;
            int parent=(curr_node.index)-(curr_node.index & (-1*curr_node.index));
            for(int i=parent;i<curr_node.index;i++)
            {
                sum+=input[i].value.a;
            }
            int x=sum,y=curr_node.itr->value.a;
            BOOST_CHECK_EQUAL(sum,curr_node.itr->value.a);
        }
        nodes_all.pop();
    } 
}


template <typename FenwicktreeType, typename ValueContainer >
void test_query_sum(ValueContainer *input)
{
    FenwicktreeType fenwicktree(input,0,199);
    fenwicktree.build(sum);
    for(int i=0;i<=199;i++)
    {
        type_used temp=fenwicktree.query(sum,i);
        int sum=0;
        for(int k=0;k<=i;k++)
        {
            sum+=input[k].value.a;
        }
        BOOST_CHECK_EQUAL(sum,temp.a);    
    }
}
