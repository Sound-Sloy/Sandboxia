#pragma once
#include <raylib.h>
#include <raymath.h>
#include <shared/utils/Vec3.h>

enum class SCameraMode {
	Orbital
};

class SBCamera {
public:
	SBCamera() = default;
	SBCamera(Camera3D camera);

	const Camera3D* GetCameraPtr() const;

	Vec3<float> GetPos() const;
	void SetPos(Vec3<double> pos);
	void SetPos(Vector3 pos);



	void Update();

	~SBCamera() = default;
	
private:
	Camera3D m_Camera;
};