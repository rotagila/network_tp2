#pragma once

#include <game_object.hpp>
#include <string>
#include "streams.hpp"

class Player : public GameObject
{

public:
	std::string name;
	Vector3 position;
	Quaternion rotation;

	Player(){}

	Player(std::string n, Vector3 p, Quaternion r);

	void Read(InputStream& in);
	void Write(OutputStream& out);
};
