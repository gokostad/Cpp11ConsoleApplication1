#include "stdafx.h"
#include <iostream>
#include "TNode.h"


template <class T>
TNode<T>::TNode(T& pValue, TNode<T>* pNext = nullptr) :
    value(pValue),
    next(pNext)
{}

template <class T>
TNode<T>::~TNode()
{}

template <class T>
bool TNode<T>::operator < (const TNode<T>& node) const
{
    return value < node;
}

template <class T>
bool TNode<T>::operator > (const TNode<T>& node) const 
{
    return value > node;
}

template <class T>
bool TNode<T>::operator == (const TNode<T>& node) const
{
    return value == node;
}
