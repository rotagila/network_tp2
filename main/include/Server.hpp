#pragma once

#include <uvw.hpp>
#include <memory>
#include <cstdlib>
#include <thread>

#include "streams.hpp"
#include "utils.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "ReplicationManager.hpp"

class Server {

private :
	std::string address;
	int port;
	std::vector<std::shared_ptr<std::thread>> threads;

public :
	std::vector<std::shared_ptr<uvw::TCPHandle>> clients;

	ReplicationManager RM;

	std::vector<GameObject*> world;

	Server(std::string ip, int port);

	void Listen(uvw::Loop &loop);

	void OnListenEvent(const uvw::ListenEvent &, uvw::TCPHandle &srv);

	void OnCloseEvent(const uvw::CloseEvent &, uvw::TCPHandle &);

	void OnEndEvent(const uvw::EndEvent &, uvw::TCPHandle &client);

	void OnDataEvent(const uvw::DataEvent& evt, uvw::TCPHandle &client);

	void SendToAll(char* msg, size_t size);

	void SendWorldToAll();






	void TestLoop();



};