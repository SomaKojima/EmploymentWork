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
	//// ----- �E�B���h�E�̏�񂪎擾�ł��Ȃ��ꍇ -----
	//if (!GetActiveWindow())
	//{
	//	return;
	//}

	//// ----- �E�B���h�E�̒����`(Rectangle)�̏����擾����
	//RECT wRect;
	//GetWindowRect(GetActiveWindow(), &wRect);
	//int width = (wRect.right - wRect.left) / 2;
	//int height = (wRect.bottom - wRect.top) / 2;

	//// ----- �E�B���h�E�̒��S���W���擾���� -----
	//int centralX = wRect.left + width;
	//int centralY = wRect.top + height;

	//// ----- �}�E�X�̍��W���擾���� -----
	//POINT p;
	//GetCursorPos(&p);

	//// ----- �}�E�X�̈ړ��ʂ��擾���� -----
	//Vector2 mouseVec = Vector2(p.x - centralX, p.y - centralY);
	//mouseVec *= 0.1f;


	//// ----- ��]���X�V -----
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

	//// ----- �}�E�X�̍��W���E�B���h�E�̒����ɌŒ肷�� -----
	//SetCursorPos(centralX, centralY);


	//// ----- �J�����̍��W�����߂� -----
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
