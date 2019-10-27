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

GameObject* ClassRegistry::Create(uint32_t classId) {
  GameObject* go = new GameObject();

  /*RegisterClass<GameObject>();

  std::function<GameObject*()> creator = classCreators[classId];

  go = creator();*/

  return go;
}

template<class T>
void ClassRegistry::RegisterClass()
{
  assert(classCreators.find(T::mClassID) == classCreators.end());
  classCreators[T::mClassID] = T::CreateInstance;
}