#include <iostream>
#include "PPM.h"
#include "NumberGrid.h"
#include "ColorTable.h"
#ifndef _ACTIONDATA_H_
#define _ACTIONDATA_H_

class ActionData : public PPM {
public:

	ActionData(std::istream& is, std::ostream& os);
	std::istream& getIS();
	std::ostream& getOS();
	PPM& getInputImage1();
	PPM& getOutputImage();
	bool getDone() const;
	void setDone();
	PPM& getInputImage2();

	~ActionData();
	NumberGrid& getGrid();
	void setGrid(NumberGrid *grid);
	ColorTable& getTable();

	bool getQuiet();
	void setQuiet();

protected:
	
	std::istream& mIs;
	std::ostream& mOs;
	PPM mInputImage1;
	PPM mOutputImage;
	bool mDone;
	PPM mInputImage2;
	NumberGrid *mNumberGrid;
	ColorTable mColorTable;
	bool mQuiet;

};

#endif