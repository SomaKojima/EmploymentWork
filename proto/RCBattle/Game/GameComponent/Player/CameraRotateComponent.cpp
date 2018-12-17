#include "../../../pch.h"
#include "CameraRotateComponent.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

CameraRotateComponent::CameraRotateComponent(MyCamera* camera)
	:
	m_x(0.0f),
	m_y(0.0f),
	m_camera(camera)
{
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

		Quaternion cameraDir = q * m_me->GetTrans().dir.Get();

		// ----- �}�E�X�̍��W���E�B���h�E�̒����ɌŒ肷�� -----
		SetCursorPos(centralX, centralY);


		// ----- �J�����̍��W�����߂� -----
		Vector3 eyeVec = Vector3::Transform(Vector3::Forward * 5.0f, cameraDir);
		Vector3 eyePos = m_me->GetTrans().world.Get().Translation() + eyeVec;

		m_camera->SetPositionTarget(eyePos, m_me->GetTrans().world.Get().Translation());

		// ----- �J�����̏����X�V -----
		m_camera->SetDir(cameraDir);
	}
}
