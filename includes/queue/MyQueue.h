#ifndef MYQUEUE_H
#define MYQUEUE_H
#include "../linked_list_functions/linked_list_functions.h"

template <typename T>
class Queue
{
public:
    class Iterator{
    public:
        friend class Queue;          //give access to list to access _ptr
        
        Iterator(){                  //default ctor
            _ptr = nullptr;
        }

        Iterator(node<T>* p){        //Point Iterator to where p is pointing to
            _ptr = p;
        }

        T &operator*(){                             //dereference operator
            assert(_ptr && "Empty Ptr");
            return _ptr->_item;
        }

        T* operator ->(){                       //member access operator
            assert(_ptr && "Ptr is null(2)");             // returns address of the item
            return &(_ptr->_item);
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
        node<T>* _ptr;               //pointer being encapsulated
    };

    Queue();

    Queue(const Queue<T>& copyMe);
    ~Queue();
    Queue& operator=(const Queue<T>& RHS);

    bool empty();
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const;            //Iterator to the head node
    Iterator end() const;              //Iterator to NULL
    void print_pointers() const;
    int size() const { return _size; }
    template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<TT>& printMe);
private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};



template <typename T>
Queue<T>::Queue()
{
    _front = nullptr;
    _rear = nullptr;
    _size = 0;
}

template <typename T>
Queue<T>::Queue(const Queue<T>& copyMe)
{
    _front = nullptr;
    _rear = _copy_list(_front, copyMe._front);
    _size = copyMe._size;
}

template <typename T>
Queue<T>::~Queue()
{
    _clear_list(_front);
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& RHS)
{
    if(this == &RHS)
    {
        return *this;
    }

    _clear_list(_front);
    _front = nullptr;
    _rear = _copy_list(_front, RHS._front);
    _size = RHS._size;
    return *this;
}

template <typename T>
bool Queue<T>::empty()
{
    if(_front)
        return false;
    return true;
}

template <typename T>
T Queue<T>::front()
{
    return _front->_item;
}

template <typename T>
T Queue<T>::back()
{
    return _rear->_item;
}

template <typename T>
void Queue<T>::push(T item)
{
    _size++;
    _rear = _insert_after(_front, _rear, item);
}

template <typename T>
T Queue<T>::pop()
{
    _size--;
    return _remove_head(_front);
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::begin() const
{
    return Iterator(_front);
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::end() const
{
    return Iterator();
}

template <typename T>
void Queue<T>::print_pointers() const
{
    _print_list(_front);
}

template<typename TT>
ostream& operator << (ostream& outs, const Queue<TT>& printMe)
{
    outs << "Queue:Head->";
    printMe.print_pointers();
    outs <<"-> |||" << endl;
    return outs;
}


#endif