#include "Player.h"

Player::Player(std::string name, uint32_t clientIndex, Vec3<float> pos) :
	m_Name(name), m_ClientIndex(clientIndex), m_Pos(pos)
{
}

Vec3<float> Player::GetPos() const
{
	return m_Pos;
}

Vec3<float>& Player::Pos()
{
	return m_Pos;
}

void Player::SetPos(Vec3<float> pos)
{
	m_Pos = pos;
}

std::string Player::GetName() const
{
	return m_Name;
}

uint32_t Player::GetClientIndex() const
{
	return m_ClientIndex;
}

bool Player::IsConnected() const
{
	return m_bConnected;
}

void Player::SetConnected(bool connected)
{
	m_bConnected = connected;
}



