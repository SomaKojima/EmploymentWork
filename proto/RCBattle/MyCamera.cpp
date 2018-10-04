#include "pch.h"
#include "MyCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

MyCamera::MyCamera()
	:
	m_angle(0.0f),
	m_mode(GAME)
{
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

void MyCamera::TitleCamera()
{
	Vector3 eye = Vector3(8.0f, 4.0f, 0.0f);

	m_angle += 0.5f;
	Matrix rotY = Matrix::CreateRotationY(XMConvertToRadians(m_angle));
	eye = Vector3::Transform(eye, rotY);
	SetPositionTarget(eye, Vector3(0.0f, 0.0f, 0.0f));
}

void MyCamera::GameCamera()
{
	Vector3 eyeVec = Vector3::Transform(Vector3(0.0f, 2.0f, -5.0f), m_target->GetTrans().GetDir());
	Vector3 eyePos =  m_target->GetTrans().GetWorld().Translation() + eyeVec;

	SetPositionTarget(eyePos, m_target->GetTrans().GetWorld().Translation());
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
		up = Vector3::Transform(Vector3::Up, m_target->GetTrans().GetDir());
		break;
	}

	return up;
}
