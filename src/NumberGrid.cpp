#include "NumberGrid.h"
#include "PPM.h"
#include "ColorTable.h"

NumberGrid::NumberGrid( )
: mHeight(300), mWidth(400), mMaxValue(255), mNumbers(mHeight * mWidth, 0)
{

}

NumberGrid::NumberGrid( const int& height, const int& width )
: mHeight(height), mWidth(width), mMaxValue(255), mNumbers(mHeight * mWidth, 0)
{

}

int NumberGrid::getHeight( ) const
{
	return mHeight;
}

int NumberGrid::getWidth( ) const
{
	return mWidth;
}

int NumberGrid::getMaxNumber( ) const
{
	return mMaxValue;
}

void NumberGrid::setGridSize( const int& height, const int& width )
{
	if (height >= 2 && width >= 2)
	{
		mHeight = height;
		mWidth = width;

		mNumbers.resize(height * width);

	}
}

void NumberGrid::setMaxNumber( const int& number )
{
	if (number >= 0)
	{
		mMaxValue = number;
	}
}

const std::vector< int >& NumberGrid::getNumbers( ) const
{
	return mNumbers;
}

int NumberGrid::index( const int& row, const int& column ) const
{
	return (row * getWidth()) + column;
}

bool NumberGrid::indexValid( const int& row, const int& column ) const
{
	if (row >= getHeight() || column >= getWidth())
	{
		return false;
	}
	else if (row < 0 || column < 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool NumberGrid::numberValid( const int& number ) const
{
	if (number < 0 || number > getMaxNumber())
	{
		return false;
	}
	else
	{
		return true;
	}
}

int NumberGrid::getNumber( const int& row, const int& column ) const
{
	if (indexValid(row, column))
	{
		return mNumbers[row * getWidth() + column];
	}
	else
	{
		return -1;
	}
}

void NumberGrid::setNumber( const int& row, const int& column, const int& number )
{
	if (indexValid(row, column) && numberValid(number))
	{
		mNumbers[row * getWidth() + column] = number;
	}
}

void NumberGrid::setPPM( PPM& ppm ) const
{
	ppm.setWidth(getWidth());
	ppm.setHeight(getHeight());
	ppm.setMaxColorValue(63);

	int Row;
	int Column;

	for (Row = 0; Row < ppm.getHeight(); Row++)
	{
		for (Column = 0; Column < ppm.getWidth(); Column++)
		{
			if (getNumber(Row, Column) == 0)
			{
				ppm.setPixel(Row, Column, 0, 0, 0);
			}
			else if (getNumber(Row, Column) == getMaxNumber())
			{
				ppm.setPixel(Row, Column, 63, 31, 31);
			}
			else if (getNumber(Row, Column) % 8 == 0)
			{
				ppm.setPixel(Row, Column, 63, 63, 63);
			}
			else if (getNumber(Row, Column) % 8 == 1)
			{
				ppm.setPixel(Row, Column, 63, 31, 31);	
			}
			else if (getNumber(Row, Column) % 8 == 2)
			{
				ppm.setPixel(Row, Column, 63, 63, 31);
			}
			else if (getNumber(Row, Column) % 8 == 3)
			{
				ppm.setPixel(Row, Column, 31, 63, 31);
			}
			else if (getNumber(Row, Column) % 8 == 4)
			{
				ppm.setPixel(Row, Column, 0, 0, 0);
			}
			else if (getNumber(Row, Column) % 8 == 5)
			{
				ppm.setPixel(Row, Column, 31, 63, 63);
			}
			else if (getNumber(Row, Column) % 8 == 6)
			{
				ppm.setPixel(Row, Column, 31, 31, 63);
			}
			else if (getNumber(Row, Column) % 8 == 7)
			{
				ppm.setPixel(Row, Column, 63, 31, 63);
			}
			
		}
	}
}

void NumberGrid::setPPM( PPM& ppm, const ColorTable& colors ) const
{
	int Column, Row, i;

	if (colors.getNumberOfColors() >= 3)
	{
		ppm.setWidth(getWidth());
		ppm.setHeight(getHeight());
		ppm.setMaxColorValue(colors.getMaxChannelValue());
		for (Row = 0; Row < ppm.getHeight(); Row++)
		{
			for (Column = 0; Column < ppm.getWidth(); Column++)
			{
				if (getNumber(Row, Column) == 0)
				{
					ppm.setPixel(Row, Column, colors[0].getRed(), colors[0].getGreen(), colors[0].getBlue());
				}
				else if (getNumber(Row, Column) == getMaxNumber())
				{
					ppm.setPixel(Row, Column, colors[colors.getNumberOfColors()-1].getRed(), colors[colors.getNumberOfColors()-1].getGreen(), colors[colors.getNumberOfColors()-1].getBlue());
				}
				else
				{
					i = getNumber(Row, Column) % colors.getNumberOfColors();
					ppm.setPixel(Row, Column, colors[i].getRed(), colors[i].getGreen(), colors[i].getBlue());
				}
			}
		}
	}
}

NumberGrid::~NumberGrid()
{

}

void NumberGrid::calculateAllNumbers()
{
	int Row, Column, number;

	for (Row = 0; Row < getHeight(); Row++)
	{
		for (Column = 0; Column < getWidth(); Column++)
		{
			number = calculateNumber(Row, Column);
			setNumber(Row, Column, number);
		}
	}
}
