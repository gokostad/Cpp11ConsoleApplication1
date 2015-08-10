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

//insert in already sorted linked list new node in sorted order
void LinkedListManipulation::sortedInsert(LLNode<INodeVal*>*& pHead, LLNode<INodeVal*>* llNode)
{
    NodeVal nodeVal(0);
    LLNode<INodeVal*> top(&nodeVal);
    top.next = pHead;

    LLNode<INodeVal*>* prevHead = &top;

    while (top.next)
    {
        if (top.next->getValue()->get() > llNode->getValue()->get())
        {
            LLNode<INodeVal*>* tmp = top.next;
            prevHead->next = llNode;
            llNode->next = tmp;
            if (prevHead == &top)
                pHead = llNode;
            break;
        }
        prevHead = top.next;
        top.next = top.next->next;
    }
    //if it should be inserted in last position
    if (!top.next)
    {
        prevHead->next = llNode;
    }
    if (!pHead)
        pHead = llNode;
}

void LinkedListManipulation::sortedInsert1(LLNode<INodeVal*>*& pHead, LLNode<INodeVal*>* llNode)
{
    if (!pHead || !pHead->next)
    {
        llNode->next = pHead;
        pHead = llNode;
        return;
    }

    LLNode<INodeVal*>* prev = pHead;
    while (prev->next->getValue()->get() < llNode->getValue()->get())
    {
        prev = prev->next;
    }

    llNode->next = pHead->next;
    pHead->next = llNode;
}


void LinkedListManipulation::sortedInsert3(LLNode<INodeVal*>** headRef, LLNode<INodeVal*>* newNode)
{
    LLNode<INodeVal*>** currentRef = headRef;
    while (currentRef && (*currentRef)->getValue()->get() < newNode->getValue()->get())
    {
        currentRef = &((*currentRef)->next);
    }
    newNode->next = *currentRef;
    *currentRef = newNode;
}

void LinkedListManipulation::sortedInsert4(LLNode<INodeVal*>*& headRef, LLNode<INodeVal*>* newNode)
{
    LLNode<INodeVal*>** currentRef = &headRef;
    while (currentRef!=NULL && (*currentRef)->getValue()->get() < newNode->getValue()->get())
    {
        currentRef = &((*currentRef)->next);
    }
    newNode->next = *currentRef;
    *currentRef = newNode;
}

//sort linked list using sortedInsert
void LinkedListManipulation::insertSort(LLNode<INodeVal*>*& head)
{

}

/*
void LinkedListManipulation::sortedInsert(LLNode<INodeVal*>* llNode)
{
    NodeVal nodeVal(0);
    LLNode<INodeVal*> top(&nodeVal);
    top.next = head;

    LLNode<INodeVal*>* prevHead = &top;

    while (head)
    {
        LLNode<INodeVal*>* loopHead = top.next;
        LLNode<INodeVal*>* prevLoopHead = &top;

        while (loopHead != head)
        {
            if (loopHead->getValue()->get() > head->getValue()->get())
            {
                prevHead->next = head->next;
                LLNode<INodeVal*>* tmp = head;
                head = prevHead;
                tmp->next = loopHead;
                prevLoopHead->next = tmp;
                break;
            }
            prevLoopHead = loopHead;
            loopHead = loopHead->next;
        }
        prevHead = head;
        head = head->next;
    }
    head = top.next;
}
*/

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
    ll->push(new LLNode<INodeVal *>(new NodeVal(9)));
    ll->push(new LLNode<INodeVal *>(new NodeVal(11)));
    ll->push(new LLNode<INodeVal *>(new NodeVal(14)));
    ll->push(new LLNode<INodeVal *>(new NodeVal(20)));
    printLL(ll->head);

/*
// Test sortedInsert at the top
    LLNode<INodeVal *> *headT = nullptr;
    LLNode<INodeVal *> *node1 = new LLNode<INodeVal *>(new NodeVal(23));
    sortedInsert(headT, node1);
    printLL(headT);

    LLNode<INodeVal *> *node2 = new LLNode<INodeVal *>(new NodeVal(25));
    sortedInsert(headT, node2);
    printLL(headT);

    delete node1;
    delete node2;
*/

    ll->head = LinkedListManipulation::reverseLL(ll->head);

    printLL(ll->head);


    ll->sortedInsert2(ll->head, new LLNode<INodeVal *>(new NodeVal(10)));
    //ll->sortedInsert2(ll->head, new LLNode<INodeVal *>(new NodeVal(0)));
    //ll->sortedInsert2(ll->head, new LLNode<INodeVal *>(new NodeVal(25)));

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
