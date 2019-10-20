#include "ClassRegistry.hpp"

ClassRegistry* ClassRegistry::instance = 0;


ClassRegistry::ClassRegistry() {
	//ClassRegistry::instance = nullptr;
}


ClassRegistry* ClassRegistry::Get()
{
	if (instance == 0)
		instance = new ClassRegistry();
	return instance;
}