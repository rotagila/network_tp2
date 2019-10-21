#include <iostream>

#include "Server.hpp"
#include "Client.hpp"

int main() {

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

	std::cin.ignore();
}
