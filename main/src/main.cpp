#include <iostream>

#include <uvw.hpp>
#include <memory>

#include "streams.hpp"
#include "utils.hpp"
#include "Player.hpp"

void listen(uvw::Loop &loop) {
	std::shared_ptr<uvw::TCPHandle> tcp = loop.resource<uvw::TCPHandle>();

	tcp->on<uvw::ListenEvent>([](const uvw::ListenEvent &, uvw::TCPHandle &srv) {
		std::shared_ptr<uvw::TCPHandle> client = srv.loop().resource<uvw::TCPHandle>();

		client->on<uvw::CloseEvent>([ptr = srv.shared_from_this()](const uvw::CloseEvent &, uvw::TCPHandle &) { ptr->close(); });
		client->on<uvw::EndEvent>([](const uvw::EndEvent &, uvw::TCPHandle &client) { client.close(); });
		client->on<uvw::DataEvent>([](const uvw::DataEvent& evt, uvw::TCPHandle &) {
			std::string s(evt.data.get(), evt.length);
			std::cout << "received " << s << std::endl;
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


}

void conn(uvw::Loop &loop) {
	auto tcp = loop.resource<uvw::TCPHandle>();

	tcp->on<uvw::ErrorEvent>([](const uvw::ErrorEvent &, uvw::TCPHandle &) { /* handle errors */ });

	tcp->on<uvw::ConnectEvent>([](const uvw::ConnectEvent &, uvw::TCPHandle &tcp) {

		std::cout << "connected" << std::endl;

		tcp.read();

		std::vector<std::byte> bytes = {
			std::byte(65),
			std::byte(65)
		};

		std::string s(reinterpret_cast<char*>(bytes.data()), bytes.size());

		tcp.write(s.data(), s.length());
		std::cout << "send" << std::endl;

		//tcp.close();
		});

	tcp->on<uvw::DataEvent>([](const uvw::DataEvent& evt, uvw::TCPHandle &) {
		std::string s(evt.data.get(), evt.length);
		std::cout << "received " << s << std::endl;
		});

	tcp->connect(std::string{ "127.0.0.1" }, 4242);
	std::cin.ignore();

}

int main() {
	/*auto loop = uvw::Loop::getDefault();


	int i = getchar();

	if (i == '0')
	{
		listen(*loop);
	}
	else
		conn(*loop);

	loop->run();

	*/


	MemoryStream stream = MemoryStream();
	//float f = 4.2f;
	//unsigned int i = 1000999;
	

	//String Example
	/*std::string c = "toto";

	stream.WriteStr(c);

	std::string result = stream.ReadStr();*/

	//std::cout << result << std::endl;



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
	Player p(
		"toto",
		Vector3(1, 2, 3),
		Quaternion(4,5,6,7)
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

	std::cin.ignore();
}