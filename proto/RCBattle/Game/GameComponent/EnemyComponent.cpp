#include "EnemyComponent.h"
#include "../Scene/SceneManager.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

EnemeyComponent::EnemeyComponent(Entity* target)
	:
	m_count(3),
	m_target(target)
{
}

EnemeyComponent::~EnemeyComponent()
{
}

void EnemeyComponent::Update(DX::StepTimer const & timer)
{
}

void EnemeyComponent::OnCollide(Entity & collide, Collision::CollisionData* data)
{
	if (collide.GetName() == "Bullet")
	{
		m_count--;
		if (m_count < 0)
		{
			SceneManager* sceneManager = SceneManager::GetInstance();
			sceneManager->ChangeSceneID(SceneManager::SceneID::Title);
		}
	}

	if (m_target)
	{
		Entity* cannon = m_me->GetChild("cannon");
		Vector3 targetVec = m_me->GetTrans().pos.Get() - m_target->GetTrans().pos.Get();
		Vector3 forward = Vector3::Transform(Vector3::Forward, m_me->GetTrans().dir.GetWorld());
		Vector3 axis = targetVec.Cross(forward);

		targetVec.Normalize();

		float cosine = targetVec.Dot(forward);
		if (cosine > 1.0f)
		{
			cosine = 1.0f;
		}

		if (axis != Vector3::Zero)
		{
			Quaternion Q1 = Quaternion::CreateFromAxisAngle(axis, -acos(cosine));

			if (cannon)
			{
				cannon->GetTrans().dir.Set(Q1);
			}
		}
	}
}
