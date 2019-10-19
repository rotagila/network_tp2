#include "..\include\Enemy.hpp"

void Enemy::Read(InputStream& in)
{
	type = in.ReadStr();
	position = in.ReadVector3();
	rotation = in.ReadQuat();
}

void Enemy::Write(OutputStream& out)
{
	out.WriteStr(type);
	out.Write(position);
	out.Write(rotation);
}
