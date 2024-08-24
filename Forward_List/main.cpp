#include "forward_list.h"
#include <iostream>
int main(){
    forward_list<int> obj;
    obj.push_front(1);
    obj.push_front(2);
    obj.push_front(3);

    for(auto i = obj.begin(); i != obj.end();++i){
        std::cout << *i << std::endl;
    }

    auto it = obj.find_by_value(2);
    obj.insert_after(it,0);
    std::cout << std::endl;

    for(auto i = it; i != obj.end();++i){
        std::cout << *i << std::endl;
    }

    forward_list<int> tmp;
    tmp.push_front(7);
    std::cout << std::endl;
    tmp = obj;

    std::cout << std::endl;
    
    for(auto i = tmp.begin(); i != tmp.end();++i){
        std::cout << *i << std::endl;
    }

    std::cout << std::endl;
}