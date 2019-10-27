#pragma once

#include <cstdint>
#include "streams.hpp"
#include "LinkingContext.hpp"

using ReplicationClassID = uint32_t;

#define REPLICATED(id,className)                                    \
enum : ReplicationClassID{mClassID = id};                           \
virtual ReplicationClassID ClassID() const  { return mClassID;}     \
static GameObject* CreateInstance() {return new className();}       \
//ClassRegistry::Get()->RegisterClass<GameObject>();

class GameObject
{
public:
	REPLICATED('GOBJ', GameObject);

	GameObject() {}
	~GameObject() {}

	virtual void Read(MemoryStream& in){}
	virtual void Write(MemoryStream& out){}
	//virtual void Destroy(){}
	virtual void Destroy(LinkingContext &lc)
	{
		lc.RemoveGameObject(this);
		this->~GameObject();
	}
};