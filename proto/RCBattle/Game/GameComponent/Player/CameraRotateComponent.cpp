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
	// ----- ウィンドウの情報が取得できない場合 -----
	if (!GetActiveWindow())
	{
		return;
	}

	// ----- ウィンドウの長方形(Rectangle)の情報を取得する
	RECT wRect;
	GetWindowRect(GetActiveWindow(), &wRect);
	int width = (wRect.right - wRect.left) / 2;
	int height = (wRect.bottom - wRect.top) / 2;

	// ----- ウィンドウの中心座標を取得する -----
	int centralX = wRect.left + width;
	int centralY = wRect.top + height;

	// ----- マウスの座標をウィンドウの中央に固定する -----
	SetCursorPos(centralX, centralY);
}

CameraRotateComponent::~CameraRotateComponent()
{
}

void CameraRotateComponent::Update(DX::StepTimer const & timer)
{
	if (m_camera)
	{
		// ----- ウィンドウの情報が取得できない場合 -----
		if (!GetActiveWindow())
		{
			return;
		}

		// ----- ウィンドウの長方形(Rectangle)の情報を取得する
		RECT wRect;
		GetWindowRect(GetActiveWindow(), &wRect);
		int width = (wRect.right - wRect.left) / 2;
		int height = (wRect.bottom - wRect.top) / 2;

		// ----- ウィンドウの中心座標を取得する -----
		int centralX = wRect.left + width;
		int centralY = wRect.top + height;

		// ----- マウスの座標を取得する -----
		POINT p;
		GetCursorPos(&p);

		// ----- マウスの移動量を取得する -----
		Vector2 mouseVec = Vector2(p.x - centralX, p.y - centralY);
		mouseVec *= 0.1f;


		// ----- 回転を更新 -----
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


		// ----- マウスの座標をウィンドウの中央に固定する -----
		SetCursorPos(centralX, centralY);

		// ----- カメラの座標を求める -----
		Vector3 eyeVec = Vector3::Transform(Vector3(0.0f, 0.0f, -10.0f), cameraDir) + 
			Vector3::Transform(Vector3(0.0f, 2.0f * cos(m_y), 2.0f * sin(m_y)), m_me->GetTrans().dir.Get());
		Vector3 eyePos = m_me->GetTrans().world.Get().Translation() + eyeVec;

		Vector3 target = m_me->GetTrans().world.Get().Translation() + Vector3::Transform(Vector3(0.0f, 0.0f, 10.0f), cameraDir);

		m_camera->SetPositionTarget(eyePos, target);

		// ----- カメラの情報を更新 -----
		m_camera->SetDir(cameraDir);
	}
}
