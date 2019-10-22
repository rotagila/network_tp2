#pragma once

#include <uvw.hpp>
#include <memory>
#include <cstdlib>

#include "streams.hpp"
#include "utils.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "ReplicationManager.hpp"


class Client {

private:
	std::string address;
	int port;

public:
	ReplicationManager *RM = new ReplicationManager();

	Client(std::shared_ptr<uvw::Loop> loop, std::string ip, int port);

	void ConnectLoop(uvw::Loop &loop);

	void Connect(uvw::TCPHandle &tcp);

	void OnConnectEvent(const uvw::ConnectEvent &, uvw::TCPHandle &srv);

	void OnErrorEvent(const uvw::ErrorEvent &, uvw::TCPHandle &srv);

	void OnDataEvent(const uvw::DataEvent& evt, uvw::TCPHandle &srv);

};