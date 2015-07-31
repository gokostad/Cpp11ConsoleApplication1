#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <atomic>

#include "LinkedListManipulation.h"

static const char FILENAME[] = "LinkedListManipulation => ";


void NodeVal::makeString()
{
    std::ostringstream ostr;
    ostr << value;
    strValue = ostr.str();
}

LinkedListManipulation::~LinkedListManipulation()
{
    if (autoDestruct)
    {
        deleteAll(&this->head);
    }
}


void LinkedListManipulation::printLL(LLNode<INodeVal*> *head)
{
    std::cout << std::endl;
    LLNode<INodeVal*> *next = head;
    while (next != nullptr)
    {
        if (next->getValue() != nullptr)
            std::cout << " " << next->getValue()->toString();
        else
            std::cout << " X" << next->getValue()->toString();
        next = next->next;
    }
    std::cout << std::endl;
}

void LinkedListManipulation::deleteAll(LLNode<INodeVal*> **head)
{
    while (head != nullptr && *head != nullptr)
    {
        LLNode<INodeVal*> *next = (*head)->next;
        //TODO: what if T is not class and heap object 
        //for example int???
        if ((*head)->value != nullptr)
            delete (*head)->value;

        delete *head;
        *head = next;
    }
    *head = nullptr;
}


void LinkedListManipulation::push(LLNode<INodeVal*> *val)
{
    if (val == nullptr)
        return;
    
    //maybe we received another linked list
    LLNode<INodeVal*> *back = val;
    while (back->next != nullptr)
    {
        back = back->next;
    }
    back->next = nullptr;

    if (head == nullptr)
        head = val;
    else
    {
        back->next = head;
        head = val;
    }
}

LLNode<INodeVal*> *LinkedListManipulation::pop()
{
    if (head == nullptr)
        return nullptr;

    LLNode<INodeVal*> *oldHead = head;
    head = head->next;
    return oldHead;
}
/*
void *LinkedListManipulation::insertOnPosition(LLNode<INodeVal*> *llNode, int n)
{
    LLNode<INodeVal*> const *top = head;
    while (top)
    {
        if (--n = 0)
        {
            //std::atomic_exchange()
        }
        top = top->next;
    }
}
*/
void LinkedListManipulation::remove(LLNode<INodeVal*> const *llNode)
{
    if (head == nullptr)
        return;
    LLNode<INodeVal*> *headR = head;
    LLNode<INodeVal*> *prev = nullptr;
    while (headR != nullptr)
    {
        if (headR == llNode)
        {
            if (prev != nullptr)
            {
                prev->next = headR->next;
            }
            else
            {
                head = head->next;
            }
            return;
        }
        prev = headR;
        headR = headR->next;
    }
}

LLNode<INodeVal*>* LinkedListManipulation::getNth(int n) const
{
    int count = 0;

    LLNode<INodeVal*> *headR = head;
    while (headR != nullptr)
    {
        if (count++ == n)
            return headR;
        headR = headR->next;
    }
    return nullptr;
}

LLNode<INodeVal*>* LinkedListManipulation::removeNth(int n)
{
    LLNode<INodeVal*>* node = getNth(n);
    if (node != nullptr)
    {
        remove(node);
    }
    return node;
}


LLNode<INodeVal*> *LinkedListManipulation::reverseLL(LLNode<INodeVal*> *headToReverse)
{
    if (headToReverse == nullptr || headToReverse->next == nullptr)
        return nullptr;
    LLNode<INodeVal*> *nextNode = headToReverse->next;
    headToReverse->next = nullptr;
    while (nextNode != nullptr)
    {
        LLNode<INodeVal*> *nextNextNode = nextNode->next;
        nextNode->next = headToReverse;
        headToReverse = nextNode;
        nextNode = nextNextNode;
    }
    return headToReverse;
}

void LinkedListManipulation::reverseLL(LLNode<INodeVal*> **headToReverse)
{
    if (headToReverse == nullptr || (*headToReverse) == nullptr ||
        (*headToReverse)->next == nullptr)
        return;
    LLNode<INodeVal*> *nextNode = (*headToReverse)->next;
    (*headToReverse)->next = nullptr;
    while (nextNode != nullptr)
    {
        LLNode<INodeVal*> *nextNextNode = nextNode->next;
        nextNode->next = (*headToReverse);
        (*headToReverse) = nextNode;
        nextNode = nextNextNode;
    }
}

void LinkedListManipulation::reverseK(LLNode<INodeVal*> **headToReverse, int k)
{
    if (headToReverse == nullptr
        || (*headToReverse) == nullptr
        || (*headToReverse)->next == nullptr
        || k <= 1)
        return;
    LLNode<INodeVal*> *saveTop = *headToReverse;
    LLNode<INodeVal*> *nextNode = (*headToReverse)->next;
    (*headToReverse)->next = nullptr;
    while (nextNode != nullptr && k-- > 1)
    {
        LLNode<INodeVal*> *nextNextNode = nextNode->next;
        nextNode->next = (*headToReverse);
        (*headToReverse) = nextNode;
        nextNode = nextNextNode;
    }
    saveTop->next = nextNode;
}

bool LinkedListManipulation::detectLoop(LLNode<INodeVal*> *head)
{
    if (head == nullptr || head->next == nullptr)
        return false;
    LLNode<INodeVal*> *nextNode = head;
    LLNode<INodeVal*> *next2Node = head;

    while (nextNode && next2Node && nextNode->next != nullptr)
    {
        nextNode = nextNode->next;
        next2Node = next2Node->next->next;
        if (nextNode == next2Node)
            return true;
    }
    return false;
}

int LinkedListManipulation::length(LLNode<INodeVal*> *head) 
{
    if (head == nullptr)
        return 0;
    return 1 + length(head->next);
}

bool LinkedListManipulation::isPalindrome(LLNode<INodeVal*> *head)
{
    if (head == nullptr)
        return false;

    LLNode<INodeVal*> *top = head;
    LLNode<INodeVal*> *back = head;
    bool isOdd = false;
    bool result = true;

    back = findMiddleElement(head, isOdd);
    if (isOdd)
    {
        back = back->next;
    }

    back = LinkedListManipulation::reverseLL(back);

    LLNode<INodeVal*> *backFw = back;

    while (backFw != nullptr)
    {
        if (top->value->get() != backFw->value->get())
        {
            result = false;
            break;
        }
        top = top->next;
        backFw = backFw->next;
    }

    back = LinkedListManipulation::reverseLL(back);
    return result;
}

LLNode<INodeVal*> *LinkedListManipulation::findMiddleElement(LLNode<INodeVal*> *head, bool& isOdd)
{
    isOdd = false;
    if (head == nullptr)
        return nullptr;

    LLNode<INodeVal*> *top1 = head;
    LLNode<INodeVal*> *top2 = head;

    while (top2 != nullptr && top2->next != nullptr)
    {
        top1 = top1->next;
        top2 = top2->next->next;
    }
    if (top2 != nullptr)
        isOdd = true;
    return top1;
}

void LinkedListManipulation::mergeExample()
{
    LinkedListManipulation *ll1 = new
        LinkedListManipulation(new LLNode<INodeVal *>(new NodeVal(1)), true);
    ll1->push(new LLNode<INodeVal *>(new NodeVal(2)));
    ll1->push(new LLNode<INodeVal *>(new NodeVal(30)));
    ll1->push(new LLNode<INodeVal *>(new NodeVal(40)));
    ll1->push(new LLNode<INodeVal *>(new NodeVal(50)));

    LinkedListManipulation *ll2 = new
        LinkedListManipulation(new LLNode<INodeVal *>(new NodeVal(21)), true);
    ll2->push(new LLNode<INodeVal *>(new NodeVal(22)));
    ll2->push(new LLNode<INodeVal *>(new NodeVal(43)));

    //LinkedListManipulation *llR = new
    //    LinkedListManipulation(nullptr, true);

    LLNode<INodeVal *> *head1 = ll1->head;
    LLNode<INodeVal *> *head2 = ll2->head;
    LLNode<INodeVal *> *head;

    std::cout << "\nmergeExample\n";
    printLL(head1);
    printLL(head2);

    if (head1->value->get() > head2->value->get())
    {
        head = head1;
        head1 = head1->next;
    }
    else
    {
        head = head2;
        head2 = head2->next;
    }
    head->next = nullptr;
    LLNode<INodeVal *> *headRet = head;

    while (head1 != nullptr && head2 != nullptr)
    {
        if (head1->value->get() > head2->value->get())
        {
            head->next = head1;
            head1 = head1->next;
        }
        else
        {
            head->next = head2;
            head2 = head2->next;
        }
        head = head->next;
        head->next = nullptr;
    }

    if (head1 == nullptr)
        head->next = head2;
    else if (head2 == nullptr)
        head->next = head1;
   
    printLL(headRet);

    deleteAll(&headRet);
    ll1->head = nullptr;
    ll2->head = nullptr;
    delete ll1;
    delete ll2;
}

void LinkedListManipulation::Main_LinkedListManipulation()
{
    /*** BEGIN OF FILE ***/
    std::cout << "\n------ BOF " << FILENAME << " ----\n";

    LinkedListManipulation *ll = new 
        LinkedListManipulation(
             new LLNode<INodeVal *>(new NodeVal(1)), true);
    ll->push(new LLNode<INodeVal *>(new NodeVal(2)));
    ll->push(new LLNode<INodeVal *>(new NodeVal(3)));
    ll->push(new LLNode<INodeVal *>(new NodeVal(4)));
    ll->push(new LLNode<INodeVal *>(new NodeVal(5)));
    ll->push(new LLNode<INodeVal *>(new NodeVal(5)));
    ll->push(new LLNode<INodeVal *>(new NodeVal(6)));
    ll->push(new LLNode<INodeVal *>(new NodeVal(7)));
    ll->push(new LLNode<INodeVal *>(new NodeVal(8)));
    ll->push(new LLNode<INodeVal *>(new NodeVal(9)));
    printLL(ll->head);

    ll->head = LinkedListManipulation::reverseLL(ll->head);

    printLL(ll->head);

    LinkedListManipulation::reverseLL(&ll->head);

    printLL(ll->head);

    LinkedListManipulation::reverseK(&(ll->head->next->next->next->next->next->next->next), 4);

    printLL(ll->head);

    std::cout << "\nIs palindrome=" << ll->isPalindrome(ll->head) << "\n";
    std::cout << "\nLenght LL=" << ll->length(ll->head) << "\n";

    printLL(ll->head);

    mergeExample();

    delete ll;

    /*** END OF FILE ***/
    std::cout << std::endl << "------ EOF " << FILENAME << " ----" << std::endl << std::endl;
}
