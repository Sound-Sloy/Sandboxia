#pragma once

#include <string>
#include <shared/utils/Vec3.h>

class Player {
public:
	Player(std::string name, uint32_t clientIndex, Vec3<float> pos);

	Vec3<float> GetPos() const;
	Vec3<float>& Pos();
	void SetPos(Vec3<float> pos);

	std::string GetName() const;
	uint32_t GetClientIndex() const;

	bool IsConnected() const;
	void SetConnected(bool connected);
private:
	std::string m_Name;
	uint32_t m_ClientIndex = 0;
	Vec3<float> m_Pos = { 0.f, 0.f, 0.f };

	bool m_bConnected = false;
};