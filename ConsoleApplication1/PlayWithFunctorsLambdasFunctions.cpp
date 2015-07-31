#include "stdafx.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <typeinfo>
#include <functional>

//#include <boost\lambda\lambda.hpp>
//#include <boost\thread\mutex.hpp>
#include "PlayWithFunctorsLambdasFunctions.h"

static const char FILENAME[] = "PlayWithFunctorsLambdasFunctions => ";

/*
* http://ciere.com/cppnow12/lambda.pdf Page 116 example
*
*/

struct machine
{
    template< typename T >
    void add(T f)
    {
        to_do.push_back(f);
    }
    int run(int v)
    {
        std::for_each(to_do.begin(), to_do.end(),
            [&v](std::function<int(int)> f)
        { v = f(v); });
        return v;
    }
    std::vector< std::function<int(int)> > to_do;
};

int foo(int i){ return i + 4; }


typedef std::function<int(int)> intIntF;

class CallableQueue
{
private:
    std::queue<intIntF> q;
public:
    void add(intIntF f)
    {
        q.push(f);
    }

    int run(int init)
    {
        if (!q.empty())
        {
            init = q.back()(init);
            q.pop();
            return run(init);
        }
        return init;
    }
};

int fun1(int i)
{
    std::cout << i << '\n';
    return i + 1;
}

/****************************/

template <typename T>
struct product
{
    product(T & storage) : value(storage) {}

    template <typename V>
    void operator()(V& v)
    {
        value *= v;
    }

    int size()
    {
        std::cout << "product<T>::size()\n";
        return 1;
    }

    T& value;
};

template <class T>
void fill(std::vector<int> &v, T done)
{
    machine m;
    m.add([](int i){ return i * 3; });
    m.add(foo);
    m.add([](int i){ return i / 5; });

    std::cout << "run(7) : " << m.run(7) << std::endl;

    int i = 0;
    while (!done())
    {
        v.push_back(i++);
    }
}


/*
template <class T>
struct sizeOfReference
{
    T& t;
    int i;
    sizeOfReference(T& rt, int pi) : t(rt) i(pi) {}
};
*/

typedef int(*callbackMain)();

void funcCallbackParam(callbackMain pf)
{
    pf();
    return;
}
/*
class Person
{
public:
enum PersonType {ME, YOU};
void setPersonType(PersonType p) { this->p = p; }
PersonType getPersonType() { return this->p; }

private:
PersonType p;
};
*/

void Main_PlayWithFunctorsLambdasFunctions()
{
    /*** BEGIN OF FILE ***/
    std::cout << "\n------ BOF " << FILENAME << " ----\n";

    funcCallbackParam([]() -> int { return 2; });


    //std::cout << sizeof(sizeOfReference<CallableQueue>);

    int totalMux = 1;
    std::vector<int> vector;

    for (int i = 1; i < 10; i++)
        vector.push_back(i);

    std::vector<int>::const_iterator vector_begin = vector.begin();
    std::vector<int>::const_iterator vector_end = vector.end();

    while (vector_begin != vector_end)
    {
        totalMux *= *vector_begin;
        vector_begin++;
    }

    std::cout << totalMux << '\n';

    totalMux = 1;
    for_each(vector.begin(), vector.end(), product<int>(totalMux));

    for_each(vector.begin(), vector.end(), [&totalMux](int i){ totalMux *= i; });

    vector.clear();

    fill(vector, [&]()
    {
        int sume = 0;
        for_each(vector.begin(), vector.end(), [&](int i){ sume += i; });
        return sume > 30;
    });

    int intI = 2;

    auto two = [=]() mutable -> int{ intI *= 2; return intI; } ();

    std::cout << "i=" << intI << "; two=" << two << '\n';
    std::cout << typeid(two).name() << '\n';

    int pp = 2;
    product<int> p(pp);
    std::function<int()> f;
    f = std::bind(&product<int>::size, std::ref(p));

    f();


    /*** END OF FILE ***/
    std::cout << "\n------ EOF " << FILENAME << " ----\n\n";
}
