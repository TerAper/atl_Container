template <typename T,typename U>
#include <iostream>
class _iterator{
    U*  it;
    public:
    _iterator():it(nullptr){}
    _iterator(U* start):it(start){}
    T& operator *(){
        return it->val;
    }
    bool operator !=(_iterator other){
        return it != other.it;
    }
    _iterator& operator ++(){
            it = it->next;
        return *this;
    }
    _iterator operator ++(int){
            U* tmp = it;
            it = it->next;
        return iterator(tmp);
    }
    U* operator ->(){
        return it;
    }

};