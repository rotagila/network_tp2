#pragma once

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


  void Replicate(OutputStream& stream, std::vector<GameObject*>& totalGameObjects)
  {
    //inStream.Write(PT_ReplicationData, GetRequiredBits<PT_MAX>::Value);
    
	  std::vector<std::byte> protocolID;
	  protocolID.push_back(std::byte(0xDA));
	  protocolID.push_back(std::byte(0xDA));
	  protocolID.push_back(std::byte(0xDA));
	  protocolID.push_back(std::byte(0xDA));

	  gsl::span<std::byte> bytes(protocolID);

	  stream.Write(bytes);

    for (GameObject* go : totalGameObjects)
    {

		uint32_t temp = linkingContext->GetNetworkId(go, true).value();
		
		if (temp != NULL) {
			stream.Write(temp);
			uint32_t test = go->ClassID();
			stream.Write(test);
			if (go->ClassID() == 'PLAY')
				((Player*)go)->Write(stream);
			else if (go->ClassID() == 'ENEM')
				((Enemy*)go)->Write(stream);
			else
				go->Write(stream);
		}
    }
    
  }

  void Replicate(InputStream& stream) {

      
	  if (stream.RemainingSize() > 3) {
		  
		  std::cout << "i : " << std::endl;

		  bool sameProtocol = true;
		  gsl::span<std::byte> protocolID = stream.Read(4);
		  
		  for (int i = 0; i < protocolID.size(); i++) {
			  if (protocolID[i] != std::byte(0xDA)) {
				  sameProtocol = false;
				  std::cout << i << std::endl;
			  }
		  }
		  if (sameProtocol) {



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
					  go->Destroy(*linkingContext);
					  //go->Destroy();
				  }
			  }

			  replicatedGameObject = receivedObjects;
		  }

	  }

  }

  GameObject* ReplicateReadObject(InputStream& stream)
  {
	  uint32_t networkId;
	  uint32_t classId;

	  networkId = stream.Read<uint32_t>();
	  classId = stream.Read<uint32_t>();

	  if (classId == 'PLAY') 
	  {
		  GameObject* go = linkingContext->GetGameObject(networkId).value();

		  if (!go)
		  {
			  go = dynamic_cast<Player *>(ClassRegistry::Get()->Create(classId));
			  linkingContext->AddGameObject(go, networkId);
		  }

		  Player* p = new Player(*go);
		  
		  p->Read(stream);

		  return p;
	  }
	  else if(classId == 'ENEM')
	  {
		  GameObject* go = linkingContext->GetGameObject(networkId).value();

		  if (!go)
		  {
			  go = dynamic_cast<Enemy*>(ClassRegistry::Get()->Create(classId));
			  linkingContext->AddGameObject(go, networkId);
		  }

		  Enemy* e = new Enemy(*go);

		  e->Read(stream);

		  return e;
	  }

	  else
	  {
		  std::cout << "ReplicateGameObject unknown type" << std::endl;

		  GameObject *go = (linkingContext->GetGameObject(networkId)).value();

		  if (!go)
		  {
			  go = ClassRegistry::Get()->Create(classId);

			  linkingContext->AddGameObject(go, networkId);
		  }
			
		  // Type* t = new Type(*go);
		  //t->read(stream);
		  // return t;

		  go->Read(stream);
		  return go;

	  }

  }

  
  

  private:
    LinkingContext* linkingContext;
};