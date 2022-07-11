#ifndef _THREADEDGRID_H_
#define _THREADEDGRID_H_
#include "NumberGrid.h"
#include "ThreadedVector.h"
#include <vector>

class ThreadedGrid : public NumberGrid 
{
public:
	ThreadedGrid();
	ThreadedGrid(const int& height, const int& width);
	virtual ~ThreadedGrid();
	virtual void calculateAllNumbers();
	virtual void worker();

protected:
	ThreadedVector<int> mTasks;
};

#endif