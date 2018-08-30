#pragma once

#include "Camera.h"
#include "Player.h"

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

	Player* m_player;
public:
	MyCamera();

	void Update();

	void SetCameraModel(CAMERA_MODE mode) { 
		ResetCamera();
		m_mode = mode; 
	}

	void SetPlayer(Player* player) { m_player = player; }

	void TitleCamera();

	void GameCamera();
};