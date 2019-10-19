#include "..\include\Player.hpp"


Player::Player(std::string n, Vector3 p, Quaternion r) {
	name = n;
	position = p;
	rotation = r;
}


void Player::Read(InputStream& in)
{
	name = in.ReadStr();
	position = in.ReadVector3();
	rotation = in.ReadQuat();
}

void Player::Write(OutputStream& out)
{
	out.WriteStr(name);
	out.Write(position);
	out.Write(rotation);
}
