#include "ComplexFractal.h"
#include <cmath>

ComplexFractal::ComplexFractal( )
: ThreadedGrid(200, 300), mMinX(-1.5), mMinY(-1), mMaxX(1.5), mMaxY(1), mDeltaX(.01), mDeltaY(.01), mEscapeRad(2)
{
	setMaxNumber(255);
}

ComplexFractal::ComplexFractal( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y )
: ThreadedGrid(height, width), mMinX(min_x), mMinY(min_y), mMaxX(max_x), mMaxY(max_y), mDeltaX(.01), mDeltaY(.01), mEscapeRad(2)
{
	setMaxNumber(255);
}

ComplexFractal::~ComplexFractal( )
{

}

double ComplexFractal::getMinX( ) const
{
	return mMinX;
}

double ComplexFractal::getMaxX( ) const
{
	return mMaxX;
}

double ComplexFractal::getMinY( ) const
{
	return mMinY;
}

double ComplexFractal::getMaxY( ) const
{
	return mMaxY;
}

void ComplexFractal::setGridSize( const int& height, const int& width)
{
	if (height >= 2 && width >= 2)
	{
		NumberGrid::setGridSize(height, width);
		setDeltas(calculateDeltaX(), calculateDeltaY());
	}
}

void ComplexFractal::setPlaneSize( const double& min_x, const double& max_x, const double& min_y, const double& max_y )
{
	if (min_x != max_x && min_y != max_y && min_x >= -2 && min_x <= 2 && min_y >= -2 && min_y <= 2 && max_x >= -2 && max_x <= 2 && max_y >= -2 && max_y <= 2)
	{
		
		if (min_x > max_x)
		{
			mMinX = max_x;
			mMaxX = min_x;
		}
		else 
		{
			mMinX = min_x;
			mMaxX = max_x;
		}

		if (min_y > max_y)
		{
			mMinY = max_y;
			mMaxY = min_y;
		}
		else 
		{
			mMinY = min_y;
			mMaxY = max_y;
		}
		setDeltas(calculateDeltaX(), calculateDeltaY());
	}
}

double ComplexFractal::getDeltaY( ) const
{
	return mDeltaY;
}

double ComplexFractal::getDeltaX( ) const
{
	return mDeltaX;
}

void ComplexFractal::setDeltas( const double& delta_x, const double& delta_y)
{
	if (delta_x > 0 && delta_y > 0)
	{
		mDeltaX = delta_x;
		mDeltaY = delta_y;
	}
}

double ComplexFractal::calculateDeltaY( ) const
{
	return ( mMaxY - mMinY ) / ( getHeight() - 1 );
}

double ComplexFractal::calculateDeltaX( ) const
{
	return ( mMaxX - mMinX ) / ( getWidth() - 1 );
}

double ComplexFractal::calculatePlaneXFromPixelColumn( const int& column) const
{
	if (column < 0 || column >= getWidth())
	{
		return 0;
	}
	return (mMinX + column * getDeltaX());
}

double ComplexFractal::calculatePlaneYFromPixelRow( const int& row) const
{
	if (row < 0 || row >= getHeight())
	{
		return 0;
	}
	return (mMaxY - row * getDeltaY());
}

void ComplexFractal::calculatePlaneCoordinatesFromPixelCoordinates( const int& row, const int& column, double& x, double& y) const
{
	if (calculatePlaneYFromPixelRow(row) == 0 || calculatePlaneXFromPixelColumn(column) == 0)
	{
		x = 0;
		y = 0;
	}
	else
	{
		x = calculatePlaneXFromPixelColumn(column);	
		y = calculatePlaneYFromPixelRow(row); 
	}
}
 

double ComplexFractal::getEscapeRadius() const
{
	return mEscapeRad;
}

void ComplexFractal::setEscapeRadius(const double& radius)
{
	if (radius > 0)
	{
		mEscapeRad = radius;
	}
}

void ComplexFractal::setPlaneFromCenter( const double& xc, const double& yc, const double& xsize, const double& ysize )
{
	double minx, miny, maxx, maxy;

	if (xsize > 0 && ysize > 0)
		{
			minx = xc - xsize / 2;
			maxx = xc + xsize / 2;
			miny = yc - ysize / 2;
			maxy = yc + ysize / 2;
		if (maxx > 2)
		{
			maxx = 2;
		}
		if (maxy > 2)
		{
			maxy = 2;
		}
		if (minx < -2)
		{
			minx = -2;
		}
		if (miny < -2)
		{
			miny = -2;
		}
		setPlaneSize(minx, maxx, miny, maxy);
	}
}

void ComplexFractal::findInterestingPoint( double& xc, double& yc ) const
{
	int big_value = 1000000000, interest = 0;
	double x, y;
	while (interest < (4 * NumberGrid::getMaxNumber( ) / 6) || (5 * NumberGrid::getMaxNumber( ) / 6) > interest)
	{
		x = ( ( std::rand( ) % big_value ) - ( big_value / 2.0 ) ) / ( big_value / 4.0 );
		y = ( ( std::rand( ) % big_value ) - ( big_value / 2.0 ) ) / ( big_value / 4.0 );
		interest = calculatePlaneEscapeCount(x, y);
	}
	xc = x;
	yc = y;

}

void ComplexFractal::setRandomCenter( const double& xsize, const double& ysize)
{
	
	double x, y;

	findInterestingPoint(x, y);

	setPlaneFromCenter(x, y, xsize, ysize);

}
