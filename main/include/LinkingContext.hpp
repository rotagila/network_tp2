#pragma once

#include <map>
#include <cstdint>
#include <optional>
#include "streams.hpp"
//#include "game_object.hpp"
class GameObject;

class LinkingContext 
{
  public:
    

    LinkingContext();

    uint32_t AddLink(GameObject* go);

    std::optional<uint32_t> GetNetworkId(GameObject* go, bool ifError);

    std::optional<GameObject*> GetGameObject(uint32_t id);

    void AddGameObject(GameObject* go, uint32_t id);

    void RemoveGameObject(GameObject* go);

private:
  std::map<uint32_t, GameObject*> idToPtr;
  std::map<GameObject*, uint32_t> ptrToId;

  uint32_t nextId;
};