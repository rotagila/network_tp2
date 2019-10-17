#include <iostream>

#include <uvw.hpp>
#include <memory>

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
	auto loop = uvw::Loop::getDefault();


	int i = getchar();

	if (i == '0')
	{
		listen(*loop);
	}
	else
		conn(*loop);

	loop->run();


	std::cin.ignore();
}