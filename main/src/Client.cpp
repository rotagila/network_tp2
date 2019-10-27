#include "../include/Client.hpp"

Client::Client(std::shared_ptr<uvw::Loop> loop, std::string s, int p) {
	address = s;
	port = p;

	ConnectLoop(*loop);
}

void Client::ConnectLoop(uvw::Loop &loop) {
	auto tcp = loop.resource<uvw::TCPHandle>();


	//Error Event Declaration
	std::function<void(const uvw::ErrorEvent &, uvw::TCPHandle &)> onError;
	onError = std::bind(&Client::OnErrorEvent, this, std::placeholders::_1, std::placeholders::_2);
	tcp->on<uvw::ErrorEvent>(onError);

	//Connect Event Declaration
	std::function<void(const uvw::ConnectEvent &, uvw::TCPHandle &)> onConnect;
	onConnect = std::bind(&Client::OnConnectEvent, this, std::placeholders::_1, std::placeholders::_2);
	tcp->on<uvw::ConnectEvent>(onConnect);
	
	//Data Event Declaration
	std::function<void(const uvw::DataEvent &, uvw::TCPHandle &)> onData;
	onData = std::bind(&Client::OnDataEvent, this, std::placeholders::_1, std::placeholders::_2);
	tcp->on<uvw::DataEvent>(onData);

	tcp->connect(address, port);
}

void Client::Connect(uvw::TCPHandle &tcp) {

	tcp.connect(address, port);

}

void Client::OnConnectEvent(const uvw::ConnectEvent &, uvw::TCPHandle &srv) {
	std::cout << "connected" << std::endl;

	srv.read();
}

void Client::OnErrorEvent(const uvw::ErrorEvent &evt, uvw::TCPHandle &srv) {
	std::cout << "ERROR CODE : " << evt.code() << std::endl;
}

void Client::OnDataEvent(const uvw::DataEvent& evt, uvw::TCPHandle &srv) {
	std::string msg(evt.data.get(), evt.length);
		
	InputStream in(msg);
	RM->Replicate(in);

	for (GameObject *go : RM->replicatedGameObject) 
	{	
		if (go->ClassID() == 'PLAY')
		{
			Player* p = (dynamic_cast<Player*>(go));
			std::cout << "Player :\n"
				<< "Name : " << p->name << "\n"
				<< "Position : x: " << p->position.x << "  y:  " << p->position.y << "  z:  " << p->position.z << "\n"
				<< "Rotation : x: " << p->rotation.x << "  y:  " << p->rotation.y << "  z:  " << p->rotation.z << "  w:  " << p->rotation.w << "\n";
		}
		else if (go->ClassID() == 'ENEM')
		{
			Enemy* e = (dynamic_cast<Enemy*>(go));
			std::cout << "Enemy :\n"
				<< "Type : " << e->type << "\n"
				<< "Position : x: " << e->position.x << "  y:  " << e->position.y << "  z:  " << e->position.z << "\n"
				<< "Rotation : x: " << e->rotation.x << "  y:  " << e->rotation.y << "  z:  " << e->rotation.z << "  w:  " << e->rotation.w << "\n";
		}
		else
		{
			std::cout << "unknown gameobject type" << std::endl;
		}
		

		
	}

	in.Flush();
}