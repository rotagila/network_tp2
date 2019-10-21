#include <iostream>

#include "Server.hpp"
#include "Client.hpp"

int main(int argc, char* argv[]) 
{
	std::string mode = std::string(argv[1]);

	if (mode == "server")
		Server server(argv[2], atoi(argv[3]));

	else if(mode == "client")
		Client client(argv[2], atoi(argv[3]));

	else
	{
		std::cout << "Invalid args (... (client|server) ip port)" << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "the end" << std::endl;

	std::cin.ignore();

}
