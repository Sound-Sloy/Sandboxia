#include "NetworkString.h"

NetworkString::NetworkString()
{
	m_Length = 0;
}

NetworkString::NetworkString(std::string str)
{
	m_Length = str.length();
	m_Data = str.data();
}

NetworkString::NetworkString(const char* cstr)
{
	m_Length = strlen(cstr);
	m_Data = (char*)malloc(m_Length + 1);
	strncpy_s(m_Data, m_Length, cstr, m_Length);
	m_Data[m_Length] = '\0';
}

NetworkString::~NetworkString()
{
	if (m_Data) {
		free(m_Data);
		m_Length = 0;
		m_Data = nullptr;
	}
}

uint32_t NetworkString::Lenght() const
{
	return m_Length;
}

std::string NetworkString::String() const
{
	return std::string(m_Data);
}

void NetworkString::CString(char* out) const
{
	out = m_Data;
}


