#include "..\include\Enemy.hpp"

void Enemy::Read(InputStream& in)
{
	type = in.ReadStr();
	in.Read(position);
	in.Read(rotation);
}

void Enemy::Write(OutputStream& out)
{
	out.WriteStr(type);
	out.Write(position);
	out.Write(rotation);
}
