#pragma once

#include <game_object.hpp>
#include <string>
#include "streams.hpp"

class Enemy : public GameObject
{

public:
	REPLICATED('ENEM', Enemy);

	Vector3 position;
	std::string type;
	Quaternion rotation;

	Enemy(){}
	Enemy(std::string t, Vector3 p, Quaternion r);
	Enemy(const Enemy& p);
	Enemy(const GameObject& g);

	void Read(InputStream& in);
	void Write(OutputStream& out);
};
