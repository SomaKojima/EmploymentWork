#pragma once

#include "Camera.h"
#include "Game\/Object\Entity.h"

class MyCamera : public Camera
{
public:
	enum CAMERA_MODE
	{
		TITLE,
		GAME
	};

private:
	CAMERA_MODE m_mode;

	float m_angle;

	DirectX::SimpleMath::Quaternion m_dir;

	Entity* m_target;

public:
	MyCamera();

	void Initialize();
	void Update();

	void SetCameraModel(CAMERA_MODE mode) { 
		ResetCamera();
		m_mode = mode;
	}

	void SetPlayer(Entity* entity) { m_target = entity; }

	void TitleInitialize();
	void TitleCamera();

	void GameInitialize();
	void GameCamera();

	DirectX::SimpleMath::Vector3 GetUp();

	DirectX::SimpleMath::Quaternion GetDir() { return m_dir; }
	void SetDir(DirectX::SimpleMath::Quaternion dir) { m_dir = dir; }

};