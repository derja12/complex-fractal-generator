#include "ThreadedGrid.h"
#include "NumberGrid.h"
#include "JuliaSet.h"
#include <thread>


ThreadedGrid::ThreadedGrid()
: NumberGrid() {

}

ThreadedGrid::ThreadedGrid(const int& height, const int& width)
: NumberGrid(height, width) {

}

ThreadedGrid::~ThreadedGrid()
{

}

void ThreadedGrid::calculateAllNumbers()
{
 	int Row;
	unsigned int max_threads = 4; //std::thread::hardware_concurrency();
	unsigned int i;
	std::vector<std::thread> threads;

	for (Row = 0; Row < getHeight(); Row++)
	{
		mTasks.push_back(Row);
	}

	for (i = 0; i < max_threads; i++)
	{
		threads.push_back( std::thread(&ThreadedGrid::worker, this) );
	}

	for(i = 0; i < max_threads; i++) 
	{
    	threads[i].join();
	}
}

void ThreadedGrid::worker()
{
	std::vector<int> my_tasks;
	int Column, Row, number;
	

	while (!mTasks.empty())
	{
		my_tasks.clear();
		mTasks.pop_back(my_tasks,1);
		if (my_tasks.size() > 0)
		{
			Row = my_tasks[0];
			for (Column = 0; Column < mWidth; Column++)
			{
				number = calculateNumber(Row, Column);
				setNumber(Row, Column, number);
			}
		}
	}
}
