#include "../include/Client.hpp"

Client::Client(std::string s, int p) {
	address = s;
	port = p;

	auto loop = uvw::Loop::getDefault();
	ConnectLoop(*loop);
	loop->run();
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

void Client::OnErrorEvent(const uvw::ErrorEvent &, uvw::TCPHandle &srv) {
	std::cout << "ERROR" << std::endl;
}

void Client::OnDataEvent(const uvw::DataEvent& evt, uvw::TCPHandle &srv) {
	std::string msg(evt.data.get(), evt.length);
	
	std::cout << "data received : " << msg << std::endl;
	
	InputStream in(msg);

	RM.ReplicateReadStream(in);

	for (GameObject *go : RM.replicatedGameObject) {
		Player* p = (dynamic_cast<Player*>(go));

		std::cout << "P :\n"
			<< "Name : " << p->name << "\n"
			<< "Position : (" << p->position.x << ", " << p->position.y << ", " << p->position.z << ")\n"
			<< "Rotation : (" << p->rotation.x << ", " << p->rotation.y << ", " << p->rotation.z << ", " << p->rotation.w << ")\n";
	}

	in.Flush();
}