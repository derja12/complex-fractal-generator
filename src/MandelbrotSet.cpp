#include "MandelbrotSet.h"
#include <cmath>


MandelbrotSet::MandelbrotSet( )
: ComplexFractal()
{

}


MandelbrotSet::MandelbrotSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y )
: ComplexFractal(height, width, min_x, max_x, min_y, max_y)
{

}

MandelbrotSet::~MandelbrotSet( )
{

}

void MandelbrotSet::calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double &y1 ) const
{

	x1 = (x0 * x0) - (y0 * y0) + a;
	y1 = (2 * x0 * y0) + b;

}

int MandelbrotSet::calculatePlaneEscapeCount( const double& a, const double& b ) const
{
	int eCount = 0;
	double newX, newY, d, x = a, y = b;
	d = std::sqrt( (x * x) + (y * y));

	calculateNextPoint(0, 0, a, b, newX, newY);
	x = newX;
	y = newY;
	
	while (eCount >= 0 && d <= getEscapeRadius() && eCount < NumberGrid::getMaxNumber())
	{
		calculateNextPoint(x, y, a, b, newX, newY);
		eCount += 1;
		x = newX;
		y = newY;

		d = std::sqrt( (x * x) + (y * y) );
	}

	return eCount;
}

int MandelbrotSet::calculateNumber( const int& row, const int& column ) const
{

	double x, y;

	x = calculatePlaneXFromPixelColumn(column);
	y = calculatePlaneYFromPixelRow(row);

	if (row < 0 || row >= getHeight() || column < 0 || column >= getWidth())
	{
		return -1;
	}

	
	return calculatePlaneEscapeCount(x, y);

}

BurningShip::BurningShip( )
: MandelbrotSet( )
{

}

BurningShip::~BurningShip( )
{

}

void BurningShip::calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double &y1 ) const
{
	x1 = x0*x0 - y0*y0 + a;
	y1 = (-2*std::abs(x0*y0)) + b;
}

MandelbarSet::MandelbarSet( )
: MandelbrotSet( )
{

}

MandelbarSet::~MandelbarSet( )
{

}

void MandelbarSet::calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double &y1 ) const
{
	x1 = x0*x0 - y0*y0 + a;
	y1 = -2*x0*y0 + b;
}
