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
	Vector3 eye = Vector3(0.0f, 2.0f, -5.0f);

	Matrix rotY = Matrix::CreateRotationY(m_target->GetAngle().y);
	eye = Vector3::Transform(eye, rotY);
	eye += Vector3::Transform(Vector3::Zero, m_target->GetWorld());

	SetPositionTarget(eye, Vector3::Transform(Vector3::Zero, m_target->GetWorld()));
}
