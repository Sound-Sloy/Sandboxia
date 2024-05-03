#pragma once

#include <iostream>
#include <yojimbo.h>
#include <string>
#include <cstring>

class NetworkString {
public:
	NetworkString();
	NetworkString(std::string str);
	NetworkString(const char* cstr);
	~NetworkString();

	uint32_t Lenght() const;
	std::string String() const;
	void CString(char* out) const;

	constexpr bool operator==(const NetworkString& rhs) {
		return this->m_Length == rhs.m_Length and ((this->m_Data == nullptr and rhs.m_Data == nullptr) or strncmp(this->m_Data, rhs.m_Data, this->m_Length) == 0);
	}

	constexpr std::ostream& operator<<(std::ostream& os) const {
		for (uint32_t _ = 0; _ < m_Length; ++_) {
			os.put(m_Data[_]);
		}
		return os;
	}

	constexpr std::istream& operator>>(std::istream& is) const {
		is.read(m_Data, m_Length);
		return is;
	}

	template <typename Stream>
	bool Serialize(Stream& stream)
	{
		serialize_bits(stream, m_Length, sizeof(m_Length) * sizeof(uint8_t));

		if (m_Data) {
			free(m_Data);
			m_Data = nullptr;
		}

		m_Data = (char*)malloc(m_Length);
		serialize_bytes(stream, ClientVersion, sizeof(ClientVersion) * sizeof(uint8_t));
		
		return true;
	}

private:
	uint32_t m_Length = 0;
	char* m_Data = nullptr;
};