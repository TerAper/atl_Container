#include<iostream>
template <typename T>
class allocator{
    public:
    static void construct (T* start,const T& obj){
        std::cout << "constructor called"<<std::endl;
            new(start) T(obj);
    }
    
    static void construct (T* start){
        std::cout << "constructor called"<<std::endl;
            new(start) T;
    }

    static  T* allocate(int size){
        T* tmp = (T*)operator new(size*sizeof(T));
        return tmp;
    }

    static void destruct(T* start){
            (*start).~T();
    }

    static  void deallocate(T* ptr){
        operator delete (ptr);
    }
    
};