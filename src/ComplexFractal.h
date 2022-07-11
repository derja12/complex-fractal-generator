#include <iostream>
#include "ThreadedGrid.h"
#ifndef _COMPLEXFRACTAL_H_
#define _COMPLEXFRACTAL_H_

class ComplexFractal : public ThreadedGrid {
public:
	ComplexFractal( );
	ComplexFractal( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y );
	virtual ~ComplexFractal( );
	double getMinX( ) const;
	double getMaxX( ) const;
	double getMinY( ) const;
	double getMaxY( ) const;
	virtual void setGridSize( const int& height, const int& width);
	void setPlaneSize( const double& min_x, const double& max_x, const double& min_y, const double& max_y );
	double getDeltaY( ) const;
	double getDeltaX( ) const;
	void setDeltas( const double& delta_x, const double& delta_y);
	double calculateDeltaY( ) const;
	double calculateDeltaX( ) const;
	double calculatePlaneXFromPixelColumn( const int& column) const;
	double calculatePlaneYFromPixelRow( const int& row) const;
	void calculatePlaneCoordinatesFromPixelCoordinates( const int& row, const int& column, double& x, double& y) const; 
	double getEscapeRadius() const;
	void setEscapeRadius(const double& radius);
	
	virtual int calculatePlaneEscapeCount( const double& x0, const double& y0 ) const = 0;
	void setPlaneFromCenter( const double& xc, const double& yc, const double& xsize, const double& ysize );
	virtual void findInterestingPoint( double& xc, double& yc ) const;
	void setRandomCenter( const double& xsize, const double& ysize);

protected:
	double mMinX;
	double mMinY;
	double mMaxX;
	double mMaxY;
	double mDeltaX;
	double mDeltaY;
	double mEscapeRad;

};

#endif