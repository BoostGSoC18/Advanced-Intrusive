#include<bits/stdc++.h>
template<typename T>
class segment_tree_algorithms
{
    public:
    T* init(int n,T *ptr)
    {
       ptr=(T*)malloc(4*n*sizeof(T));
       return ptr;     
    }

};