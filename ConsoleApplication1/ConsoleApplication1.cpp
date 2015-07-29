// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "PlayingWithTemplate1.h"
#include "PlayWithFunctorsLambdasFunctions.h"
#include "LinkedListManipulation.h"
#include "Tree.h"

int _tmain(int argc, _TCHAR* argv[])
{
    Main_PlayingWithTemplate1();

    Main_PlayWithFunctorsLambdasFunctions();

    LinkedListManipulation::Main_LinkedListManipulation();

    Tree::main();

    std::cout << "\n\nPress ENTER to exit";
    std::cin.get();
	return 0;
}
