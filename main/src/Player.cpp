#include "Player.hpp"
Player::Player(const GameObject& g){

	/*if (g != null && g.ClassID() == 'PLAY')
	{
		Player p = Player((Player)g);

		/*name = p.name;
		position = p.position;
		rotation = p.rotation;*/
	//}
}

Player::Player(std::string n, Vector3 p, Quaternion r) {
	name = n;
	position = p;
	rotation = r;
}

Player::Player(const Player & p)
{
	name = p.name;
	position = p.position;
	rotation = p.rotation;
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
