#include <iostream>
#include "ComplexFractal.h"
#ifndef _MANDELBROTSET_H_
#define _MANDELBROTSET_H_

class MandelbrotSet : public ComplexFractal {
public:
	MandelbrotSet( );
	MandelbrotSet( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y );
	virtual ~MandelbrotSet( );
	virtual void calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double &y1 ) const;
	virtual int calculatePlaneEscapeCount( const double& a, const double& b ) const;
	virtual int calculateNumber( const int& row, const int& column ) const;

};

class BurningShip : public MandelbrotSet {
public:
	BurningShip( );
	virtual ~BurningShip( );
	virtual void calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double &y1 ) const;
};

class MandelbarSet : public MandelbrotSet {
public:
	MandelbarSet( );
	virtual ~MandelbarSet( );
	virtual void calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double &y1 ) const;
};

#endif