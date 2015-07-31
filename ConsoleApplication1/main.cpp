#include <QCoreApplication>

#include "stdafx.h"
#include <iostream>

#include "PlayingWithTemplate1.h"
#include "PlayWithFunctorsLambdasFunctions.h"
#include "LinkedListManipulation.h"
#include "Tree.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Main_PlayingWithTemplate1();

    Main_PlayWithFunctorsLambdasFunctions();

    LinkedListManipulation::Main_LinkedListManipulation();

    Tree::main();

    std::cout << "\n\nPress ENTER to exit";
    std::cin.get();

    return a.exec();
}
