#ifndef ADD_ENTRY_H
#define ADD_ENTRY_H

#include "../array_functions/array_functions.h"

template<class T>
T* add_entry(T* list, const T& new_entry, int& size, int& capacity)
{
    if (size == capacity) 
    {
        capacity *= 2;
        T* new_list = reallocate(list, size, capacity);
        append_array(new_list, size, new_entry);
        return new_list;
    }

    append_array(list, size, new_entry);
    return list;
}


template<class T>
T* remove_entry(T* list, const T& delete_me, int& size, int& capacity)
{
    T* walker = list;
    T* target = search_entry(list, size, delete_me);
    for(int i=0; i<size; i++)
    {
        if(walker == target)
        {
            shift_left(list, size, target);
        }
        walker++;        
    }

    if(size == .25 * capacity)
    {
        capacity /= 2;
        T* new_list = reallocate(list, size, capacity);
        return new_list;
    }
    return list;
}

// template <class T>
// T *remove_last_entry(T *list, T &popped, int &size, int &capacity)
// {
//     T* target = &list[size-1];
//     cout << "removing " << *target << endl;
//     popped = *target;
//     return remove_entry(list, *target, size, capacity);
// }

template <class T>
T *remove_last_entry(T *list, T &popped, int &size, int &capacity)
{
    T* walker = list;
    T* target = &list[size-1];
    popped = *target;
    
    if(walker <= target)
    {
        shift_left(list, size, target);
    }

    if(size == .25 * capacity)
    {
        capacity /= 2;
        T* new_list = reallocate(list, size, capacity);
        return new_list;
    }
    
    return list;
}

template <class T>
T *insert_entry(T *list, const T &insert_this, int insert_here, int &size, int &capacity)
{
    if (size == capacity) 
    {
        capacity *= 2;
        T* new_list = reallocate(list, size, capacity);
        T* walker = &new_list[insert_here];
        shift_right(new_list, size, insert_here);
        *walker = insert_this;
        return new_list;
    }
    
    T* walker = &list[insert_here];
    shift_right(list, size, insert_here);
    *walker = insert_this;
    
    return list;
}

template <class T>
T *erase_entry(T *list, int index, int &size, int &capacity)
{
    T* walker = &list[index];
    return remove_entry(list, *walker, size, capacity);
}

#endif