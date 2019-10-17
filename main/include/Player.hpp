#pragma once

#include <string>
#include "streams.hpp"

class Player : public GameObject
{

public:
	Vector3 position;
	std::string name;
	Quaternion rotation;

	void Read(InputStream& in);
	void Write(OutputStream& out) const;
};
