#include "pch.h"
#include "MyCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

MyCamera::MyCamera()
	:
	m_angle(0.0f),
	m_dir(Quaternion::Identity),
	m_distance(Vector2::Zero),
	m_mousePos(Vector2::Zero),
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

	// マウスの取得
	Mouse::State mouse = Mouse::Get().GetState();

	// マウスの位置を更新
	SetCursorPos(0, 0);
	Vector2 mousePos((float)mouse.x, (float)mouse.y);

	m_mousePos = mousePos;
}

void MyCamera::GameCamera()
{
	/*Vector3 eyeVec = Vector3::Transform(Vector3(0.0f, 2.0f, -5.0f), m_target->GetTrans().dir.Get());
	Vector3 eyePos =  m_target->GetTrans().world.Get().Translation() + eyeVec;*/

	//// マウスの取得
	//Mouse::State mouse = Mouse::Get().GetState();

	//// マウスの座標を取得
	//Vector2 mousePos((float)mouse.x, (float)mouse.y);
	//m_distance += (mousePos - m_mousePos) * 0.001f;

	//Quaternion q = Quaternion::CreateFromYawPitchRoll(-m_distance.x, m_distance.y, m_dir.z);
	//m_dir = q;

	// マウスの位置を更新

	//SetCursorPos(0, 0);
	


	Vector3 eyeVec = Vector3::Transform(Vector3(0.0f, 2.0f, -5.0f), m_dir);
	Vector3 eyePos = m_target->GetTrans().world.Get().Translation() + eyeVec;

	SetPositionTarget(eyePos, m_target->GetTrans().world.Get().Translation());
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
		up = Vector3::Transform(Vector3::Up, m_target->GetTrans().dir.Get());
		break;
	}

	return up;
}
