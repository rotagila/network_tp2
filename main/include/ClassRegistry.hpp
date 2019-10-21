#pragma once

#include "game_object.hpp"
#include <map>
#include <functional>




class ClassRegistry
{
public:

	static ClassRegistry* Get();

	template<class T>
	void RegisterClass()
	{
		assert(classCreators.find(T::mClassID) == classCreators.end());
		classCreators[T::mClassID] = T::CreateInstance;
	}

	GameObject* Create(uint32_t classId)
	{
		GameObject* go = new GameObject();
		
		/*RegisterClass<GameObject>();

		std::function<GameObject*()> creator = classCreators[classId];

		go = creator();*/
		
		return go;
	}


private:
	std::map<uint32_t, std::function<GameObject*()>> classCreators;
  ClassRegistry();
  static ClassRegistry* instance;

};
