#include "pch.h"
#include "MyCamera.h"
#include "Mouse.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

MyCamera::MyCamera()
	:
	m_angle(0.0f),
	m_dir(Quaternion::Identity),
	m_x(0.0f),
	m_y(0.0f),
	m_mode(GAME)
{
}

void MyCamera::Initialize()
{
	switch (m_mode)
	{
	case MyCamera::TITLE:
		TitleInitialize();
		break;
	case MyCamera::GAME:
		GameInitialize();
		break;
	default:
		break;
	}
}

void MyCamera::Update()
{
	switch (m_mode)
	{
	case MyCamera::TITLE:
		TitleCamera();
		break;
	case MyCamera::GAME:
		GameCamera();
		break;
	default:
		break;
	}
}

void MyCamera::TitleInitialize()
{
}

void MyCamera::TitleCamera()
{
	Vector3 eye = Vector3(8.0f, 4.0f, 0.0f);

	m_angle += 0.5f;
	Matrix rotY = Matrix::CreateRotationY(XMConvertToRadians(m_angle));
	eye = Vector3::Transform(eye, rotY);
	SetPositionTarget(eye, Vector3(0.0f, 0.0f, 0.0f));
}

void MyCamera::GameInitialize()
{
	m_dir = m_target->GetTrans().dir.Get();
}

void MyCamera::GameCamera()
{
	//// ----- ウィンドウの情報が取得できない場合 -----
	//if (!GetActiveWindow())
	//{
	//	return;
	//}

	//// ----- ウィンドウの長方形(Rectangle)の情報を取得する
	//RECT wRect;
	//GetWindowRect(GetActiveWindow(), &wRect);
	//int width = (wRect.right - wRect.left) / 2;
	//int height = (wRect.bottom - wRect.top) / 2;

	//// ----- ウィンドウの中心座標を取得する -----
	//int centralX = wRect.left + width;
	//int centralY = wRect.top + height;

	//// ----- マウスの座標を取得する -----
	//POINT p;
	//GetCursorPos(&p);

	//// ----- マウスの移動量を取得する -----
	//Vector2 mouseVec = Vector2(p.x - centralX, p.y - centralY);
	//mouseVec *= 0.1f;


	//// ----- 回転を更新 -----
	//m_x += XMConvertToRadians(mouseVec.x);
	//m_y += XMConvertToRadians(mouseVec.y);

	//if (m_y > XMConvertToRadians(90.0f))
	//{
	//	m_y = XMConvertToRadians(90.0f);
	//}
	//else if (m_y < -XMConvertToRadians(90.0f))
	//{
	//	m_y = -XMConvertToRadians(90.0f);
	//}

	//Quaternion q = Quaternion::CreateFromYawPitchRoll(0.0f, m_y, 0.0f);

	//m_dir = q * m_target->GetTrans().dir.Get();

	//// ----- マウスの座標をウィンドウの中央に固定する -----
	//SetCursorPos(centralX, centralY);


	//// ----- カメラの座標を求める -----
	//Vector3 eyeVec = Vector3::Transform(Vector3::Forward * 5.0f, m_dir);
	//Vector3 eyePos = m_target->GetTrans().world.Get().Translation() + eyeVec;

	//SetPositionTarget(eyePos, m_target->GetTrans().world.Get().Translation());
}

DirectX::SimpleMath::Vector3 MyCamera::GetUp()
{
	Vector3 up = Vector3::Up;
	switch (m_mode)
	{
	case MyCamera::TITLE:
		up = Vector3::Up;
		break;
	case MyCamera::GAME:
		up = Vector3::Transform(Vector3::Up, m_dir);
		break;
	}

	return up;
}
