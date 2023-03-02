#ifndef MYSTACK_H
#define MYSTACK_H
#include "../linked_list_functions/linked_list_functions.h"

template <typename T>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack;                     //give access to list to access _ptr
        Iterator(){_ptr = NULL;}                //default ctor
        Iterator(node<T>* p){_ptr =p;}          //Point Iterator to where
                                                //  p is pointing to

        T &operator*(){                             //dereference operator
            assert(_ptr && "Empty Ptr");
            return _ptr->_item;
        }

        bool is_null(){                             //true if _ptr is NULL
            if(_ptr)
                return false;
            return true;
        }        

        friend bool operator!=(const Iterator &left,
                               const Iterator &right){ //true if left != right
            return left._ptr != right._ptr;
        }

        friend bool operator==(const Iterator &left,
                               const Iterator &right){ //true if left == right
            return left._ptr == right._ptr;
        }
        
        Iterator &operator++(){                         //member operator:
            _ptr = _ptr->_next;                                     //  ++it; or
            return *this;                               //  ++it = new_value
        }

        friend Iterator operator++(Iterator &it,
                                   int unused){          //friend operator: it++
            Iterator temp;
            temp = it;
            it._ptr = it._ptr->_next;
            return temp;
        }

    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };

    Stack();
    Stack(const Stack<T>& copyMe);
    ~Stack();
    Stack<T>& operator=(const Stack<T>& RHS);
    T top();
    bool empty();
    void push(T item);
    T pop();
    template<typename TT>
    friend ostream& operator<<(ostream& outs, 
                                        const Stack<TT>& printMe);
    void Print() const;

    Iterator begin() const;              //Iterator to the head node
    Iterator end() const;                //Iterator to NULL
    int size() const { return _size; }

private:
    node<T>* _top;
    int _size;
};



template <typename T>
Stack<T>::Stack()
{
    _top = nullptr;
    _size = 0;
}

template <typename T>
Stack<T>::Stack(const Stack<T>& copyMe)
{
    _top = _copy_list(copyMe._top);
    _size = copyMe._size;
}

template <typename T>
Stack<T>::~Stack()
{
    _clear_list(_top);
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& RHS)
{
    if(this == &RHS)
    {
        return *this;
    }

    _clear_list(_top);
    _top = _copy_list(RHS._top);
    _size = RHS._size;
    return *this;
}

template <typename T>
T Stack<T>::top()
{
    return _top->_item;
}

template <typename T>
bool Stack<T>::empty()
{
    if(_top)
        return false;
    return true;
}

template <typename T>
void Stack<T>::push(T item)
{
    _size++;
    _insert_head(_top, item);
}

template <typename T>
T Stack<T>::pop()
{
    _size--;
    return _remove_head(_top);
}

template <class T>
void Stack<T>::Print() const
{
    _print_list(_top);
}         

template<typename TT>
ostream& operator<<(ostream& outs, const Stack<TT>& printMe)
{
    outs << "Stack:Head->";
    printMe.Print();
    outs << "-> |||" << endl;
    return outs; 
}

template <typename T>
typename Stack<T>::Iterator Stack<T>::begin() const
{
    return Iterator(_top);
}

template <typename T>
typename Stack<T>::Iterator Stack<T>::end() const
{
    return Iterator();
}

#endif