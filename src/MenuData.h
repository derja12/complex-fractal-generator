#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "ActionData.h"
#ifndef _MENUDATA_H_
#define _MENUDATA_H_

typedef void (*ActionFunctionType)(ActionData& action_data);

class MenuData 
{

public:

	MenuData();
	void addAction(const std::string& name, ActionFunctionType func, const std::string& description);
	const std::vector<std::string>& getNames() const;
	ActionFunctionType getFunction(const std::string& name);
	const std::string& getDescription(const std::string& name);

protected:
	std::vector<std::string> mNames;
	std::map<std::string,ActionFunctionType> mFunctions;
	std::map<std::string,std::string> mDescriptions;

};
#endif