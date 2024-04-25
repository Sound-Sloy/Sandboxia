#pragma once

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#define ASIO_STANDALONE 1

#include <cstdint>
#include <string>
#include <asio.hpp>


// https://www.rogiel.com/en/blog/getting-started-with-asio-cpp-creating-tcp-server


class SocketServer {
public:
	SocketServer(std::string ipv4 = "", uint32_t port = 25565);
private:
	std::string m_ServerIP = "";
	uint32_t m_ServerPort = 25565;
	
	asio::io_service m_Service;
	asio::ip::tcp::endpoint m_EndPoint;
	asio::ip::tcp::acceptor m_Acceptor;

};
