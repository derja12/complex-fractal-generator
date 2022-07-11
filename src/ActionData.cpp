#include <iostream>
#include "PPM.h"
#include "ActionData.h"
#include "ColorTable.h"


ActionData::ActionData(std::istream& is, std::ostream& os) 
: mIs(is), mOs(os), mDone(false), mNumberGrid(0), mColorTable(16), mQuiet(false)
{
	Color color1(0,255,0);
	Color color2(255,0,255);
	
	mColorTable.insertGradient(color1, color2, 0, 15);
}

std::istream& ActionData::getIS()
{
	return mIs;
}

std::ostream& ActionData::getOS()
{
	return mOs;
}

PPM& ActionData::getInputImage1()
{
	return mInputImage1;
}

PPM& ActionData::getOutputImage()
{
	return mOutputImage;
}

bool ActionData::getDone() const
{
	return mDone;
}

void ActionData::setDone()
{
	mDone = true;
}

PPM& ActionData::getInputImage2()
{
	return mInputImage2;
}

ActionData::~ActionData()
{
	if (mNumberGrid != 0)
	{
		delete mNumberGrid;
	}
}

NumberGrid& ActionData::getGrid()
{
	return *mNumberGrid;
}

void ActionData::setGrid(NumberGrid *grid)
{
	if (mNumberGrid != 0)
	{
		delete mNumberGrid;
	}
	mNumberGrid = grid;
}

ColorTable& ActionData::getTable()
{
	return mColorTable;
}

bool ActionData::getQuiet()
{
	return mQuiet;
}

void ActionData::setQuiet()
{
	if (getQuiet())
	{
		mQuiet = false;
	}
	else
	{
		mQuiet = true;
	}
}