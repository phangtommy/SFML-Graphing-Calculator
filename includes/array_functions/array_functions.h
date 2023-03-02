#ifndef ARRAY_FUNCTIONS_H
#define ARRAY_FUNCTIONS_H

#include <iostream>
using namespace std;
const int MINIMUM_CAPACITY = 3;

// template<class T>
// T* allocate(int capacity= MINIMUM_CAPACITY)
// {
//     T* newArray = new T[capacity];
//     return newArray;
// } 

template <class T>
T* allocate(int capacity)
{
    const bool debug = false;
    if (debug) cout<<"allocate: capacity: "<<capacity<<endl;
    return new T[capacity];
}

template<class T>
void print_array(T* a, int size, int capacity = 0, ostream& outs = cout)
{
    T *walker = a;
    for(int i=0; i<size; i++)
    {
        cout << *walker << " ";
        walker++;
    }
    //cout << endl;
}

template <class T>
void print(T* a, unsigned int how_many, ostream& outs = cout)
{
    print_array(a, how_many);
}

template<class T>
T* search_entry(T* a, int size, const T& find_me)
{
    T *walker = a;
    for(int i=0; i<size; i++)
    {
        if(*walker == find_me)
        {
            return walker;
        }
        walker++;
    }
    return nullptr;
}  

template <class T> 
int search(T* a, int size, const T& find_me)
{
    T *target = search_entry(a, size, find_me);
    if(*target == find_me)
    {
        return target - a;
    }
    return -1;
}  

template <class T>
void shift_left(T* a, int &size, T* shift_here)
{
    T *sizePtr = &a[size-1];
    T *mark = shift_here;
    T *nextMark = mark + 1;
    int val = sizePtr - mark;
    for(int i=0; i<val; i++)
    {
        *mark = *nextMark;
        mark++;
        nextMark++;
    }
    size--;
} 

template <class T>
void shift_left(T* a, int& size, int shift_here)
{
    T* index = &a[shift_here];
    shift_left(a, size, index);
}  

template <class T>
void shift_right(T *a, int &size, T* shift_here)
{
    T *walker = &a[size];
    T *prevWalker = walker - 1;
    int val = walker - shift_here;
    for(int i=0; i<val; i++)
    {
        *walker = *prevWalker;
        walker--;
        prevWalker--;
    }
    size++;
}

template <class T>
void shift_right(T *a, int &size, int shift_here)
{
    T* index = &a[shift_here];
    shift_right(a, size, index);
}


template<class T>
void copy_array(T *dest, const T* src, int many_to_copy)
{
    T* destWalker= dest;
    const T* srcWalker = src;

    for(int i=0; i<many_to_copy; i++)
    {
        *destWalker = *srcWalker;
        destWalker++;
        srcWalker++;
    }
}    

template <class T>
T* copy_array(const T *src, int size)
{
    T* walker = new T[size];
    copy_array(walker, src, size);
    return walker;
}                

template<class T>
T* reallocate(T* a, int size, int capacity)
{
    T* newArr = allocate<T>(capacity);
    copy_array(newArr, a, size);
    delete[] a;
    return newArr;
}

template <class T>
string array_string(const T *a, int size)
{
    string str;
    const T *walker = a;
    for(int i=0; i<size; i++)
    {
        str += to_string(*walker) + " ";
        walker++;
    }
    return str;
}



template<class T>
void init(T* a, int size, int val)
{
    T *walker = a;
    for (int i = 0; i < size; i++)
    {
        *walker = val;
        walker++;
    }
}

template<class T>
void append_array(T* a, int &size, T item)
{
    T* walker = a + size;
    *walker = item;
    size++; 
}



#endif // ARRAY_FUNCTIONS_H