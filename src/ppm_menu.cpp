#include "image_menu.h"
#include "MenuData.h"
#include <utility>
#include <iostream>
#include <cstdlib>
#include <ctime>

int main( )
{
	std::srand(std::time(0));
	return imageMenu(std::cin, std::cout);
}