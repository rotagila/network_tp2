#include <iostream>

#include "Server.hpp"
#include "Client.hpp"

/*
ReplicationManager RM;

std::vector<GameObject*> world;

void PrintReplicatedGameObject() {
	std::cout << "----------------" << std::endl;
	for each(GameObject *go in RM.replicatedGameObject) {
		Player p = Player(*(reinterpret_cast<Player*>(go)));

		std::cout << "P :\n"
			<< "Name : " << p.name << "\n"
			<< "Position : (" << p.position.x << ", " << p.position.y << ", " << p.position.z << ")\n"
			<< "Rotation : (" << p.rotation.x << ", " << p.rotation.y << ", " << p.rotation.z << ", " << p.rotation.w << ")\n";
	}
	std::cout << "----------------" << std::endl;

}



void listen(uvw::Loop &loop) {
	std::shared_ptr<uvw::TCPHandle> tcp = loop.resource<uvw::TCPHandle>();

	tcp->on<uvw::ListenEvent>([](const uvw::ListenEvent &, uvw::TCPHandle &srv) {
		std::shared_ptr<uvw::TCPHandle> client = srv.loop().resource<uvw::TCPHandle>();
		
		client->on<uvw::CloseEvent>([ptr = srv.shared_from_this()](const uvw::CloseEvent &, uvw::TCPHandle &) { ptr->close(); });
		client->on<uvw::EndEvent>([](const uvw::EndEvent &, uvw::TCPHandle &client) { client.close(); });
		client->on<uvw::DataEvent>([](const uvw::DataEvent& evt, uvw::TCPHandle &client) {
			std::string s(evt.data.get(), evt.length);
			std::cout << "received" << std::endl;

			InputStream iStream(s);

			RM.ReplicateReadStream(iStream);

			for (GameObject *go : RM.replicatedGameObject) {
				Player* p = (dynamic_cast<Player*>(go));

				std::cout << "P1 :\n"
					<< "Name : " << p->name << "\n"
					<< "Position : (" << p->position.x << ", " << p->position.y << ", " << p->position.z << ")\n"
					<< "Rotation : (" << p->rotation.x << ", " << p->rotation.y << ", " << p->rotation.z << ", " << p->rotation.w << ")\n";
			}

			PrintReplicatedGameObject();

			client.write("ok",2);


			});
		srv.accept(*client);

		std::cout << "accept" << std::endl;

		client->read();

		auto dataWrite = std::unique_ptr<char[]>(new char[2]{ 'a', 'b' });

		client->write(std::move(dataWrite), 2);
		std::cout << "send" << std::endl;
		});

	tcp->bind("127.0.0.1", 4242);
	tcp->listen();
	std::cin.ignore();


}*/



void conn(uvw::Loop &loop) {
	auto tcp = loop.resource<uvw::TCPHandle>();

	tcp->on<uvw::ErrorEvent>([](const uvw::ErrorEvent &, uvw::TCPHandle &) { 
	//handle errors  
	});

	tcp->on<uvw::ConnectEvent>([](const uvw::ConnectEvent &, uvw::TCPHandle &tcp) {

		std::cout << "connected" << std::endl;

		/*OutputStream oStream;


		Player *antoria = new Player(
			"antoria",
			Vector3(0.451, -455.236, 424.242),
			Quaternion(0.002, 0.783, -0.261, 0.565)
		);

		Player *p1 = antoria;



		world.push_back(
			antoria
		);

		RM.replicatedGameObject.insert(world[0]);

		reinterpret_cast<Player*>(world[0])->position.x += 10;
		
		RM.replicatedGameObject.insert(world[0]);

		PrintReplicatedGameObject();

		RM.ReplicateWrite(oStream, world);

		std::string s(reinterpret_cast<char*>(oStream.Data().data()), oStream.Data().size());

		tcp.write(s.data(), s.length());*/

		tcp.read();
		});

	tcp->on<uvw::DataEvent>([](const uvw::DataEvent& evt, uvw::TCPHandle &tcp) {
		std::string s(evt.data.get(), evt.length);
		std::cout << "received " << s << std::endl;

		/*OutputStream oStream;

		reinterpret_cast<Player*>(world[0])->position.x += 10;

		RM.replicatedGameObject.insert(world[0]);

		RM.ReplicateWrite(oStream, world);

		std::string msg(reinterpret_cast<char*>(oStream.Data().data()), oStream.Data().size());
		*/
		tcp.write("ping", 4);
		});

	tcp->connect(std::string{ "127.0.0.1" }, 4242);
	std::cin.ignore();

}

int main() {

	//auto loop = uvw::Loop::getDefault();

	int i = getchar();

	if (i == '0')
	{
		Server server("127.0.0.1", 4242);
		std::cout << "you are now a server" << std::endl;
	}
	else {
		Client client("127.0.0.1",4242);
		std::cout << "you are now a client" << std::endl;
	}








	/*auto loop = uvw::Loop::getDefault();


	int i = getchar();

	if (i == '0')
	{
		std::cout << "you are now a server" << std::endl;
		listen(*loop);
	}
	else {
		std::cout << "you are now a client" << std::endl;
		conn(*loop);
	}

	loop->run();*/

	//MemoryStream stream = MemoryStream();
	
	//String Example
	/*std::string c = "toto";

	stream.WriteStr(c);

	std::string result = stream.ReadStr();

	std::cout << result << std::endl;*/



	//uint32 Example
	/*uint32_t i = 1000999;

	stream.Write(i);

	int j = stream.Read<int>();

	std::cout << j << std::endl;*/


	//Vector Example
	/*Vector3 v(42.42, 1.1, 0.1234);

	stream.Write(v);

	Vector3 result = stream.ReadVector3();

	std::cout << result.x << " " << result.y << " " << result.z << " " << std::endl;*/

	//Quaternion Example
	/*Quaternion q(42.42, 1.1, 0.1234, 1);

	stream.Write(q);

	Quaternion result = stream.ReadQuat();

	std::cout << result.x << " " << result.y << " " << result.z << " " << result.w << std::endl;*/

	//Player Example
	/*Player p(
		"toto",
		Vector3(0.999, -499.999, 499.213),
		Quaternion(0.002, 0.783, -0.261, 0.565)
		);

	OutputStream oStream = OutputStream();

	p.Write(oStream);

	InputStream iStream = InputStream(oStream.Data());

	Player p2;
	
	p2.Read(iStream);

	std::cout << "P1 :\n"
		<< "Name : " << p.name << "\n"
		<< "Position : (" << p.position.x << ", " << p.position.y << ", " << p.position.z << ")\n"
		<< "Rotation : (" << p.rotation.x << ", " << p.rotation.y << ", " << p.rotation.z << ", " << p.rotation.w << ")\n";

	std::cout << "P2 :\n"
		<< "Name : " << p2.name << "\n"
		<< "Position : (" << p2.position.x << ", " << p2.position.y << ", " << p2.position.z << ")\n"
		<< "Rotation : (" << p2.rotation.x << ", " << p2.rotation.y << ", " << p2.rotation.z << ", " << p2.rotation.w << ")\n";
		*/

	/*ReplicationManager RM = ReplicationManager();

	std::vector<GameObject*> world;

	Player antoria(
		"antoria",
		Vector3(0.451, -455.236, 424.242),
		Quaternion(0.002, 0.783, -0.261, 0.565)
	);

	Player p1 = antoria;

	std::cout << "P1 :\n"
		<< "Name : " << p1.name << "\n"
		<< "Position : (" << p1.position.x << ", " << p1.position.y << ", " << p1.position.z << ")\n"
		<< "Rotation : (" << p1.rotation.x << ", " << p1.rotation.y << ", " << p1.rotation.z << ", " << p1.rotation.w << ")\n";

	world.push_back(&antoria);

	RM.replicatedGameObject.insert(&antoria);


	MemoryStream stream = MemoryStream();

	RM.ReplicateWrite(stream, world);

	RM.ReplicateReadStream(stream);

	for (GameObject *go : RM.replicatedGameObject) {
		Player p = *(dynamic_cast<Player*>(go));
		std::cout << "P1 :\n"
			<< "Name : " << p.name << "\n"
			<< "Position : (" << p.position.x << ", " << p.position.y << ", " << p.position.z << ")\n"
			<< "Rotation : (" << p.rotation.x << ", " << p.rotation.y << ", " << p.rotation.z << ", " << p.rotation.w << ")\n";
	}*/

	

	std::cin.ignore();
}