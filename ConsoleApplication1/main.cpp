#include <QCoreApplication>

#include "stdafx.h"
#include <iostream>

#include "PlayingWithTemplate1.h"
#include "PlayWithFunctorsLambdasFunctions.h"
#include "LinkedListManipulation.h"
#include "Tree.h"


void f(int& x)
{
    x = 5;
}

void f1(int* x)
{
    *x = 5;
}

void callF()
{
    int z = 4;
    int z1 = 4;

    f(z);
    f1(&z1);
}

char *mia = "Mia";
char *laza = "Laza";

void f11(char*& s)
{
    char*& s1 = s;
    s1 = laza;
}

void f12(char** s)
{
    char** s1 = s;
    *s1 = laza;
}

void f3()
{
    char c = 'M';
    char& x = c;
    char* pX = &x;

}

int main(int argc, char *argv[])
{
    f3();
    char* s = mia;
    f12(&s);
    f11(s);

    callF();
    QCoreApplication a(argc, argv);

    Main_PlayingWithTemplate1();

    Main_PlayWithFunctorsLambdasFunctions();

    LinkedListManipulation::Main_LinkedListManipulation();

    Tree::main();

    std::cout << "\n\nPress ENTER to exit";
    std::cin.get();

    return a.exec();
}


