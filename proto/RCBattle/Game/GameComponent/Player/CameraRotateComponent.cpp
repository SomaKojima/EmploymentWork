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

		Quaternion cameraDir = q * m_me->GetTrans().dir.Get();

		// ----- マウスの座標をウィンドウの中央に固定する -----
		SetCursorPos(centralX, centralY);


		// ----- カメラの座標を求める -----
		Vector3 eyeVec = Vector3::Transform(Vector3::Forward * 5.0f, cameraDir);
		Vector3 eyePos = m_me->GetTrans().world.Get().Translation() + eyeVec;

		m_camera->SetPositionTarget(eyePos, m_me->GetTrans().world.Get().Translation());

		// ----- カメラの情報を更新 -----
		m_camera->SetDir(cameraDir);
	}
}
