#pragma once

#include "game_object.hpp"
#include <map>
#include <functional>




class ClassRegistry
{
public:

	static ClassRegistry* Get();

	template<class T>
  void RegisterClass();

  GameObject* Create(uint32_t classId);


private:
	std::map<uint32_t, std::function<GameObject*()>> classCreators;
  ClassRegistry();
  static ClassRegistry* instance;

};
