#include <map>
#include <unordered_set>
#include <functional>

#include "game_object.hpp"
#include "LinkingContext.hpp"
#include "ClassRegistry.hpp"

class ReplicationManager
{
public:
	std::unordered_set <GameObject*> replicatedGameObject;

	ReplicationManager(){
		linkingContext = new LinkingContext();
	}





  void ReplicateWrite(OutputStream& stream, std::vector<GameObject*>& totalGameObjects)
  {
    //inStream.Write(PT_ReplicationData, GetRequiredBits<PT_MAX>::Value);
    
    for (GameObject* go : totalGameObjects)
    {

		uint32_t temp = linkingContext->GetNetworkId(go, true).value();
		
		if (temp != NULL) {
			stream.Write(temp);
			uint32_t test = go->ClassID();
			stream.Write(test);
			if (go->ClassID() == 'PLAY')
				((Player*)go)->Write(stream);
			else
				go->Write(stream);
		}
    }
    
  }

  void ReplicateReadStream(InputStream& stream) {

      std::unordered_set<GameObject*> receivedObjects;
      while (stream.RemainingSize() > 0)
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

  GameObject* ReplicateReadObject(InputStream& stream)
  {
	  uint32_t networkId;
	  uint32_t classId;


	  std::string s(reinterpret_cast<char*>(stream.Data().data()), stream.Data().size());

	  std::cout << "data " << s << std::endl;


	  networkId = stream.Read<uint32_t>();
	  classId = stream.Read<uint32_t>();


	  //GameObject * go = (linkingContext->GetGameObject(networkId)).value();

	  //GameObject *go;

	  if (classId == 'PLAY') {
		  Player *go = new Player(**(linkingContext->GetGameObject(networkId)));

		  if (!go)
		  {
			  go = dynamic_cast<Player *>(ClassRegistry::Get()->Create(classId));

			  linkingContext->AddGameObject(go, networkId);
		  }

		  go->name = "antoria";

		  std::cout << "mais fuck la vie" << std::endl;
		  go->Read(stream);
		  return go;
	  }
	  else
	  {
		  GameObject *go = (linkingContext->GetGameObject(networkId)).value();

		  if (!go)
		  {
			  go = ClassRegistry::Get()->Create(classId);

			  linkingContext->AddGameObject(go, networkId);
		  }
		  go->Read(stream);
		  return go;
	  }

  }

  
  

  private:
    LinkingContext* linkingContext;
};