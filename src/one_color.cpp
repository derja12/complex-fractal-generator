#include "image_menu.h"
#include "PPM.h"
#include "Image.h"
#include <utility>
#include <iostream>

int main( )
{
	int returnVal;
	
	returnVal = askForUserValue(std::cin, std::cout);

	return returnVal;
}