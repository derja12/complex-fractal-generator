#include <iostream>
#include "Image.h"

Image::Image()
	:mHeight(0), mWidth(0) {
	mVector.resize( mHeight * mWidth * 3);
}

Image::Image( const int& height, const int& width )
	:mHeight(height), mWidth(width) {
	mVector.resize( mHeight * mWidth * 3);
}

int Image::getHeight( ) const {
	return mHeight;
}
int Image::getWidth( ) const {
	return mWidth;
}
bool Image::indexValid( const int& row, const int& column, const int& channel ) const {
	if(row >= 0 && row < mHeight && column >= 0 && column < mWidth && channel >= 0 && channel < 3) {
		if(mVector.size() == 0){
			return false;
		}
		return true;
	}
	else {
		return false;
	}
}
int Image::index( const int& row, const int& column, const int& channel ) const {
	int ind;
	ind = ((row * mWidth * 3) + (column * 3)) + channel;
	return ind;
}
int Image::getChannel( const int& row, const int& column, const int& channel ) const {
	if (indexValid(row, column, channel)) 
	{
		if (mVector.size() == 0)
		{
			return -1;
		}
		return mVector[index(row,column,channel)];
	}
	return -1;
}
void Image::setHeight( const int& height) {
	if (height >= 0)
	{
		mHeight = height;
		mVector.resize(mHeight * mWidth * 3);	
	}
}
void Image::setWidth( const int& width) {
	if (width >= 0)
	{
		mWidth = width;
		mVector.resize(mHeight * mWidth * 3);	
	}
}
void Image::setChannel( const int&row, const int&column, const int& channel, const int& value) {
	if (indexValid(row, column, channel)) {
		mVector[index(row, column, channel)] = value;
	}
}
