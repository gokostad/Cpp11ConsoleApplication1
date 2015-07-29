#include "stdafx.h"
#include <iostream>

#include "PlayingWithTemplate1.h"

static const char FILENAME[] = "PlayingWithTemplate1 => ";

template <typename T>
struct structPWT1
{
    structPWT1(T& storage) : value(storage) {}

    int size() const
    {
        std::cout << "\n" << FILENAME << "structPWT1 type = " << typeid(T).name() << "\n";;
        return 1;
    }

    T& value;
};

class classPWT1_airplane
{
public:
    classPWT1_airplane(int i) { this->i = i; }

    int size() const { return i; }

private:
    int i;
};

//function with template <template <class> class A> parameter
template <template <class> class A, class B>
auto functionWithTemplateTemplate(const A<B>& p) -> decltype(p.size())
{
    return p.size();
}

//template function
template <typename A>
auto functionWithTemplate(const A& p) -> decltype(p.size())
{
    structPWT1<A> p1(const_cast<A&>(p));
    return functionWithTemplateTemplate(p1);
}


void Main_PlayingWithTemplate1()
{
    /*** BEGIN OF FILE ***/
    std::cout << "\n------ BOF " << FILENAME << " ----\n";


    classPWT1_airplane c1(1);
    functionWithTemplate(c1);

    structPWT1<classPWT1_airplane> s1(c1);
    functionWithTemplateTemplate<structPWT1, classPWT1_airplane>(s1);


    /*** END OF FILE ***/
    std::cout << "\n------ EOF " << FILENAME << " ----\n\n";
}