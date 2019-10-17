#pragma once

#include <map>
#include <cstdint>
#include <optional>
#include "streams.hpp"
#include "game_object.hpp"

class LinkingContext 
{
  public:
    

    LinkingContext() {
      nextId = 1;
    }

    void AddLink(GameObject* go) {
      //ca marche probablement pas
      AddGameObject(go, nextId++);
    }

    std::optional<uint32_t> GetNetworkId(GameObject* go, bool ifError)
    {
      auto it = ptrToId.find(go);
      if (it != ptrToId.end())
        return it->second;
      
      else if (ifError)
      {
        uint32_t newId = nextId++;
        AddGameObject(go, newId);
        return newId;
      }
      else
        return -1;
      
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