#include "..\include\Player.hpp"

void Player::Read(InputStream& in)
{
	name = in.ReadStr();
	in.Read(position);
	in.Read(rotation);
}

void Player::Write(OutputStream& out)
{
	out.WriteStr(name);
	out.Write(position);
	out.Write(rotation);
}
