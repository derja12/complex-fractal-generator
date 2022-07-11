#include <iostream>
#include <string>
#include "PPM.h"
#include "Image.h"

PPM::PPM( )
: Image(), mMax(1)
{

}

PPM::PPM( const int& height, const int& width )
: Image(height,width), mMax(1)
{

}

int PPM::getMaxColorValue( ) const
{
	return mMax;
}

bool PPM::valueValid( const int& value ) const 
{
	if ( value >= 0 && value <= mMax)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void PPM::setMaxColorValue( const int& max_color_value )
{
	if ( max_color_value > 0 && max_color_value < 256)
	{
		mMax = max_color_value;
	}
}

void PPM::setChannel( const int& row, const int& column, const int& channel, const int& value )
{
	if (valueValid(value))
	{
		Image::setChannel(row, column, channel, value);
	}
}

void PPM::setPixel( const int& row, const int& column, const int& red, const int& green, const int& blue )
{
	setChannel(row,column,0,red);
	setChannel(row,column,1,green);
	setChannel(row,column,2,blue);
}

void PPM::writeStream(std::ostream& os) const 
{
	os << "P6" << " " << Image::getWidth() << " " << Image::getHeight() << " " << getMaxColorValue() << "\n";

	unsigned char c;
	int Row;
	int Column;

	for (Row = 0; Row < Image::getHeight(); Row++)
	{
		for (Column = 0; Column < Image::getWidth(); Column++)
		{
			c = getChannel(Row, Column, 0);
			os.write((char *) &c, sizeof(c));
			c = getChannel(Row, Column, 1);
			os.write((char *) &c, sizeof(c));
			c = getChannel(Row, Column, 2);
			os.write((char *) &c, sizeof(c));
		}
	}

}

void PPM::magenta(const int& row, const int& column) 
{
	setChannel(row,column,0,getMaxColorValue());
	setChannel(row,column,1,0);
	setChannel(row,column,2,getMaxColorValue());
}

void PPM::readStream(std::istream& is)
{
	std::string magic;

	int width;
	int height;
	int mcv;
	int Row;
	int Column;

	unsigned char v;

	is >> magic >> width >> height >> mcv;

	setWidth(width);
	setHeight(height);
	setMaxColorValue(mcv);

	
	is.read((char*)&v, sizeof(v));

	for (Row = 0; Row < height; Row++)
	{
		for (Column = 0; Column < width; Column++)
		{
			is.read((char*)&v, sizeof(v));
			setChannel(Row, Column, 0, v);
			is.read((char*)&v, sizeof(v));
			setChannel(Row, Column, 1, v);
			is.read((char*)&v, sizeof(v));
			setChannel(Row, Column, 2, v);

		}
	}
}

// OPERATORS

bool PPM::operator==( const PPM& rhs) const 
{
	return this->mVector.size() == rhs.mVector.size();
}

bool PPM::operator!=( const PPM& rhs) const 
{
	return this->mVector.size() != rhs.mVector.size();
}

bool PPM::operator<( const PPM& rhs) const 
{
	return this->mVector.size() < rhs.mVector.size();
}

bool PPM::operator<=( const PPM& rhs) const 
{
	return this->mVector.size() <= rhs.mVector.size();
}

bool PPM::operator>( const PPM& rhs) const 
{
	return this->mVector.size() > rhs.mVector.size();
}

bool PPM::operator>=( const PPM& rhs) const 
{
	return this->mVector.size() >= rhs.mVector.size();
}

PPM& PPM::operator+=( const PPM& rhs) 
{
	int Row;
	int Column;
	int newChannel;

	for (Row = 0; Row < this->getHeight(); Row++)
	{
		for (Column = 0; Column < this->getWidth(); Column++)
		{
			newChannel = this->getChannel(Row, Column, 0) + rhs.getChannel(Row,Column, 0);
			if (newChannel > this->getMaxColorValue())
			{
				newChannel = this->getMaxColorValue();
			}
			this->setChannel(Row, Column, 0, newChannel);
			newChannel = this->getChannel(Row, Column, 1) + rhs.getChannel(Row,Column, 1);
			if (newChannel > this->getMaxColorValue())
			{
				newChannel = this->getMaxColorValue();
			}
			this->setChannel(Row, Column, 1, newChannel);
			newChannel = this->getChannel(Row, Column, 2) + rhs.getChannel(Row,Column, 2);
			if (newChannel > this->getMaxColorValue())
			{
				newChannel = this->getMaxColorValue();
			}
			this->setChannel(Row, Column, 2, newChannel);
		}
	}
	return *this;
}

PPM& PPM::operator-=( const PPM& rhs) 
{
	int Row;
	int Column;
	int newChannel;

	for (Row = 0; Row < this->getHeight(); Row++)
	{
		for (Column = 0; Column < this->getWidth(); Column++)
		{
			newChannel = this->getChannel(Row, Column, 0) - rhs.getChannel(Row,Column, 0);
			if (newChannel < 0)
			{
				newChannel = 0;
			}
			this->setChannel(Row, Column, 0, newChannel);
			newChannel = this->getChannel(Row, Column, 1) - rhs.getChannel(Row,Column, 1);
			if (newChannel < 0)
			{
				newChannel = 0;
			}
			this->setChannel(Row, Column, 1, newChannel);
			newChannel = this->getChannel(Row, Column, 2) - rhs.getChannel(Row,Column, 2);
			if (newChannel < 0)
			{
				newChannel = 0;
			}
			this->setChannel(Row, Column, 2, newChannel);
		}
	}
	return *this;
}

PPM& PPM::operator*=( const double& rhs) 
{
	int Row;
	int Column;
	int newChannel;

	for (Row = 0; Row < this->getHeight(); Row++)
	{
		for (Column = 0; Column < this->getWidth(); Column++)
		{
			newChannel = this->getChannel(Row, Column, 0) * rhs;
			if (newChannel > this->getMaxColorValue())
			{
				newChannel = this->getMaxColorValue();
			}
			if (newChannel < 0)
			{
				newChannel = 0;
			}
			this->setChannel(Row, Column, 0, newChannel);
			newChannel = this->getChannel(Row, Column, 1) * rhs;
			if (newChannel > this->getMaxColorValue())
			{
				newChannel = this->getMaxColorValue();
			}
			if (newChannel < 0)
			{
				newChannel = 0;
			}
			this->setChannel(Row, Column, 1, newChannel);
			newChannel = this->getChannel(Row, Column, 2) * rhs;
			if (newChannel > this->getMaxColorValue())
			{
				newChannel = this->getMaxColorValue();
			}
			if (newChannel < 0)
			{
				newChannel = 0;
			}
			this->setChannel(Row, Column, 2, newChannel);
		}
	}
	return *this;
}

PPM& PPM::operator/=( const double& rhs) 
{
	int Row;
	int Column;
	int newChannel;

	for (Row = 0; Row < this->getHeight(); Row++)
	{
		for (Column = 0; Column < this->getWidth(); Column++)
		{
			newChannel = this->getChannel(Row, Column, 0) / rhs;
			if (newChannel > this->getMaxColorValue())
			{
				newChannel = this->getMaxColorValue();
			}
			if (newChannel < 0)
			{
				newChannel = 0;
			}
			this->setChannel(Row, Column, 0, newChannel);
			newChannel = this->getChannel(Row, Column, 1) / rhs;
			if (newChannel > this->getMaxColorValue())
			{
				newChannel = this->getMaxColorValue();
			}
			if (newChannel < 0)
			{
				newChannel = 0;
			}
			this->setChannel(Row, Column, 1, newChannel);
			newChannel = this->getChannel(Row, Column, 2) / rhs;
			if (newChannel > this->getMaxColorValue())
			{
				newChannel = this->getMaxColorValue();
			}
			if (newChannel < 0)
			{
				newChannel = 0;
			}
			this->setChannel(Row, Column, 2, newChannel);
		}
	}
	return *this;
}

PPM PPM::operator+( const PPM& rhs) const 
{
	PPM newppm(this->getHeight(), this->getWidth());
	int Row;
	int Column;
	int newChannel;

	newppm.setMaxColorValue(this->getMaxColorValue());

	for (Row = 0; Row < this->getHeight(); Row++)
	{
		for (Column = 0; Column < this->getWidth(); Column++)
		{
			newChannel = this->getChannel(Row, Column, 0) + rhs.getChannel(Row,Column, 0);
			if (newChannel > this->getMaxColorValue())
			{
				newChannel = this->getMaxColorValue();
			}
			newppm.setChannel(Row, Column, 0, newChannel);
			newChannel = this->getChannel(Row, Column, 1) + rhs.getChannel(Row,Column, 1);
			if (newChannel > this->getMaxColorValue())
			{
				newChannel = this->getMaxColorValue();
			}
			newppm.setChannel(Row, Column, 1, newChannel);
			newChannel = this->getChannel(Row, Column, 2) + rhs.getChannel(Row,Column, 2);
			if (newChannel > this->getMaxColorValue())
			{
				newChannel = this->getMaxColorValue();
			}
			newppm.setChannel(Row, Column, 2, newChannel);
		}
	}
	return newppm;
}

PPM PPM::operator-( const PPM& rhs) const 
{
	PPM newppm(this->getHeight(), this->getWidth());
	int Row;
	int Column;
	int newChannel;

	newppm.setMaxColorValue(this->getMaxColorValue());

	for (Row = 0; Row < this->getHeight(); Row++)
	{
		for (Column = 0; Column < this->getWidth(); Column++)
		{
			newChannel = this->getChannel(Row, Column, 0) - rhs.getChannel(Row,Column, 0);
			if (newChannel < 0)
			{
				newChannel = 0;
			}
			newppm.setChannel(Row, Column, 0, newChannel);
			newChannel = this->getChannel(Row, Column, 1) - rhs.getChannel(Row,Column, 1);
			if (newChannel < 0)
			{
				newChannel = 0;
			}
			newppm.setChannel(Row, Column, 1, newChannel);
			newChannel = this->getChannel(Row, Column, 2) - rhs.getChannel(Row,Column, 2);
			if (newChannel < 0)
			{
				newChannel = 0;
			}
			newppm.setChannel(Row, Column, 2, newChannel);
		}
	}
	return newppm;
}

PPM PPM::operator*( const double& rhs) const 
{
	PPM newppm(this->getHeight(), this->getWidth());
	int Row;
	int Column;
	int newChannel;

	newppm.setMaxColorValue(this->getMaxColorValue());

	for (Row = 0; Row < this->getHeight(); Row++)
	{
		for (Column = 0; Column < this->getWidth(); Column++)
		{
			newChannel = this->getChannel(Row, Column, 0) * rhs;
			if (newChannel > this->getMaxColorValue())
			{
				newChannel = this->getMaxColorValue();
			}
			if (newChannel < 0)
			{
				newChannel = 0;
			}
			newppm.setChannel(Row, Column, 0, newChannel);
			newChannel = this->getChannel(Row, Column, 1) * rhs;
			if (newChannel > this->getMaxColorValue())
			{
				newChannel = this->getMaxColorValue();
			}
			if (newChannel < 0)
			{
				newChannel = 0;
			}
			newppm.setChannel(Row, Column, 1, newChannel);
			newChannel = this->getChannel(Row, Column, 2) * rhs;
			if (newChannel > this->getMaxColorValue())
			{
				newChannel = this->getMaxColorValue();
			}
			if (newChannel < 0)
			{
				newChannel = 0;
			}
			newppm.setChannel(Row, Column, 2, newChannel);
		}
	}
	return newppm;
}

PPM PPM::operator/( const double& rhs) const 
{
	PPM newppm(this->getHeight(), this->getWidth());
	int Row;
	int Column;
	int newChannel;

	newppm.setMaxColorValue(this->getMaxColorValue());

	for (Row = 0; Row < this->getHeight(); Row++)
	{
		for (Column = 0; Column < this->getWidth(); Column++)
		{
			newChannel = this->getChannel(Row, Column, 0) / rhs;
			if (newChannel > this->getMaxColorValue())
			{
				newChannel = this->getMaxColorValue();
			}
			if (newChannel < 0)
			{
				newChannel = 0;
			}
			newppm.setChannel(Row, Column, 0, newChannel);
			newChannel = this->getChannel(Row, Column, 1) / rhs;
			if (newChannel > this->getMaxColorValue())
			{
				newChannel = this->getMaxColorValue();
			}
			if (newChannel < 0)
			{
				newChannel = 0;
			}
			newppm.setChannel(Row, Column, 1, newChannel);
			newChannel = this->getChannel(Row, Column, 2) / rhs;
			if (newChannel > this->getMaxColorValue())
			{
				newChannel = this->getMaxColorValue();
			}
			if (newChannel < 0)
			{
				newChannel = 0;
			}
			newppm.setChannel(Row, Column, 2, newChannel);
		}
	}
	return newppm;
}

void PPM::grayFromChannel( PPM& dst, const int& src_channel ) const
{
	int Row;
	int Column;
	int value;

	dst.setHeight(this->getHeight());
	dst.setWidth(this->getWidth());
	dst.setMaxColorValue(this->getMaxColorValue());

	for (Row = 0; Row < dst.getHeight(); Row++)
	{
		for (Column = 0; Column < dst.getWidth(); Column++)
		{
			value = this->getChannel(Row, Column, src_channel);
			dst.setChannel(Row, Column, 0, value);
			dst.setChannel(Row, Column, 1, value);
			dst.setChannel(Row, Column, 2, value);
		}
	}	
}

void PPM::grayFromRed( PPM& dst ) const
{
	this->grayFromChannel(dst, 0);
}

void PPM::grayFromGreen( PPM& dst ) const
{
	this->grayFromChannel(dst, 1);
}

void PPM::grayFromBlue( PPM& dst ) const
{
	this->grayFromChannel(dst, 2);
}

double PPM::linearColorimetricPixelValue( const int& row, const int& column ) const
{
	int red;
	int green;
	int blue;
	red = this->getChannel(row, column, 0);
	green = this->getChannel(row, column, 1);
	blue = this->getChannel(row, column, 2);

	return 0.2126*red + 0.7152*green + 0.0722*blue;
}

void PPM::grayFromLinearColorimetric( PPM& dst ) const
{
	int Row;
	int Column;
	int value;

	dst.setHeight(this->getHeight());
	dst.setWidth(this->getWidth());
	dst.setMaxColorValue(this->getMaxColorValue());

	for (Row = 0; Row < dst.getHeight(); Row++)
	{
		for (Column = 0; Column < dst.getWidth(); Column++)
		{
			value = this->linearColorimetricPixelValue(Row, Column);
			dst.setChannel(Row, Column, 0, value);
			dst.setChannel(Row, Column, 1, value);
			dst.setChannel(Row, Column, 2, value);
		}
	}	
}

PPM& PPM::operator*=( const PPM& rhs )
{
	int Row;
	int Column;
	int newChannel;


	for (Row = 0; Row < this->getHeight(); Row++)
	{
		for (Column = 0; Column < this->getWidth(); Column++)
		{
			newChannel = this->getChannel(Row, Column, 0) * rhs.getChannel(Row, Column, 0);
			newChannel = newChannel / rhs.getMaxColorValue();
			this->setChannel(Row, Column, 0, newChannel);
			newChannel = this->getChannel(Row, Column, 1) * rhs.getChannel(Row, Column, 1);
			newChannel = newChannel / rhs.getMaxColorValue();
			this->setChannel(Row, Column, 1, newChannel);
			newChannel = this->getChannel(Row, Column, 2) * rhs.getChannel(Row, Column, 2);
			newChannel = newChannel / rhs.getMaxColorValue();
			this->setChannel(Row, Column, 2, newChannel);
		}
	}
	return *this;
}

void PPM::orangeFilter(PPM& dst) const 
{
	int Row;
	int Column;
	int newRed;
	int newGreen;
	int newBlue;

	dst.setHeight(this->getHeight());
	dst.setWidth(this->getWidth());
	dst.setMaxColorValue(this->getMaxColorValue());

	for (Row = 0; Row < dst.getHeight(); Row++)
	{
		for (Column = 0; Column < dst.getWidth(); Column++)
		{
			newRed = 2*(2*this->getChannel(Row, Column, 0) + this->getChannel(Row, Column, 1))/3;
			if (newRed > dst.getMaxColorValue())
			{
				newRed = dst.getMaxColorValue();
			}
			newGreen = 2*(2*this->getChannel(Row, Column, 0) + this->getChannel(Row, Column, 1))/6;
			if (newGreen > dst.getMaxColorValue())
			{
				newGreen = dst.getMaxColorValue();
			}
			newBlue = this->getChannel(Row,Column, 2)/2;
			if (newBlue > dst.getMaxColorValue())
			{
				newBlue = dst.getMaxColorValue();
			}
			dst.setChannel(Row, Column, 0, newRed);
			dst.setChannel(Row, Column, 1, newGreen);
			dst.setChannel(Row, Column, 2, newBlue);
		}
	}	
}

void PPM::antiAlias(const int& n, PPM& dst) const
{
	dst.setWidth(getWidth()/n);
	dst.setHeight(getHeight()/n);
	dst.setMaxColorValue(getMaxColorValue());
	
	int Row, Column, Srow, Scolumn, tRed = 0, tGreen = 0, tBlue = 0;
	for (Row = 0; Row < getHeight(); Row += n)
	{
		for (Column = 0; Column < getWidth(); Column += n)
		{
			for (Srow = 0; Srow < n; Srow++)
			{
				for (Scolumn = 0; Scolumn < n; Scolumn++)
				{
					tRed += getChannel(Row+Srow, Column+Scolumn, 0); 	//Get's the RED
					tGreen += getChannel(Row+Srow, Column+Scolumn, 1); 	//Get's the GREEN
					tBlue += getChannel(Row+Srow, Column+Scolumn, 2); 	//Get's the BLUE
				}
			}
			dst.setChannel(Row/n, Column/n, 0, tRed/(n*n));
			dst.setChannel(Row/n, Column/n, 1, tGreen/(n*n));
			dst.setChannel(Row/n, Column/n, 2, tBlue/(n*n));

			tRed = 0;
			tGreen = 0;
			tBlue = 0;
		}
	}
}
