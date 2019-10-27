#pragma once

#include "game_object.hpp"
#include <string>
#include "streams.hpp"

class Player : public GameObject
{
public:
	REPLICATED('PLAY', Player);

	std::string name;
	Vector3 position;
	Quaternion rotation;

	Player() {};
	~Player() {};

	Player(std::string n, Vector3 p, Quaternion r);
	Player(const Player& p);
	Player(const GameObject& g);
	

	void Read(InputStream& in);
	void Write(OutputStream& out);
};
