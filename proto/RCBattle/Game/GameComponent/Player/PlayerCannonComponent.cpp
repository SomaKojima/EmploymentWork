#include "../../../pch.h"
#include "PlayerCannonComponent.h"

#include "../../Object/Factory/BulletFactory.h"
#include "../../Object/EntityVector.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

PlayerCannonComponent::PlayerCannonComponent(MyCamera* camera)
	:
	m_camera(camera)
{
}

PlayerCannonComponent::~PlayerCannonComponent()
{
}

void PlayerCannonComponent::Update(DX::StepTimer const & timer)
{
	if (m_camera)
	{
		Quaternion inv = Quaternion::Identity;

		m_me->GetParent()->GetTrans().dir.Get().Inverse(inv);

		Quaternion q1 = m_camera->GetDir();
		m_me->GetTrans().dir.Set(q1 * inv);
		//Vector3 target = Vector3::Transform(m_camera->GetTargetPosition(), m_camera->GetDir());

		//Vector3 targetVec = target - m_me->GetTrans().pos.Get();
		//targetVec.Normalize();

		//// p¨‚ğ‡‚í‚¹
		//Vector3 forward = Vector3::Transform(Vector3::Forward, m_me->GetTrans().dir.Get());
		//// ‰ñ“]²ŒvZ
		//Vector3 axis = forward.Cross(targetVec);
		//if (axis != Vector3::Zero)
		//{
		//	// Šp“x‚ğ‹‚ß‚é
		//	float cosine = forward.Dot(targetVec);
		//	if (cosine > 1.0f)
		//	{
		//		cosine = 1.0f;
		//	}
		//	float rot = acos(cosine);
		//	Quaternion  Q1 = Quaternion::CreateFromAxisAngle(axis, rot);



		//	Quaternion inv = Quaternion::Identity;
		//	m_me->GetParent()->GetTrans().dir.Get().Inverse(inv);

		//	m_me->GetTrans().dir.Set(m_me->GetTrans().dir.Get() * Q1);
		//}

	}
}