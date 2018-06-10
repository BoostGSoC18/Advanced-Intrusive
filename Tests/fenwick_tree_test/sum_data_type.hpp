struct type_used
{
public:
  int a;
};
template<typename Base_hook,typename Hooks>
class MyClass: public Base_hook
{
public:
   typename Hooks::member_hook_type        node_;
   typename Hooks::auto_member_hook_type   auto_node_;
   typename Hooks::nonhook_node_member_type nhn_member_;
public:
  typedef type_used data_type;
  data_type value;
};
auto sum=[](auto a,auto b)
{
  type_used c;
  c.a=a.a+b.a;
  return c;
};

