#include "../../../pch.h"
#include "ResultCameraComponent.h"
#include "../../Scene/SceneManager.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

ResultCameraComponent::ResultCameraComponent(MyCamera * camera)
	:
	m_camera(camera),
	m_angle(0.0f),
	m_time(0),
	m_count(0)
{
}

ResultCameraComponent::~ResultCameraComponent()
{
}

void ResultCameraComponent::Update(DX::StepTimer const & timer)
{
	Vector3 eye = Vector3(-3.0f, 0.0f, 3.0f);

	m_angle += 0.8f;
	Vector3 up = Vector3::Transform(Vector3::Up, m_me->GetTrans().dir.Get());
	Quaternion q = Quaternion::CreateFromAxisAngle(up, XMConvertToRadians(m_angle));
	eye = Vector3::Transform(eye, m_me->GetTrans().dir.Get() * q);
	eye = eye + m_me->GetTrans().world.Get().Translation();

	m_camera->SetPositionTarget(eye, m_me->GetTrans().world.Get().Translation());


	// マウスの入力でタイトルに戻る
	// マウスの作成 
	Mouse::State mouse = Mouse::Get().GetState();
	if (mouse.leftButton)
	{
		m_count++;
		if (m_count > 3)
		{
			SceneManager* sceneManager = SceneManager::GetInstance();
			sceneManager->ChangeSceneID(SceneManager::SceneID::Title);
		}
	}

	// 時間経過でタイトルに戻る
	m_time++;
	if (m_time > 600)
	{
		SceneManager* sceneManager = SceneManager::GetInstance();
		sceneManager->ChangeSceneID(SceneManager::SceneID::Title);
	}
}
