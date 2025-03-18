#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "list/XArrayList.h"
#include "list/DLinkedList.h"
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

// -------------------- List1D --------------------
template <typename T>
class List1D
{
private:
    IList<T> *pList;

public:
    List1D();
    List1D(int num_elements);
    List1D(const T *array, int num_elements);
    List1D(const List1D<T> &other);
    virtual ~List1D();

    int size() const;
    T get(int index) const;
    void set(int index, T value);
    void add(const T &value);
    string toString() const;
    template <typename U> //! thêm vào  để chạy test 
    friend ostream &operator<<(ostream &os, const List1D<T> &list);
};



// -------------------- List1D Method Definitions --------------------
template <typename T>
List1D<T>::List1D()
{
    // TODO
    pList = new XArrayList<T>();
}

template <typename T>
List1D<T>::List1D(int num_elements)
{
    // TODO
    pList = new XArrayList<T>();
    for(int i = 0; i < num_elements; i++)
    {
        pList->add(T{});
    }
}

template <typename T>
List1D<T>::List1D(const T *array, int num_elements)
{
    // TODO
    pList = new XArrayList<T>();
    for(int i = 0; i < num_elements; i++)
    {
        pList->add(array[i]);
    }
}

template <typename T>
List1D<T>::List1D(const List1D<T> &other)
{
    // TODO
    pList = new XArrayList<T>();
    if(this != &other)
    {
        for(int i = 0; i < other.size(); i++)
        {
            this->pList->add(other.get(i));
        }
    }

}

template <typename T>
List1D<T>::~List1D()
{
    // TODO
    delete pList;
}

template <typename T>
int List1D<T>::size() const
{
    // TODO
    return pList->size();
}

template <typename T>
T List1D<T>::get(int index) const
{
    // TODO

    if(index < 0 || index >= pList->size())
        throw out_of_range("Index is out of range!");
    return pList->get(index);
}

template <typename T>
void List1D<T>::set(int index, T value)
{
    // TODO

    if(index >= 0 && index <= pList->size())
    {
        if(index < pList->size())
            pList->removeAt(index);
        pList->add(index, value); 
    }
    else 
        throw out_of_range("Index is out of range!");
}

template <typename T>
void List1D<T>::add(const T &value)
{
    // TODO
    pList->add(value);
}

template <typename T>
string List1D<T>::toString() const
{
    // TODO
    return pList->toString([](T &item) -> string{
        ostringstream os;
        os <<item;
        return os.str();
    });
    
}

template <typename T>
ostream &operator<<(ostream &os, const List1D<T> &list)
{
    os << list.toString();
    return os;
}




#endif /* INVENTORY_MANAGER_H */
