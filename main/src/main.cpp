#include <iostream>

#include "Server.hpp"
#include "Client.hpp"

int main(int argc, char* argv[]) 
{
	std::cout << "once upon a time" << std::endl;


	if (argc != 4)
	{
		std::cout << "Invalid args (... (client|server) ip port)" << std::endl;
		return EXIT_FAILURE;
	}
	else
	{
		std::string mode = std::string(argv[1]);

		auto loop = uvw::Loop::getDefault();


		if (mode == "server")
		{
			Server server(loop, argv[2], atoi(argv[3]));
			std::cout << "server started" << std::endl;
		}

		else if (mode == "client")
		{
			Client client(loop, argv[2], atoi(argv[3]));
			std::cout << "client started" << std::endl;
		}

		else
		{
			std::cout << "Invalid args (... (client|server) ip port)" << std::endl;
			return EXIT_FAILURE;
		}

		loop->run();

		std::cout << "the end" << std::endl;

		std::cin.ignore();
	}


	

}
