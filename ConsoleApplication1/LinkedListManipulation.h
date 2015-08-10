#pragma once

#include <iostream>

class INodeVal
{
public:
    virtual ~INodeVal() {}
    virtual std::string toString() const = 0;
    virtual int get() const = 0;
    virtual void set(int val) = 0;
};

class NodeVal : public INodeVal
{
public:
    NodeVal(int val) : value(val)
    {
        makeString();
    }

    virtual ~NodeVal() {}

    int get() const { return value; }
    void set(int val) { value = val; makeString(); }

    virtual std::string toString() const {
        return strValue;
    }

protected:
    void makeString(); 

private:
    int value;
    std::string strValue;
};

template <class T>
class LLNode
{
public:
    LLNode(T val, LLNode<T> *nextLL = nullptr) :
        next(nextLL),
        value(val)
    {}

    T getValue() { return value; }

protected:
    LLNode<T> *next;

private:
    T value;

    friend class LinkedListManipulation;
};


class LinkedListManipulation
{
public:
    LinkedListManipulation(LLNode<INodeVal*> *llNode = nullptr,
                           bool autoDelete = false) :
        head(llNode),
        autoDestruct(autoDelete)
    {}

    virtual ~LinkedListManipulation();

    static void printLL(LLNode<INodeVal*> *head);
    static void deleteAll(LLNode<INodeVal*> **head);

    void push(LLNode<INodeVal*> *llNode);
    LLNode<INodeVal*> *pop();
    
    //just remove from the list,  it is not deleted from memory
    void remove(LLNode<INodeVal*> const *llNode);
    LLNode<INodeVal*>* removeNth(int n);
    LLNode<INodeVal*>* getNth(int n) const;
    //insert in already sorted linked list new node in sorted order
    static void sortedInsert(LLNode<INodeVal*>*& head, LLNode<INodeVal*>* llNode);
    static void sortedInsert1(LLNode<INodeVal*>*& head, LLNode<INodeVal*>* llNode);
    static void sortedInsert3(LLNode<INodeVal*>** head, LLNode<INodeVal*>* llNode);
    static void sortedInsert4(LLNode<INodeVal*>*& head, LLNode<INodeVal*>* llNode);
    //sort linked list using sortedInsert
    void insertSort(LLNode<INodeVal*>*& head);

    static int length(LLNode<INodeVal*> *head);

    static LLNode<INodeVal*> *reverseLL(LLNode<INodeVal*> *headToReverse);
    static void reverseLL(LLNode<INodeVal*> **headToReverse);

    static void reverseK(LLNode<INodeVal*> **headToReverse, int k);

    static bool detectLoop(LLNode<INodeVal*> *head);

    static LLNode<INodeVal*> *findMiddleElement(LLNode<INodeVal*> *head, bool& isOdd);

    static bool isPalindrome(LLNode<INodeVal*> *head); // R A D A R  or  L A P P A L 

    static void mergeExample();

    //test case for manipulating LL
    static void Main_LinkedListManipulation();

private:
    LLNode<INodeVal*> *head;
    bool autoDestruct;
};

