#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H
#include "../node/node.h"
#include <cassert>

//Linked List General Functions:
template <typename ITEM_TYPE>
void _print_list(node<ITEM_TYPE>* head)
{
    node<ITEM_TYPE>* walker = head;
    while(walker->_next != nullptr) 
    {
        cout << *walker << "->";    
        walker = walker->_next;
    }
    cout << *walker ; 
}

//recursive fun! :)
template <typename ITEM_TYPE>
void _print_list_backwards(node<ITEM_TYPE> *head)
{
    if(head == nullptr)
    {
        return;
    }
    node<ITEM_TYPE>* walker = head;
    _print_list_backwards(walker->_next);
    cout << "<-" << *walker ;
}

//return ptr to key or NULL
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _search_list(node<ITEM_TYPE>* head, ITEM_TYPE key)
{
    node<ITEM_TYPE>* walker = head;
    while(walker != nullptr)
    {
        if(walker->_item == key)
        {
            return walker;
        }
        walker = walker->_next;
    }
    return nullptr;
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_head(node<ITEM_TYPE> *&head, ITEM_TYPE insert_this)
{
    node<ITEM_TYPE>* newNode = new node<ITEM_TYPE>;
    newNode->_item = insert_this;
    newNode->_next = head;
    head = newNode;
    return head;
}

//insert after ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_after(node<ITEM_TYPE>*& head, node<ITEM_TYPE> *after_this, ITEM_TYPE insert_this)
{
    if(head == nullptr || after_this == nullptr)
    {
        return _insert_head(head, insert_this);
    }
    node<ITEM_TYPE>* newNode = new node<ITEM_TYPE>;
    newNode->_item = insert_this;
    newNode->_next = after_this->_next;
    after_this->_next = newNode;
    return newNode;
}

//insert before ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_before(node<ITEM_TYPE>*& head, node<ITEM_TYPE>* before_this, ITEM_TYPE insert_this)
{
    if(before_this == head || before_this == nullptr)
    {
        return _insert_head(head, insert_this);
    }
    node<ITEM_TYPE>* prevNode = _previous_node(head, before_this);
    node<ITEM_TYPE>* newNode = new node<ITEM_TYPE>;
    newNode->_item = insert_this;
    newNode->_next = before_this;
    prevNode->_next = newNode;
    return newNode;
}

//ptr to previous node
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _previous_node(node<ITEM_TYPE>* head, node<ITEM_TYPE>* prev_to_this)
{
    node<ITEM_TYPE>* walker = head;
    while(walker != nullptr)
    {
        if(prev_to_this == nullptr)
        {
            assert("Mark is not on the list");
            break;
        }
        if(walker->_next == prev_to_this)
        {
            return walker;
        }
        walker = walker->_next;
    }
    return nullptr;
}

template <typename ITEM_TYPE>
ITEM_TYPE _remove_head(node<ITEM_TYPE>*&head)
{
    assert(head != nullptr && "List is already empty");
    node<ITEM_TYPE>* walker = head;
    ITEM_TYPE item = walker->_item;
    head = walker->_next;
    delete walker;
    return item;
}

//delete, return item
template <typename ITEM_TYPE>
ITEM_TYPE _delete_node(node<ITEM_TYPE>*&head, node<ITEM_TYPE>* delete_this)
{
    assert(delete_this != nullptr && "Can't delete, target not on list!");
    ITEM_TYPE item = delete_this->_item;
    node<ITEM_TYPE>* walker = head;
    if(walker == delete_this)
    {
        head = walker->_next;
        delete delete_this;
        return item;
    }
    while(walker != nullptr)
    {
        if(walker->_next == delete_this)
        {
            walker->_next = walker->_next->_next;
            delete delete_this;
        }
        walker = walker->_next;
    }
    return item;
}

//duplicate the list...
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* head)
{
    node<ITEM_TYPE>* newList = nullptr;
    _copy_list(newList, head);
    return newList;
}

//duplicate list and return the last node of the copy
template <typename T>
node<T> *_copy_list(node<T>* &dest, node<T> *src)
{
   if(src == nullptr)
    {
        return nullptr;
    }
    _clear_list(dest);
    node<T>* srcWalker = src;
    node<T>* destWalker = dest;

    while(srcWalker != nullptr)
    {
        destWalker = _insert_after(dest, destWalker, srcWalker->_item);
        srcWalker = srcWalker->_next;
    }
    return destWalker;
}


//delete all the nodes
template <typename ITEM_TYPE>
void _clear_list(node<ITEM_TYPE>*& head)
{
    if(head == nullptr)
    {
        return;
    }
    node<ITEM_TYPE>* walker = head;
    while(walker->_next != nullptr)
    {
        node<ITEM_TYPE>* walker2 = walker->_next;
        delete walker;
        walker = walker2;
    }
    delete walker;
    head = nullptr;
}

//_item at this position
template <typename ITEM_TYPE>
ITEM_TYPE& _at(node<ITEM_TYPE>* head, int pos)
{
    assert(pos >= 0 && "Index cannot be negative value");
    node<ITEM_TYPE>* walker = head;
    for(int i=0; i<pos; i++)
    {
        walker = walker->_next;
        if(walker == nullptr)
        {
            assert(0 && "Node is out of bounds");
        }
    }
    return walker->_item;
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//      Sorted List Routines. order: 0: ascending, order: other: descending
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

//insert
template <typename ITEM_TYPE> 
node<ITEM_TYPE>* _insert_sorted(node<ITEM_TYPE>* &head, ITEM_TYPE item, bool ascending=true)
{
    node<ITEM_TYPE>* mark = _where_this_goes(head, item, ascending);
    if(mark)
        return _insert_after(head, mark, item);
    return _insert_head(head, item);
}

//insert or add if a dup
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted_and_add(node<ITEM_TYPE>* &head, ITEM_TYPE item, bool ascending=true)
{
    node<ITEM_TYPE>* mark = _where_this_goes(head, item, ascending);

    if(mark)
    {
        if(mark->_item == item)
        {
            ITEM_TYPE temp = _delete_node(head, mark);
            return _insert_sorted(head, temp + item, ascending);
        }
    }
    return _insert_sorted(head, item, ascending);
}

//node after which this item goes order: 0 ascending
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _where_this_goes(node<ITEM_TYPE>* head, ITEM_TYPE item, bool ascending=true)
{
    node<ITEM_TYPE>* leadW = head;
    node<ITEM_TYPE>* backW = nullptr;
    while(leadW->_next != nullptr && leadW->_item >= item)
    {
        backW = leadW;
        leadW = leadW->_next;
        if(leadW->_item < item)// && backW->_item >= item)
        {   
            break;
        }
        else if(leadW->_next == nullptr)// && backW->_item >= item)
        {
            return leadW;
        }
    }
    return backW;
}

//Last Node in the list
// template <typename ITEM_TYPE>
// node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>* head);            //never use this function.

#endif