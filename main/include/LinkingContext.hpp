#pragma once

#include <map>
#include <cstdint>
#include <optional>
#include "streams.hpp"
#include "game_object.hpp"

class LinkingContext 
{
  public:
    

    LinkingContext() 
	{
      nextId = 1;
	  ptrToId = std::map<GameObject*, uint32_t>();
	  idToPtr = std::map<uint32_t, GameObject*>();

    }

    uint32_t AddLink(GameObject* go) 
	{
		uint32_t newId = nextId++;
		AddGameObject(go, newId);
		return newId;
    }

    std::optional<uint32_t> GetNetworkId(GameObject* go, bool ifError)
    {
		if (ptrToId.size() >= 0) {
			auto it = ptrToId.find(go);
			if (it != ptrToId.end())
				return it->second;

			else if (ifError)
			{
				return AddLink(go);
			}
			else
				return -1;
		}
      
    }

    std::optional<GameObject*> GetGameObject(uint32_t id)
    {
      auto it = idToPtr.find(id);
      if (it != idToPtr.end())
        return it->second;

      else
        return nullptr;
    }

    void AddGameObject(GameObject* go, uint32_t id)
    {
      idToPtr[id] = go;
      ptrToId[go] = id;
    }

    void RemoveGameObject(GameObject* go)
    {
      uint32_t id = ptrToId[go];
      ptrToId.erase(go);
      idToPtr.erase(id);
    }

private:
  std::map<uint32_t, GameObject*> idToPtr;
  std::map<GameObject*, uint32_t> ptrToId;

  uint32_t nextId;
};