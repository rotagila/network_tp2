#include <map>
#include <unordered_set>
#include <functional>

#include "game_object.hpp"
#include "LinkingContext.hpp"
#include "ClassRegistry.hpp"

class ReplicationManager
{
public:
  void ReplicateWrite(MemoryStream& stream, std::vector<GameObject*>& totalGameObjects)
  {
    //inStream.Write(PT_ReplicationData, GetRequiredBits<PT_MAX>::Value);
    
    for (GameObject* go : totalGameObjects)
    {
      stream.Write(linkingContext->GetNetworkId(go, true));
      uint32_t test = go->ClassID();
      stream.Write(test);
      go->Write(stream);
    }
    
  }

  void ReplicateReadStream(MemoryStream& stream) {

      std::unordered_set<GameObject*> receivedObjects;
      while (stream.Size() > 0)
      {
        GameObject* receivedGo = ReplicateReadObject(stream);
        receivedObjects.insert(receivedGo);
      }

      for (GameObject* go : replicatedGameObject)
      {
        if (receivedObjects.find(go) != receivedObjects.end())
        {
          linkingContext->RemoveGameObject(go);
          go->Destroy();
        }
      }

      replicatedGameObject = receivedObjects;

  }

  GameObject* ReplicateReadObject(MemoryStream& stream)
  {
    uint32_t networkId;
    uint32_t classId;
    stream.Read(networkId);
    stream.Read(classId);
    std::optional <GameObject*> go = linkingContext->GetGameObject(networkId);

    if (!go)
    {
      *go = &ClassRegistry::Get().Create(classId);
      
      linkingContext->AddGameObject(*go, networkId);
    }
    go.value()->Read(stream);
    return *go;
  }

  
  

  private:
    LinkingContext* linkingContext;
    std::unordered_set <GameObject*> replicatedGameObject;
};