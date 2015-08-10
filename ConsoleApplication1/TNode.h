#pragma once


template <class T>
struct TNode
{
public:
    TNode(T& value, TNode<T>* next = nullptr);
    virtual ~TNode();

    bool operator < (const TNode<T>& node) const;
    bool operator > (const TNode<T>& node) const;
    bool operator == (const TNode<T>& node) const;
    bool operator != (const TNode<T>& node) const { return !(*this == node;) }

public:
    T& value;
    TNode<T>* next;
};