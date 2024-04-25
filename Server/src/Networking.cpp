#include "Networking.h"
#include <olebind.h>

SocketServer::SocketServer(std::string ipv4, uint32_t port) :
	m_ServerIP(ipv4), m_ServerPort(port), m_EndPoint(ipv4, port) {
	
}