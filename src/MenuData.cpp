#include <iostream>
#include "MenuData.h"
#include "ActionData.h"

MenuData::MenuData()
{

}

void MenuData::addAction(const std::string& name, ActionFunctionType func, const std::string& description) 
{
	mNames.push_back(name);

	mFunctions[name] = func;

	mDescriptions[name] = description;
}

const std::vector<std::string>& MenuData::getNames() const 
{
	return mNames;
}

ActionFunctionType MenuData::getFunction(const std::string& name)
{
 	if (mFunctions.find(name) != mFunctions.end())
 	{
 		return mFunctions[name];
 	}
 	return 0;
}

const std::string& MenuData::getDescription(const std::string& name)
{
	static std::string nothin;

	if (mDescriptions.find(name) != mDescriptions.end())
 	{
 		return mDescriptions[name];
 	}
 	return nothin;
}