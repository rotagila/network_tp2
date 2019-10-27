#include "../include/Server.hpp"

#include <chrono>

using namespace std::chrono_literals;

Server::Server(std::shared_ptr<uvw::Loop> loop, std::string s, int p) {
	address = s;
	port = p;

	Listen(*loop);
}

void Server::Listen(uvw::Loop &loop) {
	std::shared_ptr<uvw::TCPHandle> tcp = loop.resource<uvw::TCPHandle>();

	std::function<void(const uvw::ListenEvent &, uvw::TCPHandle &srv)> onListen;

	onListen = std::bind(&Server::OnListenEvent, this, std::placeholders::_1, std::placeholders::_2);

	tcp->on<uvw::ListenEvent>(onListen);

	tcp->bind(address, port);
	tcp->listen();
	//std::cin.ignore();
}


void Server::OnListenEvent(const uvw::ListenEvent &, uvw::TCPHandle &srv) {

	std::shared_ptr<uvw::TCPHandle> client = srv.loop().resource<uvw::TCPHandle>();


	//OnCloseEvent Declaration
	std::function<void(const uvw::CloseEvent &, uvw::TCPHandle &)> onClose;
	onClose = std::bind(&Server::OnCloseEvent, this, std::placeholders::_1, std::placeholders::_2);
	srv.on<uvw::CloseEvent>(onClose);


	//OnEndEvent Declaration
	std::function<void(const uvw::EndEvent &, uvw::TCPHandle &)> onEnd;
	onEnd = std::bind(&Server::OnEndEvent, this, std::placeholders::_1, std::placeholders::_2);
	srv.on<uvw::EndEvent>(onEnd);


	//OnDataEvent Declaration
	std::function<void(const uvw::DataEvent &, uvw::TCPHandle &)> onData;
	onData = std::bind(&Server::OnDataEvent, this, std::placeholders::_1, std::placeholders::_2);
	srv.on<uvw::DataEvent>(onData);


	srv.accept(*client);

	clients.push_back(client);

	std::cout << "accepted new client" << std::endl;

	client->read();

	auto t = std::make_shared<std::thread>(&Server::TestLoop, this);
	threads.emplace_back(t);
}

void Server::OnCloseEvent(const uvw::CloseEvent &, uvw::TCPHandle &client) {
	std::cout << "client close" << std::endl;
}

void Server::OnEndEvent(const uvw::EndEvent &, uvw::TCPHandle &client) {
	std::cout << "end event" << std::endl;
}

void Server::OnDataEvent(const uvw::DataEvent& evt, uvw::TCPHandle &client) {
	std::cout << "data received : " << std::string(evt.data.get(), evt.length) << std::endl;
	client.write("pong", 4);
}

void Server::SendToAll(char* msg, size_t size) {
	for(int i = 0; i < clients.size(); i++)
	{
		clients[i]->write(msg, size);	
	}
}

void Server::SendWorldToAll() {

	OutputStream out;

	RM->Replicate(out, world);

	std::string msg(reinterpret_cast<char*>(out.Data().data()), out.Data().size());

	SendToAll(msg.data(), msg.size());

	out.Flush();
}



void Server::TestLoop() {
	//Create your starting GameObjects here

	Enemy *antoria = new Enemy(
		"antoria",
		Vector3(1.23, 4.5, 6.789),
		Quaternion(0.002, 0.783, -0.261, 0.565)
	);

	Enemy *rotagg = new Enemy(
		"rotaggikoi",
		Vector3(0, 0, 0),
		Quaternion(0.002, 0.783, -0.261, 0.565)
	);

	Player *kathaersys = new Player(
		"kathaersys",
		Vector3(-500, 499.999, 0),
		Quaternion(0.002, 0.783, -0.261, 0.565)
	);

	Player *null_reference = new Player(
		"cataclimax > ubi",
		Vector3(150, 150, 150),
		Quaternion(0.002, 0.783, -0.261, 0.565)
	);

	world.push_back(antoria);
	world.push_back(rotagg);
	world.push_back(kathaersys);
	world.push_back(null_reference);
	
	std::cout << "Last gameobject won't be updated (for testing purposes) during this execution." << std::endl;

	int i = 0;

	while (true) 
	{
		RM->replicatedGameObject.clear();

		if (i == 2)
		{
			std::cout << "Deleting Kathaersys" << std::endl;

			std::vector<GameObject*> newWorld;
			newWorld.push_back(antoria);
			newWorld.push_back(rotagg);
			newWorld.push_back(null_reference);

			world = newWorld;

		}
		if (i >= 2)
		{
			std::cout << "Moving antoria on x axis, changing rotagg type" << std::endl;

			RM->replicatedGameObject.insert(world[0]);
			RM->replicatedGameObject.insert(world[1]);
			RM->replicatedGameObject.insert(world[2]);

			SendWorldToAll();
			std::this_thread::sleep_for(3.5s);

			reinterpret_cast<Enemy*>(world[0])->position.x += 1;

			if (i % 2 == 0)
				reinterpret_cast<Enemy*>(world[1])->type = "dragon";
			else
				reinterpret_cast<Enemy*>(world[1])->type = "rotaggikoi";

		}
		else
		{
			std::cout << "Moving antoria on x axis, changing rotagg type, moving kathaersys on z axis" << std::endl;

			RM->replicatedGameObject.insert(world[0]);
			RM->replicatedGameObject.insert(world[1]);
			RM->replicatedGameObject.insert(world[2]);
			RM->replicatedGameObject.insert(world[3]);

			SendWorldToAll();
			std::this_thread::sleep_for(3.5s);

			reinterpret_cast<Enemy*>(world[0])->position.x += 1;

			if (i % 2 == 0)
				reinterpret_cast<Enemy*>(world[1])->type = "dragon";
			else
				reinterpret_cast<Enemy*>(world[1])->type = "rotaggikoi";

			reinterpret_cast<Player*>(world[2])->position.z += 0.42;

		}
		
		i++;
	}
}

