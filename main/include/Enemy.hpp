#pragma once

#include <string>
#include "streams.hpp"

class Enemy : public GameObject
{

public:
	Vector3 position;
	std::string type;
	Quaternion rotation;

	void Read(InputStream& in);
	void Write(OutputStream& out) const;
};
