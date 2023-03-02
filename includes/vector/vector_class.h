#ifndef VECTOR_CLASS_H
#define VECTOR_CLASS_H

#include "../add_entry/add_entry.h"

template <class T>
class Vector{
public:

    Vector(int size = 100);
    Vector(T *arr, int size);

    // big three:

    Vector(const Vector& RHS); // COPY CONSTRUCTOR

    Vector& operator =(const Vector& RHS)  // OVERLOADED ASSIGNMENT OPERATOR
    {
        if(this == &RHS)
        {
            return *this;
        }

        _size = RHS._size;
        _capacity = RHS._capacity;
        vptr = allocate<T>(_capacity);
        copy_array(vptr, RHS.vptr, _size);
       
        return *this;
    }

    ~Vector();      // DESTRUCTOR
    
    //member access functions:
    T& operator [](int index);
    const T& operator [](int index) const;

    T& at(int index);              //return reference to item at position index
    const T& at(int index) const;  //return a const item at position index

    T& front();                         //return item at position 0.
    T& back();                          //return item at the last position


    //Push and Pop functions:
    Vector& operator +=(const T& item)
    {
        vptr = add_entry(vptr, item, _size, _capacity);
        return *this;
    } ; //push_back
    void push_back(const T& item);      //append to the end
    T pop_back();                       //remove last item and return it


    //Insert and Erase:
    void insert(int insert_here, const T& insert_this); //insert at pos
    void erase(int erase_this_index);        //erase item at position
    int index_of(const T& item);             //search for item. retur index.

    //size and capacity:
    void set_size(int size);              //enlarge the vector to this size
    void set_capacity(int capacity);      //allocate this space
    int size() const {return _size;}  //return _size
    int capacity() const {return _capacity;} //return _capacity

    bool empty() const;                    //return true if vector is empty

    //OUTPUT:
    template <class U>
    friend ostream& operator <<(ostream& outs, const Vector<U>& _a);

private:
    T* vptr;
    int _size;
    int _capacity;
};

// Friend function

template <class U>
ostream& operator <<(ostream& outs, const Vector<U>& _a)
{
    outs << "(" <<_a._size << "/" << _a._capacity<<")" << "[ ";
    print_array(_a.vptr, _a._size);
    outs << "]";
    return outs;
}

// CONSTRUCTORS

template <class T>
Vector<T>::Vector(int size)
{
    _size = 0;
    _capacity = size;
    vptr = allocate<T>(_capacity);
}

template <class T>
Vector<T>::Vector(T *arr, int size)
{
    _size = size;
    _capacity = size + 2;
    vptr = allocate<T>(_capacity);
    copy_array(vptr, arr, size);
}

// BIG THREE 

template <class T>
Vector<T>::Vector(const Vector& RHS) // COPY CONSTRUCTOR
{
    _size = RHS._size;
    _capacity = RHS._capacity;
    // vptr = copy_array(RHS.vptr, RHS._capacity);
    vptr = allocate<T>(_capacity);
    copy_array(vptr, RHS.vptr, _size);
}

template <class T>
Vector<T>::~Vector()
{
    delete[] vptr;
}

// MEMBER ACCESS FUNCTIONS

template <class T>
T& Vector<T>::operator [](int index)
{
    return vptr[index];
}

template <class T>
const T& Vector<T>::operator [](int index) const
{
    return vptr[index];
}

template <class T>
T& Vector<T>::at(int index)
{
    return vptr[index];
}

template <class T>
const T& Vector<T>::at(int index) const
{
    return vptr[index];
}  

template <class T>
T& Vector<T>::front()
{
    return vptr[0];
}                         

template <class T>
T& Vector<T>::back()
{
    return vptr[_size - 1];
}  

// PUSH AND POP BACK

template <class T>
void Vector<T>::push_back(const T& item)
{
    this->vptr = add_entry(this->vptr, item, this->_size, this->_capacity);
}      

template <class T>
T Vector<T>::pop_back()
{
    T target;
    this->vptr = remove_last_entry(this->vptr, target, this->_size, this->_capacity);

    return target;
}            

// Insert and Erase:

template <class T>
void Vector<T>::insert(int insert_here, const T& insert_this)
{
    vptr = insert_entry(vptr, insert_this, insert_here, _size, _capacity);
} 

template <class T>
void Vector<T>::erase(int erase_this_index)
{
    vptr = erase_entry(vptr, erase_this_index, _size, _capacity);
}      

template <class T>
int Vector<T>::index_of(const T& item)
{
    return search(vptr, size(), item);
}            

// size and capacity:

template <class T>
void Vector<T>::set_size(int size)
{
    _size = size;
}             

template <class T>
void Vector<T>::set_capacity(int capacity)
{
    _capacity = capacity;
}   

template <class T>
bool Vector<T>::empty() const
{
    if(size() == 0)
    {
        return true;
    }
    return false;
}                  

#endif