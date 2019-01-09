#include "../../../pch.h"
#include "CameraRotateComponent.h"
#include "../../Command/Command.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

CameraRotateComponent::CameraRotateComponent(MyCamera* camera, Type type)
	:
	m_x(0.0f),
	m_y(0.0f),
	m_type(type),
	m_camera(camera)
{
	// ----- �E�B���h�E�̏�񂪎擾�ł��Ȃ��ꍇ -----
	if (!GetActiveWindow())
	{
		return;
	}

	// ----- �E�B���h�E�̒����`(Rectangle)�̏����擾����
	RECT wRect;
	GetWindowRect(GetActiveWindow(), &wRect);
	int width = (wRect.right - wRect.left) / 2;
	int height = (wRect.bottom - wRect.top) / 2;

	// ----- �E�B���h�E�̒��S���W���擾���� -----
	int centralX = wRect.left + width;
	int centralY = wRect.top + height;

	// ----- �}�E�X�̍��W���E�B���h�E�̒����ɌŒ肷�� -----
	SetCursorPos(centralX, centralY);
}

CameraRotateComponent::~CameraRotateComponent()
{
}

void CameraRotateComponent::Update(DX::StepTimer const & timer)
{
	if (m_camera)
	{
		// ----- �E�B���h�E�̏�񂪎擾�ł��Ȃ��ꍇ -----
		if (!GetActiveWindow())
		{
			return;
		}

		// ----- �E�B���h�E�̒����`(Rectangle)�̏����擾����
		RECT wRect;
		GetWindowRect(GetActiveWindow(), &wRect);
		int width = (wRect.right - wRect.left) / 2;
		int height = (wRect.bottom - wRect.top) / 2;

		// ----- �E�B���h�E�̒��S���W���擾���� -----
		int centralX = wRect.left + width;
		int centralY = wRect.top + height;

		// ----- �}�E�X�̍��W���擾���� -----
		POINT p;
		GetCursorPos(&p);

		// ----- �}�E�X�̈ړ��ʂ��擾���� -----
		Vector2 mouseVec = Vector2(p.x - centralX, p.y - centralY);
		mouseVec *= 0.1f;


		// ----- ��]���X�V -----
		m_x += XMConvertToRadians(mouseVec.x);
		m_y += XMConvertToRadians(mouseVec.y);

		if (m_y > XMConvertToRadians(90.0f))
		{
			m_y = XMConvertToRadians(90.0f);
		}
		else if (m_y < -XMConvertToRadians(90.0f))
		{
			m_y = -XMConvertToRadians(90.0f);
		}

		Quaternion q = Quaternion::CreateFromYawPitchRoll(-m_x, m_y, 0.0f);

		Quaternion dir = Quaternion::Identity;
		Vector3 upDir = Vector3::Transform(Vector3::Up, m_me->GetTrans().dir.Get());
		float degree = mouseVec.x;
		Quaternion cameraDir = Quaternion::Identity;
		switch (m_type)
		{
		case Normal:
			q = Quaternion::CreateFromYawPitchRoll(-m_x, m_y, 0.0f);
			cameraDir = q;
			break;
		case CameraRotateComponent::Horizon:
			q = Quaternion::CreateFromYawPitchRoll(-m_x, 0.0f, 0.0f);
			cameraDir = q * m_me->GetTrans().dir.Get();
			break;
		case CameraRotateComponent::Vertical:
			q = Quaternion::CreateFromYawPitchRoll(0.0f, m_y, 0.0f);
			if (mouseVec.x > 0)
			{
				dir = Quaternion::CreateFromAxisAngle(upDir, -XMConvertToRadians(degree));
			}
			else if (mouseVec.x < 0)
			{
				dir = Quaternion::CreateFromAxisAngle(upDir, -XMConvertToRadians(degree));
			}
			m_me->GetTrans().dir.Set(m_me->GetTrans().dir.Get() * dir);
			cameraDir = q * m_me->GetTrans().dir.Get();
			break;
		case CameraRotateComponent::NONE:
			q = Quaternion::CreateFromYawPitchRoll(0.0f, 0.0f, 0.0f); 
			cameraDir = q * m_me->GetTrans().dir.Get();
			break;
		}


		// ----- �}�E�X�̍��W���E�B���h�E�̒����ɌŒ肷�� -----
		SetCursorPos(centralX, centralY);

		// ----- �J�����̍��W�����߂� -----
		Vector3 eyeVec = Vector3::Transform(Vector3(0.0f, 0.0f, -10.0f), cameraDir) + 
			Vector3::Transform(Vector3(0.0f, 2.0f * cos(m_y), 2.0f * sin(m_y)), m_me->GetTrans().dir.Get());
		Vector3 eyePos = m_me->GetTrans().world.Get().Translation() + eyeVec;

		Vector3 target = m_me->GetTrans().world.Get().Translation() + Vector3::Transform(Vector3(0.0f, 0.0f, 10.0f), cameraDir);

		m_camera->SetPositionTarget(eyePos, target);

		// ----- �J�����̏����X�V -----
		m_camera->SetDir(cameraDir);
	}
}
