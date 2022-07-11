#include <iostream>
#include <cmath>
#include "ComplexFractal.h"
#include "JuliaSet.h"
#include "NumberGrid.h"

JuliaSet::JuliaSet()
:ComplexFractal(), mA( -0.650492), mB( -0.478235)
{

}

JuliaSet::JuliaSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y, const double& a, const double& b)
:ComplexFractal(height, width, min_x, max_x, min_y, max_y), mA(a), mB(b)
{

}

JuliaSet::~JuliaSet( )
{

}

double JuliaSet::getA( ) const
{
	return mA;
}

double JuliaSet::getB( ) const
{
	return mB;
}

void JuliaSet::setParameters( const double& a, const double& b)
{
	if (a <= 2.0 && a >= -2.0 && b <= 2.0 && b >= -2.0)
	{
		mA = a;
		mB = b;
	}
}

void JuliaSet::calculateNextPoint( const double x0, const double y0, double& x1, double& y1 ) const
{
	x1 = (x0 * x0) - (y0 * y0) + mA;
	y1 = (2 * x0 * y0) + mB;
}

int JuliaSet::calculatePlaneEscapeCount( const double& x0, const double& y0) const
{
	int eCount = 0;
	double newX, newY, d, x = x0, y = y0;
	d = std::sqrt( (x0 * x0) + (y0 * y0));
	
	while (eCount >= 0 && d <= getEscapeRadius() && eCount < NumberGrid::getMaxNumber())
	{
		calculateNextPoint(x, y, newX, newY);
		eCount += 1;
		x = newX;
		y = newY;

		d = std::sqrt( (x * x) + (y * y) );
	}

	return eCount;
}

int JuliaSet::calculateNumber( const int& row, const int& column ) const
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

JuliaSetFour::JuliaSetFour( )
: JuliaSet() {

}

JuliaSetFour::~JuliaSetFour( )
{

}

void JuliaSetFour::calculateNextPoint( const double x0, const double y0, double& x1, double &y1 ) const
{
	x1 = (x0 * x0 * x0 * x0) - (6 * x0 * x0 * y0 * y0) + (y0 * y0 * y0 * y0) + getA();
	y1 = (4 * x0 * x0 * x0 * y0) - (4 * x0 * y0 * y0 * y0) + getB();
}
