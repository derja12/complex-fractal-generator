#include <iostream>
#include <fstream>
#include "image_menu.h"
#include "Image.h"
#include "PPM.h"
#include "ActionData.h"
#include "MenuData.h"
#include "NumberGrid.h"
#include "ComplexFractal.h"
#include "JuliaSet.h"
#include "ColorTable.h"
#include "MandelbrotSet.h"
#include <cmath>

std::string getString( ActionData& action_data, const std::string& prompt ) {

	std::string str1;
	
	if (not action_data.getQuiet())
	{
		action_data.getOS() << prompt;
	}
	action_data.getIS() >> str1;

	return str1;
}
int getInteger( ActionData& action_data, const std::string& prompt ) {

	int number;
	if (not action_data.getQuiet())
	{
		action_data.getOS() << prompt;
	}
	action_data.getIS() >> number;

	return number;
}
double getDouble( ActionData& action_data, const std::string& prompt ) {

	double dub1;
	
	if (not action_data.getQuiet())
	{
		action_data.getOS() << prompt;
	}
	action_data.getIS() >> dub1;

	return dub1;
}

int assignment1( std::istream& is, std::ostream& os ) {

	ActionData action_data(is, os);
	int fave_line;
	std::string fave_color;
	double fave_number;

	fave_color = getString(action_data, "What's your favorite color? ");
	fave_line = getInteger(action_data, "What's your favorite integer? ");
	fave_number = getDouble(action_data, "What's your favorite number? ");

	int i;

	for (i = 0; i < fave_line; i++) {
		os << (i + 1) << " " << fave_color << " " << fave_number << std::endl;
	}
	return fave_line;
}

void drawAsciiImage( ActionData& action_data ) 
{
	int Row;
	int Column;
	char c;
	
	for (Row = 0; Row < action_data.getOutputImage().getHeight(); Row++)
	{
		for (Column = 0; Column < action_data.getOutputImage().getWidth(); Column++)
		{
			double scale;
			scale = (action_data.getOutputImage().getChannel(Row, Column, 0) + action_data.getOutputImage().getChannel(Row, Column, 1) + action_data.getOutputImage().getChannel(Row, Column, 2)) / 765.0;
			if (scale >= 1.0) 
			{
				c = '@';
			}
			else if (scale >= 0.9) 
			{
				c = '#';
			}
			else if (scale >= 0.8) 
			{
				c = '%';
			}
			else if (scale >= 0.7) 
			{
				c = '*';
			}
			else if (scale >= 0.6) 
			{
				c = '|';
			}
			else if (scale >= 0.5) 
			{
				c = '+';
			}
			else if (scale >= 0.4) 
			{
				c = ';';
			}
			else if (scale >= 0.3) 
			{
				c = '~';
			}
			else if (scale >= 0.2) 
			{
				c = '-';
			}
			else if (scale >= 0.1) 
			{
				c = '.';
			}
			else  
			{
				c = ' ';
			}
			action_data.getOS() << c;
		}
		action_data.getOS() << std::endl;
	}	
}
int assignment2( std::istream& is, std::ostream& os ) 
{

	ActionData action_data(is, os);
	int cHeight;
	int cWidth;
	int Row;
	int Column;
	int R;
	int G;
	int B;

	cHeight = getInteger(action_data, "Image height? ");
	cWidth = getInteger(action_data, "Image width? ");
	action_data.getOutputImage().setHeight(cHeight);
	action_data.getOutputImage().setWidth(cWidth);
	action_data.getOutputImage().setMaxColorValue(255);

	for (Row = 0; Row < action_data.getOutputImage().getHeight(); Row++)
	{
		for (Column = 0; Column < action_data.getOutputImage().getWidth(); Column++)
		{
			if (Row < action_data.getOutputImage().getHeight()/2)
			{
				R = 0;
			}
			else 
			{
				R = 255;
			}
			if (Column < action_data.getOutputImage().getWidth()/2)
			{
				B = 0;
			}
			else 
			{
				B = 255;
			}
			G = ((2 * Row) + (2 * Column))% 256;
			action_data.getOutputImage().setChannel(Row, Column, 0, R);
			action_data.getOutputImage().setChannel(Row, Column, 1, G);
			action_data.getOutputImage().setChannel(Row, Column, 2, B);
				
		}
	}

	drawAsciiImage(action_data);

	return 0;

}

void writeUserImage( ActionData& action_data )
{
	std::string filename;

	filename = getString(action_data , "Output filename? ");

	std::ofstream fout(filename, std::ios::binary);

	action_data.getOutputImage().writeStream(fout);

	fout.close();

}

int assignment3( std::istream& is, std::ostream& os )
{
	ActionData action_data(is, os);
	int w;
	int h;
	int max;
	int Row;
	int Column;
	int R;
	int G;
	int B;

	h = getInteger(action_data,"Image height? ");

	w = getInteger(action_data,"Image width? ");

	max = (h + w)/3;
	if (max > 255)
	{
		max = 255;
	}
	action_data.getOutputImage().setMaxColorValue(max);
	action_data.getOutputImage().setWidth(w);
	action_data.getOutputImage().setHeight(h);
	


	for (Row = 0; Row < action_data.getOutputImage().getHeight(); Row++)
	{
		for (Column = 0; Column < action_data.getOutputImage().getWidth(); Column++)
		{
			if (Row < action_data.getOutputImage().getHeight()/2)
			{
				R = 0;
			}
			else if (Row%3 == 0) 
			{
				R = 0;
			}
			else
			{
				R = max;
			}
			if (Column < Row)
			{
				B = 0;
			}
			else 
			{
				B = max;
			}
			G = (Row + action_data.getOutputImage().getWidth() - Column - 1) % (1 + max);
			action_data.getOutputImage().setChannel(Row, Column, 0, R);
			action_data.getOutputImage().setChannel(Row, Column, 1, G);
			action_data.getOutputImage().setChannel(Row, Column, 2, B);
				
		}
	}

	writeUserImage(action_data);

	return 0;
}

int askForUserValue( std::istream& is, std::ostream& os )
{
	int givenValueR;
	int givenValueG;
	int givenValueB;
	ActionData action_data(is,os);

	int Row;
	int Column;

	int h;
	int w;
	int max;

	givenValueR = getInteger(action_data, "What Value would you like to assign for Red? ");
	givenValueG = getInteger(action_data, "What Value would you like to assign for Green? ");
	givenValueB = getInteger(action_data, "What Value would you like to assign for Blue? ");


	h = getInteger(action_data,"Image height? ");

	w = getInteger(action_data,"Image width? ");

	max = (h + w)/3;
	if (max > 255)
	{
		max = 255;
	}
	action_data.getOutputImage().setMaxColorValue(max);


	for (Row = 0; Row < action_data.getOutputImage().getHeight(); Row++)
	{
		for (Column = 0; Column < action_data.getOutputImage().getWidth(); Column++)
		{
			if (givenValueR > action_data.getOutputImage().getMaxColorValue()) {
				givenValueR = action_data.getOutputImage().getMaxColorValue();
			}

			if (givenValueG > action_data.getOutputImage().getMaxColorValue()) {
				givenValueG = action_data.getOutputImage().getMaxColorValue();
			}

			if (givenValueB > action_data.getOutputImage().getMaxColorValue()) {
				givenValueB = action_data.getOutputImage().getMaxColorValue();
			}

			action_data.getOutputImage().setChannel(Row, Column, 0, givenValueR);
			action_data.getOutputImage().setChannel(Row, Column, 1, givenValueG);
			action_data.getOutputImage().setChannel(Row, Column, 2, givenValueB);
				
		}
	}

	writeUserImage(action_data);

	return 0;
}

int hero(std::istream& is, std::ostream& os) 
{
	ActionData action_data(is,os);
	int birth_year;
	std::string name;

	name = getString(action_data, "Who is your hero? ");
	birth_year = getInteger(action_data, "What year were they born? ");	

	os << name << " was born in " << birth_year << "." << std::endl;

	return birth_year;
}

int four_square_ascii(std::istream& is, std::ostream& os) 
{
	int size;
	int Row;
	int Column;
	int R;
	int G;
	int B;
	ActionData action_data(is,os);

	size = getInteger(action_data, "Image size? ");
	action_data.getOutputImage().setWidth(size);
	action_data.getOutputImage().setHeight(size);

	for (Row = 0; Row < action_data.getOutputImage().getHeight(); Row++)
	{
		for (Column = 0; Column < action_data.getOutputImage().getWidth(); Column++)
		{
			if (Row < action_data.getOutputImage().getHeight()/2)
			{
				R = 127;
			}
			else 
			{
				R = 255;
			}
			if (Column < action_data.getOutputImage().getWidth()/2)
			{
				G = 0;
			}
			else 
			{
				G = 255;
			}
			B = 255;
			action_data.getOutputImage().setChannel(Row, Column, 0, R);
			action_data.getOutputImage().setChannel(Row, Column, 1, G);
			action_data.getOutputImage().setChannel(Row, Column, 2, B);
				
		}
	}

	drawAsciiImage(action_data);
	return 0;
}

std::string getChoice( ActionData& action_data )
{
	std::string choice;

	choice = getString(action_data, "Choice? ");

	return choice;
}

void copyImage(ActionData& action_data)
{
	action_data.getOutputImage() = action_data.getInputImage1();
}

void readUserImage1( ActionData& action_data )
{
	std::string getName;

	getName = getString( action_data, "Input filename? ");

	std::ifstream fin(getName, std::ios::binary);

	action_data.getInputImage1().readStream(fin);

	fin.close();
}

void commentLine( ActionData& action_data)
{
	unsigned char v;

	action_data.getIS().read((char*)&v, sizeof(v));

	while (action_data.getIS().good() && v != '\n')
	{
		action_data.getIS().read((char*)&v, sizeof(v));
	}

	return;
}

void setSize( ActionData& action_data )
{
	int h;
	int w;

	h = getInteger(action_data, "Height? ");
	w = getInteger(action_data, "Width? ");

	action_data.getInputImage1().setHeight(h);
	action_data.getInputImage1().setWidth(w);
}

void setMaxColorValue( ActionData& action_data)
{
	int mcv;

	mcv = getInteger(action_data, "Max color value? ");

	action_data.getInputImage1().setMaxColorValue(mcv);
}

void setChannel( ActionData& action_data)
{
	int row;
	int col;
	int cha;
	int val;

	row = getInteger(action_data, "Row? ");
	col = getInteger(action_data, "Column? ");
	cha = getInteger(action_data, "Channel? ");
	val = getInteger(action_data, "Value? ");

	action_data.getInputImage1().setChannel(row, col, cha, val);
}

void setPixel( ActionData& action_data)
{
	int row;
	int col;
	int red;
	int green;
	int blue;

	row = getInteger(action_data, "Row? ");
	col = getInteger(action_data, "Column? ");
	red = getInteger(action_data, "Red? ");
	green = getInteger(action_data, "Green? ");
	blue = getInteger(action_data, "Blue? ");

	action_data.getInputImage1().setChannel(row, col, 0, red);
	action_data.getInputImage1().setChannel(row, col, 1, green);
	action_data.getInputImage1().setChannel(row, col, 2, blue);

}

void clearAll( ActionData& action_data)
{
	int Row;
	int Column;

	for (Row = 0; Row < action_data.getInputImage1().getHeight(); Row++)
	{
		for (Column = 0; Column < action_data.getInputImage1().getWidth(); Column++)
		{
			action_data.getInputImage1().setChannel(Row, Column, 0, 0);
			action_data.getInputImage1().setChannel(Row, Column, 1, 0);
			action_data.getInputImage1().setChannel(Row, Column, 2, 0);

		}
	}
}

void quit(ActionData& action_data)
{
	action_data.setDone();
}

void showMenu( MenuData& menu_data, ActionData& action_data )
{
	/*
	std::vector<std::string>::iterator name;
	for(name = menu_data.getNames().begin(); p != menu_data.getNames().end(); name++)
	*/
	int items;
	int i;

	items = menu_data.getNames().size();

	for(i = 0; i < items; i++)
	{
		action_data.getOS() << menu_data.getNames()[i] << ") " << menu_data.getDescription(menu_data.getNames()[i]) << std::endl;
	}



}

void takeAction(const std::string& choice, MenuData& menu_data, ActionData& action_data)
{
	ActionFunctionType function;
	function = menu_data.getFunction(choice);

	if(function == 0)
	{
		if(choice == "menu")
		{
			showMenu(menu_data, action_data);
		}
		else
		{
			action_data.getOS() << "Unknown action '" << choice << "'." << std::endl;
		}
	}
	else
	{
		function(action_data);
	}
}

void configureMenu( MenuData& menu_data )
{
	menu_data.addAction("draw-ascii", drawAsciiImage, "Write output image to terminal as ASCII art.");
	menu_data.addAction("write", writeUserImage, "Write output image to file.");
	menu_data.addAction("copy", copyImage, "Copy input image 1 to output image.");
	menu_data.addAction("read1", readUserImage1, "Read file into input image 1.");
	menu_data.addAction("#", commentLine, "Comment to end of line.");
	menu_data.addAction("size", setSize, "Set the size of input image 1.");
	menu_data.addAction("max-color-value", setMaxColorValue, "Set the max color value of input image 1.");
	menu_data.addAction("channel", setChannel, "Set a channel value in input image 1.");
	menu_data.addAction("pixel", setPixel, "Set a pixel's 3 values in input image 1.");
	menu_data.addAction("clear", clearAll, "Set all pixels to 0,0,0 in input image 1.");
	menu_data.addAction("quit", quit, "Quit.");
	menu_data.addAction("read2", readUserImage2, "Read file into input image 2.");
	menu_data.addAction("+", plus, "Set output image from sum of input image 1 and input image 2.");
	menu_data.addAction("+=", plusEquals, "Set input image 1 by adding in input image 2.");
	menu_data.addAction("-", minus, "Set output image from difference of input image 1 and input image 2.");
	menu_data.addAction("-=", minusEquals, "Set input image 1 by subtracting input image 2.");
	menu_data.addAction("*", times, "Set output image from input image 1 multiplied by a number.");
	menu_data.addAction("*=", timesEquals, "Set input image 1 by multiplying by a number.");
	menu_data.addAction("/", divide, "Set output image from input image 1 divided by a number.");
	menu_data.addAction("/=", divideEquals, "Set input image 1 by dividing by a number.");
	menu_data.addAction("red-gray", grayFromRed, "Set output image from input image 1's grayscale from red.");
	menu_data.addAction("green-gray", grayFromGreen, "Set output image from input image 1's grayscale from green.");
	menu_data.addAction("blue-gray", grayFromBlue, "Set output image from input image 1's grayscale from blue.");
	menu_data.addAction("linear-gray", grayFromLinearColorimetric, "Set output image from input image 1's grayscale from linear colorimetric.");
	menu_data.addAction("circle", drawCircle, "Draw a circle shape in input image 1.");
	menu_data.addAction("box", drawBox, "Draw a box shape in input image 1.");
	menu_data.addAction("copy12", copyImage1ToImage2, "Copy input image 1 to input image 2.");
	menu_data.addAction("*=-ppm", timesEqualsPPM, "Set input image 1 by multiplying by input image 2.");
	menu_data.addAction("orange", orangeFilter, "Set output image from input image 1's orange filter.");
	menu_data.addAction("grid", configureGrid, "Configure the grid.");
	menu_data.addAction("grid-set", setGrid, "Set a single value in the grid.");
	menu_data.addAction("grid-apply", applyGrid, "Use the grid values to set colors in the output image.");
	menu_data.addAction("fractal-plane-size", setFractalPlaneSize, "Set the dimensions of the grid in the complex plane.");
	menu_data.addAction("fractal-calculate", calculateFractal, "Calculate the escape values for the fractal, multi-thread.");
	menu_data.addAction("julia-parameters", setJuliaParameters, "Set the parameters of the Julia Set function.");
	menu_data.addAction("fractal-calculate-single-thread", calculateFractalSingleThread, "Calculate the escape values for the fractal, single-thread.");
	menu_data.addAction("grid-apply-color-table", applyGridColorTable, "Use the grid values to set colors in the output image using the color table.");
	menu_data.addAction("set-color-table-size", setColorTableSize, "Change the number of slots in the color table.");
	menu_data.addAction("set-color", setColor, "Set the RGB values for one slot in the color table.");
	menu_data.addAction("set-random-color", setRandomColor, "Randomly set the RGB values for one slot in the color table.");
	menu_data.addAction("set-color-gradient", setColorGradient, "Smoothly set the RGB values for a range of slots in the color table.");
	menu_data.addAction("julia-four", setJuliaFourFractal, "Choose to make a Julia set with the fourth power function.");
	menu_data.addAction("escape-radius", setEscapeRadius, "Set the fractal escape radius.");
	menu_data.addAction("set-inverted-color-gradient", setInvertedColorGradient, "Smoothly set the values for a range of slots in the color table, using a color and its inverse.");
	menu_data.addAction("julia", setJuliaFractal, "Choose to make a Julia set.");
	menu_data.addAction("mandelbrot", setMandelbrotFractal, "Choose to make a Mandelbrot set.");
	menu_data.addAction("quiet", toggleQuiet, "Silences the prompts.");
	menu_data.addAction("burning-ship", setBurningShipFractal, "Choose to make a Mandelbrot set with the burning ship function.");
	menu_data.addAction("mandelbar", setMandelbarFractal, "Choose to make a Mandelbar set.");
	menu_data.addAction("anti-alias", antiAliasFilter, "Set output image from Anti-alias filter on input image 1.");
	menu_data.addAction("set-random-color-gradient", setRandomColorGradient, "Smoothly set the values for a range of slots in the color table, using random colors.");
	menu_data.addAction("fractal-random-center", setRandomCenter, "Randomly set the center of the calculation in the complex plane.");	
}

int imageMenu(std::istream& is, std::ostream& os)
{
	ActionData action_data(is, os);
	action_data.setGrid(new JuliaSet);
	MenuData menu_data;
	std::string choice;
	
	configureMenu(menu_data);
	while(action_data.getDone() == false && action_data.getIS().good())
	{
		choice = getChoice(action_data);
		takeAction(choice, menu_data, action_data);
	}

	return 0;


}

void readUserImage2( ActionData& action_data)
{
	std::string getName;

	getName = getString( action_data, "Input filename? ");

	std::ifstream fin(getName, std::ios::binary);

	action_data.getInputImage2().readStream(fin);

	fin.close();
}

void plusEquals( ActionData& action_data)
{
	action_data.getInputImage1() += action_data.getInputImage2();
}

void minusEquals( ActionData& action_data)
{
	action_data.getInputImage1() -= action_data.getInputImage2();
}

void timesEquals( ActionData& action_data)
{
	double rhs;
	rhs = getDouble(action_data, "Factor? ");
	action_data.getInputImage1() *= rhs;
}

void divideEquals( ActionData& action_data)
{
	double rhs;
	rhs = getDouble(action_data, "Factor? ");
	action_data.getInputImage1() /= rhs;
}

void plus( ActionData& action_data)
{
	action_data.getOutputImage() = action_data.getInputImage1() + action_data.getInputImage2();
}

void minus( ActionData& action_data)
{
	action_data.getOutputImage() = action_data.getInputImage1() - action_data.getInputImage2();
}

void times( ActionData& action_data)
{
	double rhs;
	rhs = getDouble(action_data, "Factor? ");
	action_data.getOutputImage() = (action_data.getInputImage1() * rhs);
}

void divide( ActionData& action_data)
{
	double rhs;
	rhs = getDouble(action_data, "Factor? ");
	action_data.getOutputImage() = (action_data.getInputImage1() / rhs);
}

void grayFromRed(ActionData& action_data)
{
	action_data.getInputImage1().grayFromRed(action_data.getOutputImage());
}

void grayFromGreen(ActionData& action_data)
{
	action_data.getInputImage1().grayFromGreen(action_data.getOutputImage());
}

void grayFromBlue(ActionData& action_data)
{
	action_data.getInputImage1().grayFromBlue(action_data.getOutputImage());
}

void grayFromLinearColorimetric(ActionData& action_data)
{
	action_data.getInputImage1().grayFromLinearColorimetric(action_data.getOutputImage());
}

void drawCircle(ActionData& action_data)
{
	int Row;
	int Column;
	int Radius;
	int Red;
	int Green;
	int Blue;
	int y;
	int x;
	double d;

	Row = getInteger(action_data, "Center Row? ");
	Column = getInteger(action_data, "Center Column? ");
	Radius = getInteger(action_data, "Radius? ");
	Red = getInteger(action_data, "Red? ");
	Green = getInteger(action_data, "Green? ");
	Blue = getInteger(action_data, "Blue? ");
	

	for (y = 0; y < action_data.getInputImage1().getHeight(); y++)
	{
		for (x = 0; x < action_data.getInputImage1().getWidth(); x++)
		{
			d = std::sqrt( ( y - Row )*( y - Row ) + (x - Column)*(x - Column ) );
			if (d <= Radius)
			{
				action_data.getInputImage1().setPixel(y, x, Red, Green, Blue);
			}

		}
	}	
}

void drawBox(ActionData& action_data)
{
	int trow, lcol, brow, rcol, Red, Green, Blue, y, x;

	trow = getInteger(action_data, "Top Row? ");
	lcol = getInteger(action_data, "Left Column? ");
	brow = getInteger(action_data, "Bottom Row? ");
	rcol = getInteger(action_data, "Right Column? ");
	Red = getInteger(action_data, "Red? ");
	Green = getInteger(action_data, "Green? ");
	Blue = getInteger(action_data, "Blue? ");

	for (y = 0; y < action_data.getInputImage1().getHeight(); y++)
	{
		for (x = 0; x < action_data.getInputImage1().getWidth(); x++)
		{
			if (x >= lcol && x <= rcol && y >= trow && y <= brow)
			{
				action_data.getInputImage1().setPixel(y, x, Red, Green, Blue);
			}
		}
	}
}

void copyImage1ToImage2(ActionData& action_data)
{
	action_data.getInputImage2() = action_data.getInputImage1();
}

void timesEqualsPPM(ActionData& action_data)
{
	action_data.getInputImage1() *= action_data.getInputImage2();
}

void orangeFilter(ActionData& action_data)
{
	action_data.getInputImage1().orangeFilter(action_data.getOutputImage());
}

void configureGrid(ActionData& action_data)
{
	int height;
	int width;
	int value;

	height = getInteger(action_data, "Grid Height? ");
	width = getInteger(action_data, "Grid Width? ");
	value = getInteger(action_data, "Grid Max Value? ");

	action_data.getGrid().setGridSize(height, width);
	action_data.getGrid().setMaxNumber(value);
}

void setGrid(ActionData& action_data)
{
	int Row;
	int Column;
	int value;

	Row = getInteger(action_data, "Grid Row? ");
	Column = getInteger(action_data, "Grid Column? ");
	value = getInteger(action_data, "Grid Value? ");

	action_data.getGrid().setNumber(Row, Column, value);

}

void applyGrid(ActionData& action_data)
{
	action_data.getGrid().setPPM(action_data.getOutputImage());
}

void setFractalPlaneSize(ActionData& action_data)
{
	double minX, maxX, minY, maxY;

	minX = getDouble(action_data, "Min X? ");
	maxX = getDouble(action_data, "Max X? ");
	minY = getDouble(action_data, "Min Y? ");
	maxY = getDouble(action_data, "Max Y? ");

	ComplexFractal *ptr = dynamic_cast< ComplexFractal* >(&action_data.getGrid());
	if(ptr != 0) 
	{
		ptr->setPlaneSize(minX, maxX, minY, maxY);
	} 
	else 
	{
	  	action_data.getOS() << "Not a JuliaSet object.  Can't do the work." << std::endl;
	}
}

void calculateFractal(ActionData& action_data)
{
	action_data.getGrid().calculateAllNumbers();
}

void setJuliaParameters(ActionData& action_data)
{
	double a, b;

	a = getDouble(action_data, "Parameter a? ");
	b = getDouble(action_data, "Parameter b? ");

	JuliaSet *ptr = dynamic_cast< JuliaSet* >(&action_data.getGrid());
	if(ptr != 0) 
	{
		ptr->setParameters(a, b);
	} 
	else 
	{
		action_data.getOS() << "Not a JuliaSet object.  Can't do the work." << std::endl;
	}
}

void calculateFractalSingleThread(ActionData& action_data)
{
	action_data.getGrid().NumberGrid::calculateAllNumbers();
}

void applyGridColorTable(ActionData& action_data)
{
	action_data.getGrid().setPPM(action_data.getOutputImage(), action_data.getTable());
}

void setColorTableSize(ActionData& action_data)
{
	int size;
	size = getInteger(action_data, "Size? ");
	action_data.getTable().setNumberOfColors(size);
}

void setColor(ActionData& action_data)
{
	int pos, red, green, blue;
	pos = getInteger(action_data, "Position? ");
	red = getInteger(action_data, "Red? ");
	green = getInteger(action_data, "Green? ");
	blue = getInteger(action_data, "Blue? ");
	action_data.getTable()[pos].setChannel(0, red);
	action_data.getTable()[pos].setChannel(1, green);
	action_data.getTable()[pos].setChannel(2, blue);	
}

void setRandomColor(ActionData& action_data)
{
	int pos;
	pos = getInteger(action_data, "Position? ");
	action_data.getTable().setRandomColor(255, pos);
}

void setColorGradient(ActionData& action_data)
{
	int pos1, pos2, red1, red2, green1, green2, blue1, blue2;

	pos1 = getInteger(action_data, "First position? ");
	red1 = getInteger(action_data, "First red? ");
	green1 = getInteger(action_data, "First green? ");
	blue1 = getInteger(action_data, "First blue? ");
	pos2 = getInteger(action_data, "Second position? ");
	red2 = getInteger(action_data, "Second red? ");
	green2 = getInteger(action_data, "Second green? ");
	blue2 = getInteger(action_data, "Second blue? ");
	Color c1(red1, green1, blue1), c2(red2, green2, blue2);

	action_data.getTable().insertGradient(c1, c2, pos1, pos2);
}

void setJuliaFourFractal(ActionData& action_data)
{
	action_data.setGrid(new JuliaSetFour);
}

void setEscapeRadius( ActionData& action_data )
{
	double radius;
	radius = getDouble(action_data, "Escape Radius? ");

	ComplexFractal *ptr = dynamic_cast< ComplexFractal* >(&action_data.getGrid());
	if(ptr != 0) 
	{
		ptr->setEscapeRadius(radius);
	} 
	else 
	{
	  	action_data.getOS() << "Not a ComplexFractal object.  Can't do the work." << std::endl;
	}
}

void setInvertedColorGradient(ActionData& action_data)
{
	unsigned int pos1, pos2;
	int cRed, cBlue, cGreen;

	pos1 = getInteger(action_data, "First position? ");
	cRed = getInteger(action_data, "First red? ");
	cGreen = getInteger(action_data, "First green? ");
	cBlue = getInteger(action_data, "First blue? ");
	pos2 = getInteger(action_data, "Second position? ");

	Color color1(cRed, cGreen, cBlue);

	action_data.getTable().insertInvertedGradient(color1, pos1, pos2);
}

void setJuliaFractal( ActionData& action_data )
{
	action_data.setGrid(new JuliaSet);
}

void setMandelbrotFractal( ActionData& action_data )
{
	action_data.setGrid(new MandelbrotSet);
}

void toggleQuiet( ActionData& action_data )
{
	action_data.setQuiet();
}

void setBurningShipFractal(ActionData& action_data)
{
	action_data.setGrid(new BurningShip);
}

void setMandelbarFractal(ActionData& action_data)
{
	action_data.setGrid(new MandelbarSet);
}

void antiAliasFilter(ActionData& action_data)
{
	int reduction;

	reduction = getInteger(action_data, "Reduction count? ");

	action_data.getInputImage1().antiAlias(reduction, action_data.getOutputImage());
}

void setRandomColorGradient(ActionData& action_data)
{
	int minD, maxD, pos1, pos2;

	pos1 = getInteger(action_data, "First position? ");
	pos2 = getInteger(action_data, "Second position? ");
	minD = getInteger(action_data, "Minimum difference? ");
	maxD = getInteger(action_data, "Maximum difference? ");

	action_data.getTable().insertRandomGradient(minD, maxD, 255, pos1, pos2);
}

void setRandomCenter(ActionData& action_data)
{
	double xsize, ysize;

	xsize = getDouble(action_data, "X Size? ");
	ysize = getDouble(action_data, "Y Size? ");

	ComplexFractal *ptr = dynamic_cast< ComplexFractal* >(&action_data.getGrid());
	if(ptr != 0) 
	{
		ptr->setRandomCenter(xsize, ysize);
	} 
	else 
	{
	  	action_data.getOS() << "Not a ComplexFractal object.  Can't do the work." << std::endl;
	}
}