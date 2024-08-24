#include <iostream>
#include"allocator.h"
#include"forward_iterator.h"

template <typename T,template <class> class alloc = allocator,template <class,class> class iter = _iterator>
class forward_list{
    struct Node{
        Node(T _val = T{},Node* ptr = nullptr):val(_val),next(ptr){};
            T val;
            Node* next;
        ~Node(){
            std::cout << "destuctor called" << std::endl; 
        }
        };
        using iterator = iter<T&,Node>;
        using const_iterator = iter<const T&,const Node>;
        Node* head;

    public:

    iterator begin(){
        return iterator(head);
    }

    iterator end(){
        return iterator(nullptr);
    }

    const_iterator cbegin(){
        return const_iterator(head);
    }

    const_iterator cend(){
        return const_iterator(nullptr);
    }


    forward_list():head(nullptr){}

    forward_list(int size){
        Node* head_tmp = head;
        if(size > 0){
        head = alloc<Node>::allocate(sizeof(Node));
        alloc<Node>::construct(head);
        head_tmp = head;
        for(int i = 0; i < size-1 ; i++){
            head_tmp->next = alloc<Node>::allocate(1);
            alloc<Node>::construct(head->next);
            head_tmp = head_tmp->next;
        }
        }else{
            head = nullptr;
            return;
        }
        head_tmp->next = nullptr;
    }

    forward_list(const forward_list& obj){
            if(obj.head){
                head = alloc<Node>::allocate(1);
                alloc<Node>::construct(head);
                head->val = obj.head->val;
            }else{
                head = nullptr;
                return;
            }
            Node*objtmp = obj.head;
            Node*tmp = head;
            while(objtmp->next){
                tmp ->next= alloc<Node>::allocate(1);
                tmp = tmp->next;
                alloc<Node>::construct(tmp);
                objtmp = objtmp->next;
                tmp->val = objtmp->val;
            }
            tmp->next = nullptr;
        }

    forward_list& operator=(const forward_list& obj){
        if(this == &obj){
            return *this;
        }else if(!obj.head){
            Node* tmp = head;
            while(head){
                tmp = tmp->next;
                alloc<Node>::destruct(head);
                alloc<Node>::deallocate(head);  
                head = tmp;
            }
            head = nullptr;
            return *this;
        }
        if(!head){
            head = alloc<Node>::allocate(1);
            alloc<Node>::construct(head);
        }

        Node* objtmp = obj.head;
        Node* tmp = head;
        while(objtmp){
            if(!objtmp->next){
                tmp->val = objtmp->val;
                Node* Y = tmp;
                Node* X = tmp->next;
                tmp = tmp->next;
                while (tmp){
                    tmp = tmp->next;
                    alloc<Node>::destruct(X);
                    alloc<Node>::deallocate(X);
                    X = tmp;
                }
                Y->next = nullptr;
                return *this;
            }
            tmp->val = objtmp->val;
            if(!tmp->next){
                tmp->next = alloc<Node>::allocate(1);
                alloc<Node>::construct(tmp->next);
            }
                objtmp = objtmp->next;
                tmp = tmp->next;
            
        }
        return *this;
    }

    forward_list(forward_list&& obj){
        head = obj.head;
        obj.head = nullptr;
    }

    forward_list& operator=(forward_list&& obj){
        if(!head){
            head = obj.head;
            obj.head = nullptr;
            obj.size = 0;
            return *this;
        }
        Node* tmp = head;
        while(head){
            tmp = tmp->next;
            alloc<Node>::destruct(head);
            head = tmp;
        }
        head = obj.head;
        obj.head = nullptr;
        return *this;
    }

    ~forward_list(){
        Node* tmp = head;
        while(head){
            tmp = tmp->next;
            alloc<Node>::destruct(head);
            alloc<Node>::deallocate(head);  
            head = tmp;
        }
    }

    iterator find_by_value(T vla){
        Node* tmp = head;
        while(tmp){
            if(tmp->val == vla){
                return iterator(tmp);
            }
            tmp = tmp->next;
        }
        return iterator(end());
    }

    iterator find_by_index(int pos){
        Node* tmp = head;
        while(tmp){
            if(pos == 1){
                return iterator(tmp);
            }else if(pos < 1){
                break;
            }
            pos--;
            tmp = tmp->next;
        }
        return iterator(end());
    }

    bool operator==(const forward_list& obj){
        if(!head || !obj.head){
            return false;
        }
        Node* tmp = head;
        Node* objtmp = obj.head;
        while(tmp->next && objtmp->next){
            if(tmp->val != objtmp->val){
                break;
            }
            tmp = tmp->next;
            objtmp = objtmp->next;
        }
        return tmp->val == objtmp->val;
    }

    bool operator!=(const forward_list& obj){
        return !(*this == obj);
    }
    
    void insert_after(iterator pos,T num){
        if(pos.operator->() == nullptr){
            return;
        }
        Node* tmp = pos->next;
        pos->next = alloc<Node>::allocate(sizeof(Node));
        alloc<Node>::construct(pos->next);
        pos->next->val = num;
        pos->next->next = tmp;
    }

    void push_front(T num){
        Node* tmp = alloc<Node>::allocate(sizeof(Node));
        alloc<Node>::construct(tmp);
        tmp->val = num;
        tmp->next = head;
        head = tmp;
    }

    void erase_after(iterator pos){
         if(pos.operator->() == nullptr||pos->next == nullptr){
            return;
        }
            Node* tmp = pos.operator->()->next;
            pos->next = pos->next->next;
            alloc<Node>::destruct(tmp);
            alloc<Node>::deallocate(tmp);
        }

    bool empaty(){
        if(!head){
            return true;
        }
        return false;
    }

    T pop_back(){
        if(!head){
            return 0;
        }
        T num;
        if(!head->next){
            num = head->val;
            alloc<Node>::destruct(head);
            alloc<Node>::deallocate(head);
            head = nullptr;
            return num;
        }   
        Node* tmp = head;
        Node*x;
        while(tmp->next){
            x = tmp;
            tmp = tmp->next;
        }
        num = tmp->val;
        alloc<Node>::destruct(x->next);
        alloc<Node>::deallocate(x->next);
        x->next = nullptr;
        return num;
    }
};


