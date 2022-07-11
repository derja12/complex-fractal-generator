#include "ColorTable.h"
#include <cstdlib>
#include <ctime>

Color::Color( )
: mRed(0), mGreen(0), mBlue(0) 
{

}

Color::Color(const int& red, const int& green, const int& blue)
: mRed(red), mGreen(green), mBlue(blue)
{

}

int Color::getRed( ) const
{
	return mRed;
}

int Color::getGreen( ) const
{
	return mGreen;
}

int Color::getBlue( ) const
{
	return mBlue;
}

int Color::getChannel( const int& channel ) const
{
	if (channel == 0)
	{
		return mRed;
	}
	else if (channel == 1)
	{
		return mGreen;
	}
	else if (channel == 2)
	{
		return mBlue;
	}
	else
	{
		return -1;
	}
}

void Color::setRed( const int& value )
{
	if (value >= 0)
	{
		mRed = value;
	}
}

void Color::setGreen( const int& value )
{
	if (value >= 0)
	{
		mGreen = value;
	}
}

void Color::setBlue( const int& value )
{
	if (value >= 0)
	{
		mBlue = value;
	}
}

void Color::setChannel( const int& channel, const int& value )
{
	if (value >= 0)
	{
		if (channel == 0)
		{
			mRed = value;
		}
		else if (channel == 1)
		{
			mGreen = value;
		}
		else if (channel == 2)
		{
			mBlue = value;
		}
	}
}

void Color::invert( const int& max_color_value )
{
	if (max_color_value >= mRed && max_color_value >= mGreen && max_color_value >= mBlue)
	{
		mRed = max_color_value - mRed;
		mGreen = max_color_value - mGreen;
		mBlue = max_color_value - mBlue;
	}
}

bool Color::operator==( const Color& rhs ) const
{
	if (mRed == rhs.getRed() && mGreen == rhs.getGreen() && mBlue == rhs.getBlue())
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::ostream& operator<<( std::ostream& os, const Color& color )
{
	os << color.getRed() << ":" << color.getGreen() << ":" << color.getBlue();
	return os;
}


ColorTable::ColorTable( const size_t& num_color )
{
	mColors.resize(num_color);
}

size_t ColorTable::getNumberOfColors( ) const
{
	return mColors.size();
}

void ColorTable::setNumberOfColors( const size_t& num_color )
{
	mColors.resize(num_color);
}

const Color& ColorTable::operator[]( const unsigned int& i ) const
{
	if (i < getNumberOfColors())
	{
		return mColors[i];
	}
	else
	{
	    static Color ec( -1, -1, -1 );
	    static Color c( -1, -1, -1 );
	    c = ec;
	    return c;
	}
}

Color& ColorTable::operator[]( const unsigned int& i )
{
	if (i < getNumberOfColors())
	{
		return mColors[i];
	}
	else
	{
	    static Color ec( -1, -1, -1 );
	    static Color c( -1, -1, -1 );
	    c = ec;
	    return c;
	}
}

void ColorTable::setRandomColor( const int& max_color_value, const size_t& position )
{
	int rand_color;
	if (max_color_value >= 0 && position < getNumberOfColors())
	{
		rand_color = std::rand() % (max_color_value + 1);
		mColors[position].setRed(rand_color);
		rand_color = std::rand() % (max_color_value + 1);
		mColors[position].setGreen(rand_color);
		rand_color = std::rand() % (max_color_value + 1);
		mColors[position].setBlue(rand_color);
	}
}

void ColorTable::insertGradient( const Color& color1, const Color& color2, const size_t& position1, const size_t& position2 )
{
	int new_red, new_green, new_blue, n, i;
	float red_step, green_step, blue_step, rinterm, ginterm, binterm;
	if (position1 < getNumberOfColors() && position2 < getNumberOfColors() && position1 < position2)
	{
		n = position2 - position1;
		rinterm = (color2.getRed()-color1.getRed());
		red_step = rinterm/(n);
		ginterm = (color2.getGreen()-color1.getGreen());
		green_step = ginterm/(n);
		binterm = (color2.getBlue()-color1.getBlue());
		blue_step = binterm/(n);
		for (i = 0; i < (n + 1); i++)
		{
			new_red = color1.getRed() + (i * red_step);
			new_green = color1.getGreen() + (i * green_step);
			new_blue = color1.getBlue() + (i * blue_step);
			mColors[position1 + i].setRed(new_red);
			mColors[position1 + i].setGreen(new_green);
			mColors[position1 + i].setBlue(new_blue);
		}
	}
}

int ColorTable::getMaxChannelValue( ) const
{
	unsigned int i;
	int Max;
	Max = mColors[0].getRed();
	for (i = 0; i < getNumberOfColors(); i++)
	{
		if (mColors[i].getRed() > Max)
		{
			Max = mColors[i].getRed();
		}
		if (mColors[i].getGreen() > Max)
		{
			Max = mColors[i].getGreen();
		}
		if (mColors[i].getBlue() > Max)
		{
			Max = mColors[i].getBlue();
		}
	}
	return Max;
}

void ColorTable::insertInvertedGradient( const Color& color1, const size_t& position1, const size_t& position2 )
{
	Color color2(color1.getRed(), color1.getGreen(), color1.getBlue());

	color2.invert(255);

	insertGradient(color1, color2, position1, position2);
	
}

int Color::operator-( const Color& rhs ) const
{
	return (std::abs(getRed() - rhs.getRed()) + std::abs(getGreen() - rhs.getGreen()) + std::abs(getBlue() - rhs.getBlue()));
}

void ColorTable::insertRandomGradient( const int& min_dist, const int& max_dist, const int& max_color_value, const size_t& position1, const size_t& position2 )
{
	int distance = 0;
	Color c1, c2;

	while (distance < min_dist || distance > max_dist)
	{
		c1.setRed(std::rand() % (max_color_value + 1));
		c1.setGreen(std::rand() % (max_color_value + 1));
		c1.setBlue(std::rand() % (max_color_value + 1));
		c2.setRed(std::rand() % (max_color_value + 1));
		c2.setGreen(std::rand() % (max_color_value + 1));
		c2.setBlue(std::rand() % (max_color_value + 1));

		distance = c1 - c2;
	}

	insertGradient(c1, c2, position1, position2);
}