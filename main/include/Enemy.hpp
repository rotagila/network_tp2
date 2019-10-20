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

	void Read(InputStream& in);
	void Write(OutputStream& out);
};
