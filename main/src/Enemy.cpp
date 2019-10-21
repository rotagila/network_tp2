#include "..\include\Enemy.hpp"

Enemy::Enemy(const GameObject& g) {


}

Enemy::Enemy(std::string t, Vector3 p, Quaternion r) {
	type = t;
	position = p;
	rotation = r;
}

Enemy::Enemy(const Enemy& e)
{
	type = e.type;
	position = e.position;
	rotation = e.rotation;
}

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
